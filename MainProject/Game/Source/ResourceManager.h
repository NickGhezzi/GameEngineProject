#pragma once
#include <string>
#include <map>

class Mesh;
class Material;


class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    void AddTexture(std::string name, fw::Texture* pTexture); // init textures in game
    fw::Texture* GetTexture(std::string name);

    void AddShader(std::string name, fw::ShaderProgram* pShader); // init shaders in game
    fw::ShaderProgram* GetShader(std::string name);

    Mesh* AddMesh(std::string name, Mesh* pmesh); // init meshes in game
    Mesh* GetMesh(std::string name);


    void AddMaterial(std::string name, Material* pmat); // init materials in game
    Material* GetMaterial(std::string name);


private:
    std::map<std::string, fw::Texture*> m_Textures;
    std::map<std::string, fw::ShaderProgram*> m_Shaders;
    std::map<std::string, Mesh*> m_Meshes;
    std::map<std::string, Material*> m_Materials;
};
