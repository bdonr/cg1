#include "CgAppearance.h"

glm::vec4 CgAppearance::getSpecular() const
{
    return specular;
}

void CgAppearance::setSpecular(const glm::vec4 &value)
{
    specular = value;
}

glm::vec4 CgAppearance::getDiffuse() const
{
    return diffuse;
}

void CgAppearance::setDiffuse(const glm::vec4 &value)
{
    diffuse = value;
}

glm::vec4 CgAppearance::getAmbiente() const
{
    return ambiente;
}

void CgAppearance::setAmbiente(const glm::vec4 &value)
{
    ambiente = value;
}

glm::vec4 CgAppearance::getMaterial() const
{
    return material;
}

void CgAppearance::setMaterial(const glm::vec4 &value)
{
    material = value;
}

CgAppearance::CgAppearance()
{

}