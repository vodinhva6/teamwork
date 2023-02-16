#include "Framework.h"
#include <string>
#include "DataFormat.h"
#include "GraphicEngine.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "DataBase.h"
Framework::Framework()
{
	frameBuffer_SIZE = { 1080,720 };
	hwnd = {};
	WINDOW_WIDTH = 1080;
	WINDOW_HEIGHT = 720;

	FULLSCREEN = FALSE;
}

void Framework::Init(HWND hwnd)
{
    this->hwnd = hwnd;
	HRESULT hr{ S_OK };
	
	CreateFactory();
	
	CreateDevice();
	
	CreateSwapchain();

	ResetViewPort();

	GraphicEngine::get()->CreateCOM(device.Get(),swapChain.Get(),frameBuffer_SIZE);

	

	
	//buffer_desc.ByteWidth = ShadowManager::get()->getSizeOfShadowBuffer();
	//hr = device->CreateBuffer(&buffer_desc, nullptr, constant_buffers[ConstantBuffer::SHADOWBUFFER].GetAddressOf());
	//_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	//
	//buffer_desc.ByteWidth = GraphicEngine::get()->getSizeOfUVScrollBuffer();
	//hr = device->CreateBuffer(&buffer_desc, nullptr, constant_buffers[ConstantBuffer::UVSCROLLBUFFER].GetAddressOf());
	//_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	//
	//buffer_desc.ByteWidth = GraphicEngine::get()->getSizeOfFogBuffer();
	//hr = device->CreateBuffer(&buffer_desc, nullptr, constant_buffers[ConstantBuffer::BLURBUFFER].GetAddressOf());
	//_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	//wheel = 0;
}

void Framework::ReleaseSwapchain()
{
	GraphicEngine::get()->ResetRenderTagertAndDepthStencil();
	if (swapChain)
	{
		swapChain.Get()->SetFullscreenState(FALSE, NULL);
		swapChain.Reset();
	}

}

void Framework::ImGuiSetup()
{
#ifdef USE_IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\consola.ttf", 14.0f, nullptr, glyphRangesJapanese);
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device.Get(), GraphicEngine::get()->getDeviceContext());
	ImGui::StyleColorsLight();
#endif
}

void Framework::ImGuiUninstall()
{
#ifdef USE_IMGUI
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif
}

void Framework::ImGuiRender()
{
#ifdef USE_IMGUI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
}

void Framework::SetWindowBoderLess()
{
	LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
	lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
	SetWindowLong(hwnd, GWL_STYLE, lStyle);
}


void Framework::ImGuiNewFrame()
{
#ifdef USE_IMGUI
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
#endif
}


Framework::~Framework()
{
	ReleaseSwapchain();
	delete GraphicEngine::get();
	delete InputManager::get();
	delete AudioManager::get();
}

void Framework::ChangeSizeWindow(UINT64 width, UINT height)
{
	HRESULT hr{ S_OK };
	if (width != frameBuffer_SIZE.cx || height != frameBuffer_SIZE.cy)
	{
		frameBuffer_SIZE.cx = static_cast<LONG>(width);
		frameBuffer_SIZE.cy = height;
		ResetViewPort();

		CreateSwapchain();

	}

}

void Framework::CalculateFrameStats()
{
	if (++frames, (tictoc.time_stamp() - elapsedTime) >= 1.0f)
	{
		fps = static_cast<float>(frames);
		frames = 0;
		elapsedTime += 1.0f;
	}
	std::string st = "FPS : " + std::to_string(fps);// + " / " + "Frame Time : " + std::to_string( 1000.0f / fps ) + " (ms)";
	GraphicEngine::get()->textOut(4, st, { 200,200 }, 1, { 1,1,1,1 }, 1);
}

LRESULT Framework::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef USE_IMGUI
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) { return true; }
#endif
	switch (message)
	{
	case WM_CREATE:
		Init(hWnd);
		break;
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_ACTIVATE:
		if(FULLSCREEN)
		swapChain.Get()->SetFullscreenState(TRUE, NULL);
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ENTERSIZEMOVE:
		tictoc.stop();
		break;
	case WM_MOUSEWHEEL:
		//wheel = GET_WHEEL_DELTA_WPARAM(wparam);
		break;
	case WM_EXITSIZEMOVE:
		tictoc.start();
		break;
	case WM_SIZE:
	{
		RECT client_rect{};
		GetClientRect(hWnd, &client_rect);
		ChangeSizeWindow(static_cast<UINT64>(fabs(client_rect.right) - fabs(client_rect.left)), client_rect.bottom - client_rect.top);
		break;
	}
	case WM_KEYDOWN:
	case WM_KEYUP:
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Framework::AcquireHighPerformanceAdapter(IDXGIFactory6* dxgi_factory6, IDXGIAdapter3** dxgi_adapter3)
{
	HRESULT hr{ S_OK };

	Microsoft::WRL::ComPtr<IDXGIAdapter3> enumerated_adapter;
	for (UINT adapter_index = 0; DXGI_ERROR_NOT_FOUND != dxgi_factory6->EnumAdapterByGpuPreference(adapter_index, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(enumerated_adapter.ReleaseAndGetAddressOf())); ++adapter_index)
	{
		DXGI_ADAPTER_DESC1 adapter_desc;
		hr = enumerated_adapter->GetDesc1(&adapter_desc);
		_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

		if (adapter_desc.VendorId == 0x1002/*AMD*/ || adapter_desc.VendorId == 0x10DE/*NVIDIA*/)
		{
			OutputDebugStringW((std::wstring(adapter_desc.Description) + L" has been selected.\n").c_str());
			OutputDebugStringA(std::string("\tVendorId:" + std::to_string(adapter_desc.VendorId) + '\n').c_str());
			OutputDebugStringA(std::string("\tDeviceId:" + std::to_string(adapter_desc.DeviceId) + '\n').c_str());
			OutputDebugStringA(std::string("\tSubSysId:" + std::to_string(adapter_desc.SubSysId) + '\n').c_str());
			OutputDebugStringA(std::string("\tRevision:" + std::to_string(adapter_desc.Revision) + '\n').c_str());
			OutputDebugStringA(std::string("\tDedicatedVideoMemory:" + std::to_string(adapter_desc.DedicatedVideoMemory) + '\n').c_str());
			OutputDebugStringA(std::string("\tDedicatedSystemMemory:" + std::to_string(adapter_desc.DedicatedSystemMemory) + '\n').c_str());
			OutputDebugStringA(std::string("\tSharedSystemMemory:" + std::to_string(adapter_desc.SharedSystemMemory) + '\n').c_str());
			OutputDebugStringA(std::string("\tAdapterLuid.HighPart:" + std::to_string(adapter_desc.AdapterLuid.HighPart) + '\n').c_str());
			OutputDebugStringA(std::string("\tAdapterLuid.LowPart:" + std::to_string(adapter_desc.AdapterLuid.LowPart) + '\n').c_str());
			OutputDebugStringA(std::string("\tFlags:" + std::to_string(adapter_desc.Flags) + '\n').c_str());
			break;
		}
	}
	*dxgi_adapter3 = enumerated_adapter.Detach();
}

void Framework::CreateSwapchain()
{
	HRESULT hr{ S_OK };
	if (swapChain)
	{
		ID3D11RenderTargetView* null_render_target_view{};
		GraphicEngine::get()->getDeviceContext()->OMSetRenderTargets(1, &null_render_target_view, NULL);
		GraphicEngine::get()->ResetRenderTagertAndDepthStencil();
		GraphicEngine::get()->ResetFrameBufferManager();
		//EffectSeerManager::get()->Deinit();
		DXGI_SWAP_CHAIN_DESC swap_chain_desc{};
		swapChain->GetDesc(&swap_chain_desc);
		hr = swapChain->ResizeBuffers(swap_chain_desc.BufferCount, frameBuffer_SIZE.cx, frameBuffer_SIZE.cy, swap_chain_desc.BufferDesc.Format, swap_chain_desc.Flags);
		_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

		GraphicEngine::get()->CreateRenderTagert(device.Get(), swapChain.Get());

		GraphicEngine::get()->CreateDepthStencilView(device.Get(), swapChain.Get(), frameBuffer_SIZE);
		//GraphicEngine::get()->resetPointRenderTagert(render_target_view.Get(), depth_stencil_view.Get());

		D3D11_VIEWPORT viewPort;
		UINT viewNum = 1;
		GraphicEngine::get()->getDeviceContext()->RSGetViewports(&viewNum, &viewPort);
		GraphicEngine::get()->CreateFramebuffer(device.Get(), swapChain.Get());
		//EffectSeerManager::get()->Init(device.Get(), immediate_context.Get());
	}
	else
	{

		BOOL allow_tearing = FALSE;
		BOOL support = FALSE;
		hr = dxgiFactory6->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allow_tearing, sizeof(allow_tearing));
		support = SUCCEEDED(hr) && allow_tearing;


		DXGI_SWAP_CHAIN_FULLSCREEN_DESC aa{};
		aa.RefreshRate.Denominator = 1;
		aa.RefreshRate.Numerator = 120;
		aa.Windowed = TRUE;
		aa.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		aa.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;

		DXGI_SWAP_CHAIN_DESC1 swap_chain_desc{};

		swap_chain_desc.Width = frameBuffer_SIZE.cx;
		swap_chain_desc.Height = frameBuffer_SIZE.cy;
		swap_chain_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_chain_desc.Stereo = FALSE;
		swap_chain_desc.SampleDesc.Count = 1;
		swap_chain_desc.SampleDesc.Quality = 0;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 2;
		swap_chain_desc.Scaling = DXGI_SCALING_NONE;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swap_chain_desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swap_chain_desc.Flags = support ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

		hr = dxgiFactory6->CreateSwapChainForHwnd(device.Get(), hwnd, &swap_chain_desc, &aa, NULL, swapChain.ReleaseAndGetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
		
	}
}

void Framework::CreateFactory()
{
	HRESULT hr{ S_OK };
	UINT create_factory_flags{ 0 };
#ifdef _DEBUG
	create_factory_flags |= DXGI_CREATE_FACTORY_DEBUG;
#endif

	
	hr = CreateDXGIFactory2(create_factory_flags, IID_PPV_ARGS(dxgiFactory6.GetAddressOf()));
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	AcquireHighPerformanceAdapter(dxgiFactory6.Get(), adapter.GetAddressOf());

}

void Framework::CreateDevice()
{
	HRESULT hr{ S_OK };
	UINT create_device_flags{ 0 };
#ifdef _DEBUG
	create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL feature_levels{ D3D_FEATURE_LEVEL_11_0 };
	hr = D3D11CreateDevice(adapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, 0, create_device_flags, &feature_levels, 1, D3D11_SDK_VERSION, device.ReleaseAndGetAddressOf(),
		NULL, GraphicEngine::get()->getAddrDeviceContext()
	);
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
}



void Framework::ResetViewPort()
{
	D3D11_VIEWPORT viewport{};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(frameBuffer_SIZE.cx);
	viewport.Height = static_cast<float>(frameBuffer_SIZE.cy);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	GraphicEngine::get()->getDeviceContext()->RSSetViewports(1, &viewport);
}




int Framework::GameRun()
{
	GraphicEngine::get()->Init();
	InputManager::get()->Init(&hwnd);
	AudioManager::get()->Init();
	DataBase::get()->CreateAllObject();
	SceneManager::get()->Init();
	
	ImGuiSetup();


	MSG msg;
	GetMessage(&msg, nullptr, 0, 0);
	swapChain.Get()->SetFullscreenState(FULLSCREEN, NULL);
	
	// Main message loop:
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			ImGuiNewFrame();
			tictoc.tick();
			CalculateFrameStats();
			InputManager::get()->Update();
			GraphicEngine::get()->Update(elapsedTime);
			SceneManager::get()->UpdateChangeScene();
			SceneManager::get()->Update(elapsedTime);
			SceneManager::get()->Render();
			GraphicEngine::get()->Render();
			GraphicEngine::get()->RemoveQueneObject();
			ImGuiRender();
			PresentFrame();
			if (GraphicEngine::get()->getExitGame())
				break;
		}
	}

	ImGuiUninstall();

	return 0;
}

void Framework::PresentFrame()
{
	swapChain.Get()->Present(1, 0);
}
