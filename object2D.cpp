#include "object2D.h"

#include <vector>
#include <iostream>
#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float height,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width , 0, 0), color),
        VertexFormat(corner + glm::vec3(width , height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
};
Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float radius,
    int num_segments ,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices ;

    vertices.push_back(VertexFormat(center, color));
    //indices.push_back(0);
    glm::vec3 myCenter = center;
    for (int ii = 0; ii <= num_segments; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
        float x = radius * cosf(theta);//calculate the x component 
        float y = radius * sinf(theta);//calculate the y component 
        // glVertex2f(x + cx, y + cy);//output vertex 
        vertices.push_back(VertexFormat(center + glm::vec3(x , y , 0), color));
        indices.push_back(0);
        indices.push_back(ii);
        indices.push_back(ii+1);

      
      //  indices.push_back(ii + 1);
       // std::cout<<indices.back;
    }
   


    Mesh* square = new Mesh(name);
    //std::vector<unsigned int> indices = { 0, 1, 2, 3 };


    square->InitFromData(vertices, indices);
    return square;
}
Mesh* object2D::CreateDuckBody(
const std::string& name,
glm::vec3 leftBottomCorner,
float length,
glm::vec3 color,
bool fill)
{
glm::vec3 corner = leftBottomCorner;

std::vector<VertexFormat> vertices =
{
    //VertexFormat(corner, color),
    VertexFormat(corner + glm::vec3(length, 0, 0), color),
    VertexFormat(corner + glm::vec3(3*length, 3*length, 0), color),
    VertexFormat(corner + glm::vec3(0, length, 0), color)
};

Mesh* square = new Mesh(name);
std::vector<unsigned int> indices = { 0, 1, 2 };

if (!fill) {
    //square->SetDrawMode(GL_LINE_LOOP);
}
else {
    // Draw 2 triangles. Add the remaining 2 indices
   // indices.push_back(0);
   // indices.push_back(2);
}

square->InitFromData(vertices, indices);
return square;
};
Mesh* object2D::CreateDuckWings(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        //VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(2*length, 0, 0), color),
        VertexFormat(corner + glm::vec3( 1.63*length, 1.63*length, 0), color),
        VertexFormat(corner + glm::vec3(0,2*length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        //square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
       // indices.push_back(0);
       // indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
};
Mesh* object2D::CreateDuckBeak(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        //VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(2.3 * length, 1.8*length, 0), color),
        VertexFormat(corner + glm::vec3(3 * length, 3 * length, 0), color),
        VertexFormat(corner + glm::vec3(1.8 * length,2.3 * length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        //square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
       // indices.push_back(0);
       // indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
};
