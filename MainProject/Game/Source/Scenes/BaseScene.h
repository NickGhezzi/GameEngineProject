#pragma once

class Game;
class GameObject;

class BaseScene
{
public:
    BaseScene(Game* game);
    virtual ~BaseScene();

    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    virtual void LoadFromFile(const char* filename) = 0;

    virtual void AddObjectToScene(GameObject* pObj);
    virtual void RemoveObjectFromScene(GameObject* pObj);


    virtual Game* GetGame();
    

protected:
    Game* m_pGame;
    std::vector<GameObject*> m_pGameObjects;

};