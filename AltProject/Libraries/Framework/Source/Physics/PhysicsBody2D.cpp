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

        fixturedef.filter.categoryBits = 0x0002;
        fixturedef.filter.maskBits = 0x0004;

        m_pBody->CreateFixture( &fixturedef );
    }

    void PhysicsBody2D::AddBox(Vector3 size, float density, bool isSensor)
    {
        b2PolygonShape shape;
        shape.SetAsBox(size.x / 2, size.y / 2);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = density;
        fixturedef.isSensor = isSensor;
        fixturedef.friction = 0.2f;
        fixturedef.restitution = 0;

        m_pBody->CreateFixture(&fixturedef);
    }

    void PhysicsBody2D::AddBox(Vector3 size, float density, bool isSensor, int numMaskBits, uint16 categorybits, uint16* maskbits[])
    {
        b2PolygonShape boxShape;
        boxShape.SetAsBox(size.x / 2, size.y / 2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;
        fixtureDef.density = density;
        fixtureDef.isSensor = isSensor;
        fixtureDef.friction = 0.2;
        fixtureDef.restitution = 0;

        fixtureDef.filter.categoryBits = categorybits;
        fixtureDef.filter.maskBits = *maskbits[0];
        for (int i = 1; i < numMaskBits; i++)
        {
            fixtureDef.filter.maskBits |= *maskbits[i];
        }


        m_pBody->CreateFixture(&fixtureDef);
       // delete[] maskbits;

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

    void PhysicsBody2D::AddCircle(float radius, float density, int numMaskBits, uint16 categorybits, uint16* maskbits[])
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

        fixtureDef.filter.categoryBits = categorybits;
        fixtureDef.filter.maskBits = *maskbits[0];
        for (int i = 1; i < numMaskBits; i++)
        {
            fixtureDef.filter.maskBits |= *maskbits[i];
        }

        m_pBody->CreateFixture(&fixtureDef);

       // delete[] maskbits;
    }

    void PhysicsBody2D::AddChain(Vector2* points, int numPoints, float density)
    {
        b2ChainShape shape;
        shape.CreateChain( (b2Vec2*)points, numPoints );

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = density;
        fixturedef.isSensor = false;
        fixturedef.friction = 0.2f;
        fixturedef.restitution = 0;

        fixturedef.filter.categoryBits = 0x0002;
        fixturedef.filter.maskBits = 0x0004 | 0x0008;

        m_pBody->CreateFixture( &fixturedef );
    }

    void PhysicsBody2D::AddPrismaticJoint(PhysicsBody* objectToAttach, float upperTranslation, float LowerTranslation, float maxMotorForce, float motorSpeed)
    {
        b2PrismaticJointDef prismaticJointDef;
        prismaticJointDef.bodyA = m_pBody;
        prismaticJointDef.bodyB = objectToAttach->GetBody();
        prismaticJointDef.collideConnected = false;

        prismaticJointDef.localAxisA.Set(0, -1);

        prismaticJointDef.enableLimit = true;
        prismaticJointDef.upperTranslation = upperTranslation;
        prismaticJointDef.lowerTranslation = LowerTranslation;

        prismaticJointDef.enableMotor = true;
        prismaticJointDef.maxMotorForce = maxMotorForce;
        prismaticJointDef.motorSpeed = motorSpeed;

        m_Joint = (b2PrismaticJoint*)m_pBody->GetWorld()->CreateJoint(&prismaticJointDef);

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

    Vector2 PhysicsBody2D::GetLinearVelocity()
    {
        return Vector2(m_pBody->GetLinearVelocity().x, m_pBody->GetLinearVelocity().y);
    }

    b2Body* PhysicsBody2D::GetBody()
    {
        return m_pBody;
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

    void PhysicsBody2D::SetFixedRotation(bool isFixed)
    {
        m_pBody->SetFixedRotation(isFixed);
    }

    void PhysicsBody2D::EnableMotor(bool isEnabled)
    {
        m_Joint->EnableMotor(isEnabled);
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
