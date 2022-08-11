/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <IL/il.h>  // This is the DevIL, which must be installed as a runtime dependency
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace render::obj {
    class texture {
        public:
            texture(std::string, GLuint);
            ~texture();
            GLuint getTexHandle();

            GLuint unit;
        private:
            //unsigned char* colorbuf;
            unsigned int width;
            unsigned int height;
            GLuint tex;
    };
}
