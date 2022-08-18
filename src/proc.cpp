/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#include "input/config.h"
#include <proc/main.h>

proc::proc::proc(std::string title) {
    windowTitle = title;
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    ilInit(); 

    // Initialize rendering
    vertArrObj = new render::va();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    shader = new render::shaders(QUOTE(__PREFIX) + std::string("shaders/vertex.vs"), QUOTE(__PREFIX) + std::string("shaders/fragment.fs"));

    conf = new input::config();

    plyr = new entity::player(
        glm::vec3(3, 3, 3),
        glm::vec3(0, 0, 0),
        shader->getUniLoc("texunit"),
        conf->data["keymap"]
    );
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
    return plyr->getview();
}

glm::mat4 proc::proc::plrGetModl() {
    return plyr->model->model;
}

void proc::proc::plrDraw() {
    vertArrObj->objDraw(plyr->model);
}
