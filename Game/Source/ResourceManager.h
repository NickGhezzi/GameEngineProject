#pragma once
#include <string>
#include <map>

class Mesh;

//TODO add materials

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    void AddTexture(std::string name, fw::Texture* pTexture); // init textures in game
    fw::Texture* GetTexture(std::string name);

    void AddShader(std::string name, fw::ShaderProgram* pShader); // init shaders in game
    fw::ShaderProgram* GetShader(std::string name);

    void AddMesh(std::string name, Mesh* pmesh); // init shaders in game
    Mesh* GetMesh(std::string name);

private:
    std::map<std::string, fw::Texture*> m_Textures;
    std::map<std::string, fw::ShaderProgram*> m_Shaders;
    std::map<std::string, Mesh*> m_Meshes;
};
