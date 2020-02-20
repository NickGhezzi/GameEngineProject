#include "FrameworkPCH.h"

#include "PhysicsWorld2D.h"
#include "box2d/box2d.h"

namespace fw
{
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
            void* pUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
            void* pUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

            b2WorldManifold worldManifold;
            contact->GetWorldManifold( &worldManifold );
            Vector3 position( worldManifold.points[0].x, worldManifold.points[0].y, 0 );
            Vector3 normal( worldManifold.normal.x, worldManifold.normal.y, 0 );

            CollisionEvent* pEvent = new CollisionEvent( pUserDataA, pUserDataB, position, normal );
            m_pFramework->GetEventManager()->AddEventToQueue( pEvent );
        }
    };

    PhysicsWorld2D::PhysicsWorld2D(Framework* pFramework)
    : PhysicsWorld( pFramework )
    {
        m_pWorld = new b2World( b2Vec2( 0, -10 ) );
        m_pContactListener = new Box2DContactListener( pFramework );
        m_pWorld->SetContactListener( m_pContactListener );
    }

    PhysicsWorld2D::~PhysicsWorld2D()
    {
        delete m_pWorld;
        delete m_pContactListener;
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
}
