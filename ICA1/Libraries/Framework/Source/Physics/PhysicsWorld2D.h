#pragma once

#include "PhysicsWorld.h"

class b2World;

namespace fw
{
    class PhysicsBody;
    class PhysicsBody2D;
    class Box2DContactListener;

    class PhysicsWorld2D : public PhysicsWorld
    {
    protected:
        b2World* m_pWorld;
        Box2DContactListener* m_pContactListener;

    public:
        PhysicsWorld2D(Framework* pFramework);
        virtual ~PhysicsWorld2D();

        virtual void Update(float deltaTime) override;
        virtual PhysicsBody* CreateBody(Vector3 pos, Vector3 rot, bool isDynamic, void* pUserData) override;
    };
}
