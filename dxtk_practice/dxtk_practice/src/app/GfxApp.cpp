#include "GfxApp.h"
#include "common.h"



// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

GFXApp::GFXApp()
{
	_hInstance = GetHInstance();
	_hPrevInstance = GetHPrevInstance();
}

GFXApp::~GFXApp()
{
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}

int GFXApp::main(UINT wX, UINT wY)
{
	std::cout << "This is the default App Implementation." << std::endl;

	m_wX = wX;
	m_wY = wY;

	initWindow();
	initGraphics();

	mainLoop();

	return 0;
}

int GFXApp::mainLoop()
{

	MSG msg;

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		Update();
		Render();
	}

	return 0;
}

int GFXApp::initWindow()
{
	WNDCLASSEX wc;
	int nCmdShow = GetNCmdShow();
	HINSTANCE hInstance = getInstance();

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass";

	RegisterClassEx(&wc);

	RECT wr = { 0, 0, m_wX, m_wY };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hWnd = CreateWindowEx(NULL,
		"WindowClass",
		"DX Window",
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	setHwnd(hWnd);

	return 1;
}

int GFXApp::initGraphics()
{

	HWND hWnd = getHwnd();
	if (hWnd == nullptr)
	{
		std::cout << "No window initialized! Cannot draw graphics if there is no window!" << std::endl;
		return 0;
	}

	DXGI_SWAP_CHAIN_DESC scd;							//We want to create a swapchain that outputs to the window we just created.
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = TRUE;

	D3D11CreateDeviceAndSwapChain(
		NULL,								//This gives us a handle to our swapchain, device, and the device's context.
		D3D_DRIVER_TYPE_HARDWARE,			//After this, we can start doing some DX11!
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);

	//get address of back buffer
	ComPtr<ID3D11Texture2D> pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pBackBuffer.GetAddressOf());

	//create a render target at the back buffer address.
	dev->CreateRenderTargetView(pBackBuffer.Get(), NULL, backbuffer.GetAddressOf());
	pBackBuffer->Release();

	// set the render target as the back buffer.
	devcon->OMSetRenderTargets(1, backbuffer.GetAddressOf(), NULL);

	//Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = m_wX;
	viewport.Height = m_wY;

	devcon->RSSetViewports(1, &viewport);

	return 1;
}

int GFXApp::initScene()
{
	return 0;
}

int GFXApp::initPipeline()
{
	return 0;
}

int GFXApp::Update()
{
	return 0;
}

int GFXApp::Render()
{
	FLOAT color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
	devcon->ClearRenderTargetView(backbuffer.Get(), color);

	swapchain->Present(0, 0);
	return 0;
}
