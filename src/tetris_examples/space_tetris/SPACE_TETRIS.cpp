#include<windows.h>
#include<time.h>
#include <stdlib.h>
#include <MMSystem.h>

// winmm.lib をリンクする
#pragma comment(lib,"winmm")

// エラ�`
#define ERR -1

// ピ�`スの罪と�kのマス方
#define PIECE_WIDTH		4
#define PIECE_HEIGHT	4

/* フィ�`ルドの罪と�kのマス方 */
#define FIELD_WIDTH		14
#define FIELD_HEIGHT	24

// マスのピクセル方
#define CELL_WIDTH		20
#define CELL_HEIGHT		20

/* MovePiece �v方の哈方 */
#define PIECE_LEFT		2
#define PIECE_RIGHT		4
#define PIECE_DOWN		8

BYTE field[FIELD_WIDTH][FIELD_HEIGHT]={0};		/* ゲ�`ムフィ�`ルド */
DWORD fColor[FIELD_WIDTH][FIELD_HEIGHT]={0};	// ゲ�`ムフィ�`ルドの弼

BYTE piece[PIECE_WIDTH][PIECE_HEIGHT]={0};		/* �F壓卞�嗽个離屮蹈奪� */
DWORD pColor[PIECE_WIDTH][PIECE_HEIGHT]={0};	// �F壓卞�嗽个離屮蹈奪�の弼
POINT location={0,0};							/* �F壓卞�嗽个離屮蹈奪�の了崔 */

BYTE next[PIECE_WIDTH][PIECE_HEIGHT]={0};		// 肝のブロック
DWORD nColor[PIECE_WIDTH][PIECE_HEIGHT]={0};	// 肝のブロックの弼

DWORD score=0;			// �@誼泣方
DWORD playTime=0;		// プレイ�r�g
BOOL GameOver=FALSE;	// TRUE となるのはゲ�`ムオ�`バ�`からリプレイするまで

#define MUTEX_NAME	"MutexObject of SPACE TETRIS"	// ミュ�`テックスオブジェクトの兆念

#define WM_MUTEX	WM_APP		// メインスレッドにミュ�`テックスの侭嗤�愴ゝ辰鰔�箔するメッセ�`ジ

/* piece[][] 坪のブロックの恷貧何の了崔を卦す */
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

/* piece[][]　坪のブロックの恷和何の了崔を卦す */
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

/* piece[][]　坪のブロックの恣�箸領志辰魴気� */
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

/* piece[][]　坪のブロックの嘔�箸領志辰魴気� */
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

/* ブロックの卞�單亢� */
// ��り�｣�TURE(卞�咾靴�) or FALSE(卞�啣賛�)
BOOL MovePiece(int move)	// move�災��咾靴燭し熟�
{
	int x,y,left,right,bottom;
	switch(move){
		case PIECE_LEFT:
			left=GetPieceLeft();

			if((location.x)+left <= 0) return FALSE;

			for(y=0;y<PIECE_HEIGHT;y++){		// ◎(location.x)+x-1>=0 , (location.y)+y>=0
				for(x=0;x<PIECE_WIDTH;x++){		// は耶忖の嗤�塵圓鰌{べている
					if(piece[x][y] && (location.x)+x-1>=0 && (location.y)+y>=0
						&& field[(location.x)+x-1][(location.y)+y]){	// 匯つ恣にブロックがある
                            return FALSE;
					}
				}
			}
			location.x--;
			return TRUE;
		case PIECE_RIGHT:
            right=GetPieceRight();

			if((location.x)+right >= FIELD_WIDTH-1) return FALSE;

			for(y=0;y<PIECE_HEIGHT;y++){		// ◎(location.x)+x+1<FIELD_WIDTH , (location.y)+y>=0
				for(x=0;x<PIECE_WIDTH;x++){		// は耶忖の嗤�塵圓鰌{べている
					if(piece[x][y] && (location.x)+x+1<FIELD_WIDTH && (location.y)+y>=0
						&& field[(location.x)+x+1][(location.y)+y]){	// 匯つ嘔にブロックがある
                            return FALSE;
					}
				}
			}
			location.x++;
			return TRUE;
		case PIECE_DOWN:
            bottom=GetPieceBottom();

			if((location.y)+bottom >= FIELD_HEIGHT-1) return FALSE;

			for(y=0;y<PIECE_HEIGHT;y++){		// ◎(location.y)+y+1>=0 , (location.y)+y+1<FIELD_HEIGHT
				for(x=0;x<PIECE_WIDTH;x++){		// は耶忖の嗤�塵圓鰌{べている
					if(piece[x][y] && (location.y)+y+1>=0 && (location.y)+y+1<FIELD_HEIGHT
						&& field[(location.x)+x][(location.y)+y+1]){	// 匯つ和にブロックがある
                            return FALSE;
					}
				}
			}
			location.y++;
			return TRUE;
	}
	return FALSE;
}

/* ブロックを指��させる */
// ��り�｣�TURE(指��した) or FALSE(指��音辛)
BOOL TurnPiece(void)
{
	int x,y,offsetX,offsetY;
	BYTE pTurn[PIECE_WIDTH][PIECE_HEIGHT];
	DWORD pcTurn[PIECE_WIDTH][PIECE_HEIGHT];

	/* 指��したブロックを伏撹する */
	for(y=0;y<PIECE_HEIGHT;y++){
		for(x=0;x<PIECE_WIDTH;x++){
			pTurn[(PIECE_HEIGHT-1)-y][x]=piece[x][y];
			pcTurn[(PIECE_HEIGHT-1)-y][x]=pColor[x][y];
		}
	}
	/* 指��辛嬬かどうかを�{べる */
	for(y=0;y<PIECE_HEIGHT;y++){
		for(x=0;x<PIECE_WIDTH;x++){
			if(pTurn[x][y]){
				offsetX=(location.x)+x;
				offsetY=(location.y)+y;
				if(offsetX<0 || offsetX>=FIELD_WIDTH
					|| offsetY>=FIELD_HEIGHT	// ◎offsetY>=0 は耶忖の嗤�塵圓鰌{べている
					|| (offsetY>=0 && field[offsetX][offsetY])){	//屡にブロックがある
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

/* 光佩を�{べ、佩が托まっている��栽は佩を��茅する */
// ��り�｣栽�茅した佩方
int DeleteLine(void)
{
	int x,y,delCount=0;
	for(y=FIELD_HEIGHT-1;y>=0;y--){
		int lineCount=0;
		for(x=0;x<FIELD_WIDTH;x++){
			lineCount+=field[x][y];
		}

		if(lineCount==0) break;		/* これより貧にブロックはない */
		if(lineCount!=FIELD_WIDTH) continue;

		/* 匯佩��茅する */
		delCount++;
		for(x=0;x<FIELD_WIDTH;x++){
			field[x][y]=0;
		}
	}
	return delCount;
}

// ��茅した佩を��める
void ShiftLine(int delCount)	// delCount�栽�茅した佩方
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

		// 匯佩��める
		delCount--;
		for(int iy=y;iy>=0;iy--){
			for(x=0;x<FIELD_WIDTH;x++){
				if(iy-1>=0){
					field[x][iy]=field[x][iy-1];
					fColor[x][iy]=fColor[x][iy-1];
				}else{
					field[x][0]=0;		/* 0 佩より貧はないので 0 で托める */
					fColor[x][0]=0;
				}
			}
		}
	}
}

// 肝のブロックをあらかじめ恬っておく
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

/* 肝のブロックへ */
void NextPiece(BOOL first)		// first�坤鴬`ム�_兵から恷兜の柵び竃しか倦か
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

/* ブロックを了崔秤�鵑�惄辰謄侫��`ルドにコピ�`する */
void PieceToField(void)
{
	for(int y=0;y<PIECE_HEIGHT;y++){
		for(int x=0;x<PIECE_WIDTH;x++){		// ◎(location.y)+y>=0 は耶忖の嗤�塵圓鰌{べている
			if(piece[x][y] && (location.y)+y>=0){
				field[(location.x)+x][(location.y)+y]=piece[x][y];
				fColor[(location.x)+x][(location.y)+y]=pColor[x][y];
			}
		}
	}
}

// �嘛�崙囮スレッド
DWORD WINAPI ThreadProc(LPVOID lpParameter)		// lpParameter�坤Ε�ンドウのハンドル
{
	HWND hWnd=(HWND)lpParameter;
	HANDLE hMutex=OpenMutex(MUTEX_ALL_ACCESS,FALSE,MUTEX_NAME);
	DWORD beforeTime=timeGetTime();
	DWORD sleep=1000;
	DWORD minute=0;
	DWORD progress,signal=1;
	int x,y,line;

	while(1){								// ◎メインスレッドからの初秘がない�泙�
		progress=timeGetTime()-beforeTime;	// タイムアウトによって棋�Cを盾茅する
		if(progress<sleep) signal=WaitForSingleObject(hMutex,sleep-progress);
		progress=timeGetTime()-beforeTime;	// ○メインスレッドからの初秘により
		playTime+=progress;					// タイムアウトを棋つことなく棋�Cを盾茅した辛嬬來を深�]
		minute+=progress;
		if(minute>=60*1000 && sleep>100){
			sleep-=100;		// 匯蛍ごとに棋�C�r�gを�pらしてゆく
			minute=0;
		}
		beforeTime=timeGetTime();

		if(!MovePiece(PIECE_DOWN)){		// �F壓卞�嗽个離屮蹈奪�が和粁に�_したら◎
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
			if(field[6][0] || field[7][0]){		/* ゲ�`ム�K阻 */
				GameOver=TRUE;
				ReleaseMutex(hMutex);	// ミュ�`テックスの侭嗤�悗鮟盞�
				CloseHandle(hMutex);	// 畠てのハンドルを�]じない�泙螢潺紿`テックスは篤��されない
				MessageBox(hWnd,"このメッセ�`ジボックスを�]じた瘁に\n"
					"    Enterキ�`を兀せば´´仟しいゲ�`ムが兵まります\n"
					"    〜ボタンを兀せば´´�K阻します","GAME OVER",MB_OK);
				return 0;		// ゲ�`ム�K阻でスレッドは篤��する
			}
			NextPiece(FALSE);
		}
		InvalidateRect(hWnd,NULL,FALSE);

		if(signal==WAIT_OBJECT_0){				// メインスレッドからの初秘により棋�Cを盾茅した
			ReleaseMutex(hMutex);				// ミュ�`テックスの侭嗤�悗鮟盞�
			SendMessage(hWnd,WM_MUTEX,0,0);		// メインスレッドにミュ�`テックスの侭嗤�愴ゝ辰鰔�箔
		}
	}
	return 0;
}

// 宙鮫する
void Paint(HDC hdc)		// hdc�坤妊丱ぅ好灰鵐謄�ストのハンドル
{
	int x,y,ptx,pty;
	HBRUSH hBrush,hOldBrush;

	SelectObject(hdc,GetStockObject(NULL_PEN));
	for(y=0;y<FIELD_HEIGHT;y++){		// ゲ�`ムフィ�`ルドのブロック
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
	for(y=0;y<PIECE_HEIGHT;y++){			// �F壓卞�嗽个離屮蹈奪�
		if((location.y)+y < 0) continue;	// ゲ�`ムフィ�`ルドの��より貧は宙かない
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
	for(y=0;y<PIECE_HEIGHT;y++){		// 肝のブロック
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
	Rectangle(hdc,CELL_WIDTH,CELL_HEIGHT,					// ゲ�`ムフィ�`ルドの��
		(FIELD_WIDTH+1)*CELL_WIDTH,(FIELD_HEIGHT+1)*CELL_HEIGHT);
	Rectangle(hdc,(FIELD_WIDTH+2)*CELL_WIDTH,CELL_HEIGHT,	// 肝のブロックの��
		(FIELD_WIDTH+2+PIECE_WIDTH)*CELL_WIDTH,(PIECE_HEIGHT+1)*CELL_HEIGHT);

	char buf[32];
	SetTextColor(hdc,RGB(255,255,255));
	SetBkMode(hdc,TRANSPARENT);
	// �@誼泣方
	wsprintf(buf,"SCORE");
	TextOut(hdc,(FIELD_WIDTH+2)*CELL_WIDTH,(PIECE_HEIGHT+2)*CELL_HEIGHT,buf,(int)strlen(buf));
	wsprintf(buf,"%d",score);
	TextOut(hdc,(FIELD_WIDTH+2)*CELL_WIDTH,(PIECE_HEIGHT+3)*CELL_HEIGHT,buf,(int)strlen(buf));
	// プレイ�r�g
	wsprintf(buf,"PLAY TIME");
	TextOut(hdc,(FIELD_WIDTH+2)*CELL_WIDTH,(PIECE_HEIGHT+5)*CELL_HEIGHT,buf,(int)strlen(buf));
	wsprintf(buf,"%02d:%02d:%03d",(playTime/1000)/60,(playTime/1000)%60,playTime%1000);
	TextOut(hdc,(FIELD_WIDTH+2)*CELL_WIDTH,(PIECE_HEIGHT+6)*CELL_HEIGHT,buf,(int)strlen(buf));
}

// 壅兜豚晒する
// ��り�｣歳造靴ぅ好譽奪匹離魯鵐疋�
HANDLE ReInitialize(HWND hWnd)		// hWnd�坤Ε�ンドウのハンドル
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
	NextPiece(TRUE);	// が NextPiece() で兜豚晒される
	return CreateThread(NULL,0,ThreadProc,hWnd,0,&dwID);		// ゲ�`ム�K阻瘁にスレッドは篤��されている
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
	static HANDLE hThread;		// �嘛�崙囮スレッドのハンドル
	static HANDLE hMutex;		// ミュ�`テックスオブジェクトのハンドル

	switch(uMsg) {
		case WM_CREATE:
			// 嘘尚鮫�颪鬟踪`ドする
			hBitmap=(HBITMAP)LoadImage((HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),
				"andromeda.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			if(hBitmap==NULL){
				MessageBox(hWnd,"プログラムを�K阻します","嘘尚鮫�颪�ありません",MB_OK);
				SendMessage(hWnd,WM_DESTROY,0,0);
				return 0;
			}
			GetObject(hBitmap,sizeof(BITMAP),&bitmap);
			hdc=GetDC(hWnd);
			hBackDC=CreateCompatibleDC(hdc);
			SelectObject(hBackDC,hBitmap);
			DeleteObject(hBitmap);

			// メモリデバイスコンテキストを恬る
			hBitmap=CreateCompatibleBitmap(hdc,bitmap.bmWidth,bitmap.bmHeight);
			hMemDC=CreateCompatibleDC(hdc);
			ReleaseDC(hWnd,hdc);
			SelectObject(hMemDC,hBitmap);
			DeleteObject(hBitmap);

			srand((unsigned)time(NULL));
			hMutex=CreateMutex(NULL,TRUE,MUTEX_NAME);	//恷兜の侭嗤宀はメインスレッド

			NextPiece(TRUE);
			hThread=CreateThread(NULL,0,ThreadProc,hWnd,0,&dwID);	// スレッドを恬る
			return 0;
		case WM_DESTROY:
			DeleteDC(hBackDC);
			DeleteDC(hMemDC);
			CloseHandle(hThread);
			CloseHandle(hMutex);
			PostQuitMessage(0);
			return 0;
		case WM_MUTEX:
			WaitForSingleObject(hMutex,INFINITE);	// ミュ�`テックスの侭嗤�悗鯣ゝ辰垢�
			return 0;								// (�嘛�崙囮スレッドを棋�Cさせる)
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
					break;	// ●�F壓卞�嗽个離屮蹈奪�を耕協させる�蕕��嘛�崙囮スレッドの棋�C盾茅
				case VK_SPACE:
					bl=TurnPiece();
					break;
				case VK_ESCAPE:		// 匯�r唯峭
					SuspendThread(hThread);
					beforeTime=timeGetTime();
					MessageBox(hWnd,"ゲ�`ムを壅�_しますか��","匯�r唯峭嶄",MB_OK);
					ResumeThread(hThread);
					playTime-=(timeGetTime()-beforeTime);
					break;
				case VK_RETURN:		// ゲ�`ムオ�`バ�`していれば仟しいゲ�`ムを兵める
					if(GameOver){
						WaitForSingleObject(hMutex,INFINITE);	// 仟しく恬る�嘛�崙囮スレッドを棋�Cさせる
						CloseHandle(hThread);					// ハンドルを�]じてもスレッドは�K阻しない
						hThread=ReInitialize(hWnd);				// 壅兜豚晒(�嘛�崙囮スレッドも仟しく恬る)
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

	// 峺協したクライアント�I囃を�_隠するために駅勣なウィンドウ恙�砲鰉�麻する
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