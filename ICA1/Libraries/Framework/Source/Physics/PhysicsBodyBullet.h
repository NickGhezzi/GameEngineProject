#pragma once

#include "PhysicsBody.h"

class btRigidBody;
class btDiscreteDynamicsWorld;

namespace fw
{
    class PhysicsBodyBullet : public PhysicsBody
    {
    protected:
        btRigidBody* m_pBody;
        btDiscreteDynamicsWorld* m_pDynamicsWorld;

    public:
        PhysicsBodyBullet(btDiscreteDynamicsWorld* pDynamicsWorld, btRigidBody* pBody);
        virtual ~PhysicsBodyBullet();

        virtual void AddBox(Vector3 size, float density) override;
        virtual void AddCircle(float radius, float density) override;

        virtual Vector3 GetPosition() override;
        virtual Vector3 GetRotation() override;
        virtual float GetMass() override;

        virtual void SetTransform(Vector3 pos, Vector3 rot) override;
        virtual void SetLinearVelocity(Vector3 vel) override;
        virtual void SetAngularVelocity(Vector3 vel) override;
        virtual void SetAwake(bool awake) override;
        virtual void SetActive(bool active) override;

        virtual void ApplyLinearForceToCenter(Vector3 impulse) override;
        virtual void ApplyLinearImpulseToCenter(Vector3 impulse) override;
        virtual void ApplyTorque(Vector3 torque) override;
    };
}
