#include "GamePCH.h"

#include "GameObjectTargetBonus.h"

#include "SceneCactusFall.h"
#include "Game.h"
#include "Scenes/BaseScene.h"

GameObjectTargetBonus::GameObjectTargetBonus(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: GameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
}

GameObjectTargetBonus::~GameObjectTargetBonus()
{
}

void GameObjectTargetBonus::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

    float time = (float)fw::GetSystemTimeSinceGameStart();

    float speed = 90;

    if (m_Rotation.y >= 360 || m_Rotation.y <= -360)
    {
        m_Rotation.y = 0.0f;
    }

    GameObject* pPlayer = m_pScene->GetGameObjectByName( "Player" );
    if( pPlayer )
    {
        if( pPlayer->GetPosition().y == 0 )
            speed = 0;
    }

    if( static_cast<SceneCactusFall*>( m_pScene )->IsInTestMode() && m_pScene->GetGame()->GetFramework()->IsKeyDown( 'Q' ) )
        speed = 90;
    if( static_cast<SceneCactusFall*>( m_pScene )->IsInTestMode() && m_pScene->GetGame()->GetFramework()->IsKeyDown( 'E' ) )
        speed = -90;

    if( static_cast<SceneCactusFall*>( m_pScene )->IsInTestMode() && m_pScene->GetGame()->GetFramework()->IsKeyDown( 'Z' ) )
        speed = 90 * 8;
    if( static_cast<SceneCactusFall*>( m_pScene )->IsInTestMode() && m_pScene->GetGame()->GetFramework()->IsKeyDown( 'C' ) )
        speed = -90 * 8;

    m_Rotation.y += speed * deltaTime;
}
