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

}
    
Player::~Player()
{
    
}

void Player::Update(float deltaTime)
{
    GameObject::Update( deltaTime);

    float speed = 12;
    vec3 dir( 0, 0, 0 );

    if( m_pController->m_Up )
        dir.y = 1 * speed;
    if( m_pController->m_Down )
        dir.y = -1 * speed;
    if( m_pController->m_Left )
        dir.x = -1 * speed;
    if( m_pController->m_Right )
        dir.x = 1 * speed;

    m_pPhysicsBody->ApplyForce(dir);
    //m_Position += dir * speed * deltaTime;

    //ImGui::Text("%f", m_pPhysicsBody->GetPosition().y);
}