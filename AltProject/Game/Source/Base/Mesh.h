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
    
    void SetupAttributes(Material* pMaterial);
    void SetupUniforms(Material* pMaterial, mat4* worldMatrix, Camera* pCamera, vec2 uvScale, vec2 uvOffset);
    void SetupUniforms(Material* pMaterial, mat4* worldMatrix, Camera* pCamera, vec2 uvScale, vec2 uvOffset, vec3 color);
    void Draw(Material* pMaterial);

    void CreateBox(vec2 size, vec2 offset);
    void CreatePlane(vec2 worldSize, ivec2 vertexCount, vec2 pivotPoint, vec2 uvRepeat);
    void CreateOBJ(const char* objFilename, vec3 scale);
    void CreateRing(float innerradius, float outerradius, int numsegments, ColorByte color);
    void CreateArc(float outerradius, int degrees, int numsegments, ColorByte color);
};

#endif //__Mesh_H__
