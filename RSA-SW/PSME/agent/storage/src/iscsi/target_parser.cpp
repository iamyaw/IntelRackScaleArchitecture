/*!
 * @section LICENSE
 *
 * @copyright
 * Copyright (c) 2015 Intel Corporation
 *
 * @copyright
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * @copyright
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * @copyright
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @section DESCRIPTION
*/

#include "iscsi/target_parser.hpp"
#include "iscsi/tokenizer.hpp"
#include <regex>
#include <algorithm>

using namespace agent::storage::iscsi::tgt;

namespace {
std::string &ltrim(std::string &s) {
    s.erase(s.begin(),
            std::find_if(s.begin(), s.end(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

std::string &rtrim(std::string &s) {
     s.erase(std::find_if(s.rbegin(), s.rend(),
             std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
                       s.end());
    return s;
}

std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
}

class TargetParser::Impl {
public:
    enum class Section {
        NONE,
        SYSTEM,
        NEXUS,
        LUN,
        ACCOUNT,
        ACL
    };

    TargetDataSVec parse(const std::string& text) {
        TargetDataSVec targets_data{};

        Tokenizer tokens{text, "\n"};
        while (tokens.next_token()) {
            const auto& token = tokens.get_token();
            if (is_null_terminator(token)) {
                continue;
            }

            if (auto target = check_target(token)) {
                m_section = Section::NONE;
                targets_data.emplace_back(target);
            }

            check_section(token);

            if (Section::LUN == m_section) {
                check_lun(token);
                check_lun_device_path(token);
            }

            if (Section::ACL == m_section) {
                check_acl_initiator(token);
            }

        }
        return targets_data;
    }

    TargetDataSPtr check_target(const std::string& text) {
        std::smatch match;
        if (std::regex_match(text, match, m_target_re)) {
            auto target_obj  = std::make_shared<TargetData>();
            target_obj->set_target_id(
                    static_cast<std::int32_t>(std::stoi(match[1].str())));
            target_obj->set_target_iqn(match[2].str());
            m_target_data = target_obj;
            return target_obj;
        }
        return {};
    }

    void check_lun(const std::string& text) {
        std::smatch match;
        if (std::regex_match(text, match, m_lun_re)) {
            auto lun_no = static_cast<std::uint64_t>(
                                                std::stoi(match[1].str()));
            if (0 == lun_no) { // lun 0 controller
                m_lun_data = nullptr;
                return;
            }
            auto lun_obj = std::make_shared<LunData>();
            lun_obj->set_lun(lun_no);
            m_lun_data = lun_obj;
            if (m_target_data) {
                m_target_data->add_lun_data(lun_obj);
            }
        }
    }

    void check_lun_device_path(const std::string& text) {
        std::smatch match;
        if (std::regex_match(text, match, m_lun_device_re)) {
            if (m_lun_data) {
                m_lun_data->set_device_path(match[1].str());
            }
        }
    }

    void check_section(const std::string& text) {
        if (std::regex_match(text, m_system_section_re)) {
            m_section = Section::SYSTEM;
        } else if (std::regex_match(text, m_lun_section_re)) {
            m_section = Section::LUN;
        } else if (std::regex_match(text, m_account_section_re)) {
            m_section = Section::ACCOUNT;
        } else if (std::regex_match(text, m_acl_section_re)) {
            m_section = Section::ACL;
        }
    }

    void check_acl_initiator(const std::string& text) {
        if (m_target_data &&
            !std::regex_match(text, m_acl_address_re) &&
            !std::regex_match(text, m_acl_section_re)) {
            auto initiator = text;
            m_target_data->set_target_initiator(trim(initiator));
        }
    }

    bool is_null_terminator(const std::string& text) {
        return 1 == text.size() && ('\0' == text[0]);
    }

private:
    Section m_section{Section::NONE};
    TargetDataSPtr m_target_data{nullptr};
    LunDataSPtr m_lun_data{nullptr};

    std::regex m_target_re{R"(.*Target\s*([\d]+):\s*(.+).*)"};
    std::regex m_lun_re{R"(.*LUN:\s*([\d]+).*)"};
    std::regex m_lun_device_re{R"(.*Backing store path:\s*(.+).*)"};
    // Regex for check IPv4 and IPv6 addresses
    std::regex m_acl_address_re{R"(.*(((([1]?\d)?\d|2[0-4]\d|25[0-5])\.){3})"
                        R"((([1]?\d)?\d|2[0-4]\d|25[0-5]))|([\da-fA-F]{1,4})"
                        R"("(\:[\da-fA-F]{1,4}){7})|(([\da-fA-F]{1,4}:){0,5})"
                        R"(::([\da-fA-F]{1,4}:){0,5}[\da-fA-F]{1,4}).*)"};

    std::regex m_system_section_re{R"(.*System information:.*)"};
    std::regex m_lun_section_re{R"(.*LUN information:.*)"};
    std::regex m_account_section_re{R"(.*Account information:.*)"};
    std::regex m_acl_section_re{R"(.*ACL information:.*)"};
};

TargetParser::TargetParser() : m_impl{new TargetParser::Impl{}} {}
TargetParser::~TargetParser() {}

TargetDataSVec TargetParser::parse(const std::string& text) {
    return m_impl->parse(text);
}