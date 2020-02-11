#ifndef __Game_H__
#define __Game_H__

//TODO:: Move Physics world into theyre repective scene
//TODO:: get debug draw working


class Ball;
class Camera;
class GameObject;
class Mesh;
class Player;
class PlayerController;
class PhysicsWorld;
class BaseScene;
class ResourceManager;
class Material;

class Game : public fw::GameCore
{
protected:
    fw::ImGuiManager* m_pImGuiManager;

    BaseScene* m_pCurrentScene;
    BaseScene* m_pSceneWater;
    BaseScene* m_pSceneCube;
    BaseScene* m_pScenePhysics;
    BaseScene* m_pBoxStackingScene;

    ResourceManager* m_pResourceManager;

    fw::PhysicsWorld* m_pPhysicsWorld;

public:
    Game(fw::Framework* pFramework);
    virtual ~Game();

    virtual void Init() override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    ResourceManager* GetResourceManager();

    fw::PhysicsWorld2D* GetPhysicsWorld();
    fw::Framework* GetFramework();

    PlayerController* m_pController;
};

#endif //__Game_H__
