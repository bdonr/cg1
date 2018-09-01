#ifndef INTERPOLATIONCHANGED_H
#define INTERPOLATIONCHANGED_H
#include "CgBase/CgBaseEvent.h"
class BoxChangedEvent : public CgBaseEvent
{

private: enum Cg::EventType type;
    float selected;
public:
    BoxChangedEvent();

    BoxChangedEvent(const enum Cg::EventType type, const float selected);

    // CgBaseEvent interface
public:
    Cg::EventType getType();
    CgBaseEvent *clone();
    float getSelected() const;
    void setSelected(float value);
};

#endif // INTERPOLATIONCHANGED_H
