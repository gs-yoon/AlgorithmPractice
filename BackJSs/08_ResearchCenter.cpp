#include <iostream>
#include <queue>

#define MAX 8
#define VIRUS 2
#define WALL 1
#define EMPTYSPACE 0

enum direction_e
{
	UP =0,
	DOWN,
	LEFT,
	RIGHT
};
struct pos
{
	int x = 0;
	int y = 0;
};
void chooseWall(int x_arr[], int y_arr[], int wall_num);
void spreadVirus(int x_arr[], int y_arr[]);
void print_map(int local_map[MAX][MAX]);

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
int x_max = 0;
int y_max = 0;
int g_max = 0;
int g_map[MAX][MAX];
int virus_x[10] = {99};
int virus_y[10] = {99};
int virus_num = 0;
using namespace std;

int main()
{
	cin >> y_max;
	cin >> x_max;
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			cin >> g_map[xi][yi];
			if (g_map[xi][yi] == VIRUS)
			{
				virus_x[virus_num] = xi;
				virus_y[virus_num] = yi;
				virus_num++;
			}
		}
	}
	int x_arr[4] = { -1 };
	int y_arr[4] = { 0 };

	chooseWall(x_arr, y_arr, 0);

	cout << g_max;
}

void chooseWall(int x_arr[], int y_arr[], int wall_num)
{
	wall_num++;
	int wall_idx= wall_num -1;
	int yi = y_arr[wall_idx];
	int xi = x_arr[wall_idx] + 1;


	for (yi; yi < y_max; yi++)
	{
		for (xi; xi < x_max; xi++)
		{
			if (g_map[xi][yi] == EMPTYSPACE)
			{
				x_arr[wall_num] = xi;
				y_arr[wall_num] = yi;
				if (wall_num < 3)
				{
					chooseWall(x_arr, y_arr, wall_num);
				}
				else
				{
					spreadVirus(x_arr, y_arr);
				}
			}
		}
		xi = 0;
	}
}

void spreadVirus(int x_arr[], int y_arr[])
{
	// make local map
	int local_map[MAX][MAX] = {99};
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			local_map[xi][yi] = g_map[xi][yi];
		}
	}
	for (int wall_num = 1; wall_num < 4; wall_num++)
	{
		local_map[x_arr[wall_num]][y_arr[wall_num]] = WALL;
	}

	//spreadAll
	for (int vnum = 0; vnum < virus_num; vnum++)
	{
		//spread one
		pos start_pos;
		start_pos.x = virus_x[vnum];
		start_pos.y = virus_y[vnum];

		queue<pos> virus_q;

		virus_q.push(start_pos);

		while (!virus_q.empty())
		{
			pos cur_pos = virus_q.front(); virus_q.pop();
			for (int dir =0 ; dir < 4; dir++)
			{
				pos next_pos;
				next_pos.x = cur_pos.x + dx[dir];
				next_pos.y = cur_pos.y + dy[dir];

				if (0 <= next_pos.x && next_pos.x < x_max && 0 <= next_pos.y && next_pos.y < y_max)
				{
					if (local_map[next_pos.x][next_pos.y] == EMPTYSPACE)
					{
						local_map[next_pos.x][next_pos.y] = VIRUS;
						virus_q.push(next_pos);
					}
				}
			}
		}
	}
	//print_map(local_map);

	//calculate result
	int sum = 0;
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			if (local_map[xi][yi] == EMPTYSPACE)
			{
				sum++;
			}
		}
	}
	if (g_max < sum)
	{
		g_max = sum;
	}
}

void print_map(int local_map[MAX][MAX])
{
	cout << endl;
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			cout << local_map[xi][yi] << " ";
		}
		cout << endl;
	}
	cout << endl;
}