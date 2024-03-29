#pragma once
#include "BaseScene.h"

class Camera;
class Game;
class ResourceManager;

class ScenePhysics : public BaseScene
{
public:
    ScenePhysics(Game* game);
    ~ScenePhysics();

    virtual void Init() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void LoadFromFile(const char* filename) override;

private:
    ResourceManager* m_pResources;
    Camera* m_pCamera;
};