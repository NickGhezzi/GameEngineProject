#ifndef __TrigPlayer_H__
#define __TrigPlayer_H__

#include "GameObjects/GameObject.h"

class PlayerController;

class TrigPlayer : public GameObject
{
protected:
    PlayerController* m_pController;

public:
    TrigPlayer(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture);
    virtual ~TrigPlayer();

    void SetController(PlayerController* pController);

    virtual void Update(float deltaTime) override;
};

#endif //__TrigPlayer_H__
