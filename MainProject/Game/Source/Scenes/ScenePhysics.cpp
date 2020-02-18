#include "GamePCH.h"
#include "ScenePhysics.h"
#include "BaseScene.h"
#include "Game.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/Camera.h"
#include "ResourceManager.h"

ScenePhysics::ScenePhysics(Game* game) :
    BaseScene(game)
{
}

ScenePhysics::~ScenePhysics()
{
    for (auto obj : m_pGameObjects)
    {
        delete obj;
    }


    delete m_pCamera;
    m_pGameObjects.clear();
}

void ScenePhysics::Init()
{
    m_pResources = m_pGame->GetResourceManager();
    m_pCamera = new Camera(this, vec3(0, 0, 0), vec2(1 / 5.0f, 1 / 5.0f));
}

void ScenePhysics::Update(float deltaTime)
{
    m_pPhysicsWorld->Update(deltaTime);
    for (auto obj : m_pGameObjects)
    {
        obj->Update(deltaTime);
    }
    m_pCamera->Update(deltaTime);
}

void ScenePhysics::Draw()
{
    for (auto obj : m_pGameObjects)
    {
        obj->Draw(m_pCamera);
    }
}

void ScenePhysics::LoadFromFile(const char* filename)
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

        if (name == "Player")
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

            Player* pPlayer = new Player(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial(material), vscale, vrot, vpos, 1, m_pGame->m_pController);
            pPlayer->CreateBody(isStatic);
            pPlayer->AddBox(vec2(1, 1), density, issensor, friction, restitution);
            m_pGameObjects.push_back(pPlayer);
            //todo if type == box create box

        }
        if (name == "Ground")
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
            pGround->AddBox(vec2(1, 1), density, issensor, friction, restitution);
            m_pGameObjects.push_back(pGround);
        }
    }


    cJSON_Delete(jRoot);
    delete[] contents;
}
