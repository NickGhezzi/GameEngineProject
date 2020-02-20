#include "GamePCH.h"

#include "SheepObject.h"
#include "SheepTitleCard.h"
#include "ICA1Scene.h"
#include "Scenes/BaseScene.h"
#include "GameObjects/PlayerController.h"

SheepObject::SheepObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pShader, pTexture)
{
    m_pController = nullptr;

    m_IsDead = false;

}

SheepObject::~SheepObject()
{
}

void SheepObject::Reset()
{
    GameObject::Reset();

    m_IsDead = false;
}

void SheepObject::SetController(PlayerController* pController)
{
    m_pController = pController;
}

void SheepObject::Update(float deltaTime)
{
    GameObject::Update(deltaTime);


    if (m_pController == 0)
        return;

    if (m_IsDead == true)
    {
        m_pBody->SetTransform(vec3(10000, 0, 0), 0);
        ((ICA1Scene*)m_pScene)->GetLose()->Display();
        return;
    }

    if (m_Position.y < -5)
    {
        ((ICA1Scene*)m_pScene)->GetWin()->Display();
    }

    // TODO_ICA1: Make the SheepObject make small jumps to the left or right based on input from the player controller object.
    if (m_IsDead == false)
    {
        if (m_pController->IsRightHeld() && m_CanJump == true)
        {
            m_pBody->ApplyLinearImpulseToCenter(vec3(0.7, 3, 0));
            m_CanJump = false;
        }
        if (m_pController->IsLeftHeld() && m_CanJump == true)
        {
            m_pBody->ApplyLinearImpulseToCenter(vec3(-0.7, 3, 0));
            m_CanJump = false;
        }
    }

}

void SheepObject::Die()
{
    // TODO_ICA1: Hide the sheep, disable input and call a scene method to spawn a bunch of meat chunks.
    m_IsDead = true;
    static_cast<ICA1Scene*>(m_pScene)->SpawnMeatChunks(m_Position, 20);
}

void SheepObject::OnCollision(GameObject* pOtherGameObject, vec3 worldPosition, vec3 worldNormal)
{
    GameObject::OnCollision(pOtherGameObject, worldPosition, worldNormal);

    // TODO_ICA1: Based on the normal of the collision, allow the sheep to jump.
    //            Use only the normal to detect the ground.

    if (worldNormal.y < 0)
    {
        m_CanJump = true;
    }

    // TODO_ICA1: If hit by a meteor, call die().
    if (pOtherGameObject->GetName() == "Meteor")
    {
        Die();
    }

}
