#pragma once
#include "BaseScene.h"

class Player;
class Camera;
class Game;
class ResourceManager;

class SceneCube : public BaseScene
{
public:
    SceneCube(Game* game);
    ~SceneCube();

    virtual void Init() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void LoadFromFile(const char* filename) override;
    
private:
    Player* m_pPlayer;
    Player* m_pDummy;
    Camera* m_pCamera;
    ResourceManager* m_pResources;

    float m_Timer;
};