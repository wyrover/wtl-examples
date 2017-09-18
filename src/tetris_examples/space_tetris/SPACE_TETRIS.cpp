#include<windows.h>
#include<time.h>
#include <stdlib.h>
#include <MMSystem.h>

// winmm.lib をリンクする
#pragma comment(lib,"winmm")

// エラー
#define ERR -1

// ピースの横と縦のマス数
#define PIECE_WIDTH		4
#define PIECE_HEIGHT	4

/* フィールドの横と縦のマス数 */
#define FIELD_WIDTH		14
#define FIELD_HEIGHT	24

// マスのピクセル数
#define CELL_WIDTH		20
#define CELL_HEIGHT		20

/* MovePiece 関数の引数 */
#define PIECE_LEFT		2
#define PIECE_RIGHT		4
#define PIECE_DOWN		8

BYTE field[FIELD_WIDTH][FIELD_HEIGHT]={0};		/* ゲームフィールド */
DWORD fColor[FIELD_WIDTH][FIELD_HEIGHT]={0};	// ゲームフィールドの色

BYTE piece[PIECE_WIDTH][PIECE_HEIGHT]={0};		/* 現在移動中のブロック */
DWORD pColor[PIECE_WIDTH][PIECE_HEIGHT]={0};	// 現在移動中のブロックの色
POINT location={0,0};							/* 現在移動中のブロックの位置 */

BYTE next[PIECE_WIDTH][PIECE_HEIGHT]={0};		// 次のブロック
DWORD nColor[PIECE_WIDTH][PIECE_HEIGHT]={0};	// 次のブロックの色

DWORD score=0;			// 獲得点数
DWORD playTime=0;		// プレイ時間
BOOL GameOver=FALSE;	// TRUE となるのはゲームオーバーからリプレイするまで

#define MUTEX_NAME	"MutexObject of SPACE TETRIS"	// ミューテックスオブジェクトの名前

#define WM_MUTEX	WM_APP		// メインスレッドにミューテックスの所有権取得を要求するメッセージ

/* piece[][] 内のブロックの最上部の位置を返す */
int GetPieceTop(void)
{
	for(int y=0;y<PIECE_HEIGHT;y++){
		for(int x=0;x<PIECE_WIDTH;x++){
			if(piece[x][y]){
				return y;
			}
		}
	}
	return ERR;
}

/* piece[][]　内のブロックの最下部の位置を返す */
int GetPieceBottom(void)
{
	for(int y=PIECE_HEIGHT-1;y>=0;y--){
		for(int x=0;x<PIECE_WIDTH;x++){
			if(piece[x][y]){
				return y;
			}
		}
	}
	return ERR;
}

/* piece[][]　内のブロックの左側の位置を返す */
int GetPieceLeft(void)
{
	for(int x=0;x<PIECE_WIDTH;x++){
		for(int y=0;y<PIECE_HEIGHT;y++){
			if(piece[x][y]){
				return x;
			}
		}
	}
	return ERR;
}

/* piece[][]　内のブロックの右側の位置を返す */
int GetPieceRight(void)
{
	for(int x=PIECE_WIDTH-1;x>=0;x--){
		for(int y=0;y<PIECE_HEIGHT;y++){
			if(piece[x][y]){
				return x;
			}
		}
	}
	return ERR;
}

/* ブロックの移動判定 */
// 戻り値：TURE(移動した) or FALSE(移動不可)
BOOL MovePiece(int move)	// move：移動したい方向
{
	int x,y,left,right,bottom;
	switch(move){
		case PIECE_LEFT:
			left=GetPieceLeft();

			if((location.x)+left <= 0) return FALSE;

			for(y=0;y<PIECE_HEIGHT;y++){		// ↓(location.x)+x-1>=0 , (location.y)+y>=0
				for(x=0;x<PIECE_WIDTH;x++){		// は添字の有効性を調べている
					if(piece[x][y] && (location.x)+x-1>=0 && (location.y)+y>=0
						&& field[(location.x)+x-1][(location.y)+y]){	// 一つ左にブロックがある
                            return FALSE;
					}
				}
			}
			location.x--;
			return TRUE;
		case PIECE_RIGHT:
            right=GetPieceRight();

			if((location.x)+right >= FIELD_WIDTH-1) return FALSE;

			for(y=0;y<PIECE_HEIGHT;y++){		// ↓(location.x)+x+1<FIELD_WIDTH , (location.y)+y>=0
				for(x=0;x<PIECE_WIDTH;x++){		// は添字の有効性を調べている
					if(piece[x][y] && (location.x)+x+1<FIELD_WIDTH && (location.y)+y>=0
						&& field[(location.x)+x+1][(location.y)+y]){	// 一つ右にブロックがある
                            return FALSE;
					}
				}
			}
			location.x++;
			return TRUE;
		case PIECE_DOWN:
            bottom=GetPieceBottom();

			if((location.y)+bottom >= FIELD_HEIGHT-1) return FALSE;

			for(y=0;y<PIECE_HEIGHT;y++){		// ↓(location.y)+y+1>=0 , (location.y)+y+1<FIELD_HEIGHT
				for(x=0;x<PIECE_WIDTH;x++){		// は添字の有効性を調べている
					if(piece[x][y] && (location.y)+y+1>=0 && (location.y)+y+1<FIELD_HEIGHT
						&& field[(location.x)+x][(location.y)+y+1]){	// 一つ下にブロックがある
                            return FALSE;
					}
				}
			}
			location.y++;
			return TRUE;
	}
	return FALSE;
}

/* ブロックを回転させる */
// 戻り値：TURE(回転した) or FALSE(回転不可)
BOOL TurnPiece(void)
{
	int x,y,offsetX,offsetY;
	BYTE pTurn[PIECE_WIDTH][PIECE_HEIGHT];
	DWORD pcTurn[PIECE_WIDTH][PIECE_HEIGHT];

	/* 回転したブロックを生成する */
	for(y=0;y<PIECE_HEIGHT;y++){
		for(x=0;x<PIECE_WIDTH;x++){
			pTurn[(PIECE_HEIGHT-1)-y][x]=piece[x][y];
			pcTurn[(PIECE_HEIGHT-1)-y][x]=pColor[x][y];
		}
	}
	/* 回転可能かどうかを調べる */
	for(y=0;y<PIECE_HEIGHT;y++){
		for(x=0;x<PIECE_WIDTH;x++){
			if(pTurn[x][y]){
				offsetX=(location.x)+x;
				offsetY=(location.y)+y;
				if(offsetX<0 || offsetX>=FIELD_WIDTH
					|| offsetY>=FIELD_HEIGHT	// ↓offsetY>=0 は添字の有効性を調べている
					|| (offsetY>=0 && field[offsetX][offsetY])){	//既にブロックがある
                        return FALSE;
					}
			}
		}
	}
	for(y=0;y<PIECE_HEIGHT;y++){
		for(x=0;x<PIECE_WIDTH;x++){
			piece[x][y]=pTurn[x][y];
			pColor[x][y]=pcTurn[x][y];
		}
	}
	return TRUE;
}

/* 各行を調べ、行が埋まっている場合は行を削除する */
// 戻り値：削除した行数
int DeleteLine(void)
{
	int x,y,delCount=0;
	for(y=FIELD_HEIGHT-1;y>=0;y--){
		int lineCount=0;
		for(x=0;x<FIELD_WIDTH;x++){
			lineCount+=field[x][y];
		}

		if(lineCount==0) break;		/* これより上にブロックはない */
		if(lineCount!=FIELD_WIDTH) continue;

		/* 一行削除する */
		delCount++;
		for(x=0;x<FIELD_WIDTH;x++){
			field[x][y]=0;
		}
	}
	return delCount;
}

// 削除した行を詰める
void ShiftLine(int delCount)	// delCount：削除した行数
{
	int x,y;
	for(y=FIELD_HEIGHT-1;y>=0 && delCount>0; ){
		int lineCount=0;
		for(x=0;x<FIELD_WIDTH;x++){
			lineCount+=field[x][y];
		}

		if(lineCount!=0){
			y--;
			continue;
		}

		// 一行詰める
		delCount--;
		for(int iy=y;iy>=0;iy--){
			for(x=0;x<FIELD_WIDTH;x++){
				if(iy-1>=0){
					field[x][iy]=field[x][iy-1];
					fColor[x][iy]=fColor[x][iy-1];
				}else{
					field[x][0]=0;		/* 0 行より上はないので 0 で埋める */
					fColor[x][0]=0;
				}
			}
		}
	}
}

// 次のブロックをあらかじめ作っておく
void CreatePiece(void)
{
	for(int y=0;y<PIECE_HEIGHT;y++){
		for(int x=0;x<PIECE_WIDTH;x++){
			next[x][y]=0;
			nColor[x][y]=0;
		}
	}
	switch(rand()%7){
        case 0:
			next[1][1]=1; next[2][1]=1; next[1][2]=1; next[2][2]=1;
			nColor[1][1]=nColor[2][1]=nColor[1][2]=nColor[2][2]=0x000000ff;
			return;
		case 1:
			next[1][0]=1; next[1][1]=1; next[1][2]=1; next[1][3]=1;
			nColor[1][0]=nColor[1][1]=nColor[1][2]=nColor[1][3]=0x0000ff00;
			return;
		case 2:
			next[1][1]=1; next[1][2]=1; next[2][2]=1; next[1][3]=1;
			nColor[1][1]=nColor[1][2]=nColor[2][2]=nColor[1][3]=0x0000ffff;
			return;
		case 3:
			next[1][1]=1; next[2][1]=1; next[1][2]=1; next[1][3]=1;
			nColor[1][1]=nColor[2][1]=nColor[1][2]=nColor[1][3]=0x00ff0000;
			return;
		case 4:
			next[1][1]=1; next[2][1]=1; next[2][2]=1; next[2][3]=1;
			nColor[1][1]=nColor[2][1]=nColor[2][2]=nColor[2][3]=0x00ff00ff;
			return;
		case 5:
			next[2][1]=1; next[1][2]=1; next[2][2]=1; next[1][3]=1;
			nColor[2][1]=nColor[1][2]=nColor[2][2]=nColor[1][3]=0x00ffff00;
			return;
		case 6:
			next[1][1]=1; next[1][2]=1; next[2][2]=1; next[2][3]=1;
			nColor[1][1]=nColor[1][2]=nColor[2][2]=nColor[2][3]=0x00ffffff;
			return;
	}
}

/* 次のブロックへ */
void NextPiece(BOOL first)		// first：ゲーム開始から最初の呼び出しか否か
{
	if(first) CreatePiece();

	for(int y=0;y<PIECE_HEIGHT;y++){
		for(int x=0;x<PIECE_WIDTH;x++){
			piece[x][y]=next[x][y];
			pColor[x][y]=nColor[x][y];
		}
	}
	location.x=5;
	location.y=-3;

	CreatePiece();
}

/* ブロックを位置情報に従ってフィールドにコピーする */
void PieceToField(void)
{
	for(int y=0;y<PIECE_HEIGHT;y++){
		for(int x=0;x<PIECE_WIDTH;x++){		// ↓(location.y)+y>=0 は添字の有効性を調べている
			if(piece[x][y] && (location.y)+y>=0){
				field[(location.x)+x][(location.y)+y]=piece[x][y];
				fColor[(location.x)+x][(location.y)+y]=pColor[x][y];
			}
		}
	}
}

// 動作制御スレッド
DWORD WINAPI ThreadProc(LPVOID lpParameter)		// lpParameter：ウィンドウのハンドル
{
	HWND hWnd=(HWND)lpParameter;
	HANDLE hMutex=OpenMutex(MUTEX_ALL_ACCESS,FALSE,MUTEX_NAME);
	DWORD beforeTime=timeGetTime();
	DWORD sleep=1000;
	DWORD minute=0;
	DWORD progress,signal=1;
	int x,y,line;

	while(1){								// ↓メインスレッドからの介入がない限り
		progress=timeGetTime()-beforeTime;	// タイムアウトによって待機を解除する
		if(progress<sleep) signal=WaitForSingleObject(hMutex,sleep-progress);
		progress=timeGetTime()-beforeTime;	// ←メインスレッドからの介入により
		playTime+=progress;					// タイムアウトを待つことなく待機を解除した可能性を考慮
		minute+=progress;
		if(minute>=60*1000 && sleep>100){
			sleep-=100;		// 一分ごとに待機時間を減らしてゆく
			minute=0;
		}
		beforeTime=timeGetTime();

		if(!MovePiece(PIECE_DOWN)){		// 現在移動中のブロックが下段に達したら↓
			PieceToField();
			line=DeleteLine();
			if(line>0){
				for(y=0;y<PIECE_HEIGHT;y++){
					for(x=0;x<PIECE_WIDTH;x++){
						piece[x][y]=0;
					}
				}
				if(line==4) score+=1000;
				else score+=(line*100);
				InvalidateRect(hWnd,NULL,FALSE);
				Sleep(500);
				ShiftLine(line);
			}
			if(field[6][0] || field[7][0]){		/* ゲーム終了 */
				GameOver=TRUE;
				ReleaseMutex(hMutex);	// ミューテックスの所有権を解放
				CloseHandle(hMutex);	// 全てのハンドルを閉じない限りミューテックスは破棄されない
				MessageBox(hWnd,"このメッセージボックスを閉じた後に\n"
					"    Enterキーを押せば……新しいゲームが始まります\n"
					"    ×ボタンを押せば……終了します","GAME OVER",MB_OK);
				return 0;		// ゲーム終了でスレッドは破棄する
			}
			NextPiece(FALSE);
		}
		InvalidateRect(hWnd,NULL,FALSE);

		if(signal==WAIT_OBJECT_0){				// メインスレッドからの介入により待機を解除した
			ReleaseMutex(hMutex);				// ミューテックスの所有権を解放
			SendMessage(hWnd,WM_MUTEX,0,0);		// メインスレッドにミューテックスの所有権取得を要求
		}
	}
	return 0;
}

// 描画する
void Paint(HDC hdc)		// hdc：デバイスコンテキストのハンドル
{
	int x,y,ptx,pty;
	HBRUSH hBrush,hOldBrush;

	SelectObject(hdc,GetStockObject(NULL_PEN));
	for(y=0;y<FIELD_HEIGHT;y++){		// ゲームフィールドのブロック
		for(x=0;x<FIELD_WIDTH;x++){
			ptx=(x+1)*CELL_WIDTH;
			pty=(y+1)*CELL_HEIGHT;
			if(field[x][y]){
				hBrush=CreateSolidBrush(fColor[x][y]);
				hOldBrush=(HBRUSH)SelectObject(hdc,hBrush);
				Rectangle(hdc,ptx,pty,ptx+CELL_WIDTH,pty+CELL_HEIGHT);
				SelectObject(hdc,hOldBrush);
				DeleteObject(hBrush);
			}
		}
	}
	for(y=0;y<PIECE_HEIGHT;y++){			// 現在移動中のブロック
		if((location.y)+y < 0) continue;	// ゲームフィールドの枠より上は描かない
		for(x=0;x<PIECE_WIDTH;x++){
			ptx=((location.x)+x+1)*CELL_WIDTH;
			pty=((location.y)+y+1)*CELL_HEIGHT;
			if(piece[x][y]){
				hBrush=CreateSolidBrush(pColor[x][y]);
				hOldBrush=(HBRUSH)SelectObject(hdc,hBrush);
				Rectangle(hdc,ptx,pty,ptx+CELL_WIDTH,pty+CELL_HEIGHT);
				SelectObject(hdc,hOldBrush);
				DeleteObject(hBrush);
			}
		}
	}
	for(y=0;y<PIECE_HEIGHT;y++){		// 次のブロック
		for(x=0;x<PIECE_WIDTH;x++){
			ptx=(FIELD_WIDTH+2+x)*CELL_WIDTH;
			pty=(y+1)*CELL_HEIGHT;
			if(next[x][y]){
				hBrush=CreateSolidBrush(nColor[x][y]);
				hOldBrush=(HBRUSH)SelectObject(hdc,hBrush);
				Rectangle(hdc,ptx,pty,ptx+CELL_WIDTH,pty+CELL_HEIGHT);
				SelectObject(hdc,hOldBrush);
				DeleteObject(hBrush);
			}
		}
	}
	SelectObject(hdc,GetStockObject(WHITE_PEN));
	SelectObject(hdc,GetStockObject(NULL_BRUSH));
	Rectangle(hdc,CELL_WIDTH,CELL_HEIGHT,					// ゲームフィールドの枠
		(FIELD_WIDTH+1)*CELL_WIDTH,(FIELD_HEIGHT+1)*CELL_HEIGHT);
	Rectangle(hdc,(FIELD_WIDTH+2)*CELL_WIDTH,CELL_HEIGHT,	// 次のブロックの枠
		(FIELD_WIDTH+2+PIECE_WIDTH)*CELL_WIDTH,(PIECE_HEIGHT+1)*CELL_HEIGHT);

	char buf[32];
	SetTextColor(hdc,RGB(255,255,255));
	SetBkMode(hdc,TRANSPARENT);
	// 獲得点数
	wsprintf(buf,"SCORE");
	TextOut(hdc,(FIELD_WIDTH+2)*CELL_WIDTH,(PIECE_HEIGHT+2)*CELL_HEIGHT,buf,(int)strlen(buf));
	wsprintf(buf,"%d",score);
	TextOut(hdc,(FIELD_WIDTH+2)*CELL_WIDTH,(PIECE_HEIGHT+3)*CELL_HEIGHT,buf,(int)strlen(buf));
	// プレイ時間
	wsprintf(buf,"PLAY TIME");
	TextOut(hdc,(FIELD_WIDTH+2)*CELL_WIDTH,(PIECE_HEIGHT+5)*CELL_HEIGHT,buf,(int)strlen(buf));
	wsprintf(buf,"%02d:%02d:%03d",(playTime/1000)/60,(playTime/1000)%60,playTime%1000);
	TextOut(hdc,(FIELD_WIDTH+2)*CELL_WIDTH,(PIECE_HEIGHT+6)*CELL_HEIGHT,buf,(int)strlen(buf));
}

// 再初期化する
// 戻り値：新しいスレッドのハンドル
HANDLE ReInitialize(HWND hWnd)		// hWnd：ウィンドウのハンドル
{
	for(int y=0;y<FIELD_HEIGHT;y++){
		for(int x=0;x<FIELD_WIDTH;x++){
			field[x][y]=0;
			fColor[x][y]=0;
		}
	}
	score=0;
	playTime=0;
	GameOver=FALSE;

	DWORD dwID;			// piece[][] , pColor[][] , location , next[][] , nColor[][]
	NextPiece(TRUE);	// が NextPiece() で初期化される
	return CreateThread(NULL,0,ThreadProc,hWnd,0,&dwID);		// ゲーム終了後にスレッドは破棄されている
}

LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	BOOL bl;
	DWORD beforeTime,dwID;
	HBITMAP hBitmap;
	static BITMAP bitmap;
	static HDC hBackDC,hMemDC;
	static HANDLE hThread;		// 動作制御スレッドのハンドル
	static HANDLE hMutex;		// ミューテックスオブジェクトのハンドル

	switch(uMsg) {
		case WM_CREATE:
			// 背景画像をロードする
			hBitmap=(HBITMAP)LoadImage((HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),
				"andromeda.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			if(hBitmap==NULL){
				MessageBox(hWnd,"プログラムを終了します","背景画像がありません",MB_OK);
				SendMessage(hWnd,WM_DESTROY,0,0);
				return 0;
			}
			GetObject(hBitmap,sizeof(BITMAP),&bitmap);
			hdc=GetDC(hWnd);
			hBackDC=CreateCompatibleDC(hdc);
			SelectObject(hBackDC,hBitmap);
			DeleteObject(hBitmap);

			// メモリデバイスコンテキストを作る
			hBitmap=CreateCompatibleBitmap(hdc,bitmap.bmWidth,bitmap.bmHeight);
			hMemDC=CreateCompatibleDC(hdc);
			ReleaseDC(hWnd,hdc);
			SelectObject(hMemDC,hBitmap);
			DeleteObject(hBitmap);

			srand((unsigned)time(NULL));
			hMutex=CreateMutex(NULL,TRUE,MUTEX_NAME);	//最初の所有者はメインスレッド

			NextPiece(TRUE);
			hThread=CreateThread(NULL,0,ThreadProc,hWnd,0,&dwID);	// スレッドを作る
			return 0;
		case WM_DESTROY:
			DeleteDC(hBackDC);
			DeleteDC(hMemDC);
			CloseHandle(hThread);
			CloseHandle(hMutex);
			PostQuitMessage(0);
			return 0;
		case WM_MUTEX:
			WaitForSingleObject(hMutex,INFINITE);	// ミューテックスの所有権を取得する
			return 0;								// (動作制御スレッドを待機させる)
		case WM_PAINT:
			hdc=BeginPaint(hWnd,&ps);
			BitBlt(hMemDC,0,0,bitmap.bmWidth,bitmap.bmHeight,hBackDC,0,0,SRCCOPY);
			Paint(hMemDC);
			BitBlt(hdc,0,0,bitmap.bmWidth,bitmap.bmHeight,hMemDC,0,0,SRCCOPY);
			EndPaint(hWnd,&ps);
			return 0;
		case WM_KEYDOWN:
			bl=NULL;
			switch(wParam){
				case VK_LEFT:
                    bl=MovePiece(PIECE_LEFT);
					break;
				case VK_RIGHT:
                    bl=MovePiece(PIECE_RIGHT);
					break;
				case VK_DOWN:
                    bl=MovePiece(PIECE_DOWN);
					if(!bl) ReleaseMutex(hMutex);
					break;	// ↑現在移動中のブロックを固定させる為に動作制御スレッドの待機解除
				case VK_SPACE:
					bl=TurnPiece();
					break;
				case VK_ESCAPE:		// 一時停止
					SuspendThread(hThread);
					beforeTime=timeGetTime();
					MessageBox(hWnd,"ゲームを再開しますか？","一時停止中",MB_OK);
					ResumeThread(hThread);
					playTime-=(timeGetTime()-beforeTime);
					break;
				case VK_RETURN:		// ゲームオーバーしていれば新しいゲームを始める
					if(GameOver){
						WaitForSingleObject(hMutex,INFINITE);	// 新しく作る動作制御スレッドを待機させる
						CloseHandle(hThread);					// ハンドルを閉じてもスレッドは終了しない
						hThread=ReInitialize(hWnd);				// 再初期化(動作制御スレッドも新しく作る)
					}
					break;
			}
			if(bl) InvalidateRect(hWnd,NULL,FALSE);
			break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
	PSTR lpCmdLine,int nCmdShow)
{
	WNDCLASS wc;
	MSG msg;

	wc.style		 = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	 = WindowProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName	 = NULL;
	wc.lpszClassName = __FILE__;

	if(!RegisterClass(&wc)) return 0;

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算する
	RECT rc={0,0,(FIELD_WIDTH+7)*CELL_WIDTH,(FIELD_HEIGHT+2)*CELL_HEIGHT};
	AdjustWindowRect(&rc,WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,FALSE);

	HWND hWnd=CreateWindow(
		__FILE__,"SPACE TETRIS",
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX) | WS_VISIBLE,
		CW_USEDEFAULT,CW_USEDEFAULT,
		rc.right-rc.left,rc.bottom-rc.top, 
		NULL,NULL,hInstance,NULL);
	if(hWnd==NULL) return 0;

	BOOL bRet;
	while((bRet=GetMessage(&msg,NULL,0,0))!=0){
		if(bRet==-1) break;
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}