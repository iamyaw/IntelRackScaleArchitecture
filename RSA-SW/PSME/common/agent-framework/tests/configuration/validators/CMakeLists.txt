# <license_header>
#
# Copyright (c) 2015 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# </license_header>

if (NOT GTEST_FOUND)
    return()
endif()

add_gtest(validators_test
    test_runner.cpp
    min_test.cpp
    max_test.cpp
    type_test.cpp
    address_test.cpp
    url_test.cpp
)

target_link_libraries(validators_test
    ${LOGGER_LIBRARIES}
    ${UUID_LIBRARIES}
    ${AGENT_FRAMEWORK_LIB}
    ${SAFESTRING_LIBRARIES}
    agent-mocks
    ${PCA95XX_LIBRARIES}
    ${CONFIGURATION_LIBRARIES}
    ${JSONCXX_LIBRARIES}
)

