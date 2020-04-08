#ifndef __ElevatorObject_H__
#define __ElevatorObject_H__

#include "GameObjects/GameObject.h"

class ElevatorObject : public GameObject
{
protected:
    GameObject* m_Sensor;
public:
    ElevatorObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~ElevatorObject();

    virtual void Reset();

    virtual void Update(float deltaTime);

    void CreateJointAndSensor();
    void EnableMotor();

};

#endif //__ElevatorObject_H__
