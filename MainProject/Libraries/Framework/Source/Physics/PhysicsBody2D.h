#pragma once

class b2Body;

namespace fw
{
    class PhysicsBody2D: public PhysicsBody
    {
    public:
        PhysicsBody2D(b2Body* body);
        virtual ~PhysicsBody2D();

        virtual void AddBox(Vector3 size, float density, bool isSensor, float friction, float restitution) override;
        virtual void AddCircle(float radius) override;

        virtual void ApplyForce(Vector3 force) override;
        virtual Vector3 GetPosition() override;

        virtual void SetActive(bool isactive) override;
    private:
        b2Body* m_pBody;
    };
}