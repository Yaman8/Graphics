#pragma once

#include <fstream>
#include <sstream>
#include <string.h>

#include "Coord.h"

std::vector<Triangle> load(std::string filename)
{
    // std::cout << "Filename : " << filename;
    //Reads in file
    std::ifstream in;
    in.open(filename, std::ifstream::in);

    // Local cache of verts
    std::vector<Point> vertices;
    // Triangle triangle;
    std::vector<Triangle> model;
    Point2i texture;
    Point normal;

    //if file cannot be opened
    if (in.fail())
    {
        std::cout << "Cannot Read" << std::endl;
        exit(-1);
    }
    std::string line;

    while (!in.eof())
    {
        //get one line at a time
        std::getline(in, line);
        //string object
        std::istringstream iss(line.c_str());

        char trash;
        if (!line.compare(0, 2, "v ")) //starts with v<space>
        {
            iss >> trash; // first character is v
            Point v;
            // followed by xyz co-ords
            iss >> v.x;
            iss >> v.y;
            iss >> v.z;
            vertices.push_back(v);
        }
        else if (!line.compare(0, 2, "f ")) //starts with f<space>
        {
            Point temp;
            iss >> trash;                                               //first charecter is f
            while (iss >> temp.x >> trash >> temp.y >> trash >> temp.z) // in the form vert/vertTex/norm (vert is read, the rest are treated as trash)
            {
                //in wavefront obj all indices start at 1, not zero
                temp.x--; //vert
                temp.y--; //texture
                temp.z--; // normal
            }
            model.push_back(Triangle{ vertices[temp.x], vertices[temp.y], vertices[temp.z] });
        }
        else if (!line.compare(0, 3, "vt ")) //starts with vt<space>
        {
            iss >> trash >> trash; //Ignore vt
            Point2i uv;
            iss >> uv.x;
            iss >> uv.y;
            // triangle.texture = uv;
            texture = uv;
        }

        else if (!line.compare(0, 3, "vn ")) //starts with vn<space>
        {
            iss >> trash >> trash; //Ignore vn
            Point n;
            iss >> n.x;
            iss >> n.y;
            iss >> n.z;
            // triangle.normal = n;
            normal = n;
        }
    }
    return model;
}