#ifndef __VertexFormat_H__
#define __VertexFormat_H__

struct VertexFormat
{
    vec3 pos;
    ColorByte color;
    vec2 uv;
    vec3 normal;

    VertexFormat()
    {
        pos.Set( 0, 0, 0 );
        color.Set( 255, 255, 255, 255 );
        uv.Set( 0, 0 );
        normal.Set(0, 0, 0);
    }

    VertexFormat(vec3 npos, ColorByte ncolor, vec2 nuv)
    {
        pos = npos;
        color = ncolor;
        uv = nuv;
        normal.Set(0, 1, 0);
    }
};

#endif //__VertexFormat_H__

