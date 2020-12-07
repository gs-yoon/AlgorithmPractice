#include<iostream>

using namespace std;


int main_()
{
	int storeSize = 13;
	int m = 5;
	int* comb;
	comb = new int[m];
	for (int i = 0; i < 5; i++)
		comb[i] = i;

	bool end = 0;

	while (!end)
	{//make combination
		for (int i = m - 1; i >= 0; i--)
		{
			if (comb[i] + 1 < storeSize - (m - 1 - i))
			{
				comb[i]++;

				for (int j = i; j < m - 1; j++)
				{
					comb[j + 1] = comb[j] + 1;
				}
				break;
			}

		}
		for (int i = 0; i < m; i++)
		{
			cout << comb[i] << " ";
		}
		cout << endl;
		if (comb[0] == storeSize - m)
			end = true;
	}
	return 0;
}