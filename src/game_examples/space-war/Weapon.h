#ifndef WEAPON_H_
#define WEAPON_H_

#include"Bullet.h"
#include<stdlib.h>
#include<iostream>
#include"Arr.h"

#include<graphics.h>

enum WEAPON_TYPE {TP_GUN,TP_MISSILE};

void putpicture(int x, int y, IMAGE* img);


class Weapon
{
protected:

	BULLET_TYPE m_type;
	Arr<Bullet>m_bullet;

	IMAGE*m_imgbullet;

	static const int AMMO = 100;
	int m_timer;

public:

	Weapon(BULLET_TYPE tp, IMAGE*img) :m_bullet(AMMO), m_type(tp), m_imgbullet(img), m_timer(0) {};
	virtual ~Weapon() {};


	int reload(const Location& loc)
	{
		Bullet*tem;
		switch(m_type)
		{
		case TP_M1:
			tem = new B1(loc.m_px, loc.m_py);		break;
		case TP_B1:
			tem = new M1(loc.m_px, loc.m_py);	break;
		default:
			std::cout << "wrong bullet type" << std::endl;		exit(-1);
		}
		return m_bullet.insert(tem);
	}

	int getFireRate()const
	{
		return Bullet::getRate(m_type);
	}

	void restart()
	{
		m_bullet.restart();
	}


	int Hit(const Location& loc,const int s)
	{
		int r = 0;
		for (int i = 0;i <m_bullet.getSize();i++)
			if (m_bullet[i])
			{
				int t = m_bullet[i]->Hit(loc,m_type,s);
				r += t;
				if (t > 0)
					m_bullet.setFlag(i);
			}
		return r;
	}


	virtual void fire(const Location&,double angle) = 0;


	void checkAmmo()
	{
		for (int i = 0;i <m_bullet.getSize();i++)
			if (m_bullet[i])
			{
				int x = m_bullet[i]->getPosX(), y = m_bullet[i]->getPoxY();
				if (x<0 || x>BOUND_X || y<0 || y>BOUND_Y)
					m_bullet.setFlag(i);
				else
					m_bullet[i]->BulletFly();
			}
		m_bullet.removeAll();
	}


	void showimage()
	{
		int i;
		for (i = 0;i <m_bullet.getSize();i++)
		{
			if (m_bullet[i])
				putpicture(m_bullet[i]->getPosX(), m_bullet[i]->getPoxY(), m_imgbullet);
		}
	}
};




#endif