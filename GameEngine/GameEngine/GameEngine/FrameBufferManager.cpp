#include "FrameBufferManager.h"
#include "Misc.h"
#include "DataFormat.h"

void FrameBufferManager::Clear(ID3D11DeviceContext* immediateContext, FrameBuffer* framebuffer, float r, float g, float b, float a, float depth)
{
    float color[4]{ r,g,b,a };
    immediateContext->ClearRenderTargetView(framebuffer->getRenderTargetView(), color);
    immediateContext->ClearDepthStencilView(framebuffer->getDepthStencilView(), D3D11_CLEAR_DEPTH, depth, 0);


}

void FrameBufferManager::Activate(ID3D11DeviceContext* immediateContext, FrameBuffer* framebuffer)
{
    viewportCount = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
    immediateContext->RSGetViewports(&viewportCount, cachedViewports);
    immediateContext->OMGetRenderTargets(1, cachedRenderTargetView.ReleaseAndGetAddressOf(), cachedDepthStencilView.ReleaseAndGetAddressOf());

    immediateContext->RSSetViewports(1, &viewport);
    ID3D11RenderTargetView* renderTagertView = framebuffer->getRenderTargetView();
    immediateContext->OMSetRenderTargets(1, &renderTagertView, framebuffer->getDepthStencilView());

}

void FrameBufferManager::Deactivate(ID3D11DeviceContext* immediateContext, FrameBuffer* framebuffer)
{
    immediateContext->RSSetViewports(viewportCount, cachedViewports);
    immediateContext->OMSetRenderTargets(1, cachedRenderTargetView.GetAddressOf(), cachedDepthStencilView.Get());

}

void FrameBufferManager::Resolve(ID3D11Device* device,ID3D11DeviceContext* immediateContext, FrameBuffer* framebufferSource, FrameBuffer* framebufferReception)
{
    Microsoft::WRL::ComPtr<ID3D11Resource> resouce[2];
    framebufferSource->getRenderTargetView()->GetResource(resouce[0].GetAddressOf());
    framebufferReception->getRenderTargetView()->GetResource(resouce[1].GetAddressOf());

    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2d;
    HRESULT hr = resouce[0].Get()->QueryInterface<ID3D11Texture2D>(texture2d.GetAddressOf());
    D3D11_TEXTURE2D_DESC MSAADesc{};
    texture2d.Get()->GetDesc(&MSAADesc);

    D3D11_TEXTURE2D_DESC texture2dDesc{};
    texture2dDesc.Width = static_cast<UINT>(MSAADesc.Width);
    texture2dDesc.Height = static_cast<UINT>(MSAADesc.Height);
    texture2dDesc.MipLevels = 1;
    texture2dDesc.ArraySize = 1;
    texture2dDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texture2dDesc.SampleDesc.Count = 1;
    texture2dDesc.SampleDesc.Quality = 0;
    texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
    texture2dDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    texture2dDesc.CPUAccessFlags = 0;
    texture2dDesc.MiscFlags = 0;
    hr = device->CreateTexture2D(&texture2dDesc, 0, texture2d.ReleaseAndGetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc{};
    shaderResourceViewDesc.Format = texture2dDesc.Format;
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Texture2D.MipLevels = 1;
    hr = device->CreateShaderResourceView(texture2d.Get(), &shaderResourceViewDesc,
        shaderResourceView.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));


    hr = resouce[0].Get()->QueryInterface<ID3D11Texture2D>(texture2d.ReleaseAndGetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
    D3D11_TEXTURE2D_DESC texture2d_desc;
    texture2d->GetDesc(&texture2d_desc);
    _ASSERT_EXPR(texture2d_desc.SampleDesc.Count > 1, L"source texture must be multisample texture");

    Microsoft::WRL::ComPtr<ID3D11Resource> res;
    shaderResourceView.Get()->GetResource(res.GetAddressOf());
    immediateContext->ResolveSubresource(res.Get(), D3D11CalcSubresource(0, 0, 1), resouce[0].Get(), D3D11CalcSubresource(0, 0, 1), texture2d_desc.Format);

    blitTransfer.get()->blit(immediateContext, shaderResourceView.GetAddressOf(), 0, 1);

}

void FrameBufferManager::Init(IDXGISwapChain* swapChain, ID3D11Device* device, D3D11_VIEWPORT* viewPort)
{
    listFrameBuffer.push_back(std::make_unique<Framebuffer2DEarly>(swapChain, device, viewPort->Width, viewPort->Height, false, FrameBufferName::FRAMEBUFFER2DEARLY));
    listFrameBuffer.push_back(std::make_unique<ShadowFrameBuffer>(swapChain, device, viewPort->Width, viewPort->Height, false, FrameBufferName::SHADOWFRAMEBUFFER, true));
    listFrameBuffer.push_back(std::make_unique<MSAABuffer1>(swapChain, device, viewPort->Width, viewPort->Height, true, FrameBufferName::MSAABUFFER1));
    listFrameBuffer.push_back(std::make_unique<MSAABuffer2>(swapChain, device, viewPort->Width, viewPort->Height, true, FrameBufferName::MSAABUFFER2));
    listFrameBuffer.push_back(std::make_unique<MSAABuffer3>(swapChain, device, viewPort->Width, viewPort->Height, true, FrameBufferName::MSAABUFFER3));
    listFrameBuffer.push_back(std::make_unique<BlurFrameBuffer>(swapChain, device, viewPort->Width, viewPort->Height, false, FrameBufferName::BLURFRAMEBUFFER));
    listFrameBuffer.push_back(std::make_unique<DebuggerFrameBuffer>(swapChain, device, viewPort->Width, viewPort->Height, false, FrameBufferName::DEBUGERFRAMEBUFFER));
    listFrameBuffer.push_back(std::make_unique<Framebuffer2DLate>(swapChain, device, viewPort->Width, viewPort->Height, false, FrameBufferName::FRAMEBUFFER2DLATE));
    listFrameBuffer.push_back(std::make_unique<MainFrameBuffer>(swapChain, device, viewPort->Width, viewPort->Height, false, FrameBufferName::MAINBLITFRAMEBUFFER));

    //listFrameBuffer.push_back(std::make_unique<FrameBuffer>(swapChain, device, viewPort->Width, viewPort->Height, false, FrameBufferName::SOFTSHADOWFRAMEBUFFER));
    //listFrameBuffer.push_back(std::make_unique<FrameBuffer>(swapChain, device, viewPort->Width, viewPort->Height, false, FrameBufferName::TESTBUFER));
    

    blitTransfer = std::make_unique<FullscreenQuad>(device);

    viewport.Width = viewPort->Width;
    viewport.Height = viewPort->Height; 
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
}


void FrameBufferManager::ClearAllBuffer(ID3D11DeviceContext* immediateContext)
{
    for (size_t i = 0; i < listFrameBuffer.size(); i++)
    {
        if (i == (int)(FrameBufferName::SHADOWFRAMEBUFFER))
            continue;
        Clear(immediateContext, listFrameBuffer[i].get());
    }
}

void FrameBufferManager::DrawOnFrameBuffer(ID3D11DeviceContext* immediateContext)
{
    for (size_t i = 0; i < listFrameBuffer.size(); i++)
    {
        Activate(immediateContext, listFrameBuffer[i].get());
        listFrameBuffer[i].get()->DrawedOn(immediateContext);
        Deactivate(immediateContext, listFrameBuffer[i].get());
    }
}

void FrameBufferManager::ResolveMSAAFrameBufferToMainBuffer(ID3D11Device* device,ID3D11DeviceContext* immediateContext)
{
    Resolve(device, immediateContext, listFrameBuffer[(int)FrameBufferName::MSAABUFFER1].get(), listFrameBuffer[(int)FrameBufferName::MAINBLITFRAMEBUFFER].get());
    Resolve(device, immediateContext, listFrameBuffer[(int)FrameBufferName::MSAABUFFER2].get(), listFrameBuffer[(int)FrameBufferName::MAINBLITFRAMEBUFFER].get());
    Resolve(device, immediateContext, listFrameBuffer[(int)FrameBufferName::MSAABUFFER3].get(), listFrameBuffer[(int)FrameBufferName::MAINBLITFRAMEBUFFER].get());
}

void FrameBufferManager::BlitMainFrameBufferToScreen(ID3D11DeviceContext* immediateContext)
{
    BlitFrom(immediateContext, listFrameBuffer[(int)FrameBufferName::MAINBLITFRAMEBUFFER].get());
}

void FrameBufferManager::BlitFrom(ID3D11DeviceContext* immediateContext, FrameBuffer* frameBuffer)
{
    blitTransfer.get()->blit(immediateContext, frameBuffer->getAddrShaderResourceView(0), 0, 1);
}

FrameBuffer* FrameBufferManager::getFrameBuffer(FrameBufferName name)
{
    return listFrameBuffer[(int)name].get();
}


FrameBufferManager::~FrameBufferManager()
{
    
}
