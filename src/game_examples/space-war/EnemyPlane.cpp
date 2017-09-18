#include"enemyPlane.h"
#include<time.h>
#include<conio.h>




void EnemyPlane::move()
{
	srand((unsigned int)time(NULL));
	double a = 0;
	while (!(a > PI&&a < 2 * PI))
	{
		int t = rand() % 360;
		a = (t * 2 * PI) / 360;
	}
	m_s.SpeedReset(SPEED, a);
	flyto();
}