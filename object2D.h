#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float height,float width, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string &name, glm::vec3 center, float radius,int num_segments, glm::vec3 color, bool fill = false);
    
    Mesh* CreateDuckBody(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

    Mesh* CreateDuckWings(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

    Mesh* CreateDuckBeak(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

    //std::vector<VertexFormat> vertices; 

}
