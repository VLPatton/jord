/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#include <cstdio>
#include <cassert>
#include <main.h>
#include <rendering/vertexarray.h>
#include <rendering/shaders.h>

#define WIN_TITLE "game"

int main(void) {
    // Force glfw to init, if it doesn't, call abort()
    assert(glfwInit());

    glfwWindowHint(GLFW_SAMPLES, 4);                                // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // We don't want the old OpenGL

    proc::proc* the = new proc::proc(WIN_TITLE);
    glewInit();
    render::va* vertArrObj = new render::va();
    GLfloat tri_data[9] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f
    };
    render::triangle* tri = new render::triangle(tri_data, glm::vec3(0.0f, 0.0f, 0.0f));
    render::shaders* shader = new render::shaders("shaders/vertex.vs", "shaders/fragment.fs");
    
    glEnableVertexAttribArray(0);
    glClearColor(0.4f, 0.6f, 0.9f, 0.0f);   // Sky blue background

    // Create our perspective matrix (TODO: add dynamic FOV and aspect ratio)
    const glm::mat4 projection = glm::perspective(
        glm::radians(70.0f),    // The vertical Field of View
        16.0f / 9.0f,           // Aspect Ratio, should be 16.0f / 9.0f for most people
        0.1f,                   // Near clipping plane
        100.0f                  // Far clipping plane
    );

    GLuint mvpID = shader->getUniLoc("MVP");

    do {
        // Clear the color and depth bits every frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render
        shader->apply();
        glm::mat4 mvp = projection * the->camGetView() * tri->model;
        glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

        // Draw
        vertArrObj->triangleDraw(tri);

        // Swap buffers and poll events
        the->windowSwapBuffers();
        glfwPollEvents();
    } while (the->windowShouldClose() == 0);

    glDisableVertexAttribArray(0);

    return 0;
}