#include "GamePCH.h"

#include "BarrelObject.h"
#include "Events/GameEvents.h"
#include "Scenes/BaseScene.h"
#include "Game.h"

BarrelObject::BarrelObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: GameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
    m_pPool = nullptr;
    m_JumpedOver = false;
}

BarrelObject::~BarrelObject()
{
}

void BarrelObject::Reset()
{
    Destroy();
}

void BarrelObject::RemoveFromSceneAndReturnToPool()
{
    GameObject::RemoveFromSceneAndReturnToPool();

    fw::PhysicsBody* pBody = GetBody();
   // pBody->SetActive( false );
    pBody->SetLinearVelocity( vec2(0,0) );
    pBody->SetTransform( vec2(-10000,-10000), 0 );
    m_Position = vec2(-10000, -10000);
 /*   if( m_pPool )
    {
        m_pPool->AddObjectToPool( this );
    }*/
}

void BarrelObject::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

    if( m_pBody == nullptr )
        return;

    if( m_Position.x > 6.5f )
    {
        m_pBody->ApplyLinearForceToCenter( vec2( -20, 0 ) );
        m_pBody->SetAngularVelocity( 0 );
    }

    if( m_Position.x < -6.5f && m_Position.y < -6.5f )
    {
        Destroy();
        return;
    }

    if( m_Position.x < -6.5f )
    {
        m_pBody->ApplyLinearForceToCenter( vec2( 20, 0 ) );
        m_pBody->SetAngularVelocity( 0 );
    }
}

void BarrelObject::Destroy()
{
    assert( m_pScene != nullptr );
    m_JumpedOver = false;
    RemoveFromSceneEvent* pEvent = new RemoveFromSceneEvent( this );
    m_pScene->GetGame()->GetFramework()->GetEventManager()->AddEventToQueue( pEvent );
}
