#ifndef __CactusCam_H__
#define __CactusCam_H__

#include "GameObjects/Camera.h"

class CactusCam : public Camera
{
protected:
    vec3 m_Offset;
    GameObject* m_pObjectFollowing;

    vec3 m_LastPosition;

public:
    CactusCam(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale);
    virtual ~CactusCam();

    virtual void Reset() override;
    virtual void Update(float deltaTime) override;

    void SetObjectToFollow(GameObject* pObject);
};

#endif //__CactusCam_H__
