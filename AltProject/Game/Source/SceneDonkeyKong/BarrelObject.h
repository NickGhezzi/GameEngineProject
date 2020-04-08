#ifndef __BarrelObject_H__
#define __BarrelObject_H__

#include "GameObjects/GameObject.h"
#include "Base/ObjectPool.h"

class BarrelObject : public GameObject
{
protected:
    ObjectPool<GameObject*>* m_pPool;

public:
    BarrelObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~BarrelObject();

    virtual void Reset();
    virtual void RemoveFromSceneAndReturnToPool();

    virtual void Update(float deltaTime);

    void SetPool(ObjectPool<GameObject*>* pPool) { m_pPool = pPool; m_pPoolWeCameFrom = pPool; }

    void Destroy();

    bool m_JumpedOver;
};

#endif //__BarrelObject_H__
