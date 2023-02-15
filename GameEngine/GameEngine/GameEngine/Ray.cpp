#include "Ray.h"
#include "GraphicEngine.h"
#include "MyMath.h"
#include "Misc.h"
Ray::Ray(ID3D11Device* device, const VECTOR3& begin, const VECTOR3& end, const VECTOR4& color, RayType Type): begin(begin),end(end),color(color),type(Type)
{
    vertex Vertexx[2];
    Vertexx[0].position = begin;
    Vertexx[1].position = end;
    uint32_t indicess[2];
    indicess[0] = 0;
    indicess[1] = 1;

    create_com_buffers(device, Vertexx, 2, indicess, 2);

    HRESULT hr{ S_OK };

    D3D11_INPUT_ELEMENT_DESC input_element_desc[]
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
       D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
       D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    ShaderManager* shaderManager = GraphicEngine::get()->getShaderManager();
    hr = shaderManager->createVSFromFile_cso(device, "./Data/Shaders/geometric_primitive_vs.cso", vertex_shader.ReleaseAndGetAddressOf(), input_layout.ReleaseAndGetAddressOf(), input_element_desc, ARRAYSIZE(input_element_desc));
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
    hr = shaderManager->createPSFromFile_cso(device, "./Data/Shaders/geometric_primitive_ps.cso", pixel_shader.ReleaseAndGetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
}
