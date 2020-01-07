#include "GamePCH.h"

#include "Base/Mesh.h"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"

using namespace fw;

GameObject::GameObject(Game* pGame, Mesh* pMesh, ShaderProgram* pShader, fw::Texture* pTexture, vec2 position)
: m_pGame( pGame )
, m_pMesh( pMesh )
, m_pShader( pShader )
, m_pTexture( pTexture )
, m_Position( position )
, m_Radius( 2 )
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw(Camera* pCamera)
{
	if( m_pMesh != 0 )
        m_pMesh->Draw( pCamera, m_pShader, m_Position, m_pTexture );
}

bool GameObject::IsColliding(GameObject* pOtherGameObject)
{
    float radii = m_Radius + pOtherGameObject->m_Radius;
    if( (m_Position - pOtherGameObject->m_Position).Length() < radii )
        return true;

    return false;
}

void GameObject::OnCollision(GameObject* pOtherGameObject)
{
}