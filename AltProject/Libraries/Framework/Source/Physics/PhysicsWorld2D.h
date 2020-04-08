#pragma once

#include "PhysicsWorld.h"

class b2World;

namespace fw
{
    class PhysicsBody;
    class PhysicsBody2D;
    class Box2DDebugDraw;
    class Box2DContactListener;
    class RayCastResultCallback;

    class PhysicsWorld2D : public PhysicsWorld
    {
    protected:
        b2World* m_pWorld;
        Box2DContactListener* m_pContactListener;

        RayCastResultCallback* m_pRayCastCallback;

        Box2DDebugDraw* m_pDebugDraw;

        ShaderProgram* m_pShader;

    public:
        PhysicsWorld2D(Framework* pFramework);
        virtual ~PhysicsWorld2D();

        void DrawDebugData(mat4* view, mat4* proj);

        virtual void Update(float deltaTime) override;
        virtual PhysicsBody* CreateBody(Vector3 pos, Vector3 rot, bool isDynamic, void* pUserData) override;
        virtual void* RayCast(Vector2 posa, Vector2 posb) override;
    };
}
