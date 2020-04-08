#ifndef __SceneDonkeyKong_H__
#define __SceneDonkeyKong_H__

#include "Scenes/BaseScene.h"
#include "Base/ObjectPool.h"

class SceneDonkeyKong : public BaseScene
{
public:
    static const float TIME_BEFORE_INITIAL_BARREL_SPAWN;
    static const float TIME_BETWEEN_BARREL_SPAWNS;
    static const int NUM_BARRELS_IN_POOL;

protected:
    ObjectPool<GameObject*> m_BarrelPool;

    float m_BarrelSpawnTimer;
    int m_Score;

public:
    SceneDonkeyKong(Game* pGame);
    virtual ~SceneDonkeyKong() override;

    virtual void Init() override;

    virtual void Reset() override;

    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__Scene_H__
