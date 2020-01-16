#include "FrameworkPCH.h"
#include "box2d/box2d.h"


namespace fw
{
    PhysicsWorld2D::PhysicsWorld2D()
    {
        m_pWorld = new b2World(b2Vec2(0, -9.8));
    }
    PhysicsWorld2D::~PhysicsWorld2D()
    {
        delete m_pWorld;
    }

    void PhysicsWorld2D::Update(float deltaTime)
    {
        float timeStep = 1 / 60.0;  
        int velocityIterations = 8;  
        int positionIterations = 3;  

        m_pWorld->Step(timeStep, velocityIterations, positionIterations);
    }

    PhysicsBody* PhysicsWorld2D::CreateBody(Vector3 pos, float angle, bool isDynamic, void* pUserData)
    {
        b2BodyDef bodydef;
        bodydef.position = b2Vec2(pos.x, pos.y);
        bodydef.angle = angle;
        bodydef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
        bodydef.userData = pUserData;

        b2Body* pBody = m_pWorld->CreateBody(&bodydef);
        PhysicsBody* pPhysicsBody = new PhysicsBody2D(pBody);

        return pPhysicsBody;
    }
}