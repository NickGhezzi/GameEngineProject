#include "FrameworkPCH.h"

#include "PhysicsBody2D.h"
#include "box2d/box2d.h"

namespace fw
{
    PhysicsBody2D::PhysicsBody2D(b2Body* pBody)
    {
        m_pBody = pBody;
    }

    PhysicsBody2D::~PhysicsBody2D()
    {
        m_pBody->GetWorld()->DestroyBody( m_pBody );
    }

    void PhysicsBody2D::AddBox(Vector3 size, float density)
    {
        b2PolygonShape shape;
        shape.SetAsBox( size.x/2, size.y/2 );

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = density;
        fixturedef.isSensor = false;
        fixturedef.friction = 0.2f;
        fixturedef.restitution = 0;

        m_pBody->CreateFixture( &fixturedef );
    }

    void PhysicsBody2D::AddCircle(float radius, float density)
    {
        b2CircleShape shape;
        shape.m_radius = radius;
        shape.m_p.SetZero();

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = density;
        fixturedef.isSensor = false;
        fixturedef.friction = 0.2f;
        fixturedef.restitution = 0;

        m_pBody->CreateFixture( &fixturedef );
    }

    Vector3 PhysicsBody2D::GetPosition()
    {
        b2Vec2 pos = m_pBody->GetPosition();
        return Vector3( pos.x, pos.y, 0 );
    }

    Vector3 PhysicsBody2D::GetRotation()
    {
        float rot = m_pBody->GetAngle();
        return Vector3( 0, 0, -rot / PI * 180.0f );
    }

    float PhysicsBody2D::GetMass()
    {
        return m_pBody->GetMass();
    }

    void PhysicsBody2D::SetTransform(Vector3 pos, Vector3 rot)
    {
        m_pBody->SetTransform( b2Vec2( pos.x, pos.y ), -rot.z / 180.0f * PI );
    }

    void PhysicsBody2D::SetLinearVelocity(Vector3 vel)
    {
        m_pBody->SetLinearVelocity( b2Vec2( vel.x, vel.y ) );
    }

    void PhysicsBody2D::SetAngularVelocity(Vector3 vel)
    {
        m_pBody->SetAngularVelocity( vel.z );
    }

    void PhysicsBody2D::SetAwake(bool awake)
    {
        m_pBody->SetAwake( awake );
    }

    void PhysicsBody2D::SetActive(bool active)
    {
        m_pBody->SetActive( active );
    }

    void PhysicsBody2D::ApplyLinearForceToCenter(Vector3 impulse)
    {
        m_pBody->ApplyForceToCenter( b2Vec2( impulse.x, impulse.y ), true );
    }

    void PhysicsBody2D::ApplyLinearImpulseToCenter(Vector3 impulse)
    {
        m_pBody->ApplyLinearImpulseToCenter( b2Vec2( impulse.x, impulse.y ), true );
    }

    void PhysicsBody2D::ApplyTorque(Vector3 torque)
    {
        m_pBody->ApplyTorque( -torque.z, true );
    }
}
