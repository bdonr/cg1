#include "materialchangeevent.h"

MaterialChangeEvent::MaterialChangeEvent(): type(Cg::EventType::CgChangeMaterial)
{

}

MaterialChangeEvent::MaterialChangeEvent(glm::vec4 mat, glm::vec4 amb, glm::vec4 diffuse, float scalar, enum Cg::EventType type)
{
    this->amb=amb;
    this->diffuse=diffuse;
    this->mat=mat;
    this->scalar = scalar;
    this->type = type;
}

float MaterialChangeEvent::getScalar() const
{
    return scalar;
}

void MaterialChangeEvent::setScalar(float value)
{
    scalar = value;
}

glm::vec4 MaterialChangeEvent::getDiffuse() const
{
    return diffuse;
}

void MaterialChangeEvent::setDiffuse(const glm::vec4 &value)
{
    diffuse = value;
}

glm::vec4 MaterialChangeEvent::getAmb() const
{
    return amb;
}

void MaterialChangeEvent::setAmb(const glm::vec4 &value)
{
    amb = value;
}

glm::vec4 MaterialChangeEvent::getMat() const
{
    return mat;
}

void MaterialChangeEvent::setMat(const glm::vec4 &value)
{
    mat = value;
}

Cg::EventType MaterialChangeEvent::getType()
{
    return type;
}

CgBaseEvent *MaterialChangeEvent::clone()
{
    return new MaterialChangeEvent(mat,amb,diffuse,scalar,type);
}
