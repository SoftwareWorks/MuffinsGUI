//
//  Window.hpp
//  LibOpenGL
//
//  Created by Jake Sanders on 11/12/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "Macros.h"

//Standard library includes
#include <string>
#include <exception>

//GLEW: Locates memory location of OpenGL functions
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW: Window functionality
#include <GLFW/glfw3.h>

//GLM: OpenGL math, including vectors
#include <glm/glm.hpp>

class Window {
public:
    //Constructor
    Window(int width, int height, std::string name, bool resizable, bool fillScreen);
    
    //Public methods
    
    void setKeyCallback(GLFWkeyfun function);
    
    void setMouseButtonCallback(GLFWmousebuttonfun function);
    
    void setClearColor(float x, float y, float z);
    
    void updateScreen();
    
    void close();
    
    void terminate();
    
    bool shouldClose();
    
    glm::ivec2 windowSize();
    
    glm::ivec2 framebufferSize();
    
    glm::dvec2 cursorPos();
    
private:
    GLFWwindow* window;
    
    glm::vec4 clearColor = glm::vec4(0.0, 0.0, 0.0, 1.0);
};

#endif /* Window_hpp */
