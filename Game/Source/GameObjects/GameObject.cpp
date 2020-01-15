#include "GamePCH.h"

#include "Base/Mesh.h"
#include "Base/Material.h"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"

using namespace fw;

GameObject::GameObject(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec2 position)
: m_pScene(m_pScene)
, m_pMesh( pMesh )
, m_pMaterial(pMat)
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
        m_pMesh->Draw( pCamera, m_pMaterial, m_Position );
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