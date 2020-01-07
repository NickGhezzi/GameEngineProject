#ifndef __VertexFormat_H__
#define __VertexFormat_H__

struct VertexFormat
{
    vec2 pos;
    ColorByte color;
    vec2 uv;

    VertexFormat()
    {
        pos.Set( 0, 0 );
        color.Set( 255, 255, 255, 255 );
        uv.Set( 0, 0 );
    }

    VertexFormat(vec2 npos, ColorByte ncolor, vec2 nuv)
    {
        pos = npos;
        color = ncolor;
        uv = nuv;
    }
};

#endif //__VertexFormat_H__

