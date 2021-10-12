#include <iostream>

using namespace std;

#define MAX 20

void selectPlayer(int input_player_arr[], int last_index, int trial);
void print_arr(int A[], int B[]);

int N = 0;
int S[MAX][MAX] = { 99 };
int team_max = 0;
int g_min = 99999;
int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> S[i][j];
		}
	}
	team_max = N / 2;

	int player_teamA_arr[MAX / 2] = { 99 };
	selectPlayer(player_teamA_arr, -1, -1);
	cout << g_min;
}

void selectPlayer(int input_player_teamA_arr[], int last_index, int trial)
{
	trial++;
	if (trial < team_max)
	{
		int local_player_teamA_arr[MAX / 2] = {99};
		for (int i = 0; i < team_max; i++)
		{
			local_player_teamA_arr[i] = input_player_teamA_arr[i];
		}
		for (int i = last_index + 1; i < N; i++)
		{
			local_player_teamA_arr[trial] = i;
			selectPlayer(local_player_teamA_arr, i, trial);
		}
	}

	else
	{
		int local_player_teamB_arr[MAX / 2] = { 99, };
		bool visited[MAX] = { 0};
		for (int i = 0; i < team_max; i++)
		{
			visited[input_player_teamA_arr[i]] = 1;
		}
		int num = 0;
		for (int i = 0; i < N; i++)
		{
			if (visited[i] == 0)
			{
				local_player_teamB_arr[num] = i;
				num++;
			}
		}

		int teamA_ability = 0;
		int teamB_ability = 0;
		for (int i = 0; i < team_max; i++)
		{
			for (int j = 0; j < team_max; j++)
			{
				teamA_ability += S[input_player_teamA_arr[i]][input_player_teamA_arr[j]];
				teamB_ability += S[local_player_teamB_arr[i]][local_player_teamB_arr[j]];
			}
		}
		int diff = 0;
		if (teamA_ability >= teamB_ability)
		{
			diff = teamA_ability - teamB_ability;
		}
		else
		{
			diff = teamB_ability - teamA_ability ;
		}
		if (g_min > diff)
		{
			g_min = diff;
		}
	}
}


void print_arr(int A[],int B[])
{
	cout << "A : ";
	for (int i = 0; i < team_max; i++)
		cout << A[i] << " ";
	cout << endl<<"B : ";
	for (int i = 0; i < team_max; i++)
		cout << B[i] << " ";
	cout << endl;
}