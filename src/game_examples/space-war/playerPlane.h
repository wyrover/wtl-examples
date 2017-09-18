#ifndef PLAYERPLANE_H_
#define PLAYERPLANE_H_



#include"Plane.h"

const int PLAYER_HP = 100;
const int PLAYER_ARMOR = 100;
const int PLAYER_SPEED = 20;
const int PLAYER_SIZE = 100;

class PlayerPlane: public Plane
{
private:
	static const int HP=PLAYER_HP;
	static const int ARMOR=PLAYER_ARMOR;
	static const int SPEED=PLAYER_SPEED;
	static const int SIZE=PLAYER_SIZE;

public:
	PlayerPlane(int tp,IMAGE*img,double a = 0,int x = 0, int y = 0) :
		Plane(HP, ARMOR, SPEED, a, tp,img,x,y)
	{
		//m_img = img;
	}

	/*设置飞机为初始状态 重新开始游戏*/
	void setInit()
	{
		m_hp = HP;
		m_armor = ARMOR;
		m_loc.setLocation(START_X, START_Y);
		m_wp->restart();
	}
	void setSpeed(char key)
	{
		switch (key)
		{
		case 'w':		m_s.setSpeed(0, -SPEED);		break;
		case 'a':		m_s.setSpeed(-SPEED, 0);		break;
		case 's':		m_s.setSpeed(0, SPEED);			break;
		case 'd':		m_s.setSpeed(SPEED, 0);			break;
		default:		break;
		}
	}
	void move()
	{

	}
	virtual int getSize()const
	{
		return SIZE;
	}
};




#endif