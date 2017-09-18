#ifndef  ARR_H_
#define ARR_H_

#include<iostream>
#include<memory.h>

template<typename T>
class Arr
{
private:
	enum {SIZE=100};

	int m_bufferSize;
	int m_curNum;
	T**m_data;
	int m_next;
	bool*m_flag;

public:
	Arr(int sz = SIZE) :m_bufferSize(sz), m_next(0), m_curNum(0)
	{
		m_flag = new bool[m_bufferSize];
		memset(m_flag, 0, sizeof(bool)*m_bufferSize);

		m_data = new T*[m_bufferSize];
		for (int i = 0;i < m_bufferSize;i++)
			m_data[i] = NULL;
	}

	Arr(const Arr<T>&);
	Arr& operator=(const Arr<T>&);
	T* operator[](int);

	int insert(const T*);
	void remove(int);
	void setFlag(int);
	void removeAll()
	{
		for (int i = 0;i < m_bufferSize;i++)
			if (m_flag[i])
				remove(i);
		memset(m_flag, 0, sizeof(bool)*m_bufferSize);
	}

	void restart()
	{
		for (int i = 0;i < m_bufferSize;i++)
			if (m_data[i])
			{
				delete m_data[i];
				m_data[i] = NULL;
			}
		m_curNum = 0;
		memset(m_flag, 0, sizeof(bool)*m_bufferSize);
	}

	int getNum()const { return m_curNum; }
	int getSize()const { return m_bufferSize; }

	~Arr()
	{
		for (int i = 0;i < m_curNum;i++)
			delete m_data[i];
		delete[] m_data;
	}
};

template<typename T>
inline Arr<T>::Arr(const Arr<T>& x)
{
	m_bufferSize = x.m_bufferSize;
	m_curNum = 0;
	m_next = 0;
	m_data = new T[m_bufferSize];
	int i;
	for (i = 0;i < m_bufferSize;i++)
		m_data[i] = NULL;
}

template<typename T>
inline Arr<T>& Arr<T>::operator=(const Arr<T>& x)
{
	for (int i = 0;i < m_bufferSize;i++)
		delete m_data[i];
	delete[] m_data;

	m_bufferSize = x.m_bufferSize;
	m_curNum = 0;
	m_next = 0;
	m_data = new T[m_bufferSize];
	for (int i = 0;i < m_bufferSize;i++)
			m_data[i] = NULL;
	return *this;
}
template<typename T>
inline T* Arr<T>::operator[](int index)
{
	if (index < 0 || index >= m_bufferSize)
	{
		std::cout << "invalid index" <<std::endl;
		exit(-1);
	}
	return m_data[index];
}
template<typename T>
inline void Arr<T>::setFlag(int index)
{
	if (index < 0 || index >= m_bufferSize)
	{
		std::cout << "invalid index" << std::endl;
		exit(-1);
	}
	if (m_data[index])
		m_flag[index] = true;
}
template<typename T>
inline int Arr<T>::insert(const T* x)
{
	m_data[m_next] =const_cast<T*>(x);
	m_curNum++;
	int r = m_next;
	for (int i =1;i < m_bufferSize;i++)
		if (!m_data[(m_next + i) % m_bufferSize])
		{
			m_next = (m_next + i) % m_bufferSize;
			break;
		}
	return r;
}
template<typename T>
inline void Arr<T>::remove(int index)
{
	if (index < 0 || index >= m_bufferSize)
	{
		std::cout << "index invalid: " << index << std::endl;
		exit(-1);
	}
	if (m_data[index])
	{
		delete m_data[index];
		m_data[index] = NULL;
		m_curNum--;
	}
}
#endif