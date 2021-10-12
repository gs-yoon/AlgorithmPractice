#include <iostream>
#include <utility>

using namespace std;

enum direction_e
{
	UP=0,
	DOWN,
	RIGHT,
	LEFT
};

struct shark
{
	int x = 0;
	int y = 0;
	int vel = 0;
	int dir = 0;
	int size = 0;
};

void move_shark();
void fishing(int x);
void print_map();
inline int revesers_dir(int dir)
{
	if (dir == UP)
		return DOWN;
	else if (dir == DOWN)
		return UP;
	else if (dir == RIGHT)
		return LEFT;
	else if (dir == LEFT)
		return RIGHT;
}


int dx[] = { 0,0,1,-1 };
int dy[] = { -1,1,0,0 };

int x_max;
int y_max;
int shark_total;
int got_shark_num = 0;

shark* shark_arr;
pair<int, shark*> map[100][100];
int main()
{
	for (int yi = 0; yi < y_max; yi++)
		for (int xi = 0; xi < x_max; xi++)
			map[xi][yi].first = 0;


	cin >> y_max >> x_max >> shark_total;
	shark_arr = new shark[shark_total];

	for (int i = 0; i < shark_total; i++)
	{
		cin >> shark_arr[i].y;
		cin >> shark_arr[i].x;
		cin >> shark_arr[i].vel;
		cin >> shark_arr[i].dir;
		cin >> shark_arr[i].size;

		shark_arr[i].y--;
		shark_arr[i].x--;
		shark_arr[i].dir--;

		map[shark_arr[i].x][shark_arr[i].y].first = shark_arr[i].size;

		map[shark_arr[i].x][shark_arr[i].y].second = shark_arr + i;
	}

	if (shark_total == 0)
	{
		cout << 0;
		return 0;
	}

	for (int fisher_x = 0; fisher_x < x_max; fisher_x++)
	{
		fishing(fisher_x);
		move_shark();
		//print_map();
	}
	cout << got_shark_num;
}


void fishing(int x)
{
	for (int yi = 0; yi < y_max; yi++)
	{
		if (map[x][yi].first > 0)
		{
			//add
			got_shark_num += map[x][yi].first;
			//delete in map
			map[x][yi].first = 0;
			//delete mark in array
			map[x][yi].second->size = -1;

			break;
		}
	}
}

void move_shark()
{
	bool visited[100][100] = { 0 };
	for (int i = 0; i < shark_total; i < i++)
	{
		//only live shark
		if (shark_arr[i].size > 0)
		{
			//delete in map
			if (visited[shark_arr[i].x][shark_arr[i].y] == 0)
			{
				map[shark_arr[i].x][shark_arr[i].y].first = 0;
				map[shark_arr[i].x][shark_arr[i].y].second = nullptr;
			}
			//move
			int nx = shark_arr[i].x + dx[shark_arr[i].dir] * shark_arr[i].vel;
			int ny = shark_arr[i].y + dy[shark_arr[i].dir] * shark_arr[i].vel;

			while (nx < 0 || nx >= x_max)
			{
				if (nx < 0)
				{
					nx = nx * -1;
					shark_arr[i].dir = revesers_dir(shark_arr[i].dir);
				}
				else if (nx >= x_max)
				{
					//max idx - diff
					nx = (x_max - 1) + (x_max - 1 - nx);
					shark_arr[i].dir = revesers_dir(shark_arr[i].dir);
				}
			}
			while (ny < 0 || ny >= y_max)
			{
				if (ny < 0)
				{
					ny = ny * -1;
					shark_arr[i].dir = revesers_dir(shark_arr[i].dir);
				}
				else if (ny >= y_max)
				{
					//max idx - diff
					ny = (y_max - 1) + (y_max - 1 - ny);
					shark_arr[i].dir = revesers_dir(shark_arr[i].dir);
				}
			}
			//cmp with visited
			if (visited[nx][ny] == 0)
			{
				shark_arr[i].x = nx;
				shark_arr[i].y = ny;
				
				//mark in map
				map[nx][ny].first = shark_arr[i].size;
				map[nx][ny].second = shark_arr + i;

				visited[nx][ny] = 1;
			}
			else
			{
				//cur shar dead
				if (map[nx][ny].first > shark_arr[i].size)
				{
					shark_arr[i].size = -1;
				}
				else
				{
					//die org shark
					map[nx][ny].second->size = -1;

					shark_arr[i].x = nx;
					shark_arr[i].y = ny;

					//mark in map
					map[nx][ny].first = shark_arr[i].size;
					map[nx][ny].second = shark_arr + i;
				}
			}
		}
	}
}

void print_map()
{
	cout << endl;
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			cout << map[xi][yi].first << " ";
		}
		cout << endl;
	}
	cout << endl;
}