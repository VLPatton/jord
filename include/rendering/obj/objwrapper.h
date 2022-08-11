/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <rendering/obj/tinyObjLoader.h>
#include <rendering/obj/texture.h>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// OBJect wrapper namespace
namespace render::obj {
    class obj3d {
        public:
            obj3d(std::string, glm::vec3);
            obj3d(std::string, glm::vec3, std::string, GLuint);
            ~obj3d();
            size_t getBufferSize();

            GLuint vb;
            GLuint uv;
            glm::mat4 model;
            texture* tex;
        private:
            tinyobj::ObjReader* reader;
            std::vector<GLfloat> vertvec;
    };
}
