#ifndef LOCATION_H_
#define LOCATION_H_


/*在后期扩展中 Location应该是数组 以进行更加准确的定位与碰撞检测*/
/*当前将每个对象简化为圆 因此只需要一个圆心坐标即可*/

struct Location
{
	int m_px;
	int m_py;

	Location(int x = 0, int y = 0) :
		m_px(x),
		m_py(y) {};
	
	void setLocation(int x, int y)
	{
		m_px = x;
		m_py = y;
	}

	int getLocX()const{return m_px;}
	int getLocY()const{return m_py;}
	int cal_distance(const Location& loc)const
	{
		int a = m_px - loc.m_px;
		int b = m_py - loc.m_py;
		return sqrt(a*a + b*b);
	}
};


#endif