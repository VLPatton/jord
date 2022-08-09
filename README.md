# Jord - Some game idea I had
There isn't much to it, it's pretty much just a game like Minecraft but with more natural terrain. "Jord" is pronounced like English, "yard," but with an "o" instead of "a."
## Version
Stable: N/A <br>
Working: v0.0.1-alpha
## Building/Launching the Game
Within the project root, run `make && make install` as regular user to install to home directory. With `sudo` privileges, run `make && sudo make install` to install to `/usr/local`. After making sure that `/usr/local/bin` is in `$PATH`, you can run it from the terminal through the command `jord`.
### Hardware Requirements
Jord uses OpenGL 3.3; if your GPU does not support this version at a minimum, it will NOT run. The tested/known-working hardware is below:
* Core i7 10700K, Geforce RTX 3080 
    * 16 GB RAM, 10 GB VRAM
* Ryzen 9 5900HX, Geforce RTX 3050-Ti Mobile
    * 16 GB RAM, 4 GB VRAM
### Software Requirements
Jord has no distro-specific dependencies for Linux, but macOS and Windows are strictly not supported, even if it's easy to get working on those platforms. The tested OS is Arch Linux, running the newest stable kernel at each release, with KDE Plasma/X11 as the graphical environment. <br>
It is important to mention that there are certain dependencies which do need to be met at runtime and compilation. Importantly, an OpenGL implementation must be available on your distro of choice (such as `mesa`), as well as GL Math (pacman: `glm`), GLFW (pacman: `glfw`), and GLEW (pacman: `glew`). Compilation dependencies include `gcc` and `make`, other than the libraries previously mentioned. The compiler (gcc) and GNU Make can be installed together on most distros (pacman: `base-devel`, apt: `build-essential`); read your distro's package docs for information on where to obtain all of the mentioned dependencies.
## Licensing and Notes
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
### Third Party Licenses
`tinyobjloader` : MIT License, compatible with GPLv3
