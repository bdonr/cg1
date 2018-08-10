#include "lightsource.h"

glm::vec3 LightSource::getDirection() const
{
    return direction;
}

void LightSource::setDirection(const glm::vec3 &value)
{
    direction = value;
}


CgAppearance *LightSource::getAppearance() const
{
    return appearance;
}

void LightSource::setAppearance(CgAppearance *value)
{
    appearance = value;
}


LightSource::LightSource()
{

}

LightSource::LightSource(CgAppearance *appearance)
{
    this->appearance=appearance;
}
