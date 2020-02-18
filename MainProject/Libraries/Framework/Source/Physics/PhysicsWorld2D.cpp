#include "FrameworkPCH.h"
#include "box2d/box2d.h"
#include "Box2DDebugDraw.h"
#include "../Events/CollisionEvent.h"

namespace fw
{

    class Box2DContactListener : public b2ContactListener
    {
    protected:
        Framework* m_pFramework;

    public:
        Box2DContactListener(Framework* pFramework)
        {
            m_pFramework = pFramework;
        }
        virtual void BeginContact(b2Contact* contact) override;
        virtual void EndContact(b2Contact* contact) override;
    };

    void Box2DContactListener::BeginContact(b2Contact* contact)
    {
        void* pUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
        void* pUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

        b2WorldManifold world;

        contact->GetWorldManifold(&world);

        Vector2 normal(world.normal.x, world.normal.y);

        CollisionEvent* pEvent = new CollisionEvent(CollisionEventType::OnHit, pUserDataA, pUserDataB, normal);
        m_pFramework->GetEventManager()->AddEventToQueue(pEvent);
    }

    void Box2DContactListener::EndContact(b2Contact* contact)
    {
        //contact->GetFixtureA()->GetBody()->GetUserData();
    }


    ///////////////////////////////////////////////////////////////////////


    PhysicsWorld2D::PhysicsWorld2D(Framework* pFramework)
    {
       m_pWorld = new b2World(b2Vec2(0, -9.8));
        //m_pWorld = new b2World(b2Vec2(0, 0));

        m_pShader = new ShaderProgram("Data/Shaders/Box2DDebug.vert", "Data/Shaders/Box2DDebug.frag");

        m_pContactListener = new Box2DContactListener(pFramework);
        m_pDebugDraw = new Box2DDebugDraw(m_pShader, nullptr, nullptr);

        m_pWorld->SetContactListener(m_pContactListener);
        m_pWorld->SetDebugDraw(m_pDebugDraw);
        m_UnusedTime = 0;

    }

    PhysicsWorld2D::~PhysicsWorld2D()
    {
        delete m_pWorld;
        delete m_pContactListener;
        delete m_pShader;
        delete m_pDebugDraw;
    }

    void PhysicsWorld2D::Update(float deltaTime)
    {
        m_UnusedTime += deltaTime;
        float timeStep = 1 / 60.0;  
        int velocityIterations = 8;  
        int positionIterations = 3;  
        while (m_UnusedTime > 1 / 60.0f)
        {
            m_pWorld->Step(timeStep, velocityIterations, positionIterations);
            m_UnusedTime -= 1 / 60.0f;
        }
    }

    void PhysicsWorld2D::DrawDebugData(mat4* view, mat4* proj)
    {
        m_pDebugDraw->SetViewProjMatrices(view, proj);
        m_pWorld->DrawDebugData();

        int32 flags = b2Draw::e_shapeBit; 
        flags |= b2Draw::e_jointBit; 
        flags |= b2Draw::e_centerOfMassBit; 
        flags |= b2Draw::e_aabbBit; 
        flags |= b2Draw::e_pairBit;

        m_pDebugDraw->SetFlags(flags);
    }

    PhysicsBody* PhysicsWorld2D::CreateBody(Vector3 pos, float angle, bool isStatic, void* pUserData)
    {
        b2BodyDef bodydef;
        bodydef.position = b2Vec2(pos.x, pos.y);
        bodydef.angle = angle;
        bodydef.type = isStatic ? b2_staticBody : b2_dynamicBody;
        bodydef.userData = pUserData;
        

        b2Body* pBody = m_pWorld->CreateBody(&bodydef);
        PhysicsBody* pPhysicsBody = new PhysicsBody2D(pBody);

        return pPhysicsBody;
    }

}