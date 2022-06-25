//
// Created by phue on 6/11/22.
//

#include "objects.h"
#include "GLSLProgram.h"

extern cg::GLSLProgram program;

extern glm::mat4x4 view;
extern glm::mat4x4 projection;

void Object::init() {
    // Step 0: Create vertex array object.
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &positionBuffer);
    glGenBuffers(1, &indexBuffer);
    glGenBuffers(1, &colorBuffer);

    // Modify model matrix.
    model = glm::mat4(1.0f);

    initialized = true;
}

void Object::render(glm::mat4x4 model) {
    // Bind the shader program and set uniform(s).
    program.use();
    program.setUniform("model", model * this->model);
    program.setUniform("view", view);
    program.setUniform("projection", projection);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Bind vertex array object so we can render the 1 triangle.
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}

void Sphere::init(int n) {
    Object::init();
    update(n);
}

constexpr float deg2rad(float deg)
{
    constexpr float pi = 3.14159265358979f;
    return deg * (pi / 180.0f);
}

void copyIndices(std::vector<ushort> &src, std::vector<ushort> &dest, int base) {
    for (ushort index: src) {
        dest.emplace_back(index + base);
    }
}

void Sphere::update(int n) {
    float subangle_y = 90.0f / (n + 1.0f);

    std::vector<glm::vec3> base_vertices;
    std::vector<ushort> base_indices;

    glm::vec4 normal(0.0f, 0.0f, 1.0f, 1.0f);

    for (int i = 0; i <= n + 1; i++) {
        float angle_y = subangle_y * i;
        glm::vec4 pitch = normal *
                          glm::rotate(glm::mat4(1.0f), deg2rad(angle_y), glm::vec3(1.0f, 0.0f, 0.0f));

        float subangle_x = 90.0f;
        if (i < n + 1)
            subangle_x /= (n - i + 1.0f);

        for (int j = 0; j <= n - i + 1; j++) {
            float angle_x = subangle_x * j;
            glm::vec4 rotated = pitch *
                                glm::rotate(glm::mat4(1.0f), deg2rad(-angle_x), glm::vec3(0.0f, 1.0f, 0.0f));

            base_vertices.emplace_back(rotated.x, rotated.y, rotated.z);
        }
    }

    int index = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n - i; j++) {
            int next = n + 2 - i + index;
            int prev = index - n - 2 + i;

            base_indices.emplace_back(index);
            base_indices.emplace_back(next);
            base_indices.emplace_back(index + 1);

            if (prev > 0) {
                base_indices.emplace_back(index);
                base_indices.emplace_back(prev);
                base_indices.emplace_back(index + 1);
            }

            index++;
        }
        index++;
    }

    std::vector<glm::vec3> vertices;
    std::vector<ushort> indices;

    // top, front, right -> just copy
    copyIndices(base_indices, indices, vertices.size());
    for (glm::vec3 vertex: base_vertices) {
        vertices.emplace_back(vertex);
    }

    // top, back, right -> flip z
    copyIndices(base_indices, indices, vertices.size());
    for (glm::vec3 vertex: base_vertices) {
        vertex.z *= -1;
        vertices.emplace_back(vertex);
    }

    // top, back, left -> flip z and x
    copyIndices(base_indices, indices, vertices.size());
    for (glm::vec3 vertex: base_vertices) {
        vertex.x *= -1;
        vertex.z *= -1;
        vertices.emplace_back(vertex);
    }

    // top, front, left -> flip x
    copyIndices(base_indices, indices, vertices.size());
    for (glm::vec3 vertex: base_vertices) {
        vertex.x *= -1;
        vertices.emplace_back(vertex);
    }

    // copy all vertices and flip y for bottom half
    base_vertices = vertices;
    base_indices = indices;
    copyIndices(base_indices, indices, vertices.size());
    for (glm::vec3 vertex: base_vertices) {
        vertex.y *= -1;
        vertices.emplace_back(vertex);
    }

    std::vector<glm::vec3> colors;
    for (int i = 0; i < vertices.size(); i++) {
        colors.emplace_back(glm::vec3(1.0f, 1.0f, 0.0f));
    }

    count = indices.size();

    GLuint programId = program.getHandle();
    GLuint pos;

    glBindVertexArray(vao);

    // Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(programId, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Step 3: Create vertex buffer object for indices. No binding needed here.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Step 2: Create vertex buffer object for color attribute and bind it to...
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "color");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Unbind vertex array object (back to default).
    glBindVertexArray(0);

}

void Axis::init(bool x, bool y, bool z, glm::vec3 color) {
    Object::init();
    update(x, y, z, color);
}

void Axis::update(bool x, bool y, bool z, glm::vec3 color) {
    const std::vector<glm::vec3> vertices = { glm::vec3(0.0f, 0.0f, 0.0f),
                                              glm::vec3(1.0f, 0.0f, 0.0f),
                                              glm::vec3(0.0f, 1.0f, 0.0f),
                                              glm::vec3(0.0f, 0.0f, 1.0f) };
    const std::vector<glm::vec3> colors   = { color,
                                              color,
                                              color,
                                              color };
    std::vector<GLushort>  indices;

    if (x) {
        indices.emplace_back(0);
        indices.emplace_back(1);
    }
    if (y) {
        indices.emplace_back(0);
        indices.emplace_back(2);
    }
    if (z) {
        indices.emplace_back(0);
        indices.emplace_back(3);
    }

    count = indices.size();

    GLuint programId = program.getHandle();
    GLuint pos;

    glBindVertexArray(vao);

    // Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(programId, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Step 3: Create vertex buffer object for indices. No binding needed here.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Step 2: Create vertex buffer object for color attribute and bind it to...
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "color");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Unbind vertex array object (back to default).
    glBindVertexArray(0);
}

void Axis::render(glm::mat4x4 model) {
    // Bind the shader program and set uniform(s).
    program.use();
    program.setUniform("model", model * this->model);
    program.setUniform("view", view);
    program.setUniform("projection", projection);

    // Bind vertex array object so we can render the 1 triangle.
    glBindVertexArray(vao);
    glDrawElements(GL_LINES, count, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}