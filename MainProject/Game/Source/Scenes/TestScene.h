#pragma once
#include "BaseScene.h"

class Player;
class Camera;
class Game;
class ResourceManager;

class TestScene : public BaseScene
{
public:
    TestScene(Game* game);
    ~TestScene();

    virtual void Init() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void LoadFromFile(const char* filename) override;

private:
    Player* m_pPlayer;
    GameObject* m_pFloor;
    Camera* m_pCamera;
    ResourceManager* m_pResources;
};