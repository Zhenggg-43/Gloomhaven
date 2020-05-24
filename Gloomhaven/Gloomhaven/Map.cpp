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
bool map_data::step(int Y,int X)
{

}
bool map_data::creature_Move(const int index,const char icon,const std::string movement)
{
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

			if (body[Y][X])
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

			if (body[Y][X])
			{
				body[monster_coordinate[index].y][monster_coordinate[index].x] = '1';
				body[Y][X] = icon;
				monster_coordinate[index].y = Y;
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

			if (body[Y][X])
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

			if (body[Y][X])
			{
				body[monster_coordinate[index].y][monster_coordinate[index].x] = '1';
				body[Y][X] = icon;
				monster_coordinate[index].y = Y;
			}
		}
	}
	return 1;
}
int map_data::countRange(int C_index, int M_index)
{
	if (C_index >= 0 && C_index < character_coordinate.size() && M_index >= 0 && M_index < monster_coordinate.size())
		return abs(character_coordinate[C_index].x - monster_coordinate[M_index].x) + abs(character_coordinate[C_index].y - monster_coordinate[M_index].y);
	else
		return -1;
}
bool map_data::visible(int C_index,  int M_index)
{
	return 1;
}