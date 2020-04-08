#include "GamePCH.h"

#include "MarioObject.h"

#include "BarrelObject.h"
#include "ElevatorObject.h"

#include "Game.h"
#include "Base/ResourceManager.h"
#include "Scenes/BaseScene.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"

MarioObject::MarioObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, ResourceManager* pResourceManager)
    : Player(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_InitialPosition = pos;
    m_InitialRotation = rot;
    m_pResourceManager = pResourceManager;
    m_Dead = false;
    m_CanJump = true;
    m_IsRight = false;
    m_Switched = false;
    m_IsInvincible = false;
    m_InvincibleTimeLeft = 0;
    m_WalkTimer = 0.2;
    m_Score = 0;
    m_HasWon = false;
}

MarioObject::~MarioObject()
{
}

void MarioObject::Reset()
{
    m_Dead = false;
    m_HasWon = false;
    m_InvincibleTimeLeft = 0;
    m_pMaterial->m_pTexture = m_pResourceManager->GetTexture("MarioStanding");
    m_Score = 0;
    SetDead(false);
    GameObject::Reset();
}

void MarioObject::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    if (m_pBody == nullptr)
        return;

    if (m_pController == nullptr)
        return;



    if (m_Dead == false)
    {
        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('I'))
        {
            m_InvincibleTimeLeft = 100.0f;
        }

        // Left/Right.
        {
            float speed = 2.0f;

            vec2 targetVelocity(0, 0);

            if (m_pController->IsLeftHeld())
            {
                targetVelocity.x = -speed;
                m_IsWalking = true;
                m_IsRight = false;
            }
            if (m_pController->IsRightHeld())
            {
                targetVelocity.x = speed;
                m_IsWalking = true;
                m_IsRight = true;
            }

            // TODO_DonkeyKong: Make mario run left/right at the targetVelocity, see the slides for this.
            if (abs(GetBody()->GetLinearVelocity().x) < speed)
            {
                GetBody()->ApplyLinearForceToCenter(targetVelocity);
            }

            if (targetVelocity.x == 0 && m_IsInvincible == false)
            {
                m_IsWalking = false;
                m_pMaterial->m_pTexture = m_pResourceManager->GetTexture("MarioStanding");
            }
        }

        // Jumping.
        if (m_pController->WasActionPressed() && m_CanJump == true)
        {
            // TODO_DonkeyKong: Make mario jump when "up" is pressed.
            //        Mario should only jump once before hitting the ground.
            //        Mario can jump off a wall only once.
            //        Most of the code doesn't go here.
            m_pBody->ApplyLinearImpulseToCenter(vec3(0, 3, 0));
            m_CanJump = false;
        }
    }



    if (m_InvincibleTimeLeft > 0)
    {
        m_InvincibleTimeLeft -= deltaTime;
    }
    else
    {
        m_IsInvincible = false;
    }

    if (m_IsInvincible == true)
    {
        m_pMaterial->m_pTexture = m_pResourceManager->GetTexture("Hammer");
    }

    // TODO_DonkeyKong: Change textures for the following states: Invincible, Standing, Running, Dead.
    //        Running has 2 frames.
    //        For Invincibility, just show the hammer sprite.

    if (m_Dead == false)
    {
        if (m_IsWalking == true && m_IsInvincible == false)
        {
            m_WalkTimer -= deltaTime;
            if (m_WalkTimer <= 0)
            {
                if (m_pMaterial->m_pTexture == m_pResourceManager->GetTexture("MarioRunning1"))
                {
                    m_pMaterial->m_pTexture = m_pResourceManager->GetTexture("MarioRunning2");
                }
                else
                {
                    m_pMaterial->m_pTexture = m_pResourceManager->GetTexture("MarioRunning1");
                }
                m_WalkTimer = 0.5;
            }
        }
    }
    else
    {
        m_pMaterial->m_pTexture = m_pResourceManager->GetTexture("MarioDead");
    }


    // TODO_DonkeyKong: The sprite should also face the correct direction, you're not allowed to make new PNGs.
    if (m_IsRight && !m_Switched)
    {
        m_UVScale.x *= -1;
        m_Switched = true;
    }
    else if (!m_IsRight && m_Switched)
    {
        m_UVScale.x *= -1;
        m_Switched = false;
    }

    // TODO_DonkeyKong: Raycast to see if Mario jumped over a barrel, if so, increment the score by 1.
    //        Only give the point if the player actually jumps over the barrel, not if he gets hit by it.
    //        Make sure the same Barrel doesn't count multiple times.
    //        Display the score in an imgui window called "Debug Score".
    //        Display the score using meshes, you can use the same system as in Cactus Fall.
    if (m_CanJump == false)
    {

        GameObject* obj = static_cast<GameObject*>(m_pScene->GetPhysicsWorld()->RayCast(vec2(m_Position.x, m_Position.y), vec2(m_Position.x, m_Position.y - 5)));
        if (obj)
        {
            if (obj->GetName() == "Barrel")
            {
                BarrelObject* obj1 = static_cast<BarrelObject*>(obj);
                if (obj1->m_JumpedOver == false)
                {
                    obj1->m_JumpedOver = true;
                    m_Score++;
                }
            }
        }
    }

}

void MarioObject::OnCollision(GameObject* pOtherGameObject, vec3 worldPosition, vec3 worldNormal)
{
    GameObject::OnCollision(pOtherGameObject, worldPosition, worldNormal);

    if (worldNormal.y < 0)
    {
        m_CanJump = true;
    }

    if (pOtherGameObject)
    {
        if (pOtherGameObject->GetName() == "Barrel")
        {
            BarrelObject* obj = static_cast<BarrelObject*>(pOtherGameObject);
            if (m_IsInvincible == true)
            {
                obj->Destroy();
            }
            else
            {
                SetDead(true);
            }
        }
        if (pOtherGameObject->GetName() == "Hammer1")
        {
            m_InvincibleTimeLeft = 5.0f;
            m_IsInvincible = true;
            //m_pScene->RemoveObjectFromScene(pOtherGameObject);
        }

        if (pOtherGameObject->GetName() == "ElevatorSensor")
        {
            m_HasWon = true;
        }
    }
    // TODO_DonkeyKong: Check for collision with Hammer and make the player invincible for 5 seconds.
    //        Tint the player a different color when he's invincible.
}

void MarioObject::SetDead(bool dead)
{
    // TODO_DonkeyKong: Make the player collide with barrels if alive, make barrels pass through player if dead.
    //        Make sure this is called when the player gets hit by a barrel.
    if (dead)
    {
        m_Dead = dead;
        m_pBody->SetActive(false);
    }
    if (!dead)
    {
        m_pBody->SetActive(true);
    }
}

int MarioObject::GetScore()
{
    return m_Score;
}

bool MarioObject::GetHasWon()
{
    return m_HasWon;
}
