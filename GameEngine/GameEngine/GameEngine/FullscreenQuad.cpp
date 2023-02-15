#include "FullscreenQuad.h"
#include "GraphicEngine.h"
#include "Misc.h"


FullscreenQuad::FullscreenQuad(ID3D11Device* device)
{
    HRESULT hr{ S_OK };
    
    ShaderManager* shaderManager = GraphicEngine::get()->getShaderManager();
    hr = shaderManager->createVSFromFile_cso(device, "./Data/Shaders/FullscreenQuad_vs.cso", embedded_vertex_shader.ReleaseAndGetAddressOf(),nullptr,nullptr,0);
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
    hr = shaderManager->createPSFromFile_cso(device, "./Data/Shaders/FullscreenQuad_ps.cso", embedded_pixel_shader.ReleaseAndGetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

}

void FullscreenQuad::blit(ID3D11DeviceContext* immediate_context, ID3D11ShaderResourceView** shader_resource_view, uint32_t start_slot, uint32_t num_views, ID3D11PixelShader* replaced_pixel_shader)
{
    immediate_context->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
    immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    immediate_context->IASetInputLayout(nullptr);

    immediate_context->VSSetShader(embedded_vertex_shader.Get(), 0, 0);
    replaced_pixel_shader ? immediate_context->PSSetShader(replaced_pixel_shader, 0, 0) :
        immediate_context->PSSetShader(embedded_pixel_shader.Get(), 0, 0);

    immediate_context->PSSetShaderResources(start_slot, num_views, shader_resource_view);

    immediate_context->Draw(4, 0);

    ID3D11ShaderResourceView* dummy = nullptr;
    immediate_context->PSSetShaderResources(start_slot, num_views, &dummy);
}
