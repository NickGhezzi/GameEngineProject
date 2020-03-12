#pragma once
#include "BaseScene.h"

class Camera;
class Game;
class ResourceManager;

class HUDElementsScene : public BaseScene
{
public:
    HUDElementsScene(Game* game);
    ~HUDElementsScene();

    virtual void Init() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void UpdateScore(int score);
    void AddHUDElement(GameObject* element);
private:
    ResourceManager* m_pResources;
    Camera* m_pHUDCamera;

    GameObject* m_pScore[10];
    GameObject* m_pScore2[10];

    int m_Score1;
    int m_Score2;
};