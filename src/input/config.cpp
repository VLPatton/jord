/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#include <input/config.h>
#include <fstream>
#include <string>

input::config::config() {
    std::fstream rawstream = std::fstream(QUOTE(__PREFIX) + std::string("assets/config.json"), rawstream.in);
    data = nlohmann::json::parse(rawstream);
}

