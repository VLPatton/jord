/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#include <rendering/shaders.h>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <vector>

render::shaders::shaders(std::string vert_filename, std::string frag_filename) {
    // Create the shader instances
    GLuint vert_shaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag_shaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vert_code;
    std::ifstream vert_stream(vert_filename, std::ios::in);
    if(vert_stream.is_open()){
        std::stringstream sstr;
        sstr << vert_stream.rdbuf();
        vert_code = sstr.str();
        vert_stream.close();
    } else {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vert_filename.c_str());
        getchar();
    }

    std::string frag_code;
    std::ifstream frag_stream(frag_filename, std::ios::in);
    if(frag_stream.is_open()){
        std::stringstream sstr;
        sstr << frag_stream.rdbuf();
        frag_code = sstr.str();
        frag_stream.close();
    } else {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", frag_filename.c_str());
        getchar();
    }

    GLint result = GL_FALSE;
    int ILL; // Info Log Length

    // Compile Vertex Shader
    printf("Compiling shader: %s\n", vert_filename.c_str());
    char const* vert_pointer = vert_code.c_str();
    glShaderSource(vert_shaderID, 1, &vert_pointer, NULL);
    glCompileShader(vert_shaderID);

    // Check Vertex Shader
    glGetShaderiv(vert_shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vert_shaderID, GL_INFO_LOG_LENGTH, &ILL);
    if (ILL > 0) {
        std::vector<char> vert_err(ILL + 1);
        glGetShaderInfoLog(vert_shaderID, ILL, NULL, &vert_err[0]);
        printf("%s\n", &vert_err[0]);
    }

    // Compile Fragment Shader
    printf("Compiling shader: %s\n", frag_filename.c_str());
    char const* frag_pointer = frag_code.c_str();
    glShaderSource(frag_shaderID, 1, &frag_pointer, NULL);
    glCompileShader(frag_shaderID);

    // Check Fragment Shader
    glGetShaderiv(frag_shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(frag_shaderID, GL_INFO_LOG_LENGTH, &ILL);
    if (ILL > 0) {
        std::vector<char> frag_err(ILL + 1);
        glGetShaderInfoLog(frag_shaderID, ILL, NULL, &frag_err[0]);
        printf("%s\n", &frag_err[0]);
    }

    // Link the program
    printf("Linking program\n");
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vert_shaderID);
    glAttachShader(programID, frag_shaderID);
    glLinkProgram(programID);

    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &ILL);
    if (ILL > 0) {
        std::vector<char> program_err(ILL + 1);
        glGetProgramInfoLog(programID, ILL, NULL, &program_err[0]);
        printf("%s\n", &program_err[0]);
    }

    glDetachShader(programID, vert_shaderID);
    glDetachShader(programID, frag_shaderID);
    
    glDeleteShader(vert_shaderID);
    glDeleteShader(frag_shaderID);

    prog = programID;
}

void render::shaders::apply() {
    glUseProgram(prog);
}

GLuint render::shaders::getUniLoc(std::string name) {
    return glGetUniformLocation(prog, name.c_str());
}