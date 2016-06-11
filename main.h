//==============================================================================
// Author: SEN KA (HAL Tokyo AT11C273-19 学籍番号 50326)
//==============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib"/* マルチメディア命令 */)		// システム時刻取得に必要

// 画面サイズ
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)

// 頂点フォーマット
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1/* テクスチャ座標 */)

//==============================================================================
// 構造体定義
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;	// 座標変換済み頂点(通常1.0f)
	D3DCOLOR color;	// 頂点色
	D3DXVECTOR2 tex; // テクスチャ
}VERTEX_2D;

//==============================================================================
// プロトタイプ宣言
//==============================================================================
LPDIRECT3DDEVICE9 GetDevice(void);

#endif