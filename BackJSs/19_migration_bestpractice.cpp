#include <iostream>

using namespace std;

enum direction_e
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN

};

void print_map(int input_map[50][50]);
void move(int start_X, int start_Y, int avg);
void find_alias(int start_X, int start_Y, int last_num);
void reset_visited();

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

int N;
int L;
int R;
int map[50][50];
int visited[50][50];
int g_cnt = 0;
int g_sum = 0;
int main()
{
	cin >> N >> L >> R;

	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> map[xi][yi];
		}
	}

	bool moving_flag = true;
	int trial = 0;
	while (moving_flag)
	{
		moving_flag = false;
		reset_visited();
		for (int yi = 0; yi < N; yi++)
		{
			for (int xi = 0; xi < N; xi++)
			{
				g_cnt = 0;
				g_sum = 0;

				find_alias(xi, yi, -1);
				if (g_cnt <= 1)
				{
					moving_flag |= false;
					visited[xi][yi] = 2;
				}
				else
				{
					moving_flag |= true;
					move(xi, yi, g_sum / g_cnt);
					print_map(visited);
					print_map(map);
				}

			}
		}
		if(moving_flag == true)
			trial++;
	}
	cout << trial;
}

void reset_visited()
{
	for (int yi = 0; yi < N; yi++)
		for (int xi = 0; xi < N; xi++)
			visited[xi][yi] = 0;
}

void find_alias(int start_X, int start_Y, int last_num)
{
	if (visited[start_X][start_Y] != 0)
		return ;
	if (start_X < 0 || start_X >= N || start_Y < 0 || start_Y >= N)
		return ;

	int diff = abs(map[start_X][start_Y] - last_num);
	if ((L <= diff && diff <= R) || last_num<0)
	{
		g_sum += map[start_X][start_Y];
		g_cnt++;
		visited[start_X][start_Y] = 1;
		for (int dir = 0; dir < 4; dir++)
		{
			int next_X = start_X + dx[dir];
			int next_Y = start_Y + dy[dir];
			find_alias(next_X, next_Y, map[start_X][start_Y]);
		}
	}
}


void move(int start_X, int start_Y, int avg)
{
	if (visited[start_X][start_Y] != 1)
		return;
	if (start_X < 0 || start_X >= N || start_Y < 0 || start_Y >= N)
		return;

	visited[start_X][start_Y] = 2;
	map[start_X][start_Y] = avg;
	for (int dir = 0; dir < 4; dir++)
	{
		int next_X = start_X + dx[dir];
		int next_Y = start_Y + dy[dir];
		move(next_X, next_Y, avg);
	}
}

void print_map(int input_map[50][50])
{
	cout << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cout << input_map[xi][yi] << " ";
		}
		cout << endl;
	}
	cout << endl;
}