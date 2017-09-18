#ifndef WEAPON_MISSLE_H
#define WEAPON_MISSLE_H


#include"Weapon.h"

class Weapon_missle:public Weapon
{

public:
	Weapon_missle(BULLET_TYPE tp,IMAGE*img) :Weapon(tp,img)
	{
	}
	virtual void fire(const Location&,double angle)
	{

	}
	~Weapon_missle()
	{
	}

};




#endif