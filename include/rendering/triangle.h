/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace render {
    class triangle {
        public:
            triangle(GLfloat[9], glm::vec3);    // Reltives for vertices, followed by absolute position of the whole triangle
            ~triangle();

            GLfloat verticesNorm[9];
            GLuint vb;
            glm::mat4 model;
    };
}