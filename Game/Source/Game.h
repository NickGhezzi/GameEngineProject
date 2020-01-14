#ifndef __Game_H__
#define __Game_H__

class Ball;
class Camera;
class GameObject;
class ImGuiManager;
class Mesh;
class Player;
class PlayerController;
class PhysicsWorld;
class BaseScene;
class ResourceManager;

class Game : public fw::GameCore
{
protected:
    ImGuiManager* m_pImGuiManager;

    BaseScene* m_pScenes;

    ResourceManager* m_pResourceManager;

    Player* m_pPlayer;
    Camera* m_pCamera;

    fw::ShaderProgram* m_pShaderTexture;
    Mesh* m_pMeshBox;
    fw::Texture* m_pTexture;

    fw::PhysicsWorld* m_pPhysicsWorld;

public:
    Game(fw::Framework* pFramework);
    virtual ~Game();

    virtual void Init() override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    ResourceManager* GetResourceManager();

    fw::PhysicsWorld* GetPhysicsWorld();

    PlayerController* m_pController;
};

#endif //__Game_H__
