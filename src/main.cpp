/*
 * Dripleaf
 * Copyright (C) 2022  JNNGL
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <dripleaf/renderer/window.h>
#include <dripleaf/renderer/window_loop.h>

#include "renderer/gl_surface.h"
#include "renderer/window_glfw.h"

int main() {
  auto* windowLoop = new WindowLoop;

  ISurface* surface = new GLSurface;
  surface->setBackgroundColor({0.1f, 0.3f, 0.6f, 1.0f});

  windowLoop->addWindow(new WindowGLFW(surface, 1280, 720, "Hello, world"));

  windowLoop->loop();
  delete windowLoop;

  return 0;
}
