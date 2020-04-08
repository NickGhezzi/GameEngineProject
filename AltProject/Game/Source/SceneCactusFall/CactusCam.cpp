#include "GamePCH.h"

#include "CactusCam.h"
#include "Scenes/BaseScene.h"
#include "GameObjects/GameObject.h"

CactusCam::CactusCam(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale)
: Camera( pScene, pos )
{
    m_Offset = vec3( 0, 15, 0 );
}

CactusCam::~CactusCam()
{
}

void CactusCam::Reset()
{
    m_Position = m_pObjectFollowing->GetPosition() + m_Offset;
}

void CactusCam::Update(float deltaTime)
{
    Camera::Update( deltaTime );

    if( m_pObjectFollowing )
    {
        vec3 otherObjectPos = m_pObjectFollowing->GetPosition();
        vec3 targetPos = otherObjectPos + m_Offset;

        m_Position = targetPos;
        vec3 camLookAtPos = m_pObjectFollowing->GetPosition();

        //float turbulanceScale = (m_LastPosition.y - m_Position.y) * 1.0f;
        //camLookAtPos.x += (rand()%1000 - 500) / 2400.0f * turbulanceScale;
        //camLookAtPos.z += (rand()%1000 - 500) / 2400.0f * turbulanceScale;

        m_ViewMatrix.CreateLookAtView( m_Position, vec3(0,0,1), camLookAtPos );
    }
    else
    {
        m_ViewMatrix.SetIdentity();
    }

    m_LastPosition = m_Position;
}

void CactusCam::SetObjectToFollow(GameObject* pObject)
{
    m_pObjectFollowing = pObject;

    m_Position = m_pObjectFollowing->GetPosition() + m_Offset;
}
