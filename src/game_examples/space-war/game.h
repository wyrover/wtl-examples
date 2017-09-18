#ifndef GAME_H_
#define GAME_H_

#include"Player.h"
#include"playerPlane.h"
#include"enemyPlane.h"
#include"weapon_gun.h"
#include"weapon_missle.h"
#include<time.h>
#include"costant.h"

/*负责控制游戏的运行*/
class Game
{
private:

	Player* m_player;
	PlayerPlane*m_fighter;		//player飞机
	int m_maxEnemyPlane;		//最大敌机数量
	Arr<Plane>m_enemy;			//敌机
	unsigned int m_timer;
public:
	Game()
	{
		m_timer = 0;
	}
	void addPlayer(Player*p)
	{
		m_player = p;
		m_fighter = new PlayerPlane(m_player->m_type,&Fighter,0,START_X, START_Y);
		m_maxEnemyPlane = (m_player->m_dificulty + 2) * 5;
	}
	int regEnemy(int tp, int x, int y)
	{
		EnemyPlane*t = new EnemyPlane(tp, &Ufo1,0,x, y);
		return m_enemy.insert(t);
	}
	bool isover()const
	{
		return m_player->m_left == 0;
	}
	
	/*游戏重新开始*/
	void restart();

	/*游戏结束处理*/
	void gameover();

	/*游戏开始*/
	void play();

	/*绘图函数*/
	void Show();

	/*计算各个飞机的伤害*/
	void Hit();
	
	/*读取用户输入 调整飞机状态*/
	void Control();

	/*改变下一时刻各个元素的状态*/
	void React();

	~Game()
	{
		delete m_fighter;
	}
};




#endif
