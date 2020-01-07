#ifndef __Camera_H__
#define __Camera_H__

#include "GameObject.h"

class Game;

class Camera : public GameObject
{
protected:
    vec2 m_ProjectionScale;

public:
    Camera(Game* pGame, vec2 position, vec2 projectionScale);
    ~Camera();

    vec2 GetProjectionScale() { return m_ProjectionScale; }
};

#endif //__Camera_H__
