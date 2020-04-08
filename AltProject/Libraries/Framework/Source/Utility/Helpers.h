#ifndef __Helpers_H__
#define __Helpers_H__

namespace fw
{
    void OutputMessage(const char* message, ...);
    char* LoadCompleteFile(const char* filename, long* length);
    double GetSystemTime();
    double GetSystemTimeSinceGameStart();

    GLuint LoadTexture(const char* filename);
    void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height);

    void Clamp(float& value, float min, float max);

    class ColorByte
    {
    public:
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;

        ColorByte()
        {
            r = 255; g = 255; b = 255; a = 255;
        }

        ColorByte(unsigned char nr, unsigned char ng, unsigned char nb, unsigned char na)
        {
            r = nr; g = ng; b = nb; a = na;
        }

        void Set(unsigned char nr, unsigned char ng, unsigned char nb, unsigned char na)
        {
            r = nr; g = ng; b = nb; a = na;
        }
    };
} // namespace fw

#endif //__Helpers_H__
