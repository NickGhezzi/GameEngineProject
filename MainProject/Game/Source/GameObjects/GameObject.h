#ifndef __GameObject_H__
#define __GameObject_H__
#include "Base/ObjectPool.h"

class Game;
class BaseScene;
class Mesh;
class Material;

class GameObject
{
protected:
    BaseScene* m_pScene;
    Mesh* m_pMesh;
    Material* m_pMaterial;
    vec3 m_Position;
    vec3 m_Rotation;
    vec3 m_Scale;
    float m_Radius;

    //create physics body
    fw::PhysicsBody* m_pPhysicsBody;

    ObjectPool<GameObject*>* m_pPoolWeCameFrom;

public:
    //swap all vec2 to vec3
    GameObject(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position);

    ~GameObject();

    vec3 GetPosition() { return m_Position; }
    float GetRadius() { return m_Radius; }

    void SetScale(vec3 scale) { m_Scale = scale; }
    void SetRotation(vec3 rot) { m_Rotation = rot; }
    void SetPosition(vec3 pos) { m_Position = pos; }

    void CreateBody(bool isStatic);
    fw::PhysicsBody* GetBody();
    void AddCircle(float radius);
    void AddBox(vec3 size, float density, bool isSensor, float friction, float restitution);
    void AddJoint(GameObject* thingtoattach, vec2 pos);

    virtual void Update(float deltaTime);
    virtual void Draw(Camera* pCamera);

    virtual bool IsColliding(GameObject* pOtherGameObject);
    virtual void OnCollision(GameObject* pOtherGameObject);

    void SetPoolWhereWeCameFrom(ObjectPool<GameObject*>* obj);
};

#endif //__GameObject_H__
