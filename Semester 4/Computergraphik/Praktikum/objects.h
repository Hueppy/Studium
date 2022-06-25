//
// Created by phue on 6/11/22.
//

#ifndef BLATT01_OBJECTS_H
#define BLATT01_OBJECTS_H

#include <GL/glew.h>
#include <glm/glm.hpp>

/*
Struct to hold data for object rendering.
*/
class Object
{
public:
    inline Object ()
            : vao(0),
              positionBuffer(0),
              colorBuffer(0),
              indexBuffer(0),
              initialized(false)
    {}

    inline ~Object () { // GL context must exist on destruction
        if (initialized) {
            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(1, &indexBuffer);
            glDeleteBuffers(1, &colorBuffer);
            glDeleteBuffers(1, &positionBuffer);
            initialized = false;
        }
    }

    void init();
    void render(glm::mat4x4 model);

    GLuint vao;        // vertex-array-object ID

    GLuint positionBuffer; // ID of vertex-buffer: position
    GLuint colorBuffer;    // ID of vertex-buffer: color

    GLuint indexBuffer;    // ID of index-buffer

    GLsizei count;

    bool initialized;

    glm::mat4x4 model; // model matrix
};

class Sphere : public Object {
public:
    void init(int n);
    void update(int n);
};

class Axis : public Object {
public:
    void init(bool x, bool y, bool z, glm::vec3 color);
    void update(bool x, bool y, bool z, glm::vec3 color);
    void render(glm::mat4x4 model);
};

#endif //BLATT01_OBJECTS_H
