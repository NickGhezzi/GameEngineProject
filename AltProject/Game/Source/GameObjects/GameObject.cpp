#include "GamePCH.h"

#include "Base/Mesh.h"
#include "Base/ObjectPool.h"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"
#include "Scenes/BaseScene.h"

using namespace fw;

GameObject::GameObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: m_pScene( pScene )
, m_Name( name )
, m_pMesh( pMesh )
, m_pMaterial( pMaterial )
, m_Position( pos )
, m_Rotation( rot )
, m_Scale( scale )
{
    m_InitialPosition = m_Position;
    m_InitialRotation = m_Rotation;
    m_InitialScale = m_Scale;

    m_pBody = nullptr;

    m_UVScale.Set( 1, 1 );
    m_UVOffset.Set( 0, 0 );

    m_pPoolWeCameFrom = nullptr;
}

GameObject::~GameObject()
{
    delete m_pBody;
}

void GameObject::Update(float deltaTime)
{
    if( m_pBody )
    {
        m_Position = m_pBody->GetPosition();
        m_Rotation.z = m_pBody->GetRotation().z;
    }
}

void GameObject::Draw(Camera* pCamera)
{
    if( m_pMesh != nullptr )
    {
        mat4 worldMatrix;
        worldMatrix.CreateSRT( m_Scale, m_Rotation, m_Position );

        m_pMesh->SetupAttributes( m_pMaterial );
        m_pMesh->SetupUniforms( m_pMaterial, &worldMatrix, pCamera, m_UVScale, m_UVOffset );
        m_pMesh->Draw( m_pMaterial );
    }
}

void GameObject::Reset()
{
    m_Position = m_InitialPosition;
    m_Rotation = m_InitialRotation;
    m_Scale = m_InitialScale;

    if( m_pBody )
    {
        m_pBody->SetLinearVelocity( 0 );
        m_pBody->SetAngularVelocity( 0 );
        m_pBody->SetTransform( m_InitialPosition, m_InitialRotation );
        m_pBody->SetAwake( true );
    }
}

void GameObject::SetUVScaleAndOffset(vec2 uvScale, vec2 uvOffset)
{
    m_UVScale = uvScale;
    m_UVOffset = uvOffset;
}

void GameObject::RemoveFromSceneAndReturnToPool()
{
    if( m_pScene->IsInScene( this ) )
    {
        if( m_pBody )
        {
            m_pBody->SetActive( false );
        }
        m_pScene->RemoveObjectFromScene( this );
        m_pPoolWeCameFrom->AddObjectToPool( this );
    }
}

void GameObject::CreateBody(bool isDynamic)
{
    m_pBody = m_pScene->GetPhysicsWorld()->CreateBody( m_Position, m_Rotation, isDynamic, this );
}

void GameObject::OnCollision(GameObject* pOtherGameObject, vec3 worldPosition, vec3 worldNormal)
{
}