#ifndef MATERIALCHANGEEVENT_H
#define MATERIALCHANGEEVENT_H
#include <CgBase/CgBaseEvent.h>
#include <glm/common.hpp>
#include "CgBase/CgEnums.h"
class MaterialChangeEvent :public CgBaseEvent
{
public:
    MaterialChangeEvent();
    MaterialChangeEvent(glm::vec4 mat,glm::vec4 amb, glm::vec4 diffuse, float scalar, enum Cg::EventType type);
    enum Cg::EventType type;
    glm::vec4 mat;
    glm::vec4 amb;
    glm::vec4 diffuse;
    float scalar;

    // CgBaseEvent interface
public:

    Cg::EventType getType();
    CgBaseEvent *clone();
    glm::vec4 getMat() const;
    void setMat(const glm::vec4 &value);
    glm::vec4 getAmb() const;
    void setAmb(const glm::vec4 &value);
    glm::vec4 getDiffuse() const;
    void setDiffuse(const glm::vec4 &value);
    float getScalar() const;
    void setScalar(float value);
};

#endif // MATERIALCHANGEEVENT_H
