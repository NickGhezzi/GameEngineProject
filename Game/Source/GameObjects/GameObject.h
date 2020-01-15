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
   // fw::ShaderProgram* m_pShader;
    //fw::Texture* m_pTexture;
    Material* m_pMaterial;
    vec2 m_Position;
    float m_Radius;

public:
    //GameObject(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 position);
    //GameObject(BaseScene* m_pScene, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 position);
    GameObject(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec2 position);


    ~GameObject();

    vec2 GetPosition() { return m_Position; }
    float GetRadius() { return m_Radius; }

    void SetPosition(vec2 pos) { m_Position = pos; }

    virtual void Update(float deltaTime);
    virtual void Draw(Camera* pCamera);

    virtual bool IsColliding(GameObject* pOtherGameObject);
    virtual void OnCollision(GameObject* pOtherGameObject);
};

#endif //__GameObject_H__
