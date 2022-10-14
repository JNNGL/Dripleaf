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

#pragma once

#include <dripleaf/renderer/window.h>

#include <algorithm>
#include <vector>

class WindowLoop {
 private:
  std::vector<IWindow*> windows;

 public:
  WindowLoop() = default;
  ~WindowLoop() {
    for (IWindow* window : windows) {
      delete window;
    }
  }

  IWindow* addWindow(IWindow* window) {
    windows.push_back(window);
    return window;
  }

  bool destroyWindow(IWindow* window) {
    auto it = std::find(windows.begin(), windows.end(), window);
    if (it != windows.end()) {
      windows.erase(it);
      delete window;
      return true;
    }
    return false;
  }

  void loop() {
    while (!windows.empty()) {
      for (IWindow* window : windows) {
        if (window->shouldClose()) {
          destroyWindow(window);
          continue;
        }

        window->doLoopWork();
      }
    }
  }
};