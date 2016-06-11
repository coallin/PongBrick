//==============================================================================
// Author: SEN KA (HAL Tokyo AT11C273-19 �w�Дԍ� 50326)
//==============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib"/* �}���`���f�B�A���� */)		// �V�X�e�������擾�ɕK�v

// ��ʃT�C�Y
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)

// ���_�t�H�[�}�b�g
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1/* �e�N�X�`�����W */)

//==============================================================================
// �\���̒�`
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;	// ���W�ϊ��ςݒ��_(�ʏ�1.0f)
	D3DCOLOR color;	// ���_�F
	D3DXVECTOR2 tex; // �e�N�X�`��
}VERTEX_2D;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
LPDIRECT3DDEVICE9 GetDevice(void);

#endif