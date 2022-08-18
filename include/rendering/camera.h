/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

/*
Description:

The namespace render here contains one class: camera. This class stores
rendering related information about the PoV and view matrix. This is the only
purpose it serves, since the view matrix used by the engine comes from an
instance of this class. However, with changes to the engine, other PoVs could
be used, such as a 3rd person PoV.

Namespace: render
Classes: camera

*/

#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace render {
    class camera {
        public:
            camera(glm::vec3, glm::vec3 = glm::vec3(0, 0, 0));  // Init the view matrix at the given position
            void lookat(glm::vec3);
            void moveto(glm::vec3);
            glm::vec3 getpos();
            glm::vec3 getangle();
            glm::mat4 getview();

        private:
            glm::vec3 pos;      // The position of the camera
            glm::vec3 angle;    // The coord in 3D space that the camera is looking at
            glm::mat4 view;     // The view matrix to be used by rendering
    };
}
