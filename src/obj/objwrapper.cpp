/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#include <obj/objwrapper.h>
#include <cassert>
#include <cstdio>

// TODO: implement usage of materials, textures, normals, and potentially color
obj::obj3d::obj3d(std::string filename, glm::vec3 pos) {
    tinyobj::ObjReaderConfig reader_config;
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(filename, reader_config)) {
        if (!reader.Error().empty()) {
            printf("[E] tinyobj::reader : %s\n", reader.Error().c_str());
        }
        assert(0); // Fail intentionally if parsing the file fails
    }

    if (!reader.Warning().empty()) {
        printf("[W] tinyobj::reader : %s\n", reader.Warning().c_str());
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                // Push the vertex coords onto the vector so they can be read by OpenGL
                vertvec.push_back((GLfloat)vx);
                vertvec.push_back((GLfloat)vy);
                vertvec.push_back((GLfloat)vz);
                vertvec.push_back((GLfloat)0);  // Unused UV/texcoord
                vertvec.push_back((GLfloat)0);  // ^
            }
            index_offset += fv;
        }
    }

    // Generate and bind the VBO in the class
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);

    // In the VBO, give the size of the vector and its data to OpenGL
    glBufferData(GL_ARRAY_BUFFER, vertvec.size() * sizeof(GLfloat), vertvec.data(), GL_STATIC_DRAW);

    // Create the model matrix necessary for proper rendering
    model = glm::translate(glm::mat4(1.0f), pos);
}

// Constructor with the added ability to load a texture from a file called texname
obj::obj3d::obj3d(std::string filename, glm::vec3 pos, std::string texname, GLuint progunit) {
    tinyobj::ObjReaderConfig reader_config;
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(filename, reader_config)) {
        if (!reader.Error().empty()) {
            printf("[E] tinyobj::reader : %s\n", reader.Error().c_str());
        }
        assert(0); // Fail intentionally if parsing the file fails
    }

    if (!reader.Warning().empty()) {
        printf("[W] tinyobj::reader : %s\n", reader.Warning().c_str());
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                // Push the vertex coords onto the vector so they can be read by OpenGL
                vertvec.push_back((GLfloat)vx);
                vertvec.push_back((GLfloat)vy);
                vertvec.push_back((GLfloat)vz);
                /*
                ////TODO:////

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                    tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                    tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                }
                */

                tinyobj::real_t tx = 0;
                tinyobj::real_t ty = 0;

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) {
                    tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                    ty = 1 - attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                }

                // Push the new texture coords into vertvec
                vertvec.push_back((GLfloat)tx);
                vertvec.push_back((GLfloat)ty);

                /*
                // vertex colors
                // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
                // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
                // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
                */
            }
            index_offset += fv;
        }
    }

    tex = new texture(texname, progunit);

    // Generate and bind the VBO in the class
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);

    // In the VBO, give the size of the vector and its data to OpenGL
    glBufferData(GL_ARRAY_BUFFER, vertvec.size() * sizeof(GLfloat), vertvec.data(), GL_STATIC_DRAW);

    // Create the model matrix necessary for proper rendering
    model = glm::translate(glm::mat4(1.0f), pos);
}

// Returns the size of the vector in number of elements
size_t obj::obj3d::getBufferSize() {
    return vertvec.size();
}
