#include "stdafx.h"
#include "yaMangDxDll.h"
#include "GlobalVar.h"


//////////////////////////////////////////////////////////////////////////
//���� heightMap ���� �Լ�
//////////////////////////////////////////////////////////////////////////
/**
*@breif
*
*/
YAMANGDXDLL_API HRESULT HeightMapTextureImport( HWND hWnd, LPCTSTR heightMap, LPCTSTR mapTexture )
{
	if ( FAILED( D3DXCreateTextureFromFileEx( g_D3dDevice, heightMap, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_X8B8G8R8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &g_MapHeightTexture ) ) )
	{
		MessageBox( NULL, L"Could not find heightMap file", L"YaMang.DLL", MB_OK );
		return E_FAIL;
	}


	if ( FAILED( D3DXCreateTextureFromFile( g_D3dDevice, mapTexture, &g_MapTexture ) ) )
	{
		MessageBox( NULL, L"Could not find heightMapTexture file", L"YaMang.DLL", MB_OK );
		return E_FAIL;
	}


	return S_OK;
}

////////////////////////////////////////////////////////////////////////// triz
//Ŭ���̾�Ʈ �б� ���� �Լ� ������ ��
//1. ���� ���� ���� ���Ϸ� ���� �׸���(vertexBuffer)
//   ���̰� array return
//2. ���� ���� �ؽ��� ������
//3. �ε��� ����ؼ� �ֱ�(���� �Լ����� �ش� ���� ���� �Լ�ȭ)
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//���� ���� �Լ�
//���� ���� �Լ�
//���⸦ ���� �Լ�
//////////////////////////////////////////////////////////////////////////
YAMANGDXDLL_API HRESULT MapToolTextureImport( HWND hWnd, LPCTSTR toolTexture )
{
	for ( int i = 0; i < MAP_TEXTURE_COUNT; ++i )
	{
		if ( nullptr == g_MapTextureArray[i] )
		{
			if ( FAILED( D3DXCreateTextureFromFile( g_D3dDevice, toolTexture, &g_MapTextureArray[i] ) ) )
			{
				MessageBox( NULL, L"Could not find heightMapTexture file", L"YaMang.DLL", MB_OK );
				return E_FAIL;
			}
			break;
		}

	}
	return S_OK;

}


YAMANGDXDLL_API void InitGroundMesh( int row, int col )
{
	if ( g_Mesh != nullptr )
	{
		g_Mesh->Release( );
	}
	g_XHeight = col + 1;
	g_ZHeight = row + 1;

	int verticesCount = (g_XHeight)* ( g_ZHeight );
	int faceCount = ( g_XHeight - 1 ) * ( g_ZHeight - 1 ) * 2;

	//mesh�� ���� ����� ����
	//mesh�� ���� ����� �Ǹ� ��� global vertex buffer�� index buffer�� ���ǹ� �ϴ�.

	HRESULT hr = NULL;
	hr = D3DXCreateMeshFVF( faceCount, verticesCount, D3DXMESH_MANAGED | D3DXMESH_32BIT, D3DFVF_CUSTOMVERTEX, g_D3dDevice, &g_Mesh );
	if ( hr != S_OK )
	{
		MessageBox( NULL, L"CreateMesh Failed", L"YaMang.DLL", MB_OK );
		return;
	}
}


YAMANGDXDLL_API void CreateRawGround( int row, int col, float pixelSize )
{
	int verticesCount = (g_XHeight)* ( g_ZHeight );

	CUSTOMVERTEX* baseVertex = new CUSTOMVERTEX[verticesCount];
	if ( nullptr == baseVertex )
	{
		assert( false );
	}

	int startIdx = 0;
	CUSTOMVERTEX vPos0;

	vPos0.m_VertexPoint.x = -1.f * col * pixelSize * 0.5f;
	vPos0.m_VertexPoint.y = 0.0f;
	vPos0.m_VertexPoint.z = -1.f * row * pixelSize * 0.5f;
	for ( int z = 0; z <= row; ++z )
	{
		for ( int x = 0; x <= col; ++x )
		{
			baseVertex[startIdx].m_VertexPoint.x = vPos0.m_VertexPoint.x + ( pixelSize * x );
			baseVertex[startIdx].m_VertexPoint.y = 0.f;
			baseVertex[startIdx].m_VertexPoint.z = vPos0.m_VertexPoint.z + ( pixelSize * z );

			baseVertex[startIdx].m_Diffuse = D3DCOLOR_ARGB( 255, 255, 255, 255 );

			baseVertex[startIdx].m_VertexTexturePoint0.x = static_cast<float>(x)* 1 / col;
			baseVertex[startIdx].m_VertexTexturePoint0.y = static_cast<float>(z)* 1 / row;

			++startIdx;
		}
	}
	/*
	//vertex ���� Ȯ��
	for ( int i = 0; i < startIdx; ++i )
	{
	printf_s( "vertex %d: (%f, %f)\n", i, baseVertex[i].vertexPoint.x, baseVertex[i].vertexPoint.z );
	}
	*/

	void *pVertices;
	if ( FAILED( g_Mesh->LockVertexBuffer( 0, &pVertices ) ) )
	{
		if ( baseVertex )
		{
			delete[] baseVertex;
			baseVertex = nullptr;
		}
		MessageBox( NULL, L"Fail in lock VertexBuffer", L"YaMang.DLL", MB_OK );
		return;
	}
	memcpy( pVertices, baseVertex, verticesCount * sizeof( CUSTOMVERTEX ) );
	g_Mesh->UnlockVertexBuffer( );



	int indicesCount = g_XHeight * g_ZHeight + ( g_ZHeight - 2 )*( g_XHeight + 1 );
	UINT* baseIndex = new UINT[indicesCount];
	if ( nullptr == baseIndex )
	{
		assert( false );
	}

	//���� �ﰢ�� ���� �κ�
	startIdx = 0;
	for ( int z = 0; z < row; ++z )
	{
		if ( z % 2 == 0 )
		{
			int x;
			for ( x = 0; x < col + 1; ++x )
			{
				UINT a = static_cast<UINT>( x + ( z*g_XHeight ) );
				baseIndex[startIdx++] = a;
				UINT b = static_cast<UINT>( x + ( z*g_XHeight ) + g_XHeight );
				baseIndex[startIdx++] = b;
				//Log( "a: %d | b: %d\n", a, b );
			}
			if ( z != g_ZHeight - 2 )
			{
				UINT c = static_cast<UINT>( ( x - 1 ) + ( z*g_XHeight ) + g_XHeight );
				baseIndex[startIdx++] = c;
				//Log( "c: %d \n", c );
			}
		}
		else
		{
			int x;
			for ( x = col; x >= 0; --x )
			{
				UINT a = static_cast<UINT>( x + ( z*g_XHeight ) );
				baseIndex[startIdx++] = a;
				UINT b = static_cast<UINT>( x + ( z*g_XHeight ) + g_XHeight );
				baseIndex[startIdx++] = b;
				//Log( "a: %d | b: %d\n", a, b );
			}
			if ( z != g_ZHeight - 2 )
			{
				UINT c = static_cast<UINT>( ( x + 1 ) + ( z*g_XHeight ) + g_XHeight );
				baseIndex[startIdx++] = c;
				//Log( "c: %d \n", c );
			}
		}
	}

	/*
	//index buffer�� ���ֳ�?
	for ( int i = 0; i < startIdx; ++i )
	{
	printf_s( "index %d: %d\n", i, baseIndex[i] );
	}
	*/

	void* pIndices;
	if ( FAILED( g_Mesh->LockIndexBuffer( 0, &pIndices ) ) )
	{
		if ( baseVertex )
		{
			delete[] baseVertex;
			baseVertex = nullptr;
		}
		if ( baseIndex )
		{
			delete[] baseIndex;
			baseIndex = nullptr;
		}
		MessageBox( NULL, L"Fail in lock IndexBuffer", L"YaMang.DLL", MB_OK );
		return;
	}
	memcpy( pIndices, baseIndex, sizeof(UINT)*indicesCount );

	g_Mesh->UnlockIndexBuffer( );

	if ( baseVertex )
	{
		delete[] baseVertex;
		baseVertex = nullptr;
	}
	if ( baseIndex )
	{
		delete[] baseIndex;
		baseIndex = nullptr;
	}
}

//ī�޶� ����� ���ڰ� �޾Ƽ� ���ĵǵ��� ���� �ʿ� triz
YAMANGDXDLL_API void ToolViewSetting( int width, int height )
{
	// ���� ���
	D3DXMATRIXA16 world;
	D3DXMatrixIdentity( &world );
	g_D3dDevice->SetTransform( D3DTS_WORLD, &world );


	D3DXVECTOR3 vEyePt( 0.f, 70.f, -350.f );
	D3DXVECTOR3 vLookatPt( 0.f, 69.8f, -349.f );
	D3DXVECTOR3 vUpVec( 0.f, 1.f, 0.f );

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	g_D3dDevice->SetTransform( D3DTS_VIEW, &matView );

	// �������� ���
	// âũ�� ���濡 ���� ũ�� �۾����� �� ��
	//SetAspectRatio( 729, 588 );
	SetAspectRatio( width, height );
}


/*
HRESULT InitVertexBuffer( HWND hWnd )
{
D3DSURFACE_DESC ddsd;
D3DLOCKED_RECT d3drc;

g_TexHeight->GetLevelDesc( 0, &ddsd );
g_XHeight = ddsd.Width;
g_ZHeight = ddsd.Height;

if ( FAILED( g_D3dDevice->CreateVertexBuffer( ddsd.Width * ddsd.Height * sizeof( CUSTOMVERTEX ), D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &g_VertexBuffer, NULL ) ) )
{
MessageBox( NULL, L"Fail in Creating VertexBuffer", L"YaMang.exe", MB_OK );
return E_FAIL;
}

//surface lock
//Ȯ�θ� �ϰ� ������ �����Ƿ� readonly
g_TexHeight->LockRect( 0, &d3drc, NULL, D3DLOCK_READONLY );

VOID* vertices;
if ( FAILED( g_VertexBuffer->Lock( 0, g_XHeight*g_ZHeight*sizeof( CUSTOMVERTEX ), (void**)&vertices, 0 ) ) )
{
MessageBox( NULL, L"Fail in lock VertexBuffer", L"YaMang.exe", MB_OK );
return E_FAIL;
}


// Vertex ����ü ä���
CUSTOMVERTEX vertex;
CUSTOMVERTEX* vertexPointer = (CUSTOMVERTEX*)vertices;

for ( DWORD z = 0; z < g_ZHeight; ++z )
{
for ( DWORD x = 0; x < g_XHeight; ++x )
{
vertex.vertexPoint.x = (float)x - g_XHeight / 2.0f;
vertex.vertexPoint.z = -( (float)z - g_ZHeight / 2.0f );
vertex.vertexPoint.y = ( (float)( *( (LPDWORD)d3drc.pBits + x + z*( d3drc.Pitch / 4 ) ) & 0x000000ff ) ) / 10.f;

// normal ���̰�
// 0,0,0 �������� �� ������ normal ���� ���
// vertex.vertexNormal.x = vertex.vertexPoint.x;
// vertex.vertexNormal.y = vertex.vertexPoint.y;
// vertex.vertexNormal.z = vertex.vertexPoint.z;
//
// // ���� ���ͷ� ����� ��
// // ����ȭ ���ͷ� �����ϴ� ����
// D3DXVec3Normalize(&vertex.vertexNormal, &vertex.vertexNormal);

vertex.vertexTexturePoint.x = (float)x / ( g_XHeight - 1 );
vertex.vertexTexturePoint.y = (float)z / ( g_ZHeight - 1 );
*vertexPointer++ = vertex;
}
}
g_VertexBuffer->Unlock();

g_TexHeight->UnlockRect( 0 );

return S_OK;
}


HRESULT InitIdxBuffer(HWND hWnd)
{
if (FAILED(g_D3dDevice->CreateIndexBuffer((g_XHeight - 1)*(g_ZHeight - 1) * 2 * sizeof(MYINDEX), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &g_IdxBuffer, NULL)))
{
MessageBox(NULL, L"Fail in CreateIndexBuffer", L"YaMang.exe", MB_OK);
return E_FAIL;
}

MYINDEX idx;
MYINDEX* idxPointer;

if (FAILED(g_IdxBuffer->Lock(0, (g_XHeight - 1)*(g_ZHeight - 1) * 2 * sizeof(MYINDEX), (void**)&idxPointer, 0)))
{
MessageBox(NULL, L"Fail in index locking", L"YaMang.exe", MB_OK);
return E_FAIL;
}

for (UINT z = 0; z < g_ZHeight - 1; ++z)
{
for (UINT x = 0; x < g_XHeight - 1; ++x)
{
idx._0 = static_cast<UINT>( z * g_XHeight + x );
idx._1 = static_cast<UINT>( z * g_XHeight + x + 1 );
idx._2 = static_cast<UINT>( ( z + 1 ) * g_XHeight + x );
*idxPointer++ = idx;
idx._0 = static_cast<UINT>( ( z + 1 ) * g_XHeight + x );
idx._1 = static_cast<UINT>( z * g_XHeight + x + 1 );
idx._2 = static_cast<UINT>( ( z + 1 ) * g_XHeight + x + 1 );
*idxPointer++ = idx;
}
}
g_IdxBuffer->Unlock();

return S_OK;
}

*/