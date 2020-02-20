#ifndef __MeatChunkObject_H__
#define __MeatChunkObject_H__

#include "GameObjects/GameObject.h"

class MeatChunkObject : public GameObject
{
protected:

public:
    MeatChunkObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture);
    virtual ~MeatChunkObject();

    virtual void Reset() override;
};

#endif //__MeatChunkObject_H__
