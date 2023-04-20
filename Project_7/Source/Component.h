#pragma once
#include "Stream.h"

class Entity;

class Component
{
public:
    enum  class Type
    {
        Transform,
        Behavior,
        Physics,
        Animation,
        Collider,
        Sprite,
        Count
    };
    Component(Entity& parent);
    virtual void Update(float dt) {UNREFERENCED_PARAMETER(dt);}
    virtual void Render() {}
    virtual void Read(Stream stream) = 0;
    virtual Component* Clone(Entity& newParent) const = 0;
    virtual void OnCollision(Entity* other) {UNREFERENCED_PARAMETER(other);}
    virtual ~Component() = default;
    Entity& GetParent() { return parent; }
private:
    // moved "Entity& parent;" to protected because it was blocking access from behaviorSpaceship
protected:
    Entity& parent;
};
