#include "GamePCH.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for (auto g : m_Textures)
    {
        delete g.second; //second is the texture pointer, first is the string
    }

    for (auto g : m_Shaders)
    {
        delete g.second; //second is the texture pointer, first is the string
    }

    m_Textures.clear();
    m_Shaders.clear();
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

void ResourceManager::AddMesh(std::string name, Mesh* pmesh)
{
    m_Meshes[name] = pmesh;
}

Mesh* ResourceManager::GetMesh(std::string name)
{
    if (m_Meshes.find(name) != m_Meshes.end())
    {
        return m_Meshes[name];
    }

    assert(m_Meshes.find(name) == m_Meshes.end());
}
