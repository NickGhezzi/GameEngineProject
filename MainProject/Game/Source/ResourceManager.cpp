#include "GamePCH.h"
#include "ResourceManager.h"
#include "Base/Material.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for (auto g : m_Shaders)
    {
        if (g.second != nullptr)
        delete g.second; 
    }

    for (auto g : m_Textures)
    {
        if(g.second != nullptr)
        delete g.second; 
    }

    for (auto g : m_Meshes)
    {
        if (g.second != nullptr)
            delete g.second; 
    }

    for (auto g : m_Materials)
    {
        if (g.second != nullptr)
            delete g.second;
    }

    m_Textures.clear();
    m_Shaders.clear();
    m_Meshes.clear();
    m_Materials.clear();
}

void ResourceManager::AddTexture(std::string name, fw::Texture* pTexture)
{
    m_Textures[name] = pTexture;
}

fw::Texture* ResourceManager::GetTexture(std::string name)
{
    if (m_Textures.find(name) != m_Textures.end())
    {
        return m_Textures[name];
    }
    
    assert(m_Textures.find(name) == m_Textures.end());
}

void ResourceManager::AddShader(std::string name, fw::ShaderProgram* pShader)
{
    m_Shaders[name] = pShader;
}

fw::ShaderProgram* ResourceManager::GetShader(std::string name)
{
    if (m_Shaders.find(name) != m_Shaders.end())
    {
        return m_Shaders[name];
    }

    assert(m_Shaders.find(name) == m_Shaders.end());
}

Mesh* ResourceManager::AddMesh(std::string name, Mesh* pmesh)
{
    m_Meshes[name] = pmesh;
    return pmesh;
}

Mesh* ResourceManager::GetMesh(std::string name)
{
    if (m_Meshes.find(name) != m_Meshes.end())
    {
        return m_Meshes[name];
    }

    assert(m_Meshes.find(name) == m_Meshes.end());
}

void ResourceManager::AddMaterial(std::string name, Material* pmat)
{
    m_Materials[name] = pmat;
}

Material* ResourceManager::GetMaterial(std::string name)
{
    if (m_Materials.find(name) != m_Materials.end())
    {
        return m_Materials[name];
    }

    assert(m_Materials.find(name) == m_Materials.end());
}
