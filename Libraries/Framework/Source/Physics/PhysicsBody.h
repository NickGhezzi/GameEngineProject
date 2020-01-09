#pragma once

namespace fw
{
    class PhysicsBody
    {
    public:
        virtual ~PhysicsBody() {}

        virtual void ApplyForce(Vector3 force) = 0;
    };
}