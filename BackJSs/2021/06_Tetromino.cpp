#include <iostream>

using namespace std;

#define MAX 500

enum driection_e
{
	LEFT =0,
	RIGHT,
	UP,
	DOWN
};

void make_tetromino_dfs(int* input_tetro_x, int* input_tetro_y, int dir, int index,int trial);
void print_map(int x_arr[], int y_arr[]);

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

int y_max;
int x_max;
int g_map[MAX][MAX] = {0};
int g_max = 0;

int main()
{
	cin >> y_max;
	cin >> x_max;
	
	for (int iy = 0; iy < y_max; iy++)
	{
		for (int ix = 0; ix < x_max; ix++)
		{
			cin >> g_map[ix][iy];
		}
	}

	int start_tetro_x[4] = { 99,99,99,99};
	int start_tetro_y[4] = { 99,99,99,99};
	
	for (int yi = 0; yi < y_max; yi += 1)
	{
		for (int xi = 0; xi < x_max; xi += 1)
		{
			start_tetro_x[0] = xi;
			start_tetro_y[0] = yi;
			make_tetromino_dfs(start_tetro_x, start_tetro_y, LEFT,0, 0);
			make_tetromino_dfs(start_tetro_x, start_tetro_y, RIGHT,0, 0);
			make_tetromino_dfs(start_tetro_x, start_tetro_y, UP,0, 0);
			make_tetromino_dfs(start_tetro_x, start_tetro_y, DOWN,0, 0);
		}
	}

	cout << g_max;
}

void copy_arr(int* output_tetro_x, int* output_tetro_y, int* input_tetro_x, int* input_tetro_y)
{
	for (int i = 0; i < 4; i++)
	{
		output_tetro_x[i] = input_tetro_x[i];
		output_tetro_y[i] = input_tetro_y[i];
	}
}

void make_tetromino_dfs(int* input_tetro_x, int *input_tetro_y, int dir, int index ,int trial)
{ 
	int last_x = input_tetro_x[index];
	int last_y = input_tetro_y[index];

	int local_tetro_x[4] = { 0 };
	int local_tetro_y[4] = { 0 };

	copy_arr(local_tetro_x, local_tetro_y, input_tetro_x, input_tetro_y);
	//memcpy(local_tetro_x, input_tetro_x, 4);
	//memcpy(local_tetro_y, input_tetro_y, 4);

	int next_x = last_x + dx[dir];
	int next_y = last_y + dy[dir];

	if (next_x < 0 || next_x >= x_max || next_y < 0 || next_y >= y_max)
	{
		return;
	}
	else
	{
		for (int tetro_idx = 0; tetro_idx <= trial ; tetro_idx++)
		{
			if (local_tetro_x[tetro_idx] == next_x && local_tetro_y[tetro_idx] == next_y)
			{
				return;
			}
		}
		
		trial++;
		local_tetro_x[trial] = next_x;
		local_tetro_y[trial] = next_y;
		//print_map(local_tetro_x, local_tetro_y);

		if (trial < 3)
		{
			for (int loop = 0; loop < trial; loop++)
			{
				make_tetromino_dfs(local_tetro_x, local_tetro_y, LEFT, loop ,trial);
				make_tetromino_dfs(local_tetro_x, local_tetro_y, RIGHT, loop ,trial);
				make_tetromino_dfs(local_tetro_x, local_tetro_y, UP,loop ,trial);
				make_tetromino_dfs(local_tetro_x, local_tetro_y, DOWN,loop ,trial);
			}
		}
		else if (trial == 3)
		{
			int sum = 0;
			for(int it = 0; it<4 ; it++ )
			{ 
				sum += g_map[ local_tetro_x[it] ][ local_tetro_y[it] ];
			}
			if (g_max < sum)
			{
				g_max = sum;
			}

			//print_map(local_tetro_x, local_tetro_y);
			return;
		}
		else
		{
			cout << "cirital_error";
			return;
		}
	}
}

void print_map(int x_arr[], int y_arr[])
{
	cout << endl;
	bool outable = true;
	for (int yi =0 ; yi < y_max; yi++)
	{
		for (int xi =0 ; xi < x_max; xi++)
		{
			//cout << g_map[xi][yi] << " ";
			outable = true;
			for (int arr_idx = 0; arr_idx < 4; arr_idx++)
			{
				if (x_arr[arr_idx] == xi && y_arr[arr_idx] == yi)
				{
					cout << "o" << " ";
					outable = false;
					break;
				}
			}
			if (outable == true)
			{
				cout << g_map[xi][yi] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}