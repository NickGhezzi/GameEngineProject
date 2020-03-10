#include "GamePCH.h"

#include "BaseScene.h"
#include "Base/Mesh.h"
#include "Base/VertexFormat.h"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"
#include "Events/GameEvents.h"

BaseScene::BaseScene(Game* pGame)
: m_pGame( pGame )
, m_pPhysicsWorld( nullptr )
, m_pCamera( nullptr )
{
}

BaseScene::~BaseScene()
{
    delete m_pCamera;

    for( GameObject* object : m_Objects )
    {
        delete object;
    }

    delete m_pPhysicsWorld;
}

void BaseScene::Init()
{
}

void BaseScene::OnEvent(fw::Event* pEvent)
{
    if( pEvent->GetType() == "CollisionEvent" )
    {
        fw::CollisionEvent* pCollision = (fw::CollisionEvent*)pEvent;

        GameObject* pA = (GameObject*)pCollision->GetObjectA();
        GameObject* pB = (GameObject*)pCollision->GetObjectB();

        pA->OnCollision( pB, pCollision->GetPosition(), pCollision->GetNormal() );
        pB->OnCollision( pA, pCollision->GetPosition(), pCollision->GetNormal() * -1 );
    }

    if( pEvent->GetType() == "RemoveFromSceneEvent" )
    {
        RemoveFromSceneEvent* pRemoveFromSceneEvent = (RemoveFromSceneEvent*)pEvent;

        GameObject* pGameObject = pRemoveFromSceneEvent->GetGameObject();

        pGameObject->RemoveFromSceneAndReturnToPool();
    }
}

void BaseScene::Reset()
{
    for( int i=0; i<m_Objects.size(); i++ )
    {
        m_Objects[i]->Reset();
    }
}

void BaseScene::Update(float deltaTime)
{
    if(m_pPhysicsWorld)
    m_pPhysicsWorld->Update( deltaTime );

    for( GameObject* object : m_Objects )
    {
        object->Update( deltaTime );
    }

    m_pCamera->Update( deltaTime );
}

void BaseScene::Draw()
{
    for( GameObject* object : m_Objects )
    {
        object->Draw( m_pCamera );
    }
}

void BaseScene::AddObjectToScene(GameObject* pObj)
{
    assert( std::find( m_Objects.begin(), m_Objects.end(), pObj ) == m_Objects.end() ); // Object isn't already in list.

    m_Objects.push_back( pObj );
}

bool BaseScene::IsInScene(GameObject* pObj)
{
    if( std::find( m_Objects.begin(), m_Objects.end(), pObj ) != m_Objects.end() )
        return true;

    return false;
}

void BaseScene::RemoveObjectFromScene(GameObject* pObj)
{
    assert( std::find( m_Objects.begin(), m_Objects.end(), pObj ) != m_Objects.end() ); // Object is in list.

    // Remove object.
    auto it = std::find( m_Objects.begin(), m_Objects.end(), pObj );
    if( it != m_Objects.end() )
    {
        m_Objects.erase( it );
    }

    assert( std::find( m_Objects.begin(), m_Objects.end(), pObj ) == m_Objects.end() ); // Object isn't still in the list.
}
