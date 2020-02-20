#pragma once

namespace fw
{
    class Framework;
    class PhysicsBody;

    class PhysicsWorld
    {
    protected:
        Framework* m_pFramework;

    public:
        PhysicsWorld(Framework* pFramework) : m_pFramework( pFramework ) {}
        virtual ~PhysicsWorld() = 0 {}

        virtual void Update(float deltaTime) = 0;
        virtual PhysicsBody* CreateBody(Vector3 pos, Vector3 rot, bool isDynamic, void* pUserData) = 0;
    };
}
