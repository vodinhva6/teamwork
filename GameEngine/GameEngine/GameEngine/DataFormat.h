#ifndef INCLUDED_FORMAT
#define INCLUDED_FORMAT
#include <DirectXMath.h>
#include <functional>
class VECTOR4;
class VECTOR2 : public DirectX::XMFLOAT2
{
public:
    VECTOR2() : DirectX::XMFLOAT2(0, 0) {}
    VECTOR2(float x, float y) : DirectX::XMFLOAT2(x, y) {}
    VECTOR2(const VECTOR2& v) { x = v.x; y = v.y; }
    ~VECTOR2() {}

    VECTOR2& operator=(const VECTOR2&);
    VECTOR2& operator+=(const VECTOR2&);
    VECTOR2& operator-=(const VECTOR2&);
    VECTOR2& operator*=(float);
    VECTOR2& operator/=(float);

    VECTOR2 operator+() const;
    VECTOR2 operator-() const;

    VECTOR2 operator+(const VECTOR2&) const;
    VECTOR2 operator-(const VECTOR2&) const;
    VECTOR2 operator*(float) const;
    friend VECTOR2 operator*(float, const VECTOR2&);
    VECTOR2 operator/(float) const;

    bool operator == (const VECTOR2&) const;
    bool operator != (const VECTOR2&) const;
};




class VECTOR3 : public DirectX::XMFLOAT3
{
public:
    VECTOR3() : DirectX::XMFLOAT3(0, 0, 0) {}
    VECTOR3(float x, float y, float z) : DirectX::XMFLOAT3(x, y, z) {}
    VECTOR3(const VECTOR3& v) { x = v.x; y = v.y; z = v.z; }
    ~VECTOR3() {}

    VECTOR3& operator=(const VECTOR3& v);
    VECTOR3& operator+=(const VECTOR3&);
    VECTOR3& operator-=(const VECTOR3&);
    VECTOR3& operator*=(float);
    VECTOR3& operator/=(float);

    VECTOR3 operator+() const;
    VECTOR3 operator-() const;

    VECTOR3 operator+(const VECTOR3&) const;
    VECTOR3 operator-(const VECTOR3&) const;
    VECTOR3 operator*(float) const;
    friend VECTOR3 operator*(float, const VECTOR3&);
    VECTOR3 operator/(float) const;

    bool operator == (const VECTOR3&) const;
    bool operator != (const VECTOR3&) const;

    VECTOR3(const VECTOR2& v);
    // VECTOR3‚ÉVECTOR2‚ð‘ã“ü
    VECTOR3& operator=(const VECTOR2&);
};




class VECTOR4 : public DirectX::XMFLOAT4
{
public:
    VECTOR4() : DirectX::XMFLOAT4(0, 0, 0, 0) {}
    VECTOR4& operator+=(const VECTOR4&);
    VECTOR4& operator-=(const VECTOR4&);
    VECTOR4& operator+=(const VECTOR3&);
    VECTOR4& operator=(const VECTOR3&);

    VECTOR4 operator-(const VECTOR4&) const;

    VECTOR4& operator*=(float);
    VECTOR4& operator/=(float);

    VECTOR4(float x, float y, float z, float w) : DirectX::XMFLOAT4(x, y, z, w) {}
    ~VECTOR4() {}
};






enum class DepthStencilStates
{
    DepthTestOff_DepthWriteOff,
    DepthTestOff_DepthWriteOn,
    DepthTestOn_DepthWriteOff,
    DepthTestOn_DepthWriteOn,
};
const int MAX_DEPTH_STATES = sizeof(DepthStencilStates) + 1;

enum class RasterizerStates
{
    DrawTriangles_BackTrianglesOff_AntialiasedLineOff,
    DrawTriangles_BackTrianglesOff_AntialiasedLineOn,
    DrawLines_BackLinesOff_AntialiasedLineOn,
    DrawLines_BackLinesOn_AntialiasedLineOn,
    CullingOpposition,
};
const int MAX_RASTERIZER_STATES = sizeof(RasterizerStates) + 1;
enum BlendStates
{
    Default,
    Alpha,
    AlphaBlendAlphaCoverage,
    Subtract,
    RevSubtract
};
const int MAX_BLEND_STATES = sizeof(BlendStates) + 1;
enum class SamplerStates
{
    Point,
    Linear,
    Anisotropic,
    LinearClamp,
    Shadow,
};
const int MAX_SAMPLER_STATES = sizeof(SamplerStates) + 1;
enum ObjectType
{
    Object2D,
    Object3D
};

enum DrawType
{
    BACKGROUND,
    Picture,
    Text,
    Cube,
    Box,
    StaticMeshObject,
    SkinnedMeshObject,
    EffectObject,
    SKYBOX
};

struct DrawStates
{
    DepthStencilStates depthState;
    RasterizerStates rasterizerState;
    SamplerStates samplerState;
    BlendStates blendState;
    DrawType    drawType;
};

struct ShaderData
{
    const char* vsfile;
    const char* psfile;
};



enum SkinnedMeshObjectAxis
{
   
    TEXTURE_FLIP_Z,
    LHS_Y_UP,
    RHS_Z_UP,
    LHS_Z_UP,
    DEFAULT,
};


#define SizeOfConstantBuffer 7
enum ConstantBufferName
{
    SCENEBUFFER,
    LIGHTBUFFER,
    FILTERBUFFER,
    SHADOWBUFFER,
    //UVSCROLLBUFFER,
    FOGBUFFER,
    //BLURBUFFER
};

template <class myType>
void SafeDelete(myType*& T) 
{
    if (T != nullptr)
        delete T;
    T = nullptr;
}
float clamp(float v, float lo, float hi);
#endif // !INCLUDED_FORMAT

