#include"Bullet.h"
#include<iostream>

int Bullet::getRate(BULLET_TYPE tp)
{
	switch (tp)
	{
	case TP_B1:		return B1::getRate();
	case TP_M1:		return M1::getRate();
	default:	std::cout << "bullet type error" << std::endl;		exit(-1);
	}
}

int Bullet::getSize(BULLET_TYPE tp)
{
	switch (tp)
	{
	case TP_B1:		return B1::getSize();
	case TP_M1:		return M1::getSize();
	default:	std::cout << "bullet type error" << std::endl;		exit(-1);
	}
}

int Bullet::getDamage(BULLET_TYPE tp)
{
	switch (tp)
	{
	case TP_B1:		return B1::getDamage();
	case TP_M1:		return M1::getDamage();
	default:	std::cout << "bullet type error" << std::endl;		exit(-1);
	}
}
int Bullet::getSpeed(BULLET_TYPE tp)
{
	switch (tp)
	{
	case TP_B1:		return B1::getSpeed();
	case TP_M1:		return M1::getSpeed();
	default:	std::cout << "bullet type error" << std::endl;		exit(-1);
	}
}