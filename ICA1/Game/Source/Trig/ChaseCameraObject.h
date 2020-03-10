#ifndef __ChaseCameraObject_H__
#define __ChaseCameraObject_H__

#include "GameObjects/Camera.h"

class ChaseCameraObject : public Camera
{
protected:
    GameObject* m_ObjectFollowing;
    float m_Distance;
    float m_Angle;

public:
    ChaseCameraObject(BaseScene* pScene, vec3 pos);
    virtual ~ChaseCameraObject();

    virtual void Update(float deltaTime) override;

    void SetObjectToFollow(GameObject* pObject, float dist) { m_ObjectFollowing = pObject; m_Distance = dist; }
};

#endif //__ChaseCameraObject_H__
