#include "GamePCH.h"

#include "Base/Mesh.h"
#include "Base/VertexFormat.h"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"
#include "ResourceManager.h"
#include "Base/OBJLoader.h"

using namespace fw;

Mesh::Mesh()
{
    m_VBO = 0;

    m_PrimitiveType = -1;
    m_NumVerts = 0;
}
    
Mesh::~Mesh()
{
    glDeleteBuffers( 1, &m_VBO );
}

void Mesh::Init(VertexFormat* pVerts, int numVerts, unsigned int* pIndices, int numIndices, GLenum primitiveType, GLenum usage)
{
    m_NumVerts = numVerts;
    m_NumIndices = numIndices;
    m_PrimitiveType = primitiveType;

    // Generate and fill buffer with our vertex attributes.
    glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*numVerts, pVerts, usage );

    // Generate and fill buffer with our indices.
    if( pIndices )
    {
        glGenBuffers( 1, &m_IBO );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*numIndices, pIndices, usage );
    }
}

void Mesh::Init(VertexFormat* pVerts, unsigned int numVerts, GLenum primitiveType)
{
    Init( pVerts, numVerts, nullptr, 0, primitiveType, GL_STATIC_DRAW );
}

void SetUniformMatrix(GLuint shader, char* name, mat4* pMat)
{
    GLint location = glGetUniformLocation( shader, name );
    if( location != -1 )
    {
        glUniformMatrix4fv( location, 1, false, &pMat->m11 );
    }
}

void SetUniform1f(GLuint shader, const char* uniformName, float value)
{
    GLint loc = glGetUniformLocation( shader, uniformName );
    if( loc != -1 )
    {
        glUniform1f( loc, value );
    }
}

void SetUniform2f(GLuint shader, const char* uniformName, vec2 value)
{
    GLint loc = glGetUniformLocation( shader, uniformName );
    if( loc != -1 )
    {
        glUniform2f( loc, value.x, value.y );
    }
}

void SetUniform3f(GLuint shader, const char* uniformName, vec3 value)
{
    GLint loc = glGetUniformLocation( shader, uniformName );
    if( loc != -1 )
    {
        glUniform3f( loc, value.x, value.y, value.z );
    }
}

void Mesh::SetupAttributes(Material* pMaterial)
{
    assert( m_VBO != 0 );
    assert( pMaterial != nullptr );
    assert( pMaterial->GetShader() != nullptr );
    assert( pMaterial->GetShader()->GetProgram() != 0 );

    GLuint shader = pMaterial->GetShader()->GetProgram();

    // Bind buffer and set up attributes.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );

    GLint loc = glGetAttribLocation( shader, "a_Position" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, 24, (void*)0 );
        glEnableVertexAttribArray( loc );
    }

    loc = glGetAttribLocation( shader, "a_Color" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, 24, (void*)12 );
        glEnableVertexAttribArray( loc );
    }

    loc = glGetAttribLocation( shader, "a_UV" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 24, (void*)16 );
        glEnableVertexAttribArray( loc );
    }
}

void Mesh::SetupUniforms(Material* pMaterial, mat4* worldMatrix, Camera* pCamera, vec2 uvScale, vec2 uvOffset)
{
    assert( pMaterial != nullptr );
    assert( pMaterial->GetShader() != nullptr );
    assert( pMaterial->GetShader()->GetProgram() != 0 );
    assert( pCamera != nullptr );

    GLuint shader = pMaterial->GetShader()->GetProgram();

    // Set up shader.
    glUseProgram( shader );

    // Set up uniforms.
    SetUniformMatrix( shader, "u_WorldMatrix", worldMatrix );
    SetUniformMatrix( shader, "u_ViewMatrix", pCamera->GetView() );
    SetUniformMatrix( shader, "u_ProjectionMatrix", pCamera->GetProj() );

    if( uvScale.x < 1 )
        int bp = 1;
    SetUniform2f( shader, "u_UVScale", uvScale );
    SetUniform2f( shader, "u_UVOffset", uvOffset );

    SetUniform1f( shader, "u_Time", (float)GetSystemTimeSinceGameStart() );

    // Setup our texture.
    Texture* pTexture = pMaterial->GetTexture();
    if( pTexture != nullptr )
    {
        int textureUnitIndex = 0;
        glActiveTexture( GL_TEXTURE0 + textureUnitIndex );
        glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureID() );
        GLint loc = glGetUniformLocation( shader, "u_TextureSampler" );
        if( loc != -1 )
        {
            glUniform1i( loc, textureUnitIndex );
        }
    }
}

void Mesh::Draw(Material* pMaterial)
{
    assert( m_PrimitiveType != -1 );
    assert( m_NumVerts != 0 );
    assert( pMaterial != nullptr );
    assert( pMaterial->GetShader() != nullptr );
    assert( pMaterial->GetShader()->GetProgram() != 0 );

    // Draw.
    if( m_NumIndices > 0 )
    {
        glDrawElements( m_PrimitiveType, m_NumIndices, GL_UNSIGNED_INT, 0 );
    }
    else
    {
        glDrawArrays( m_PrimitiveType, 0, m_NumVerts );
    }

    // Disable the attribute arrays used.
    {
        GLuint shader = pMaterial->GetShader()->GetProgram();

        GLint aPos = glGetAttribLocation( shader, "a_Position" );
        GLint aColor = glGetAttribLocation( shader, "a_Color" );
        GLint aUV = glGetAttribLocation( shader, "a_UV" );

        glDisableVertexAttribArray( aPos );

        if( aColor != -1 )
            glDisableVertexAttribArray( aColor );

        if( aUV != -1 )
            glDisableVertexAttribArray( aUV );
    }
}

void Mesh::CreateBox(vec2 size, vec2 offset)
{
    // ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
    assert( m_VBO == 0 );

    VertexFormat vertexAttributes[] =
    {
        VertexFormat( vec2( -size.x/2, -size.y/2 ) + offset, ColorByte( 255, 255, 255, 255 ), vec2( 0.0f, 0.0f ) ),
        VertexFormat( vec2( -size.x/2,  size.y/2 ) + offset, ColorByte( 255, 255, 255, 255 ), vec2( 0.0f, 1.0f ) ),
        VertexFormat( vec2(  size.x/2,  size.y/2 ) + offset, ColorByte( 255, 255, 255, 255 ), vec2( 1.0f, 1.0f ) ),
        VertexFormat( vec2(  size.x/2, -size.y/2 ) + offset, ColorByte( 255, 255, 255, 255 ), vec2( 1.0f, 0.0f ) ),
    };

    unsigned int indices[6] = { 0,1,2, 0,2,3 };

    Init( vertexAttributes, 4, indices, 6, GL_TRIANGLES, GL_STATIC_DRAW );
}

void Mesh::CreatePlane(vec2 worldSize, ivec2 vertexCount, vec2 pivotPoint, vec2 uvRepeat)
{
    int numVerts = vertexCount.x * vertexCount.y;
    int numIndices = (vertexCount.x - 1) * (vertexCount.y - 1) * 6;

    VertexFormat* verts = new VertexFormat[numVerts];
    unsigned int* indices = new unsigned int[numIndices];

    float stepX = worldSize.x / ( vertexCount.y - 1 );
    float stepY = worldSize.y / ( vertexCount.y - 1 );

    float uvStepX = uvRepeat.x / ( vertexCount.y - 1 );
    float uvStepY = uvRepeat.y / ( vertexCount.y - 1 );

    for( int y = 0; y < vertexCount.y; y++ )
    {
        for( int x = 0; x < vertexCount.x; x++ )
        {
            verts[y * vertexCount.x + x].pos.Set( x * stepX - pivotPoint.x, 0, y * stepY - pivotPoint.y );
            verts[y * vertexCount.x + x].uv.Set( x * uvStepX, y * uvStepY );;
        }
    }

    for( int y = 0; y < vertexCount.y - 1; y++ )
    {
        for( int x = 0; x < vertexCount.x - 1; x++ )
        {
            int bottomLeftIndex = y * vertexCount.x + x;
            int elementIndex = ( y * (vertexCount.x-1) + x ) * 6;

            indices[ elementIndex + 0 ] = bottomLeftIndex + 0;
            indices[ elementIndex + 1 ] = bottomLeftIndex + vertexCount.x;
            indices[ elementIndex + 2 ] = bottomLeftIndex + vertexCount.x + 1;

            indices[ elementIndex + 3 ] = bottomLeftIndex + 0;
            indices[ elementIndex + 4 ] = bottomLeftIndex + vertexCount.x + 1;
            indices[ elementIndex + 5 ] = bottomLeftIndex + 1;
        }
    }

    Init( verts, numVerts, indices, numIndices, GL_TRIANGLES, GL_STATIC_DRAW );

    delete[] verts;
    delete[] indices;
}

void Mesh::CreateOBJ(const char* objFilename, vec3 scale)
{
    unsigned int numVerts = 0;
    unsigned int numIndices = 0;
    VertexFormat* verts = 0;
    unsigned int* indices = 0;

    LoadBasicOBJFromFile( objFilename, scale, &numVerts, &numIndices, &verts, &indices );

    Init( verts, numVerts, nullptr, 0, GL_TRIANGLES, GL_STATIC_DRAW );

    delete[] verts;
    delete[] indices;
}

void Mesh::CreateRing(float innerradius, float outerradius, int numsegments, ColorByte color)
{
    int numverts = numsegments * 2;
    int numindices = numsegments * 6;

    VertexFormat* verts = new VertexFormat[numverts];
    unsigned int* indices = new unsigned int[numindices];

    for( int i=0; i<numsegments; i++ )
    {
        float angledeginc = 360.0f/numsegments;
        float angledeg = angledeginc * i;
        float anglerad = angledeg / 180.0f * PI;

        // outer
        verts[ i*2 + 0 ].pos.x = cosf( anglerad ) * outerradius;
        verts[ i*2 + 0 ].pos.y = 0;
        verts[ i*2 + 0 ].pos.z = sinf( anglerad ) * outerradius;
        verts[ i*2 + 0 ].color = color;

        // inner
        verts[ i*2 + 1 ].pos.x = cosf( anglerad ) * innerradius;
        verts[ i*2 + 1 ].pos.y = 0;
        verts[ i*2 + 1 ].pos.z = sinf( anglerad ) * innerradius;
        verts[ i*2 + 1 ].color = color;
    }

    for( int i=0; i<numsegments; i++ )
    {
        indices[ i*6 + 0 ] = i*2 + 0;
        indices[ i*6 + 1 ] = i*2 + 1;
        indices[ i*6 + 2 ] = i*2 + 3;

        indices[ i*6 + 3 ] = i*2 + 0;
        indices[ i*6 + 4 ] = i*2 + 3;
        indices[ i*6 + 5 ] = i*2 + 2;
    }

    // fix the last set of indices so they use the original verts.
    indices[ (numsegments-1)*6 + 2 ] = 1;
    indices[ (numsegments-1)*6 + 4 ] = 1;
    indices[ (numsegments-1)*6 + 5 ] = 0;    

    Init( verts, numverts, indices, numindices, GL_TRIANGLES, GL_STATIC_DRAW );

    delete[] verts;
    delete[] indices;
}

void Mesh::CreateArc(float outerradius, int degrees, int numsegments, ColorByte color)
{
    int numverts = numsegments + 2;
    int numindices = numsegments * 3;

    VertexFormat* verts = new VertexFormat[numverts];
    unsigned int* indices = new unsigned int[numindices];

    float startdegrees = -(float)degrees/2;
    float degreeinc = (float)degrees / numsegments;

    verts[ 0 ].pos.x = 0;
    verts[ 0 ].pos.y = 0;
    verts[ 0 ].pos.z = 0;
    verts[ 0 ].color = color;

    verts[ 1 ].pos.x = cosf( startdegrees / 180.0f * PI ) * outerradius;
    verts[ 1 ].pos.y = 0;
    verts[ 1 ].pos.z = sinf( startdegrees / 180.0f * PI ) * outerradius;
    verts[ 1 ].color = color;

    for( int i=0; i<numsegments; i++ )
    {
        float angledeg = startdegrees + degreeinc * (i+1);
        float anglerad = angledeg / 180.0f * PI;

        verts[ 2 + i ].pos.x = cosf( anglerad ) * outerradius;
        verts[ 2 + i ].pos.y = 0;
        verts[ 2 + i ].pos.z = sinf( anglerad ) * outerradius;
        verts[ 2 + i ].color = color;
    }

    for( int i=0; i<numsegments; i++ )
    {
        indices[ i*3 + 0 ] = 0;
        indices[ i*3 + 1 ] = i+2;
        indices[ i*3 + 2 ] = i+1;
    }

    Init( verts, numverts, indices, numindices, GL_TRIANGLES, GL_STATIC_DRAW );

    delete[] verts;
    delete[] indices;
}
