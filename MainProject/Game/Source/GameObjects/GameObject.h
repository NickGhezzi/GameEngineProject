#ifndef __GameObject_H__
#define __GameObject_H__
#include "Base/ObjectPool.h"

class Game;
class BaseScene;
class Mesh;
class Material;
class Camera;

enum class ColorType
{
    Red = 0,
    Green,
    Blue
};


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

    std::string m_Name;
public:
    //TODO:: Add std::string tag or name to constructor
    GameObject(BaseScene* m_pScene,Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position);

    ~GameObject();

    vec3 GetPosition() { return m_Position; }
    float GetRotation() { return m_Rotation.z; }
    float GetRadius() { return m_Radius; }
    std::string GetName();

    void SetScale(vec3 scale) { m_Scale = scale; }
    void SetRotation(float rot) { m_pPhysicsBody->SetRotation(rot); }
    void SetPosition(vec3 pos) { m_pPhysicsBody->SetPosition(pos); }
    void SetName(std::string name) { m_Name = name; }

    void CreateBody(bool isStatic);
    fw::PhysicsBody* GetBody();
    void AddCircle(float radius);
    void AddBox(vec3 size, float density, bool isSensor, float friction, float restitution);
    void AddJoint(GameObject* thingtoattach, vec2 pos);
    void AddJointWithRestraint(GameObject* thingtoattach, vec2 pos, float minangle, float maxangle);

    virtual void Update(float deltaTime);
    virtual void Draw(Camera* pCamera);

    virtual bool IsColliding(GameObject* pOtherGameObject);
    virtual void OnCollision(GameObject* pOtherGameObject);

    void SetPoolWhereWeCameFrom(ObjectPool<GameObject*>* obj);

    bool bHasCollided;
};

#endif //__GameObject_H__
