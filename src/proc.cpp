/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#include <proc/main.h>

proc::proc::proc(std::string title) {
    windowTitle = title;
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);

    cam = new render::camera(glm::vec3(3, 3, 3));
}

proc::proc::~proc() {

}

bool proc::proc::windowShouldClose() {
    return glfwWindowShouldClose(window);
}

void proc::proc::windowSwapBuffers() {
    glfwSwapBuffers(window);
}

glm::mat4 proc::proc::camGetView() {
    return cam->getview();
}
