#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgEvents/CgLoadObjFileEvent.h"
#include "CgEvents/CgTrackballEvent.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgExampleTriangle.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "CgUtils/ObjLoader.h"
#include <string>

CgSceneControl::CgSceneControl()
{
    m_triangle=NULL;
    lightsource=NULL;
    shadingon=true;
    m_current_transformation=glm::mat4(1.0);
    m_lookAt_matrix= glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    m_trackball_rotation=glm::mat4(1.);

    //.33 .22 .03 1.0 A
    // .78 .57 .11 1.0 D
    // .99 .94 .81 1.0 Sa
    // 27.9 S

}


CgSceneControl::~CgSceneControl()
{
    if(m_triangle!=NULL)
        delete m_triangle;
}

void CgSceneControl::setRenderer(CgBaseRenderer* r)
{
    m_renderer=r;
    m_renderer->setSceneControl(this);
}


void CgSceneControl::createbunny()
{


    ObjLoader* loader= new ObjLoader();
    loader->load("/home/don/Schreibtisch/Sommer2018/CgData/bunny.obj");

    std::vector<glm::vec3> pos;
    loader->getPositionData(pos);

    std::vector<glm::vec3> norm;
    loader->getNormalData(norm);

    std::vector<unsigned int> indx;
    loader->getFaceIndexData(indx);

    m_triangle->init(pos,norm,indx);
    m_renderer->init(m_triangle);
    m_renderer->render(m_triangle);
}

LightSource *CgSceneControl::getLightsource() const
{
    return lightsource;
}

void CgSceneControl::setLightsource(LightSource *value)
{
    lightsource = value;
}

void CgSceneControl::setMaterialEigenschaften()
{
    if(shadingon){
        m_renderer->setUniformValue("shininess",m_triangle->getShininess());
        m_renderer->setUniformValue("matDiffuseColor",m_triangle->getAppearance()->getDiffuse());
        m_renderer->setUniformValue("matAmbientColor",m_triangle->getAppearance()->getAmbiente());
        m_renderer->setUniformValue("matSpecularColor",m_triangle->getAppearance()->getMaterial());
    }
    else{
        std::cout<<"nmormal"<<std::endl;
        m_renderer->setUniformValue("color",m_triangle->getAppearance()->getColor());
    }
}
void CgSceneControl::setLightEigenschaften()
{
    m_renderer->setUniformValue("lightDiffuseColor",lightsource->getAppearance()->getDiffuse());
    m_renderer->setUniformValue("lightAmbientColor",lightsource->getAppearance()->getAmbiente());
    m_renderer->setUniformValue("lightSpecularColor",lightsource->getAppearance()->getMaterial());
    m_renderer->setUniformValue("lightdirection",lightsource->getDirection());

}

void CgSceneControl::setTriangle()
{
    m_triangle = new CgExampleTriangle();
    createbunny();
    CgAppearance *x = new CgAppearance();
    x->setColor(glm::vec4(0.,1.0,0,1.));
    m_triangle->setAppearance(x);
    m_triangle->setShininess(10.0);
    m_current_transformation*glm::vec4(0.1);
}

void CgSceneControl::drawTriangle()
{
    if(!m_triangle){
        setTriangle();
    }
    if(m_triangle)  {
        setMaterialEigenschaften();
    }
}

void CgSceneControl::createLightSource()
{
    CgAppearance *x = new CgAppearance();
    x->setAmbiente(glm::vec4(.2));
    x->setDiffuse(glm::vec4(1,1,1,1));
    x->setMaterial(glm::vec4(1.,1.,1.,.1));
    lightsource = new LightSource(x);
    lightsource->setDirection(glm::vec3(1.,1.,3.));
}

void CgSceneControl::setLightSource()
{
    if(!lightsource){
        createLightSource();
    }
    if(lightsource){
        setLightEigenschaften();
    }
}

void CgSceneControl::renderObjects()
{
    if(shadingon){
        std::cout<<"shading an"<<std::endl;
        m_renderer->setShaderSourceFiles("../Sommer2018/CgShader/phong.vert","../Sommer2018/CgShader/phong.frag");
    }
    else{
        std::cout<<"shading aus"<<std::endl;
        m_renderer->setShaderSourceFiles("../Sommer2018/CgShader/simple.vert","../Sommer2018/CgShader/simple.frag");
        m_renderer->setUniformValue("color",m_triangle->getAppearance()->getColor());
    }
    setLightSource();
    drawTriangle();
    // Materialeigenschaften setzen
    // sollte ja eigentlich pro Objekt unterschiedlich sein können, naja bekommen sie schon hin....



    glm::mat4 scale = glm::scale(m_current_transformation,glm::vec3(.2));

    glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation* m_current_transformation*scale ;
    glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

    m_renderer->setUniformValue("projMatrix",m_proj_matrix);
    m_renderer->setUniformValue("modelviewMatrix",mv_matrix);
    m_renderer->setUniformValue("normalMatrix",normal_matrix);
    m_renderer->setUniformValue("viewpos",glm::vec3(0,0,-1));

    m_renderer->init(m_triangle);
    m_renderer->render(m_triangle);


}



void CgSceneControl::checkValueOfEvent(CgBaseEvent* e)
{
    shadingon=true;
    if( ((BoxChangedEvent*)e)->getSelected()==0){
        shadingon=false;
    }
}

void CgSceneControl::handleEvent(CgBaseEvent* e)
{
    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    if(e->getType() & Cg::CgMouseEvent)
    {
        CgMouseEvent* ev = (CgMouseEvent*)e;
        //std::cout << *ev << std::endl;

        // hier kommt jetzt die Abarbeitung des Events hin...
    }


    if(e->getType() & Cg::CgTrackballEvent)
    {
        CgTrackballEvent* ev = (CgTrackballEvent*)e;
        m_trackball_rotation=ev->getRotationMatrix();
        m_renderer->redraw();
    }


    // die Enums sind so gebaut, dass man alle Arten von KeyEvents über CgEvent::CgKeyEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    // momentan werden nur KeyPressEvents gefangen.

    if(e->getType() & Cg::CgKeyEvent)
    {
        CgKeyEvent* ev = (CgKeyEvent*)e;
        std::cout << *ev <<std::endl;

        if(ev->text()=="+")
        {
            glm::mat4 scalemat;
            scalemat= glm::scale(scalemat,glm::vec3(1.1,1.1,1.1));
            m_current_transformation=m_current_transformation*scalemat;
            m_renderer->redraw();
        }
        if(ev->text()=="-")
        {
            glm::mat4 scalemat;
            scalemat= glm::scale(scalemat,glm::vec3(0.8,0.8,0.8));
            m_current_transformation=m_current_transformation*scalemat;
            m_renderer->redraw();
        }
        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    if(e->getType() & Cg::WindowResizeEvent)
    {
        CgWindowResizeEvent* ev = (CgWindowResizeEvent*)e;
        std::cout << *ev <<std::endl;
        m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
    }

    /**
      * bekommt Event vom Typ CgChangeMaterial und ändert dementsprechend das Material
    **/
    if(e->getType() & Cg::EventType::CgChangeMaterial){
        if(shadingon){
            this->m_triangle->getAppearance()->setAmbiente(((MaterialChangeEvent*)e)->getAmb());
            this->m_triangle->getAppearance()->setDiffuse(((MaterialChangeEvent*)e)->getDiffuse());
            this->m_triangle->getAppearance()->setMaterial(((MaterialChangeEvent*)e)->getMat());
            std::cout<<((MaterialChangeEvent*)e)->getScalar()<<std::endl;
            this->m_triangle->setShininess(((MaterialChangeEvent*)e)->getScalar());
            m_renderer->redraw();

        }
    }

    if(e->getType() & Cg::EventType::CgChangeShader){
        checkValueOfEvent(e);
        m_renderer->redraw();

    }

    if(e->getType() & Cg::EventType::CgChangeInterpolation){
        checkValueOfEvent(e);
        m_renderer->redraw();
    }
    if(e->getType() & Cg::LoadObjFileEvent)
    {

        CgLoadObjFileEvent* ev = (CgLoadObjFileEvent*)e;


        ObjLoader* loader= new ObjLoader();
        loader->load(ev->FileName());

        std::cout << ev->FileName() << std::endl;

        std::vector<glm::vec3> pos;
        loader->getPositionData(pos);

        std::vector<glm::vec3> norm;
        loader->getNormalData(norm);

        std::vector<unsigned int> indx;
        loader->getFaceIndexData(indx);



        m_triangle->init(pos,norm,indx);
        m_renderer->init(m_triangle);
        m_renderer->redraw();
    }

    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;


}
