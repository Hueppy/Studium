#include <iostream>
#include <vector>

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"
#include "color.h"
#include "objects.h"

// Standard window width
const int WINDOW_WIDTH = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;

cg::GLSLProgram program;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

int n = 0;
float size = 1.0f;
float distance = 4.0f;
float speed = 0.01f;
float speed2 = 0.01f;

const float MIN_SPEED = 0.0001f;
const float MAX_SPEED = 0.1f;

bool sunStopped = false;

glm::vec3 global_rotation(0.0f, 0.0f, 0.0f);
glm::mat4 global(1.0f);

class PlanetarySystem {
public:
    PlanetarySystem()
            : model(1.f),
              drawAxis(false) {
        children.reserve(10);
    }

    PlanetarySystem(int n)
            : model(1.f),
              drawAxis(false) {
        init(n);
        children.reserve(10);
    }

    void init(int n) {
        sphere.init(n);
        axis.init(false, true, false, glm::vec3(1.f, 0.f, 0.f));
    }

    void render(glm::mat4x4 model) {
        sphere.render(model);
        if (drawAxis)
            axis.render(model);

        auto m = model * this->model;
        for (auto &child: children) {
            child.render(m);
        }
    }

    PlanetarySystem &add() {
        return children.emplace_back(5);
    }

    void translate(glm::vec3 v) {
        sphere.model = glm::translate(sphere.model, v);
        axis.model = glm::translate(axis.model, v);
        model = glm::translate(model, v);
    }

    void scale(glm::vec3 v) {
        sphere.model = glm::scale(sphere.model, v);
    }

    void rotate(glm::vec3 v) {
        model = glm::rotate(model, v.x, glm::vec3(1.f, 0.f, 0.f));
        model = glm::rotate(model, v.y, glm::vec3(0.f, 1.f, 0.f));
        model = glm::rotate(model, v.z, glm::vec3(0.f, 0.f, 1.f));
    }

    void rotateLocal(glm::vec3 v) {
        sphere.model = glm::rotate(sphere.model, v.x, glm::vec3(1.f, 0.f, 0.f));
        sphere.model = glm::rotate(sphere.model, v.y, glm::vec3(0.f, 1.f, 0.f));
        sphere.model = glm::rotate(sphere.model, v.z, glm::vec3(0.f, 0.f, 1.f));
    }

    Sphere sphere;
    Axis axis;
    bool drawAxis;
    std::vector<PlanetarySystem> children;
    glm::mat4x4 model;
};

PlanetarySystem sun;

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init() {
    // OpenGL: Set "background" color and enable depth testing.
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Create a shader program and set light direction.
    if (!program.compileShaderFromFile("shader/flat.vert", cg::GLSLShader::VERTEX)) {
        std::cerr << program.log();
        return false;
    }

    if (!program.compileShaderFromFile("shader/flat.frag", cg::GLSLShader::FRAGMENT)) {
        std::cerr << program.log();
        return false;
    }

    if (!program.link()) {
        std::cerr << program.log();
        return false;
    }

    // Create all objects.

    sun.init(2);
    sun.scale(glm::vec3(.5f));
    sun.drawAxis = true;
    auto &planet = sun.add();
    planet.translate(glm::vec3(1.f, 0.f, 0.f));
    planet.scale(glm::vec3(.25f));
    planet.drawAxis = true;

    auto &m1 = planet.add();
    m1.translate(glm::vec3(0.f, .5f, 0.f));
    m1.scale(glm::vec3(.125f));

    auto &m2 = planet.add();
    m2.translate(glm::vec3(0.f, -.5f, 0.f));
    m2.scale(glm::vec3(.125f));

    return true;
}

/*
 Rendering.
 */
void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Construct view matrix.
    glm::vec3 eye(0.0f, 0.0f, distance);
    glm::vec3 center(0.0f, 0.0f, 0.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);

    if (!sunStopped)
        sun.rotate(glm::vec3(0.f, -speed, 0.f));
    for (auto &planet: sun.children) {
        planet.rotate(glm::vec3(speed, 0.f, 0.f));
        planet.rotateLocal(glm::vec3(0.f, 3 * -speed2, 0.f));
    }

    global = glm::rotate(glm::mat4(1.0f), global_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    global = glm::rotate(global, global_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    global = glm::rotate(global, global_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    view = glm::lookAt(eye, center, up);

    sun.render(global);
}

void glutDisplay() {
    render();
    glutSwapBuffers();
}

/*
 Resize callback.
 */
void glutResize(int width, int height) {
    // Division by zero is bad...
    height = height < 1 ? 1 : height;
    glViewport(0, 0, width, height);

    // Construct projection matrix.
    projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
}

/*
 Callback for char input.
 */
void glutKeyboard(unsigned char keycode, int x, int y) {
    switch (keycode) {
        case 27: // ESC
            glutDestroyWindow(glutID);
            return;
        case 'u':
            sun.rotate(glm::vec3(0.f, 0.f, 0.05f));
            break;
        case 'i':
            sun.rotate(glm::vec3(0.f, 0.f, -0.05f));
            break;
        case 'x':
            global_rotation.x += 0.1f;
            break;
        case 'y':
            global_rotation.y += 0.1f;
            break;
        case 'q':
            global_rotation.z += 0.1f;
            break;
        case 'w':
            global_rotation.z -= 0.1f;
            break;
        case 'd':
            speed2 *= 0.9f;
            if (speed2 <= MIN_SPEED)
                speed2 = MIN_SPEED;
            break;
        case 'f':
            speed2 *= 1.1f;
            if (speed2 >= MAX_SPEED)
                speed2 = MAX_SPEED;
            break;
        case 'g':
            sunStopped = !sunStopped;
            break;

    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    // GLUT: Initialize freeglut library (window toolkit).
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(40, 40);
    glutInit(&argc, argv);

    // GLUT: Create a window and opengl context (version 4.3 core profile).
    glutInitContextVersion(4, 3);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutCreateWindow("Aufgabenblatt 01");
    glutID = glutGetWindow();

    // GLEW: Load opengl extensions
    //glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        return -1;
    }
#if _DEBUG
    if (glDebugMessageCallback) {
      std::cout << "Register OpenGL debug callback " << std::endl;
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
      glDebugMessageCallback(cg::glErrorVerboseCallback, nullptr);
      glDebugMessageControl(GL_DONT_CARE,
                GL_DONT_CARE,
                GL_DONT_CARE,
                0,
                nullptr,
                true); // get all debug messages
    } else {
      std::cout << "glDebugMessageCallback not available" << std::endl;
    }
#endif

    // GLUT: Set callbacks for events.
    glutReshapeFunc(glutResize);
    glutDisplayFunc(glutDisplay);
    glutIdleFunc(glutDisplay); // redisplay when idle

    glutKeyboardFunc(glutKeyboard);

    // init vertex-array-objects.
    bool result = init();
    if (!result) {
        return -2;
    }

    // GLUT: Loop until the user closes the window
    // rendering & event handling
    glutMainLoop();

    // Cleanup in destructors:
    // Objects will be released in ~Object
    // Shader program will be released in ~GLSLProgram

    return 0;
}
