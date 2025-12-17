#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <unordered_map>

using namespace std;

//중단사항
//1. 연산자가 연달아 있는 경우
//2. 계산기에 있으면 안될 값이 있는 경우
//3. 안닫힌 괄호가 있을 경우
//4. 괄호 앞뒤에 이상한 값이 있을 경우(ex) 열린 괄호 뒤에 연산자가 오거나, 닫힌 괄호 앞에 연산자가 올 경우, 열린 괄호 앞이나 닫힌 괄호 뒤는 괜찮다.)
/*
알고리즘
- 문자열의 공백을 없앤다.
- 먼저 중단사항을 검사해서 문제가 있으면 중단한다.
- 문자열의 가장 안쪽 괄호를 찾아서 그 괄호부터 계산한다.
- 안쪽 괄호의 연산만 뽑아다가 함수로 보내서 괄호를 없애고 값만 저장한다. 추출한 값은 맵에 첫번째 주소를 가리키는 곳에 넣는다.
  ex) 1+5를 할 경우(길이 : 3) cal_map[0]="6"이 되고, 문자열 buffer[0]='m'이 된다. 나머지는 공백 처리한다. "m  "
- 해당 함수를 재귀호출해서 최종 문자열의 괄호가 없어지게 한다.
- 최종 문자열을 다시 함수로 보내서 최종 계산을 한다.
- cal_map[0]의 값을 출력한다.

*/
/*
입력 예시
1. 문자열 형식으로 개행을 통해 문자열을 구분하며, calculate를 입력할 경우 앞서 입력한 문자열들이 전부 계산된다.

input)

1+1
2*6=
3.33/5.2=
5++2
nbc
(5+2)(
5*(2+)=
(((5+7)))
2+3*5=
calculate


output)
2
12
0.640385
4번째 식이 잘못되었습니다.(연산자가 2개 이상 연달아 사용되었습니다)
5번째 식이 잘못되었습니다.(계산기에 불가능한 연산 및 숫자입니다)
6번째 식이 잘못되었습니다.(괄호를 짝지어서 여닫지 않았습니다.)
7번째 식이 잘못되었습니다.(괄호 앞뒤에는 연산자나 다른 기호가 올수 없습니다.)
12
17




*/

void calculatethis(string &buffer,int start,int end, unordered_map<int, double> &cal_map)
{
	int i,j;
	int pmcnt = 0;
	int mdcnt = 0;
	char plusminus[2] = { '+','-' };
	char muldiv[2] = { '*','/' };
	string str;
	double num1;
	int lastpm = 0;

	//연산자의 개수를 센다.
	for (i = start; i < end; i++)
	{
		for (j = 0; j < 2; j++)
		{
			if (buffer[i] == plusminus[j])
			{
				pmcnt++;
			}
			if (buffer[i] ==muldiv[j])
			{
				mdcnt++;
			}
		}
	}
	//연산자가 없을 경우
	if (pmcnt+mdcnt == 0)
	{
		if (buffer[start] == 'm')return;
		for (i = start+1; i < end; i++)
		{
			if (buffer[i] == 'm')
			{
				buffer[start] = 'm';
				cal_map[start] = cal_map[i];
				buffer[i] = ' ';
				cal_map[i] = 0;
				return;
			}
		}



		str=buffer.substr(start, end - start);
		stringstream ss(str);
		ss >> num1;
		cal_map[start] = num1;
		buffer[start] = 'm';
		for (i = start + 1; i < end; i++)
		{
			buffer[i] = ' ';
		}
		return;
	}
	//연산자가 1개일 경우
	if (pmcnt + mdcnt == 1)
	{
		
		for (i = start; i < end; i++)
		{
			if (buffer[i] == '+'||buffer[i]=='-'||buffer[i]=='*'||buffer[i] == '/')
			{
				if (buffer[start] != 'm')
				{
					calculatethis(buffer, start, i, cal_map);
				}
				if (buffer[i + 1] != 'm')
				{
					calculatethis(buffer, i + 1, end, cal_map);
				}
				switch (buffer[i])
				{
				case '+':
					num1 = cal_map[start] + cal_map[i + 1];
					break;
				case '-':
					num1 = cal_map[start] - cal_map[i + 1];
					break;
				case '*':
					num1 = cal_map[start] * cal_map[i + 1];
					break;
				case '/':
					num1 = cal_map[start] / cal_map[i + 1];
					break;
				}
				cal_map[start] = num1;
				buffer[i] = ' ';
				buffer[i + 1] = ' ';
			}
		}
	}
	//연산자가 2개 이상일경우
	if (pmcnt + mdcnt > 1)
	{
		lastpm = start;
		//곱셈, 나눗셈을 우선적으로 계산한다.
		if (mdcnt > 0)
		{
			for (i = start; i < end; i++)
			{
				if (buffer[i] == '+' || buffer[i] == '-')
				{
					lastpm = i + 1;
				}
				if (buffer[i] == '*' || buffer[i] == '/')
				{
					for (j = i + 1; j < end; j++)
					{
						if (buffer[j] == '+' || buffer[j] == '-' || buffer[j] == '*' || buffer[j] == '/' || j == end - 1)
						{
							if (j == end - 1) j = end;
							return calculatethis(buffer, lastpm, j, cal_map);
						}
					}
				}
			}
		}
		//곱셈, 나눗셈이 없을 경우 순차적으로 계산한다.
		else
		{
			for (i = start; i < end; i++)
			{
				if (buffer[i] == '+' || buffer[i] == '-')
				{
					for (j = i + 1; j < end; j++)
					{
						if (buffer[j] == '+' || buffer[j] == '-'|| j == end - 1)
						{
							if (j == end - 1) j = end;
							return calculatethis(buffer,start, j, cal_map);
						}
					}
				}
			}

		}



	}



}






int main()
{
	vector<string> cal_string;
	vector<string> buffervector;
	char ops[6] = { '+','-','*','/','.','='};
	string buffer;
	string token;
	string sbuffer;
	char cbuffer;
	bool ispossible = false;
	bool isopsnotpossible = false;
	bool isbracketnotpossible = false;
	bool isbracknotopen = false;
	stack<int> brackstack;
	int lastopenbrack = 0;
	int ki;
	unordered_map<int, double > cal_map;

	//입력을 받다가 "calculate"가 들어오면 입력을 종료한다.
	while (true)
	{
		getline(cin, buffer);
		if (buffer == "calculate") break;
		cal_string.push_back(buffer);
	}
	
	for (int i = 0; i < cal_string.size(); i++)
	{
		//공백 제거
		sbuffer = cal_string[i];
		sbuffer.erase(remove(sbuffer.begin(), sbuffer.end(),' '), sbuffer.end());
		isopsnotpossible = false;
		isbracketnotpossible = false;
		isbracknotopen = false;
		while (brackstack.empty() == false) brackstack.pop();
		for (int j = 0; j < sbuffer.length(); j++)
		{
			ispossible = false;
			cbuffer = sbuffer[j];
			//숫자인지 체크
			if (cbuffer >= '0' && cbuffer <= '9')
			{
				ispossible = true;
			}
			//연산자인지 체크
			for (int k = 0; k < 6; k++)
			{
				if (cbuffer == ops[k])
				{
					ispossible = true;
					//연산자가 연달아 있는지 체크
					if (j != sbuffer.length() - 1)
					{
						for (int kn = 0; kn < 6; kn++)
						{
							if (sbuffer[j + 1] == ops[kn])
							{
								isopsnotpossible = true;
								break;
							}
						}
					}
					break;
				}
			}
			//괄호인지 체크
			if (cbuffer == '(')
			{
				ispossible = true;
				//'('뒤에 오는게 '(',')'나 숫자여야함.
				if (j != sbuffer.length() - 1)
				{
					if (sbuffer[j + 1] !='('&&(sbuffer[j+1]<'0'||sbuffer[j+1]>'9')&&sbuffer[j+1]!=')')
					{
							isbracketnotpossible = true;
							break;
					}
				}
				//열린괄호면 push
				brackstack.push(1);

			}
			if (cbuffer == ')')
			{
				ispossible = true;
				//')'앞에오는게 '(',')'나 숫자여야함.
				if (j != 0)
				{
					if (sbuffer[j - 1] != '(' && (sbuffer[j - 1] < '0' || sbuffer[j- 1]>'9') && sbuffer[j - 1] != ')')
					{
						isbracketnotpossible = true;
						break;
					}
				}
				//닫힌괄호면 pop, 열린괄호가 없다면 break
				if (brackstack.empty() == true)
				{
					isbracknotopen = true;
					break;
				}
				brackstack.pop();
			}

			//중단사항에 포함되면 중단
			if (!ispossible) break;
			if (isopsnotpossible) break;
			if (isbracketnotpossible)break;
			if (isbracknotopen)break;
		}
		//문자열 한바퀴 순회 완료 및 중단사항 체크

		if (!ispossible)
		{
			cout << i + 1 << "번째 식이 잘못되었습니다.(계산기에 불가능한 연산 및 숫자입니다)" << endl;
			continue;
		}
		if (isopsnotpossible)
		{
			cout << i + 1 << "번째 식이 잘못되었습니다.(연산자가 2개 이상 연달아 사용되었습니다)" << endl;
			continue;
		}
		if (isbracketnotpossible)
		{
			cout << i + 1 << "번째 식이 잘못되었습니다.(괄호 앞뒤에는 연산자나 다른 기호가 올수 없습니다.)" << endl;
			continue;
		}
		
		if (isbracknotopen||brackstack.empty()==false)
		{
			cout << i + 1 << "번째 식이 잘못되었습니다.(괄호를 짝지어서 여닫지 않았습니다.)" << endl;
			continue;
		}
		
		//중단사항 체크 완료

		//괄호를 먼저 계산한다.
		while (true)
		{
			for (ki = 0; ki < sbuffer.length(); ki++)
			{
				cbuffer = sbuffer[ki];
				if (cbuffer == '(') lastopenbrack = ki;
				if (cbuffer == ')')
				{
					//제일 안쪽의 괄호를 먼저 계산한다.
					sbuffer[ki] = ' ';
					sbuffer[lastopenbrack] = ' ';
					calculatethis(sbuffer, lastopenbrack, ki,cal_map);
					break;
				}
			}
			//닫힌 괄호가 없다면 탈출
			if (ki == sbuffer.length()) break;

		}

		//연산자가 없을 때까지 반복한다.
		while (true)
		{
			for (ki = 0; ki < sbuffer.length(); ki++)
			{
				cbuffer = sbuffer[ki];
				if (cbuffer == '+' || cbuffer == '-' || cbuffer == '*' || cbuffer == '/')
				{
					calculatethis(sbuffer, 0, sbuffer.length(), cal_map);
					break;
				}
			}
			//연산자가 남아있지 않다면 탈출
			if (ki == sbuffer.length())break;
		}


		//정답은 맨 앞에 저장된다.
		cout << cal_map[0] << endl;
	}

}