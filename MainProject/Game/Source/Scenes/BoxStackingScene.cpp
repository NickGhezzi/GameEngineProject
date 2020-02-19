#include "GamePCH.h"
#include "BoxStackingScene.h"
#include "Game.h"
#include "GameObjects/Player.h"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"
#include "ResourceManager.h"
#include "Base/ObjectPool.h"

BoxStackingScene::BoxStackingScene(Game* game):
    BaseScene(game),
    m_ObjectPool()
{
    m_pCamera = nullptr;
    m_pResources = nullptr;
    m_pPlayer = nullptr;
    m_pFloor = nullptr;
    m_NumActiveBoxes = 0;
    m_Score = 0;
    m_bInitialBox = false;
}

BoxStackingScene::~BoxStackingScene()
{
    for (auto obj : m_pGameObjects)
    {
        delete obj;
    }
    m_pGameObjects.clear();

    delete m_pCamera;
    delete m_pPlayer;
    delete m_pFloor;
}

void BoxStackingScene::Init()
{
    m_pResources = m_pGame->GetResourceManager();
    m_pCamera = new Camera(this, vec3(0, 0, 0), vec2(1 / 5.0f, 1 / 5.0f));

    m_pPlayer = new Player(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Megaman"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, 3, 0), 0, m_pGame->m_pController);
    m_pPlayer->CreateBody(false);
    m_pPlayer->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);
    m_pPlayer->GetBody()->SetGravity(0);
    m_pPlayer->bLockControlls = true;

    m_pFloor = new GameObject(this, m_pResources->GetMesh("FloorMesh"), m_pResources->GetMaterial("Ground"), vec3(2, 1, 1), vec3(0, 0, 0), vec3(0, -5, 0));
    m_pFloor->SetName("Floor");
    m_pFloor->CreateBody(true);
    m_pFloor->AddBox(vec3(10, 1, 1), 1, false, 0.2, 0);

    //add to pool
    for (int i = 0; i < 100; i++)
    {
        GameObject* pObj = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Box"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, 0, 0));
        pObj->CreateBody(false);
        pObj->GetBody()->SetActive(false);
        pObj->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);
        pObj->SetName("Box");
        m_ObjectPool.AddObjectToPool(pObj);
        pObj->SetPoolWhereWeCameFrom(&m_ObjectPool);
    }

    
}

void BoxStackingScene::Update(float deltaTime)
{
    m_pPhysicsWorld->Update(deltaTime);
    m_pPlayer->Update(deltaTime);
    m_pFloor->Update(deltaTime);
    m_pPlayer->SetPosition(vec3(sin(fw::GetSystemTimeSinceGameStart()) * 5, 3, 0));
    //////////// game stuff //////////////
    if (m_pPlayer->bIsActionPressed == true)
    {
        SpawnBox();
        m_pPlayer->bIsActionPressed = false;
    }


    for (auto obj : m_pGameObjects)
    {
        obj->Update(deltaTime);
        if (obj->GetPosition().y < -10.0f)
        {
            obj->GetBody()->ResetVelocity();
            obj->GetBody()->SetActive(false);
            m_ObjectPool.AddObjectToPool(obj);
            RemoveObjectFromScene(obj);
            m_NumActiveBoxes--;
        }
    }

    ImGui::Begin("GameStuff");
    ImGui::Text("Score: %d", m_Score);

    ImGui::End();
    ////////////////////////////////////////
    m_pCamera->Update(deltaTime);
}

void BoxStackingScene::Draw()
{
    m_pPlayer->Draw(m_pCamera);
    m_pFloor->Draw(m_pCamera);
    for (auto obj : m_pGameObjects)
    {
        obj->Draw(m_pCamera);
    }

    static_cast<fw::PhysicsWorld2D*>(m_pPhysicsWorld)->DrawDebugData(&m_pCamera->GetViewMatrix(), &m_pCamera->GetProjectionMatrix());
}

void BoxStackingScene::LoadFromFile(const char* filename)
{

}

void BoxStackingScene::OnEvent(fw::Event* pEvent)
{
    m_PreviousHighestY = m_HighestY;

    if (pEvent->GetType() == "CollisionEvent")
    {
        fw::CollisionEvent* pCollisionEvent = (fw::CollisionEvent*)pEvent;
        if (pCollisionEvent)
        {
            GameObject* A = static_cast<GameObject*>(pCollisionEvent->GetBodyA());
            GameObject* B = static_cast<GameObject*>(pCollisionEvent->GetBodyB());
            
            if (A->GetName() == "Box")
            {
                if(B->GetName() == "Box")
                {
                    for (int i = 0; i < m_NumActiveBoxes; i++)
                    {
                        float tempy = m_pGameObjects[i]->GetPosition().y;
                        if (tempy > m_HighestY)
                        {
                            m_PreviousHighestY = m_HighestY;
                            m_HighestY = tempy;
                            
                        }
                        A->bHasCollided = true;
                        B->bHasCollided = true;
                    }
                }
            }

            if (A->GetName() == "Floor" || B->GetName() == "Floor")
            {
                if (m_bInitialBox)
                {
                    Reset();
                }
                else
                {
                    m_bInitialBox = true;
                }
            }
                 //if (m_HighestY > m_PreviousHighestY && (A->bHasCollided == true && B->bHasCollided == false || A->bHasCollided == false && B->bHasCollided == true || A->bHasCollided == false && B->bHasCollided == false))
                 //{
                 //    m_Score++;
                 //    A->bHasCollided = true;
                 //    B->bHasCollided = true;
                 //}
        }
   
    }

                 if (m_HighestY > m_PreviousHighestY)
                 {
                      m_Score++;
                 }
}

void BoxStackingScene::SpawnBox()
{
    GameObject* pObj = m_ObjectPool.GetObjectFromPool();
    AddObjectToScene(pObj);
    pObj->SetPosition(vec3(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y - 1, 0));
    pObj->GetBody()->SetActive(true);
    m_NumActiveBoxes++;
}

void BoxStackingScene::Reset()
{

    for(int i = m_pGameObjects.size() - 1; i >= 0; i--)
    {
            GameObject* obj = m_pGameObjects[i];
            obj->GetBody()->ResetVelocity();
            obj->GetBody()->SetActive(false);
            m_ObjectPool.AddObjectToPool(obj);
            RemoveObjectFromScene(obj);
            m_NumActiveBoxes--;
    }
    m_bInitialBox = false;
    m_Score = 0;
    m_HighestY = m_pFloor->GetPosition().y + 1;
}


