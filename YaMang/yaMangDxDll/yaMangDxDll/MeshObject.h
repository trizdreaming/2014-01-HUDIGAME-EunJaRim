#include <d3dx9.h>

struct MESHOBJECT
{
	//vertexbuffer�� ���� ���� ����ϴ� ���� ���� ���̹Ƿ� ����
	//LPDIRECT3DVERTEXBUFFER9 VertexBuffer = nullptr;

	LPD3DXMESH importedMesh = nullptr;
	D3DMATERIAL9* MeshMarterials = nullptr;
	LPDIRECT3DTEXTURE9* MeshTexture = nullptr;

	DWORD NumMaterials = 0L;
};