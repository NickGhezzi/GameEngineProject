#include "FrameworkPCH.h"

#undef new

#include "PhysicsBody2D.h"
#include "btBulletDynamicsCommon.h"

namespace fw
{
    PhysicsBodyBullet::PhysicsBodyBullet(btDiscreteDynamicsWorld* pDynamicsWorld, btRigidBody* pBody): PhysicsBody()
    {
        m_pBody = pBody;
        m_pDynamicsWorld = pDynamicsWorld;
    }

    PhysicsBodyBullet::~PhysicsBodyBullet()
    {
        delete m_pBody->getMotionState();
        m_pDynamicsWorld->removeRigidBody(m_pBody);
        delete m_pBody;
    }

    void PhysicsBodyBullet::AddBox(Vector3 size, float density)
    {
        btCollisionShape* colshape = new btBoxShape(btVector3(size.x / 2, size.y / 2, size.z / 2));
        m_pBody->setCollisionShape(colshape);

        btVector3 localInertia(0, 0, 0);
        float mass = density;//???????????????????????
        colshape->calculateLocalInertia(mass, localInertia);

        m_pDynamicsWorld->removeRigidBody(m_pBody);
        m_pBody->setMassProps(mass, localInertia);
        m_pDynamicsWorld->addRigidBody(m_pBody);
    }

    void PhysicsBodyBullet::AddCircle(float radius, float density)
    {
        btCollisionShape* colshape = new btSphereShape(radius);
        m_pBody->setCollisionShape(colshape);

        btVector3 localInertia(0, 0, 0);
        float mass = density;//???????????????????????
        colshape->calculateLocalInertia(mass, localInertia);

        m_pDynamicsWorld->removeRigidBody(m_pBody);
        m_pBody->setMassProps(mass, localInertia);
        m_pDynamicsWorld->addRigidBody(m_pBody);
    }

    Vector3 PhysicsBodyBullet::GetPosition()
    {
       btTransform& transform = m_pBody->getWorldTransform();
       btVector3& pos = transform.getOrigin();
       return Vector3(pos.getX(), pos.getY(), pos.getZ());
    }

    Vector3 PhysicsBodyBullet::GetRotation()
    {
        return Vector3(0,0,0);
    }

    float PhysicsBodyBullet::GetMass()
    {
        return 0.0f;
    }

    void PhysicsBodyBullet::SetTransform(Vector3 pos, Vector3 rot)
    {
    }

    void PhysicsBodyBullet::SetLinearVelocity(Vector3 vel)
    {
    }

    void PhysicsBodyBullet::SetAngularVelocity(Vector3 vel)
    {

    }

    void PhysicsBodyBullet::SetAwake(bool awake)
    {
 
    }

    void PhysicsBodyBullet::SetActive(bool active)
    {
        m_pBody->activate(active);
    }

    void PhysicsBodyBullet::ApplyLinearForceToCenter(Vector3 impulse)
    {
        m_pBody->applyCentralForce(btVector3(impulse.x, impulse.y, impulse.z));
    }

    void PhysicsBodyBullet::ApplyLinearImpulseToCenter(Vector3 impulse)
    {
        m_pBody->applyCentralImpulse(btVector3(impulse.x, impulse.y, impulse.z));
    }

    void PhysicsBodyBullet::ApplyTorque(Vector3 torque)
    {

    }
}
