//
//  Box.cpp
//  MuffinsGUI
//
//  Created by Jake Sanders on 8/20/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#include "Box.hpp"

//Public member functions

Box::Box(Shader shader, Window* window, GLfloat x, GLfloat y, GLfloat width, GLfloat height, std::string boxText) : lowerLeftX((2.0 * x) - 1.0), lowerLeftY((2.0 * y) - 1.0), boxWidth(2.0 * width), boxHeight(2.0 * height), boxColor(glm::vec4(Box::defaultColor, Box::defaultColor, Box::defaultColor, 1.0)), text(boxText), font(Font(FONT_PATH)) {
    
    this->boxWindow = window;
    this->boxShader = shader;
    
    GLfloat data[] = {
        //Rectangle is drawn by two triangles
        this->lowerLeftX, this->lowerLeftY,
        this->lowerLeftX + this->boxWidth, this->lowerLeftY,
        this->lowerLeftX, this->lowerLeftY + this->boxHeight,
        
        this->lowerLeftX + this->boxWidth, this->lowerLeftY,
        this->lowerLeftX, this->lowerLeftY + this->boxHeight,
        this->lowerLeftX + this->boxWidth, this->lowerLeftY + this->boxHeight,
    };
    
    glm::vec4 colorData[6];
    for (int a = 0; a < 6; a++) {
        colorData[a] = this->boxColor;
    }
    
    //Draw with OpenGL
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->boxVBO);
    glGenBuffers(1, &this->colorVBO);
    
    //First we bind the VAO
    glBindVertexArray(this->VAO);
    
    //Position VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->boxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    
    //Next we tell OpenGL how to interpret the array
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    //Color VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
    
    //Next we tell OpenGL how to interpret the array
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Box::Box(Shader shader, Window* window, GLfloat x, GLfloat y, GLfloat width, GLfloat height, glm::vec4 color, std::string boxText) : lowerLeftX((2.0 * x) - 1.0), lowerLeftY((2.0 * y) - 1.0), boxWidth(2.0 * width), boxHeight(2.0 * height), boxColor(color), text(boxText), font(Font(FONT_PATH)) {
    
    this->boxWindow = window;
    this->boxShader = shader;
    
    GLfloat data[] = {
        //Rectangle is drawn by two triangles
        this->lowerLeftX, this->lowerLeftY,
        this->lowerLeftX + this->boxWidth, this->lowerLeftY,
        this->lowerLeftX, this->lowerLeftY + this->boxHeight,
        
        this->lowerLeftX + this->boxWidth, this->lowerLeftY,
        this->lowerLeftX, this->lowerLeftY + this->boxHeight,
        this->lowerLeftX + this->boxWidth, this->lowerLeftY + this->boxHeight,
    };
    
    glm::vec4 colorData[6];
    for (int a = 0; a < 6; a++) {
        colorData[a] = this->boxColor;
    }
    
    //Draw with OpenGL
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->boxVBO);
    glGenBuffers(1, &this->colorVBO);
    
    //First we bind the VAO
    glBindVertexArray(this->VAO);
    
    //Position VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->boxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    
    //Next we tell OpenGL how to interpret the array
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    //Color VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
    
    //Next we tell OpenGL how to interpret the array
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Box::render() {
    std::string boxText = ' ' + this->text + ' ';
    
    //Bind the VAO and draw shapes
    this->boxShader.use();
    
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    
    //Set the scale for the text
    GLfloat scale = 1.0f;
    
    //Get the text size
    glm::vec2 textSize = this->font.getSize(boxText, scale);
    
    //Initialized with the lower left corner position of the Box
    
    //The arithmatic done on the lower left corner converts it from -1 to 1 into 0 to 1
    glm::vec2 textPos = glm::vec2((this->lowerLeftX + 1.0) / 2.0, (this->lowerLeftY + 1.0) / 2.0);
    
    //The first .5 puts the Box width/height back to 0 to 1 (instead of -1 to 1)
    //The second .5 represents moving half of the Box width/height rather than the full width/height
    
    //Horizontally center the text so its center is at the Box's center
    textPos.x += (this->boxWidth * 0.5) * 0.5 - (textSize.x / 2.0);
    
    //Vertically center the text so its center is at the Box's center
    textPos.y += (this->boxHeight * 0.5) * 0.5 - (textSize.y / 2.0);
    
    GLfloat sizeFraction = textSize.x / (this->boxWidth * 0.5); //This represents what fraction of the Box the text will take up
    
    if (sizeFraction > 1) { //If the width of the text is greater than the Box size, scale down the text proportionally
        scale = 1.0 / sizeFraction;
        
        //Redo the size calculations with the new text size
        
        //Get the text size
        textSize = this->font.getSize(boxText, scale);
        
        textPos = glm::vec2((this->lowerLeftX + 1.0) / 2.0, (this->lowerLeftY + 1.0) / 2.0);
        
        //Horizontally center the text so its center is at the Box's center
        textPos.x += (this->boxWidth * 0.5) * 0.5 - (textSize.x / 2.0);
        
        //Vertically center the text so its center is at the Box's center
        textPos.y += (this->boxHeight * 0.5) * 0.5 - (textSize.y / 2.0);
    }
    
    //Render the text on the Box
    this->font.render(boxText, textPos.x, textPos.y, scale, glm::vec3(1.0f, 1.0f, 1.0f), 1.0, 1.0);
}

glm::vec4 Box::color() {
    return this->boxColor;
}
