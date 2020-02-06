#pragma once

#include "BaseScene.h"
#include "Base/ObjectPool.h"

class Player;
class Camera;
class Game;
class ResourceManager;


class BoxStackingScene : public BaseScene
{
public:
    BoxStackingScene(Game* game);
    ~BoxStackingScene();

    virtual void Init() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void LoadFromFile(const char* filename) override;

private:
    Camera* m_pCamera;
    ResourceManager* m_pResources;
    ObjectPool<GameObject*> m_ObjectPool;
};