#ifndef BULLET_H_
#define BULLET_H_

#include"Speed.h"
#include"Location.h"


//伤害 速度与射速
const int DAMAGE_B1 = 5,
DAMAGE_M1 = 20,
SPEED_B1 = 5,
SPEED_M1 = 50,
RATE_B1 = 5,
RATE_M1 = 1000;


//子弹的大小
const int BULLET_SIZE = 6;

enum BULLET_TYPE { TP_B1, TP_M1 };


class Bullet
{

protected:

	Location m_loc;
	Speed m_s;
	/*发射一颗子弹 根据a设置子弹的下一位置*/

public:
	
	Bullet(int x = 0, int y = 0) :
		m_loc(x, y) {};

	/*向weapon接口*/
	void BulletFly()
	{
		m_loc = m_s.getNextLoc(m_loc);
	}
	void setSpeed(double a,BULLET_TYPE tp)
	{
		m_s.SpeedReset(getSpeed(tp), a);
	}

	/*子弹是否击中*/
	int Hit(const Location& loc,BULLET_TYPE tp,const int size)const
	{
		return m_loc.cal_distance(loc) <= size + getSize(tp) ? getDamage(tp) : 0;
	}

	/*设置坐标*/
	void setLoction(const Location& loc)
	{
		m_loc = loc;
	}

	static int getRate(BULLET_TYPE tp);
	static int getSize(BULLET_TYPE tp);
	static int getDamage(BULLET_TYPE tp);
	static int getSpeed(BULLET_TYPE tp);

	int getPosX() { return m_loc.getLocX(); }
	int getPoxY() { return m_loc.getLocY(); }
	
};



class B1:public Bullet
{

private:

	static const int DAMAGE = DAMAGE_B1;
	static const int SPEED = SPEED_B1;
	static const int RATE = RATE_B1;
	static const int SIZE = BULLET_SIZE;

public:

	B1(int x=0, int y=0,double a = 0):
		Bullet(x,y)
		{
			m_s.SpeedReset(SPEED,a);
		}

	/*virtual void shoot(double a)
	{
		m_s.SpeedReset(SPEED, a);
		m_loc = m_s.getNextLoc(m_loc);
	}*/

	/*const限定符仅使用于非静态成员函数 表示不修改函数调用的对象的成员变量*/
	static int getDamage(){return DAMAGE;}
	static int getRate(){return RATE;}
	static int getSize(){return SIZE;}
	static int getSpeed() { return SPEED; };
};



class M1 :public Bullet
{

private:

	static const int DAMAGE = DAMAGE_M1;
	static const int SPEED = SPEED_M1;
	static const int RATE = RATE_M1;
	static const int SIZE = BULLET_SIZE;
	
public:

	M1(int x = 0, int y = 0, double a = 0) :
		Bullet( x, y)
		{
			m_s.SpeedReset(SPEED,a);
		}

	/*virtual void shoot(double a)
	{
		m_s.SpeedReset(SPEED, a);
		m_loc = m_s.getNextLoc(m_loc);
	}*/
	static int getDamage(){return DAMAGE;}
	static int getRate(){return RATE;}
	static int getSize(){return SIZE;}
	static int getSpeed() { return SPEED; }
};
#endif