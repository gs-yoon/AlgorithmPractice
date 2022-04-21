#include <iostream>
#include <vector>

using namespace std;

struct Fish
{
	int x;
	int y;
	int size;
};

void hunt_fish__(int x, int y, Fish* shark, Fish* hunted_fish, int map[20][20], bool visited[20][20], int* fin_time, int time);
int hunt_fish(Fish* shark, int map[20][20]);

enum DIR
{
	UP = 0,
	LEFT,
	DOWN,
	RIGHT
};

int dx[] = { 0, -1, 0, 1 };
int dy[] = { -1, 0, 1 ,0 };

int map[20][20] = { 0 };
int N = 0;
Fish shark;

int main()
{
	cin >> N;

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> map[x][y];
			if (map[x][y] == 9)
			{
				shark.x = x;
				shark.y = y;
				map[x][y] = 0;
			}
		}
	}

	shark.size = 2;

	bool condition = true;
	int elapesed_time = 0;
	while (condition)
	{
		int time = 0;
		time = hunt_fish(&shark, map);

		if (time > 0)
		{
			elapesed_time += time;
		}
		else
		{
			condition = false;
		}
	}
	cout << elapesed_time;
	return 0;
}


int hunt_fish(Fish* shark, int map[20][20])
{
	int fin_time = 0;
	bool visited[20][20] = { 0 };
	Fish hunted_fish;
	hunted_fish.x = 99;
	hunted_fish.y = 99;
	hunted_fish.size = -1;

	hunt_fish__(shark->x, shark->y, shark, &hunted_fish, map, visited, &fin_time, -1);
	return fin_time;
}

void hunt_fish__(int x, int y, Fish* shark, Fish* hunted_fish, int map[20][20], bool visited[20][20], int* fin_time, int time)
{
	if (visited[x][y] != 0)
	{
		cout << "dfd" << endl;
		return;
	}
	if (map[x][y] > shark->size)
	{
		cout << "dfd" << endl;
		return;
	}
	visited[x][y] = 1;
	time++;

	if (time > *fin_time)
		return;

	//found
	cout << "int" << endl;
	if (0 < map[x][y] && map[x][y] < shark->size)
	{
		cout << "dddd" << endl;
		if (hunted_fish->size <= 0)
		{
			hunted_fish->size = map[x][y];
			hunted_fish->x = x;
			hunted_fish->y = y;
			*fin_time = time;
		}
		else
		{
			if (y < hunted_fish->y)
			{
				hunted_fish->x = x;
				hunted_fish->y = y;
				hunted_fish->size = map[x][y];
			}
			else if (y == hunted_fish->y)
			{
				if (x < hunted_fish->x)
				{
					hunted_fish->x = x;
					hunted_fish->y = y;
					hunted_fish->size = map[x][y];
				}
			}
			if (time < *fin_time)
				cout << "time error \n";
		}
	}
	//keep going
	else if (map[x][y] == shark->size || map[x][y] == 0)
	{
		cout << "int" << endl;
		for (int dir = 0; dir < 4; dir++)
		{
			cout << "int" << endl;
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if( 0<= nx && nx <N && 0<=ny && ny <N)
				hunt_fish__(nx, ny, shark, hunted_fish, map, visited, fin_time, time);
		}
	}
	else
	{
		cout << "find algo error \n";
	}
}