#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include "CgClasses/lightsource.h"
#include "CgEvents/materialchangeevent.h"
#include "CgEvents/BoxChangedEvent.h"
class CgBaseEvent;
class CgBaseRenderer;
class CgExampleTriangle;

class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    CgSceneControl();
    ~CgSceneControl();
    void handleEvent(CgBaseEvent* e);
    void setRenderer(CgBaseRenderer* r);

    void renderObjects();

    void createbunny();

    LightSource *getLightsource() const;
    void setLightsource(LightSource *value);

    void setMaterialEigenschaften();

    void setLightEigenschaften();

    void drawTriangle();
    
    void setTriangle();
    
    void setLightSource();
    
    void createLightSource();
    
    void checkValueOfEvent(CgBaseEvent* e);

private:

    CgBaseRenderer* m_renderer;

    CgExampleTriangle* m_triangle;
    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;
    LightSource * lightsource;
    bool shadingon;

};

#endif // CGSCENECONTROL_H
