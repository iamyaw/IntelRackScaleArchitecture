/*!
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
 *
 * @file exception_base.hpp
 *
 * @brief Exception base class interface
 * */

#ifndef AGENT_FRAMEWORK_EXCEPTIONS_EXCEPTION_BASE_HPP
#define AGENT_FRAMEWORK_EXCEPTIONS_EXCEPTION_BASE_HPP

#include "agent-framework/exceptions/error_codes.hpp"
#include "logger/logger_factory.hpp"
#include <jsonrpccpp/common/exception.h>

namespace agent_framework {
namespace exceptions {

/* Base exception implementation */
class ExceptionBase : public jsonrpc::JsonRpcException {
public:
    /*!
     * @brief Create exception object
     * @param code error code
     * @param message error message
     */
    explicit ExceptionBase(const ErrorCode code, const std::string& message);

    virtual ~ExceptionBase();

    /*!
     * @brief Get error code
     * @return Error code
     */
    virtual ErrorCode get_error_code() const;

    /*!
     * @brief Get exception message
     * @return ExceptionBase message
     */
    virtual const std::string& get_message() const;

private:
   ErrorCode m_error_code{ErrorCode::NoError};
   std::string m_message{};
};

} // namesapce exceptions
} // namespace agent_framework

#endif	/* AGENT_FRAMEWORK_EXCEPTIONS_EXCEPTION_BASE_HPP */
