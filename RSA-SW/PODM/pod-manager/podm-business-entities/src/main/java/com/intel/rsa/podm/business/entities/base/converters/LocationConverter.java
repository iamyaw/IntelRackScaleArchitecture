/*
 * Copyright (c) 2015 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.intel.rsa.podm.business.entities.base.converters;

import com.intel.rsa.common.types.locations.Location;

public final class LocationConverter implements PropertyTypeConverter<String, Location> {
    @Override
    public String convertFromMappedType(Location location) {
        return location == null
                ? null
                : location.toString();
    }

    @Override
    public Location convertToMappedType(String text) {
        return text == null
                ? null
                : new Location(text);
    }
}