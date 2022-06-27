//
// Created by phue on 6/11/22.
//

#include <glm/gtc/matrix_inverse.hpp>
#include "objects.h"
#include "GLSLProgram.h"

const float normalScale = 0.2f;

extern glm::mat4x4 view;
extern glm::mat4x4 projection;
extern glm::vec4 light;
extern float lightI;

bool loadShader(cg::GLSLProgram &p, const char *vertex, const char *fragment) {
    // Create a shader program and set light direction.
    if (!p.compileShaderFromFile(vertex, cg::GLSLShader::VERTEX)) {
        std::cerr << p.log();
        return false;
    }

    if (!p.compileShaderFromFile(fragment, cg::GLSLShader::FRAGMENT)) {
        std::cerr << p.log();
        return false;
    }

    if (!p.link()) {
        std::cerr << p.log();
        return false;
    }

    return true;
}

void Object::init() {
    // Step 0: Create vertex array objSharp.
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &positionBuffer);
    glGenBuffers(1, &indexBuffer);
    glGenBuffers(1, &colorBuffer);
    glGenBuffers(1, &normalBuffer);

    // Modify model matrix.
    model = glm::mat4(1.0f);
}

void Object::render(glm::mat4x4 model, cg::GLSLProgram &program) {
    auto m = model * this->model;
    auto normalMatrix = glm::inverseTranspose(glm::mat3(m));

    // Bind the shader program and set uniform(s).
    program.use();
    program.setUniform("model", m);
    program.setUniform("view", view);
    program.setUniform("projection", projection);
    program.setUniform("normalMatrix", normalMatrix);
    program.setUniform("light", light);
    program.setUniform("lightI", lightI);

    // Bind vertex array objSharp so we can render the 1 triangle.
    glBindVertexArray(vao);
    glDrawElements(mode, count, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}

void Object::from(ObjFile &objFile, cg::GLSLProgram &program) {
    std::vector<ushort> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;

    for (auto &face: objFile.faces) {
        for (int i = 0; i <= face.size() - 3; i++) {
            for (int j = 0; j < 3; j++) {
                auto index = face[j == 0 ? 0 : i + j];
                auto v = vertices.emplace_back(objFile.vertices[index.indexVertices - 1]);
                if (!objFile.normals.empty())
                    normals.emplace_back(objFile.normals[index.indexNormals - 1]);
                indices.emplace_back(vertices.size() - 1);
                colors.emplace_back(1.f, 1.f, 0.f);
                std::cout << v.x << " " << v.y << " " << v.z << "\n";
            }
        }
    }

    GLuint programId = program.getHandle();
    GLuint pos;

    count = indices.size();

    glBindVertexArray(vao);

    // Step 1: Create vertex buffer objSharp for position attribute and bind it to the associated "shader attribute".
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(programId, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Step 2: Create vertex buffer objSharp for color attribute and bind it to...
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "color");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    if (!objFile.normals.empty()) {
        // Step 2: Create vertex buffer objSharp for color attribute and bind it to...
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

        // Bind it to color.
        pos = glGetAttribLocation(programId, "normal");
        glEnableVertexAttribArray(pos);
        glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    // Step 3: Create vertex buffer objSharp for indices. No binding needed here.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Unbind vertex array objSharp (back to default).
    glBindVertexArray(0);
}

void Object::fromNormals(ObjFile &objFile, cg::GLSLProgram &program) {
    std::vector<ushort> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    for (auto &face: objFile.faces) {
        for (auto &index: face) {
            vertices.emplace_back(objFile.vertices[index.indexVertices - 1]);
            indices.emplace_back(vertices.size() - 1);
            colors.emplace_back(0.f, 0.f, 0.f);
            vertices.emplace_back(objFile.vertices[index.indexVertices - 1] + objFile.normals[index.indexNormals - 1] * normalScale);
            indices.emplace_back(vertices.size() - 1);
            colors.emplace_back(1.f, 0.f, 1.f);
        }
    }

    GLuint programId = program.getHandle();
    GLuint pos;

    count = indices.size();

    glBindVertexArray(vao);

    // Step 1: Create vertex buffer objSharp for position attribute and bind it to the associated "shader attribute".
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(programId, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Step 2: Create vertex buffer objSharp for color attribute and bind it to...
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "color");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Step 3: Create vertex buffer objSharp for indices. No binding needed here.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Unbind vertex array objSharp (back to default).
    glBindVertexArray(0);

}

bool Sphere::init(int n, glm::vec3 color) {
    shading = Shading::Flat;
    // Create a shader program and set light direction.
    if (!loadShader(flatShader, "shader/flat.vert", "shader/flat.frag")) {
        return false;
    }
    if (!loadShader(gouraudShader, "shader/gouraud.vert", "shader/gouraud.frag")) {
        return false;
    }
    if (!loadShader(simpleShader, "shader/simple.vert", "shader/simple.frag")) {
        return false;
    }

    objNormals.mode = GL_LINES;
    objBounding.mode = GL_LINES;
    renderNormals = false;
    hasNormals = true;
    renderBounding = false;

    objSharp.init();
    objSmooth.init();
    objNormals.init();
    objBounding.init();
    update(n, color);
}

constexpr float deg2rad(float deg) {
    constexpr float pi = 3.14159265358979f;
    return deg * (pi / 180.0f);
}

void copyIndices(std::vector<ushort> &src, std::vector<ushort> &dest, int base) {
    for (ushort index: src) {
        dest.emplace_back(index + base);
    }
}

void Sphere::update(int n, glm::vec3 color) {
    float subangle_y = 90.0f / (n + 1.0f);

    std::vector<glm::vec3> base_vertices;
    std::vector<glm::vec3> base_triangles;
    std::vector<ushort> base_indices;
    std::vector<glm::vec3> base_normals;

    std::vector<glm::vec3> base_normal_vertices;
    std::vector<ushort> base_normal_indices;
    std::vector<glm::vec3> normal_colors;

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

            auto a = base_triangles.emplace_back(base_vertices[index]);
            base_indices.emplace_back(base_triangles.size() - 1);

            auto b = base_triangles.emplace_back(base_vertices[next]);
            base_indices.emplace_back(base_triangles.size() - 1);

            auto c = base_triangles.emplace_back(base_vertices[index + 1]);
            base_indices.emplace_back(base_triangles.size() - 1);

            // calculate normal
            auto u = b - a;
            auto v = c - a;
            auto normal = -glm::normalize(glm::cross(v, u));

            base_normals.emplace_back(normal);
            base_normals.emplace_back(normal);
            base_normals.emplace_back(normal);

            base_normal_vertices.emplace_back(a);
            base_normal_indices.emplace_back(base_normal_vertices.size() - 1);
            base_normal_vertices.emplace_back(a - normal * normalScale);
            base_normal_indices.emplace_back(base_normal_vertices.size() - 1);
            base_normal_vertices.emplace_back(b);
            base_normal_indices.emplace_back(base_normal_vertices.size() - 1);
            base_normal_vertices.emplace_back(b - normal * normalScale);
            base_normal_indices.emplace_back(base_normal_vertices.size() - 1);
            base_normal_vertices.emplace_back(c);
            base_normal_indices.emplace_back(base_normal_vertices.size() - 1);
            base_normal_vertices.emplace_back(c - normal * normalScale);
            base_normal_indices.emplace_back(base_normal_vertices.size() - 1);

            if (prev > 0) {
                auto a = base_triangles.emplace_back(base_vertices[index]);
                base_indices.emplace_back(base_triangles.size() - 1);

                auto b = base_triangles.emplace_back(base_vertices[prev]);
                base_indices.emplace_back(base_triangles.size() - 1);

                auto c = base_triangles.emplace_back(base_vertices[index + 1]);
                base_indices.emplace_back(base_triangles.size() - 1);

                // calculate normal
                auto u = b - a;
                auto v = c - a;
                auto normal = glm::normalize(glm::cross(v, u));

                base_normals.emplace_back(normal);
                base_normals.emplace_back(normal);
                base_normals.emplace_back(normal);

                base_normal_vertices.emplace_back(a);
                base_normal_indices.emplace_back(base_normal_vertices.size() - 1);
                base_normal_vertices.emplace_back(a - normal * normalScale);
                base_normal_indices.emplace_back(base_normal_vertices.size() - 1);
                base_normal_vertices.emplace_back(b);
                base_normal_indices.emplace_back(base_normal_vertices.size() - 1);
                base_normal_vertices.emplace_back(b - normal * normalScale);
                base_normal_indices.emplace_back(base_normal_vertices.size() - 1);
                base_normal_vertices.emplace_back(c);
                base_normal_indices.emplace_back(base_normal_vertices.size() - 1);
                base_normal_vertices.emplace_back(c - normal * normalScale);
                base_normal_indices.emplace_back(base_normal_vertices.size() - 1);
            }

            index++;
        }
        index++;
    }

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<ushort> indices;
    std::vector<glm::vec3> normal_vertices;
    std::vector<ushort> normal_indices;

    // top, front, right -> just copy
    copyIndices(base_indices, indices, vertices.size());
    for (glm::vec3 vertex: base_triangles) {
        vertices.emplace_back(vertex);
    }
    for (glm::vec3 normal: base_normals) {
        normals.emplace_back(normal);
    }
    copyIndices(base_normal_indices, normal_indices, normal_vertices.size());
    for (glm::vec3 normal_vertex: base_normal_vertices) {
        normal_vertices.emplace_back(normal_vertex);
    }


    // top, back, right -> flip z
    copyIndices(base_indices, indices, vertices.size());
    for (glm::vec3 vertex: base_triangles) {
        vertex.z *= -1;
        vertices.emplace_back(vertex);
    }
    for (glm::vec3 normal: base_normals) {
        normal.z *= -1;
        normals.emplace_back(normal);
    }
    copyIndices(base_normal_indices, normal_indices, normal_vertices.size());
    for (glm::vec3 normal_vertex: base_normal_vertices) {
        normal_vertex.z *= -1;
        normal_vertices.emplace_back(normal_vertex);
    }

    // top, back, left -> flip z and x
    copyIndices(base_indices, indices, vertices.size());
    for (glm::vec3 vertex: base_triangles) {
        vertex.x *= -1;
        vertex.z *= -1;
        vertices.emplace_back(vertex);
    }
    for (glm::vec3 normal: base_normals) {
        normal.x *= -1;
        normal.z *= -1;
        normals.emplace_back(normal);
    }
    copyIndices(base_normal_indices, normal_indices, normal_vertices.size());
    for (glm::vec3 normal_vertex: base_normal_vertices) {
        normal_vertex.x *= -1;
        normal_vertex.z *= -1;
        normal_vertices.emplace_back(normal_vertex);
    }

    // top, front, left -> flip x
    copyIndices(base_indices, indices, vertices.size());
    for (glm::vec3 vertex: base_triangles) {
        vertex.x *= -1;
        vertices.emplace_back(vertex);
    }
    for (glm::vec3 normal: base_normals) {
        normal.x *= -1;
        normals.emplace_back(normal);
    }
    copyIndices(base_normal_indices, normal_indices, normal_vertices.size());
    for (glm::vec3 normal_vertex: base_normal_vertices) {
        normal_vertex.x *= -1;
        normal_vertices.emplace_back(normal_vertex);
    }

    // copy all vertices and flip y for bottom half
    base_triangles = vertices;
    base_normals = normals;
    base_indices = indices;
    base_normal_vertices = normal_vertices;
    base_normal_indices = normal_indices;
    copyIndices(base_indices, indices, vertices.size());
    for (glm::vec3 vertex: base_triangles) {
        vertex.y *= -1;
        vertices.emplace_back(vertex);
    }
    for (glm::vec3 normal: base_normals) {
        normal.y *= -1;
        normals.emplace_back(normal);
    }
    copyIndices(base_normal_indices, normal_indices, normal_vertices.size());
    for (glm::vec3 normal_vertex: base_normal_vertices) {
        normal_vertex.y *= -1;
        normal_vertices.emplace_back(normal_vertex);
    }

    std::vector<glm::vec3> colors;
    for (int i = 0; i < vertices.size(); i++) {
        colors.emplace_back(color);
    }
    for (int i = 0; i < normal_vertices.size(); i++) {
        normal_colors.emplace_back(glm::vec3(1.f, 0.f, 1.f));
    }
    objSharp.count = indices.size();
    objSmooth.count = indices.size();
    objNormals.count = normal_indices.size();

    GLuint programId = flatShader.getHandle();
    GLuint pos;

    glBindVertexArray(objSharp.vao);

    // Step 1: Create vertex buffer objSharp for position attribute and bind it to the associated "shader attribute".
    glBindBuffer(GL_ARRAY_BUFFER, objSharp.positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(programId, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Step 3: Create vertex buffer objSharp for indices. No binding needed here.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objSharp.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Step 2: Create vertex buffer objSharp for color attribute and bind it to...
    glBindBuffer(GL_ARRAY_BUFFER, objSharp.colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "color");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Step 2: Create vertex buffer objSharp for color attribute and bind it to...
    glBindBuffer(GL_ARRAY_BUFFER, objSharp.normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "normal");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Unbind vertex array objSharp (back to default).
    glBindVertexArray(0);

    programId = gouraudShader.getHandle();

    glBindVertexArray(objSmooth.vao);

    // Step 1: Create vertex buffer objSharp for position attribute and bind it to the associated "shader attribute".
    glBindBuffer(GL_ARRAY_BUFFER, objSmooth.positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(programId, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Step 3: Create vertex buffer objSharp for indices. No binding needed here.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objSmooth.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Step 2: Create vertex buffer objSharp for color attribute and bind it to...
    glBindBuffer(GL_ARRAY_BUFFER, objSmooth.colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "color");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Step 2: Create vertex buffer objSharp for color attribute and bind it to...
    glBindBuffer(GL_ARRAY_BUFFER, objSmooth.normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "normal");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Unbind vertex array objSharp (back to default).
    glBindVertexArray(0);

    programId = simpleShader.getHandle();

    glBindVertexArray(objNormals.vao);

    // Step 1: Create vertex buffer objSharp for position attribute and bind it to the associated "shader attribute".
    glBindBuffer(GL_ARRAY_BUFFER, objNormals.positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, normal_vertices.size() * sizeof(glm::vec3), normal_vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(programId, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Step 3: Create vertex buffer objSharp for indices. No binding needed here.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objNormals.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, normal_indices.size() * sizeof(GLushort), normal_indices.data(), GL_STATIC_DRAW);

    // Step 2: Create vertex buffer objSharp for color attribute and bind it to...
    glBindBuffer(GL_ARRAY_BUFFER, objNormals.colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, normal_colors.size() * sizeof(glm::vec3), normal_colors.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "color");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Unbind vertex array objSharp (back to default).
    glBindVertexArray(0);
}

void Sphere::render(glm::mat4x4 model) {
    if (shading == Shading::Flat) {
        objSharp.render(model, flatShader);
    } else {
        objSmooth.render(model, gouraudShader);
    }
    if (renderNormals) {
        objNormals.render(model, simpleShader);
    }
    if (renderBounding) {
        objBounding.render(model, simpleShader);
    }

}

void Sphere::updateBounding(glm::vec3 start, glm::vec3 stop) {
    const std::vector<glm::vec3> vertices = { glm::vec3(start.x, start.y, start.z),
                                              glm::vec3(start.x, start.y, stop.z),
                                              glm::vec3(start.x, stop.y, start.z),
                                              glm::vec3(start.x, stop.y, stop.z),
                                              glm::vec3(stop.x, start.y, start.z),
                                              glm::vec3(stop.x, start.y, stop.z),
                                              glm::vec3(stop.x, stop.y, start.z),
                                              glm::vec3(stop.x, stop.y, stop.z), };
    const std::vector<glm::vec3> colors   = { glm::vec3(1.f, 0.f, 0.f),
                                              glm::vec3(1.f, 0.f, 0.f),
                                              glm::vec3(1.f, 0.f, 0.f),
                                              glm::vec3(1.f, 0.f, 0.f),
                                              glm::vec3(1.f, 0.f, 0.f),
                                              glm::vec3(1.f, 0.f, 0.f),
                                              glm::vec3(1.f, 0.f, 0.f),
                                              glm::vec3(1.f, 0.f, 0.f),};
    const std::vector<ushort> indices = { 0, 1, 1, 3, 3, 2, 2, 0,
                                          4, 5, 5, 7, 7, 6, 6, 4,
                                          0, 4, 1, 5, 3, 7, 2, 6 };

    objBounding.count = indices.size();

    GLuint programId = simpleShader.getHandle();
    GLuint pos;

    glBindVertexArray(objBounding.vao);

    // Step 1: Create vertex buffer objSharp for position attribute and bind it to the associated "shader attribute".
    glBindBuffer(GL_ARRAY_BUFFER, objBounding.positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(programId, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Step 3: Create vertex buffer objSharp for indices. No binding needed here.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objBounding.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Step 2: Create vertex buffer objSharp for color attribute and bind it to...
    glBindBuffer(GL_ARRAY_BUFFER, objBounding.colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "color");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Unbind vertex array objSharp (back to default).
    glBindVertexArray(0);

}

bool Axis::init(bool x, bool y, bool z, glm::vec3 color) {
    // Create a shader program and set light direction.
    if (!loadShader(program, "shader/simple.vert", "shader/simple.frag")) {
        return false;
    }

    object.init();
    object.mode = GL_LINES;
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

    object.count = indices.size();

    GLuint programId = program.getHandle();
    GLuint pos;

    glBindVertexArray(object.vao);

    // Step 1: Create vertex buffer objSharp for position attribute and bind it to the associated "shader attribute".
    glBindBuffer(GL_ARRAY_BUFFER, object.positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Bind it to position.
    pos = glGetAttribLocation(programId, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Step 3: Create vertex buffer objSharp for indices. No binding needed here.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Step 2: Create vertex buffer objSharp for color attribute and bind it to...
    glBindBuffer(GL_ARRAY_BUFFER, object.colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    // Bind it to color.
    pos = glGetAttribLocation(programId, "color");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Unbind vertex array objSharp (back to default).
    glBindVertexArray(0);
}

void Axis::render(glm::mat4x4 model) {
    // Bind the shader program and set uniform(s).
    program.use();
    program.setUniform("model", model * this->object.model);
    program.setUniform("view", view);
    program.setUniform("projection", projection);

    // Bind vertex array objSharp so we can render the 1 triangle.
    glBindVertexArray(object.vao);
    glDrawElements(GL_LINES, object.count, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}