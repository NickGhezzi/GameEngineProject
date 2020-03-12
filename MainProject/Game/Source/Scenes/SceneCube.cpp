#include "GamePCH.h"
#include "SceneCube.h"
#include "Game.h"
#include "GameObjects/Player.h"
#include "GameObjects/Camera.h"
#include "ResourceManager.h"


SceneCube::SceneCube(Game* game):
    BaseScene(game)
{
    m_pCamera = nullptr;
    m_pPlayer = nullptr;
    m_pCube = nullptr;
    m_pDummy = nullptr;

    m_Timer = 0;
}

SceneCube::~SceneCube()
{
    delete m_pCamera;
    delete m_pPlayer;
    delete m_pCube;
    delete m_pDummy;
}

void SceneCube::Init()
{
    m_pResources = m_pGame->GetResourceManager();
    m_pPlayer = new Player(this, m_pResources->GetMesh("CubeMesh"), m_pResources->GetMaterial("Dice"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, 0, 0), 0, m_pGame->m_pController);
    m_pPlayer->CreateBody(true);
    m_pPlayer->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);

    m_pDummy = new Player(this, m_pResources->GetMesh("Plane"), m_pResources->GetMaterial("Dice"), vec3(1,1,1), vec3(0,0,0), vec3(-3, -5, 0), 0, m_pGame->m_pController);
    m_pDummy->CreateBody(true);
    m_pDummy->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);

    m_pCube = new GameObject(this, m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("Dice"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, 0, 0));
    m_pCube->CreateBody(true);
    m_pCube->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);

    m_pCamera = new Camera(this, vec3(0, 0, 0), vec2(1 / 5.0f, 1 / 5.0f));
    
    //static_cast<fw::PhysicsWorld2D*>(m_pPhysicsWorld)->DrawDebugData(&m_pCamera->GetViewMatrix(), &m_pCamera->GetProjectionMatrix());
}

void SceneCube::Update(float deltaTime)
{
    m_pPhysicsWorld->Update(deltaTime);

    m_Timer += deltaTime * 100;
   // m_pPlayer->SetRotation(vec3(m_Timer, m_Timer, m_Timer));
    m_pPlayer->Update(deltaTime);

    m_pCube->Update(deltaTime);

    m_pDummy->Update(deltaTime);
    m_pCamera->Update(deltaTime);
}

void SceneCube::Draw()
{
   // m_pPlayer->Draw(m_pCamera);
    m_pCube->Draw(m_pCamera);
    m_pDummy->Draw(m_pCamera);
    static_cast<fw::PhysicsWorld2D*>(m_pPhysicsWorld)->DrawDebugData(&m_pCamera->GetViewMatrix(), &m_pCamera->GetProjectionMatrix());
}

void SceneCube::LoadFromFile(const char* filename)
{
    //char* contents = fw::LoadCompleteFile(filename, nullptr);

    //cJSON* jRoot = cJSON_Parse(contents);

    //cJSON* jGameObjectArray = cJSON_GetObjectItem(jRoot, "GameObjects");

    //int numGameObjects = cJSON_GetArraySize(jGameObjectArray);
    //for (int i = 0; i < numGameObjects; i++)
    //{
    //    cJSON* jGameObject = cJSON_GetArrayItem(jGameObjectArray, i);

    //    std::string name = (std::string)cJSON_GetObjectItem(jGameObject, "Name")->valuestring;
    //    cJSON* pos = cJSON_GetObjectItem(jGameObject, "Pos");
    //    cJSON* rot = cJSON_GetObjectItem(jGameObject, "Rot");
    //    cJSON* scale = cJSON_GetObjectItem(jGameObject, "Scale");

    //    vec3 vpos, vrot, vscale;
    //    vpos.x = (float)cJSON_GetArrayItem(pos, 0)->valuedouble;
    //    vpos.y = (float)cJSON_GetArrayItem(pos, 1)->valuedouble;
    //    vpos.z = (float)cJSON_GetArrayItem(pos, 2)->valuedouble;

    //    vrot.x = (float)cJSON_GetArrayItem(rot, 0)->valuedouble;
    //    vrot.y = (float)cJSON_GetArrayItem(rot, 1)->valuedouble;
    //    vrot.z = (float)cJSON_GetArrayItem(rot, 2)->valuedouble;

    //    vscale.x = (float)cJSON_GetArrayItem(scale, 0)->valuedouble;
    //    vscale.x = (float)cJSON_GetArrayItem(scale, 1)->valuedouble;
    //    vscale.x = (float)cJSON_GetArrayItem(scale, 2)->valuedouble;

    //    if (name == "Player")
    //    {

    //    }
    //}


    //cJSON_Delete(jRoot);
    //delete[] contents;
}
