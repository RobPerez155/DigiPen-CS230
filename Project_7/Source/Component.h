#pragma once
#include "Stream.h"

class Entity;

class Component
{
public:
    Component(Entity& parent);
    virtual void Update(float dt) {UNREFERENCED_PARAMETER(dt);}
    virtual void Render() {}
    virtual void Read(Stream stream) = 0;
    virtual Component* Clone(Entity& newParent) const = 0;
    virtual ~Component() = default;
    Entity& GetParent() { return parent; }
private:
    Entity& parent;
};
