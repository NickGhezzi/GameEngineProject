#pragma once
class b2Body;
namespace fw
{
    class PhysicsBody
    {
    public:
        virtual ~PhysicsBody() = 0 {}

        virtual void AddBox(Vector3 size, float density) = 0;
        virtual void AddBox(Vector3 size, float density, bool isSensor) = 0;
        virtual void AddBox(Vector3 size, float density, bool isSensor, int numMaskBits, uint16 categorybits, uint16* maskbits[]) = 0;
        virtual void AddCircle(float radius, float density) = 0;
        virtual void AddCircle(float radius, float density, int numMaskBits,uint16 categorybits, uint16* maskbits[]) = 0;
        virtual void AddChain(Vector2* points, int numPoints, float density) = 0;
        virtual void AddPrismaticJoint(PhysicsBody* objectToAttach, float upperTranslation, float LowerTranslation, float maxMotorForce, float motorSpeed) = 0;

        virtual Vector3 GetPosition() = 0;
        virtual Vector3 GetRotation() = 0;
        virtual float GetMass() = 0;
        virtual Vector2 GetLinearVelocity() = 0;
        virtual b2Body* GetBody() = 0;

        
        virtual void SetTransform(Vector3 pos, Vector3 rot) = 0;
        virtual void SetLinearVelocity(Vector3 vel) = 0;
        virtual void SetAngularVelocity(Vector3 vel) = 0;
        virtual void SetAwake(bool awake) = 0;
        virtual void SetActive(bool active) = 0;
        virtual void SetFixedRotation(bool isFixed) = 0;
        virtual void EnableMotor(bool isEnabled) = 0;

        virtual void ApplyLinearForceToCenter(Vector3 impulse) = 0;
        virtual void ApplyLinearImpulseToCenter(Vector3 impulse) = 0;
        virtual void ApplyTorque(Vector3 torque) = 0;

    };
}
