/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

/*
Description:

The namespace render::obj contains three classes: obj, obj3d and obj2d. One is
for rendering 3D entities, and the other for 2D sprites. They are very similar
to one another, and bc of this, a single interface should be able to interface
with both classes in a very general way.

Namespace: render::obj;
Functions: glm::quat rotateFromVectors(glm::vec3, glm::vec3 [default]);
Classes: obj; obj3d; obj2d;

*/

#pragma once

#include <rendering/obj/tinyObjLoader.h>
#include <rendering/obj/texture.h>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>

// Object wrapper namespace
namespace render::obj {
    glm::quat rotateFromVectors(glm::vec3, glm::vec3 = glm::vec3(0, 0, 0));

    class obj {
        public:
            virtual size_t getBufferSize();
            virtual void rotate(float, glm::vec3);
            virtual void lookat(glm::vec3);

            GLuint vb;
            GLuint uv;
            glm::mat4 model;
            texture* tex;
        protected:
            glm::vec3 pos;      // Position vector
            glm::quat qangle;   // Orientation quaternion (actually used in the math)
            float prevqangle;   // previous orientation vector
            tinyobj::ObjReader* reader;
            std::vector<GLfloat> vertvec;
    };

    class obj3d : public obj {
        public:
            obj3d(std::string, glm::vec3, std::string = "", GLuint = 0, glm::vec3 angle = glm::vec3(0, 0, 0));
            ~obj3d();
    };

    class obj2d : public obj {
        public:
            obj2d(std::string, glm::vec3);
    };
}
