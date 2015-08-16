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
 * */

#include "agent-framework/command/compute/get_components.hpp"

using namespace agent_framework;
using namespace agent_framework::command;
using namespace agent_framework::generic;

/*! Stubs GetComponents implementation */
class GetComponents : public compute::GetComponents {
public:
    GetComponents() { }

    using compute::GetComponents::execute;

    void execute(const Request&, Response& response) {
        std::vector<Response::Component> components{};
        components.push_back({"RSAComputeModule",
                              "321e4567-e89b-12d3-a456-000000000001",
                              {
                                  {"RSABlade", "321e4567-e89b-12d3-a456-000000000002"},
                                  {"RSABlade", "321e4567-e89b-12d3-a456-00000000i003"},
                                  {"RSABlade", "321e4567-e89b-12d3-a456-000000000004"}
                              }});
        components.push_back({"RSAChassis", "321e4567-e89b-12d3-a456-436655440227"});
        response.set_components(components);
    }

    ~GetComponents();
};

GetComponents::~GetComponents() { }

static Command::Register<GetComponents> g("Stubs");