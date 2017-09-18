#include"game.h"
#include<graphics.h>


void putpicture(int x, int y, IMAGE*img);

void Game::gameover()
{
	std::cout << "game over" << std::endl;
}
void Game::restart()
{
	m_enemy.restart();
	m_fighter->setInit();
	m_player->m_left--;
}
void Game::play()
{
	while (!isover())
	{
		Show();
		Sleep(GAP);
		m_timer += GAP;
		Hit();
		if (m_fighter->idDesd())
		{
			restart();
			continue;
		}
		Control();
		React();
	}
	gameover();
}
void Game::Show()
{
	SetWorkingImage(&GraphBuffer);
	putpicture(0, 0, &Background);
	for (int i = 0;i < m_enemy.getSize();i++)
		if (m_enemy[i])
			m_enemy[i]->showImage();
	m_fighter->showImage();
	SetWorkingImage();
	putimage(0, 0, &GraphBuffer);
}
double getAngle(int x1, int y1, int x2, int y2)
{
	int x = x2 - x1, y = y2 - y1;
	double s = sqrt(x*x + y*y);
	if (s == 0)
		return 0;
	else
	{
		double t = asin(y / s);
		if (x <= 0 && y <= 0)
			return PI + t;
		else if (x <= 0 && y > 0)
			return PI + t;
		else if (x > 0 && y > 0)
			return 2 * PI - t;
		else
			return -t;
	}
}
void Game::Control()
{
	char key = '.';MOUSEMSG msg;
	if (_kbhit())
	{
		key = _getch();
		if (key == 'w' || key == 'a' || key == 's' || key == 'd')
		{
			m_fighter->setSpeed(key);
			m_fighter->flyto();
		}
	}
	while (MouseHit())
	{
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:	m_fighter->fire(
			getAngle(
				m_fighter->getPosX(),
				m_fighter->getPosY(),
				msg.x,
				msg.y
				)
			);		break;
		default:
			break;
		}
	}
}
void Game::React()
{
	
	for (int i = 0;i < m_enemy.getSize();i++)
		if (m_enemy[i] && (m_enemy[i]->idDesd()||m_enemy[i]->getPosX()>=BOUND_X||m_enemy[i]->getPosX()<0||m_enemy[i]->getPosY()>=BOUND_Y))
			m_enemy.setFlag(i);
	m_enemy.removeAll();


	m_fighter->checkAmmo();

	
	if (m_enemy.getNum() < m_maxEnemyPlane&&m_timer == TIMER_NEWPLANE)
	{
		regEnemy(0, BORN_X, BORN_Y);
		m_timer = 0;
	}
	for (int i = 0;i <m_enemy.getSize();i++)
		if (m_enemy[i])
		{
			m_enemy[i]->move();
			m_enemy[i]->checkAmmo();
			m_enemy[i]->fire();
		}
}

void Game::Hit()
{
	int i;
	for (i = 0;i <m_enemy.getSize();i++)
		if (m_enemy[i])
		{
			m_fighter->getHit(m_enemy[i]->Hit(m_fighter));
			m_enemy[i]->getHit(m_fighter->Hit(m_enemy[i]));
		}
}