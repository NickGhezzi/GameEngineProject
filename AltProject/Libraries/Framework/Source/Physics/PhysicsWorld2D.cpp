#include "FrameworkPCH.h"

#include "PhysicsWorld2D.h"
#include "box2d/box2d.h"
#include "Box2DDebugDraw.h"

namespace fw
{
    //----------------------------------------------------------------------------------------------------------------

    class RayCastResultCallback : public b2RayCastCallback
    {
    public:
        bool m_Hit;
        b2Body* m_pBody;
        RayCastResultCallback()
        {
            m_Hit = false;
            m_pBody = nullptr;
        }

        float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override
        {
            m_Hit = true;        
            m_pBody = fixture->GetBody(); 
            return fraction; 
        }
    };


    //----------------------------------------------------------------------------------------------------------------
    class Box2DContactListener : public b2ContactListener
    {
    protected:
        Framework* m_pFramework;

    public:
        Box2DContactListener(Framework* pFramework)
        : m_pFramework( pFramework )
        {
        }

        virtual void BeginContact(b2Contact* contact) override
        {
            uint16 catA = contact->GetFixtureA()->GetBody()->GetFixtureList()->GetFilterData().categoryBits;
            uint16 maskA = contact->GetFixtureA()->GetBody()->GetFixtureList()->GetFilterData().maskBits;
            uint16 catB = contact->GetFixtureB()->GetBody()->GetFixtureList()->GetFilterData().categoryBits;
            uint16 maskB = contact->GetFixtureB()->GetBody()->GetFixtureList()->GetFilterData().maskBits;

            if ((catA & maskB) != 0 && (catB & maskA) != 0)
            {
                void* pUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
                void* pUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

                b2WorldManifold worldManifold;
                contact->GetWorldManifold(&worldManifold);
                Vector3 position(worldManifold.points[0].x, worldManifold.points[0].y, 0);
                Vector3 normal(worldManifold.normal.x, worldManifold.normal.y, 0);

                CollisionEvent* pEvent = new CollisionEvent(pUserDataA, pUserDataB, position, normal);
                m_pFramework->GetEventManager()->AddEventToQueue(pEvent);
            }
          
        }
    };
    //----------------------------------------------------------------------------------------------------------------


    PhysicsWorld2D::PhysicsWorld2D(Framework* pFramework)
    : PhysicsWorld( pFramework )
    {
        m_pWorld = new b2World( b2Vec2( 0, -10 ) );
        m_pContactListener = new Box2DContactListener( pFramework );
        m_pRayCastCallback = new RayCastResultCallback();
        m_pWorld->SetContactListener( m_pContactListener );

        m_pShader = new ShaderProgram("Data/Shaders/Box2DDebug.vert", "Data/Shaders/Box2DDebug.frag");

        m_pDebugDraw = new Box2DDebugDraw(m_pShader, nullptr, nullptr);
        m_pWorld->SetDebugDraw(m_pDebugDraw);
    }

    PhysicsWorld2D::~PhysicsWorld2D()
    {
        delete m_pWorld;
        delete m_pContactListener;
        delete m_pDebugDraw;
        delete m_pShader;
        delete m_pRayCastCallback;
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

    void PhysicsWorld2D::Update(float deltaTime)
    {
        float timeStep = 1 / 60.0f;
        int velocityIterations = 8;
        int positionIterations = 3;

        m_pWorld->Step( timeStep, velocityIterations, positionIterations );
    }

    PhysicsBody* PhysicsWorld2D::CreateBody(Vector3 pos, Vector3 rot, bool isDynamic, void* pUserData)
    {
        b2BodyDef bodydef;
        bodydef.position = b2Vec2( pos.x, pos.y );
        bodydef.angle = -rot.z / 180.0f * PI;
        bodydef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
        bodydef.userData = pUserData;
    
        b2Body* pBody = m_pWorld->CreateBody( &bodydef );

        PhysicsBody* pPhysicsBody = new PhysicsBody2D( pBody );

        return pPhysicsBody;
    }

    void* PhysicsWorld2D::RayCast(Vector2 posa, Vector2 posb)
    {
        b2Vec2 pointA = b2Vec2(posa.x, posa.y);
        b2Vec2 pointB = b2Vec2(posb.x, posb.y);
        m_pWorld->RayCast(m_pRayCastCallback, pointA, pointB);
        if (m_pRayCastCallback->m_Hit == true)
        {
            return m_pRayCastCallback->m_pBody->GetUserData();
        }
        return nullptr;
    }


}
