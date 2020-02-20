#include "GamePCH.h"

#include "Game.h"
#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"

using namespace fw;

Player::Player(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture)
: GameObject( pScene, name, pos, rot, scale, pMesh, pShader, pTexture )
, m_pController( nullptr )
{
}
    
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

    float speed = 30;
    vec2 dir( 0, 0 );

    if( m_pController->IsUpHeld() )
        dir.y = 1;
    if( m_pController->IsDownHeld() )
        dir.y = -1;
    if( m_pController->IsLeftHeld() )
        dir.x = -1;
    if( m_pController->IsRightHeld() )
        dir.x = 1;

    m_Position += dir * speed * deltaTime;

    //ImGui::Text( "%f", m_pBody->GetPosition().y );
}
