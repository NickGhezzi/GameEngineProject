#include "GamePCH.h"
#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position):
    GameObject(m_pScene, pMesh, pMat, scale, rotation, position)
{
    m_IsTouching = false;
    m_StartingPos = m_Position;
    m_Name = "MovingPlatform";
}

MovingPlatform::~MovingPlatform()
{
}

void MovingPlatform::SetIsTouching(bool istouching)
{
    m_IsTouching = istouching;
}

void MovingPlatform::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    float Distance = sqrt(((m_Position.x - m_StartingPos.x) * (m_Position.x - m_StartingPos.x)) + ((m_Position.y - m_StartingPos.y) * (m_Position.y - m_StartingPos.y)));

    if (m_IsTouching == true || abs(Distance) > 1.5)
    {
   
        SetPosition(vec3(sin(fw::GetSystemTimeSinceGameStart()) * 1.2, m_Position.y, 0));
      
    }
    else if(abs(Distance) < 1)
    {
        m_IsTouching = false;
        m_Position = m_StartingPos;
    }
}
