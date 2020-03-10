#include "GamePCH.h"
#include "TrigPlayer.h"
#include "TrigScene.h"
#include "GameObjects/PlayerController.h"
#include "Scenes/BaseScene.h"

TrigPlayer::TrigPlayer(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture)
: GameObject( pScene, name, pos, rot, scale, pMesh, pShader, pTexture )
{
    m_pController = nullptr;
}

TrigPlayer::~TrigPlayer()
{
}

void TrigPlayer::SetController(PlayerController* pController)
{
    m_pController = pController;
}

void TrigPlayer::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

    std::vector<TrigPickup*> pickups = ((TrigScene*)m_pScene)->GetPickups();
    for( int i=0; i<pickups.size(); i++ )
    {
        TrigPickup* pPickup = pickups[i];
    }

    float speed = 5;
    vec3 dir( 0, 0, 0 );

    if( m_pController->IsUpHeld() )
        dir.z = 1;
    if( m_pController->IsDownHeld() )
        dir.z = -1;
    if( m_pController->IsLeftHeld() )
        dir.x = -1;
    if( m_pController->IsRightHeld() )
        dir.x = 1;

    m_Position += dir * speed * deltaTime;
}
