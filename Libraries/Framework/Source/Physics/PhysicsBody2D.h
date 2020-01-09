#pragma once

class b2Body;

namespace fw
{
    class PhysicsBody2D: public PhysicsBody
    {
    public:
        PhysicsBody2D(b2Body* body);
        virtual ~PhysicsBody2D();

        virtual void ApplyForce(Vector3 force) override;
    private:
        b2Body* m_pBody;
    };
}