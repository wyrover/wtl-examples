#ifndef PLANE_H_
#define PLANE_H_


#include"weapon_gun.h"
#include"weapon_missle.h"
#include"Location.h"




struct PLANE_TYPE
{
	WEAPON_TYPE m_wp;
	BULLET_TYPE m_bullet;
};
const PLANE_TYPE PlaneData[4] =
{
	{ TP_GUN,TP_B1 },
	{ TP_GUN,TP_M1 },
	{ TP_MISSILE,TP_B1 },
	{ TP_MISSILE,TP_M1 }
};

extern IMAGE GraphBuffer, Background, Fighter, Ufo1, Ufo2, Ufo3, gBullet;
//void putpicture(int x, int y, IMAGE img);

class Plane
{

protected:

	int m_hp;
	int m_armor;
	Speed m_s;
	Weapon*m_wp;
	Location m_loc;

	IMAGE*m_img;

public:

	Plane(int h, int ar, double s, double a, int tp,IMAGE*img,int x = 0,int y = 0) :
		m_hp(h),
		m_armor(ar),
		m_s(s, a),
		m_loc(x, y),
		m_img(img)
	{
		assert(tp >= 0 && tp <= 3);
		WEAPON_TYPE w = PlaneData[tp].m_wp;
		switch (w)
		{
		case TP_GUN:		m_wp = new Weapon_gun(PlaneData[tp].m_bullet,&gBullet);		break;
		case TP_MISSILE:		m_wp = new Weapon_missle(PlaneData[tp].m_bullet,&gBullet);		break;
		}
	}
	
	/*调整飞机的位置*/
	void flyto()
	{
		int x = m_loc.m_px, y = m_loc.m_py;
		x = m_s.getNextX(x);
		y = m_s.getNextY(y);
		m_loc.setLocation(x, y);
	}


	/*发射弹药*/
	void fire(double angle=-1)const
	{
		m_wp->fire(m_loc,angle);
	}

	/*运动方式*/
	virtual void move() = 0;

	/*计算造成的伤害*/
	int Hit(const Plane*p)const
	{
		return m_wp->Hit(p->m_loc, p->getSize());
	}

	void getHit(int hurt)
	{
		m_hp -= hurt;
	}

	bool idDesd()
	{
		return m_hp <= 0;
	}

	void showImage()
	{
		putpicture(m_loc.getLocX(), m_loc.getLocY(), m_img);
		m_wp->showimage();
	}


	/*改变弹药状态*/
	void checkAmmo()
	{
		m_wp->checkAmmo();
	}

	int getPosX()const { return m_loc.getLocX(); }
	int getPosY()const { return m_loc.getLocY(); }

	virtual int getSize()const= 0;

	virtual ~Plane()
	{
		delete m_wp;
	}
};
#endif