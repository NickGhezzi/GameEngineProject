#ifndef __GameObject_H__
#define __GameObject_H__

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
    float m_Radius;

    //create physics body
    fw::PhysicsBody* m_pPhysicsBody;

public:
    //swap all vec2 to vec3
    GameObject(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 position);

    ~GameObject();

    vec3 GetPosition() { return m_Position; }
    float GetRadius() { return m_Radius; }

    void SetPosition(vec3 pos) { m_Position = pos; }

    void CreateBody(bool isDynamic);
    void AddCircle(float radius);
    void AddBox(vec3 size);

    virtual void Update(float deltaTime);
    virtual void Draw(Camera* pCamera);

    virtual bool IsColliding(GameObject* pOtherGameObject);
    virtual void OnCollision(GameObject* pOtherGameObject);
};

#endif //__GameObject_H__
