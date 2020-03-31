#include "GamePCH.h"

#include "Base/Mesh.h"
#include "Base/ObjectPool.h"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"
#include "Scenes/BaseScene.h"

using namespace fw;

GameObject::GameObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture)
: m_pScene( pScene )
, m_Name( name )
, m_pMesh( pMesh )
, m_pShader( pShader )
, m_pTexture( pTexture )
, m_Position( pos )
, m_Rotation( rot )
, m_Scale( scale )
{
    m_InitialPosition = m_Position;
    m_InitialRotation = m_Rotation;
    m_InitialScale = m_Scale;

    m_pBody = nullptr;
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
        m_Rotation = m_pBody->GetRotation();
    }
}

void GameObject::Draw(Camera* pCamera, vec3 lightcolor)
{
    if( m_pMesh != nullptr )
    {
        mat4 worldMat;
        worldMat.CreateSRT( m_Scale, m_Rotation, m_Position );

        m_pMesh->Draw(pCamera, m_pShader, &worldMat, m_pTexture, lightcolor);
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

void GameObject::RemoveFromSceneAndReturnToPool()
{
    if( m_pScene->IsInScene( this ) )
    {
        // TODO_ICA1: Finish implementing this method.
        m_pPoolWeCameFrom->AddObjectToPool(this);
        Reset();
        m_pScene->RemoveObjectFromScene(this);
    }
}

void GameObject::CreateBody(bool isDynamic)
{
    m_pBody = m_pScene->GetPhysicsWorld()->CreateBody( m_Position, m_Rotation, isDynamic, this );
}

void GameObject::OnCollision(GameObject* pOtherGameObject, vec3 worldPosition, vec3 worldNormal)
{
}