#include"Map.h"
#include<cmath>
#define pos_start_T this->position_start 
using namespace std;
void map_data::Print_Sightedmap()
{
	for (int y = 0;y < Y_border;y++)
	{
		for (int x = 0;x < X_border;x++)
		{
			if (sight[y][x])
			{
				cout << body[y][x];
			}
			else
			{
				cout << ' ';
			}
		}
		cout << endl;
	}
}
void map_data::Print_Allmap()
{
	for (int i = 0;i < Y_border;i++)
	{
		cout << this->body[i] << endl;
	}
}
void map_data::Set_Sight(int y,int x)
{
		sight[y][x] = 1;
		if (x - 1 >= 0)
		{
			if (sight[y][x - 1] == 0)//未走訪過
			{
				if (body[y][x - 1] == '0')//遇到牆壁中止
				{
					
				}
				else if (body[y][x - 1] == '3')//遇到門中止
				{
					sight[y][x - 1] = 1;
				}
				else
				{
					Set_Sight(y, x - 1);
				}
			}
		}
		if (x + 1 < X_border)
		{
			if (sight[y][x + 1] == 0)
			{
				if (body[y][x + 1] == '0' )
				{
					
				}
				else if (body[y][x + 1] == '3')
				{
					sight[y][x + 1] = 1;
				}
				else
				{
					Set_Sight(y, x + 1);
				}
			}
		}
		if (y - 1 >= 0)
		{
			if (sight[y - 1][x] == 0)
			{
				if (body[y - 1][x] == '0')
				{

				}
				else if (body[y - 1][x] == '3')
				{
					sight[y - 1][x] = 1;
				}
				else
				{
					Set_Sight(y - 1, x);
				}
			}
		}
		if (y + 1 <Y_border)
		{
			if (sight[y + 1][x] == 0)
			{
				if (body[y + 1][x] == '0' )
				{
					
				}
				else if (body[y + 1][x] == '3')
				{
					sight[y + 1][x] = 1;
				}
				else
				{
					Set_Sight(y + 1, x);
				}
			}
		}
}
void map_data::Set_Characterpos(int character_amount)
{
	Set_Sight(pos_start_T[0][0], pos_start_T[0][1]);
	string selectmove;
	bool choosed[4] = { 0 };
	char icon = 'A';
	for (int i = 0;i < character_amount;i++)
	{
		string *temp_map = new string[Y_border];
		for (int i = 0;i < Y_border;i++)
		{
			temp_map[i] = body[i];
		}
		// revise temp_map
		int origin_index;
		{
			// find * pos
			int min_row = 99999999;
			for (int a = 0;a < 4;a++)
			{
				if (!choosed[a])
				{
					if (pos_start_T[a][0] < min_row)
					{
						min_row = pos_start_T[a][0];
						origin_index = a;
					}
					else if (pos_start_T[a][0] == min_row)
					{
						if (pos_start_T[a][1] < pos_start_T[origin_index][1])
						{
							origin_index = a;
						}
					}
				}
			}
			// revise map
			for (int a = 0;a < 4;a++)
			{
				if (!choosed[a])
				{
					if (a == origin_index)
					{
						temp_map[pos_start_T[a][0]][pos_start_T[a][1]] = '*';
					}
					else
					{
						temp_map[pos_start_T[a][0]][pos_start_T[a][1]] = '_';
					}
				}
			}
		}
		//print
		{
			for (int y = 0;y < Y_border;y++)
			{
				for (int x = 0;x < X_border;x++)
				{
					if (sight[y][x])
					{
						cout << temp_map[y][x];
					}
					else
					{
						cout << ' ';
					}
				}
				cout << endl;
			}
		}
		//select pos
		cout << "請輸入起始位置\n";
		cin >> selectmove;
		{
			int x_selected = pos_start_T[origin_index][1], y_selected = pos_start_T[origin_index][0];
			for (int a = 0;a < selectmove.length();a++)
			{
				if (selectmove[a] == 'w')
				{
					for (int b = 0;b < 4;b++)//search start_pos
					{
						if (!choosed[b])//exclude used
						{
							if ((x_selected == pos_start_T[b][1]) && (y_selected - 1 == pos_start_T[b][0]))
							{
								y_selected --;
							}
						}
					}
				}
				else if (selectmove[a] == 'a')
				{
					for (int b = 0;b < 4;b++)
					{
						if (!choosed[b])
						{
							if ((x_selected - 1 == pos_start_T[b][1]) && (y_selected == pos_start_T[b][0]))
							{
								x_selected--;
							}
						}
					}
				}
				else if (selectmove[a] == 's')
				{
					for (int b = 0;b < 4;b++)
					{
						if (!choosed[b])
						{
							if ((x_selected == pos_start_T[b][1]) && (y_selected + 1 == pos_start_T[b][0]))
							{
								y_selected ++;
							}
						}
					}
				}
				else if (selectmove[a] == 'd')
				{
					for (int b = 0;b < 4;b++)
					{
						if (!choosed[b])
						{
							if ((x_selected + 1 == pos_start_T[b][1]) && (y_selected == pos_start_T[b][0]))
							{
								x_selected++;
							}
						}
					}
				}
			}
			
			//enter map
			S_coordinate temp;
			temp.x = x_selected, temp.y = y_selected;
			this->character_coordinate.push_back(temp);//character coordinate

			this->body[y_selected][x_selected] = icon;//map
			icon++;
			int b = 0;
			for (;b < 4;b++)
			{
				if ((x_selected == pos_start_T[b][1]) && (y_selected  == pos_start_T[b][0]))
				{
					choosed[b] = 1;
				}
			}

		}
	}

}
void map_data::Set_Monsterpos(string icon)
{
	int pos = 0;
	//cout << endl << icon << endl;
	for (auto monster_c : monster_coordinate)
	{
		body[monster_c.y][monster_c.x] = icon[pos];
		pos++;
	}
}

bool map_data::creature_Move(const char icon,const std::string movement)
{
	const int index = icon - 'A';
	if (index < 0 && index >= character_coordinate.size())
	{
		cout << "index ERROR in charaMove\n";
		return 0;
	}

	int X = character_coordinate[index].x, Y = character_coordinate[index].y;
	for (int i=0;i<movement.length();i++)
	{
		if (movement[i] == 'w')
		{
			Y--;
		}
		else if (movement[i] == 'a')
		{
			X--;
		}
		else if (movement[i] == 's')
		{
			Y++;
		}
		else if (movement[i] == 'd')
		{
			X++;
		}
		////移動是否合法
		if (Y<0||Y>Y_border||X<0||X>X_border)
		{
			return 0;
		}
		else if (body[Y][X] == '0' || body[Y][X] == '2')
		{
			return 0;
		}
		else if(body[Y][X] >= 'a'&&body[Y][X] <= 'z')
		{
			return 0;
		}
		else if (i == movement.length() - 1 && (body[Y][X] >= 'A'&&body[Y][X] <= 'Z'))
		{
			return 0;
		}

	}
	body[character_coordinate[index].y][character_coordinate[index].x] = '1';
	body[Y][X] = icon;
	character_coordinate[index].x = X;
	character_coordinate[index].y = Y;
	return 1;
}
bool map_data::creature_Move(const int index,const char icon,const std::string movement)
{
	if (index < 0 && index >= monster_coordinate.size())
	{
		cout << "index ERROR in monMove\n";
		return 0;
	}
		
	int X = monster_coordinate[index].x, Y = monster_coordinate[index].y;
	for (int i = 0;i < movement.length();i++)
	{
		if (movement[i] == 'w')
		{
			Y--;
			if (Y<0 || Y>Y_border || X<0 || X>X_border)
			{
				return 0;
			}
			else if (body[Y][X] == '0' || body[Y][X] == '2' || body[Y][X] == '3')
			{
				return 0;
			}
			else if (body[Y][X] >= 'A'&&body[Y][X] <= 'Z')
			{
				return 0;
			}
			else if (i == movement.length() - 1 && (body[Y][X] >= 'a'&&body[Y][X] <= 'z'))
			{
				return 0;
			}

			if (body[Y][X]=='1')
			{
				body[monster_coordinate[index].y][monster_coordinate[index].x] = '1';
				body[Y][X] = icon;
				monster_coordinate[index].y = Y;
			}
		}
		else if (movement[i] == 'a')
		{
			X--;
			if (Y<0 || Y>Y_border || X<0 || X>X_border)
			{
				return 0;
			}
			else if (body[Y][X] == '0' || body[Y][X] == '2' || body[Y][X] == '3')
			{
				return 0;
			}
			else if (body[Y][X] >= 'A'&&body[Y][X] <= 'Z')
			{
				return 0;
			}
			else if (i == movement.length() - 1 && (body[Y][X] >= 'a'&&body[Y][X] <= 'z'))
			{
				return 0;
			}

			if (body[Y][X] == '1')
			{
				body[monster_coordinate[index].y][monster_coordinate[index].x] = '1';
				body[Y][X] = icon;
				monster_coordinate[index].x = X;
			}
		}
		else if (movement[i] == 's')
		{
			Y++;
			if (Y<0 || Y>Y_border || X<0 || X>X_border)
			{
				return 0;
			}
			else if (body[Y][X] == '0' || body[Y][X] == '2' || body[Y][X] == '3')
			{
				return 0;
			}
			else if (body[Y][X] >= 'A'&&body[Y][X] <= 'Z')
			{
				return 0;
			}
			else if (i == movement.length() - 1 && (body[Y][X] >= 'a'&&body[Y][X] <= 'z'))
			{
				return 0;
			}

			if (body[Y][X] == '1')
			{
				body[monster_coordinate[index].y][monster_coordinate[index].x] = '1';
				body[Y][X] = icon;
				monster_coordinate[index].y = Y;
			}
		}
		else if (movement[i] == 'd')
		{
			X++;
			if (Y<0 || Y>Y_border || X<0 || X>X_border)
			{
				return 0;
			}
			else if (body[Y][X] == '0' || body[Y][X] == '2' || body[Y][X] == '3')
			{
				return 0;
			}
			else if (body[Y][X] >= 'A'&&body[Y][X] <= 'Z')
			{
				return 0;
			}
			else if (i == movement.length() - 1 && (body[Y][X] >= 'a'&&body[Y][X] <= 'z'))
			{
				return 0;
			}

			if (body[Y][X] == '1')
			{
				body[monster_coordinate[index].y][monster_coordinate[index].x] = '1';
				body[Y][X] = icon;
				monster_coordinate[index].x = X;
			}
		}
	}
	return 1;
}
int map_data::countRange(const int C_index, const int M_index)
{
	if (C_index >= 0 && C_index < character_coordinate.size() && M_index >= 0 && M_index < monster_coordinate.size())
		return abs(character_coordinate[C_index].x - monster_coordinate[M_index].x) + abs(character_coordinate[C_index].y - monster_coordinate[M_index].y);
	else
		cout << "index ERROR in countRange\n";
		return -1;
}
bool map_data::visible(const int C_index, const  int M_index)
{
	//vertical
	if (character_coordinate[C_index].x == monster_coordinate[M_index].x)
	{
		const int dy = character_coordinate[C_index].y - monster_coordinate[M_index].y;
		if (dy > 0)
		{
			for (int i = monster_coordinate[M_index].y + 1;i < character_coordinate[C_index].y;i++)
			{
				if (body[i][character_coordinate[C_index].x] == '0')
					return 0;
			}
			return 1;
		}
		else
		{
			for (int i = character_coordinate[C_index].y + 1;i < monster_coordinate[M_index].y;i++)
			{
				if (body[i][character_coordinate[C_index].x] == '0')
					return 0;
			}
			return 1;
		}
	}
	//parallel
	else if (character_coordinate[C_index].y == monster_coordinate[M_index].y)
	{
		const int dx = character_coordinate[C_index].x - monster_coordinate[M_index].x;
		if (dx > 0)
		{
			for (int i = monster_coordinate[M_index].x + 1;i < character_coordinate[C_index].x;i++)
			{
				if (body[character_coordinate[C_index].y][i] == '0')
				{
					return 0;
				}
			}
			return 1;
		}
		else
		{
			for (int i = character_coordinate[C_index].x + 1;i < monster_coordinate[M_index].x;i++)
			{
				if (body[character_coordinate[C_index].y][i] == '0')
				{
					return 0;
				}
			}
			return 1;
		}
	}
	//y=mx+c
	const double m = ((double)(character_coordinate[C_index].y - monster_coordinate[M_index].y)) / ((double)(character_coordinate[C_index].x - monster_coordinate[M_index].x));
	const double c = (((double)monster_coordinate[M_index].y + 0.5) - m * ((double)monster_coordinate[M_index].x + 0.5));
	const int dx = (character_coordinate[C_index].x - monster_coordinate[M_index].x);
	cout << "m: " << m << "c: " << c << endl;

	double ytmp;
	if (dx > 0)
		ytmp = monster_coordinate[M_index].y + 1;
	else
		ytmp = character_coordinate[C_index].y + 1;
	for (int ix = 1;ix <= abs(dx) + 1;ix++)
	{
		double ypos;
		double xpos;
		if (dx > 0)
		{
			ypos = m * (monster_coordinate[M_index].x + ix) + c;
			xpos = monster_coordinate[M_index].x + ix;
			if (m > 0)
			{
				bool singular_dot = 0;//經過交叉點
				if (ypos - (int)ypos == 0)
					singular_dot = 1;

				ypos = ceil(ypos);
				ytmp = ceil(ytmp);

				if (ypos >= ytmp)//
				{

					if (ix == abs(dx) + 1)
						ypos = character_coordinate[C_index].y + 1;
					for (int j = ytmp;j <= ypos;j++)
					{
						body[j - 1][xpos - 1] = 'T';
						//if (body[j - 1][xpos - 1] == '0')
						//{
						//	return 0;
						//}
					}
				}
				else
				{
					if (ix == abs(dx) + 1)
						ypos = character_coordinate[C_index].y + 1;
					for (int j = ypos;j <= ytmp;j++)
					{
						body[j - 1][xpos - 1] = 'T';
						//if (body[j - 1][xpos - 1] == '0')
						//{
						//	return 0;
						//}
					}
				}
				if (singular_dot)
					ypos++;
				ytmp = ypos;
			}
			else
			{
				bool singular_dot = 0;//經過交叉點
				if (ypos - (int)ypos == 0)
					singular_dot = 1;

				ypos = ceil(ypos);
				ytmp = ceil(ytmp);

				if (singular_dot)
					ypos++;
				if (ypos >= ytmp)//
				{

					if (ix == abs(dx) + 1)
						ypos = character_coordinate[C_index].y + 1;
					for (int j = ytmp;j <= ypos;j++)
					{
						body[j - 1][xpos - 1] = 'T';
						//if (body[j - 1][xpos - 1] == '0')
						//{
						//	return 0;
						//}
					}
				}
				else
				{
					if (ix == abs(dx) + 1)
						ypos = character_coordinate[C_index].y + 1;
					for (int j = ypos;j <= ytmp;j++)
					{
						body[j - 1][xpos - 1] = 'T';
						//if (body[j - 1][xpos - 1] == '0')
						//{
						//	return 0;
						//}
					}
				}
				if (singular_dot)
					ypos--;
				ytmp = ypos;
			}
		}
		else
		{
			ypos = m * (character_coordinate[C_index].x + ix) + c;
			xpos = character_coordinate[C_index].x + ix;
			if (m > 0)
			{
				bool singular_dot = 0;//經過交叉點
				if (ypos - (int)ypos == 0)
					singular_dot = 1;

				ypos = ceil(ypos);
				ytmp = ceil(ytmp);

				if (ypos >= ytmp)//
				{

					if (ix == abs(dx) + 1)
						ypos = monster_coordinate[M_index].y + 1;
					for (int j = ytmp;j <= ypos;j++)
					{
						body[j - 1][xpos - 1] = 'T';
						//if (body[j - 1][xpos - 1] == '0')
						//{
						//	return 0;
						//}
					}
				}
				else
				{
					if (ix == abs(dx) + 1)
						ypos = monster_coordinate[M_index].y + 1;
					for (int j = ypos;j <= ytmp;j++)
					{
						body[j - 1][xpos - 1] = 'T';
						//if (body[j - 1][xpos - 1] == '0')
						//{
						//	return 0;
						//}
					}
				}
				if (singular_dot)
					ypos++;
				ytmp = ypos;
			}
			else
			{
				bool singular_dot = 0;//經過交叉點
				if (ypos - (int)ypos == 0)
					singular_dot = 1;

				ypos = ceil(ypos);
				ytmp = ceil(ytmp);

				if (singular_dot)
					ypos++;
				if (ypos >= ytmp)//
				{

					if (ix == abs(dx) + 1)
						ypos = monster_coordinate[M_index].y + 1;
					for (int j = ytmp;j <= ypos;j++)
					{
						body[j - 1][xpos - 1] = 'T';
						//if (body[j - 1][xpos - 1] == '0')
						//{
						//	return 0;
						//}
					}
				}
				else
				{
					if (ix == abs(dx) + 1)
						ypos = monster_coordinate[M_index].y + 1;
					for (int j = ypos;j <= ytmp;j++)
					{
						body[j - 1][xpos - 1] = 'T';
						//if (body[j - 1][xpos - 1] == '0')
						//{
						//	return 0;
						//}
					}
				}
				if (singular_dot)
					ypos--;
				ytmp = ypos;
			}
		}
	}
	return 1;
}