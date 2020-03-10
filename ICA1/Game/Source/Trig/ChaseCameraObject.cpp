#include "GamePCH.h"
#include "ChaseCameraObject.h"
#include "Scenes/BaseScene.h"
#include "Game.h"

ChaseCameraObject::ChaseCameraObject(BaseScene* pScene, vec3 pos)
: Camera( pScene, pos )
{
    m_ObjectFollowing = nullptr;
    m_Distance = 10;
    m_Angle = 90 * PI / 180;
}

ChaseCameraObject::~ChaseCameraObject()
{
}

void ChaseCameraObject::Update(float deltaTime)
{
    Camera::Update( deltaTime );

    vec3 otherPos = vec3(0,0,0);
    vec3 targetPos = vec3(0, 0, 0);
    
    if( m_ObjectFollowing )
        otherPos = m_ObjectFollowing->GetPosition();

    vec3 camDir = 0;
    if( m_pScene->GetGame()->GetFramework()->IsKeyDown( 'I' ) )
        camDir.y += 1;
    if( m_pScene->GetGame()->GetFramework()->IsKeyDown( 'J' ) )
        camDir.x -= 1;
    if( m_pScene->GetGame()->GetFramework()->IsKeyDown( 'K' ) )
        camDir.y -= 1;
    if( m_pScene->GetGame()->GetFramework()->IsKeyDown( 'L' ) )
        camDir.x += 1;

    m_Angle += camDir.x * 0.2f;

    vec3 dir = vec3(cosf(m_Angle), 0.0, sinf(m_Angle)) * m_Distance;

    targetPos += otherPos - dir;

    m_Position = targetPos;
    m_Position.y += 5;
    //m_Position.z -= m_Distance;
    m_ViewMat.CreateLookAtViewLeftHanded( m_Position, vec3(0,1,0), otherPos );
}
