#ifndef __ResourceManager_H__
#define __ResourceManager_H__

class ResourceManager;
class Mesh;
class SoundObject;

class ResourceManager
{
protected:
    std::map<std::string, Mesh*> m_pMeshes;
    std::map<std::string, fw::ShaderProgram*> m_pShaders;
    std::map<std::string, fw::Texture*> m_pTextures;
    std::map<std::string, SoundObject*> m_pSoundObjects;

public:
    ResourceManager();
    virtual ~ResourceManager();

    void AddMesh(const char* name, Mesh* pMesh) { m_pMeshes[name] = pMesh; }
    void AddShader(const char* name, fw::ShaderProgram* pShader) { m_pShaders[name] = pShader; }
    void AddTexture(const char* name, fw::Texture* pTextureObject) { m_pTextures[name] = pTextureObject; }
    void AddSoundObject(const char* name, SoundObject* pSoundObject) { m_pSoundObjects[name] = pSoundObject; }

    Mesh* GetMesh(const char* name) { return m_pMeshes[name]; }
    fw::ShaderProgram* GetShader(const char* name) { return m_pShaders[name]; }
    fw::Texture* GetTexture(const char* name) { return m_pTextures[name]; }
    SoundObject* GetSoundObject(const char* name) { return m_pSoundObjects[name]; }
};

#endif //__ResourceManager_H__
