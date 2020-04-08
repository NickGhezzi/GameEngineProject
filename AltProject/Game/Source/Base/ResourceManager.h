#ifndef __ResourceManager_H__
#define __ResourceManager_H__

class ResourceManager;
class Mesh;

class Material
{
public:
    fw::ShaderProgram* m_pShader;
    fw::Texture* m_pTexture;

public:
    Material(fw::ShaderProgram* pShader, fw::Texture* pTexture)
        : m_pShader( pShader ), m_pTexture( pTexture ) {}
    fw::ShaderProgram* GetShader() { return m_pShader; }
    fw::Texture* GetTexture() { return m_pTexture; }
};

class ResourceManager
{
protected:
    std::map<std::string, Mesh*> m_pMeshes;
    std::map<std::string, fw::ShaderProgram*> m_pShaders;
    std::map<std::string, fw::Texture*> m_pTextures;
    std::map<std::string, Material*> m_pMaterials;

public:
    ResourceManager();
    virtual ~ResourceManager();

    Mesh* AddMesh(const char* name, Mesh* pMesh) { m_pMeshes[name] = pMesh; return pMesh; }
    void AddShader(const char* name, fw::ShaderProgram* pShader) { m_pShaders[name] = pShader; }
    void AddTexture(const char* name, fw::Texture* pTextureObject) { m_pTextures[name] = pTextureObject; }
    void AddMaterial(const char* name, Material* pMaterial) { m_pMaterials[name] = pMaterial; }

    Mesh* GetMesh(const char* name) { return m_pMeshes[name]; }
    fw::ShaderProgram* GetShader(const char* name) { return m_pShaders[name]; }
    fw::Texture* GetTexture(const char* name) { return m_pTextures[name]; }
    Material* GetMaterial(const char* name) { return m_pMaterials[name]; }
};

#endif //__ResourceManager_H__
