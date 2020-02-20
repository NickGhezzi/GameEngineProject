#pragma once

namespace fw
{
    class PhysicsBody
    {
    public:
        virtual ~PhysicsBody() = 0 {}

        virtual void AddBox(Vector3 size, float density) = 0;
        virtual void AddCircle(float radius, float density) = 0;

        virtual Vector3 GetPosition() = 0;
        virtual Vector3 GetRotation() = 0;
        virtual float GetMass() = 0;
        
        virtual void SetTransform(Vector3 pos, Vector3 rot) = 0;
        virtual void SetLinearVelocity(Vector3 vel) = 0;
        virtual void SetAngularVelocity(Vector3 vel) = 0;
        virtual void SetAwake(bool awake) = 0;
        virtual void SetActive(bool active) = 0;

        virtual void ApplyLinearForceToCenter(Vector3 impulse) = 0;
        virtual void ApplyLinearImpulseToCenter(Vector3 impulse) = 0;
        virtual void ApplyTorque(Vector3 torque) = 0;
    };
}
