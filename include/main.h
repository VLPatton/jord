/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <rendering/camera.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <IL/il.h>

#define WIN_TITLE "game"

#define DO_QUOTE(x) #x
#define QUOTE(x) DO_QUOTE(x)

#ifndef __PREFIX
#define __PREFIX ./
#endif

namespace proc {
    class proc {
        public:
            proc(std::string);
            ~proc();
            bool windowShouldClose();
            void windowSwapBuffers();
            glm::mat4 camGetView();

        private:
            GLFWwindow* window;
            render::camera*     cam;

            const int windowWidth = 1366;
            const int windowHeight = 768;
            std::string windowTitle;
    };
}
