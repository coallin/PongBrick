////============================================================================
// Author: SEN KA (HAL Tokyo AT11C273-19 �w�Дԍ� 50326)
//==============================================================================

//==============================================================================
// �w�b�_�t�@�C��
//==============================================================================
#include "main.h"
#include "polygon.h"

//==============================================================================
// �}�N����`
//==============================================================================
// �e�N�X�`���t�@�C����
#define POLYGON_TEXTURENAME1 "bg.tga"
#define POLYGON_TEXTURENAME2 "globe.tga"
// �|���S���ʒu
#define POLYGON_POS_X	(100)
#define POLYGON_POS_Y	(100)
// �|���S���T�C�Y
#define POLYGON_WIDTH	(800)
#define POLYGON_HEIGHT	(600)
// �|���S��
#define NUM_VERTEX (8)		// ���_��
#define NUM_POLYGON (2)		// �|���S����

// �n���̍��W�̃I�t�Z�b�g
#define EARTH_MOVE (100)


//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
void MakeVertexPolygon( LPDIRECT3DDEVICE9 pDevice );							// ���_���W�̍쐬

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
VERTEX_2D g_aVertex[ 5 ][ NUM_VERTEX ];											// ���_��
LPDIRECT3DTEXTURE9 g_pTexturePolygon[ 5 ] = { NULL ,NULL ,NULL ,NULL ,NULL };	// �e�N�X�`���C���^�t�F�[�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferPolygon = NULL;								// ���_�o�b�t�@�̃|�C���^

//==============================================================================
// �|���S���̏�����
//==============================================================================
void InitPolygon( void )
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 g_pD3DDevice = GetDevice();

	// �e�N�X�`���t�@�C���̓ǂݍ���
	if ( FAILED( D3DXCreateTextureFromFile( g_pD3DDevice, POLYGON_TEXTURENAME1, &g_pTexturePolygon[ 0 ]/* �e�N�X�`���T�[�t�F�X�ɓ��� */ ) ) )
	{
		MessageBox( NULL, "ERROR!!", "ERROR!!", NULL );
	}
	if ( FAILED( D3DXCreateTextureFromFile( g_pD3DDevice, POLYGON_TEXTURENAME2, &g_pTexturePolygon[ 1 ]/* �e�N�X�`���T�[�t�F�X�ɓ��� */ ) ) )
	{
		MessageBox( NULL, "ERROR!!", "ERROR!!", NULL );
	}

	// ���_���W�̍쐬
	MakeVertexPolygon(g_pD3DDevice);

	// ���_�t�H�[�}�b�g�̐ݒ�
	g_pD3DDevice->SetFVF( FVF_VERTEX_2D );
}

//==============================================================================
// �|���S���̕`��
//==============================================================================
void DrawPolygon( void )
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �|���S���̕`��
	pDevice->SetTexture( 0, g_pTexturePolygon[ 0 ] );
	//g_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, NUM_POLYGON, &g_aVertex[ 0 ], sizeof( VERTEX_2D ) );
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0/* �f�[�^�̃I�t�Z�b�g */, NUM_POLYGON );

	pDevice->SetTexture( 0, g_pTexturePolygon[ 1 ] );
	//g_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, NUM_POLYGON, &g_aVertex[ 1 ], sizeof( VERTEX_2D ) );
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 4/* �f�[�^�̃I�t�Z�b�g */, NUM_POLYGON );

}

//==============================================================================
// �|���S���̍X�V
//==============================================================================
void UpdatePolygon( void )
{

}

//==============================================================================
// �I������
//==============================================================================
void UninitPolygon( void )
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = GetDevice();

	// �}�N���Z�[�t�����[�X�ō��Ε֗�

	// �f�o�C�X�����
	if ( g_pD3DDevice != NULL )
	{
		g_pD3DDevice->Release();	// Direct3DDevice�̃������G���A���
		g_pD3DDevice = NULL;
	}
	// �e�N�X�`�������
	if ( g_pTexturePolygon[ 0 ] != NULL )
	{
		g_pTexturePolygon[ 0 ]->Release();
		g_pTexturePolygon[ 0 ] = NULL;
	}
	if ( g_pTexturePolygon[ 1 ] != NULL )
	{
		g_pTexturePolygon[ 1 ]->Release();
		g_pTexturePolygon[ 1 ] = NULL;
	}
}

//==============================================================================
// ���_���W�̍쐬
//==============================================================================
void MakeVertexPolygon( LPDIRECT3DDEVICE9 pDevice )
{
	// ���_�|�C���^�̍쐬
	VERTEX_2D *pVtx;

	// �f�o�C�X�ɒ��_�o�b�t�@���쐬
	if ( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_2D )*NUM_VERTEX,/* �m�ۂ���o�b�t�@�T�C�Y */
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufferPolygon,
		NULL
		) ) )
	{
		MessageBox( NULL, "!!", "!!", NULL );
	}

	// �o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferPolygon->Lock( 0, 0, ( void** ) &pVtx, 0 );

	//// ���_���W�̐ݒ�
	//g_aVertex[ 0 ][ 0 ].pos = D3DXVECTOR3( 0, 0, 0.0f );
	//g_aVertex[ 0 ][ 1 ].pos = D3DXVECTOR3( POLYGON_WIDTH, 0, 0.0f );
	//g_aVertex[ 0 ][ 2 ].pos = D3DXVECTOR3( 0, POLYGON_HEIGHT, 0.0f );
	//g_aVertex[ 0 ][ 3 ].pos = D3DXVECTOR3( POLYGON_WIDTH, POLYGON_HEIGHT, 0.0f );

	//g_aVertex[ 0 ][ 0 ].tex = D3DXVECTOR2( 0, 0 );
	//g_aVertex[ 0 ][ 1 ].tex = D3DXVECTOR2( 1, 0 );
	//g_aVertex[ 0 ][ 2 ].tex = D3DXVECTOR2( 0, 0.75 );
	//g_aVertex[ 0 ][ 3 ].tex = D3DXVECTOR2( 1, 0.75 );

	//g_aVertex[ 0 ][ 0 ].rhw = 1.0f;
	//g_aVertex[ 0 ][ 1 ].rhw = 1.0f;
	//g_aVertex[ 0 ][ 2 ].rhw = 1.0f;
	//g_aVertex[ 0 ][ 3 ].rhw = 1.0f;

	//// ���_�F�̐ݒ�
	//g_aVertex[ 0 ][ 0 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//g_aVertex[ 0 ][ 1 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//g_aVertex[ 0 ][ 2 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//g_aVertex[ 0 ][ 3 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	//// ���_���W�̐ݒ�
	//g_aVertex[ 1 ][ 0 ].pos = D3DXVECTOR3( 0, 300, 0.0f );
	//g_aVertex[ 1 ][ 1 ].pos = D3DXVECTOR3( POLYGON_WIDTH, 300, 0.0f );
	//g_aVertex[ 1 ][ 2 ].pos = D3DXVECTOR3( 0, POLYGON_HEIGHT + 300, 0.0f );
	//g_aVertex[ 1 ][ 3 ].pos = D3DXVECTOR3( POLYGON_WIDTH, POLYGON_HEIGHT + 300, 0.0f );

	//g_aVertex[ 1 ][ 0 ].tex = D3DXVECTOR2( 0, 0 );
	//g_aVertex[ 1 ][ 1 ].tex = D3DXVECTOR2( 1, 0 );
	//g_aVertex[ 1 ][ 2 ].tex = D3DXVECTOR2( 0, 1 );
	//g_aVertex[ 1 ][ 3 ].tex = D3DXVECTOR2( 1, 1 );

	//g_aVertex[ 1 ][ 0 ].rhw = 1.0f;
	//g_aVertex[ 1 ][ 1 ].rhw = 1.0f;
	//g_aVertex[ 1 ][ 2 ].rhw = 1.0f;
	//g_aVertex[ 1 ][ 3 ].rhw = 1.0f;

	//// ���_�F�̐ݒ�
	//g_aVertex[ 1 ][ 0 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//g_aVertex[ 1 ][ 1 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//g_aVertex[ 1 ][ 2 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//g_aVertex[ 1 ][ 3 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	// ���_���W�̐ݒ�
	pVtx[ 0 ].pos = D3DXVECTOR3( 0, 0, 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3( POLYGON_WIDTH, 0, 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( 0, POLYGON_HEIGHT, 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3( POLYGON_WIDTH, POLYGON_HEIGHT, 0.0f );

	pVtx[ 0 ].tex = D3DXVECTOR2( 0, 0 );
	pVtx[ 1 ].tex = D3DXVECTOR2( 1, 0 );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0, 0.75 );
	pVtx[ 3 ].tex = D3DXVECTOR2( 1, 0.75 );

	pVtx[ 0 ].rhw = 1.0f;
	pVtx[ 1 ].rhw = 1.0f;
	pVtx[ 2 ].rhw = 1.0f;
	pVtx[ 3 ].rhw = 1.0f;

	// ���_�F�̐ݒ�
	pVtx[ 0 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 1 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 2 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 3 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	// ���_���W�̐ݒ�
	pVtx[ 4 ].pos = D3DXVECTOR3( 0, 0 + EARTH_MOVE, 0.0f );
	pVtx[ 5 ].pos = D3DXVECTOR3( POLYGON_WIDTH, 0 + EARTH_MOVE, 0.0f );
	pVtx[ 6 ].pos = D3DXVECTOR3( 0, POLYGON_HEIGHT + EARTH_MOVE, 0.0f );
	pVtx[ 7 ].pos = D3DXVECTOR3( POLYGON_WIDTH, POLYGON_HEIGHT + EARTH_MOVE, 0.0f );

	pVtx[ 4 ].tex = D3DXVECTOR2( 0, 0 );
	pVtx[ 5 ].tex = D3DXVECTOR2( 1, 0 );
	pVtx[ 6 ].tex = D3DXVECTOR2( 0, 1 );
	pVtx[ 7 ].tex = D3DXVECTOR2( 1, 1 );

	pVtx[ 4 ].rhw = 1.0f;
	pVtx[ 5 ].rhw = 1.0f;
	pVtx[ 6 ].rhw = 1.0f;
	pVtx[ 7 ].rhw = 1.0f;

	// ���_�F�̐ݒ�
	pVtx[ 4 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 5 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 6 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 7 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	// �o�b�t�@�̃A�����b�N
	g_pVtxBufferPolygon->Unlock();

	// �o�b�t�@����GPU�ɓ]��
	pDevice->SetStreamSource(
		0,
		g_pVtxBufferPolygon, /* Steam���Ȃ������o�b�t�@ */
		0, /* �f�[�^�̃I�t�Z�b�g�i�擪���瑗��j */
		sizeof( VERTEX_2D ) /* �X�g���C�h�ʁi�o�C�g�P�ʁj */
	);
}