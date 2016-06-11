//==============================================================================
// Author: SEN KA (HAL Tokyo AT11C273-19 学籍番号 50326)
//==============================================================================
//------------------------------------------------------------------------------

//==============================================================================
// ヘッダファイル
//==============================================================================
#include "main.h"
#include "polygon.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define CLASS_NAME		"ポリゴン表示"						// ウィンドウクラスの名前
#define WINDOW_NAME		"ポリゴン表示処理"					// ウィンドウの名前
#define WINDOW_STYLE (WS_OVERLAPPEDWINDOW)					// ウィンドウスタイル

//==============================================================================
// グローバル変数
//==============================================================================
LPDIRECT3D9 g_pD3D = NULL;					// D3D9インターフェイス
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		// Direct3Dデバイスインターフェース


//==============================================================================
// プロトタイプ宣言
//==============================================================================
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );		// ウィンドウプロシージャ
HRESULT Init( HINSTANCE hInstance, HWND hWnd, bool bWindow );						// 初期化処理
void Uninit( void );																// D3D終了処理
void Update( void );																// 更新処理
void Draw( void );																	// 描画処理
LPDIRECT3DDEVICE9 GetDevice( void );												// デバイスポインタ伝送


//==============================================================================
// メイン関数
//==============================================================================
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	// 使わない変数の警告防止
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	// 再描画範囲指定
	RECT cr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT dr;

	// ウィンドウサイズ指定
	AdjustWindowRect( &cr, WINDOW_STYLE, FALSE ); // FALSE:メニューの有無
	// デスクトップサイズ取得
	GetWindowRect( GetDesktopWindow(), &dr );

	// 描画範囲計算
	int width = cr.right - cr.left;
	int height = cr.bottom - cr.top;

	// デスクトップ中心計算
	int dwidth = dr.right - dr.left;
	int dheight = dr.bottom - dr.top;

	// 描画開始座標
	int sw = width > dwidth ? 0 : (dwidth -width) / 2;
	int sh = width > dwidth ? 0 : (dheight -height) /2;

	// ウィンドウの構造体
	WNDCLASSEX wcex = {
		sizeof( WNDCLASSEX ),					// WNDCLASSEXのメモリサイズを指定
		CS_CLASSDC,								// 表示するウィンドウのスタイルを設定
		WndProc,								// ウィンドウプロシージャのアドレス（関数名）を指定
		0,										// 通常は使用しないので”０”を指定
		0,										// 通常は使用しないので”０”を指定
		hInstance,								// WinMainのパラメータのインスタンスハンドルを設定
		NULL,									// EXEファイルのアイコンを指定
		LoadCursor( NULL,IDC_ARROW ),			// マウスカーソルを指定
		( HBRUSH )( COLOR_WINDOW + 1 ),			// ウィンドウのクライアント領域の背景色を設定
		NULL,									// ウィンドウにつけるメニューを設定
		CLASS_NAME,								// ウィンドウクラスの名前
		NULL									// 小さいアイコンが設定された場合の情報を記述
	};

	// ウィンドウクラスの登録
	RegisterClassEx( &wcex );

	// ローカル変数
	HWND hWnd;
	MSG msg;

	// ウィンドウの作成
	hWnd = CreateWindowEx(
		0,										// 拡張ウィンドウスタイル
		CLASS_NAME,								// ウィンドウクラスの名前
		WINDOW_NAME,							// ウィンドウの名前
		WINDOW_STYLE,							// ウィンドウスタイル
		sw,										// ウィンドウの左上ｘ座標
		sh,										// ウィンドウの左上ｙ座標
		width,									// ウィンドウの幅
		height,									// ウィンドウの高さ
		NULL,									// 親ウィンドウのハンドル
		NULL,									// メニューハンドルまたは
		hInstance,								// インスタンスハンドル
		NULL									// ウィンドウ作成データ
	);

	// ウィンドウの表示
	ShowWindow( hWnd, nCmdShow );				// 指定されたウィンドウの表示
	UpdateWindow( hWnd );						// ウィンドウの内容

	Init(hInstance, hWnd, TRUE);

	// 分解能の設定
	timeBeginPeriod( 1 );

	// 各カウンターの初期化
	DWORD dwFrameCount = 0;
	DWORD dwCurrentTime = 0;
	DWORD dwExecLastTime = timeGetTime();		// 現在の時刻をミリ秒単位で取得
	DWORD dwFPSLastTime = dwExecLastTime;



	// メッセージループ
	// 呼び出し側スレッドのメッセージキューからメッセージを取得
	while ( 1 )
	{
		// メッセージが来るときの判断
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 )
		{
			// Windowsの処理
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
			dwCurrentTime = timeGetTime();			// 現在の時刻をミリ秒単位で取得

			// 60フレーム/秒単位で描画する
			if ( ( dwCurrentTime - dwExecLastTime >= 1000 / 60 ) )
			{
				dwExecLastTime = dwCurrentTime;		// 処理した時間を保存
				// DirectXの処理
				Update();
				Draw();
			}
		}
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass( CLASS_NAME, wcex.hInstance );

	return ( int ) msg.wParam;
}

//==============================================================================
// ウィンドウプロシージャ
//==============================================================================
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
		UINT nID;

		// 終了ボタンが押された場合
		case WM_DESTROY:						// ウィンドウ破棄のメッセージの場合
			PostQuitMessage( 0 );				// ”WM_QUIT”メッセージを返す
			break;
		default:
			break;
	}

	// ほかのメッセージの場合なら既定の処理を提供
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//==============================================================================
// D3D初期化
// HRESULEは戻り値（中身は実行状態の具体内容）。bWindow はウィンドウモード・全画面モードフラグ
//==============================================================================
HRESULT Init( HINSTANCE hInstance, HWND hWnd, bool bWindow )
{
	// D3D Interface取得
	D3DPRESENT_PARAMETERS d3dpp = {}; // 初期化
	D3DDISPLAYMODE d3ddm;

	// D3D9インターフェイスの取得
	g_pD3D = Direct3DCreate9( D3D9b_SDK_VERSION );
	if ( g_pD3D == NULL )
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードの取得
	if ( FAILED( g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
	{
		// ディスプレイモードの戻り値を失敗したかどうかを判断する
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメーターの設定
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );						// d3dppの中の内容全部０で初期化する

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;

	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;									// triple buffer の数

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;									// フールスクリーンモードするときウィンドウスタイルも変更する必要。
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// D3Dデバイスの作成
	if ( FAILED( g_pD3D->CreateDevice( 
		D3DADAPTER_DEFAULT/* デフォルトグラフィックアダプターセレクト */, 
		D3DDEVTYPE_HAL, /* 描画処理タイプ：ハードウエア */
		hWnd, /* 描画対象ウィンドウ（フォーカスウィンドウハンドル） */
		D3DCREATE_HARDWARE_VERTEXPROCESSING, /* デバイス作成オプションフラグ：ハードウェア頂点処理 */
		&d3dpp, /* その他設定（前で設定されたもの）のポインタ */
		&g_pD3DDevice /* グローバル変数ポインタのポインタ */
		) ) )
	{
		if ( FAILED( g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT/* デフォルトグラフィックアダプターセレクト */,
			D3DDEVTYPE_HAL, /* 描画処理タイプ：ハードウエア */
			hWnd, /* 描画対象ウィンドウ（フォーカスウィンドウハンドル） */
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, /* デバイス作成オプションフラグ：ソフトウェア頂点処理 */
			&d3dpp, /* その他設定（前で設定されたもの）のポインタ */
			&g_pD3DDevice /* グローバル変数ポインタのポインタ */
			) ) )
		{
			if ( FAILED( g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT/* デフォルトグラフィックアダプターセレクト */,
				D3DDEVTYPE_REF, /* 描画処理タイプ：ソフトウェア */
				hWnd, /* 描画対象ウィンドウ（フォーカスウィンドウハンドル） */
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, /* デバイス作成オプションフラグ：ハードウェア頂点処理 */
				&d3dpp, /* その他設定（前で設定されたもの）のポインタ */
				&g_pD3DDevice /* グローバル変数ポインタのポインタ */
				) ) )
			{
				return E_FAIL;
			}
		}
	}

	// レンダーステート設定
	g_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE/* 設定名 */, TRUE/* 設定値 */ );
	g_pD3DDevice->SetRenderState( D3DRS_SRCBLEND/* 設定名 */, D3DBLEND_SRCALPHA/* 設定値 */ );
	g_pD3DDevice->SetRenderState( D3DRS_DESTBLEND/* 設定名 */, D3DBLEND_INVSRCALPHA/* 設定値 */ );
	g_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER/* 縮小のとき使用するフィルター */, D3DTEXF_POINT );
	g_pD3DDevice->SetSamplerState( 0,D3DSAMP_MAGFILTER/* 拡大のとき使用するフィルター */,D3DTEXF_POINT );
	g_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU/* UV座標設定 */, D3DTADDRESS_WRAP );
	g_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );

	// ポリゴン初期化
	InitPolygon();
	return S_OK;
}

//==============================================================================
// D3D終了処理
//==============================================================================
void Uninit( void )
{
	// インタフェースをリリース
	if ( g_pD3D != NULL )
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	// ポリゴンポインタの終了処理
	UninitPolygon();

	// 分解能の終了
	timeEndPeriod( 1 );
}

//==============================================================================
// 更新処理
//==============================================================================
void Update( void )
{

}

//==============================================================================
// 描画処理
//==============================================================================
void Draw( void )
{
	// バックバッファとZバッファのクリア
	g_pD3DDevice->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET |					/* 色 */
		D3DCLEAR_ZBUFFER,					/* 深度情報 */
		D3DCOLOR_RGBA( 0, 0, 0, 0 ),		/* 色の初期化 */
		1.0f,								/* 深度の初期化 範囲0~1（手前~奥）*/
		0									/* D3DCLEAR_SPENCILの初期化 0~255 */
	);

	// 描画の開始
	if ( SUCCEEDED( g_pD3DDevice->BeginScene() /* １フレーム一回の描画開始命令 */ ) )
	{
		DrawPolygon();
		// 描画終了
		g_pD3DDevice->EndScene();	/* １フレーム一回の描画終了命令 */
	}

	// 前バッファと裏バッファのスワップ（画面上で見えるようになる）
	g_pD3DDevice->Present( NULL, NULL, NULL, NULL );
}

//==============================================================================
// デバイスポインタ伝送
//==============================================================================
LPDIRECT3DDEVICE9 GetDevice( void )
{
	// デバイスポインタをリターンする
	return g_pD3DDevice;
}