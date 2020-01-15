#include "GamePCH.h"

#include "Game.h"
#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "BaseScene.h"

using namespace fw;

Player::Player(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec2 position, int playerNum, PlayerController* pController)
: GameObject(m_pScene, pMesh, pMat, position )
, m_PlayerNumber( playerNum )
, m_pController( pController )
{
    //void CreateBody(Vector2 pos, float angle, bool isDynamic, void* pUserData);

    m_pPhysicsBody = m_pScene->GetGame()->GetPhysicsWorld()->CreateBody(position, 0, true, this);
   
}
    
Player::~Player()
{
    //delete m_pPhysicsBody;
}

void Player::Update(float deltaTime)
{
    //GameObject::Update( deltaTime, pFramework );

    float speed = 30;
    vec2 dir( 0, 0 );

    if( m_pController->m_Up )
        dir.y = 1;
    if( m_pController->m_Down )
        dir.y = -1;
    if( m_pController->m_Left )
        dir.x = -1;
    if( m_pController->m_Right )
        dir.x = 1;

    m_Position += dir * speed * deltaTime;
}
