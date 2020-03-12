#include "GamePCH.h"

#include "Game.h"
#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "../Scenes/BaseScene.h"

using namespace fw;

Player::Player(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position, int playerNum, PlayerController* pController)
: GameObject(m_pScene, pMesh, pMat, scale, rotation, position )
, m_PlayerNumber( playerNum )
, m_pController( pController )
{
    bLockToX = false;
    bPressed = false;
    m_Name = "Player";
}
    
Player::~Player()
{
    
}

void Player::Update(float deltaTime)
{
    GameObject::Update( deltaTime);

    float speed = 12;
    vec3 dir( 0, 0, 0 );

    if (m_pController->m_Up && bLockToX == false && bLockControlls == false)
    {
        dir.y = 1 * speed;
    }
    if (m_pController->m_Down && bLockToX == false && bLockControlls == false)
    {
        dir.y = -1 * speed;
    }
    if (m_pController->m_Left && bLockControlls == false)
    {
        dir.x = -1 * speed;
    }
    if (m_pController->m_Right && bLockControlls == false)
    {
        dir.x = 1 * speed;
    }
    
    if (m_pController->m_Action && !bPressed)
    {
        bPressed = true;
        bIsActionPressed = true;
    }
    else if (!m_pController->m_Action && bPressed)
    {
        bPressed = false;
    }

    m_pPhysicsBody->ApplyForce(dir);

}
