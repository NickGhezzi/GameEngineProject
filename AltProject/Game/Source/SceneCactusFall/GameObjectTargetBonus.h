#ifndef __GameObjectTargetBonus_H__
#define __GameObjectTargetBonus_H__

#include "GameObjects/GameObject.h"

class GameObjectTargetBonus : public GameObject
{
protected:

public:
    GameObjectTargetBonus(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~GameObjectTargetBonus();

    virtual void Update(float deltaTime);
};

#endif //__GameObjectTargetBonus_H__
