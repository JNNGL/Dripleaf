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

class WindowGLFW : public IWindow {
 private:
  GLFWwindow* handle;
  uint32_t width;
  uint32_t height;
  std::string title;

 public:
  WindowGLFW(uint32_t width, uint32_t height, const std::string& title)
      : width(width),
        height(height),
        title(title) {
    if (!glfwInit()) {
      throw std::runtime_error("Couldn't initialize GLFW");
    }

    handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(handle, this);
  }

  ~WindowGLFW() override {
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
    glfwSwapBuffers(handle);
    glfwPollEvents();
  }
};