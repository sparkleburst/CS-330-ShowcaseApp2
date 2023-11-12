//
// Created by maxan on 11/7/2023.
//

#pragma once
#include <glm/glm.hpp>

// each triangle will have some or all of the attributes below
struct Vertex {
    glm::vec3 Position {0.f, 0.f, 0.f}; // default position of (0,0,0)
    glm::vec3 Color {1.f, 1.f, 1.f}; // default color white
    glm::vec3 Normal {0.f, 0.f, 0.f};
    glm::vec2 Uv {1.f, 1.f};
};


/*
// below is work done to get to a more efficient way of doing things
// a struct with 3 floats
// a struct is a class where everything is automatically public
struct Vertex{
    // glm::vec3 is a struct with three floats
    // if we initialize Position then we don't have to add this to every single vertex
    glm::vec3 Position {0.f, 0.f, 0.f}; // represents a vertex with 3 points: x, y and z
    // default position: x=0, y=0, z=0

     * above is a simpler way of writing what is below
    float positionX;
    float positionY;
    float positionZ;

    // if we initialize Color then we don't have to add this to every single vertex
    glm::vec3 Color {1.f, 1.f, 1.f}; // represents rgb color data
    // default color: white
    // if we initialize UV then we don't have to add this to every single vertex
    glm::vec2 UV {1.f, 1.f};
    glm::vec3 Normal {0.f, 0.f, 0.f}; // represents the normals (or which
    // way it is facing)
};

float RawArray[] = {
        //position                          //color
        -0.5f, -0.5f, 0.0f,     1.f, 1.f, 1.f,
        0.5f, -0.5f, 0.0f,      1.f, 1.f, 1.f,
        0.0f, 0.5f, 0.0f,     1.f, 1.f, 1.f
};

// below are the arrays in the struct Vertex
Vertex vertices[] = {
         we technically don't need to show position or color data because we have
         * initialised them in struct Vertex
         * Three empty squiggly braces will work just as well. Only need to add Vertex
         * values that are different from the default

        {
            //.Position = {-0.5f, -0.5f, 0.0f},
            //.Color = {1.f, 1.f, 1.f}
        },
        {
            //.Position = {0.5f, -0.5f, 0.0f},
            //.Color = {1.f, 1.f, 1.f}
        },
        {
            //.Position = {0.0f, 0.5f, 0.0f},
            //.Color = {1.f, 1.f, 1.f}
        },


         * below is the arrays in vertex that went with the original, more
         * complicated way of doing this
        {-0.5f, -0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {0.0f, 0.5f, 0.0f}

};

*/