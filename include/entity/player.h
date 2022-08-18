/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
#include <rendering/camera.h>
#include <entity/entity.h>

namespace entity {
    class player: public entity, public render::camera {
        public:
            // pos, angle, texunit, JSON keymap
            player(glm::vec3, glm::vec3, GLuint, nlohmann::json&); 
            void poll();

        private:
            nlohmann::json keymap;
    };
}

