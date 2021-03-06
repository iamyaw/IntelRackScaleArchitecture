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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(command)
add_subdirectory(discovery)
add_subdirectory(sysfs)
add_subdirectory(iscsi)
add_subdirectory(lvm)

add_library(storage-commands STATIC
    $<TARGET_OBJECTS:storage-command-conf-based>
)

add_library(discovery-storage
    $<TARGET_OBJECTS:discovery-impl-storage>
    $<TARGET_OBJECTS:dependency-resolver-impl-storage>
    $<TARGET_OBJECTS:iscsi-tgt>
    $<TARGET_OBJECTS:iscsi-tgt-config>
    $<TARGET_OBJECTS:sysfs-api>
    $<TARGET_OBJECTS:lvm-api>
)

add_executable(psme-storage
    main.cpp
)

target_link_libraries(psme-storage
    ${AGENT_STORAGE_LIBRARIES}
    discovery-storage
    ${AGENT_FRAMEWORK_LIBRARIES}
    ${UUID_LIBRARIES}
    ${LOGGER_LIBRARIES}
    ${PCA95XX_LIBRARIES}
    ${CONFIGURATION_LIBRARIES}
    ${JSONCXX_LIBRARIES}
    ${SAFESTRING_LIBRARIES}
    ${SYSFS_LIBRARIES}
    ${LVM2APP_LIBRARIES}
    pthread
    jsonrpccpp-server
    jsonrpccpp-client
    jsonrpccpp-common
    jsoncpp
    ${MICROHTTPD_LIBRARIES}
    ${CURL_LIBRARIES}
)
