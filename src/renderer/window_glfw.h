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

#include <GLFW/glfw3.h>
#include <dripleaf/renderer/window.h>

#include <stdexcept>

#include <dripleaf/renderer/surface.h>

class WindowGLFW : public IWindow {
 private:
  GLFWwindow* handle;
  ISurface* surface;
  uint32_t width;
  uint32_t height;
  std::string title;

 public:
  WindowGLFW(ISurface* surface, uint32_t width, uint32_t height, const std::string& title)
      : surface(surface),
        width(width),
        height(height),
        title(title) {
    if (!surface) {
      throw std::logic_error("Surface cannot be null");
    }

    if (!glfwInit()) {
      throw std::runtime_error("Couldn't initialize GLFW");
    }

    handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!handle) {
      throw std::runtime_error("Couldn't create window");
    }

    glfwSetWindowUserPointer(handle, this);
    glfwMakeContextCurrent(handle);
    surface->initialize(this);
  }

  ~WindowGLFW() override {
    delete surface;
    glfwDestroyWindow(handle);
  }

  [[nodiscard]] uint32_t getWidth() const override {
    return width;
  }

  [[nodiscard]] uint32_t getHeight() const override {
    return height;
  }

  [[nodiscard]] const std::string& getTitle() const override {
    return title;
  }

  [[nodiscard]] void* getHandle() const override {
    return handle;
  }

  [[nodiscard]] bool shouldClose() const override {
    return glfwWindowShouldClose(handle);
  }

  void doLoopWork() override {
    glfwMakeContextCurrent(handle);
    surface->render(this);
    glfwSwapBuffers(handle);
    glfwPollEvents();
  }
};