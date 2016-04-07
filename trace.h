#pragma once
#include "stdafx.h"

enum {
	smal=100,
	medium=250,
	large=500,
};

char main_color[] = "color ##";

class trace
{
private:
	vector<vector<int>> m_traca,m_traca_temp;
	vector<vector<int>> m_screen;
	vector<int> m_stroka1,m_stroka2;
	vector<int> m_stroka_finish1, m_stroka_finish2;

	int avto[3][5] = { { WHEEL1,200,202,188,WHEEL1 },{0,201,206,187,0},{ WHEEL1,126,203,126,WHEEL1 }, };
	
public:

	int speed= STANDART_SPEED;
	int again=1;
	trace();
	int set_the_traca(int,int);
	void get_the_traca(int);
	int put_the_car(int);
	void game();
	void copy_to_screen(int);
	void generate_prep();
	void change_color();
	void gotoXY(int, int);
	void change_direct();
};


void trace::change_direct()
{

	avto[0][0] = (avto[0][0] == WHEEL1) ? WHEEL2 : WHEEL1;
	avto[0][4] = (avto[0][4] == WHEEL1) ? WHEEL2 : WHEEL1;
	avto[2][0] = (avto[2][0] == WHEEL1) ? WHEEL2 : WHEEL1;
	avto[2][4] = (avto[2][4] == WHEEL1) ? WHEEL2 : WHEEL1;



}

void trace::gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),	coord	);
}

void trace::change_color()
{
	char x[] = "890A160F0";
	char y[] = "9fb07E1D9"; 
	int color = rand() % 9;

     main_color[6] = x[color];
     main_color[7] = y[color];
     system(main_color);

}

void trace::generate_prep()
{
	int temp1,temp2,temp3;
	int rand_temp;
	srand((unsigned int)time(NULL));

	for (int i = LENGTH_OF_SCREEN-5; i < (int)m_traca_temp.size()- LENGTH_OF_SCREEN-3; i +=rand()%3+5)
	{
		temp1 = rand() % (WEIGTH_OF_TRACE - 14) + 7;
		m_traca_temp.at(i).at(temp1) = PREP;
		m_traca_temp.at(i).at(temp1+1) = PREP;
		if ((rand_temp = rand()) % 2)
		{
			m_traca_temp.at(i).at(temp1 + 2) = PREP;
			m_traca_temp.at(i).at(temp1+3) = PREP;
		}



		{

			do
			temp2 = rand() % (WEIGTH_OF_TRACE - 14) + 8;
			while (abs(temp1 - temp2) < 6);


			m_traca_temp.at(i).at(temp2) = PREP;
			m_traca_temp.at(i).at(temp2 + 1) = PREP;
			if ((rand_temp = rand()) % 2)
			{
				m_traca_temp.at(i).at(temp2 + 2) = PREP;
				m_traca_temp.at(i).at(temp2 + 3) = PREP;
			}



		}
		if (rand() % 2)
		{

			do
				temp3 = rand() % (WEIGTH_OF_TRACE - 14) + 7;
			while ((abs(temp3 - temp2) < 7)&&(abs(temp3 - temp1) < 6));


			m_traca_temp.at(i).at(temp3) = PREP;
			m_traca_temp.at(i).at(temp3 + 1) = PREP;
			if ((rand_temp = rand()) % 2)
			{
				m_traca_temp.at(i).at(temp3 + 2) = PREP;
				m_traca_temp.at(i).at(temp3 + 3) = PREP;
			}


		}
	}
}




void trace::copy_to_screen(int time)
{
	if (time <(int) m_traca_temp.size() - LENGTH_OF_SCREEN)
	{
		m_screen.clear();
		for (int i = 0; i < LENGTH_OF_SCREEN; i++)
			m_screen.push_back(m_traca_temp.at(i + time));
	}
	else
	{
		
		m_screen.clear();
		for (int i = 0; i < LENGTH_OF_SCREEN; i++)
			m_screen.push_back(m_traca_temp.at((int)m_traca_temp.size()+ i  - LENGTH_OF_SCREEN-1));

	}

}



trace::trace()
{
	int lengthes[] = { 0,smal,medium,large };
	cout << "which length do you want?" << endl;
	cout << "1 - small" << endl;
	cout << "2 - medium" << endl;
	cout << "3 - large" << endl;
	char choice;
	int sch = 0;
	do
	{
		choice = _getch();
		if (choice < 49 || choice>51)
		{
			if (!sch)
			{
				cout << "Try again" << endl;
				sch++;
			}
		}
		
	} while (choice < 49 || choice>51);
	set_the_traca(lengthes[choice-48],WEIGTH_OF_TRACE);
	while (again)
	{
		m_traca_temp = m_traca;

		generate_prep();

		game();
	}
}
int trace::set_the_traca(int length,int weight)
{
	// 1 #
	m_stroka1.insert(m_stroka1.end(), 1, PREP);
	m_stroka1.insert(m_stroka1.end(), weight-2, 0);
	m_stroka1.insert(m_stroka1.end(), 1, PREP);

	//2 ##
	m_stroka2.insert(m_stroka2.end(), 2, PREP);
	m_stroka2.insert(m_stroka2.end(), weight-4, 0);
	m_stroka2.insert(m_stroka2.end(), 2, PREP);
	// finish line ==================
	m_stroka_finish1.insert(m_stroka_finish1.end(), weight , 61);
	// 2## than spaces
	m_stroka_finish2.insert(m_stroka_finish2.end(), 2, PREP);
	m_stroka_finish2.insert(m_stroka_finish2.end(), weight/2-5, 0);

	//finish 
	m_stroka_finish2.push_back(70);
	m_stroka_finish2.push_back(105);
	m_stroka_finish2.push_back(110);
	m_stroka_finish2.push_back(105);
	m_stroka_finish2.push_back(115);
	m_stroka_finish2.push_back(104);
	// spaces than 2 ##
	m_stroka_finish2.insert(m_stroka_finish2.end(), weight / 2 - 5, 0);
	m_stroka_finish2.insert(m_stroka_finish2.end(), 2, PREP);

	for (int i = 0; i < length; i++)
	{
		m_traca.push_back(m_stroka1);
		m_traca.push_back(m_stroka2);
		if (i == length - 12)
		{
			m_traca.push_back(m_stroka_finish1);
			m_traca.push_back(m_stroka_finish2);

		}

	}
	
	return 0;
}

void trace::get_the_traca(int time)
{
		for (int i = LENGTH_OF_SCREEN-1; i >=0; i--)
		{	
			for (int j = 0; j < WEIGTH_OF_TRACE; j++)
				printf("%c", m_screen.at(i).at(j));
			cout << endl;
		}
		cout << endl;
		cout <<"You progress is: "<< time*100 / (m_traca_temp.size()-24)<< "%               Your speed is [";
		printf("%c%c%c%c]\n", (speed > FOUR_SPEED) ? 0 : PREP, (speed > THIRD_SPEED) ? 0 : PREP, (speed >SECOND_SPEED) ? 0 : PREP, (speed >FIRST_SPEED) ? 0 : PREP);
}

int trace::put_the_car(int coord)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (m_screen.at(i).at(coord + j) == PREP)
				return 1;
			m_screen.at(i).at(coord + j) = avto[i][j];
		}
	}
		return 0;
}

void trace::game()
{
	int time = 0;
	int err = 0;
	int coord = WEIGTH_OF_TRACE/2-2;
	char symb;
	again = 1;
	speed= STANDART_SPEED;
	while (m_traca_temp.size() - time - 3- LENGTH_OF_SCREEN> 0)
	{

		gotoXY(0, 0);
		copy_to_screen(time);
		change_direct();
		if (put_the_car(coord))
		{
			system("cls");
			cout << "The END!" << endl;
			cout << " Again? Any key( except 0) - Yes 0 - No" << endl;
			symb = _getch();
			if (symb == 48)
				again = 0;
			err = 1;
			break;
		}
		get_the_traca(time);

		while (_kbhit())
		{
			symb = _getch();
			switch (symb)
			{
			case 'a':
			case 'ô':
				if(coord>1)
				coord-=2;
				break;
			case 'd':
			case 'â':
				if (coord<WEIGTH_OF_TRACE-6)
				coord+=2;
				break;
			case 'w':
			case 'ö':
				if (speed > FIRST_SPEED)
					speed -= DELTA_SPEED;
				break;
			case 's':
			case 'û':
				if (speed<FIVE_SPEED)
					speed+= DELTA_SPEED;
				break;
			case 32:
				change_color();
				break;
			default:
				break;
			}
		}
		Sleep(speed);
		time++;
	}
	if (!err)
	{
		system("cls");
		cout << "Congratulations" << endl;
		_getch();
	}

}