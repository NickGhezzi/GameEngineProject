#pragma once

class Game;
class GameObject;
class Camera;

class BaseScene
{
public:
    BaseScene(Game* game);
    virtual ~BaseScene();

    virtual void Init() = 0;
    virtual void Update(float deltaTime) ;
    virtual void Draw();
    virtual void LoadFromFile(const char* filename);

    virtual void AddObjectToScene(GameObject* pObj);
    virtual void RemoveObjectFromScene(GameObject* pObj);

    virtual void OnEvent(fw::Event* pEvent);

    virtual Game* GetGame();
    virtual fw::PhysicsWorld* GetPhysicsWorld();

protected:
    Game* m_pGame;
    fw::PhysicsWorld* m_pPhysicsWorld;
    Camera* m_pCamera;
    std::vector<GameObject*> m_pGameObjects;
    //add camera 

};