#pragma once

class PhysicsBody;

namespace fw
{
    class PhysicsWorld
    {
    public:
        virtual ~PhysicsWorld() {}

        virtual void Update(float deltaTime) = 0;

        virtual PhysicsBody* CreateBody(Vector3 pos, float angle, bool isDynamic, void* pUserData) = 0;
    };
}