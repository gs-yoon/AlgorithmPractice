
#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

int n = 0;
int m = 0;
int** map;

vector<pair<int, int>> store;
vector<pair<int, int>> house;


int main()
{
	//init
	cin >> n;
	cin >> m;

	int* comb;
	comb = new int[m];
	map = new int* [n];
	for (int i = 0; i < m; i++)
		comb[i] = i;
	for (int i = 0; i < n; i++)
		map[i] = new int[n];
	for (int i = 0; i < n * n; i++)
	{
		int d;
		cin >> d;
		map[i / n][i % n] = d;

		if (d == 1)
			house.push_back(make_pair(i / n, i % n));
		else if (d == 2)
			store.push_back(make_pair(i / n, i % n));

	}

	//solution
	bool end = false;
	int storeSize = store.size();
	int houseSize = house.size();
	int disSumMin = 9999;
	comb[m - 1]--;
	while (!end)
	{
		//make combination
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

		if (comb[0] == storeSize - m)
			end = true;
		
		int disSum = 0;
		//calcuate city chicken distance
		for (int i = 0; i < houseSize; i++)
		{
			int disMin = 999;
			for (int j = 0; j < m; j++)
			{
				int r = house[i].first - store[comb[j]].first;
				int c = house[i].second - store[comb[j]].second;

				if (r < 0)
					r *= -1;
				if (c < 0)
					c *= -1;

				int dis = r + c;

				if (disMin > dis)
				{
					disMin = dis;
				}
			}
			disSum += disMin;
			if (disSum > disSumMin)
				break;
		}

		if (disSum < disSumMin)
		{
			disSumMin = disSum;
		}
		
	}
	cout << disSumMin;
	return 0;
}

