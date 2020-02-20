#ifndef __SheepTitleCard_H__
#define __SheepTitleCard_H__

#include "GameObjects/GameObject.h"

class SheepTitleCard : public GameObject
{
protected:
    float m_TimeAlive;

public:
    SheepTitleCard(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture);
    virtual ~SheepTitleCard();

    virtual void Reset();

    virtual void Update(float deltaTime);

    void Display();
};

#endif //__SheepTitleCard_H__
