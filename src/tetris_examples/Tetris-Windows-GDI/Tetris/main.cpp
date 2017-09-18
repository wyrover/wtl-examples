// ゲームプログラミングの習作テトリス#1 (WindowsGDI + raw levelなWave操作API)
//	メモ:
//		・windows7環境だとAeroを無効化するだけでFrame per secondが倍になる
#include "stdafx.h"
#include "Tetris.h"
#include "Util.h"
#include <math.h>
#include <stdarg.h>
#include <MMSystem.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")

// 定義とマクロ
#define MAX_LOADSTRING 100
#define MAX_FPS 3000			// MAX_FPS
#define GAME_SPEED_FPS MAX_FPS	// ゲーム時間FPS(tick countと読んだ方が適切?)
#define VIEW_SPEED_FPS MAX_FPS	// 描画のFPS(一般的な意味でのFPS)
#define IF_KEYPRESS(vk) (::GetAsyncKeyState(vk) & 0x8000) // vk(virtual key)がpressされてるかどうか

#define SCORE_BLOCK_LANDING 5
#define SCORE_LINE_DELETE 10

#define ROTATE_LEFT 0
#define ROTATE_RIGHT 1

#define SOUND_DEBUG_SAMPLE L"sound.wav"
#define SOUND_BACKGROUND_MUSIC SOUND_DEBUG_SAMPLE
#define SOUND_MOVE SOUND_DEBUG_SAMPLE
#define SOUND_ROTATE SOUND_DEBUG_SAMPLE
#define SOUND_LINE_DELETE SOUND_DEBUG_SAMPLE
#define SOUND_GAMEOVER SOUND_DEBUG_SAMPLE
#define SOUND_ERROR SOUND_DEBUG_SAMPLE

// グローバル変数 (Windows関係)
HINSTANCE hInst;								// 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING];					// タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名
HWND g_hWnd = NULL;
HDC g_mDC = NULL;
RECT g_windowRect;

// 使用するフォントの定義
HFONT font_MSUIGothic = ::CreateFont(
		15,                   // フォントの高さ(大きさ)。
		0,                    // フォントの幅。普通０。
		0,                    // 角度。０でＯＫ。
		0,                    // 同じく角度。これも０。
		FW_DONTCARE,          // 文字の太さ。
		FALSE,                // フォントがイタリックならTRUEを指定。
		FALSE,                // 下線を引くならTRUE。
		FALSE,                // 取り消し線を引くならTRUE。
		SHIFTJIS_CHARSET,     // フォントの文字セット。このままでＯＫ。
		OUT_DEFAULT_PRECIS,   // 出力精度の設定。このままでＯＫ。
		CLIP_DEFAULT_PRECIS,  // クリッピング精度。このままでＯＫ。
		DRAFT_QUALITY,        // フォントの出力品質。このままでＯＫ。
		DEFAULT_PITCH,        // フォントのピッチとファミリを指定。このままでＯＫ。
		_T("MS UI Gothic") // フォントのタイプフェイス名の指定。これは見たまんま。
    );

// グローバル変数 (テトリス関係)
#define FIELD_X_SIZE 10	// テトリス世界の横幅
#define FIELD_Y_SIZE 20 // テトリス世界の縦幅
int g_field[FIELD_X_SIZE][FIELD_Y_SIZE] = {0};			// 固定化されたものに追加して、プレイヤーの"生きてる"ブロックの座標も含まれた配列
int g_puted_field[FIELD_X_SIZE][FIELD_Y_SIZE] = {0};	// 実際に固定化されたブロックの座標格納用配列
int g_focusX = FIELD_X_SIZE / 2;	// 現在値(X)
int g_focusY = 0;					// 現在値(Y)
int g_degree_index = 0; // 0 - TETRIS_R_MAX
DWORD g_frameRate = 0;	// フレームレート計測用
DWORD g_frame = 0;		// フレーム数計測用
int g_tetris_type = 0;	// テトリス種別(IとかOとか)
int g_status = 0;		// ゲームの状態(状態遷移に利用)
int g_score = 0;		// スコア合計
int g_time = 0;			// 経過秒数
bool bgm_enabled = false;	// BGM ON/OFF
#define TETRIS_TYPE_MAX 7	// テトリスの種類添え字数
#define TETRIS_R_MAX 4		// テトリスの角度添え字数
#define TETRIS_X_SIZE 4		// テトリスのX添え字数
#define TETRIS_Y_SIZE 4		// テトリスのY添え字数
// テトリスのデータ配列(左の添字から、テトリス種別、角度(0,90,180,270)、x、y)
int blocks[TETRIS_TYPE_MAX][TETRIS_R_MAX][TETRIS_X_SIZE][TETRIS_Y_SIZE] = {
	{ // I
		{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
		{{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},
		{{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}},
		{{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}}
	},
	{ // J
		{{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
		{{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
		{{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
		{{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}}
	},
	{ // L
		{{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
		{{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
		{{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
		{{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}}
	},
	{ // S
		{{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},
		{{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
		{{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
		{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}
	},
	{ // Z
		{{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},
		{{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
		{{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
		{{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}
	},
	{ // T
		{{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},
		{{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
		{{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
		{{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}
	},
	{ // O
		{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
		{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
		{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
		{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}}
	}
};

// グローバル変数（テトリス関係、デバッグ用)

// 関数定義
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

// 指定された座標に、指定された種別、角度のテトリスをセットすることが出来るかどうか判定するための関数
bool hitTestTetrisOverlap(int type, int r, int xx, int yy)
{
	for(int y=0; y<TETRIS_Y_SIZE; y++){
		for(int x=0; x<TETRIS_X_SIZE; x++){
			// テンプレートのブロックはそこにまずある??
			if( blocks[type][r][x][y] == 1 ){
				// 現在のアクティブな位置に変換
				int active_x = x + xx;
				int active_y = y + yy;

				// その位置は画面内に収まってる？？
				// 収まってないときは収まってない方向ごとに現在位置を補正してあげる
				if(active_x < 0){ // 左すぎ
					return true;
				}

				if(FIELD_X_SIZE - 1 < active_x){ // 右すぎ
					return true;
				}

				if(FIELD_Y_SIZE - 1 < active_y){ // 下すぎ
					return true;
				}

				// 移動先が他のブロックと重なってるか判定
				if(g_puted_field[active_x][active_y] == 1){
					return true;
				}
			}
		}
	}
	return false;
}

void onPaint(HWND hWnd, HDC hdc)
{
	// 背景全部塗りつぶし
	FillRectBrush(hdc, g_windowRect.left, g_windowRect.top,
		g_windowRect.right - g_windowRect.left,
		g_windowRect.bottom - g_windowRect.top, RGB(0,0,0));

	// テトラミノの二次元配列を描画する
	int block_width;
	int block_height;
	block_width = block_height = 20;
	COLORREF block_color = RGB(255,0,0);
	COLORREF fixed_block_color = RGB(0,255,0);
	COLORREF background_color = RGB(255,255,255);
	
	int padding_top = 30;
	int padding_left = 20;
	for(int y=0; y<FIELD_Y_SIZE; y++){
		for(int x=0; x<FIELD_X_SIZE; x++){
			if(g_puted_field[x][y] == 1){ // 配置済みテトリスの描画
				BorderedRect(hdc, padding_left + x * block_width, padding_top + y * block_height, block_width, block_height, fixed_block_color);
			}else if(g_field[x][y] == 1){ // アクティブな動いてるテトリスの描画
				BorderedRect(hdc, padding_left + x * block_width, padding_top + y * block_height, block_width, block_height, block_color);
			}
		}
	}

	// スコア表示部分の描画
	// 背景の描画
	int scoreboard_x = FIELD_X_SIZE * block_width + padding_left + 20;
	int scoreboard_y = padding_top;
	FillRectBrush(hdc, scoreboard_x, scoreboard_y, 200, 20, RGB(255,255,255));
	
	RECT rect;
	rect.left = scoreboard_x;
	rect.top = scoreboard_y;
	rect.right = rect.left + 200;
	rect.bottom = rect.top + 20;
	::DrawFormatText(hdc, &rect, DT_RIGHT, L"%d", g_score);
	::DrawFormatText(hdc, &rect, DT_LEFT, L"スコア:");
	
	// 経過時間の表示
	FillRectBrush(hdc, scoreboard_x, scoreboard_y + 20 + 20, 200, 20, RGB(255, 255, 255));
	rect.left = scoreboard_x;
	rect.top = scoreboard_y + 20 + 20;
	rect.right = rect.left + 200;
	rect.bottom = rect.top + 20;
	::DrawFormatText(hdc, &rect, DT_RIGHT, L"%d", g_time);
	::DrawFormatText(hdc, &rect, DT_LEFT, L"経過時間(秒):");

	// FPSの描画(デバッグオーバーレイ)
	HFONT oldFont = (HFONT)::SelectObject(hdc, font_MSUIGothic);
	::TextFormatOut(hdc, 0, 0, L"FPS: %d/s (%df)", g_frameRate, g_frame);
	::SelectObject(hdc, oldFont);
	::DeleteObject(font_MSUIGothic);
	
	// 外枠描画
	drawRectColor(hdc, padding_left, padding_top, FIELD_X_SIZE * block_width, FIELD_Y_SIZE * block_width, RGB(0,255,0), 1);
}

void rotateTetrisIndex(int index)
{
	g_degree_index = index;
	trace(L"g_degree_index: %d\n", g_degree_index);
}

void rotateTetris(void)
{
	if(++g_degree_index > TETRIS_R_MAX - 1){
		g_degree_index = 0;
	}
}

void reverseRotateTetris(void)
{
	if(--g_degree_index < 0)
		g_degree_index = TETRIS_R_MAX - 1;
}

void flipTetris()
{
	if(++g_tetris_type >= TETRIS_TYPE_MAX)
		g_tetris_type = 0;

	// テトリスを変更したときは、角度も元に戻す
	rotateTetrisIndex(0);
}

// 現在の設定でN秒あたりのフレーム数を
// 描画のFPSではなくて、ゲーム内時間の方
int getFramesOfSeconds(int seconds)
{
	return seconds * GAME_SPEED_FPS;
}

// ランダムにテトリスを変更します
void randomChangeTetris()
{
	g_tetris_type = rand() % TETRIS_TYPE_MAX; // 0-6がランダムに返却
	rotateTetrisIndex(rand() % TETRIS_R_MAX); // 角度は0-3の4方向
}

void GameMain_main(HWND hWnd)
{
	// 1秒に一回、プレイヤーのブロックを一つ下に移動させる
	static int timeCount = 0;	// FPSを固定化させるために使用します
	if(timeCount++ > getFramesOfSeconds(1)){
		timeCount = 0;
		g_focusY++;
		g_time += 1; // 経過時間を1sec加算します
		::PlaySound(SOUND_MOVE, NULL, SND_FILENAME | SND_ASYNC);
	}
	
	// フィールドの初期化
	for(int y=0; y<FIELD_Y_SIZE; y++){
		for(int x=0; x<FIELD_X_SIZE; x++){
			g_field[x][y] = 0;
		}
	}
	
	// 現在アクティブなテトラミノの描画
	// フォーカスしてる場所を原点として、現在選択中のテトリスを描画する
	for(int y=0; y<TETRIS_Y_SIZE; y++){
		for(int x=0; x<TETRIS_X_SIZE; x++){
			if( blocks[g_tetris_type][g_degree_index][x][y] == 1){
				// ゲームの有効範囲内だよね？
				int active_x = x + g_focusX;
				int active_y = y + g_focusY;
				g_field[active_x][active_y] = 1;
			}
		}
	}

	// 現在アクティブなテトラミノの着地判定
	// テトラミノが、自分よりも下のブロックがあることを検出した、あるいは地面があることを検出した場合
	bool landing_flag = false;
	for(int x=0; x<TETRIS_X_SIZE; x++){
		for(int y=TETRIS_Y_SIZE-1; y>=0; y--){
			bool block_found = false; // そのY軸にブロックがあるかどうかを表す

			// 一番最初に1(存在)するブロックがあったとき
			// その下にブロックが設置されていたら設置フラグをONにする
			if( block_found == false && blocks[g_tetris_type][g_degree_index][x][y] == 1 ){
				// ブロックがそのY軸ですでに一度でも見つかっている場合はこの処理を行わない
				block_found = true;

				// 絶対座標に変換して自分よりもひとつ下にブロックあるか検証
				if( g_puted_field[g_focusX + x][g_focusY + y + 1] == 1 ){
					landing_flag = true;
				}

				// あるいは、Y軸の最下行に到達しているか
				if( g_focusY + y >= FIELD_Y_SIZE - 1 ){
					landing_flag = true;
				}
			}
		}
	}

	// 着地してた場合は現在の場所に固定化
	if(landing_flag){
		for(int y=0; y<TETRIS_Y_SIZE; y++){
			for(int x=0; x<TETRIS_X_SIZE; x++){
				if(blocks[g_tetris_type][g_degree_index][x][y] == 1){
					g_puted_field[g_focusX + x][g_focusY + y] = 1;
				}
			}
		}

		// スコア加算
		g_score += SCORE_BLOCK_LANDING;

		// 次のテトラミノをランダムに選択
		randomChangeTetris();

		// 初期位置に配置する
		g_focusX = (FIELD_X_SIZE - 1) / 2;
		g_focusY = 0;
	}

	// テトラミノの消去処理
	// 横一列fillされてたら、その行を削除して
	// すべてのブロックを一個下に移動します
	bool line_delete_flag = false;
	for(int y=0; y<FIELD_Y_SIZE; y++){
		bool line_fill_flag = true;
		for(int x=0; x<FIELD_X_SIZE; x++){
			if(g_puted_field[x][y] == 0){
				line_fill_flag = false; // 行内に一個でも穴が発見されたら以後x軸のループはもったいないので抜けます
				break;
			}
		}

		// 1行すべてブロックが配置されていた行(y)があれば
		// その行のブロックを削除して、それよりも上行のブロックを全て一つ下に移動させる
		if(line_fill_flag == true){
			trace(L"detect fill line: %d(index) (all line: %dgyou)", y, FIELD_Y_SIZE);
			for(int x=0; x<FIELD_X_SIZE; x++){
				g_puted_field[x][y] = 0;
			}
			trace(L"clear line");

			// この行よりも上のブロックをすべて一個下に下げる処理
			trace(L"move upper lines");
			for(int yy=y; yy>0; yy--){
				for(int xx=0; xx<FIELD_X_SIZE; xx++){
					g_puted_field[xx][yy] = g_puted_field[xx][yy-1];
				}
			}

			// スコア加算
			g_score += SCORE_LINE_DELETE;

			// 行を削除した判定
			line_delete_flag = true;
		}
	}

	// 一行でも行を削除したときは専用の音を流す
	if(line_delete_flag == true){
		::PlaySound(SOUND_LINE_DELETE, NULL, SND_FILENAME | SND_ASYNC);
	}

	// ゲームオーバー判定
	// 一番上の行にブロックが固定化されていた場合、ゲームオーバー状態に移行します
	for(int x=0; x<FIELD_X_SIZE; x++){
		if( g_puted_field[x][0] == 1 ){
			g_status = 1;
		}
	}
}

void Game_init(){
	// 乱数の初期化
	srand((unsigned int)time(0));
	randomChangeTetris();

	if(bgm_enabled){
		::mciPlayBGM(SOUND_BACKGROUND_MUSIC, 0.1);
	}
}

void GameMain_gameOver(HWND hWnd){
	::PlaySound(SOUND_GAMEOVER, NULL, SND_FILENAME);
}

void GameMain_quit(){
	trace(L"フォントの解放\n");
	::DeleteObject(font_MSUIGothic);
}

// falseを返却すると終了処理に移行する
bool GameMain(HWND hWnd)
{
	switch(g_status){
	case 0:
		GameMain_main(hWnd);
		break;
	case 1:
		GameMain_gameOver(hWnd);
		return false;
		break;
	default:
		trace(L"UNDEFINED TYPE: %d\n", g_status);
	}

	return true;
}

// テトリスを回転させても大丈夫な時だけ回転させる
// directは方向、1が右、それ以外が左
void rotateTetrisSafety(int type, int x, int y, int direct)
{
	// 回転させる前に、回転させても大丈夫かの確認処理を入れる
	// 推定した回転後の座標、角度、種類のテトリスに対して
	// 現在のワールドで当たり判定行う
	int backup_degree = g_degree_index;

	if(direct == 1)
		rotateTetris();
	else
		reverseRotateTetris();

	int r = g_degree_index;
	rotateTetrisIndex(backup_degree);

	// 移動先が他のブロックと重なってなかったときのみ移動が成立する
	// その上でその場所が画面外だったら補正してあげる
	if(::hitTestTetrisOverlap(g_tetris_type, r, g_focusX, g_focusY) == true){
		::PlaySound(SOUND_ERROR, NULL, SND_FILENAME | SND_ASYNC);
	}else{
		rotateTetris(); // 実際に回転させます
		::PlaySound(SOUND_ROTATE, NULL, SND_FILENAME | SND_ASYNC);
	}
}

void onKeyDown(DWORD key)
{
	switch(key){
	case 'F':
		flipTetris(); // テトリスの種類変更
		break;
	case 'E': // 右回転
		rotateTetrisSafety(g_tetris_type, g_focusX, g_focusY, ROTATE_RIGHT); // 左回転
		break;
	case 'Q':
		rotateTetrisSafety(g_tetris_type, g_focusX, g_focusY, ROTATE_LEFT); // 左回転
		break;
	case 'R':
		rotateTetrisSafety(g_tetris_type, g_focusX, g_focusY, ROTATE_RIGHT); // 右回転
		break;
	case 'Z': // 強制終了
		g_status = 1;
		break;
	default:
		// プレイヤーの入力値を第一に処理
		bool move_key_pressed = false;

		// 現在の座標を保存
		int cur_x = g_focusX;
		int cur_y = g_focusY;
		if(IF_KEYPRESS('A') || IF_KEYPRESS('H') || IF_KEYPRESS(VK_LEFT)){
			cur_x--;
			move_key_pressed = true;
		}
		if(IF_KEYPRESS('S') || IF_KEYPRESS('J') || IF_KEYPRESS(VK_DOWN)){
			cur_y++;
			move_key_pressed = true;
		}
		if(IF_KEYPRESS('D') || IF_KEYPRESS('L') || IF_KEYPRESS(VK_RIGHT)){
			cur_x++;
			move_key_pressed = true;
		}
		
		// 指定された座標、角度、種類のテトリスに対して
		// 現在のワールドでヒットテストを行う
		if(move_key_pressed == true){
			// 移動先が他のブロックと重なってなかったときのみ移動が成立する
			// その上でその場所が画面外だったら補正してあげる
			if(::hitTestTetrisOverlap(g_tetris_type, g_degree_index, cur_x, cur_y) == false){ // 重なってなかったとき
				g_focusX = cur_x; // 移動を成立させる
				g_focusY = cur_y;

				// 移動が成立したときのみ音を出す
				::PlaySound(SOUND_MOVE, NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		break;
	}
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TETRIS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// アプリケーションの初期化を実行します:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TETRIS));

	// メイン メッセージ ループ:
	::timeBeginPeriod(1);
	
	double host_timescale = 1;
	double view_max_fps = VIEW_SPEED_FPS; // 描画のFPS制限
	// 上のがいわゆるnet_graphのFPSだと思う
	double game_max_fps = GAME_SPEED_FPS * host_timescale; // ゲームスピードのFPS制限
	// こっちが一般的にはtick??

	DWORD dwTime = ::timeGetTime();
	DWORD fps_after = dwTime;
	DWORD fps_before = fps_after;
	DWORD frame = 0;
	DWORD currentTime = dwTime;
	double gameSpeedWaitTime = (1.0 / game_max_fps * 1000.0);
	double gameSpeedNextTime = dwTime + gameSpeedWaitTime;
	
	double viewSpeedWaitTime = (1.0 / view_max_fps * 1000.0);
	double viewSpeedNextTime = dwTime + gameSpeedWaitTime;

	Game_init();

	while(true){
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)){
			if(!GetMessage(&msg, NULL, 0, 0))
				return msg.wParam;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}else{
			// FPS測定(1000ms秒あたりのframe数を計測)
			currentTime = ::timeGetTime();
			if(currentTime - fps_before >= 1000){ // 前回から1秒間(1000ms)経過していた場合
				fps_before = currentTime;
				g_frameRate = g_frame;
				g_frame = 0;	// フレーム数を次秒の計測のためにリセット
			}
	
			// FPS制限(1/60おきにコードが実行されるようにする)
			if(currentTime >= gameSpeedNextTime ){ // 次回の予定実行時を過ぎていた場合
				gameSpeedNextTime += gameSpeedWaitTime;

				// メイン処理
				if( GameMain(msg.hwnd) == false ){
					break; // 終了処理へ
				}
			}else{
				// 表示上のFPS描画しなければならないかチェックする
				if(currentTime >= viewSpeedNextTime ){
					viewSpeedNextTime += viewSpeedWaitTime;

					onPaint(g_hWnd, g_mDC);
					::InvalidateRect(g_hWnd, NULL, FALSE);
					g_frame++;
				}else{
					Sleep(1);
				}
			}
		}
	}

	// いろいろ後片付けを書く
	trace(L"終了処理\n");
	GameMain_quit();

	::timeEndPeriod(1);
	return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
//  コメント:
//
//    この関数および使い方は、'RegisterClassEx' 関数が追加された
//    Windows 95 より前の Win32 システムと互換させる場合にのみ必要です。
//    アプリケーションが、関連付けられた
//    正しい形式の小さいアイコンを取得できるようにするには、
//    この関数を呼び出してください。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TETRIS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TETRIS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します。
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   
   return TRUE;
}


//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:  メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND	- アプリケーション メニューの処理
//  WM_PAINT	- メイン ウィンドウの描画
//  WM_DESTROY	- 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HWND desktop;
	static HBITMAP hBitmap = NULL;
	RECT rect;

	switch (message)
	{
	case WM_CREATE:
		desktop = ::GetDesktopWindow();
		::GetWindowRect(desktop, &rect);
		
		::SetWindowPos(hWnd, NULL, rect.right / 4, (rect.bottom - rect.top) / 4, 510, 510, 0);

		::GetClientRect(hWnd, &g_windowRect);
		::FillRect(::GetDC(hWnd), &g_windowRect, ::CreateSolidBrush(RGB(0,0,0)));

		// メモリDCの作成
		{
			HDC hdc = ::GetDC(hWnd);

			g_mDC = ::CreateCompatibleDC(hdc); // メモリDCの作成
			hBitmap = ::CreateCompatibleBitmap(hdc, g_windowRect.right, g_windowRect.bottom); // メモリDC用のビットマップ作成
			::SelectObject(g_mDC, hBitmap); // 関連付け
		}
		break;
	case WM_KEYDOWN:
		onKeyDown(wParam);
		::InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// 選択されたメニューの解析:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, g_windowRect.left, g_windowRect.top, g_windowRect.right, g_windowRect.bottom, g_mDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		::GetClientRect(hWnd, &g_windowRect);
		
		if(wParam == SIZE_RESTORED){ // ウインドウのサイズ変更時
			::GetClientRect(hWnd, &g_windowRect);

			// 既存のメモリDCがあればそれを破棄
			if( g_mDC != NULL ){
				::DeleteObject(::g_mDC); // mDCを破棄
				::DeleteObject(hBitmap); // 関連するbitmapも破棄
			}

			// メモリDCの作成
			{
				HDC hdc = ::GetDC(hWnd);
				g_mDC = ::CreateCompatibleDC(hdc); // メモリDCの作成
				hBitmap = ::CreateCompatibleBitmap(hdc, g_windowRect.right, g_windowRect.bottom); // メモリDC用のビットマップ作成
				::SelectObject(g_mDC, hBitmap); // 関連付け
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND:
		return FALSE;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
