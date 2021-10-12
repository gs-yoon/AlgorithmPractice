#include <iostream>

using namespace std;
#define MAX 15
int N = 0;
int t[MAX] = {0};
int p[MAX] = {0};
int g_max = 0;

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> t[i];
		cin >> p[i];
	}

	int max_wage[MAX] = {0};

	for (int rday = N - 1; rday >= 0 ; rday--)
	{
		int next_working_day = rday + t[rday];
		int today_working = 0;

		if (next_working_day > N)
		{
			today_working = 0;

		}
		else if (next_working_day == N)
		{
			today_working = p[rday];
		}
		else
		{
			today_working = p[rday] + max_wage[next_working_day];
		}

		if (rday + 1 < N)
		{
			if (max_wage[rday + 1] > today_working)
			{
				max_wage[rday] = max_wage[rday + 1];
			}
			else
			{
				max_wage[rday] = today_working;
			}
		}
		else
		{
			max_wage[rday] = today_working;
		}
	}
	/*
	for (int i = 0; i < N; i++)
		cout << max_wage[i] << " ";
	cout << endl << endl;
	*/
	g_max = max_wage[0];
	cout << g_max;
}