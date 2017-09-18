#ifndef PLAYER_H_
#define PLAYER_H_



#include<string>
#include<iostream>
#include<conio.h>

const int MAX_LIFE = 3;



class Game;


class Player{

private:

	int m_dificulty;		
	int m_left;				
	int m_score;			
	std::string m_name;		
	int m_type;


public:

	friend class Game;

	Player(const std::string& name, int d = 0, int tp = 1) :
		m_dificulty(d),
		m_left(MAX_LIFE),
		m_score(0),
		m_name(name),
		m_type(tp)
	{
	}

	~Player() {};
};



#endif
