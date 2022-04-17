#include <iostream>
#include <algorithm>

using namespace std;

#define BLACK -1
#define RAINBOW 0
#define EMPTY -2

#define DEBUG 1

void print_map(int in_map[20][20], const char* msg);
void gravity__(int x, int y, int map[20][20]);
void gravity(int map[20][20]);
void rotate(int map[20][20]);
void copy_map(int dst[20][20], int src[20][20]);
void erase__(int x, int y, int map[20][20], int group_map[20][20], bool visited[20][20], int* cnt);
bool erase(Group group_info, int map[20][20], int group_map[20][20]);
void grouping__(int x, int  y, int color, Group* group_info, int map[20][20], bool visited[20][20], int group_map[20][20]);
Group grouping(int x, int y, int color, int map[20][20], int group_map[20][20]);

struct Group
{
	int std_x = 99;
	int std_y = 99;
	int num_of_blocks = 0;
	int num_of_rainbows = 0;
};

enum DIR
{
	UP =0,
	LEFT,
	DOWN,
	RIGHT
};

int dx[] = { 0,-1,0,1 };
int dy[] = { -1,0,1,0 };

int g_score = 0;
int map[20][20] = { 0 };
int N, M;
int main()
{
	cin >> N >> M;

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> map[x][y];
		}
	}
	
	bool playing = true;
	while (playing)
	{
		Group max_group_info;
		max_group_info.std_x = 0;
		max_group_info.std_y = 0;
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				Group group_info;
				if (map[x][y] > 0)
				{
					bool group_map[20][20] = { 0 };
					group_info = grouping(x, y, map[x][y], map, group_map);
					if (max_group_info.num_of_blocks < group_info.num_of_blocks)
					{
						max_group_info = group_info;
					}
					else if (max_group_info.num_of_blocks == group_info.num_of_blocks)
					{
						if (max_group_info.num_of_rainbows > group_info.num_of_rainbows)
						{
							max_group_info = group_info;
						}
						else if (max_group_info.num_of_rainbows == group_info.num_of_rainbows)
						{
							if (max_group_info.std_y < group_info.std_y)
							{
								max_group_info = group_info;
							}
							else if (max_group_info.std_y == group_info.std_y)
							{
								if (max_group_info.std_x < group_info.std_x)
								{
									max_group_info = group_info;
								}
							}
						}
					}
				}
			}
		}

		if (max_group_info.num_of_blocks > 1)
		{
			int max_group_map[20][20] = { 0 };
			int std_x = max_group_info.std_x;
			int std_y = max_group_info.std_y;
			grouping(std_x, std_y, map[std_x][std_y], map, max_group_map);
			print_map(max_group_map, "maximum group_map");

			// delete max group :
			bool status = erase(max_group_info, map, max_group_map);
			if (status == true)
			{
				g_score += max_group_info.num_of_blocks * max_group_info.num_of_blocks;
			}
			else
				printf("erase fail\n");

			print_map(map, "after erase");
			// gravitiy
			gravity(map);
			print_map(map, "after gravity");
			// rotate 90
			rotate(map);
			print_map(map, "after rotate");
			// apply gravity
			gravity(map);
			print_map(map, "after gravity");
		}
		else
		{
			playing = false;
		}
	}
	cout << g_score;

}

Group grouping(int x, int y, int color, int map[20][20], int group_map[20][20])
{
	bool visited[20][20] = {0};
	Group group_info;
	
	grouping__(x, y, color, &group_info, map, visited, group_map);

	return group_info;
}

void grouping__(int x, int  y, int color, Group* group_info, int map[20][20], bool visited[20][20], int group_map[20][20])
{
	if (visited[x][y] == true)
		return;
	
	visited[x][y] = true;
	if (map[x][y] >= 0)
	{
		group_map[x][y] = 1;
		group_info->num_of_blocks++;
		if (map[x][y] > 0)
		{
			if (y < group_info->std_y)
			{
				group_info->std_x = x;
				group_info->std_y = y;
			}
			else if (y == group_info->std_y)
			{
				if (x < group_info->std_x)
				{
					group_info->std_x = x;
				}
				else if ( x == group_info -> std_x)
				{
					cout << "grouping__ same block error " << endl;
				}
			}
		}
		else
		{
			group_info->num_of_rainbows++;
		}

		for (int dir = 0; dir < 4; dir++)
		{
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (0<= nx && nx <N && 0<= ny && ny < N)
				grouping__(nx, ny, color, group_info, map, visited, group_map);
		}
	}
}

bool erase(Group group_info, int map[20][20], int group_map[20][20])
{
	bool visited[20][20] = { 0 };
	int cnt = 0;
	int x = group_info.std_x;
	int y = group_info.std_y;
	erase__(x, y, map, group_map, visited, &cnt);
	if (cnt == group_info.num_of_blocks)
		return true;
	else
	{
		cout << "erase fail \n";
		cout << "num blocks = " << group_info.num_of_blocks << endl;
		cout << "cnt = " << cnt << endl;
		return false;
	}
}

void erase__(int x, int y, int map[20][20], int group_map[20][20], bool visited[20][20], int* cnt)
{
	if (visited[x][y] == true)
		return;

	visited[x][y] = true;
	group_map[x][y] = 0;
	map[x][y] = EMPTY;
	*cnt += 1;

	for (int dir = 0; dir < 4; dir++)
	{
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (0 <= nx && nx < N && 0 <= ny && ny < N)
			erase__(nx, ny, map, group_map, visited, cnt);
	}
}

void copy_map(int dst[20][20], int src[20][20])
{
	for (int i = 0; i < N; i++)
		copy(src[i], src[i] + 20, dst[i]);
}

void rotate(int map[20][20])
{
	int tmap[20][20];
	float m = (float)(N - 1) / 2.0;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			float mx = (float)x - m;
			float my = (float)y - m;
			int rx = (0 * mx + 1 * my) + m;
			int ry = (-1 * mx + 0 * my) + m;
			if (0 <= rx && rx < N && 0 <= ry && ry < N)
				tmap[rx][ry] = map[x][y];
			else
				printf("rotate error. rx = %d, ry = %d\n", rx, ry);
		}
	}
	copy_map(map, tmap);
}


void gravity(int map[20][20])
{
	for (int y = N - 1; y >= 0; y--)
	{
		for (int x = N - 1; x >= 0; x--)
		{
			if (map[x][y] >= 0) // not black, not empty
			{
				gravity__(x, y, map);
			}
		}
	}
}

void gravity__(int x, int y, int map[20][20])
{
	int ny = y;
	int nx = x;
	int ty = y;
	bool condition = true;
	bool moved = false;
	while (condition)
	{
		if (ny + 1 < N && map[nx][ny + 1] == EMPTY)
		{
			ny++;
			condition = true;
			moved = true;
		}
		else
		{
			condition = false;
		}
	}
	if (moved)
	{
		map[nx][ny] = map[x][y];
		map[x][y] = EMPTY;
	}
}

void print_map(int in_map[20][20], const char* msg)
{
#if DEBUG
	cout << msg << endl;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (map[x][y] == EMPTY)
			{
				cout << ". ";
			}
			else if (map[x][y] == BLACK)
			{
				cout << "B ";
			}
			else
			{
				cout << map[x][y] << " ";
			}

		}
		cout << endl;
	}
#endif
}