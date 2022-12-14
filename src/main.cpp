/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#include "rendering/obj/objwrapper.h"
#include <cstdio>
#include <cassert>
#include <proc/main.h>      // Most of the main includes are in here
#include <rendering/vertexarray.h>
#include <rendering/shaders.h>
#include <input/input.h>

using namespace render;

int main(void) {
    // Force glfw to init, if it doesn't, call abort()
    assert(glfwInit());

    glfwWindowHint(GLFW_SAMPLES, 4);                                // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // We want OpenGL Core

    // Initialize OpenGL and DevIL
    // NOTE: this is the most important object in the program, as it contains 
    // the VAO and shader objects, as well as initializes GLFW and GLEW
    proc::proc* the = new proc::proc(WIN_TITLE);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Cull faces which the camera cannot see
    glEnable(GL_CULL_FACE);

    glClearColor(0.4f, 0.6f, 0.9f, 0.0f);   // Sky blue background

    // Create our perspective matrix (TODO: add dynamic FOV and aspect ratio)
    const glm::mat4 projection = glm::perspective(
        glm::radians(70.0f),    // The vertical Field of View
        16.0f / 9.0f,           // Aspect Ratio, should be 16.0f / 9.0f for most people
        0.1f,                   // Near clipping plane
        100.0f                  // Far clipping plane
    );

    GLuint mvpID = the->shader->getUniLoc("MVP");

    // Initiallize timer values
    double lasttime = glfwGetTime();
    int frames = 0;

    // Test object
    obj::obj3d* blobject = new obj::obj3d(
        QUOTE(__PREFIX) + std::string("assets/test.obj"),
        glm::vec3(0, 0, 0),
        QUOTE(__PREFIX) + std::string("assets/unknowntex.bmp"),
        the->shader->getUniLoc("texunit"),
        glm::vec3(0, 0, 1.0f)
    );

    do {
        // Calculate the time in ms to draw a frame
        double currtime = glfwGetTime();
        if (currtime - lasttime >= 1.000) {
            // Print time and reset counter
            #ifdef _DBG
            printf("[I] main() : %f ms/frame\n", 1000.0 / double(frames));
            #endif
            frames = 0;
            lasttime = glfwGetTime();
        }

        // Clear the color and depth bits every frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Create/complete objects
        blobject->moveto(glm::vec3(0, sin(currtime), 0));

        // Render
        the->shader->apply();
        glm::mat4 mvp = projection * the->camGetView() * blobject->model;
        glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

        // Draw
        the->vertArrObj->objDraw(blobject);

        // Player Rendering
        mvp = projection * the->camGetView() * the->plrGetModl();
        glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
        the->plrDraw();

        // Swap buffers and poll events
        the->windowSwapBuffers();
        glfwPollEvents();

        // Increment frames counter for the time tracker
        frames++;
    } while (the->windowShouldClose() == 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    return 0;
}
