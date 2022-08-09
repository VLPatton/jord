/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace render {
    class shaders {
        public:
            shaders(std::string, std::string);
            ~shaders();
            void apply();                   // Use the shader program against the rendered models
            GLuint getUniLoc(std::string);  // Get the specified uniform from OpenGL

        private:
            GLuint prog;                    // GLuint for the program ID in OpenGL of the shaders
    };
}
