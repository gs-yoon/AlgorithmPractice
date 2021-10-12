#include <iostream>

using namespace std;

#define WALL 6
#define VISITED 7
#define MAX 8 

enum direction_e
{
	UP =0,
	LEFT,
	DOWN,
	RIGHT
};
void print_map(int input_map[MAX][MAX]);
void operate_ccvt(int local_map[MAX][MAX], int input_dir_by_kind[], int start_x, int start_y);
void select_dir(int dir_comb[], int trial);

int dx[] = { 0,-1,0,1 };
int dy[] = { -1,0,1,0 };
int y_max = 0;
int x_max = 0;
int g_map[MAX][MAX] = { 0 };
int cctv_X_arr[8];
int cctv_Y_arr[8];
int cctv_kind_arr[8];
int cctv_num;
int g_min = 9999;
int main()
{
	cin >> y_max >> x_max;
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			cin >> g_map[xi][yi];
			if (0 < g_map[xi][yi] && g_map[xi][yi] < WALL)
			{
				cctv_X_arr[cctv_num] = xi;
				cctv_Y_arr[cctv_num] = yi;
				cctv_kind_arr[cctv_num] = g_map[xi][yi];
				cctv_num++;
			}
		}
	}
	int dir_comb[8] = { 0 };

	int sum = 0;
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			if (g_map[xi][yi] == 0)
			{
				sum++;
			}
		}
	}
	if (g_min > sum)
		g_min = sum;

	select_dir(dir_comb, 0);
	cout << g_min;
}

void select_dir(int dir_comb[], int trial)
{
	int loca_dir_comb[8] = {0};
	for (int i = 0; i < cctv_num; i++)
	{
		loca_dir_comb[i] = dir_comb[i];
	}
	if (trial < cctv_num)
	{
		int cctv_idx = trial;
		trial++;
		for (int new_dir = 0; new_dir < 4; new_dir++)
		{
			if (cctv_kind_arr[cctv_idx] == 2)
			{
				if (new_dir >= 2)
				{
					break;
				}
			}
			else if (cctv_kind_arr[cctv_idx] == 5)
			{
				if (new_dir >= 1)
				{
					break;
				}
			}
			loca_dir_comb[cctv_idx] = new_dir;
			select_dir(loca_dir_comb, trial);
		}
	}
	else
	{
		int local_map[MAX][MAX];
		for (int yi = 0; yi < y_max; yi++)
		{
			for (int xi = 0; xi < x_max; xi++)
			{
				local_map[xi][yi] = g_map[xi][yi];
			}
		}
		for (int cctv_idx = 0; cctv_idx < cctv_num; cctv_idx++)
		{
			int start_x = cctv_X_arr[cctv_idx];
			int start_y = cctv_Y_arr[cctv_idx];
			int dir_by_kind[4] = { 0 };
			for (int i = 0; i < 4; i++)
				dir_by_kind[i] = 0;

			switch (cctv_kind_arr[cctv_idx])
			{
			case 1:

				dir_by_kind[dir_comb[cctv_idx]] = 1;
				break;
			case 2:
				
				dir_by_kind[dir_comb[cctv_idx]] = 1;
				dir_by_kind[ (dir_comb[cctv_idx]+2) %4] = 1;

				break;
			case 3:

				dir_by_kind[dir_comb[cctv_idx]] = 1;
				dir_by_kind[(dir_comb[cctv_idx] + 1) % 4] = 1;
				break;
			case 4:
				for (int i = 0; i < 4; i++)
					dir_by_kind[i] = 1;

				dir_by_kind[dir_comb[cctv_idx]] = 0;
				break;
			case 5:
				for (int i = 0; i < 4; i++)
					dir_by_kind[i] = 1;
				break;
			default:
				break;
			}
			operate_ccvt(local_map, dir_by_kind, start_x, start_y);
		}
		print_map(local_map);
	}
}


void operate_ccvt(int local_map[MAX][MAX],int input_dir_by_kind[], int start_x, int start_y)
{
	for (int i = 0; i < 4; i++)
	{
		if (input_dir_by_kind[i] == 1)
		{
			int dir = i;

			int next_x = start_x + dx[dir];
			int next_y = start_y + dy[dir];
			while (0 <= next_x && next_x < x_max && 0 <= next_y && next_y < y_max && g_map[next_x][next_y] != WALL)
			{
				local_map[next_x][next_y] = VISITED;
				next_x += dx[dir];
				next_y += dy[dir];
			}
		}
	}

	int sum = 0;
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			if (local_map[xi][yi] == 0)
			{
				sum++;
			}
		}
	}
	if (g_min > sum)
		g_min = sum;

}

void print_map(int input_map[MAX][MAX])
{
	cout << endl;
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			cout << input_map[xi][yi]<<" ";
		}
		cout << endl;
	}
	cout << endl;
}