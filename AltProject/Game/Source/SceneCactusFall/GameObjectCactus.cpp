#include "GamePCH.h"

#include "GameObjectCactus.h"

#include "GameObjectTarget.h"
#include "GameObjectTargetBonus.h"
#include "Base/Mesh.h"
#include "SceneCactusFall.h"
#include "Game.h"
#include "Scenes/BaseScene.h"

GameObjectCactus::GameObjectCactus(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: GameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
    m_TargetRotation = -180.0f;
    m_dis = 0;
    m_angle = 0;
    m_angle2 = 0;
}

GameObjectCactus::~GameObjectCactus()
{
}

void GameObjectCactus::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

    {
        GameObjectTarget* ringObjects[5] =
        {
            (GameObjectTarget*)m_pScene->GetGameObjectByName( "Ring1" ),
            (GameObjectTarget*)m_pScene->GetGameObjectByName( "Ring2" ),
            (GameObjectTarget*)m_pScene->GetGameObjectByName( "Ring3" ),
            (GameObjectTarget*)m_pScene->GetGameObjectByName( "Ring4" ),
            (GameObjectTarget*)m_pScene->GetGameObjectByName( "Ring5" ),
        };

        // If the player is falling.
        if( m_Position.y > 0.0f )
        {
            // Show the players altitude as score.
            static_cast<SceneCactusFall*>( m_pScene )->SetScore( m_Position.y );
        }
        else
        {
            // Otherwise, calculate score.

            // Scores for the rings, from the center ("Ring1") to outermost ring ("Ring5").
            float ringValues[5] = { 900, 700, 500, 300, 150 };
            for(int i = 0; i < 5; i++)
            {               
                // TODO_CactusFall: Figure out which ring the player landed in and set the score (stored in SceneCactusFall) to match.
                //         Each ring is 2 units thick.
                //         Use the scores stored in ringValues.

                float min = i * 2;
                float max = min + 2;
                float dis = m_Position.DistanceFrom(vec3(0, 0, 5));
                m_dis = dis;
                if (dis > min&& dis < max)
                {
                    static_cast<SceneCactusFall*>(m_pScene)->SetScore(ringValues[i]);
                    GameObjectTarget* bonus = (GameObjectTarget*)static_cast<SceneCactusFall*>(m_pScene)->GetGameObjectByName("Ring" + std::to_string(i + 1));
                    if (bonus)
                    {
                        bonus->SetColor(vec3(1, 1, 1));
                    }
                }
                else if (dis > 10)
                {
                    static_cast<SceneCactusFall*>(m_pScene)->SetScore(0);
                }
            }

            // Deal with bonus.
            vec2 playerDir = vec2(m_Position.x - 0, m_Position.z - 5);
            float playerAngle = (atan2(playerDir.y, playerDir.x)) * 180/PI;
            GameObjectTargetBonus* bonus = (GameObjectTargetBonus*)static_cast<SceneCactusFall*>(m_pScene)->GetGameObjectByName("BonusArc");
            m_angle = playerAngle;
            if (m_angle < 0)
            {
                m_angle += 360;
            }
            m_angle2 = bonus->GetRotation().y;
            if (m_angle2 < 0)
            {
                m_angle2 += 360;
            }
            if(m_angle > (m_angle2 - 30.0f) && m_angle < (m_angle2 + 30.0f))
            {
                // TODO_CactusFall: Figure out if the player landed in the "BonusArc" and award an additional 4000 points.
                //         The "BonusArc" is a 60 degree arc.
                //         It starts at 0 degrees and goes from +30 to -30 degrees.
                //         Ensure the Bonus Arc works in all conditions. Rotate it both clockwise and counter-clockwise multiple times.
                //         Use the debug keys (Q,E,Z,C) to rotate the arc.
                
                if (m_dis <= 10)
                {
                    static_cast<SceneCactusFall*>(m_pScene)->SetScore(4000);
                }

            }

            {
                // TODO_CactusFall: Change the color of the ring the player landed in to white, leaving the other ring colors as is.
                //        Ring colors should reset properly, even in test mode as you move around.
                //        This will require changes to other parts of code, so change whatever you need.
            }
        }
    }

    float speed = 60.0f;
    float fallSpeed = 60.0f;

    vec3 dir(0,0,0);

    bool sanity = false;

    if( m_pScene->GetGame()->GetFramework()->IsKeyDown( VK_SHIFT ) || static_cast<SceneCactusFall*>( m_pScene )->IsInTestMode() )
    {
        sanity = true;
        speed = 10.0f;
    }

    if( sanity || m_Position.y > 0.0f )
    {
        if( m_pScene->GetGame()->GetFramework()->IsKeyDown( ' ' ) || m_Position.y < 50.0f )
            m_TargetRotation = -180.0f;
        else
            m_TargetRotation = -90.0f;

        if( m_pScene->GetGame()->GetFramework()->IsKeyDown( 'W' ) )
            dir.z += 1.0f;
        if( m_pScene->GetGame()->GetFramework()->IsKeyDown( 'S' ) )
            dir.z -= 1.0f;
        if( m_pScene->GetGame()->GetFramework()->IsKeyDown( 'A' ) )
            dir.x -= 1.0f;
        if( m_pScene->GetGame()->GetFramework()->IsKeyDown( 'D' ) )
            dir.x += 1.0f;

        dir.y -= 1.0f;

        // Turbulence.
        if( m_pScene->GetGame()->GetFramework()->IsKeyDown( ' ' ) )
        {
            speed = 60.0f;
            fallSpeed = 200.0f;
            if( !sanity )
            {
                dir.x += (rand()%1000 - 500) / 2400.0f;
                dir.z += (rand()%1000 - 500) / 2400.0f;
            }
        }
        else
        {
            if( !sanity )
            {
                dir.x += (rand()%1000 - 500) / 800.0f;
                dir.z += (rand()%1000 - 500) / 800.0f;
            }
        }
    }

    dir.x *= speed * deltaTime;
    dir.y *= fallSpeed * deltaTime;
    dir.z *= speed * deltaTime;

    m_Position.x += dir.x;
    m_Position.y += dir.y;
    m_Position.z += dir.z;

    float rotSpeed = 600.0;

    if( m_Rotation.x < m_TargetRotation )
        m_Rotation.x += rotSpeed * deltaTime;
    if( m_Rotation.x > m_TargetRotation )
        m_Rotation.x -= rotSpeed * deltaTime;

    if( m_Position.y < 0.0f )
        m_Position.y = 0.0f;

    // Move score to be relative to player.
    m_pScene->GetGameObjectByName( "Number1000s" )->SetPosition( m_Position + vec3( 1.5f, 1, 3.5f ) );
    m_pScene->GetGameObjectByName( "Number100s" )->SetPosition(  m_Position + vec3( 2.5f, 1, 3.5f ) );
    m_pScene->GetGameObjectByName( "Number10s" )->SetPosition(   m_Position + vec3( 3.5f, 1, 3.5f ) );
    m_pScene->GetGameObjectByName( "Number1s" )->SetPosition(    m_Position + vec3( 4.5f, 1, 3.5f ) );
}

void GameObjectCactus::Draw(Camera* pCamera)
{
    if( m_pMesh != nullptr )
    {
        m_pMesh->SetupAttributes( m_pMaterial );

        // Create world matrix.
        mat4 worldMatrix;
        worldMatrix.CreateSRT( m_Scale, m_Rotation, m_Position + vec3(0,2,0) );

        m_pMesh->SetupUniforms( m_pMaterial, &worldMatrix, pCamera, 1, 0 );
        m_pMesh->Draw( m_pMaterial );
    }

    ImGui::Begin("Cactus Fall");
    ImGui::Text("%0.0f", m_dis);
    ImGui::Text("%0.0f", m_angle);
    ImGui::Text("%0.0f", m_angle2);
    ImGui::End();
}
