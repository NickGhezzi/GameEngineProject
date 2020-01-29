#pragma once

namespace fw
{
    class PhysicsBody
    {
    public:
        virtual ~PhysicsBody() {}

        virtual void ApplyForce(Vector3 force) = 0;
        virtual void AddBox(Vector3 size, float density, bool isSensor, float friction, float restitution) = 0;
        virtual void AddCircle(float radius) = 0;
        virtual Vector3 GetPosition() = 0;
    };
}