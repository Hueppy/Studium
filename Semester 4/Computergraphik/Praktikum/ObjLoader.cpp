//
// Created by phue on 6/26/22.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "ObjLoader.h"

ObjFile ObjLoader::load(const char *filename) {
    ObjFile obj;
    std::ifstream fs(filename, std::ifstream::in);

    while(fs.good()) {
        std::string type;
        fs >> type;

        if (type == "v") {
            glm::vec3 v;
            fs >> v.x;
            fs >> v.y;
            fs >> v.z;
            obj.vertices.emplace_back(v);
        } else if (type == "vn") {
            glm::vec3 n;
            fs >> n.x;
            fs >> n.y;
            fs >> n.z;
            obj.normals.emplace_back(n);
        } else if (type == "f") {
            std::string line;
            std::getline(fs, line);

            std::stringstream ss {line};
            std::vector<Index> indices;
            while (ss.good()) {
                Index i;
                std::string value;
                ss >> value;

                i.indexVertices = std::atoi(value.c_str());
                int count = 2;
                const char *str = value.c_str();
                while (count > 0 && *str != '\0') {
                    if (*str == '/')
                        count--;
                    str++;
                }
                i.indexNormals = std::atoi(str);
                indices.emplace_back(i);
            }
            obj.faces.emplace_back(indices);
        }
    }

    return obj;
}
