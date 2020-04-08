#ifndef __GameObject_H__
#define __GameObject_H__

class Game;
class Mesh;
template<class T> class ObjectPool;
class BaseScene;
class Camera;
class Material;

enum PhysicsCategories
{
    PhysicsCategory_Default = 0x0001,
    PhysicsCategory_Environment = 0x0002,
    PhysicsCategory_Player = 0x0004,
    PhysicsCategory_Barrel = 0x0008,
    PhysicsCategory_Hammer = 0x00010,

};

class GameObject
{
protected:
    BaseScene* m_pScene;

    std::string m_Name;
    Mesh* m_pMesh;
    Material* m_pMaterial;
    fw::PhysicsBody* m_pBody;
    ObjectPool<GameObject*>* m_pPoolWeCameFrom;

    vec3 m_Position;
    vec3 m_Rotation;
    vec3 m_Scale;

    vec2 m_UVScale;
    vec2 m_UVOffset;

    vec3 m_InitialPosition;
    vec3 m_InitialRotation;
    vec3 m_InitialScale;

public:
    GameObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~GameObject();

    std::string GetName() { return m_Name; }
    vec3 GetPosition() { return m_Position; }
    vec3 GetRotation() { return m_Rotation; }
    vec3 GetScale() { return m_Scale; }

    void SetPosition(vec3 pos) { m_Position = pos; }
    void SetRotation(vec3 rot) { m_Rotation = rot; }
    void SetScale(vec3 scale) { m_Scale = scale; }
    void SetUVScaleAndOffset(vec2 uvScale, vec2 uvOffset);

    virtual void Update(float deltaTime);
    virtual void Draw(Camera* pCamera);

    virtual void Reset();
    virtual void RemoveFromSceneAndReturnToPool();

    void SetPool(ObjectPool<GameObject*>* pPool) { m_pPoolWeCameFrom = pPool; }

    void CreateBody(bool isDynamic);
    fw::PhysicsBody* GetBody() { return m_pBody; }

    virtual void OnCollision(GameObject* pOtherGameObject, vec3 worldPosition, vec3 worldNormal);
};

#endif //__GameObject_H__
