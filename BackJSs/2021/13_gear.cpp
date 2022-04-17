#include <iostream>

using namespace std;

#define CLOCKWISE 1
#define COUNTERCLOKCWISE -1
#define NPOLE 0
#define SPOLE 1

void rotate_atom(int gear_idx, int dir);
void rotate_recrusion(int gear_idx, int dir);
void print_map();

int gear_arr[4][8] = { 0 };

int turning_max = 0;
int gear_selection[100] = {0};
int turning_dir[100] = {0};

int three_clock_idx[4] = { 2,2,2,2 };
int nine_clock_idx[4] = { 6,6,6,6 };
int twelve_clock_idx[4] = { 0,0,0,0 };
int gear_input[4] = {0};
bool visited[4] = { 1 };

int main()
{
	for (int gear_num = 0; gear_num < 4; gear_num++)
	{
		cin >> gear_input[gear_num];
	}
	cin >> turning_max;
	for (int i = 0; i < turning_max; i++)
	{
		cin >> gear_selection[i];
		cin >> turning_dir[i];
		gear_selection[i]--;
	}

	for (int gear_num = 0; gear_num < 4; gear_num++)
	{
		int div = 10000000;
		for (int i = 0; i < 8; i++)
		{
			gear_arr[gear_num][i] = gear_input[gear_num] / div;

			if (gear_arr[gear_num][i] == 1)
			{
				gear_input[gear_num] -= div;
			}
			div /= 10;
		}
	}

	for (int trial = 0; trial < turning_max; trial++)
	{
		for (int i =0 ; i<4 ; i++)
			visited[i]= 0;
		rotate_recrusion(gear_selection[trial], turning_dir[trial]);
		//print_map();
	}

	int sum = 0;
	int weight = 1;
	for (int gear_idx = 0; gear_idx < 4; gear_idx++)
	{
		if (gear_arr[gear_idx][twelve_clock_idx[gear_idx]] == SPOLE)
		{
			sum += weight;
		}
		weight *= 2;
	}

	cout << sum;
}

void rotate_atom(int gear_idx, int dir)
{
	if (dir == CLOCKWISE)
	{
		three_clock_idx[gear_idx]--;
		if(three_clock_idx[gear_idx] < 0 )
			three_clock_idx[gear_idx]= 7;
	}
	else
	{
		three_clock_idx[gear_idx]++;
	}
	three_clock_idx[gear_idx] %= 8;
	nine_clock_idx[gear_idx] = (three_clock_idx[gear_idx] + 4) % 8;
	twelve_clock_idx[gear_idx] =( three_clock_idx[gear_idx] + 6) %8;
}

void rotate_recrusion(int gear_idx, int dir)
{
	int right_gear_idx = gear_idx + 1;
	int left_gear_idx = gear_idx - 1;
	int temp_three = gear_arr[gear_idx][three_clock_idx[gear_idx]];
	int temp_nine = gear_arr[gear_idx][nine_clock_idx[gear_idx]];
	rotate_atom(gear_idx, dir);
	visited[gear_idx] = true;

	if (right_gear_idx < 4 )
	{
		if (visited[right_gear_idx] == false)
		{
			if (temp_three != gear_arr[right_gear_idx][nine_clock_idx[right_gear_idx]])
			{
				rotate_recrusion(right_gear_idx, dir * -1);
			}
		}
	}
	if (left_gear_idx >= 0)
	{
		if (visited[left_gear_idx] == false)
		{
			if (temp_nine != gear_arr[left_gear_idx][three_clock_idx[left_gear_idx]])
			{
				rotate_recrusion(left_gear_idx, dir * -1);
			}
		}
	}
}

void print_map()
{
	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		cout <<three_clock_idx[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 4; i++)
		cout << nine_clock_idx[i] << " ";
	cout << endl;
	cout << endl;
}