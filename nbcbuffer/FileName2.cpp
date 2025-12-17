#include <string>
#include <iostream>
#include <Windows.h>
using namespace std;

/*
* input
* 안녕하세요. ...처음뵙겠습니다. ...여기는 nbc입니다.
*/

void main()
{
	float sleeptime = 50;
	int i;
	string text;
	getline(cin, text); // 입력을 받는 부분
	for (i = 0; i < text.length(); i++)
	{
		if (text[i] == '.' && i < text.length() - 2)
		{
			if (text[i+1] == '.' && text[i + 2] == '.')
			{
				Sleep(sleeptime);
				i = i + 2;
				cout << endl;
			}
			else
			{
				Sleep(sleeptime);
				cout << text[i];
			}
		}
		else
		{
			Sleep(sleeptime);
			cout << text[i];
		}
		
	}


}
