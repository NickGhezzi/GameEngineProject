#ifndef __Mesh_H__
#define __Mesh_H__

#include "VertexFormat.h"

class fw::ShaderProgram;
class Camera;
class Material;


class Mesh
{
protected:
    GLuint m_VBO;
    GLuint m_IBO;

    unsigned int m_NumVerts;
    unsigned int m_NumIndices;

    GLenum m_PrimitiveType;

public:
    Mesh();
    ~Mesh();

    void Init(VertexFormat* pVerts, int numVerts, unsigned int* pIndices, int numIndices, GLenum primitiveType, GLenum usage);
    void Init(VertexFormat* pVerts, unsigned int numVerts, GLenum primitiveType);
    //void Draw(Camera* pCamera, fw::ShaderProgram* pShader, vec2 pos, fw::Texture* pTexture);
    void Draw(Camera* pCamera, Material* pMat, vec3 scale, vec3 rotation, vec3 pos);

    void CreateBox(vec2 size, vec2 offset);
    void CreateFloor();
    void CreateCube(vec3 size, vec3 offset);
    void CreatePlane(vec2 size, ivec2 numverts);

    void LoadObjFromFile(const char* filename);
};

#endif //__Mesh_H__
