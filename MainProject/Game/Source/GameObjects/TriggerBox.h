#pragma once
#include "GameObject.h"

class Mesh;

class TriggerBox : public GameObject
{
protected:

   
public:
    TriggerBox(BaseScene* m_pScene, vec3 scale, vec3 rotation, vec3 position);
    ~TriggerBox();

};