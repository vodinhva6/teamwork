// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <sstream>

#include <dxgi1_6.h>
#include <d3d11.h>
#include <wrl.h>

#include "Misc.h"
#include "DataFormat.h"
#include "HighResolutionTimer.h"
#include "SingletonPatternTemplate.h"



#ifdef USE_IMGUI
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern ImWchar glyphRangesJapanese[];
#endif



using namespace DirectX;

class Framework : public SingletonPatternTemplate<Framework>
{
	friend class SingletonPatternTemplate<Framework>;
public:
	Framework();
	void Init(HWND hwnd);
	int GameRun();
	void PresentFrame();
	const HWND* getHwnd() { return &hwnd; }
	~Framework();

public:
	CONST LONG& getScreenWidth() { return WINDOW_WIDTH; }
	CONST LONG& getScreenHeight() { return WINDOW_HEIGHT; }
	CONST BOOL& getFullScreen() { return FULLSCREEN; }
    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	ID3D11Device* getDevice() { return device.Get(); }
	float getElapsedTime() { return elapsedTime; }
private:
	HWND hwnd;
	SIZE frameBuffer_SIZE;
	LONG WINDOW_WIDTH{ 1920 };
	LONG WINDOW_HEIGHT{ 1080 };

	BOOL FULLSCREEN{ FALSE };

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffers[SizeOfConstantBuffer];
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;

	Microsoft::WRL::ComPtr<IDXGIAdapter3> adapter;
	Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory6;


private:
	void AcquireHighPerformanceAdapter(IDXGIFactory6* dxgi_factory6, IDXGIAdapter3** dxgi_adapter3);
	void CreateSwapchain();
	void CreateFactory();
	void CreateDevice();

	void ChangeSizeWindow(UINT64 width, UINT height);
	void CalculateFrameStats();
	void ResetViewPort();
	void ReleaseSwapchain();
	void ImGuiSetup();
	void ImGuiUninstall();
	void ImGuiRender();
	void SetWindowBoderLess();


	void ImGuiNewFrame();
private:
	HighResolutionTimer tictoc;
	uint32_t frames{ 0 };
	float elapsedTime{ 0.0f };
	float fps;



private:
};

