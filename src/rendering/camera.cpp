/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#include <rendering/camera.h>

render::camera::camera(glm::vec3 posIn, glm::vec3 angleIn) {
    pos = posIn;
    angle = angleIn;
    view = glm::lookAt(
        pos,
        angle,
        glm::vec3(0, 1.0f, 0)
    );
}

glm::mat4 render::camera::getview() {
    return view;
}

glm::vec3 render::camera::getangle() {
    return angle;
}

glm::vec3 render::camera::getpos() {
    return pos;
}

void render::camera::moveto(glm::vec3 newpos) {
    pos = newpos;
    view = glm::lookAt(
        pos,
        angle,
        glm::vec3(0, 1.0f, 0)
    );
}

void render::camera::lookat(glm::vec3 newangle) {
    pos = newangle;
    view = glm::lookAt(
        pos,
        angle,
        glm::vec3(0, 1.0f, 0)
    );
}

