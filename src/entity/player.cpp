/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#include <entity/player.h>
#include <common.h>

entity::player::player(glm::vec3 newpos, glm::vec3 newangle, GLuint texunit, nlohmann::json& conf) : render::camera(newpos, newangle){
    model = new render::obj::obj3d(
        QUOTE(__PREFIX) + std::string("assets/test.obj"),
        newpos, 
        QUOTE(__PREFIX) + std::string("assets/unknowntex.bmp"),
        texunit,
        newangle
    );
    keymap = conf;
}

