//
//  Font.hpp
//  MuffinsGUI
//
//  Created by Jake Sanders on 7/27/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//
//  Guided by the tutorial at http://learnopengl.com/#!In-Practice/Text-Rendering by Joey De Vries
//  This has been altered from the original code, and is not endoresed nor endorsed by LearnOpenGL
//

#ifndef Font_hpp
#define Font_hpp

#include "Macros.h"

//Standard library includes
#include <map>
#include <string>
#include <iostream>

//GLEW: A function that gets OpenGL functionality
#define GLEW_STATIC
#include <GL/glew.h>

//GLM: OpenGL vectors and matrix transformations
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

//FreeType font library
#include <ft2build.h>
#include FT_FREETYPE_H

//Local includes
#include "Shader.hpp"

struct Character {
    GLuint textureID; //ID handle of the glyph texture
    glm::ivec2 size; //Size of glyph
    glm::ivec2 bearing; //Offset from baseline to left/top of glyph
    GLuint advance; //Offset to advance to next glyph
};

class Font {
public:
    
    //Constructors
    Font(const char* fontPath);
    
    //Public member functions
    
    /*!
     * A function to get the size the given text would be with the given scale.
     *
     * @param text The text that would be rendered.
     * @param scale The multiple by which the text would be enlarged.
     *
     * @returns A glm::vec2 representing the bounding rectangle that the given text would take up at the given scale. The x coordinate is the total length of all of the letters, and the y coordinate is the distance from the top of the tallest character to the bottom of the lowest. It is in framebuffer coordinates.
     */
    glm::vec2 getSize(std::string text, GLfloat scale);
    
    /*!
     * A function to render text. Should be called every frame to keep the text on the screen.
     *
     * @param text The text to render onscreen.
     * @param x The lower left x coordinate of the text.
     * @param y The lower left y coordinate of the text.
     * @param scale A multiple by which to enlarge the text. Can be determined based on math with getSize(). See button.cpp and box.cpp for examples.
     * @param color The color of the text, represented by a glm::vec3.
     * @param windowWidth The fraction of the screen width being used as the viewport. Almost always 1.0 is desired, unless the viewport has been changed.
     * @param windowHeight The fraction of the screen height being used as the viewport. Almost always 1.0 is desired, unless the viewport has been changed.
     */
    void render(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, GLfloat windowWidth, GLfloat windowHeight);
    
private:
    //Private properties
    
    //A map of chars to the corresponding character
    std::map<GLchar, Character> characters;
    
    //OpenGL buffers
    GLuint VAO;
    GLuint VBO;
    
    //Shader to use when rendering
    Shader shader;
    
    //Private member functions
};

#endif /* Font_hpp */
