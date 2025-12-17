#include <iostream>
#include <cstdarg>
using namespace std;
/*
* output
5,3,5,10의 평균은 5
5,10,15,20,25,30,35,40, 45의 평균은 25

Variable argument는 cstdarg에 정의되어 있어 그것을 할용하면 된다.
주어진 함수의  형식이 int calculateAverage(int score1, int score2,...)
이기 때문에 일반적인 int function(int count, int...)의 count=개수로 판별하는 것이 아니라, 특정 올 수 없는 수(-1)를 마지막에 넣은 뒤 
그것을 검사해서 끝을 판별하는 방법을 사용하였다.

va_start는 score2의 다음 인자부터 순회한다. va_arg로 -1이 올때까지 인자를 뽑다가, -1이 오면 break한다.

*/
int calculateAverage(int score1, int score2, ...)
{
	va_list list;
	int average=0;
	va_start(list, score2);
	int buffer = 0;
	average += score1 + score2;
	int cnt = 2;

	while (true)
	{
		buffer = va_arg(list, int);
		if (buffer == -1)break;
		average += buffer;
		cnt++;
	}	
	average /= cnt;
	

	va_end(list);
	return average;
}

int main()
{
	cout<<"5,3,5,10의 평균은 "<<calculateAverage(5, 3, 5, 10, -1)<<endl;
	cout << "5,10,15,20,25,30,35,40, 45의 평균은 " << calculateAverage(5, 10, 15, 20, 25, 30, 35, 40,45, -1) << endl;
}