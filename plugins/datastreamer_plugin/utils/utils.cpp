// Copyright 2022 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Monitor.
//
// eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

/**
 * @file ReaderHandler.cpp
 */

#include <sstream>

#include "utils.hpp"

namespace eprosima {
namespace plotjuggler {
namespace utils {

std::string get_timestamp_string(
        const fastrtps::rtps::Time_t& timestamp)
{
    std::stringstream ss;
    ss << timestamp;
    return ss.str();
}

} /* namespace utils */
} /* namespace plotjuggler */
} /* namespace eprosima */
