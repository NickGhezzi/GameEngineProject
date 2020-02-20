#ifndef __MeteorObject_H__
#define __MeteorObject_H__

#include "GameObjects/GameObject.h"

class MeteorObject : public GameObject
{
protected:

public:
    MeteorObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture);
    virtual ~MeteorObject();

    virtual void Reset() override;

    virtual void Update(float deltaTime);

    virtual void OnCollision(GameObject* pOtherGameObject, vec3 worldPosition, vec3 worldNormal);
};

#endif //__MeteorObject_H__
