#pragma once

class Game;

class BaseScene
{
public:
    BaseScene(Game* game) { m_pGame = game; };
    virtual ~BaseScene() {};

    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

    virtual Game* GetGame() { return m_pGame; };
    
    void LoadFromFile(const char* filename)
    {
        char* contents = LoadCompleteFile(filename, nullptr);

        cJSON* jRoot = cJSON_Parse(contents);

        cJSON* jGameObjectArray = cJSON_GetObjectItem(jRoot, "GameObjects");

        int numGameObjects =  cJSON_GetArraySize(jGameObjectArray);
        for (int i = 0; i < numGameObjects; i++)
        {
            cJSON* jGameObject = cJSON_GetArrayItem(jGameObjectArray, i);
            //TODO pull properties from jGameObject
        }


        cJSON_Delete(jRoot);
        delete[] contents;
    };

protected:
    Game* m_pGame;
};