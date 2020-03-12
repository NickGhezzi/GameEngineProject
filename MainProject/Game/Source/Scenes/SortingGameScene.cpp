#include "GamePCH.h"
#include "SortingGameScene.h"
#include "Game.h"
#include "ResourceManager.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/Peg.h"
#include "GameObjects/Camera.h"
#include "GameObjects/MovingPlatform.h"
#include "GameObjects/Player.h"
#include "GameObjects/TriggerBox.h"

SortingGameScene::SortingGameScene(Game* game):
    BaseScene(game)
{
    m_BallSpawnTime = 15.0f;
    m_Score = 0;
}

SortingGameScene::~SortingGameScene()
{

}

void SortingGameScene::Init()
{
    //TODO find a way to make a random number of different types of balls. pick a random number between 0 and 2 then based on that number assign the corect texture and type
    m_pResources = m_pGame->GetResourceManager();
    GameObject* floor = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Ground"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(2.3, 3, 0));
    floor->CreateBody(true);
    floor->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);

    GameObject* peg = new Peg(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Megaman"), vec3(3, 1, 1), vec3(0, 0, 0), vec3(0, 3, 0), m_pGame->m_pController);
    peg->CreateBody(false);
    peg->AddBox(vec3(3, 1, 1), 1, false, 0.2, 0);
    peg->AddJointWithRestraint(floor, vec2(1, 3), peg->GetRotation() - 90, peg->GetRotation());
    peg->GetBody()->SetGravity(0);

    GameObject* dude = new Player(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Megaman"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, 0, 0), 0, m_pGame->m_pController);
    dude->CreateBody(false);
    dude->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);

    //GameObject* platform = new MovingPlatform(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Ground"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, -3, 0));
    //platform->CreateBody(true);
    //platform->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);
    //platform->AddBox(vec3(1.1, 1.1, 1.1), 1, true, 0.2, 0);



    AddObjectToScene(peg);
    AddObjectToScene(floor);
    //AddObjectToScene(platform);
    AddObjectToScene(dude);
}

void SortingGameScene::Update(float deltaTime)
{
    BaseScene::Update(deltaTime);
    m_pPhysicsWorld->Update(deltaTime);

}

void SortingGameScene::Draw()
{
    BaseScene::Draw();

    static_cast<fw::PhysicsWorld2D*>(m_pPhysicsWorld)->DrawDebugData(&m_pCamera->GetViewMatrix(), &m_pCamera->GetProjectionMatrix());
}

void SortingGameScene::LoadFromFile(const char* filename)
{
}

void SortingGameScene::OnEvent(fw::Event* pEvent)
{
    if (pEvent->GetType() == "CollisionEvent")
    {
        fw::CollisionEvent* pCollisionEvent = (fw::CollisionEvent*)pEvent;
        if (pCollisionEvent)
        {
            GameObject* A = static_cast<GameObject*>(pCollisionEvent->GetBodyA());
            GameObject* B = static_cast<GameObject*>(pCollisionEvent->GetBodyB());

            if (A->GetName() == "MovingPlatform" || B->GetName() == "MovingPlatform")
            {
                for (auto obj : m_pGameObjects)
                {
                    if (obj->GetName() == "MovingPlatform")
                    {
                        MovingPlatform* platform = static_cast<MovingPlatform*>(obj);
                        platform->SetIsTouching(true);
                    }
                }
            }
        }
    }
}

void SortingGameScene::SpawnBall()
{
}

void SortingGameScene::Reset()
{
}
