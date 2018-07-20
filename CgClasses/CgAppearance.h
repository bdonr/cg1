#ifndef CGAPPEARANCE_H
#define CGAPPEARANCE_H
#include <glm/glm.hpp>

class CgAppearance
{
private: glm::vec4 material;
    glm::vec4 ambiente;
    glm::vec4 diffuse;
    glm::vec4 specular;

public:
    CgAppearance();
    glm::vec4 getSpecular() const;
    void setSpecular(const glm::vec4 &value);
    glm::vec4 getDiffuse() const;
    void setDiffuse(const glm::vec4 &value);
    glm::vec4 getAmbiente() const;
    void setAmbiente(const glm::vec4 &value);
    glm::vec4 getMaterial() const;
    void setMaterial(const glm::vec4 &value);
};

#endif // CGAPPEARANCE_H
