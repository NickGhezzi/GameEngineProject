#include "GamePCH.h"

#include "FollowCameraObject.h"

FollowCameraObject::FollowCameraObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale)
: Camera( pScene, pos )
{
    m_ClosestZ = -10;
    m_ObjectFollowing = nullptr;
}

FollowCameraObject::~FollowCameraObject()
{
}

void FollowCameraObject::Update(float deltaTime)
{
    Camera::Update( deltaTime );

    if( m_ObjectFollowing == nullptr )
    {
        m_ViewMatrix.CreateSRT( m_Scale, m_Rotation, m_Position );
        m_ViewMatrix.Inverse();
    }
    else if( m_ObjectFollowing->GetBody() )
    {
        fw::PhysicsBody* pOtherBody = m_ObjectFollowing->GetBody();
        if( pOtherBody )
        {
            //vec2 velocity = pOtherBody->SetLinearVelocity();
            //float speed = fabs( velocity.x );

            //float zDest = m_ClosestZ - speed;

            //m_Position.z += ( zDest - m_Position.z ) * 4.0f * deltaTime;
        }

        vec3 otherPos = m_ObjectFollowing->GetPosition();
        m_Position.x += ( otherPos.x - m_Position.x ) * 4.0f * deltaTime;
        m_Position.y = otherPos.y + 5.0f;
        otherPos.y += 1.0f;
        m_ViewMatrix.CreateLookAtView( m_Position, vec3(0,1,0), otherPos );
    }
    else
    {
        vec3 otherPos = m_ObjectFollowing->GetPosition();
        m_Position.x += ( otherPos.x - m_Position.x ) * 4.0f * deltaTime;
        m_Position.y = 3;//otherPos.y;
        m_Position.z = otherPos.z + m_ClosestZ;
        m_ViewMatrix.CreateLookAtView( m_Position, vec3(0,1,0), otherPos );
    }
}
