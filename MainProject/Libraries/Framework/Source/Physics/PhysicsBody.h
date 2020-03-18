#pragma once
    class b2Body;

namespace fw
{

    class PhysicsBody
    {
    public:
        virtual ~PhysicsBody() {}

        virtual void ApplyForce(Vector3 force) = 0;
        virtual void ApplyTorque(float torque) = 0;

        virtual void AddBox(Vector3 size, float density, bool isSensor, float friction, float restitution) = 0;
        virtual void AddBoxWithFilter(Vector3 size, float density, bool isSensor, float friction, float restitution, uint16 categorybits, uint16 maskbits) = 0;
        virtual void AddCircle(float radius) = 0;
        virtual void AddCircleWithFilter(float radius, uint16 categorybits, uint16 maskbits) = 0;

        virtual void AddJoint(PhysicsBody* objectToAttach, Vector2 anchorPos) = 0;
        virtual void AddJointWithRestraint(PhysicsBody* objectToAttach, Vector2 anchorPos, float minAngle, float maxAngle) = 0;
        virtual void AddJointLocal(PhysicsBody* objectToAttach, Vector2 localanchorPosA, Vector2 localanchorPosB) = 0;
        virtual void AddJointWithMotor(PhysicsBody* objectToAttach, Vector2 anchorPos, float motorspeed, float maxtorque) = 0;

        virtual Vector3 GetPosition() = 0;
        virtual b2Body* GetBody() = 0;

        virtual float GetRotation() = 0;

        virtual void SetGravity(float scale) = 0;

        virtual void SetPosition(Vector3 pos) = 0;
        virtual void SetRotation(float pos) = 0;

        virtual void SetActive(bool isactive) = 0;

        virtual void ResetVelocity() = 0;
    };
}