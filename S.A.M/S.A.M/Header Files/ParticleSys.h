#pragma once
#ifndef _PARTICLESYS_H_
#define _PARTICLESYS_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <vector>
#include <d3dcompiler.h>
#include <cstdlib>
#include <ctime>
#include "WICTextureLoader.h"
using namespace std;
using namespace DirectX;

class PartSys
{
public:
	PartSys();
	~PartSys();
	bool CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	bool CreateShaders(ID3D11Device* device);
	bool PartRend(ID3D11DeviceContext*);
	void updatePart(ID3D11DeviceContext* deviceContext, float time, float partSpeed);
private:
	ID3D11InputLayout* m_vertexLayout = nullptr;
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11GeometryShader* m_geometryShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11ShaderResourceView* m_partTex = nullptr;
	int m_amountOfPart;
	XMFLOAT4* m_partPos;
	ID3D11Buffer *m_vertexBuffer = nullptr;

};



#endif