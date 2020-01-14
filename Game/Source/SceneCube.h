#pragma once
#include "BaseScene.h"

class Player;
class Camera;
class Game;

class SceneCube : public BaseScene
{
public:
    SceneCube(Game* game);
    ~SceneCube();

    virtual void Init() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;


private:
    Player* m_pPlayer;
    Camera* m_pCamera;
};