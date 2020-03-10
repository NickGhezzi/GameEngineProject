#ifndef __TrigPickup_H__
#define __TrigPickup_H__

#include "GameObjects/GameObject.h"

class TrigPickup : public GameObject
{
protected:

public:
    TrigPickup(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture);
    virtual ~TrigPickup();

    virtual void Update(float deltaTime) override;
};

#endif //__TrigPickup_H__
