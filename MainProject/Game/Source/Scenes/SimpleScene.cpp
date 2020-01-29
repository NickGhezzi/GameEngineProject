#include "GamePCH.h"
#include "BaseScene.h"
#include "SimpleScene.h"
#include "Game.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/Camera.h"
#include "ResourceManager.h"

SimpleScene::SimpleScene(Game* game):
BaseScene(game)
{
    
}

SimpleScene::~SimpleScene()
{
    for (auto obj : m_pGameObjects)
    {
        delete obj;
    }
    

    delete m_pCamera;
    m_pGameObjects.clear();
}

void SimpleScene::Init()
{
    m_pResources = m_pGame->GetResourceManager();
    m_pCamera = new Camera(this, vec3(0, 0, 0), vec2(1 / 5.0f, 1 / 5.0f));
    Player* pPlayer = new Player(this, m_pResources->GetMesh("CubeMesh"), m_pResources->GetMaterial("PlayerMaterial"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, 0, 0), 0, m_pGame->m_pController);
    pPlayer->CreateBody(true);
    pPlayer->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);
    m_pGameObjects.push_back(pPlayer);
}

void SimpleScene::Update(float deltaTime)
{
    for (auto obj : m_pGameObjects)
    {
        obj->Update(deltaTime);
    }
}

void SimpleScene::Draw()
{
    for (auto obj : m_pGameObjects)
    {
        obj->Draw(m_pCamera);
    }
}

void SimpleScene::LoadFromFile(const char* filename)
{
    long filelength;
    char* contents = fw::LoadCompleteFile(filename, &filelength);

    cJSON* jRoot = cJSON_Parse(contents);

    cJSON* jGameObjectArray = cJSON_GetObjectItem(jRoot, "GameObjects");

    int numGameObjects = cJSON_GetArraySize(jGameObjectArray);

    for (int i = 0; i < numGameObjects; i++)
    {
        cJSON* jGameObject = cJSON_GetArrayItem(jGameObjectArray, i);

        std::string flag = (std::string)cJSON_GetObjectItem(jGameObject, "Flags")->valuestring;

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
        vscale.x = (float)cJSON_GetArrayItem(scale, 1)->valuedouble;
        vscale.x = (float)cJSON_GetArrayItem(scale, 2)->valuedouble;

        if (flag == "Player")
        {
            int i = 0;
        }
    }


    cJSON_Delete(jRoot);
    delete[] contents;
}
