#ifndef ENEMYPLANE_H_
#define ENEMYPLANE_H_


#include"Plane.h"

const int ENEMY_HP = 50;
const int ENEMY_ARMOR = 50;
const int ENEMY_SPEED = 5;
const int ENEMY_SIZE = 91;


class EnemyPlane:public Plane
{

private:

	static const int HP=ENEMY_HP;		//直接在这里赋值好像不可以？？
	static const int ARMOR=ENEMY_ARMOR;
	static const int SPEED=ENEMY_SPEED;
	static const int SIZE=ENEMY_SIZE;


public:

	EnemyPlane(int tp, IMAGE*img,double a = 0, int x = 0, int y = 0) :
		Plane(HP, ARMOR, SPEED, a,tp,img,x, y)
	{
		//m_img = img;
	}

	virtual void move();
	virtual int getSize()const { return SIZE; }
};





#endif