#pragma once

class b2World;

namespace fw
{
    class Box2DContactListener;
    class Box2DDebugDraw;
    class Framework;

    class PhysicsWorld2D: public PhysicsWorld
    {
    protected:
        b2World* m_pWorld;
        Box2DContactListener* m_pContactListener;
        Box2DDebugDraw* m_pDebugDraw;

        ShaderProgram* m_pShader;
        float m_UnusedTime;
    public:
        PhysicsWorld2D(Framework* pFramework);
        virtual ~PhysicsWorld2D();

        virtual void Update(float deltaTime) override;
        void DrawDebugData(mat4* view, mat4* proj);

        // Inherited via PhysicsWorld
        virtual PhysicsBody* CreateBody(Vector3 pos, float angle, bool isDynamic, void* pUserData) override;
        

    };
}