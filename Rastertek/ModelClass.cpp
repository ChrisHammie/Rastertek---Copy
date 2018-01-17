
#include "ModelClass.h"


ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

	m_texture = 0;

	

	m_model = NULL;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}

bool ModelClass::initialLoad(ID3D11Device * device, ID3D11DeviceContext * deviceContext)
{
	bool result;


	result = Initialize(device, deviceContext, "stone01.tga", "Flat.txt");
	if (!result)
	{
		return false;
	}
	/*result = Initialize(device, deviceContext, "water.tga", "square.txt");
	if (!result)
	{
		return false;
	}*/

	

	
	return true;
}


bool ModelClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFileName, char* modelFilename)
{
	bool result;

	// Load in the model data,
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}


	// Initialize the vertex and index buffers.
	
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}
	
	
	


	result = LoadTexture(device, deviceContext, textureFileName);
	if (!result)
	{
		return false;
	}

	

	return true;
}


void ModelClass::Shutdown()
{
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();
	ReleaseTexture();
	// Release the model data.
	ReleaseModel();
	return;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

void ModelClass::CreateIndiceArray()
{
	m_indexCount = 36;
	/*indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return;
	}*/
}

void ModelClass::SetIndiceArray(unsigned long indice[])
{
	/*m_indexCount = 36;
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return;
	}*/
	//indices = indice;
	for (int i = 0; i < 36; i++)
	{
		indices[i] = indice[i];
	}
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_texture->GetTexture();
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	// Set the number of vertices in the vertex array.
	//m_vertexCount = 4;

	// Set the number of indices in the index array.
	//m_indexCount = 6;

	//std::vector<XMFLOAT3> midpoints(m_vertexCount / 6);

	midpoints.reserve(m_vertexCount / 6);

	//midpoints.size = m_vertexCount / 6;

	// Create the vertex array.
	m_indexCount = 36;
	


					 // Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = NULL;

	/*delete[] indices;
	indices = NULL;*/

	/*delete[] m_model;
	m_model = NULL;*/

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	if (indices)
	{
		delete[] indices;
		for (int i = 0; i < 36; i++)
		{
			indices[i] = NULL;
		}
		
	}

	/*if (vertices)
	{
		delete[] vertices;
		vertices = NULL;

	}*/

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool ModelClass::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* fileName)
{
	bool result;

	m_texture = new TextureClass;
	if (!m_texture)
	{
		return false;
	}

	result = m_texture->Initalize(device, deviceContext, fileName);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTexture()
{
	if (m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = 0;
	}
	return;
}

bool ModelClass::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;
	//bool result;


	// Open the model file.
	fin.open(filename);

	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	//m_indexCount = m_vertexCount;

	

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (i = 0; i<m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	

	// Load the vertex array and index array with data.
	for (int i = 0; i<m_vertexCount; i++)
	{
		
		vertices[i].position = XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = XMFLOAT2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = XMFLOAT3(m_model[i].nx, m_model[i].ny, m_model[i].nz);



		if (iCounter == 1)
		{
			one = vertices[i].position;

		}
		else if (iCounter == 2)
		{
			two = vertices[i].position;

			midpoint.x = (one.x + two.x) / 2;
			midpoint.y = (one.y + two.y) / 2;
			midpoint.z = (one.z + two.z) / 2;

			midpoints.push_back(midpoint);
		}
		iCounter++;
		if (iCounter == 6)
		{
			iCounter = 0;
		}

		if (run == 1)
		{
			
			indices[i+6] = i+6;
			
		}
		else
		{
			indices[i] = i;
		}
		
		
		//indicesNew++;
		//m_indexCount++;
	}

	
	run++;

	return true;
}

void ModelClass::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return;
}