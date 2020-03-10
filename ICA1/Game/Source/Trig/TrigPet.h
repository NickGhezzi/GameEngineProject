#ifndef __TrigPet_H__
#define __TrigPet_H__

#include "GameObjects/GameObject.h"

class TrigPet : public GameObject
{
protected:
    GameObject* m_pObjectWeAreFollowing;

public:
    TrigPet(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture);
    virtual ~TrigPet();

    virtual void Update(float deltaTime) override;

    void SetObjectToFollow(GameObject* pObject);
};

#endif //__GameObjectPet_H__
