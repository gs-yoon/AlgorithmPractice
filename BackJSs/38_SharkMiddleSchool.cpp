#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>

using namespace std;

#define BLACK -1
#define RAINBOW 0
#define EMPTY -2
// NORMAL > 0
#define DIRMAX 4
#define DEBUG 0

struct Group
{
	int id = 0;
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

void grouping(int x, int y, int color, Group* group_info, int map[20][20], bool visited[20][20], int group_map[20][20]);
void gravity__(int x, int y, int map[20][20]);
void gravity(int map[20][20]);
void rotate(int map[20][20]);
void copy_map(int dst[20][20], int src[20][20]);
void erase__(int x, int y, int group_id, int map[20][20], int group_map[20][20], bool visited[20][20], int* cnt);
bool erase(Group group_info, int map[20][20], int group_map[20][20]);
void print_map(int map[20][20], const char* msg);

int dx[] = { 0, -1, 0, 1 };
int dy[] = { -1, 0, 1, 0 };

int N = 0; // x < N , y < N
int M = 0; // color <= M
int g_score = 0;
int g_cnt = 0;

int main()
{

	int map[20][20] = { 0 };
	// get N, M
	cin >> N >> M;

	// get block map
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> map[xi][yi];
		}
	}
	// ** condition: **
	//black block, rainbow block, normal block(M color status)
	//all block status in a same group is rainbow or same color
	//all colors >= 0 and colors(>0) == other colors(>0)
	//rep block is normal and min(row) min(col)

	//** algo **
	bool playing = true;
	while (playing)
	{
		int group_map[20][20] = { 0 };

		vector<Group> group_vec;
		int ngid = 1;
		int max_num = 0;
		int max_idx =-1;

		print_map(map, "map");
		//grouping
		for(int ny =0; ny < N ; ny ++)
		{
			for (int nx = 0; nx < N; nx++)
			{
				if (group_map[nx][ny] == 0)
				{
					Group group_info;
					group_info.id = ngid;
					bool visited[20][20] = { 0 };
					grouping(nx, ny, map[nx][ny], &group_info, map, visited, group_map);
					if (group_info.num_of_blocks > 1)
					{
						group_vec.push_back(group_info);
						if (group_info.num_of_blocks > max_num)
						{
							max_num = group_info.num_of_blocks;
							max_idx = group_vec.size() - 1;
						}
						else if (group_info.num_of_blocks == max_num)
						{
							Group prev_max_group_info = group_vec[max_idx];

							if (group_info.num_of_rainbows > prev_max_group_info.num_of_rainbows)
							{
								max_idx = group_vec.size() - 1;
							}
							else if (group_info.num_of_rainbows == prev_max_group_info.num_of_rainbows)
							{
								if (group_info.std_y > prev_max_group_info.std_y)
								{
									max_idx = group_vec.size() - 1;
								}
								else if (group_info.std_y == prev_max_group_info.std_y)
								{
									if (group_info.std_x > prev_max_group_info.std_x)
									{
										max_idx = group_vec.size() - 1;
									}
								}
							}
						}
						ngid++;
					}
					else
					{
						group_info.num_of_blocks = 0;
					}
				}
			}
		}

		if (group_vec.size() > 0)
		{
			int max_group_map[20][20] = { 0 };
			Group max_group_info;

			max_group_info = group_vec[max_idx];
			max_group_info.id = 1;
			Group temp;
			temp.id = 1;
			bool visited[20][20] = { 0 };
			int std_x = max_group_info.std_x;
			int std_y = max_group_info.std_y;
			grouping(std_x, std_y, map[std_x][std_y], &temp, map, visited, max_group_map);
			print_map(max_group_map, "maximum group_map" );

			// delete max group :
			bool status = erase(max_group_info, map, max_group_map);
			if (status == true)
			{
				g_score += max_num * max_num;
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
		// if no group, playing is false
		else
		{
			playing = false;
		}
	}
	cout << g_score <<endl;
}

bool erase(Group group_info, int map[20][20], int group_map[20][20])
{
	bool visited[20][20] = { 0 };
	int cnt = 0;
	int x = group_info.std_x;
	int y = group_info.std_y;
	erase__(x, y, group_info.id, map, group_map ,visited, &cnt);
	if (cnt == group_info.num_of_blocks)
		return true;
	else
	{
		cout << "erase fail \n";
		cout << "num blocks = " << group_info.num_of_blocks << endl;
		cout << "cnt = " << cnt <<endl;
		return false;
	}
}

void erase__(int x, int y, int group_id, int map[20][20], int group_map[20][20] , bool visited[20][20], int * cnt)
{
	if (visited[x][y] == true)
		return;
	if (group_map[x][y] != group_id)
		return;

	visited[x][y] = true;
	group_map[x][y] = 0;
	map[x][y] = EMPTY;
	*cnt +=1;

	for (int dir = 0; dir < 4; dir++)
	{
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (0 <= nx && nx < N && 0 <= ny && ny < N)
			erase__(nx, ny, group_id, map, group_map, visited, cnt);
	}
}

void copy_map(int dst[20][20], int src[20][20])
{
	for (int i = 0; i < N; i++)
		//memcpy(dst[i], src[i], 20);
		copy(src[i], src[i]+20, dst[i]);
}

void rotate(int map[20][20])
{
	int tmap[20][20];
	float m = (float)(N-1) / 2.0;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			float mx = (float)x - m;
			float my = (float)y - m;
			int rx = ( 0 * mx + 1 * my) + m;
			int ry = (-1 * mx + 0 * my) + m;
			if (0 <= rx && rx < N && 0 <= ry && ry < N)
				tmap[rx][ry] = map[x][y];
			else
				printf("rotate error. rx = %d, ry = %d\n", rx,ry);
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

void gravity__(int x , int y , int map[20][20])
{
	int ny = y;
	int nx = x;
	int ty = y;
	bool condition = true;
	bool moved = false;
	while (condition)
	{
		if (ny+1 < N && map[nx][ny+1] == EMPTY)
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

// grouping : num of bolcoks, pos of std block, group index
void grouping(int x, int y, int color, Group* group_info, int map[20][20], bool visited[20][20], int group_map[20][20])
{
	if (visited[x][y] == 1)
		return;
	if (color < 0)
		return;
	visited[x][y] = 1;
	if( map[x][y] == RAINBOW || map[x][y] == color)
	{
		group_info->num_of_blocks++;
		group_map[x][y] = group_info->id;
		if (map[x][y] == RAINBOW)
		{
			group_info->num_of_rainbows++;
		}
		if (map[x][y] == color)
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
					group_info->std_y = y;
				}
			}
			else
			{
				//it's not std
			}
		}
	}
	else
	{
		return; 
	}

	for (int dir = 0; dir < DIRMAX; dir++)
	{
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (0 <= nx && nx < N && 0 <= ny && ny < N )
			grouping(nx, ny,color, group_info, map, visited, group_map);
	}

	if (group_info->num_of_blocks == 1)
	{
		group_map[x][y] = 0;
	}
	if (group_info->num_of_blocks  == group_info->num_of_rainbows)
	{
		group_map[x][y] = 0;
		group_info->num_of_blocks = 0;
	}

}

void print_map(int map[20][20], const char* msg)
{
#if DEBUG
	cout << msg << endl;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (map[x][y] == EMPTY)
				cout << ". ";
			else if (map[x][y] == BLACK)
				cout << "b ";
			else
				cout << map[x][y] << " ";
		}
		cout << endl;
	}
	cout << endl;
#endif
}