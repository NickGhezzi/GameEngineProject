#include "GamePCH.h"
#include "Peg.h"
#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/PlayerController.h"
#include "../Scenes/BaseScene.h"

Peg::Peg(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position, PlayerController* pController)
    : GameObject(m_pScene, pMesh, pMat, scale, rotation, position)
    , m_pController(pController)
{
    m_AngleMin = m_Rotation.z + 90.0f;
    m_AngleMax = m_Rotation.z;
    m_bHasbeenpressed = false;
}

Peg::~Peg()
{
}

void Peg::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    float speed = 10000;

    if (m_pController->m_Action)
    {
        m_bIsActionPressed = true;
        m_bHasbeenpressed = true;
    }
    else 
    {
        m_bIsActionPressed = false;
    }

    if (m_bIsActionPressed == false)
    {
        //if (GetRotation())
        //{
        //    m_pPhysicsBody->ApplyTorque(-speed);
        //}
        //else
        //{
        //    SetRotation(m_AngleMax);
        //}
      m_pPhysicsBody->ApplyTorque(-speed);
    }
    else if (m_bIsActionPressed == true)
    {
        //if (GetRotation() >= m_AngleMin)
        //{
        //    m_pPhysicsBody->ApplyTorque(speed);
        //}
  /*      else if (GetRotation() < m_AngleMin)
        {
            SetRotation(m_AngleMin);
        }*/
       m_pPhysicsBody->ApplyTorque(speed);
    }
    //float rot = m_pPhysicsBody->GetRotation();
    //fw::Clamp(rot, m_AngleMin, m_AngleMax);
    //SetRotation(rot);
    //m_pPhysicsBody->ApplyForce(dir);
}
