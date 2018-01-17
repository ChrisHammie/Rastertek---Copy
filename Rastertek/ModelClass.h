#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_



#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

#include "TextureClass.h"
#include <fstream>
#include <vector>
using namespace std;




class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
		
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool initialLoad(ID3D11Device*, ID3D11DeviceContext*);

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	bool InitializeBuffers(ID3D11Device*);

	int GetIndexCount();

	int GetIndice() { return indicesNew; }
	void SetIndice(int indice) { indicesNew = indice; }

	int GetVertexCount(){ return m_vertexCount; }
	void SetVertexCount(int vertex) { m_vertexCount = vertex; }


	void CreateIndiceArray();
	void SetIndiceArray(unsigned long indice[]);
	unsigned long* GetIndiceArray() { return indices; }

	int GetRun() { return run; }
	void SetRun(int oldRun) { run = oldRun; }
	
	ID3D11ShaderResourceView* GetTexture();

	//float length = 0.0f;

	XMFLOAT3 midpoint;
	XMFLOAT3 one;
	XMFLOAT3 two;
	int iCounter = 0;

private:
	
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	TextureClass* m_texture;

	ModelType* m_model;

	std::vector<XMFLOAT3> midpoints;

	VertexType* vertices;
	unsigned long indices[36];
	int indicesNew = 0;
	int count = 0;

	int run = 0;

};

#endif