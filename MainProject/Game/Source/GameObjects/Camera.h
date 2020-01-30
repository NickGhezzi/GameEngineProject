#ifndef __Camera_H__
#define __Camera_H__

#include "GameObject.h"

class Game;
class BaseScene;

struct ViewProperties
{
    ViewProperties() { eye = vec3(0, 0, 0);  up = vec3(0, 0, 0); at = vec3(0, 0, 0); };
   ViewProperties(vec3 e, vec3 u, vec3 a) { eye = e; up = u; at = a; };

   vec3 eye;
   vec3 up;
   vec3 at;
};

struct ProjectionProperties
{
    ProjectionProperties() { fov = 0; aspect = 0; nearzy = 0; farzy = 0; };
    ProjectionProperties(float f, float as, float n, float fer) { fov = f; aspect = as; nearzy = n; farzy = fer; };

    float fov;
    float aspect;
    float nearzy;
    float farzy;
};

class Camera : public GameObject
{
protected:
    vec2 m_ProjectionScale;
    mat4 m_ProjectionMatrix;
    mat4 m_ViewMatrix;
    mat4 m_WorldMatrix;
    ViewProperties m_ViewProperties;
    ProjectionProperties m_ProjectionProperties;

public:
    Camera(BaseScene* m_pScene, vec3 position, vec2 projectionScale);
    ~Camera();

    virtual void Update(float deltaTime) override;

    mat4 GetProjectionMatrix();
    mat4 GetViewMatrix();
    mat4 GetWorldMatrix();

    void Init(ViewProperties view, ProjectionProperties proj);
};

#endif //__Camera_H__
