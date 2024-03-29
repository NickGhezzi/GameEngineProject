#pragma once
#include "BaseScene.h"
#include "Base/ObjectPool.h"

class Player;
class GameObject;
class Camera;
class Game;
class ResourceManager;
class HUDElementsScene;


class SortingGameScene : public BaseScene
{
public:
    SortingGameScene(Game* game);
    ~SortingGameScene();

    virtual void Init() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void LoadFromFile(const char* filename) override;
    virtual void OnEvent(fw::Event* pEvent) override;

    void SpawnBall();
    void RemoveBall();
    void Reset();
private:
   // Camera* m_pCamera;
    ResourceManager* m_pResources;
    ObjectPool<GameObject*> m_BallPool;
    HUDElementsScene* m_HUDScene;

    vec3 m_BallSpawnPos;
    int m_Score;
    float m_BallSpawnTimer;
    const float m_BallSpawnTime = 5.0f;
};