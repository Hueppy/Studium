//
// Created by phue on 6/26/22.
//

#ifndef BLATT01_OBJLOADER_H
#define BLATT01_OBJLOADER_H

#include <vector>
#include <glm/vec3.hpp>

class Index {
public:
    ushort indexVertices;
    ushort indexNormals;
};

class ObjFile {
public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<std::vector<Index>> faces;
};

class ObjLoader {
public:
    ObjFile load(const char *filename);
};


#endif //BLATT01_OBJLOADER_H
