#ifndef _GAME_H_
#define _GAME_H_

#include "Graphics\Display.h"
#include "Audio/SoundManager.h"
#include "ScreenManager.h"
#include "EntityManager.h"
#include "Gamelogic\Input.h"
#include "Gamelogic\Timer.h"
#include "Graphics\DeferredRender.h"
#include "Graphics\DeferredBuffer.h"
#include "Gamelogic\Stats.h"
#include "Graphics\GaussianBlur.h"

#include <d3d11.h>	//temp
#include <dxgidebug.h>

class Game
{
private:
	void Update(double time, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	void Render();
	void CheckInput();
	void SetViewport();
	void ReadOptions();
	HRESULT CreateDirect3DContext(HWND wndHandle);
	HRESULT DepthStencilInitialicer();

public:
	Game();
	~Game();
	void InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	void InitGameRedo(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	WPARAM MainLoop(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

private:
	int m_width,m_height;

	SoundManager* m_soundManager;
	SpacePart* m_backgroundPartSys;
	ShaderHandler m_partShader, m_glowshader;
	ScreenManager* m_screenManager;
	EntityManager* m_entityManager;
	Stats* m_statsManager;
	DeferredBuffer m_deferredBuffer;
	DeferredRender m_deferredRender;
	Input* m_input;
	Display* m_display;
	MSG m_winMSG;
	ID3D11DeviceContext* m_deviceContext = nullptr;
	ID3D11Device* m_device = nullptr;
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11RenderTargetView* m_backbufferRTV = nullptr;
	ID3D11DepthStencilView* m_depthStencilView = nullptr;
	ID3D11Texture2D* m_depthStencil = nullptr;
	ID3D11SamplerState* m_sampleState = nullptr;
	ID3D11BlendState1* m_blendState = nullptr;
	ID3D11DepthStencilState* m_depthStencilState = nullptr;
	//Fixa in GaussianFilteret härräräärä
	GaussianBlur* m_gaussianFilter;
public:
};

#endif 

