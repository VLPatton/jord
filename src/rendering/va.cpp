/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#include <rendering/vertexarray.h>

render::va::va() {
    glGenVertexArrays(1, &vaID);
    glBindVertexArray(vaID);
}

render::va::~va() {

}

void render::va::triangleDraw(triangle* tri) {
    glBindBuffer(GL_ARRAY_BUFFER, tri->vb);
    glVertexAttribPointer(
    0,                  // attribute 0 (vertices)
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
    );
    // Draw the triangle!
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
}