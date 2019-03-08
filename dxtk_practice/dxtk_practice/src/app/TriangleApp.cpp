#include "TriangleApp.h"
#include <iostream>

//#pragma comment(lib, "DirectXTK.lib")

int TriangleApp::initScene() 
{
	

	return 0;
}

TriangleApp::TriangleApp()
{
	_hInstance = GetHInstance();
	_hPrevInstance = GetHPrevInstance();
}

int TriangleApp::main(UINT wX, UINT wY)
{
	std::cout << "This is a simple multicolored triangle." << std::endl;

	m_wX = wX;
	m_wY = wY;

	initWindow();
	initGraphics();
	initPipeline();

	mainLoop();

	return 0;
}

int TriangleApp::initPipeline() 
{
	m_states = std::make_unique<CommonStates>(dev.Get());

	m_effect = std::make_unique<BasicEffect>(dev.Get());
	m_effect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;
	
	//OOOH I think I know what these effects are, now..
	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	
	HRESULT hr = dev->CreateInputLayout(VertexPositionColor::InputElements, VertexPositionColor::InputElementCount, shaderByteCode, byteCodeLength, m_pLayout.ReleaseAndGetAddressOf());
	if (hr != S_OK) {
		std::cout << "Error creating input layout!" << std::endl;
	}

	//This looks like where I make that little primitivebatch thing. I feed it the goods, it draws me the things.... yeaaaaaahhhhhh....
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(devcon.Get());

	return 0;
}

int TriangleApp::Render() 
{
	FLOAT color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };

	devcon->ClearRenderTargetView(backbuffer.Get(), color);

	devcon->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	devcon->OMSetDepthStencilState(m_states->DepthNone(), 0);
	devcon->RSSetState(m_states->CullNone());

	m_effect->Apply(devcon.Get());

	devcon->IASetInputLayout(m_pLayout.Get());

	m_batch->Begin();

	m_batch->DrawTriangle(Triangle[0], Triangle[1], Triangle[2]);

	m_batch->End();

	swapchain->Present(0, 0);

	return 0;
}