#include "FrameworkPCH.h"
#include "box2d/box2d.h"
#include "Box2DDebugDraw.h"


namespace fw
{

    class Box2DContactListener : public b2ContactListener
    {
    public:
        virtual void BeginContact(b2Contact* contact) override;
        virtual void EndContact(b2Contact* contact) override;
    };

    void Box2DContactListener::BeginContact(b2Contact* contact)
    {
        //contact->GetFixtureA()->GetBody()->GetUserData();
    }

    void Box2DContactListener::EndContact(b2Contact* contact)
    {
        //contact->GetFixtureA()->GetBody()->GetUserData();
    }

    PhysicsWorld2D::PhysicsWorld2D()
    {
       // m_pWorld = new b2World(b2Vec2(0, -9.8));
        m_pWorld = new b2World(b2Vec2(0, 0));

        m_pShader = new ShaderProgram("Data/Shaders/Box2DDebug.vert", "Data/Shaders/Box2DDebug.frag");

        m_pContactListener = new Box2DContactListener();
        m_pDebugDraw = new Box2DDebugDraw(m_pShader, nullptr, nullptr);

        m_pWorld->SetContactListener(m_pContactListener);
        m_pWorld->SetDebugDraw(m_pDebugDraw);
        m_pContactListener->BeginContact(nullptr);
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
        float timeStep = 1 / 60.0;  
        int velocityIterations = 8;  
        int positionIterations = 3;  

        m_pWorld->Step(timeStep, velocityIterations, positionIterations);
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

    PhysicsBody* PhysicsWorld2D::CreateBody(Vector3 pos, float angle, bool isDynamic, void* pUserData)
    {
        b2BodyDef bodydef;
        bodydef.position = b2Vec2(pos.x, pos.y);
        bodydef.angle = angle;
        bodydef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
        bodydef.userData = pUserData;
        

        b2Body* pBody = m_pWorld->CreateBody(&bodydef);
        PhysicsBody* pPhysicsBody = new PhysicsBody2D(pBody);

        return pPhysicsBody;
    }
}