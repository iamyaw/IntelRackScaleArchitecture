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

#include "agent-framework/eventing/event_msg.hpp"

using namespace agent_framework::generic;

Json::Value EventMsg::to_json() const {
    Json::Value ret;

    ret["id"] = get_id();
    ret["newState"] = ModuleState::get_state_name(get_state());
    ret["transition"] = StateMachineTransition::get_transition_name(
                                                            get_transition());
    return ret;
}
