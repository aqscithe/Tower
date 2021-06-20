#pragma once

#include <stdbool.h>
#include <stdarg.h>

#if defined(_WIN32)
    #if defined(BUILD_SHARED)
        #define GP_API __declspec(dllexport)
    #else
        #define GP_API __declspec(dllimport)
    #endif
#else
    #define GP_API
#endif

#define GP_ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#if defined(__cplusplus)
extern "C"
{
#endif

typedef struct GPLib GPLib;

typedef struct GPVector2
{
    float x;
    float y;
} GPVector2;

typedef struct GPColor
{
    float r;
    float g;
    float b;
    float a;
} GPColor;

typedef struct GPRect
{
    float x;
    float y;
    float w;
    float h;
} GPRect;

typedef struct GPTexture
{
    unsigned int name;
    int width;
    int height;
} GPTexture;

typedef struct GPVertex
{
    GPVector2 pos;
    GPVector2 uv;
    GPColor color;
} GPVertex;

typedef struct GPFontImpl GPFontImpl;

typedef struct GPFont
{
    float scale; // All metrics values (integers) have to be multiplied by this scale value
    
	// Font metrics
    int ascent;
    int descent;
    int lineGap;

    GPTexture atlas;

    GPFontImpl* impl;
} GPFont;

typedef struct GPFramebuffer
{
    unsigned int name;
    GPTexture texture;
} GPFramebuffer;

typedef struct GPImage
{
    int width;
    int height;
    GPColor* pixels;
} GPImage;

typedef struct GPSound
{
    float* buffer;
    int nbFrames;
} GPSound;

typedef enum GPKey
{
    // Printable keys
    GP_KEY_SPACE =              32,
    GP_KEY_APOSTROPHE =         39,  // '
    GP_KEY_COMMA =              44,  // ,
    GP_KEY_MINUS =              45,  // -
    GP_KEY_PERIOD =             46,  // .
    GP_KEY_SLASH =              47,  // /
    GP_KEY_0 =                  48,
    GP_KEY_1 =                  49,
    GP_KEY_2 =                  50,
    GP_KEY_3 =                  51,
    GP_KEY_4 =                  52,
    GP_KEY_5 =                  53,
    GP_KEY_6 =                  54,
    GP_KEY_7 =                  55,
    GP_KEY_8 =                  56,
    GP_KEY_9 =                  57,
    GP_KEY_SEMICOLON =          59,  // ;
    GP_KEY_EQUAL =              61,  // =
    GP_KEY_A =                  65,
    GP_KEY_B =                  66,
    GP_KEY_C =                  67,
    GP_KEY_D =                  68,
    GP_KEY_E =                  69,
    GP_KEY_F =                  70,
    GP_KEY_G =                  71,
    GP_KEY_H =                  72,
    GP_KEY_I =                  73,
    GP_KEY_J =                  74,
    GP_KEY_K =                  75,
    GP_KEY_L =                  76,
    GP_KEY_M =                  77,
    GP_KEY_N =                  78,
    GP_KEY_O =                  79,
    GP_KEY_P =                  80,
    GP_KEY_Q =                  81,
    GP_KEY_R =                  82,
    GP_KEY_S =                  83,
    GP_KEY_T =                  84,
    GP_KEY_U =                  85,
    GP_KEY_V =                  86,
    GP_KEY_W =                  87,
    GP_KEY_X =                  88,
    GP_KEY_Y =                  89,
    GP_KEY_Z =                  90,
    GP_KEY_LEFT_BRACKET =       91,  // [
    GP_KEY_BACKSLASH =          92,  // '\'
    GP_KEY_RIGHT_BRACKET =      93,  // ]
    GP_KEY_GRAVE_ACCENT =       96,  // `

    // Function keys
    GP_KEY_ESCAPE =             256,
    GP_KEY_ENTER =              257,
    GP_KEY_TAB =                258,
    GP_KEY_BACKSPACE =          259,
    GP_KEY_INSERT =             260,
    GP_KEY_DELETE =             261,
    GP_KEY_RIGHT =              262,
    GP_KEY_LEFT =               263,
    GP_KEY_DOWN =               264,
    GP_KEY_UP =                 265,
    GP_KEY_PAGE_UP =            266,
    GP_KEY_PAGE_DOWN =          267,
    GP_KEY_HOME =               268,
    GP_KEY_END =                269,
    GP_KEY_CAPS_LOCK =          280,
    GP_KEY_SCROLL_LOCK =        281,
    GP_KEY_NUM_LOCK =           282,
    GP_KEY_PRINT_SCREEN =       283,
    GP_KEY_PAUSE =              284,
    GP_KEY_F1 =                 290,
    GP_KEY_F2 =                 291,
    GP_KEY_F3 =                 292,
    GP_KEY_F4 =                 293,
    GP_KEY_F5 =                 294,
    GP_KEY_F6 =                 295,
    GP_KEY_F7 =                 296,
    GP_KEY_F8 =                 297,
    GP_KEY_F9 =                 298,
    GP_KEY_F10 =                299,
    GP_KEY_F11 =                300,
    GP_KEY_F12 =                301,
    GP_KEY_F13 =                302,
    GP_KEY_F14 =                303,
    GP_KEY_F15 =                304,
    GP_KEY_F16 =                305,
    GP_KEY_F17 =                306,
    GP_KEY_F18 =                307,
    GP_KEY_F19 =                308,
    GP_KEY_F20 =                309,
    GP_KEY_F21 =                310,
    GP_KEY_F22 =                311,
    GP_KEY_F23 =                312,
    GP_KEY_F24 =                313,
    GP_KEY_F25 =                314,
    GP_KEY_KP_0 =               320,
    GP_KEY_KP_1 =               321,
    GP_KEY_KP_2 =               322,
    GP_KEY_KP_3 =               323,
    GP_KEY_KP_4 =               324,
    GP_KEY_KP_5 =               325,
    GP_KEY_KP_6 =               326,
    GP_KEY_KP_7 =               327,
    GP_KEY_KP_8 =               328,
    GP_KEY_KP_9 =               329,
    GP_KEY_KP_DECIMAL =         330,
    GP_KEY_KP_DIVIDE =          331,
    GP_KEY_KP_MULTIPLY =        332,
    GP_KEY_KP_SUBTRACT =        333,
    GP_KEY_KP_ADD =             334,
    GP_KEY_KP_ENTER =           335,
    GP_KEY_KP_EQUAL =           336,
    GP_KEY_LEFT_SHIFT =         340,
    GP_KEY_LEFT_CONTROL =       341,
    GP_KEY_LEFT_ALT =           342,
    GP_KEY_LEFT_SUPER =         343,
    GP_KEY_RIGHT_SHIFT =        344,
    GP_KEY_RIGHT_CONTROL =      345,
    GP_KEY_RIGHT_ALT =          346,
    GP_KEY_RIGHT_SUPER =        347,
    GP_KEY_MENU =               348,
} GPKey;

typedef enum GPMouseButton
{
    GP_MOUSE_BUTTON_1 = 0,
    GP_MOUSE_BUTTON_2 = 1,
    GP_MOUSE_BUTTON_3 = 2,
    GP_MOUSE_BUTTON_4 = 3,
    GP_MOUSE_BUTTON_5 = 4,
    GP_MOUSE_BUTTON_6 = 5,
    GP_MOUSE_BUTTON_7 = 6,
    GP_MOUSE_BUTTON_8 = 7,
    GP_MOUSE_BUTTON_LAST   = GP_MOUSE_BUTTON_8,
    GP_MOUSE_BUTTON_LEFT   = GP_MOUSE_BUTTON_1,
    GP_MOUSE_BUTTON_RIGHT  = GP_MOUSE_BUTTON_2,
    GP_MOUSE_BUTTON_MIDDLE = GP_MOUSE_BUTTON_3,
} GPMouseButton;

typedef enum GPBlendMode
{
    GP_BLEND_MUL,
    GP_BLEND_ADD
} GPBlendMode;

enum GPInitFlags
{
    GP_VSYNC_ON = 1 << 0
};

GP_API GPColor GP_CWHITE;
GP_API GPColor GP_CBLACK;

GP_API GPLib* gpInit(int displayWidth, int displayHeight, const char* windowTitle, int initFlags);
GP_API void gpShutdown(GPLib* gp);

GP_API bool gpWindowShouldClose(GPLib* gp);
GP_API void gpWindowSetShouldClose(GPLib* gp, bool value);

GP_API double gpGetTime(GPLib* gp);
GP_API float gpGetFrameTime(GPLib* gp);

GP_API float gpUtilsPerlin(float x, float y, float z);

GP_API void gpDrawBegin(GPLib* gp);
GP_API void gpDrawEnd(GPLib* gp);
GP_API void gpDrawScissorBegin(GPLib* gp, int x, int y, int width, int height);
GP_API void gpDrawScissorEnd(GPLib* gp);
GP_API void gpDrawClearBackground(GPLib* gp, GPColor color);
GP_API void gpDrawLine(GPLib* gp, GPVector2 start, GPVector2 end, GPColor color);
GP_API void gpDrawRect(GPLib* gp, GPRect rect, GPColor color);
GP_API void gpDrawRectFilled(GPLib* gp, GPRect rect, GPColor color);
GP_API void gpDrawCircle(GPLib* gp, GPVector2 center, float radius, GPColor color);
GP_API void gpDrawCircleFilled(GPLib* gp, GPVector2 center, float radius, GPColor color);
GP_API void gpDrawTexture(GPLib* gp, GPTexture texture, GPVector2 pos, bool centered, GPColor tint);
GP_API void gpDrawTextureEx(GPLib* gp, GPTexture texture, GPRect src, GPVector2 pos, float rotate, GPVector2 scale, GPVector2* pivot, GPColor tint);
GP_API void gpDrawTextureEx2(GPLib* gp, GPTexture texture, GPRect src, GPRect dst, GPColor tint);
GP_API void gpDrawText(GPLib* gp, GPFont font, GPVector2 pos, GPColor color, const char* format, ...);
GP_API void gpDrawTextV(GPLib* gp, GPFont font, GPVector2 pos, GPColor color, const char* format, va_list vargs);

GP_API void gpDrawTriangles(GPLib* gp, GPTexture texture, GPBlendMode blendMode, GPVertex* vertices, int vertexCount);

GP_API GPImage gpImageLoad(GPLib* gp, int width, int height);
GP_API GPImage gpImageLoadFromFile(GPLib* gp, const char* imageFile);
GP_API void gpImageUnload(GPLib* gp, GPImage image);
GP_API void gpImageFillPerlin(GPLib* gp, GPImage image, float scale);

GP_API GPTexture gpTextureLoad(GPLib* gp, int width, int height, GPColor* pixels);
GP_API GPTexture gpTextureLoadFromImage(GPLib* gp, GPImage image);
GP_API GPTexture gpTextureLoadFromFile(GPLib* gp, const char* imageFile);
GP_API void gpTextureUnload(GPLib* gp, GPTexture texture);
GP_API void gpTextureUpdate(GPLib* gp, GPTexture texture, GPColor* pixels);
GP_API void gpTextureUpdateFromImage(GPLib* gp, GPTexture texture, GPImage image);

GP_API GPFramebuffer gpFramebufferLoad(GPLib* gp, int width, int height);
GP_API void gpFramebufferUnload(GPLib* gp, GPFramebuffer framebuffer);
GP_API void gpFramebufferDrawBegin(GPLib* gp, GPFramebuffer framebuffer);
GP_API void gpFramebufferDrawEnd(GPLib* gp);

GP_API GPFont gpFontLoad(GPLib* gp, const char* fontFile, float fontSize);
GP_API void gpFontUnload(GPLib* gp, GPFont font);
GP_API void gpFontGetGlyphCoords(GPLib* gp, GPFont font, int charCode, float* penX, float* penY, GPRect* src, GPRect* dst);
GP_API int gpFontGetKerningAdvance(GPLib* gp, GPFont font, int char0, int char1);

GP_API void gpEventsPoll(GPLib* gp);
GP_API bool gpKeyIsPressed(GPLib* gp, GPKey key);
GP_API bool gpKeyIsDown(GPLib* gp, GPKey key);
GP_API bool gpKeyIsUp(GPLib* gp, GPKey key);
GP_API bool gpKeyIsReleased(GPLib* gp, GPKey key);
GP_API GPVector2 gpMousePosition(GPLib* gp);
GP_API bool gpMouseButtonIsPressed(GPLib* gp, GPMouseButton button);
GP_API bool gpMouseButtonIsDown(GPLib* gp, GPMouseButton button);
GP_API bool gpMouseButtonIsUp(GPLib* gp, GPMouseButton button);
GP_API bool gpMouseButtonIsReleased(GPLib* gp, GPMouseButton button);

GP_API GPSound gpSoundLoad(GPLib* gp, const char* soundFile);
GP_API void gpSoundUnload(GPLib* gp, GPSound sound);
GP_API void gpSoundPlay(GPLib* gp, GPSound sound);

#if defined(__cplusplus)
}
#endif