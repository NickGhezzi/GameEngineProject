#pragma once

class b2World;

namespace fw
{
    class PhysicsWorld2D: public PhysicsWorld
    {
    protected:
        b2World* m_pWorld;
    public:
        PhysicsWorld2D();
        virtual ~PhysicsWorld2D();

        virtual void Update(float deltaTime) override;

        // Inherited via PhysicsWorld
        virtual PhysicsBody* CreateBody(Vector2 pos, float angle, bool isDynamic, void* pUserData) override;

    };
}