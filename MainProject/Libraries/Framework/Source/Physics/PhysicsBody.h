#pragma once
    class b2Body;

namespace fw
{

    class PhysicsBody
    {
    public:
        virtual ~PhysicsBody() {}

        virtual void ApplyForce(Vector3 force) = 0;

        virtual void AddBox(Vector3 size, float density, bool isSensor, float friction, float restitution) = 0;
        virtual void AddCircle(float radius) = 0;

        virtual void AddJoint(PhysicsBody* objectToAttach, Vector2 anchorPos) = 0;

        virtual Vector3 GetPosition() = 0;
        virtual b2Body* GetBody() = 0;

        virtual void SetGravity(float scale) = 0;

        virtual void SetActive(bool isactive) = 0;
    };
}