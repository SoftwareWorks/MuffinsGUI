//
//  Interface.cpp
//  MuffinsGUI
//
//  Created by Jake Sanders on 7/9/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#include "Interface.hpp"

Interface::Interface(Shader shader, Shader shaderForButtons, Window* window) : texture(Texture("Resources/texture.png", 0, "tex")) {
    this->interfaceWindow = window;
    this->interfaceShader = shader;
    this->buttonShader = shaderForButtons;
    
    GLfloat data[] = {
        -1.0, -1.0,
        -1.0,  1.0,
         1.0, -1.0,
        
        -1.0,  1.0,
         1.0, -1.0,
         1.0,  1.0,
    };
    
    //Draw with OpenGL
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    
    //First we bind the VAO
    glBindVertexArray(this->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    
    //Next we tell OpenGL how to interpret the array
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Interface::render(bool mouseDown, bool mouseUp, bool buttonInteraction) {
    //Bind the VAO and draw shapes
    this->interfaceShader.use();
    
    this->texture.use(this->interfaceShader);
    
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    
    for (auto box = this->boxes.begin(); box != this->boxes.end(); box++) {
        box->second.render();
    }
    
    for (auto button = this->buttons.begin(); button != this->buttons.end(); button++) {
        button->second.render(mouseDown, mouseUp, buttonInteraction);
    }
}

void Interface::addBox(std::string name, Box box) {
    this->boxes.insert(std::pair<std::string, Box>(name, box));
}

void Interface::addButton(std::string name, Button button) {
    this->buttons.insert(std::pair<std::string, Button>(name, button));
}

bool Interface::removeBox(std::string name) {
    auto iterator = this->boxes.find(name);
    
    if (iterator == this->boxes.end())
        return false;
    else
        this->boxes.erase(iterator);
    
    return true;
}

bool Interface::removeButton(std::string name) {
    auto iterator = this->buttons.find(name);
    
    if (iterator == this->buttons.end())
        return false;
    else
        this->buttons.erase(iterator);
    
    return true;
}

bool Interface::setBoxText(std::string text, std::string name) {
    auto iterator = this->boxes.find(name);
    
    if (iterator == this->boxes.end())
        return false;
    else
        iterator->second.text = text;
    
    return true;
}

bool Interface::setButtonText(std::string text, std::string name) {
    auto iterator = this->buttons.find(name);
    
    if (iterator == this->buttons.end())
        return false;
    else
        iterator->second.text = text;
    
    return true;
}

bool Interface::setButtonAction(std::string action, std::string name) {
    auto iterator = this->buttons.find(name);
    
    if (iterator == this->buttons.end())
        return false;
    else
        iterator->second.action = action;
    
    return true;
}

std::vector<std::string> Interface::getButtonActions() {
    std::vector<std::string> buttonActions;
    
    for (auto button = this->buttons.begin(); button != this->buttons.end(); button++) {
        if (button->second.isPressed())
            buttonActions.push_back(button->second.action);
    }
    
    return buttonActions;
}
