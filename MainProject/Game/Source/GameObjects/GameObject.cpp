#include "GamePCH.h"

#include "Base/Mesh.h"
#include "Base/Material.h"
#include "../Scenes/BaseScene.h"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"
#include "Game.h"

using namespace fw;

GameObject::GameObject(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position)
: m_pScene(m_pScene)
, m_pMesh( pMesh )
, m_pMaterial(pMat)
, m_Scale(scale)
, m_Rotation(rotation)
, m_Position( position )
, m_Radius( 2 )
{
    m_Name = "GameObject";
    bHasCollided = false;
    m_pPhysicsBody = nullptr;
}

GameObject::~GameObject()
{
    if (m_pPhysicsBody != nullptr)
    {
        delete m_pPhysicsBody;
    }
}

std::string GameObject::GetName()
{
    return m_Name;
}

void GameObject::CreateBody(bool isStatic)
{
    m_pPhysicsBody = m_pScene->GetPhysicsWorld()->CreateBody(m_Position, m_Rotation.z, isStatic, this);
}

fw::PhysicsBody* GameObject::GetBody()
{
    return m_pPhysicsBody;
}

void GameObject::AddCircle(float radius)
{
    m_pPhysicsBody->AddCircle(radius);
}

void GameObject::AddCircleWithFilter(float radius, uint16 categorybits, uint16 maskbits)
{
    m_pPhysicsBody->AddCircleWithFilter(radius, categorybits, maskbits);
}

void GameObject::AddBox(vec3 size, float density, bool isSensor, float friction, float restitution)
{
    m_pPhysicsBody->AddBox(size, density, isSensor, friction, restitution);
}

void GameObject::AddBoxWithFilter(vec3 size, float density, bool isSensor, float friction, float restitution, uint16 categorybits, uint16 maskbits)
{
    m_pPhysicsBody->AddBoxWithFilter(size, density, isSensor, friction, restitution, categorybits, maskbits);
}

void GameObject::AddJoint(GameObject* thingtoattach, vec2 pos)
{
    m_pPhysicsBody->AddJoint(thingtoattach->GetBody(), pos);
}

void GameObject::AddJointWithRestraint(GameObject* thingtoattach, vec2 pos, float minangle, float maxangle)
{
    m_pPhysicsBody->AddJointWithRestraint(thingtoattach->GetBody(), pos, minangle, maxangle);
}

void GameObject::AddJointWithMotor(GameObject* objectToAttach, vec2 anchorPos, float motorspeed, float maxtorque)
{
    m_pPhysicsBody->AddJointWithMotor(objectToAttach->GetBody(), anchorPos, motorspeed, maxtorque);
}

void GameObject::Update(float deltaTime)
{
    if(m_pPhysicsBody)
    m_Position = m_pPhysicsBody->GetPosition();
    m_Rotation.z = -m_pPhysicsBody->GetRotation();
}

void GameObject::Draw(Camera* pCamera)
{
	if( m_pMesh != 0 )
        m_pMesh->Draw( pCamera, m_pMaterial, m_Scale, m_Rotation, m_Position);
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

void GameObject::SetPoolWhereWeCameFrom(ObjectPool<GameObject*>* obj)
{
    m_pPoolWeCameFrom = obj;
}
