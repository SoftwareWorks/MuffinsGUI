//
//  Window.hpp
//  LibOpenGL
//
//  Created by Jake Sanders on 11/12/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#include "Window.hpp"

//Constructor

Window::Window(int width, int height, std::string name, bool resizable, bool fillScreen) {
    //Initiate GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Version 3.3 of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Error with accidental use of legacy functions
    
    if (resizable)
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    else
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
#ifndef _win32
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //On OS X
#endif
    
    //Make a window object
    this->window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    
    if (fillScreen) { //Makes the window take up the entire screen but still be within a moveable window
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        
        glfwSetWindowMonitor(this->window, nullptr, 0, 0, mode->width, mode->height, mode->refreshRate);
    }

    if (this->window == nullptr) { //If the window isn't created, return an error
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW Window");
    }
    
    glfwMakeContextCurrent(this->window);
    
    //Initialize GLEW
    glewExperimental = GL_TRUE; //Allows the use of more modern OpenGL functionality
    if (glewInit() != GLEW_OK) { //If GLEW isn't properly initialized, return an error
        throw std::runtime_error("Failed to initialize GLEW");
    }
    
    //Tell OpenGL window information
    int viewportWidth, viewportHeight;
    glfwGetFramebufferSize(this->window, &viewportWidth, &viewportHeight);
    glViewport(0.0, 0.0, viewportWidth, viewportHeight);
}

//Public methods

void Window::setKeyCallback(GLFWkeyfun function) {
    //Set key callback function
    glfwSetKeyCallback(this->window, function);
}

void Window::setMouseButtonCallback(GLFWmousebuttonfun function) {
    //Set mouse button click callback function
    glfwSetMouseButtonCallback(this->window, function);
}

void Window::setClearColor(float x, float y, float z) {
    this->clearColor = glm::vec4(x, y, z, 1.0);
}

void Window::updateScreen() {
    //Swap buffers so as to properly render without flickering
    glfwSwapBuffers(this->window);
    
    //GLFW gets any events that have occurred
    glfwPollEvents();
    
    //Clears the screen after each rendering
    glClearColor(this->clearColor.x, this->clearColor.y, this->clearColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::close() {
    glfwSetWindowShouldClose(this->window, GL_TRUE);
}

void Window::terminate() {
    glfwTerminate();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(this->window);
}

glm::ivec2 Window::windowSize() {
    glm::ivec2 size;
    glfwGetWindowSize(this->window, &size.x, &size.y);
    return size;
}

glm::ivec2 Window::framebufferSize() {
    glm::ivec2 size;
    glfwGetFramebufferSize(this->window, &size.x, &size.y);
    return size;
}

glm::dvec2 Window::cursorPos() {
    glm::dvec2 pos;
    glfwGetCursorPos(this->window, &pos.x, &pos.y);
    return pos;
}
