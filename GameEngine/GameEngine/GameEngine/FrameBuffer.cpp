#include "FrameBuffer.h"
#include "Misc.h"
#include "GraphicEngine.h"
FrameBuffer::FrameBuffer(IDXGISwapChain* swapChain,ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow): name(name)
{
    HRESULT hr{ S_OK };
    Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTargetBuffer;
    D3D11_TEXTURE2D_DESC texture2dDesc{};
    texture2dDesc.Width = static_cast<UINT>(width);
    texture2dDesc.Height = static_cast<UINT>(height);
    texture2dDesc.MipLevels = 1;
    texture2dDesc.ArraySize = 1;
    texture2dDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texture2dDesc.SampleDesc.Count = msaa ? 4 : 1;
    texture2dDesc.SampleDesc.Quality = 0;
    texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
    texture2dDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    texture2dDesc.CPUAccessFlags = 0;
    texture2dDesc.MiscFlags = 0;
    hr = device->CreateTexture2D(&texture2dDesc, 0, renderTargetBuffer.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));



    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc{};
    renderTargetViewDesc.Format = texture2dDesc.Format;
    renderTargetViewDesc.ViewDimension = msaa ? D3D11_RTV_DIMENSION_TEXTURE2DMS : D3D11_RTV_DIMENSION_TEXTURE2D;
    hr = device->CreateRenderTargetView(renderTargetBuffer.Get(), &renderTargetViewDesc, renderTargetView.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc{};
    shaderResourceViewDesc.Format = texture2dDesc.Format;
    shaderResourceViewDesc.ViewDimension = msaa ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Texture2D.MipLevels = 1;
    hr = device->CreateShaderResourceView(renderTargetBuffer.Get(), &shaderResourceViewDesc,
        shaderResourceView[0].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

    Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
    texture2dDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
    texture2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
    hr = device->CreateTexture2D(&texture2dDesc, 0, depthStencilBuffer.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = msaa ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Flags = 0;
    hr = device->CreateDepthStencilView(depthStencilBuffer.Get(), &depthStencilViewDesc,
        depthStencilView.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

    shaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    shaderResourceViewDesc.ViewDimension = msaa ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2DMS;
    hr = device->CreateShaderResourceView(depthStencilBuffer.Get(), &shaderResourceViewDesc,
        shaderResourceView[1].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
       

    ShaderManager* shaderManager = GraphicEngine::get()->getShaderManager();

    shaderManager = new ShaderManager;
    
    hr = shaderManager->createVSFromFile_cso(device, "./Data/Shaders/FullscreenQuad_vs.cso", embedded_vertex_shader.ReleaseAndGetAddressOf(), nullptr, nullptr, 0);
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
    hr = shaderManager->createPSFromFile_cso(device, "./Data/Shaders/Resolve.cso", embedded_pixel_shader.ReleaseAndGetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
}

Framebuffer2DEarly::Framebuffer2DEarly(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow)
    :FrameBuffer(swapChain,device,width,height,msaa,name,shadow)
{
}

void Framebuffer2DEarly::DrawedOn(ID3D11DeviceContext* immediateContext)
{
    GraphicEngine::get()->getShaderManager()->BeginDraw2D(immediateContext);
    GraphicEngine::get()->Draw2D(false);
}

MSAABuffer1::MSAABuffer1(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow)
    :FrameBuffer(swapChain, device, width, height, msaa, name)
{
  
}

void MSAABuffer1::DrawedOn(ID3D11DeviceContext* immediateContext)
{
    GraphicEngine::get()->getShaderManager()->BeginDraw3D(immediateContext);
    GraphicEngine::get()->DrawAllUninvisibleObject(0);
}

MSAABuffer2::MSAABuffer2(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow)
    :FrameBuffer(swapChain, device, width, height, msaa, name)
{
}

void MSAABuffer2::DrawedOn(ID3D11DeviceContext* immediateContext)
{
    GraphicEngine::get()->getShaderManager()->BeginDraw3D(immediateContext);
    GraphicEngine::get()->DrawAllUninvisibleObject(1);
}

MSAABuffer3::MSAABuffer3(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow)
    :FrameBuffer(swapChain, device, width, height, msaa, name)
{
   
}

void MSAABuffer3::DrawedOn(ID3D11DeviceContext* immediateContext)
{
    GraphicEngine::get()->getShaderManager()->BeginDraw3D(immediateContext);
    GraphicEngine::get()->DrawAllUninvisibleObject(2);
}

MainFrameBuffer::MainFrameBuffer(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow)
    :FrameBuffer(swapChain, device, width, height, msaa, name)
{
}

void MainFrameBuffer::DrawedOn(ID3D11DeviceContext* immediateContext)
{
    FrameBufferManager* frameBufferManager = GraphicEngine::get()->getFrameBufferManager();

    FrameBuffer* frameBuffer = frameBufferManager->getFrameBuffer(FrameBufferName::FRAMEBUFFER2DEARLY);
    GraphicEngine::get()->getShaderManager()->SetDrawStateDraw2D(immediateContext);
    frameBufferManager->BlitFrom(immediateContext, frameBuffer);

    frameBufferManager->ResolveMSAAFrameBufferToMainBuffer(Framework::get()->getDevice(), immediateContext);


    frameBuffer = frameBufferManager->getFrameBuffer(FrameBufferName::FRAMEBUFFER2DLATE);
    GraphicEngine::get()->getShaderManager()->SetDrawStateDraw2D(immediateContext);
    frameBufferManager->BlitFrom(immediateContext, frameBuffer);

}

BlurFrameBuffer::BlurFrameBuffer(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow)
    :FrameBuffer(swapChain, device, width, height, msaa, name)
{
}

void BlurFrameBuffer::DrawedOn(ID3D11DeviceContext* immediateContext)
{
}

DebuggerFrameBuffer::DebuggerFrameBuffer(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow)
    :FrameBuffer(swapChain, device, width, height, msaa, name)
{
}

void DebuggerFrameBuffer::DrawedOn(ID3D11DeviceContext* immediateContext)
{
}

Framebuffer2DLate::Framebuffer2DLate(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow)
    :FrameBuffer(swapChain, device, width, height, msaa, name)
{
}

void Framebuffer2DLate::DrawedOn(ID3D11DeviceContext* immediateContext)
{
    GraphicEngine::get()->getShaderManager()->BeginDraw2D(immediateContext);
    GraphicEngine::get()->Draw2D(true);
}

ShadowFrameBuffer::ShadowFrameBuffer(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow)
{
    HRESULT hr{ S_OK };
    D3D11_TEXTURE2D_DESC texture2d_desc = {};
    texture2d_desc.Width = static_cast<UINT>(width);
    texture2d_desc.Height = static_cast<UINT>(height);
    texture2d_desc.MipLevels = 1;
    texture2d_desc.ArraySize = 1;
    texture2d_desc.Format = DXGI_FORMAT_R16_TYPELESS;
    texture2d_desc.SampleDesc.Count = 1;
    texture2d_desc.SampleDesc.Quality = 0;
    texture2d_desc.Usage = D3D11_USAGE_DEFAULT;
    texture2d_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
    texture2d_desc.CPUAccessFlags = 0;
    texture2d_desc.MiscFlags = 0;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2d;
    hr = device->CreateTexture2D(&texture2d_desc, 0, texture2d.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

    D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc = {};
    depth_stencil_view_desc.Format = DXGI_FORMAT_D16_UNORM;
    depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depth_stencil_view_desc.Flags = 0;
    hr = device->CreateDepthStencilView(texture2d.Get(), &depth_stencil_view_desc, depthStencilView.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

    D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc = {};
    shader_resource_view_desc.Format = DXGI_FORMAT_R16_UNORM;
    shader_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shader_resource_view_desc.Texture2D.MipLevels = 1;
    hr = device->CreateShaderResourceView(texture2d.Get(), &shader_resource_view_desc, shaderResourceView[0].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
}

void ShadowFrameBuffer::DrawedOn(ID3D11DeviceContext* immediateContext)
{
    immediateContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    ID3D11RenderTargetView* null_rtv = nullptr;
    immediateContext->OMSetRenderTargets(0, &null_rtv, depthStencilView.Get());
    GraphicEngine::get()->getShaderManager()->BeginDraw3DCreateDepthBufferOfShadow(immediateContext);
    GraphicEngine::get()->DrawAllUninvisibleObject(0);
    GraphicEngine::get()->DrawAllUninvisibleObject(1);
    GraphicEngine::get()->DrawAllUninvisibleObject(2);
}
