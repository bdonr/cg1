

#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include "../CgEvents/CgLoadObjFileEvent.h"
#include "../CgEvents/CgTrackballEvent.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMenuBar>
#include <QActionGroup>
#include <QFileDialog>
#include <iostream>


/**
 * Erstelle Materialien , die in der Combobox für Materialen
 * angezeigt werden
 * @brief CgQtGui::createMats
 */

void CgQtGui::createMats()
{
    amb.push_back(glm::vec4(.25f,.25f,.25f,1.0));
    def.push_back(glm::vec4(.40f,.40f,.40f,1.0));
    spec.push_back(glm::vec4(.77f,.77f,.77f,1.0));
    scala.push_back(76.8);

    amb.push_back(glm::vec4(.25f,.21f,.21f,.90f));
    def.push_back(glm::vec4(0.99f,.83f,.83f,.90f));
    spec.push_back(glm::vec4(0.30f,0.30f,0.30f,0.90f));
    scala.push_back(11.3);

    amb.push_back(glm::vec4(0.5f,0.5f,0.7f,0.8f));
    def.push_back(glm::vec4(0.18f,0.17f,0.23f,0.8f));
    spec.push_back(glm::vec4(0.33f,0.33f,0.35f,0.8f));
    scala.push_back(38.4);
    //gold


    amb.push_back(glm::vec4(0.25f,0.20f,0.07f,1.f));
    def.push_back(glm::vec4(0.75f,0.61f,0.23f,1.f));
    spec.push_back(glm::vec4(0.63f,0.56f,0.37f,0.9f));
    scala.push_back(51.2);

    amb.push_back(glm::vec4(0.19f,0.19f,0.19f,1.0f));
    def.push_back(glm::vec4(0.51f,0.51f,0.51f,1.0f));
    spec.push_back(glm::vec4(0.51f,0.51f,0.51f,1.f));
    scala.push_back(51.2);

    amb.push_back(glm::vec4(0.2f,0.2f,0.2f,1.0f));
    def.push_back(glm::vec4(0.1f,0.1f,0.1f,1.0f));
    spec.push_back(glm::vec4(0.5f,0.5f,0.5f,1.f));
    scala.push_back(51.2);
}

CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw)
{
    m_glRenderWidget = new CgQtGLRenderWidget;


    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent*)), this, SLOT(mouseEvent(QMouseEvent*)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int,int)), this, SLOT(viewportChanged(int,int)));
    connect(m_glRenderWidget, SIGNAL(trackballChanged()), this, SLOT(slotTrackballChanged()));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;

    QWidget *otheropt = new QWidget;
    Aufgabe6(otheropt);

    QTabWidget* m_tabs = new QTabWidget();
    m_tabs->addTab(otheropt,"&My Tab1");
    container->addWidget(m_tabs);

    m_tabs->setMaximumWidth(400);

    container->addWidget(m_glRenderWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    setLayout(mainLayout);
    setWindowTitle(tr("Übung Computergrafik 1 -  SoSe 2018"));


    /* create Menu Bar */
    m_menuBar = new QMenuBar;
    QMenu *file_menu = new QMenu("&File" );
    file_menu->addAction("&Open Mesh Model", this, SLOT(slotLoadMeshFile()));
    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    QMenu *settings_menu = new QMenu("&Setting" );
    QMenu *polygon_mode_menu = new QMenu("&Polygon Mode" );

    QAction* m_custom_rot=settings_menu->addAction("&Custom Rotations", m_glRenderWidget, SLOT(slotCustomRotation()));
    m_custom_rot->setCheckable(true);
    m_custom_rot->setChecked(false);

    QAction* m_lighting=settings_menu->addAction("&Lighting on", m_glRenderWidget, SLOT(slotLighting()));
    m_lighting->setCheckable(true);
    m_lighting->setChecked(false);


    QActionGroup* polygonmode_group = new QActionGroup(this);
    polygonmode_group->setExclusive(true);

    QAction* points=polygon_mode_menu->addAction("&Points", m_glRenderWidget, SLOT(slotPolygonPoints()));
    points->setCheckable(true);
    points->setChecked(false);


    QAction* wireframe=polygon_mode_menu->addAction("&Wireframe", m_glRenderWidget, SLOT(slotPolygonWireframe()));
    wireframe->setCheckable(true);
    wireframe->setChecked(true);

    QAction* filled=polygon_mode_menu->addAction("&Filled", m_glRenderWidget, SLOT(slotPolygonFilled()));
    filled->setCheckable(true);
    filled->setChecked(false);

    createMats();

    polygonmode_group->addAction(points);
    polygonmode_group->addAction(wireframe);
    polygonmode_group->addAction(filled);



    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    m_menuBar->addMenu( settings_menu );
    m_menuBar->addMenu( polygon_mode_menu );


    m_mainWindow->setMenuBar(m_menuBar);



}

QSlider *CgQtGui::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}





/**
 * Auswahl ändern wenn Shader on sind
 * @brief CgQtGui::selectMaterialShaderOn
 * @param names
 */

void CgQtGui::selectMaterialShaderOn()
{
    names.clear();
    names.push_back("Chrom");
    names.push_back("Perle");
    names.push_back("Obsidian");
    names.push_back("Gold");
    names.push_back("Silber");
    names.push_back("Plastik");
}

/**
 * Auswahl ändern, wenn Shader off sind
 * @brief CgQtGui::selectMaterialShaderOff
 * @param names
 */
void CgQtGui::selectMaterialShaderOff()
{
    names.clear();
    names.push_back("Rot");
    names.push_back("Gruen");
    names.push_back("Blau");
}

/**
 * Auswahl an Shadern
 * @brief CgQtGui::selectShader
 * @param names
 */
void CgQtGui::selectShader()
{
    names.clear();
    names.push_back("none");
    names.push_back("Phong");
    names.push_back("Gouraud");
}
/**
 * Auswahl an Interpolationsmöglichkeiten
 * @brief CgQtGui::selectInterpolation
 * @param names
 */
void CgQtGui::selectInterpolation()
{
    names.clear();
    names.push_back("none");
    names.push_back("flat");
    names.push_back("smooth");
}

/**
 * Erstelle Tab 6
 * @brief CgQtGui::Aufgabe6
 * @param parent
 */
void CgQtGui::Aufgabe6(QWidget* parent)
{
    QVBoxLayout *tab1_control = new QVBoxLayout();
    QLabel * opt = new QLabel("selektiere eine Objekteigenschaft");
    combo_box_shader = new QComboBox();
    combo_box_interpolation = new QComboBox();
    combo_box_material = new QComboBox();
    selectMaterialShaderOff();
    createComboBox(combo_box_material);
    selectShader();
    createComboBox(combo_box_shader);
    selectInterpolation();
    createComboBox(combo_box_interpolation);

    tab1_control->addWidget(combo_box_material);
    tab1_control->addWidget(combo_box_shader);
    tab1_control->addWidget(combo_box_interpolation);
    tab1_control->addWidget(opt);

    connect(combo_box_material, SIGNAL(currentIndexChanged(int)),this,SLOT(selectColor()));
    connect(combo_box_shader, SIGNAL(currentIndexChanged(int)),this,SLOT(selectShaderSlot()));
    connect(combo_box_interpolation, SIGNAL(currentIndexChanged(int)),this,SLOT(selectInterpolationSlot()));
    parent->setLayout(tab1_control);

}
/**
 * Erstelle Inhalt der Comboboxen
 * @brief CgQtGui::createComboBox
 * @param names
 * @param combo
 */
void CgQtGui::createComboBox(QComboBox* combo){
    for(int i =0; i<names.size(); i++){
        combo->addItem(names.at(i));
    }
}

/**
 * Löschen Inhalt der Combobox
 * @brief CgQtGui::clearComboBox
 * @param combo
 */
void CgQtGui::clearComboBox(QComboBox* combo){
    combo->clear();
}

/**
 * Slot um Material auszuwählen
 * @brief CgQtGui::selectObjectMaterial
 */
void CgQtGui::selectObjectMaterial()
{
    if(combo_box_material->currentIndex()!=-1){
        MaterialChangeEvent * materialChangeEvent = new MaterialChangeEvent();
        materialChangeEvent->setAmb(amb.at(combo_box_material->currentIndex()));
        materialChangeEvent->setDiffuse(def.at(combo_box_material->currentIndex()));
        materialChangeEvent->setScalar(scala.at(combo_box_material->currentIndex()));
        materialChangeEvent->setMat(spec.at(combo_box_material->currentIndex()));
        notifyObserver(materialChangeEvent);
    }
}

/**
 * Slot um Farbe auszuwählen
 * @brief CgQtGui::selectColor
 */
void CgQtGui::selectColor()
{
    notifyObserver(new BoxChangedEvent(Cg::EventType::CgChangeColor,combo_box_material->currentIndex()));
}


void CgQtGui::slotButtonGroupSelectionChanged()
{

}

void CgQtGui::slotMySpinBox1Changed()
{

}

void CgQtGui::slotMyCheckBox1Changed()
{

}


void CgQtGui::slotLoadMeshFile()
{
    QString file=  QFileDialog::getOpenFileName(this, tr("Open Obj-File"),"",tr("Model Files (*.obj)"));
    CgBaseEvent* e = new CgLoadObjFileEvent(Cg::LoadObjFileEvent, file.toStdString());
    std::cout<<file.toStdString()<<std::endl;
    notifyObserver(e);
}

void CgQtGui::clearBoxes()
{
    clearComboBox(combo_box_material);
    clearComboBox(combo_box_interpolation);
    clearComboBox(combo_box_shader);
}

/**
 * wenn combo_box_shader index == 0 dann ist farbe off und nun kann die farbe des objects gewählt werden
 * @brief CgQtGui::selectShaderSlot
 */
void CgQtGui::selectShaderSlot()
{

    selectShader();
    combo_box_material->clear();
    if(combo_box_shader->currentIndex()==0){
        disconnect(combo_box_material, SIGNAL(currentIndexChanged(int)),this,SLOT(selectObjectMaterial()));
        connect(combo_box_material, SIGNAL(currentIndexChanged(int)),this,SLOT(selectColor()));
        selectMaterialShaderOff();

    }
    else{
        disconnect(combo_box_material, SIGNAL(currentIndexChanged(int)),this,SLOT(selectColor()));
        connect(combo_box_material, SIGNAL(currentIndexChanged(int)),this,SLOT(selectObjectMaterial()));
        notifyObserver(new BoxChangedEvent(Cg::EventType::CgChangeShader, combo_box_shader->currentIndex()));
        selectMaterialShaderOn();

    }
    createComboBox(combo_box_material);



}

void CgQtGui::selectInterpolationSlot()
{
    std::cout<<combo_box_interpolation->currentIndex()<<std::endl;
    notifyObserver(new BoxChangedEvent(Cg::EventType::CgChangeInterpolation , combo_box_interpolation->currentIndex()));
}


void CgQtGui::slotTrackballChanged()
{
    CgBaseEvent* e = new CgTrackballEvent(Cg::CgTrackballEvent, m_glRenderWidget->getTrackballRotation());
    notifyObserver(e);
}

void CgQtGui::slotMyButton1Pressed()
{
    std::cout << "button 1 pressed " << std::endl;
}


void CgQtGui::mouseEvent(QMouseEvent* event)
{

    // std::cout << QApplication::keyboardModifiers() << std::endl;

    //  if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)==true)
    //    std::cout << Cg::ControlModifier << endl;


    if(event->type()==QEvent::MouseButtonPress)
    {


        CgBaseEvent* e = new CgMouseEvent(Cg::CgMouseButtonPress,
                                          glm::vec2(event->localPos().x() ,event->localPos().y()),
                                          (Cg::MouseButtons)event->button());

        notifyObserver(e);
    }

    if(event->type()==QEvent::MouseMove)
    {
        CgBaseEvent* e= new CgMouseEvent(Cg::CgMouseMove,
                                         glm::vec2(event->localPos().x() ,event->localPos().y()),
                                         (Cg::MouseButtons)event->button());
        notifyObserver(e);
    }



}

void CgQtGui::keyPressEvent(QKeyEvent *event)
{
    CgBaseEvent* e= new CgKeyEvent(Cg::CgKeyPressEvent,(Cg::Key)event->key(),(Cg::KeyboardModifiers)event->nativeModifiers(),event->text().toStdString());
    notifyObserver(e);
}


void CgQtGui::viewportChanged(int w, int h)
{
    CgBaseEvent* e = new CgWindowResizeEvent(Cg::WindowResizeEvent,w,h);
    notifyObserver(e);
}




CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}





