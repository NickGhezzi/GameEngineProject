#pragma once

class Game;

class BaseScene
{
public:
    BaseScene(Game* game) { m_pGame = game; };
    virtual ~BaseScene() {};

    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

    virtual Game* GetGame() { return m_pGame; };
protected:
    Game* m_pGame;
};