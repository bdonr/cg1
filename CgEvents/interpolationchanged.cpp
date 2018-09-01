#include "BoxChangedEvent.h"

float BoxChangedEvent::getSelected() const
{
    return selected;
}

void BoxChangedEvent::setSelected(float value)
{
    selected = value;
}

BoxChangedEvent::BoxChangedEvent()
{

}

BoxChangedEvent::BoxChangedEvent(const Cg::EventType type, const float selected):type(type),selected(selected)
{
}

Cg::EventType BoxChangedEvent::getType()
{
    return this->type;
}

CgBaseEvent *BoxChangedEvent::clone()
{
    return new BoxChangedEvent(type,selected);
}
