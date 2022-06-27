//
// Created by phue on 6/11/22.
//

#ifndef BLATT01_OBJECTS_H
#define BLATT01_OBJECTS_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "GLSLProgram.h"
#include "ObjLoader.h"

/*
Struct to hold data for objSharp rendering.
*/
class Object
{
public:
    inline Object ()
            : vao(0),
              positionBuffer(0),
              colorBuffer(0),
              normalBuffer(0),
              indexBuffer(0),
              mode(GL_TRIANGLES)
    {}

    inline ~Object () { // GL context must exist on destruction
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &indexBuffer);
        glDeleteBuffers(1, &colorBuffer);
        glDeleteBuffers(1, &positionBuffer);
    }

    void init();
    void render(glm::mat4x4 model, cg::GLSLProgram &program);
    void from(ObjFile &objFile, cg::GLSLProgram &program);
    void fromNormals(ObjFile &objFile, cg::GLSLProgram &program);

    GLuint vao;        // vertex-array-objSharp ID

    GLuint positionBuffer; // ID of vertex-buffer: position
    GLuint colorBuffer;    // ID of vertex-buffer: color
    GLuint normalBuffer;    // ID of vertex-buffer: color

    GLuint indexBuffer;    // ID of index-buffer
    GLuint mode;

    GLsizei count;

    glm::mat4x4 model; // model matrix
};

enum class Shading {
    Flat,
    Gouraud
};

class Sphere {
public:
    Object objSharp;
    Object objSmooth;
    Object objNormals;
    Object objBounding;
    cg::GLSLProgram flatShader;
    cg::GLSLProgram gouraudShader;
    cg::GLSLProgram simpleShader;
    Shading shading;
    bool renderNormals;
    bool renderBounding;
    bool hasNormals;

    bool init(int n, glm::vec3 color);
    void update(int n, glm::vec3 color);
    void updateBounding(glm::vec3 start, glm::vec3 stop);
    void render(glm::mat4x4 model);
};

class Axis {
public:
    Object object;
    cg::GLSLProgram program;

    bool init(bool x, bool y, bool z, glm::vec3 color);
    void update(bool x, bool y, bool z, glm::vec3 color);
    void render(glm::mat4x4 model);
};

#endif //BLATT01_OBJECTS_H
