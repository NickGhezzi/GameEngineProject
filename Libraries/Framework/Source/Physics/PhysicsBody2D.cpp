#include "FrameworkPCH.h"
#include "box2d/box2d.h"

namespace fw
{

    PhysicsBody2D::PhysicsBody2D(b2Body* body)
    {
        m_pBody = body;
    }

    PhysicsBody2D::~PhysicsBody2D()
    {

    }

    void PhysicsBody2D::ApplyForce(Vector3 force)
    {

    }
}