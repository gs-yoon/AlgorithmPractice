#include <iostream>

using namespace std;

#define LINE 1

void print_map(int input_map[10 * 2 - 1][30]);
bool operate_ladder(int input_map[10 * 2 - 1][30]);
void selcect_mid_line(int input_ladder_map[10 * 2 - 1][30], int start_hor_idx, int start_mid_idx, int trial);

int ver_line_max = 0;
int short_x_line_max = 0;
int dot_line_max = 0;

int ladder_map[10*2 -1 ][30] = {0};
int g_min = 5;
int main()
{
	cin >> ver_line_max >> short_x_line_max >> dot_line_max;

	for (int i = 0; i < short_x_line_max; i++)
	{
		int hor_line = 0;
		int mid_line = 0;
		cin >> hor_line >> mid_line;
		hor_line--;
		mid_line = mid_line * 2 - 1;
		ladder_map[mid_line][hor_line] = 1;
	}

	selcect_mid_line(ladder_map, 0, 1, 0);
	if (g_min >= 5)
	{
		g_min = -1;
	}
	cout << g_min;
}


void selcect_mid_line(int input_ladder_map[10 * 2 - 1][30], int start_hor_idx, int start_mid_idx, int trial)
{
	if (operate_ladder(input_ladder_map) == true)
	{
		if (g_min > trial)
		{
			g_min = trial;
			return;
		}
	}
	int trial_max = 3;
	if (g_min <= 3)
	{
		trial_max = g_min-1;
	}

	int local_ladder_map[10 * 2 - 1][30] = { 0 };
	for (int hor_idx = 0; hor_idx < dot_line_max; hor_idx++)
	{
		for (int ver_idx = 0; ver_idx <= ver_line_max * 2 - 2; ver_idx++)
		{
			local_ladder_map[ver_idx][hor_idx] = input_ladder_map[ver_idx][hor_idx];
		}
	}
	if (trial < trial_max)
	{
		trial++;
		int mid_ver_idx = start_mid_idx;
		for (int hor_idx = start_hor_idx; hor_idx < dot_line_max; hor_idx++)
		{
			for ( ; mid_ver_idx <= ver_line_max * 2 - 3; mid_ver_idx += 2)
			{
				if (local_ladder_map[mid_ver_idx][hor_idx] == 0)
				{
					int left_mid = mid_ver_idx - 2;
					int right_mid = mid_ver_idx + 2;
					int success = true;
					if (left_mid >= 0)
					{
						if (local_ladder_map[left_mid][hor_idx] == 1)
						{
							success = false;
						}
					}
					if ( right_mid <= ver_line_max * 2 - 3)
					{

						if (local_ladder_map[right_mid][hor_idx] == 1)
						{
							success = false;
						}
					}
					if (success)
					{
						local_ladder_map[mid_ver_idx][hor_idx] = 1;
						//print_map(local_ladder_map);
						selcect_mid_line(local_ladder_map, hor_idx, mid_ver_idx + 2, trial);
						local_ladder_map[mid_ver_idx][hor_idx] = 0;
					}
				}
			}
			mid_ver_idx = 1;
		}
	}

}

//ver line = 2N -2 까지
//middle_ladder =  2N -3 까지


bool operate_ladder(int input_map[10 * 2 - 1][30])
{
	for (int ver_idx = 0; ver_idx <= 2 * ver_line_max - 2; ver_idx+=2)
	{
		int cur_ver = ver_idx;
		int cur_hor = 0;
		for (cur_hor = 0; cur_hor < dot_line_max; )
		{
			int right_ver = cur_ver + 1;
			int left_ver = cur_ver - 1;

			if (right_ver <= 2 * ver_line_max - 2)
			{
				if (input_map[right_ver][cur_hor] == 1)
				{
					cur_ver = right_ver + 1;
				}
			}

			if (left_ver >= 0)
			{
				if (input_map[left_ver][cur_hor] == 1)
				{
					cur_ver = left_ver - 1;
				}
			}
			cur_hor++;
		}
		if (cur_ver != ver_idx)
		{
			return false;
		}
	}
	return true;

}

void print_map(int input_map[10 * 2 - 1][30])
{
	cout << endl;
	for (int hor_idx = 0; hor_idx < dot_line_max; hor_idx++)
	{
		for (int ver_idx = 0; ver_idx <= ver_line_max * 2 - 2; ver_idx++)
		{
			cout << input_map[ver_idx][hor_idx] << " ";
		}
		cout << endl;
	}
	cout << endl;
}