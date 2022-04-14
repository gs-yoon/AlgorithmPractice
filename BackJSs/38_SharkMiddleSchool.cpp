#include<iostream>
#include<vector>

using namespace std;

#define BLACK -1
#define RAINBOW 0
#define EMPTY -2
// NORMAL > 0
#define DIRMAX 8

struct Group
{
	int group_id = 0;
	int std_x = 99;
	int std_y = 99;
	int num_of_bolcks = 0;
};

enum DIR
{
	UU = 0,
	RU,
	RR,
	RD,
	DD,
	LD,
	LL,
	LU
};

int dx[] = { 0,  1, 1, 1, 0, -1, -1, -1};
int dy[] = {-1, -1, 0, 1, 1,  1,  0, -1};

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
		bool visited[20][20] = { 0 };
		int group_map[20][20] = { 0 };

		vector<Group> group_vec;
		Group group_info;
		int max_num = 0;
		int max_idx =-1;

		for(int ny =0; ny < N ; ny ++)
		{
			for (int nx = 0; nx < N; nx++)
			{
				grouping(nx,ny, map[nx][ny], &group_info, map, visited, group_map);
				if (group_info.num_of_bolcks > 1)
				{
					group_vec.push_back(group_info);
					if (group_info.num_of_bolcks > max_num)
					{
						max_num = group_info.num_of_bolcks;
						max_idx = group_vec.size() - 1;
					}
				}
			}
		}
		// find max group :
		// find max size group
			// find max rainbow num of group
				// find max row
					//find max col
		// delete found group
			// add score (deleted_size) ^ 2

		// apply gravitiy

		// rotate 90
		// apply gravity

		// if no group, playing is false
	}
}

void erase(int x, int y)
{
	bool visited[20][20] = { 0 };
	int cnt = 0;

	erase__(x, y, visited, &cnt);

}

void erase__(int x, int y, bool visited[20][20], int * cnt)
{

}

// grouping : num of bolcoks, pos of std block, group index
void grouping(int x, int y, int color, Group* group_info, int map[20][20], bool visited[20][20], int group_map[20][20])
{
	if (visited[x][y] == 1)
		return;

	visited[x][y] = 1;
	if( map[x][y] == RAINBOW || map[x][y] == color)
	{
		group_info->num_of_bolcks++;
		group_info->group_id;
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

			}
		}
	}

	for (int dir = 0; dir < DIRMAX; dir++)
	{
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		grouping(nx, ny,color, group_info ,map,visited,group_map);
	}
}



// rotate
// gravity