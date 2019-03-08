#pragma once
#include "GfxApp.h"
#include <vector>

class TriangleApp : public GFXApp
{
private:

	VertexPositionColor Triangle[3] = 
	{ 
		{Vector3(0.0f, 0.5f, 0.5f), Colors::Red},
		{Vector3(0.5f, -0.5f, 0.5f), Colors::Green},
		{Vector3(-0.5f, -0.5f, 0.5f), Colors::Blue} 
	};

public:
	ComPtr<ID3D11InputLayout>												m_pLayout;
	ComPtr<ID3D11VertexShader>												m_pVS;
	ComPtr<ID3D11PixelShader>												m_pPS;
	ComPtr<ID3D11Buffer>													m_pVBuffer;

	//DXTK-Specific hotness!
	std::unique_ptr<DirectX::CommonStates>									m_states;
	std::unique_ptr<DirectX::BasicEffect>									m_effect;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>	m_batch;

	virtual int main(UINT, UINT);
	virtual int initScene();
	virtual int initPipeline();
	virtual int Render();

	TriangleApp();
	~TriangleApp();
};