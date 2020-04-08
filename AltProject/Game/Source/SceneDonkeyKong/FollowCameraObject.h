#ifndef __FollowCameraObject_H__
#define __FollowCameraObject_H__

#include "GameObjects/Camera.h"

class FollowCameraObject : public Camera
{
protected:
    GameObject* m_ObjectFollowing;
    float m_ClosestZ;

public:
    FollowCameraObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale);
    virtual ~FollowCameraObject();

    virtual void Update(float deltaTime);

    void SetObjectToFollow(GameObject* pObject, float closestz) { m_ObjectFollowing = pObject; m_ClosestZ = closestz; }
};

#endif //__FollowCameraObject_H__
