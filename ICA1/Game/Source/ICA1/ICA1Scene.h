#ifndef __ICA1Scene_H__
#define __ICA1Scene_H__

#include "Base/ObjectPool.h"
#include "Scenes/BaseScene.h"

class Game;
class GameObject;
class SheepObject;
class SheepTitleCard;

class ICA1Scene : public BaseScene
{
    static const float INITIAL_PROJECTILE_SPAWN_DELAY;
    static const float TIME_BETWEEN_PROJECTILE_SPAWNS;
    static const int NUM_PROJECTILES_IN_POOL;
    static const int NUM_MEAT_CHUNKS_IN_POOL;

protected:
    ObjectPool<GameObject*> m_ProjectilePool;
    ObjectPool<GameObject*> m_MeatChunkPool;

    SheepObject* m_pSheep;
    SheepTitleCard* m_pTitle;
    SheepTitleCard* m_pWin;
    SheepTitleCard* m_pLose;

    float m_ProjectileSpawnTimer;

public:
    ICA1Scene(Game* pGame);
    virtual ~ICA1Scene();

    virtual void Init();
    virtual void OnEvent(fw::Event* pEvent);
    virtual void Reset();
    virtual void Update(float deltaTime);
    virtual void Draw();

    void SpawnMeatChunks(vec3 spawnPos, unsigned int numChunks);

    SheepTitleCard* GetTitle() { return m_pTitle; }
    SheepTitleCard* GetWin()   { return m_pWin; }
    SheepTitleCard* GetLose()  { return m_pLose; }
};

#endif //__Scene_H__
