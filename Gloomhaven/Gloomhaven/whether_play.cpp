#include<string>
#include <iostream>
#include"whether_play.h"
bool whether_play()
{
	std::string temp;
	while (1)
	{
		std::cin >> temp;
		if (temp == "play")
			return true;
		else if (temp == "exit")
			return false;
		else if (temp == "")
			return false;
		else
		{
			std::cout << "����??��JPlay�٬OExit�n��??" << std::endl;
		}
		temp.clear();
	}
}