//01_EscapingBead

#include <iostream>
#include <utility>
#include <vector>

using namespace std;



#define MAX 10
#define RED 0
#define BLUE 1

enum direction
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

enum status
{
	DEAD = 0,
	NM,
	FIND
};

struct pos
{
	int row = 0;
	int col = 0;
};

int calculation();

void shake_recursion(int dir, int num, pos local_pos[2], vector<pair<pos, pos>> visiteds);
bool is_visited(pos local_pos[2], vector<pair<pos, pos>> visited_vector);
int reverse_dir(int  dir);

int shake_atom(int dir, pos local_pose[2]);

int find_first(int dir, pos local_pose[2]);

void print_map(pos l[]);

int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

int g_num = 11;

int row_max = 0;
int col_max = 0;
char map[MAX][MAX] = { 0 };
pos g_ball_pos[2];
pos g_goal_pos;

int main()
{
	//cout << "start" << endl;
	cin >> row_max;
	cin >> col_max;
	for (int row = 0; row < row_max; row++)
	{
		for (int col = 0; col < col_max; col++)
		{
			cin >> map[row][col];
			if (map[row][col] == 'R')
			{
				g_ball_pos[RED].row = row;
				g_ball_pos[RED].col = col;
				map[row][col] = '.';
			}

			else if (map[row][col] == 'B')
			{
				g_ball_pos[BLUE].row = row;
				g_ball_pos[BLUE].col = col;
				map[row][col] = '.';
			}

			else if (map[row][col] == 'O')
			{
				g_goal_pos.row = row;
				g_goal_pos.col = col;
			}
		}
	}

	int result;
	result = calculation();
	cout << result << endl;

	return 0;
}

int find_first(int dir, pos local_pose[2])
{
	int first_id = 0;
	if (dir == UP)
	{
		if (local_pose[RED].row <= local_pose[BLUE].row)
			first_id = RED;
		else
			first_id = BLUE;
	}

	else if (dir == DOWN)
	{
		if (local_pose[RED].row >= local_pose[BLUE].row)
			first_id = RED;
		else
			first_id = BLUE;
	}

	else if (dir == LEFT)
	{
		if (local_pose[RED].col <= local_pose[BLUE].col)
			first_id = RED;
		else
			first_id = BLUE;
	}

	else
	{
		if (local_pose[RED].col >= local_pose[BLUE].col)
			first_id = RED;
		else
			first_id = BLUE;
	}

	return first_id;
}

int shake_atom(int dir, pos* local_pose)
{
	//find first moving ball
	int result = DEAD;
	int first_id = 0;

	first_id = find_first(dir, local_pose);

	// ball move
	for (int ball_loop= 0; ball_loop < 2; ball_loop++)
	{
		int moving = first_id;
		if (ball_loop > 0)
			moving = !first_id;

		//go to
		while (true) 
		{
			int next_row;
			int next_col;

			next_row = local_pose[moving].row + dr[dir];
			next_col = local_pose[moving].col + dc[dir];
			
			//obsatcle?
			if (map[next_row][next_col] != '#' &&  
				!(local_pose[!moving].row == next_row && local_pose[!moving].col == next_col)
				)
			{
				local_pose[moving].row = next_row;
				local_pose[moving].col = next_col;
				if(result !=FIND)
					result = NM;
			}

			else
			{
				break;
			}

			//success?
			if (map[next_row][next_col] == 'O')
			{
				if (moving == RED)
				{
					result = FIND;
					local_pose[moving].row = 99;
					local_pose[moving].col = 99;
					break;
				}
				else
				{
					result = DEAD;
					return result;
				}
			}

		}
	}
	return result;
}

int reverse_dir(int  dir)
{
	int result = 0;
	if (dir == LEFT)
	{
		result = RIGHT;
	}
	else if (dir == RIGHT)
	{
		result = LEFT;
	}
	else if (dir == UP)
	{
		result = DOWN;
	}
	else
	{
		result = UP;
	}
	return result;
}

bool is_visited(pos local_pos[2], vector<pair<pos, pos>> visited_vector)
{
	int len = visited_vector.size();
	pos visited_pos[2];
	bool visited = false;
 
	for (int i = 0; i < len; i++)
	{
		visited_pos[RED] = visited_vector.at(i).first;
		visited_pos[BLUE] = visited_vector.at(i).second;

		if (visited_pos[RED].row == local_pos[RED].row
			&& visited_pos[RED].col == local_pos[RED].col
			&& visited_pos[BLUE].row == local_pos[BLUE].row
			&& visited_pos[BLUE].col == local_pos[BLUE].col)
		{
			visited = true;
		}
	}
	return visited;
}

void shake_recursion(int dir, int num, pos* input_pos, vector<pair<pos, pos>> visited_vector)
{
	pos local_pos[2];
	pair<pos, pos> visited;
	visited.first = input_pos[RED];
	visited.second = input_pos[BLUE];
	visited_vector.push_back(visited);

	local_pos[RED] = input_pos[RED];
	local_pos[BLUE] = input_pos[BLUE];

	int result;

	result = shake_atom(dir, local_pos);
	num++;

	// die condition without same direction
	if (result == DEAD)
		return;
	else if (result == FIND)
	{
		if (g_num > num)
			g_num = num;
		/*
		cout << num << endl;
		cout << "dir : " << dir << endl;
		print_map(local_pos);
		*/
		return;
	}
	else if (is_visited(local_pos, visited_vector))
	{
		return;
	}
	else if (num > g_num)
	{
		return;
	}
	else
	{
		//cout << num << endl;
		//cout << "dir : " << dir << endl;
		//print_map(local_pos);
		for (int next_dir = 0; next_dir < 4; next_dir++)
		{
			if(next_dir != dir && next_dir != reverse_dir(dir))
				shake_recursion(next_dir, num, local_pos, visited_vector);
		}
	}
}

int calculation()
{
	pos local_pos[2];

	local_pos[RED].row = g_ball_pos[RED].row;
	local_pos[RED].col = g_ball_pos[RED].col;
	local_pos[BLUE].row = g_ball_pos[BLUE].row;
	local_pos[BLUE].col = g_ball_pos[BLUE].col;

	vector<pair<pos,pos>> visited_vector;

	shake_recursion(LEFT, 0, local_pos, visited_vector);
	shake_recursion(RIGHT, 0, local_pos, visited_vector);
	shake_recursion(UP, 0, local_pos, visited_vector);
	shake_recursion(DOWN, 0, local_pos, visited_vector);

	if (g_num < 11)
		return g_num;
	else
		return -1;
}

void print_map(pos local_pose[2])
{
	for (int i = 0; i < row_max; i++)
	{
		for (int j = 0; j < col_max; j++)
		{
			if (local_pose[RED].row == i && local_pose[RED].col == j)
				cout << 'R';
			else if (local_pose[BLUE].row == i && local_pose[BLUE].col == j)
				cout << 'B';
			else
				cout << map[i][j];
		}
		cout << endl;
	}
	cout << endl;
}