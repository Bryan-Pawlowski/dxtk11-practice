#pragma once

#include "dxtk_all.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

using namespace WinMainParameters;
using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

class GFXApp
{
private:
	HINSTANCE	_hInstance;
	HINSTANCE	_hPrevInstance;
	UINT		m_wX;
	UINT		m_wY;
	HWND		_hWnd;

public:

	ComPtr<IDXGISwapChain>			swapchain;
	ComPtr<ID3D11Device>			dev;
	ComPtr<ID3D11DeviceContext>		devcon;
	ComPtr<ID3D11RenderTargetView> 	backbuffer;

	GFXApp();
	~GFXApp();

	virtual int main(UINT, UINT);
	virtual int mainLoop();
	virtual int initWindow();
	virtual int initGraphics();
	virtual int initScene();
	virtual int initPipeline();
	virtual int Update();
	virtual int Render();
	HINSTANCE getInstance() { return _hInstance; }
	HINSTANCE getPreviousInstance() { return _hPrevInstance; }
	HWND getHwnd() { return _hWnd; }
	void setHwnd(HWND hwnd) { _hWnd = hwnd; }
	GFXApp(const GFXApp&) = default;
};



