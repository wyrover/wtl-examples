#ifndef WEAPON_GUN_H
#define WEAPON_GUN_H


#include"Weapon.h"
#include<time.h>

class Weapon_gun :public Weapon
{
public:
	Weapon_gun(BULLET_TYPE tp,IMAGE*img) :Weapon(tp,img)
	{

	}

	/*子弹的运动轨迹*/
	virtual void fire(const Location& loc, double angle)
	{
		int rate = getFireRate();
		if (m_timer % (TIMER_SHOOT / rate) == 0)
		{
			int j = reload(loc);
			if (j != -1)
			{
				if (angle == -1)
					m_bullet[j]->setSpeed((rand() % 360 * 2 * PI) / 360, m_type);
				else
					m_bullet[j]->setSpeed(angle, m_type);
				m_bullet[j]->BulletFly();
			}
		}
		m_timer += GAP;
		if (m_timer > TIMER_SHOOT)
			m_timer = 0;
	}

	~Weapon_gun()
	{
	}
};




#endif