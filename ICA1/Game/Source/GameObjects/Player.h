#ifndef __Player_H__
#define __Player_H__

#include "GameObject.h"

class Mesh;
class PlayerController;

class Player : public GameObject
{
protected:
    PlayerController* m_pController;
    int m_PlayerNumber;

public:
    Player(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture);
    ~Player();

    virtual void Update(float deltaTime);
};

#endif //__Player_H__
