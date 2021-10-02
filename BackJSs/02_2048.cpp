#include <iostream>

using namespace std;

#define MAX 20

long int g_input_map[MAX][MAX] = { 0 };
int N = 0;

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

enum direction
{
	LEFT =0,
	RIGHT,
	UP,
	DOWN,
};

long int g_max = 0;

void copy_map(long int input[MAX][MAX], long int target[MAX][MAX]);
int move_atom(int dir, long int map[MAX][MAX], bool visited[MAX][MAX], int x, int y);
int shake_atom(int dir, long int map[MAX][MAX]);
void print_map(long int map[MAX][MAX]);
long int calc_map(long int map[MAX][MAX]);
void shake_recursion(int dir, long int map[MAX][MAX], int trial);

int main()
{
	cin >> N;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
			cin >> g_input_map[x][y];

	//int tmap[MAX][MAX] = {0};
	//copy_map(g_input_map, tmap);
	//cout << shake_atom(UP, tmap) << endl;;
	//print_map(tmap);


	shake_recursion(LEFT, g_input_map, 0);
	shake_recursion(RIGHT, g_input_map, 0);
	shake_recursion(UP, g_input_map, 0);
	shake_recursion(DOWN, g_input_map, 0);

	cout << g_max;
}

void copy_map(long int input[MAX][MAX], long int target[MAX][MAX])
{
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
			target[x][y] = input[x][y];
}

void print_map(long int map[MAX][MAX])
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cout << map[x][y] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int move_atom(int dir, long int map[MAX][MAX], bool visited[MAX][MAX], int x, int y)
{
	long int cur_num = map[x][y];
	map[x][y] = 0;
	int success = 0;
	while (true)
	{
		int next_x = x + dx[dir];
		int next_y = y + dy[dir];

		if (next_x <0 || next_x >= N || next_y<0 || next_y >= N)
			break;

		if (map[next_x][next_y] == 0)
		{
			x = next_x;
			y = next_y;
			success = 1;
		}
		else
		{
			if (cur_num == map[next_x][next_y] && visited[next_x][next_y] != 1 && visited[x][y] != 1)
			{
				cur_num += map[next_x][next_y];
				visited[next_x][next_y] = 1;
				x = next_x;
				y = next_y;
				success = 1;
			}
			else
			{
				break;
			}
		}
	}
	map[x][y] = cur_num;
	return success;
}

int shake_atom(int dir, long int map[MAX][MAX])
{
	int success = 0;
	bool visited[MAX][MAX] = { 0 };
	// LEFT
	if (dir == LEFT)
	{
		for (int search_y = 0; search_y < N; search_y++)
		{
			for (int search_x = 0; search_x < N; search_x++)
			{
				if (map[search_x][search_y] != 0)
				{
					success |= move_atom(LEFT, map, visited,  search_x, search_y);
				}
			}
		}
	}

	// RIGHT
	if (dir == RIGHT)
	{
		for (int search_y = 0; search_y < N; search_y++)
		{
			for (int search_x = N - 1; search_x >= 0; search_x--)
			{
				if (map[search_x][search_y] != 0)
					success |= move_atom(RIGHT, map, visited, search_x, search_y);
			}
		}
	}

	// UP
	if (dir == UP)
	{
		for (int search_x = 0; search_x < N; search_x++)
		{
			for (int search_y = 0; search_y < N; search_y++)
			{
				if (map[search_x][search_y] != 0)
					success |= move_atom(UP, map, visited, search_x, search_y);
			}
		}
	}

	// DOWN
	if (dir == DOWN)
	{
		for (int search_x = 0; search_x < N; search_x++)
		{
			for (int search_y = N-1; search_y >= 0; search_y--)
			{
				if (map[search_x][search_y] != 0)
					success |= move_atom(DOWN, map, visited, search_x, search_y);
			}
		}
	}

	return success;
}


void shake_recursion(int dir, long int map[MAX][MAX], int trial)
{
	long int local_map[MAX][MAX];
	long int local_max = 0;
	copy_map(map, local_map);

	trial++;
	int success = 0;
	success = shake_atom(dir, local_map);
	if (success == 1 && trial < 5)
	{
		//cout << endl << "trial : " << trial << endl;
		//print_map(local_map);
		for (int next_dir = 0; next_dir < 4; next_dir++)
		{
			shake_recursion(next_dir, local_map, trial);
		}
	}

	else
	{
		local_max = calc_map(local_map);
		if (g_max < local_max)
		{
			g_max = local_max;
			return;
		}
	}
	return;
}

long int calc_map(long int map[MAX][MAX])
{
	long int local_max = 0;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (local_max < map[x][y])
				local_max = map[x][y];
		}
	}
	return local_max;
}