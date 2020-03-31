#ifndef __GameObject_H__
#define __GameObject_H__

class Game;
class Mesh;
template<class T> class ObjectPool;
class BaseScene;
class Camera;

class GameObject
{
protected:
    BaseScene* m_pScene;

    std::string m_Name;
    Mesh* m_pMesh;
    fw::ShaderProgram* m_pShader;
    fw::Texture* m_pTexture;
    fw::PhysicsBody* m_pBody;
    ObjectPool<GameObject*>* m_pPoolWeCameFrom;

    vec3 m_Position;
    vec3 m_Rotation;
    vec3 m_Scale;

    vec3 m_InitialPosition;
    vec3 m_InitialRotation;
    vec3 m_InitialScale;

public:
    GameObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture);
    ~GameObject();

    std::string GetName() { return m_Name; }
    vec3 GetPosition() { return m_Position; }
    vec3 GetRotation() { return m_Rotation; }
    vec3 GetScale() { return m_Scale; }

    void SetPosition(vec3 pos) { m_Position = pos; }
    void SetRotation(vec3 rot) { m_Rotation = rot; }
    void SetScale(vec3 scale) { m_Scale = scale; }

    virtual void Update(float deltaTime);
    virtual void Draw(Camera* pCamera, vec3 lightcolor);

    virtual void Reset();
    void RemoveFromSceneAndReturnToPool();

    void SetPool(ObjectPool<GameObject*>* pPool) { m_pPoolWeCameFrom = pPool; }

    void CreateBody(bool isDynamic);
    fw::PhysicsBody* GetBody() { return m_pBody; }

    virtual void OnCollision(GameObject* pOtherGameObject, vec3 worldPosition, vec3 worldNormal);
};

#endif //__GameObject_H__
