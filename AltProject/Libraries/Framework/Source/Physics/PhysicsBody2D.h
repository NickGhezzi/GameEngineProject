#pragma once

#include "PhysicsBody.h"

class b2Body;
class b2PrismaticJoint;

namespace fw
{
    class PhysicsBody2D : public PhysicsBody
    {
    protected:
        b2Body* m_pBody;
        b2PrismaticJoint* m_Joint;

    public:
        PhysicsBody2D(b2Body* pBody);
        virtual ~PhysicsBody2D();

        virtual void AddBox(Vector3 size, float density) override;
        virtual void AddBox(Vector3 size, float density, bool isSensor) override;
        virtual void AddBox(Vector3 size, float density, bool isSensor, int numMaskBits, uint16 categorybits, uint16* maskbits[]) override;
        virtual void AddCircle(float radius, float density) override;
        virtual void AddCircle(float radius, float density, int numMaskBits, uint16 categorybits, uint16* maskbits[]) override;
        virtual void AddChain(Vector2* points, int numPoints, float density) override;
        virtual void AddPrismaticJoint(PhysicsBody* objectToAttach, float upperTranslation, float LowerTranslation, float maxMotorForce, float motorSpeed) override;

        virtual Vector3 GetPosition() override;
        virtual Vector3 GetRotation() override;
        virtual float GetMass() override;
        virtual Vector2 GetLinearVelocity() override;
        virtual b2Body* GetBody() override;

        virtual void SetTransform(Vector3 pos, Vector3 rot) override;
        virtual void SetLinearVelocity(Vector3 vel) override;
        virtual void SetAngularVelocity(Vector3 vel) override;
        virtual void SetAwake(bool awake) override;
        virtual void SetActive(bool active) override;
        virtual void SetFixedRotation(bool isFixed) override;
        virtual void EnableMotor(bool isEnabled) override;

        virtual void ApplyLinearForceToCenter(Vector3 impulse) override;
        virtual void ApplyLinearImpulseToCenter(Vector3 impulse) override;
        virtual void ApplyTorque(Vector3 torque) override;

    };
}
