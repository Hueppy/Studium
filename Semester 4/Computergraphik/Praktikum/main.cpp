#include <iostream>
#include <vector>

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <forward_list>

#include "GLSLProgram.h"
#include "GLTools.h"
#include "color.h"
#include "objects.h"
#include "ObjLoader.h"

// Standard window width
const int WINDOW_WIDTH = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

int n = 0;
float size = 1.0f;
float distance = 4.0f;
float speed = 0.01f;
float speed2 = 0.01f;
float scale = 1.f;

const float MIN_SPEED = 0.0001f;
const float MAX_SPEED = 0.1f;

bool sunStopped = false;
bool wireframe = false;

glm::vec3 global_rotation(0.0f, 0.0f, 0.0f);
glm::mat4 global(1.0f);
glm::vec4 light(0.f, -1.f, 0.f, 0.f);
float lightI = 1.f;

class PlanetarySystem {
public:
    PlanetarySystem()
            : model(1.f),
              drawAxis(false) {
    }

    PlanetarySystem(int n, glm::vec3 color)
            : model(1.f),
              drawAxis(false) {
        init(n, color);
    }

    void init(int n, glm::vec3 color) {
        sphere.init(n, color);
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

    PlanetarySystem &add(int n, glm::vec3 color) {
        return children.emplace_front(n, color);
    }

    void translate(glm::vec3 v) {
        sphere.objSharp.model = glm::translate(sphere.objSharp.model, v);
        sphere.objSmooth.model = glm::translate(sphere.objSmooth.model, v);
        sphere.objNormals.model = glm::translate(sphere.objNormals.model, v);
        axis.object.model = glm::translate(axis.object.model, v);
        model = glm::translate(model, v);
    }

    void scale(glm::vec3 v) {
        sphere.objSharp.model = glm::scale(sphere.objSharp.model, v);
        sphere.objSmooth.model = glm::scale(sphere.objSmooth.model, v);
        sphere.objNormals.model = glm::scale(sphere.objNormals.model, v);
        sphere.objBounding.model = glm::scale(sphere.objBounding.model, v);
    }

    void rotate(glm::vec3 v) {
        model = glm::rotate(model, v.x, glm::vec3(1.f, 0.f, 0.f));
        model = glm::rotate(model, v.y, glm::vec3(0.f, 1.f, 0.f));
        model = glm::rotate(model, v.z, glm::vec3(0.f, 0.f, 1.f));
    }

    void rotateLocal(glm::vec3 v) {
        sphere.objSharp.model = glm::rotate(sphere.objSharp.model, v.x, glm::vec3(1.f, 0.f, 0.f));
        sphere.objSharp.model = glm::rotate(sphere.objSharp.model, v.y, glm::vec3(0.f, 1.f, 0.f));
        sphere.objSharp.model = glm::rotate(sphere.objSharp.model, v.z, glm::vec3(0.f, 0.f, 1.f));
        sphere.objSmooth.model = glm::rotate(sphere.objSmooth.model, v.x, glm::vec3(1.f, 0.f, 0.f));
        sphere.objSmooth.model = glm::rotate(sphere.objSmooth.model, v.y, glm::vec3(0.f, 1.f, 0.f));
        sphere.objSmooth.model = glm::rotate(sphere.objSmooth.model, v.z, glm::vec3(0.f, 0.f, 1.f));
        sphere.objNormals.model = glm::rotate(sphere.objNormals.model, v.x, glm::vec3(1.f, 0.f, 0.f));
        sphere.objNormals.model = glm::rotate(sphere.objNormals.model, v.y, glm::vec3(0.f, 1.f, 0.f));
        sphere.objNormals.model = glm::rotate(sphere.objNormals.model, v.z, glm::vec3(0.f, 0.f, 1.f));
        sphere.objBounding.model = glm::rotate(sphere.objBounding.model, v.x, glm::vec3(1.f, 0.f, 0.f));
        sphere.objBounding.model = glm::rotate(sphere.objBounding.model, v.y, glm::vec3(0.f, 1.f, 0.f));
        sphere.objBounding.model = glm::rotate(sphere.objBounding.model, v.z, glm::vec3(0.f, 0.f, 1.f));
    }

    void shading(Shading shading) {
        sphere.shading = shading;

        for (auto &child: children) {
            child.shading(shading);
        }
    }

    void normals(bool show) {
        if (sphere.hasNormals) {
            sphere.renderNormals = show;
        } else if (show) {
            std::cerr << "Objekt hat keine Normalen definiert.\n";
        }

        for (auto &child: children) {
            child.normals(show);
        }
    }

    void bounding(bool show) {
        sphere.renderBounding = show;
    }

    Sphere sphere;
    Axis axis;
    bool drawAxis;
    std::forward_list<PlanetarySystem> children;
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

    // Create all objects.

    sun.init(5, glm::vec3(1.f, 1.f, 0.f));
    sun.scale(glm::vec3(.5f));
    sun.drawAxis = true;

    auto &planet = sun.add(5, glm::vec3(0.f, 0.f, 1.f));
    planet.translate(glm::vec3(1.f, 0.f, 0.f));
    planet.scale(glm::vec3(.25f));
    planet.drawAxis = true;

    auto &m1 = planet.add(5, glm::vec3(0.5f, 0.5f, 0.5f));
    m1.translate(glm::vec3(0.f, .5f, 0.f));
    m1.scale(glm::vec3(.125f));

    auto &m2 = planet.add(5, glm::vec3(0.5f, 0.5f, 0.5f));
    m2.translate(glm::vec3(0.f, -.5f, 0.f));
    m2.scale(glm::vec3(.125f));


    ObjLoader loader;
    auto obj = loader.load("objects/bigguy.obj");
    glm::vec3 max(std::numeric_limits<float>::min());
    glm::vec3 min(std::numeric_limits<float>::max());
    for (auto &vertex: obj.vertices) {
        max.x = std::max(max.x, vertex.x);
        max.y = std::max(max.y, vertex.y);
        max.z = std::max(max.z, vertex.z);
        min.x = std::min(min.x, vertex.x);
        min.y = std::min(min.y, vertex.y);
        min.z = std::min(min.z, vertex.z);
    }

    sun.sphere.objSharp.from(obj, sun.sphere.flatShader);
    sun.sphere.objSmooth.from(obj, sun.sphere.gouraudShader);
    if (obj.normals.empty()) {
        sun.sphere.hasNormals = false;
    } else {
        sun.sphere.hasNormals = true;
        sun.sphere.objNormals.fromNormals(obj, sun.sphere.flatShader);
    }

    sun.sphere.updateBounding(min, max);

    sun.scale(glm::vec3(1 / std::max(std::max(max.x, max.y), max.z)));

    return true;
}

/*
 Rendering.
 */
void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
    global = glm::scale(global, glm::vec3(scale));

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
            sun.rotateLocal(glm::vec3(0.1f, 0.f, 0.f));
            break;
        case 'y':
            sun.rotateLocal(glm::vec3(0.f, 0.1f, 0.f));
            break;
        case 'z':
            sun.rotateLocal(glm::vec3(0.f, 0.f, 0.1f));
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
        case 'o':
            wireframe = !wireframe;
            break;
        case 'p':
            sun.shading(Shading::Flat);
            break;
        case 'P':
            sun.shading(Shading::Gouraud);
            break;
        case 'n':
            sun.normals(true);
            break;
        case 'N':
            sun.normals(false);
            break;
        case '+':
            scale *= 1.1f;
            break;
        case '-':
            scale *= 0.9f;
            break;
        case 'b':
            sun.bounding(false);
            break;
        case 'B':
            sun.bounding(true);
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
