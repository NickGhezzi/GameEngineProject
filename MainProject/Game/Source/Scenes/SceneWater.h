#pragma once
#include "BaseScene.h"

class Player;
class Camera;
class Game;
class ResourceManager;

class SceneWater : public BaseScene
{
public:
    SceneWater(Game* game);
    ~SceneWater();

    virtual void Init() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void LoadFromFile(const char* filename) override;
private:
    Player* m_pWater;
    Camera* m_pCamera;
    ResourceManager* m_pResources;
};