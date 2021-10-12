#include <iostream>

using namespace std;

#define EMPTYSPACE 0
#define WALL 1
#define VISITED 2
#define MAX 50

enum direction_e
{
	LEFT = 0,
	DOWN,
	RIGHT,
	UP
};
enum direction_input
{
	I_UP=0,
	I_RIGHT,
	I_DOWN,
	I_LEFT
};
int turnLeft(int cur_dir);
void print_map(int robot_x, int robot_y);

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
int y_max= 0;
int x_max = 0;
int g_map[MAX][MAX] = {0};
int initial_x = 0;
int initial_y = 0;
int initial_dir = 0;

int main()
{
	cin >> y_max;
	cin >> x_max;
	cin >> initial_y;
	cin >> initial_x;
	cin >> initial_dir;
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			cin >> g_map[xi][yi];
		}
	}

	switch (initial_dir)
	{
		case I_UP:
			initial_dir = UP;
			break;
		case I_DOWN:
			initial_dir = DOWN;
			break;
		case I_LEFT:
			initial_dir = LEFT;
			break;
		case I_RIGHT:
			initial_dir = RIGHT;
			break;
		default:
			break;
	}

	bool keep_going = true;
	int dir = initial_dir;
	int cur_x = initial_x;
	int cur_y = initial_y;
	int loop = 0;

	g_map[cur_x][cur_y] = VISITED;

	print_map(cur_x, cur_y);
	while (keep_going)
	{
		if (loop < 4)
		{
			int next_dir = turnLeft(dir);
			int next_x = cur_x + dx[next_dir];
			int next_y = cur_y + dy[next_dir];
			if (g_map[next_x][next_y] == EMPTYSPACE)
			{
				dir = next_dir;
				cur_x = next_x;
				cur_y = next_y;
				g_map[cur_x][cur_y] = VISITED;
				loop = 0;
				print_map(cur_x, cur_y);
			}
			else
			{
				dir = next_dir;
				loop++;
			}
		}
		else
		{
			loop = 0;
			int next_dir = turnLeft(dir);
			next_dir = turnLeft(next_dir);

			int next_x = cur_x + dx[next_dir];
			int next_y = cur_y + dy[next_dir];

			if (g_map[next_x][next_y] != WALL)
			{
				cur_x = next_x;
				cur_y = next_y;
				print_map(cur_x, cur_y);
			}
			else
			{
				keep_going = false;
			}
		}
	}

	int sum = 0;
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			if (g_map[xi][yi] == VISITED)
			{
				sum++;
			}
		}
	}
	cout << sum;
}

int turnLeft(int cur_dir)
{
	cur_dir++;
	return cur_dir % 4;
}

void print_map(int robot_x, int robot_y)
{
	cout << endl;
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			if(robot_x == xi && robot_y == yi)
			{
				cout << "r" << " ";
			}
			else
			{
				cout << g_map[xi][yi] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
