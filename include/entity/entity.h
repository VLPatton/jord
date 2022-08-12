/*
This file is part of Jord.

Jord is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Jord is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Jord. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <glm/glm.hpp>

namespace entity {
    enum aliveness {
        kALIV = 0,  // Entity exists and should not be destroyed by the engine
        kDEAD,      // Entity exists, but may be destroyed by the engine
        kZOMB,      // Entity no longer exists but is still available in the engine
                    // (NOTE: an entity with state of kZOMB should not be rendered
                    // graphically but kDEAD should still be graphically rendered)
    };

    class entity {
        public:
            entity(glm::vec3);  // Creates entity object at specified location
            ~entity();
            glm::vec3 moveto(glm::vec3);

        protected:
            obj* model;
            aliveness state = kZOMB;
    }
}
