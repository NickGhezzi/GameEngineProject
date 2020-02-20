#ifndef __Game_H__
#define __Game_H__

#include "Base/ObjectPool.h"

class Ball;
class BaseScene;
class Camera;
class GameObject;
class Mesh;
class Player;
class PlayerController;
class ResourceManager;

class Game : public fw::GameCore
{
protected:
    fw::ImGuiManager* m_pImGuiManager;

    ResourceManager* m_pResourceManager;

    BaseScene* m_pPhysicsScene;
    BaseScene* m_pActiveScene;

    PlayerController* m_pController;

public:
    Game(fw::Framework* pFramework);
    virtual ~Game();

    virtual void Init() override;
    virtual void OnBeginFrame() override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    ResourceManager* GetResourceManager() { return m_pResourceManager; }
    PlayerController* GetController() { return m_pController; }
};

#endif //__Game_H__
