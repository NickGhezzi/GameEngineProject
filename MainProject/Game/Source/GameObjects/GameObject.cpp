#include "GamePCH.h"

#include "Base/Mesh.h"
#include "Base/Material.h"
#include "BaseScene.h"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"
#include "Game.h"

using namespace fw;

GameObject::GameObject(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 position)
: m_pScene(m_pScene)
, m_pMesh( pMesh )
, m_pMaterial(pMat)
, m_Position( position )
, m_Radius( 2 )
{
    
}

GameObject::~GameObject()
{
    delete m_pPhysicsBody;
}


void GameObject::CreateBody(bool isDynamic)
{
    m_pPhysicsBody = m_pScene->GetGame()->GetPhysicsWorld()->CreateBody(m_Position, 0, isDynamic, this);
}

void GameObject::AddCircle(float radius)
{
    m_pPhysicsBody->AddCircle(radius);
}

void GameObject::AddBox(vec3 size)
{
    m_pPhysicsBody->AddBox(size);
}

void GameObject::Update(float deltaTime)
{
    if(m_pPhysicsBody)
    m_Position = m_pPhysicsBody->GetPosition();
}

void GameObject::Draw(Camera* pCamera)
{
	if( m_pMesh != 0 )
        m_pMesh->Draw( pCamera, m_pMaterial, vec2(m_Position.x, m_Position.y) );
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