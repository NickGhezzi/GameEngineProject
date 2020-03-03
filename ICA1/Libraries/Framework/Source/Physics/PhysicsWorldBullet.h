#pragma once

#include "PhysicsWorld.h"

class b2World;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btDiscreteDynamicsWorld;
class btSequentialImpulseConstraintSolver;

namespace fw
{

    class PhysicsWorldBullet : public PhysicsWorld
    {
    protected:

        btDefaultCollisionConfiguration* m_pCollisionConfiguration;
        btCollisionDispatcher* m_pDispatcher;
        btBroadphaseInterface* m_pOverlappingPairCache;
        btSequentialImpulseConstraintSolver* m_pSolver;
        btDiscreteDynamicsWorld* m_pDynamicsWorld;

    public:
        PhysicsWorldBullet(Framework* pFramework);
        virtual ~PhysicsWorldBullet();

        virtual void Update(float deltaTime) override;
        virtual PhysicsBody* CreateBody(Vector3 pos, Vector3 rot, bool isDynamic, void* pUserData) override;
    };
}
