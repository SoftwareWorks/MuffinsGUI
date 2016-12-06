//
//  main.cpp
//  Game
//
//  Created by Jake Sanders on 6/22/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#include "Macros.h"

//C library includes
#include <stdlib.h>
#include <time.h>

//Standard library includes
#include <iostream>
#include <string>
#include <vector>

//GLEW: Locates memory location of OpenGL functions
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW: Window functionality
#include <GLFW/glfw3.h>

//SOIL: Sets up texture loading
#include <SOIL/SOIL.h>

//GLM: OpenGL mathematics for rotations, translations, dilations
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

//Local includes
#include "Window.hpp"
#include "Shader.hpp"
#include "Interface.hpp"

void processButton(std::string action);
void processKeys(bool mousePressed);

//Callback functions
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

//Global variables

bool keys[1024]; //An array of booleans, representing if, for each key, if it is being pressed

//Booleans representing if the mouse has been clicked or released, for use in buttons. This boolean is set in the mouse button callback function.
bool mouseJustPressed = false; //This is only true right after the mouse is pressed. Do not use this one to check if the mouse was pressed.
bool mouseUp = false; //This is true if the mouse button has been released, for use with resetting buttons

bool mouseDown = false; //This is true during the frame as long as the mouse has been clicked. This is the boolean that can be used to tell if the mouse has just been pressed.

int main(int argc, const char * argv[]) {
//Set up:
    srand((int)time(NULL));
    
    //The second boolean, if the window should be full size (not full screen, but a window the size of the screen), can be set to true; if so, the window will take up the entire screen
    Window window(800, 600, "Muffins GUI", false, false);
    
    window.setKeyCallback(keyCallback);
    window.setMouseButtonCallback(mouseButtonCallback);
    
    //Allow for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    Shader interfaceShader("Shaders/interface/interface.vert", "Shaders/interface/interface.frag");
    Shader buttonShader("Shaders/button/button.vert", "Shaders/button/button.frag");
    
    Interface i(interfaceShader, buttonShader, &window);
    
    //Add buttons and information boxes here
    
    i.addBox("Test", Box(buttonShader, &window, 0.25, 0.25, 0.2, 0.2, "Test"));
    
    i.addButton("Test", Button(buttonShader, &window, 0.25, 0.6, 0.2, 0.2, "", "TestButton"));
    
    while(!window.shouldClose()) {
        //Since the last frame, if the mouse was pressed, set mouseDown properly
        //mouseJustPressed is set to false because it has been processed and used to set mouseDown
        if (mouseJustPressed) {
            mouseJustPressed = false;
            mouseDown = true;
        }
        
        i.render(mouseDown, mouseUp, true);
        
        //For each button pressed, gets a string to be interpretted, indicating what should be done
        std::vector<std::string> buttonActions = i.getButtonActions();
        
        //Go through all of the actions and process them
        for (int a = 0; a < buttonActions.size(); a++) {
            processButton(buttonActions[a]);
        }
        
        processKeys(mouseDown);
        
        //Reset mouseDown, for it has been processed
        mouseDown = false;
        
        window.updateScreen();
    }
    
    window.terminate();
    
    return 0;
}

void processButton(std::string action) {
    //Here indicate what to do if a button was pressed
    
    /* Example:
     
     if (action == "move_forward") { //A button with the action text "move_forward" would have been clicked
         socket.send("move_forward");
     } else if (action == ...) {
        ...
     }
     ...
     
     */
}

void processKeys(bool mouseDown) {
    //Here indicate what to do if a key is being pressed. mouseDown is a boolean representing if the mouse has been pressed for this frame
    
    /* Example:
     
     if (keys[GLFW_KEY_UP]) {
         socket.send("move_forward");
     }
     if (keys[GLFW_KEY_SPACE]) {
         ...
     }
     ...
    
     */
}

//A function GLFW can call when a key event occurs
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    
    if (key == GLFW_KEY_W && action == GLFW_PRESS && mods == GLFW_MOD_SUPER) { //Command-W: close the application
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keys[key] = true;
        }
        if (action == GLFW_RELEASE) {
            keys[key] = false;
        }
    }
}

//A function GLFW can call when a key event occurs
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    
    mouseJustPressed = false;
    mouseUp = false;
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        mouseJustPressed = true; //Indicate the mouse has just been pressed. This will then be processed at the start and end of each frame to set mouseDown
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        mouseUp = true;
    }
}
