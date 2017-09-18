///////////////////////////////////////////////////////////////////////////////
//	テトリス

#include "el.h"

#define MAIN_SCREEN 1

void MainScreen(void);

DDOBJ block;			// ブロック画像のビットマップ
int field[21][12];		// 画面データ

// 落ちてくるピース（７種）
struct Piece {
	int x, y;
} piece[7][4][4] = {
	// 長い棒
	0, 2, 1, 2, 2, 2, 3, 2,
	1, 0, 1, 1, 1, 2, 1, 3,
	0, 2, 1, 2, 2, 2, 3, 2,
	1, 0, 1, 1, 1, 2, 1, 3,
	// 正方形
	1, 1, 2, 1, 1, 2, 2, 2,
	1, 1, 2, 1, 1, 2, 2, 2,
	1, 1, 2, 1, 1, 2, 2, 2,
	1, 1, 2, 1, 1, 2, 2, 2,
	// 逆Ｌの字
	0, 1, 0, 2, 1, 2, 2, 2,
	0, 3, 1, 1, 1, 2, 1, 3,
	0, 2, 1, 2, 2, 2, 2, 3,
	1, 1, 1, 2, 1, 3, 2, 1,
	// Ｌの字
	0, 2, 1, 2, 2, 1, 2, 2,
	0, 1, 1, 1, 1, 2, 1, 3,
	0, 2, 0, 3, 1, 2, 2, 2,
	1, 1, 1, 2, 1, 3, 2, 3,
	// 右下がり階段
	1, 1, 2, 1, 2, 2, 3, 2,
	2, 1, 2, 2, 3, 0, 3, 1,
	1, 1, 2, 1, 2, 2, 3, 2,
	2, 1, 2, 2, 3, 0, 3, 1,
	// 左下がり階段
	1, 2, 2, 1, 2, 2, 3, 1,
	2, 0, 2, 1, 3, 1, 3, 2,
	1, 2, 2, 1, 2, 2, 3, 1,
	2, 0, 2, 1, 3, 1, 3, 2,
	// 砲台
	0, 2, 1, 1, 1, 2, 2, 2,
	0, 2, 1, 1, 1, 2, 1, 3,
	0, 2, 1, 2, 1, 3, 2, 2,
	1, 1, 1, 2, 1, 3, 2, 2,
};

///////////////////////////////////////////////////////////////////////////////
//	メイン関数

int elMain("テトリス");
{
	elWindow(192, 416, FALSE);
	elLoop()
	{
		elSetScreen(MAIN_SCREEN, MainScreen());
	}
	elExitMain();
}

///////////////////////////////////////////////////////////////////////////////
//	ウインドウ生成関数

void elCreate(void)
{
	elDraw::Screen(192, 416);
	// ブロック画像読み込み
	block = elDraw::LoadObject("block.bmp");
	// 画面データ初期化
	for (int y = 0; y < 21; y++) {
		for (int x = 0; x < 12; x++) {
			// 画面の左右と下の隅をブロックにして中は空に
			if (x == 0 || x == 11 || y == 20) field[y][x] = 8;
			else field[y][x] = 0;
		}
	}
	elCallScreen(MAIN_SCREEN);
}

///////////////////////////////////////////////////////////////////////////////
//	キーボード関数

void elKeyboard(void)
{
	case VK_ESCAPE:
	{
		elDraw::Exit();
		break;
	}
	elExitKeyboard();
}

///////////////////////////////////////////////////////////////////////////////
//	イベント関数

long elEvent(void)
{
	elExitEvent();
}

///////////////////////////////////////////////////////////////////////////////
//	メイン画面

void MainScreen(void)
{
	int i, x, y;
	bool downFlag = false;			// 落下中ならtrue
	static int pnext;				// ネクストピース番号（０～６）
	static int pno;					// 現在のピース番号（０～６）
	static int pr;					// ピース回転（０～３）
	static int px, py;				// ピースのＸ、Ｙ座標
	static int keyLeft = FREE_KEY;	// 左キー
	static int keyRight = FREE_KEY;	// 右キー
	static int keyDown = FREE_KEY;	// 下キー
	static int keySpace = FREE_KEY;	// スペースキー
	static bool nextFlag = true;	// ネクストピースを出すフラグ
	static bool overFlag = false;	// ゲームオーバーフラグ
	static int score = 0;			// 得点
	static DWORD rpt = 0;			// キーリピート時間(ms)
	static DWORD downTime = 1000;	// 1ブロック落下する時間(ms)
	static DWORD downCount;			// 落下時間カウンタ(ms)

	if (elChangeScreen()) pnext = rand() % 7;
	elDraw::Clear();
	// ネクストピースが出る処理
	if (nextFlag) {
		px = 4; py = 0; pr = 0;
		pno = pnext;
		pnext = rand() % 7;
		nextFlag = false;
		downCount = timeGetTime();
		if (downTime > 100) downTime -= 10;
		else downTime--;
		if (downTime < 10) downTime = 10;
		// 出た瞬間にブロックにぶつかったらゲームオーバー
		for (i = 0; i < 4; i++) {
			if (field[py + piece[pno][pr][i].y][px + piece[pno][pr][i].x]) overFlag = true;
		}
	}
	// 移動
	int kx, ky, kr;		// 仮のＸ、Ｙ座標、回転
	kx = px; ky = py; kr = pr;
	elSystem::GetKey(VK_LEFT, &keyLeft);
	elSystem::GetKey(VK_RIGHT, &keyRight);
	elSystem::GetKey(VK_DOWN, &keyDown);
	elSystem::GetKey(VK_SPACE, &keySpace);
	DWORD nowTime = timeGetTime();
	if (keySpace == PUSH_KEY) {
		if (++kr > 3) kr = 0;
	} else if (keyDown == PUSH_KEY || keyDown == HOLD_KEY && nowTime > rpt) {
		ky++; downFlag = true; rpt = nowTime + 10;
	} else if (keyLeft == PUSH_KEY) {
		kx--; rpt = nowTime + 180;
	} else if (keyLeft == HOLD_KEY && nowTime > rpt) {
		kx--; rpt = nowTime + downTime / 10;
	} else if (keyRight == PUSH_KEY) {
		kx++; rpt = nowTime + 180;
	} else if (keyRight == HOLD_KEY && nowTime > rpt) {
		kx++; rpt = nowTime + downTime / 10;
	} else if (nowTime - downCount > downTime) {
		ky++; downFlag = true; downCount = nowTime;
	}
	// 当たり判定
	for (i = 0; i < 4; i++) {
		if (field[ky + piece[pno][kr][i].y][kx + piece[pno][kr][i].x]) break;
	}
	if (i >= 4) {
		px = kx; py = ky; pr = kr;
	} else if (downFlag) {
		// ピースを固める処理
		for (i = 0; i < 4; i++) {
			field[py + piece[pno][pr][i].y][px + piece[pno][pr][i].x] = pno + 1;
		}
		nextFlag = true;
		// ブロックを消す処理
		int sc = 0;
		for (y = 19; y >= 0; y--) {
			for (x = 1; x < 11; x++) if (field[y][x] == 0) break;
			if (x == 11) {
				for (int y2 = y - 1; y2 >= 0; y2--) {
					for (int x2 = 1; x2 < 11; x2++) field[y2 + 1][x2] = field[y2][x2];
				}
				y++;
				sc = sc ? sc * 4 : 10;
			}
		}
		score += sc;
		Sleep(400);
	}
	// 画面表示
	for (y = 0; y < 21; y++) {
		for (x = 0; x < 12; x++) {
			if (field[y][x]) {
				elDraw::Layer(x * 16, y * 16 + 80, block,
					(field[y][x] - 1) * 16, 0, field[y][x] * 16, 16);
			}
		}
	}
	for (i = 0; i < 4; i++) {
		// 現在のピース表示
		elDraw::Layer((px + piece[pno][pr][i].x) * 16,
			(py + piece[pno][pr][i].y) * 16 + 80,
			block, pno * 16, 0, pno * 16 + 16, 16);
		// ネクストピース表示
		elDraw::Layer(piece[pnext][0][i].x * 16 + 64,
			piece[pnext][0][i].y * 16,
			block, pnext * 16, 0, pnext * 16 + 16, 16);
	}
	// スコア表示
	SHOW2(0, 0, "SCORE : %d", score);
	elDraw::Refresh();
	// ゲームオーバー処理
	if (overFlag) {
		elSystem::Message("ゲームオーバー");
		elDraw::Exit();
	}
}
