//01_EscapingBead

#include <iostream>
#include <utility>
#include <vector>
#include <queue>

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

int shake_recursion();
bool is_visited(pos local_pos[2], vector<pair<pos, pos>> visited_vector);
int reverse_dir(int  dir);

int shake_atom(int dir, pos local_pose[2]);

int find_first(int dir, pos local_pose[2]);

void print_map(pos l[], int num);

int dr[4] = { 0, 0, -1, 1 };
int dc[4] = { -1, 1, 0, 0 };

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
	result = shake_recursion();
	if (result > 10)
		result = -1;
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
	for (int ball_loop = 0; ball_loop < 2; ball_loop++)
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
				if (result != FIND)
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
	else if (dir == DOWN)
	{
		result = UP;
	}
	else
	{
		result = 99;
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

int shake_recursion()
{
	pos input_pos[2];
	pair<pos, pos> result_pos;
	queue<pair<pos, pos>> pos_q;
	queue<int> dir_q;
	queue<int> num_q;
	int success =0;
	int num = 1;
	int last_dir = 99;

	input_pos[RED] = g_ball_pos[RED];
	input_pos[BLUE] = g_ball_pos[BLUE];

	int visited[MAX][MAX][MAX][MAX] = {0};
	
	visited[input_pos[RED].row][input_pos[RED].col][input_pos[BLUE].row][input_pos[BLUE].col]= 1;

	while (true)
	{
		for (int next_dir = 0; next_dir < 4; next_dir++)
		{
			pos local_pos[2];
			local_pos[RED] = input_pos[RED];
			local_pos[BLUE] = input_pos[BLUE];
			success = shake_atom(next_dir, local_pos);
			if (success == FIND)
			{
				//print_map(local_pos,num);
				return num;
			}
			else if (success == NM)
			{
				if(next_dir != last_dir && next_dir != reverse_dir(last_dir))
				{
					if (visited[local_pos[RED].row][local_pos[RED].col][local_pos[BLUE].row][local_pos[BLUE].col] == 0)
					{
						pair<pos, pos> next_pos;
						next_pos.first = local_pos[RED];
						next_pos.second = local_pos[BLUE];

						pos_q.push(next_pos);
						dir_q.push(next_dir);
						num_q.push(num);
						visited[local_pos[RED].row][local_pos[RED].col][local_pos[BLUE].row][local_pos[BLUE].col] = 1;
					}

				}
			}
		}
		if (pos_q.empty() == true)
			return -1;
		result_pos =pos_q.front();
		last_dir = dir_q.front();
		num = num_q.front();
		pos_q.pop();
		dir_q.pop();
		num_q.pop();
		num++;

		if (num > 11)
			return -1;
		
		input_pos[RED] = result_pos.first;
		input_pos[BLUE] = result_pos.second;
		//print_map(input_pos,num-1);
	}
}

void print_map(pos local_pose[2],int num)
{
	
	cout << endl << "num : " << num << endl;
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