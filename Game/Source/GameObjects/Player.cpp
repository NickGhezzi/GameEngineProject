#include "GamePCH.h"

#include "Game.h"
#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"

using namespace fw;

Player::Player(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 position, int playerNum, PlayerController* pController)
: GameObject( pGame, pMesh, pShader, pTexture, position )
, m_PlayerNumber( playerNum )
, m_pController( pController )
{
}
    
Player::~Player()
{
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
