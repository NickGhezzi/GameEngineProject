#include "FrameworkPCH.h"

#undef new

#include "PhysicsWorldBullet.h"
#include "btBulletDynamicsCommon.h"

namespace fw
{
    PhysicsWorldBullet::PhysicsWorldBullet(Framework* pFramework): PhysicsWorld(pFramework)
    {
        m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
        m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
        m_pOverlappingPairCache = new btDbvtBroadphase();
        m_pSolver = new btSequentialImpulseConstraintSolver;
        m_pDynamicsWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pOverlappingPairCache, m_pSolver, m_pCollisionConfiguration);
        m_pDynamicsWorld->setGravity(btVector3(0, -10, 0));

    }
    PhysicsWorldBullet::~PhysicsWorldBullet()
    {
        delete m_pDynamicsWorld;
        delete m_pSolver;
        delete m_pOverlappingPairCache;
        delete m_pDispatcher;
        delete m_pCollisionConfiguration;
    }
    void PhysicsWorldBullet::Update(float deltaTime)
    {
        m_pDynamicsWorld->stepSimulation(deltaTime, 10);
    }
    PhysicsBody* PhysicsWorldBullet::CreateBody(Vector3 pos, Vector3 rot, bool isDynamic, void* pUserData)
    {
        btTransform groundTransform;
        groundTransform.setIdentity();
        rot = rot / 180 * PI;
        groundTransform.setRotation(btQuaternion(rot.y , rot.x , rot.z));
        groundTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));

        btScalar mass(1.f);
        if (isDynamic == false)
            mass = 0.f;

        btVector3 localInertia(0, 0, 0);

        btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, nullptr);
        btRigidBody* body = new btRigidBody(rbInfo);

        m_pDynamicsWorld->addRigidBody(body);

        PhysicsBody* pPhysicsBody = new PhysicsBodyBullet(m_pDynamicsWorld, body);
        return pPhysicsBody;
    }
}
