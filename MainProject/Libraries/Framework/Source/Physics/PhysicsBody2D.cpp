#include "FrameworkPCH.h"
#include "box2d/box2d.h"
#include "PhysicsBody2D.h"
#include "Box2DDebugDraw.h"

namespace fw
{

    PhysicsBody2D::PhysicsBody2D(b2Body* body)
    {
        m_pBody = body;

    }

    PhysicsBody2D::~PhysicsBody2D()
    {
        m_pBody->GetWorld()->DestroyBody(m_pBody);
    }

    void PhysicsBody2D::AddBox(Vector3 size, float density, bool isSensor, float friction, float restitution)
    {
        b2PolygonShape boxShape;
        boxShape.SetAsBox(size.x / 2, size.y / 2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;
        fixtureDef.density = density;
        fixtureDef.isSensor = isSensor;
        fixtureDef.friction = friction;
        fixtureDef.restitution = restitution;

        m_pBody->CreateFixture(&fixtureDef);
    }

    void PhysicsBody2D::AddCircle(float radius)
    {
        b2CircleShape circleShape;
        circleShape.m_p.Set(0.0f, 0.0f);
        circleShape.m_radius = radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        fixtureDef.density = 1;
        fixtureDef.isSensor = false;
        fixtureDef.friction = 0.2f;
        fixtureDef.restitution = 0.0f;

        m_pBody->CreateFixture(&fixtureDef);
    }

    void PhysicsBody2D::AddJoint(PhysicsBody* objectToAttach, Vector2 anchorPos)
    {
        b2RevoluteJointDef jointdef;
        b2Vec2 anchor(anchorPos.x, anchorPos.y);
     
        jointdef.Initialize(m_pBody, objectToAttach->GetBody(), anchor);

        m_pBody->GetWorld()->CreateJoint(&jointdef);
    }

    void PhysicsBody2D::ApplyForce(Vector3 force)
    {
        b2Vec2 temp = b2Vec2(force.x, force.y);
        m_pBody->ApplyForce(temp, m_pBody->GetWorldCenter(), true);
    }

    Vector3 PhysicsBody2D::GetPosition()
    {
        return Vector3(m_pBody->GetPosition().x, m_pBody->GetPosition().y, 0);
    }

    b2Body* PhysicsBody2D::GetBody()
    {
        return m_pBody;
    }

    void PhysicsBody2D::SetGravity(float scale)
    {
        m_pBody->SetGravityScale(scale);
    }

    void PhysicsBody2D::SetActive(bool isactive)
    {
        m_pBody->SetActive(isactive);
    }
}