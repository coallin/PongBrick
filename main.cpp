//==============================================================================
// Author: SEN KA (HAL Tokyo AT11C273-19 �w�Дԍ� 50326)
//==============================================================================
//------------------------------------------------------------------------------

//==============================================================================
// �w�b�_�t�@�C��
//==============================================================================
#include "main.h"
#include "polygon.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define CLASS_NAME		"�|���S���\��"						// �E�B���h�E�N���X�̖��O
#define WINDOW_NAME		"�|���S���\������"					// �E�B���h�E�̖��O
#define WINDOW_STYLE (WS_OVERLAPPEDWINDOW)					// �E�B���h�E�X�^�C��

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3D9 g_pD3D = NULL;					// D3D9�C���^�[�t�F�C�X
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		// Direct3D�f�o�C�X�C���^�[�t�F�[�X


//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );		// �E�B���h�E�v���V�[�W��
HRESULT Init( HINSTANCE hInstance, HWND hWnd, bool bWindow );						// ����������
void Uninit( void );																// D3D�I������
void Update( void );																// �X�V����
void Draw( void );																	// �`�揈��
LPDIRECT3DDEVICE9 GetDevice( void );												// �f�o�C�X�|�C���^�`��


//==============================================================================
// ���C���֐�
//==============================================================================
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	// �g��Ȃ��ϐ��̌x���h�~
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	// �ĕ`��͈͎w��
	RECT cr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT dr;

	// �E�B���h�E�T�C�Y�w��
	AdjustWindowRect( &cr, WINDOW_STYLE, FALSE ); // FALSE:���j���[�̗L��
	// �f�X�N�g�b�v�T�C�Y�擾
	GetWindowRect( GetDesktopWindow(), &dr );

	// �`��͈͌v�Z
	int width = cr.right - cr.left;
	int height = cr.bottom - cr.top;

	// �f�X�N�g�b�v���S�v�Z
	int dwidth = dr.right - dr.left;
	int dheight = dr.bottom - dr.top;

	// �`��J�n���W
	int sw = width > dwidth ? 0 : (dwidth -width) / 2;
	int sh = width > dwidth ? 0 : (dheight -height) /2;

	// �E�B���h�E�̍\����
	WNDCLASSEX wcex = {
		sizeof( WNDCLASSEX ),					// WNDCLASSEX�̃������T�C�Y���w��
		CS_CLASSDC,								// �\������E�B���h�E�̃X�^�C����ݒ�
		WndProc,								// �E�B���h�E�v���V�[�W���̃A�h���X�i�֐����j���w��
		0,										// �ʏ�͎g�p���Ȃ��̂Łh�O�h���w��
		0,										// �ʏ�͎g�p���Ȃ��̂Łh�O�h���w��
		hInstance,								// WinMain�̃p�����[�^�̃C���X�^���X�n���h����ݒ�
		NULL,									// EXE�t�@�C���̃A�C�R�����w��
		LoadCursor( NULL,IDC_ARROW ),			// �}�E�X�J�[�\�����w��
		( HBRUSH )( COLOR_WINDOW + 1 ),			// �E�B���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�
		NULL,									// �E�B���h�E�ɂ��郁�j���[��ݒ�
		CLASS_NAME,								// �E�B���h�E�N���X�̖��O
		NULL									// �������A�C�R�����ݒ肳�ꂽ�ꍇ�̏����L�q
	};

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx( &wcex );

	// ���[�J���ϐ�
	HWND hWnd;
	MSG msg;

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(
		0,										// �g���E�B���h�E�X�^�C��
		CLASS_NAME,								// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,							// �E�B���h�E�̖��O
		WINDOW_STYLE,							// �E�B���h�E�X�^�C��
		sw,										// �E�B���h�E�̍��゘���W
		sh,										// �E�B���h�E�̍��゙���W
		width,									// �E�B���h�E�̕�
		height,									// �E�B���h�E�̍���
		NULL,									// �e�E�B���h�E�̃n���h��
		NULL,									// ���j���[�n���h���܂���
		hInstance,								// �C���X�^���X�n���h��
		NULL									// �E�B���h�E�쐬�f�[�^
	);

	// �E�B���h�E�̕\��
	ShowWindow( hWnd, nCmdShow );				// �w�肳�ꂽ�E�B���h�E�̕\��
	UpdateWindow( hWnd );						// �E�B���h�E�̓��e

	Init(hInstance, hWnd, TRUE);

	// ����\�̐ݒ�
	timeBeginPeriod( 1 );

	// �e�J�E���^�[�̏�����
	DWORD dwFrameCount = 0;
	DWORD dwCurrentTime = 0;
	DWORD dwExecLastTime = timeGetTime();		// ���݂̎������~���b�P�ʂŎ擾
	DWORD dwFPSLastTime = dwExecLastTime;



	// ���b�Z�[�W���[�v
	// �Ăяo�����X���b�h�̃��b�Z�[�W�L���[���烁�b�Z�[�W���擾
	while ( 1 )
	{
		// ���b�Z�[�W������Ƃ��̔��f
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 )
		{
			// Windows�̏���
			if ( msg.message == WM_QUIT )
			{
				break;
			}
			else
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();			// ���݂̎������~���b�P�ʂŎ擾

			// 60�t���[��/�b�P�ʂŕ`�悷��
			if ( ( dwCurrentTime - dwExecLastTime >= 1000 / 60 ) )
			{
				dwExecLastTime = dwCurrentTime;		// �����������Ԃ�ۑ�
				// DirectX�̏���
				Update();
				Draw();
			}
		}
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass( CLASS_NAME, wcex.hInstance );

	return ( int ) msg.wParam;
}

//==============================================================================
// �E�B���h�E�v���V�[�W��
//==============================================================================
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
		UINT nID;

		// �I���{�^���������ꂽ�ꍇ
		case WM_DESTROY:						// �E�B���h�E�j���̃��b�Z�[�W�̏ꍇ
			PostQuitMessage( 0 );				// �hWM_QUIT�h���b�Z�[�W��Ԃ�
			break;
		default:
			break;
	}

	// �ق��̃��b�Z�[�W�̏ꍇ�Ȃ����̏������
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//==============================================================================
// D3D������
// HRESULE�͖߂�l�i���g�͎��s��Ԃ̋�̓��e�j�BbWindow �̓E�B���h�E���[�h�E�S��ʃ��[�h�t���O
//==============================================================================
HRESULT Init( HINSTANCE hInstance, HWND hWnd, bool bWindow )
{
	// D3D Interface�擾
	D3DPRESENT_PARAMETERS d3dpp = {}; // ������
	D3DDISPLAYMODE d3ddm;

	// D3D9�C���^�[�t�F�C�X�̎擾
	g_pD3D = Direct3DCreate9( D3D9b_SDK_VERSION );
	if ( g_pD3D == NULL )
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h�̎擾
	if ( FAILED( g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
	{
		// �f�B�X�v���C���[�h�̖߂�l�����s�������ǂ����𔻒f����
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�[�̐ݒ�
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );						// d3dpp�̒��̓��e�S���O�ŏ���������

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;

	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;									// triple buffer �̐�

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;									// �t�[���X�N���[�����[�h����Ƃ��E�B���h�E�X�^�C�����ύX����K�v�B
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// D3D�f�o�C�X�̍쐬
	if ( FAILED( g_pD3D->CreateDevice( 
		D3DADAPTER_DEFAULT/* �f�t�H���g�O���t�B�b�N�A�_�v�^�[�Z���N�g */, 
		D3DDEVTYPE_HAL, /* �`�揈���^�C�v�F�n�[�h�E�G�A */
		hWnd, /* �`��ΏۃE�B���h�E�i�t�H�[�J�X�E�B���h�E�n���h���j */
		D3DCREATE_HARDWARE_VERTEXPROCESSING, /* �f�o�C�X�쐬�I�v�V�����t���O�F�n�[�h�E�F�A���_���� */
		&d3dpp, /* ���̑��ݒ�i�O�Őݒ肳�ꂽ���́j�̃|�C���^ */
		&g_pD3DDevice /* �O���[�o���ϐ��|�C���^�̃|�C���^ */
		) ) )
	{
		if ( FAILED( g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT/* �f�t�H���g�O���t�B�b�N�A�_�v�^�[�Z���N�g */,
			D3DDEVTYPE_HAL, /* �`�揈���^�C�v�F�n�[�h�E�G�A */
			hWnd, /* �`��ΏۃE�B���h�E�i�t�H�[�J�X�E�B���h�E�n���h���j */
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, /* �f�o�C�X�쐬�I�v�V�����t���O�F�\�t�g�E�F�A���_���� */
			&d3dpp, /* ���̑��ݒ�i�O�Őݒ肳�ꂽ���́j�̃|�C���^ */
			&g_pD3DDevice /* �O���[�o���ϐ��|�C���^�̃|�C���^ */
			) ) )
		{
			if ( FAILED( g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT/* �f�t�H���g�O���t�B�b�N�A�_�v�^�[�Z���N�g */,
				D3DDEVTYPE_REF, /* �`�揈���^�C�v�F�\�t�g�E�F�A */
				hWnd, /* �`��ΏۃE�B���h�E�i�t�H�[�J�X�E�B���h�E�n���h���j */
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, /* �f�o�C�X�쐬�I�v�V�����t���O�F�n�[�h�E�F�A���_���� */
				&d3dpp, /* ���̑��ݒ�i�O�Őݒ肳�ꂽ���́j�̃|�C���^ */
				&g_pD3DDevice /* �O���[�o���ϐ��|�C���^�̃|�C���^ */
				) ) )
			{
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�ݒ�
	g_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE/* �ݒ薼 */, TRUE/* �ݒ�l */ );
	g_pD3DDevice->SetRenderState( D3DRS_SRCBLEND/* �ݒ薼 */, D3DBLEND_SRCALPHA/* �ݒ�l */ );
	g_pD3DDevice->SetRenderState( D3DRS_DESTBLEND/* �ݒ薼 */, D3DBLEND_INVSRCALPHA/* �ݒ�l */ );
	g_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER/* �k���̂Ƃ��g�p����t�B���^�[ */, D3DTEXF_POINT );
	g_pD3DDevice->SetSamplerState( 0,D3DSAMP_MAGFILTER/* �g��̂Ƃ��g�p����t�B���^�[ */,D3DTEXF_POINT );
	g_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU/* UV���W�ݒ� */, D3DTADDRESS_WRAP );
	g_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );

	// �|���S��������
	InitPolygon();
	return S_OK;
}

//==============================================================================
// D3D�I������
//==============================================================================
void Uninit( void )
{
	// �C���^�t�F�[�X�������[�X
	if ( g_pD3D != NULL )
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	// �|���S���|�C���^�̏I������
	UninitPolygon();

	// ����\�̏I��
	timeEndPeriod( 1 );
}

//==============================================================================
// �X�V����
//==============================================================================
void Update( void )
{

}

//==============================================================================
// �`�揈��
//==============================================================================
void Draw( void )
{
	// �o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET |					/* �F */
		D3DCLEAR_ZBUFFER,					/* �[�x��� */
		D3DCOLOR_RGBA( 0, 0, 0, 0 ),		/* �F�̏����� */
		1.0f,								/* �[�x�̏����� �͈�0~1�i��O~���j*/
		0									/* D3DCLEAR_SPENCIL�̏����� 0~255 */
	);

	// �`��̊J�n
	if ( SUCCEEDED( g_pD3DDevice->BeginScene() /* �P�t���[�����̕`��J�n���� */ ) )
	{
		DrawPolygon();
		// �`��I��
		g_pD3DDevice->EndScene();	/* �P�t���[�����̕`��I������ */
	}

	// �O�o�b�t�@�Ɨ��o�b�t�@�̃X���b�v�i��ʏ�Ō�����悤�ɂȂ�j
	g_pD3DDevice->Present( NULL, NULL, NULL, NULL );
}

//==============================================================================
// �f�o�C�X�|�C���^�`��
//==============================================================================
LPDIRECT3DDEVICE9 GetDevice( void )
{
	// �f�o�C�X�|�C���^�����^�[������
	return g_pD3DDevice;
}