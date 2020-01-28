#pragma once

class b2World;

namespace fw
{
    class Box2DContactListener;

    class PhysicsWorld2D: public PhysicsWorld
    {
    protected:
        b2World* m_pWorld;
        Box2DContactListener* m_pContactListener;
    public:
        PhysicsWorld2D();
        virtual ~PhysicsWorld2D();

        virtual void Update(float deltaTime) override;

        // Inherited via PhysicsWorld
        virtual PhysicsBody* CreateBody(Vector3 pos, float angle, bool isDynamic, void* pUserData) override;

    };
}