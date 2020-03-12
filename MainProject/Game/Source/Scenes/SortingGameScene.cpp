#include "GamePCH.h"
#include "SortingGameScene.h"
#include "Game.h"
#include "ResourceManager.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/Peg.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Launcher.h"
#include "GameObjects/Player.h"
#include "GameObjects/TriggerBox.h"
#include "GameObjects/Ball.h"
#include "GameObjects/Bin.h"

#include "HUDElementsScene.h"

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
    m_HUDScene = new HUDElementsScene(m_pGame);
    m_HUDScene->Init();
    m_HUDScene->UpdateScore(m_Score);

    ///////////////////////////////////
    GameObject* floor = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Ground"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(2.3, 3, 0));
    floor->CreateBody(true);
    floor->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);

    GameObject* peg = new Peg(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Megaman"), vec3(3, 1, 1), vec3(0, 0, 0), vec3(0, 3, 0), m_pGame->m_pController);
    peg->CreateBody(false);
    peg->AddBox(vec3(3, 1, 1), 1, false, 0.2, 0);
    peg->AddJointWithRestraint(floor, vec2(1, 3), peg->GetRotation() - 90, peg->GetRotation());
    peg->GetBody()->SetGravity(0);


    GameObject* platform = new Launcher(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Ground"), vec3(3, 1, 1), vec3(0, 0, 0), vec3(0, -3, 0));
    platform->CreateBody(false);
    platform->AddBox(vec3(3, 1, 1), 1, false, 0.2, 0);
    platform->AddJointWithRestraint(floor, vec2(-1.5, -3), platform->GetRotation() - 85, platform->GetRotation());

    GameObject* trigger = new TriggerBox(this, vec3(1, 1, 1), vec3(0, 0, 0), vec3(1, -2.5, 0));
    trigger->CreateBody(true);
    trigger->AddBox(vec3(1, 0.5, 1), 1, true, 0.2, 0);

    GameObject* ball = new Ball(this, m_pResources->GetMesh("Sphere"), m_pResources->GetMaterial("BallRed"), vec3(0.2, 0.2, 0.2), vec3(0, 0, 0), vec3(-4, 0, 0), ColorType::Red);
    ball->CreateBody(false);
    ball->AddCircle(0.2);

    GameObject* bin = new Bin(this, m_pResources->GetMesh("BinMesh"), m_pResources->GetMaterial("BinGreen"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(-4, -3, 0), ColorType::Green);
    bin->CreateBody(true);
    bin->AddBox(vec3(2, 1, 1), 1, false, 0.2, 0);


    AddObjectToScene(peg);
    AddObjectToScene(floor);
    AddObjectToScene(platform);
    AddObjectToScene(trigger);
    AddObjectToScene(ball);
    AddObjectToScene(bin);

}

void SortingGameScene::Update(float deltaTime)
{
    BaseScene::Update(deltaTime);
    m_pPhysicsWorld->Update(deltaTime);
    m_HUDScene->Update(deltaTime);
}

void SortingGameScene::Draw()
{
    BaseScene::Draw();

    static_cast<fw::PhysicsWorld2D*>(m_pPhysicsWorld)->DrawDebugData(&m_pCamera->GetViewMatrix(), &m_pCamera->GetProjectionMatrix());
    m_HUDScene->Draw();
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

            //used for launcher
            if (A->GetName() == "TriggerBox" || B->GetName() == "TriggerBox")
            {

                if (A->GetName() == "Ball" || B->GetName() == "Ball")
                {
                    for (auto obj : m_pGameObjects)
                    {
                        if (obj->GetName() == "Launcher")
                        {
                            Launcher* platform = static_cast<Launcher*>(obj);
                            platform->SetIsTouching(true);
                        }
                    }
                }
            }

            //ball and bin
            if (A->GetName() == "Bin")
            {
                Bin* bin = static_cast<Bin*>(A);
                Ball* ball = static_cast<Ball*>(B);
                if (bin->GetType() == ball->GetType())
                {
                    m_Score++;
                    m_HUDScene->UpdateScore(m_Score);
                    ball->GetBody()->ResetVelocity();
                    ball->GetBody()->SetActive(false);
                    //m_ObjectPool.AddObjectToPool(obj);
                    RemoveObjectFromScene(ball);
                }
                else
                {
                    ball->GetBody()->ResetVelocity();
                    ball->GetBody()->SetActive(false);
                    //m_ObjectPool.AddObjectToPool(obj);
                    RemoveObjectFromScene(ball);
                }
            }
            if (B->GetName() == "Bin")
            {
                Bin* bin = static_cast<Bin*>(B);
                Ball* ball = static_cast<Ball*>(A);
                if (bin->GetType() == ball->GetType())
                {
                    m_Score++;
                    m_HUDScene->UpdateScore(m_Score);
                    ball->GetBody()->ResetVelocity();
                    ball->GetBody()->SetActive(false);
                    //m_ObjectPool.AddObjectToPool(obj);
                    RemoveObjectFromScene(ball);
                }
                else
                {
                    ball->GetBody()->ResetVelocity();
                    ball->GetBody()->SetActive(false);
                    //m_ObjectPool.AddObjectToPool(obj);
                    RemoveObjectFromScene(ball);
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
