#ifndef __BaseScene_H__
#define __BaseScene_H__

class GameObject;
class Camera;
class Game;

class BaseScene
{
protected:
    Game* m_pGame;

    fw::PhysicsWorld* m_pPhysicsWorld;
    Camera* m_pCamera;

    std::vector<GameObject*> m_Objects;

public:
    BaseScene(Game* pGame);
    virtual ~BaseScene();

    virtual void Init();
    virtual void OnEvent(fw::Event* pEvent);
    virtual void Reset();
    virtual void Update(float deltaTime);
    virtual void Draw();

    void AddObjectToScene(GameObject* pObj);
    bool IsInScene(GameObject* pObj);
    void RemoveObjectFromScene(GameObject* pObj);

    GameObject* GetGameObjectByName(std::string name);

    Game* GetGame() { return m_pGame; }
    fw::PhysicsWorld* GetPhysicsWorld() { return m_pPhysicsWorld; }

    Camera* GetCamera() { return m_pCamera; }
};

#endif //__BaseScene_H__
