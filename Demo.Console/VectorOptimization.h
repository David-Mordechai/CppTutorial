#pragma once

#include <iostream>
#include <ostream>
#include <vector>

struct Vertex
{
    float x, y, z;

    Vertex(const float x, const float y, const float z)
        : x(x), y(y), z(z)
    {

    }

    Vertex(const Vertex& vertex)
        : x(vertex.x), y(vertex.y), z(vertex.z)
    {
        std::cout << "Copied!" << std::endl;
    }
};

void inline  VectorOptimization()
{
    std::vector<Vertex> vertices;
    vertices.reserve(3);
    vertices.emplace_back(1, 2, 3);
    vertices.emplace_back(4, 5, 6);
    vertices.emplace_back(7, 8, 9);
    vertices.emplace_back(10, 11, 12);
}