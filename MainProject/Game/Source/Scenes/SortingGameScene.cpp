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

SortingGameScene::SortingGameScene(Game* game) :
    BaseScene(game),
    m_BallPool()
{
    m_BallSpawnTimer = m_BallSpawnTime;
    m_Score = 0;
    m_BallSpawnPos = vec3(-5, 6, 0);
}

SortingGameScene::~SortingGameScene()
{
    delete m_HUDScene;
}

void SortingGameScene::Init()
{
    m_pResources = m_pGame->GetResourceManager();
    m_HUDScene = new HUDElementsScene(m_pGame);
    m_HUDScene->Init();
    m_HUDScene->UpdateScore(m_Score);

    ///////////////////////////////////
   //balls
    for (int i = 0; i < 30; i++)
    {
        GameObject* ball;
        int v = rand() % 3;

        if (v == 0)
        {
          ball = new Ball(this, m_pResources->GetMesh("Sphere"), m_pResources->GetMaterial("BallRed"), vec3(0.2, 0.2, 0.2), vec3(0, 0, 0), m_BallSpawnPos, ColorType::Red);
        }
        else if (v == 1)
        {
            ball = new Ball(this, m_pResources->GetMesh("Sphere"), m_pResources->GetMaterial("BallGreen"), vec3(0.2, 0.2, 0.2), vec3(0, 0, 0), m_BallSpawnPos, ColorType::Green);
        }
        else if (v == 2)
        {
            ball = new Ball(this, m_pResources->GetMesh("Sphere"), m_pResources->GetMaterial("BallBlue"), vec3(0.2, 0.2, 0.2), vec3(0, 0, 0), m_BallSpawnPos, ColorType::Blue);
        }

        ball->CreateBody(false);
        ball->AddCircle(0.2);
        ball->GetBody()->SetActive(false);
        m_BallPool.AddObjectToPool(ball);
        ball->SetPoolWhereWeCameFrom(&m_BallPool);
    }

    // PEEEEEGS
    vec3 pegscale = vec3(1.5, 0.5, 1);
    vec3 anchorscale = vec3(0.5, 0.5, 0.5);

    GameObject* peg = new Peg(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Peg"), vec3(1.5, 0.5, 1), vec3(0, -0, 6.65360689163208), vec3(1.9877731800079346, 3.7031209468841553, 3.814697265625e-006), m_pGame->m_pController);
    peg->CreateBody(false);
    peg->AddBox(vec3(1.5, 0.5, 1), 1, false, 0.2, 0);
    peg->GetBody()->SetGravity(0);
    GameObject* anchor = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Peg"), anchorscale, vec3(0, -0, 6.65360689163208), vec3(2.9877731800079346, 3.5, 0));
    anchor->CreateBody(true);
    anchor->AddBox(anchorscale, 1, false, 0.2, 0);
    peg->AddJointWithRestraint(anchor, vec2(anchor->GetPosition().x - 0.5, anchor->GetPosition().y), peg->GetRotation() - 85, peg->GetRotation() - 10);
    AddObjectToScene(peg);
    AddObjectToScene(anchor);


    GameObject* peg1 = new Peg(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Peg"), vec3(1.5, 0.5, 1), vec3(0, -0, -91.819374084472656), vec3(-3.916886568069458, 1.7999534606933594, 0), m_pGame->m_pController);
    peg1->CreateBody(false);
    peg1->AddBox(vec3(1.5, 0.5, 1), 1, false, 0.2, 0);
    peg1->GetBody()->SetGravity(0);
    GameObject* anchor1 = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Peg"), anchorscale, vec3(0, -0, -91.819374084472656), vec3(-3.916886568069458,2.5, 0));
    anchor1->CreateBody(true);
    anchor1->AddBox(anchorscale, 1, false, 0.2, 0);
    peg1->AddJointWithRestraint(anchor1, vec2(anchor1->GetPosition().x , anchor1->GetPosition().y - 0.5),peg1->GetRotation() - 10 ,peg1->GetRotation() + 85);
    AddObjectToScene(peg1);
    AddObjectToScene(anchor1);

    GameObject* peg2 = new Peg(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Peg"), vec3(1.5, 0.5, 1), vec3(0, -0, 3.5127899646759033), vec3(2.3433418273925781, -1.0894522666931152, 0), m_pGame->m_pController);
    peg2->CreateBody(false);
    peg2->AddBox(vec3(1.5, 0.5, 1), 1, false, 0.2, 0);
    peg2->GetBody()->SetGravity(0);
    GameObject* anchor2 = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Peg"), anchorscale, vec3(0, -0, -91.819374084472656), vec3(3.3433418273925781, -1.0894522666931152, 0));
    anchor2->CreateBody(true);
    anchor2->AddBox(anchorscale, 1, false, 0.2, 0);
    peg2->AddJointWithRestraint(anchor2, vec2(anchor2->GetPosition().x - 0.5, anchor2->GetPosition().y), peg2->GetRotation() - 85, peg2->GetRotation() - 10);
    AddObjectToScene(peg2);
    AddObjectToScene(anchor2);

    GameObject* peg3 = new Peg(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Peg"), vec3(1.5, 0.5, 1), vec3(0, -0, 8.2547492980957031), vec3(-3.8054983615875244, -3.8725945949554443, 0), m_pGame->m_pController);
    peg3->CreateBody(false);
    peg3->AddBox(vec3(1.5, 0.5, 1), 1, false, 0.2, 0);
    peg3->GetBody()->SetGravity(0);
    GameObject* anchor3 = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Peg"), anchorscale, vec3(0, -0, -91.819374084472656), vec3(-2.8054983615875244, -3.8725945949554443, 0));
    anchor3->CreateBody(true);
    anchor3->AddBox(anchorscale, 1, false, 0.2, 0);
    peg3->AddJointWithRestraint(anchor3, vec2(anchor3->GetPosition().x - 0.5, anchor3->GetPosition().y), peg3->GetRotation() - 85, peg3->GetRotation() - 10);
    AddObjectToScene(peg3);
    AddObjectToScene(anchor3);

    GameObject* platform = new Launcher(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Wood"), vec3(1.5, 0.5, 1), vec3(0, 0, 0), vec3(4.97, -5, 0));
    platform->CreateBody(false);
    platform->AddBox(vec3(1.5, 0.5, 1), 1, false, 0.2, 0);

    GameObject* anchor4 = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Peg"), anchorscale, vec3(0, -0, -0.3), vec3(3.83, -5, 0));
    anchor4->CreateBody(true);
    anchor4->AddBox(anchorscale, 1, false, 0.2, 0);


    platform->AddJointWithRestraint(anchor4, vec2(anchor4->GetPosition().x + .5, anchor4->GetPosition().y), platform->GetRotation() - 85, platform->GetRotation());

    GameObject* trigger = new TriggerBox(this, vec3(0.5, 0.5, 0.5), vec3(0, 0, 0), vec3(5.25, -4.85, 0));
    trigger->CreateBody(true);
    trigger->AddBox(vec3(0.5, 0.5, 0.5), 1, true, 0.2, 0);
    AddObjectToScene(platform);
    AddObjectToScene(trigger);
    AddObjectToScene(anchor4);

    GameObject* spinner = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Wood"), vec3(1.1,1.1,1.1), vec3(0, 0, 0), vec3(-.5, -3.75, 0));
    spinner->CreateBody(false);
    spinner->AddBox(vec3(1.1, 1.1, 1.1), 1, false, 0.2, 0);

    GameObject* anchor5 = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Peg"), anchorscale, vec3(0, -0, 0), vec3(-.5, -2, 0));
    anchor5->CreateBody(true);
    anchor5->AddBox(anchorscale, 1, false, 0.2, 0);
    spinner->AddJointWithMotor(anchor5, vec2(-.5f, -3.75f), 5, 5);

    AddObjectToScene(spinner);
    AddObjectToScene(anchor5);



    SpawnBall();
   
}

void SortingGameScene::Update(float deltaTime)
{
    BaseScene::Update(deltaTime);
    m_pPhysicsWorld->Update(deltaTime);
    m_HUDScene->Update(deltaTime);

    m_BallSpawnTimer -= deltaTime;
    if (m_BallSpawnTimer <= 0)
    {
        SpawnBall();
        m_BallSpawnTimer = m_BallSpawnTime;
    }

    for (auto obj : m_pGameObjects)
    {

        if (obj->GetName() == "Ball")
        {
            if (obj->GetPosition().y < -10.0f)
            {
                obj->GetBody()->ResetVelocity();
                obj->GetBody()->SetActive(false);
                m_BallPool.AddObjectToPool(obj);
                RemoveObjectFromScene(obj);
            }
        }
    }

}

void SortingGameScene::Draw()
{
    BaseScene::Draw();

    //static_cast<fw::PhysicsWorld2D*>(m_pPhysicsWorld)->DrawDebugData(&m_pCamera->GetViewMatrix(), &m_pCamera->GetProjectionMatrix());
    m_HUDScene->Draw();
}

void SortingGameScene::LoadFromFile(const char* filename)
{
    long filelength;
    char* contents = fw::LoadCompleteFile(filename, &filelength);

    cJSON* jRoot = cJSON_Parse(contents);

    cJSON* jGameObjectArray = cJSON_GetObjectItem(jRoot, "GameObjects");

    int numGameObjects = cJSON_GetArraySize(jGameObjectArray);

    for (int i = 0; i < numGameObjects; i++)
    {
        cJSON* jGameObject = cJSON_GetArrayItem(jGameObjectArray, i);

        std::string name = (std::string)cJSON_GetObjectItem(jGameObject, "Name")->valuestring;

        cJSON* tag = cJSON_GetObjectItem(jGameObject, "Flags");
        std::string comptag = cJSON_GetArrayItem(tag, 0)->valuestring;

        cJSON* pos = cJSON_GetObjectItem(jGameObject, "Pos");
        cJSON* rot = cJSON_GetObjectItem(jGameObject, "Rot");
        cJSON* scale = cJSON_GetObjectItem(jGameObject, "Scale");

        vec3 vpos, vrot, vscale;
        vpos.x = (float)cJSON_GetArrayItem(pos, 0)->valuedouble;
        vpos.y = (float)cJSON_GetArrayItem(pos, 1)->valuedouble;
        vpos.z = (float)cJSON_GetArrayItem(pos, 2)->valuedouble;

        vrot.x = (float)cJSON_GetArrayItem(rot, 0)->valuedouble;
        vrot.y = (float)cJSON_GetArrayItem(rot, 1)->valuedouble;
        vrot.z = (float)cJSON_GetArrayItem(rot, 2)->valuedouble;

        vscale.x = (float)cJSON_GetArrayItem(scale, 0)->valuedouble;
        vscale.y = (float)cJSON_GetArrayItem(scale, 1)->valuedouble;
        vscale.z = (float)cJSON_GetArrayItem(scale, 2)->valuedouble;

        if (comptag == "0")
        {
            cJSON* components = cJSON_GetObjectItem(jGameObject, "Components");

            cJSON* physicscomp = cJSON_GetArrayItem(components, 0);
            cJSON* spritecomp = cJSON_GetArrayItem(components, 1);

            std::string type = cJSON_GetArrayItem(physicscomp, 3)->valuestring;
            bool isStatic = cJSON_GetArrayItem(physicscomp, 4)->valueint;
            float density = (float)cJSON_GetArrayItem(physicscomp, 6)->valuedouble;
            float issensor = (float)cJSON_GetArrayItem(physicscomp, 7)->valuedouble;
            float friction = (float)cJSON_GetArrayItem(physicscomp, 8)->valuedouble;
            float restitution = (float)cJSON_GetArrayItem(physicscomp, 9)->valuedouble;

            std::string material = (std::string)cJSON_GetArrayItem(spritecomp, 2)->valuestring;
            std::string texture = (std::string)cJSON_GetArrayItem(spritecomp, 3)->valuestring;
            std::string shader = (std::string)cJSON_GetArrayItem(spritecomp, 4)->valuestring;

          

            GameObject* pGround = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial(material), vec3(0.5,0.5,0.5), vrot, vpos - 1);
            pGround->CreateBody(isStatic);
            pGround->AddBox(vec3(0.5, 0.5, 0.5), density, issensor, friction, restitution);

            Peg* pPlayer = new Peg(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial(material), vscale, vrot, vpos, m_pGame->m_pController);
            pPlayer->CreateBody(false);
            pPlayer->AddBox(vscale, density, issensor, friction, restitution);
            pPlayer->AddJointWithRestraint(pGround, vec2(vpos.x + 1, vpos.y), pPlayer->GetRotation() - 90, pPlayer->GetRotation());
            
            pPlayer->GetBody()->SetGravity(0);
            m_pGameObjects.push_back(pPlayer);
            m_pGameObjects.push_back(pGround);
            //todo if type == box create box

        }
        if (comptag == "5")
        {
            cJSON* components = cJSON_GetObjectItem(jGameObject, "Components");

            cJSON* physicscomp = cJSON_GetArrayItem(components, 0);
            cJSON* spritecomp = cJSON_GetArrayItem(components, 1);

            std::string type = (std::string)cJSON_GetArrayItem(physicscomp, 3)->valuestring;
            bool isStatic = (bool)cJSON_GetArrayItem(physicscomp, 4)->valueint;
            float density = (float)cJSON_GetArrayItem(physicscomp, 6)->valuedouble;
            float issensor = (float)cJSON_GetArrayItem(physicscomp, 7)->valuedouble;
            float friction = (float)cJSON_GetArrayItem(physicscomp, 8)->valuedouble;
            float restitution = (float)cJSON_GetArrayItem(physicscomp, 9)->valuedouble;

            std::string material = (std::string)cJSON_GetArrayItem(spritecomp, 2)->valuestring;
            std::string texture = (std::string)cJSON_GetArrayItem(spritecomp, 3)->valuestring;
            std::string shader = (std::string)cJSON_GetArrayItem(spritecomp, 4)->valuestring;

            GameObject* pGround = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial(material), vscale, vrot, vpos);
            pGround->CreateBody(isStatic);
            pGround->AddBox(vscale, density, issensor, friction, restitution);
            m_pGameObjects.push_back(pGround);
        }
        if (name == "BinRed")
        {
            cJSON* components = cJSON_GetObjectItem(jGameObject, "Components");

            cJSON* physicscomp = cJSON_GetArrayItem(components, 0);
            cJSON* spritecomp = cJSON_GetArrayItem(components, 1);

            std::string type = (std::string)cJSON_GetArrayItem(physicscomp, 3)->valuestring;
            bool isStatic = (bool)cJSON_GetArrayItem(physicscomp, 4)->valueint;
            float density = (float)cJSON_GetArrayItem(physicscomp, 6)->valuedouble;
            float issensor = (float)cJSON_GetArrayItem(physicscomp, 7)->valuedouble;
            float friction = (float)cJSON_GetArrayItem(physicscomp, 8)->valuedouble;
            float restitution = (float)cJSON_GetArrayItem(physicscomp, 9)->valuedouble;

            std::string material = (std::string)cJSON_GetArrayItem(spritecomp, 2)->valuestring;
            std::string texture = (std::string)cJSON_GetArrayItem(spritecomp, 3)->valuestring;
            std::string shader = (std::string)cJSON_GetArrayItem(spritecomp, 4)->valuestring;
            //vpos.x += 0.3;
            vscale -= 0.3;
            GameObject* bin = new Bin(this, m_pResources->GetMesh("BinMesh"), m_pResources->GetMaterial("BinRed"), vscale, vrot, vpos, ColorType::Red);
            bin->CreateBody(isStatic);
            bin->AddBox(vscale, density, issensor, friction, restitution);
            m_pGameObjects.push_back(bin);
        }
        if (name == "BinGreen")
        {
            cJSON* components = cJSON_GetObjectItem(jGameObject, "Components");

            cJSON* physicscomp = cJSON_GetArrayItem(components, 0);
            cJSON* spritecomp = cJSON_GetArrayItem(components, 1);

            std::string type = (std::string)cJSON_GetArrayItem(physicscomp, 3)->valuestring;
            bool isStatic = (bool)cJSON_GetArrayItem(physicscomp, 4)->valueint;
            float density = (float)cJSON_GetArrayItem(physicscomp, 6)->valuedouble;
            float issensor = (float)cJSON_GetArrayItem(physicscomp, 7)->valuedouble;
            float friction = (float)cJSON_GetArrayItem(physicscomp, 8)->valuedouble;
            float restitution = (float)cJSON_GetArrayItem(physicscomp, 9)->valuedouble;

            std::string material = (std::string)cJSON_GetArrayItem(spritecomp, 2)->valuestring;
            std::string texture = (std::string)cJSON_GetArrayItem(spritecomp, 3)->valuestring;
            std::string shader = (std::string)cJSON_GetArrayItem(spritecomp, 4)->valuestring;
            vscale -= 0.3;
            GameObject* bin = new Bin(this, m_pResources->GetMesh("BinMesh"), m_pResources->GetMaterial("BinGreen"), vscale, vrot, vpos, ColorType::Green);
            bin->CreateBody(isStatic);
            bin->AddBox(vscale, density, issensor, friction, restitution);
            m_pGameObjects.push_back(bin);
        }
        if (name == "BinBlue")
        {
            cJSON* components = cJSON_GetObjectItem(jGameObject, "Components");

            cJSON* physicscomp = cJSON_GetArrayItem(components, 0);
            cJSON* spritecomp = cJSON_GetArrayItem(components, 1);

            std::string type = (std::string)cJSON_GetArrayItem(physicscomp, 3)->valuestring;
            bool isStatic = (bool)cJSON_GetArrayItem(physicscomp, 4)->valueint;
            float density = (float)cJSON_GetArrayItem(physicscomp, 6)->valuedouble;
            float issensor = (float)cJSON_GetArrayItem(physicscomp, 7)->valuedouble;
            float friction = (float)cJSON_GetArrayItem(physicscomp, 8)->valuedouble;
            float restitution = (float)cJSON_GetArrayItem(physicscomp, 9)->valuedouble;

            std::string material = (std::string)cJSON_GetArrayItem(spritecomp, 2)->valuestring;
            std::string texture = (std::string)cJSON_GetArrayItem(spritecomp, 3)->valuestring;
            std::string shader = (std::string)cJSON_GetArrayItem(spritecomp, 4)->valuestring;
            vscale -= 0.3;
            GameObject* bin = new Bin(this, m_pResources->GetMesh("BinMesh"), m_pResources->GetMaterial("BinBlue"), vscale, vrot, vpos, ColorType::Blue);
            bin->CreateBody(isStatic);
            bin->AddBox(vscale, density, issensor, friction, restitution);
            m_pGameObjects.push_back(bin);
        }
    }


    cJSON_Delete(jRoot);
    delete[] contents;
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
                    m_BallPool.AddObjectToPool(ball);
                    RemoveObjectFromScene(ball);
                }
                else
                {
                    ball->GetBody()->ResetVelocity();
                    ball->GetBody()->SetActive(false);
                    m_BallPool.AddObjectToPool(ball);
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
                    m_BallPool.AddObjectToPool(ball);
                    RemoveObjectFromScene(ball);
                }
                else
                {
                    ball->GetBody()->ResetVelocity();
                    ball->GetBody()->SetActive(false);
                    m_BallPool.AddObjectToPool(ball);
                    RemoveObjectFromScene(ball);
                }
            }
        }
    }
}

void SortingGameScene::SpawnBall()
{
    GameObject* pObj = m_BallPool.GetObjectFromPool();
    AddObjectToScene(pObj);
    pObj->SetPosition(m_BallSpawnPos);
    pObj->GetBody()->SetActive(true);
}

void SortingGameScene::RemoveBall()
{
}

void SortingGameScene::Reset()
{
}
