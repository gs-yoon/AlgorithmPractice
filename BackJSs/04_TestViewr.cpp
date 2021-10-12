#include <iostream>

using namespace std;

int N = 0;
int mainViewrAbility = 0;
int subViewrAbility = 0;
int* area;

int main()
{
	long int needs=0;
	cin >> N;
	area = new int[N];
	for (int i = 0; i < N; i++)
	{
		cin >> area[i];
	}
	cin >> mainViewrAbility;
	cin >> subViewrAbility;

	for (int i = 0; i < N; i++)
	{
		area[i] -= mainViewrAbility;
		needs++;
		if (area[i] > 0)
		{
			if (subViewrAbility != 0)
			{
				needs += area[i] / subViewrAbility;
				if (area[i] % subViewrAbility > 0)
				{
					needs++;
				}
			}
		}
	}
	cout << needs;
}