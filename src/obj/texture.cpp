/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#include <obj/texture.h>
#include <cstdio>
#include <cassert>

obj::texture::texture(std::string filename, GLuint progunit) {
    // Create image buffer through DevIL and bind it
    ILuint image;
    ilGenImages(1, &image);
    ilBindImage(image);

    // Load image from file
    ilLoadImage(filename.c_str());
    int err = ilGetError();
    if (err != 0) {
        printf("[E] obj::texture : DevIL error generated: 0x%X\n", err);
        assert(0);
    }

    // Get image data and attributes
    unsigned char* colorbuf = ilGetData();
    width = ilGetInteger(IL_IMAGE_WIDTH);
    height = ilGetInteger(IL_IMAGE_HEIGHT); 

    // Load image as texture into OpenGL
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, colorbuf);

    // Save GL texture parameters
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    unit = progunit;
}

GLuint obj::texture::getTexHandle() {
    return tex;
}