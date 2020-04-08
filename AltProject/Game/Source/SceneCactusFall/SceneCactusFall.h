#ifndef __SceneCactusFall_H__
#define __SceneCactusFall_H__

#include "Scenes/BaseScene.h"

class ResourceManager;

class SceneCactusFall : public BaseScene
{
protected:
    float m_Score;
    bool m_TestMode;

public:
    SceneCactusFall(Game* pGame);
    virtual ~SceneCactusFall() override;

    virtual void Init() override;

    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    bool IsInTestMode() { return m_TestMode; }
    void SetScore(float value) { m_Score = value; }
    void AddScore(float value) { m_Score += value; }
    float GetScore() { return m_Score; }
};

#endif //__SceneCactusFall_H__
