//
//  Interface.hpp
//  MuffinsGUI
//
//  Created by Jake Sanders on 7/9/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#ifndef Interface_hpp
#define Interface_hpp

#include "Macros.h"

//Standard library includes
#include <string>
#include <vector>
#include <map>

//GLEW: Locates memory location of OpenGL functions
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW: Window functionality
#include <GLFW/glfw3.h>

//Local includes
#include "Shader.hpp"
#include "Font.hpp"
#include "Texture.hpp"
#include "Box.hpp"
#include "Button.hpp"
#include "Window.hpp"

class Interface {
public:
    //Constructors
    
    /*!
     * A class representing an interface box.
     *
     * @param shader A compiled shader object for the interface box to use for rendering.
     * @param shaderForButtons A compiled shader object that will be used for rendering the buttons, as well as boxes, on this interface.
     * @param window A pointer to the current window object.
     */
    Interface(Shader shader, Shader shaderForButtons, Window* window);
    
    //Public properties
    
    /*!
     * An std::map of the boxes contained in this interface, with key values of type std::string
     */
    std::map<std::string, Box> boxes; //So that the boxes can be accessed by the game
    
    /*!
     * An std::map of the buttons contained in this interface, with key values of type std::string
     */
    std::map<std::string, Button> buttons; //So that the buttons can be accessed by the game
    
    //Public member functions
    
    /*!
     * Add a text box to the interface.
     *
     * @param The key that can be used to access the box.
     * @param A template for the box which will be added.
     */
    void addBox(std::string name, Box box);
    
    /*!
     * Add a button to the interface.
     *
     * @param The key that can be used to access the button.
     * @param A template for the button which will be added.
     */
    void addButton(std::string name, Button button);
    
    /*!
     * Remove a box from the interface.
     *
     * @param The key of the box to be removed.
     *
     * @returns If the box was successfully removed. False is returned if there was no box with the given key.
     */
    bool removeBox(std::string name);
    
    /*!
     * Remove a button from the interface.
     *
     * @param The key of the button to be removed.
     *
     * @returns If the box was successfully removed. False is returned if there was no box with the given key.
     */
    bool removeButton(std::string name);
    
    /*!
     * Set the text on a box.
     *
     * @param The text to be set as the box's text.
     * @param The key of the box to be edited.
     *
     * @returns If the box was successfully altered. False is returned if there was no box with the given key.
     */
    bool setBoxText(std::string text, std::string name);
    
    /*!
     * Set the text on a button.
     *
     * @param The text to be set as the button's text.
     * @param The key of the button to be edited.
     *
     * @returns If the button was successfully altered. False is returned if there was no button with the given key.
     */
    bool setButtonText(std::string text, std::string name);
    
    /*!
     * Set the action text on a button.
     *
     * @param The action to be set as the button's action. This will be sent to the processButton() function when pressed.
     * @param The key of the button to be edited.
     *
     * @returns If the button was successfully altered. False is returned if there was no button with the given key.
     */
    bool setButtonAction(std::string action, std::string name);
    
    /*!
     * A function to render the interface. Should be called within the game loop's render function. This also renders the buttons on this interface.
     *
     * @param mouseDown A boolean representing if the mouse is down, for the buttons to figure out whether to become pressed.
     * @param mouseUp A boolean representing if the mouse has just been released. This is used for when the button resets its 'down' state.
     * @param buttonInteraction A boolean representing whether or not buttons should change color or jsut stay at default. This can be for when the settings menu is up, so button interaction outside of the menu doesn't occur.
     */
    void render(bool mouseDown, bool mouseUp, bool buttonInteraction);
    
    std::vector<std::string> getButtonActions();
    
private:
    //OpenGL and GLFW properties
    Window *interfaceWindow;
    Shader interfaceShader; //Compiled shader
    Shader buttonShader; //Shader for the buttons
    GLuint VAO; //VAO (Vertex Array Object) stores objects that can be drawn, including VBO data with the linked shader
    //VBO (Vertex Buffer Object) stores vertex data in the GPU graphics card. Will be stored in VAO
    GLuint VBO;
    
    Texture texture;
    
};

#endif /* Interface_hpp */
