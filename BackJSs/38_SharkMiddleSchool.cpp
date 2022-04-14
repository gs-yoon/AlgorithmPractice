#include<iostream>
#include<vector>

using namespace std;

#define BLACK -1
#define RAINBOW 0
// NORMAL > 0

struct Group
{
	int group_num = 0;
	int std_x = 0;
	int std_y = 0;
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
vector<Group> group_vec;

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

// grouping : num of bolcoks, pos of std block, group index
void grouping(int nx, int ny, int group_num, int** map, int** visited)
{

	x
	visited[nx][ny] = group_num;

	

}



// rotate
// gravity