#ifndef SPEED_H_
#define SPEED_H_

#include<assert.h>
#include<math.h>
#include"costant.h"
#include"Location.h"


/*单位为像素格/GAP毫秒*/
struct Speed
{
	double m_speed;
	double m_angle;
	int m_x;
	int m_y;

	Speed(double s = 0, double a = 0) :m_speed(s), m_angle(a)
	{
		assert(m_angle >= 0 && m_angle <= 2 * PI);
		m_x = (int)m_speed*cos(m_angle);
		m_y = (int)-m_speed*sin(m_angle);
	}

	/*两种方式换算*/
	void transfer()
	{
		m_speed = sqrt(m_x*m_x + m_y*m_y);
		if (m_speed == 0)
			m_angle = 0;
		else
		{
			double t = asin(-m_y / m_speed);
			if (m_x <= 0 && m_y <= 0)
				m_angle = t;
			else if (m_x <= 0 && m_y > 0)
				m_angle = 2 * PI + t;
			else
				m_angle = PI - t;
		}
	}

	void SpeedReset(double s, double a)
	{
		m_speed = s;
		m_angle = a;
		m_x =(int) m_speed*cos(m_angle);
		m_y =(int)-m_speed*sin(m_angle);
	}

	void setSpeedX(int x)
	{
		m_x = x;
		transfer();
	}
	void setSpeedY(int y)
	{
		m_y = y;
		transfer();
	}
	void setSpeed(int x, int y)
	{
		m_x = x;
		m_y = y;
		transfer();
	}
	int getNextX(int posx)const{return (m_x + posx);}
	int getNextY(int posy)const{return m_y + posy;}
	Location getNextLoc(const Location& loc)const
	{
		return Location(loc.getLocX() + m_x, loc.getLocY() + m_y);
	}
};




#endif