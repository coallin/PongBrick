////============================================================================
// Author: SEN KA (HAL Tokyo AT11C273-19 学籍番号 50326)
//==============================================================================

//==============================================================================
// ヘッダファイル
//==============================================================================
#include "main.h"
#include "polygon.h"

//==============================================================================
// マクロ定義
//==============================================================================
// テクスチャファイル名
#define POLYGON_TEXTURENAME1 "bg.tga"
#define POLYGON_TEXTURENAME2 "globe.tga"
// ポリゴン位置
#define POLYGON_POS_X	(100)
#define POLYGON_POS_Y	(100)
// ポリゴンサイズ
#define POLYGON_WIDTH	(800)
#define POLYGON_HEIGHT	(600)
// ポリゴン
#define NUM_VERTEX (8)		// 頂点数
#define NUM_POLYGON (2)		// ポリゴン数

// 地球の座標のオフセット
#define EARTH_MOVE (100)


//==============================================================================
// プロトタイプ宣言
//==============================================================================
void MakeVertexPolygon( LPDIRECT3DDEVICE9 pDevice );							// 頂点座標の作成

//==============================================================================
// グローバル変数
//==============================================================================
VERTEX_2D g_aVertex[ 5 ][ NUM_VERTEX ];											// 頂点数
LPDIRECT3DTEXTURE9 g_pTexturePolygon[ 5 ] = { NULL ,NULL ,NULL ,NULL ,NULL };	// テクスチャインタフェース
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferPolygon = NULL;								// 頂点バッファのポインタ

//==============================================================================
// ポリゴンの初期化
//==============================================================================
void InitPolygon( void )
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 g_pD3DDevice = GetDevice();

	// テクスチャファイルの読み込み
	if ( FAILED( D3DXCreateTextureFromFile( g_pD3DDevice, POLYGON_TEXTURENAME1, &g_pTexturePolygon[ 0 ]/* テクスチャサーフェスに入る */ ) ) )
	{
		MessageBox( NULL, "ERROR!!", "ERROR!!", NULL );
	}
	if ( FAILED( D3DXCreateTextureFromFile( g_pD3DDevice, POLYGON_TEXTURENAME2, &g_pTexturePolygon[ 1 ]/* テクスチャサーフェスに入る */ ) ) )
	{
		MessageBox( NULL, "ERROR!!", "ERROR!!", NULL );
	}

	// 頂点座標の作成
	MakeVertexPolygon(g_pD3DDevice);

	// 頂点フォーマットの設定
	g_pD3DDevice->SetFVF( FVF_VERTEX_2D );
}

//==============================================================================
// ポリゴンの描画
//==============================================================================
void DrawPolygon( void )
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ポリゴンの描画
	pDevice->SetTexture( 0, g_pTexturePolygon[ 0 ] );
	//g_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, NUM_POLYGON, &g_aVertex[ 0 ], sizeof( VERTEX_2D ) );
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0/* データのオフセット */, NUM_POLYGON );

	pDevice->SetTexture( 0, g_pTexturePolygon[ 1 ] );
	//g_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, NUM_POLYGON, &g_aVertex[ 1 ], sizeof( VERTEX_2D ) );
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 4/* データのオフセット */, NUM_POLYGON );

}

//==============================================================================
// ポリゴンの更新
//==============================================================================
void UpdatePolygon( void )
{

}

//==============================================================================
// 終了処理
//==============================================================================
void UninitPolygon( void )
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = GetDevice();

	// マクロセーフリリースで作れば便利

	// デバイスを解放
	if ( g_pD3DDevice != NULL )
	{
		g_pD3DDevice->Release();	// Direct3DDeviceのメモリエリア解放
		g_pD3DDevice = NULL;
	}
	// テクスチャを解放
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
// 頂点座標の作成
//==============================================================================
void MakeVertexPolygon( LPDIRECT3DDEVICE9 pDevice )
{
	// 頂点ポインタの作成
	VERTEX_2D *pVtx;

	// デバイスに頂点バッファを作成
	if ( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_2D )*NUM_VERTEX,/* 確保するバッファサイズ */
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufferPolygon,
		NULL
		) ) )
	{
		MessageBox( NULL, "!!", "!!", NULL );
	}

	// バッファをロックし仮想アドレスを取得する
	g_pVtxBufferPolygon->Lock( 0, 0, ( void** ) &pVtx, 0 );

	//// 頂点座標の設定
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

	//// 頂点色の設定
	//g_aVertex[ 0 ][ 0 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//g_aVertex[ 0 ][ 1 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//g_aVertex[ 0 ][ 2 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//g_aVertex[ 0 ][ 3 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	//// 頂点座標の設定
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

	//// 頂点色の設定
	//g_aVertex[ 1 ][ 0 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//g_aVertex[ 1 ][ 1 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//g_aVertex[ 1 ][ 2 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//g_aVertex[ 1 ][ 3 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	// 頂点座標の設定
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

	// 頂点色の設定
	pVtx[ 0 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 1 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 2 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 3 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	// 頂点座標の設定
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

	// 頂点色の設定
	pVtx[ 4 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 5 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 6 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 7 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	// バッファのアンロック
	g_pVtxBufferPolygon->Unlock();

	// バッファからGPUに転送
	pDevice->SetStreamSource(
		0,
		g_pVtxBufferPolygon, /* Steamをつなぎたいバッファ */
		0, /* データのオフセット（先頭から送る） */
		sizeof( VERTEX_2D ) /* ストライド量（バイト単位） */
	);
}