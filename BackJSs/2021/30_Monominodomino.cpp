#include <iostream>

using namespace std;

#define DELETE 0
#define CHECK 1
#define CHECKONLYONE 2
enum direction_e
{
	DOWN = 0,
	RIGHT
};

struct Block
{
	int type = 0;
	int x = 0;
	int y = 0;
};

bool line_operation(int x, int y, int dir, int cmd);
void move_all_atom(int x, int y, int dir);
void move(Block in_block);
bool check_range(int x, int y, int dir);
void move_atom(Block in_block, int dir);
void print_map();

int dx[] = { 0,1 };
int dy[] = { 1,0 };

int map[10][10] = { 0 };
int green_min_x = 0;
int green_max_x = 4;
int green_min_y = 4;
int green_max_y = 10;

int blue_min_x = 4;
int blue_max_x = 10;
int blue_min_y = 0;
int blue_max_y = 4;
int N = 0;
Block* block_arr;

int score = 0;
int main()
{
	cin >> N;
	block_arr = new Block[N];
	for (int i = 0; i < N; i++)
	{
		cin >> block_arr[i].type;
		cin >> block_arr[i].y;
		cin >> block_arr[i].x;
	}

	for (int i = 0; i < N; i++)
	{
		move(block_arr[i]);
		//print_map();
	}

	int sum = 0;
	for (int yi = blue_min_y; yi < blue_max_y; yi++)
	{
		for (int xi = blue_min_x; xi < blue_max_x; xi++)
		{
			if (map[xi][yi] > 0)
				sum++;
		}
	}
	for (int yi = green_min_y; yi < green_max_y; yi++)
	{
		for (int xi = green_min_x; xi < green_max_x; xi++)
		{
			if (map[xi][yi] > 0)
				sum++;
		}
	}

	cout << score << endl;
	cout << sum;
}

void move(Block in_block)
{
	move_atom(in_block, DOWN);
	move_atom(in_block, RIGHT);
}

void move_atom(Block in_block, int dir)
{
	//get pos
	int x[2] = {-1,-1};
	int y[2] = {-1,-1};
	x[0] = in_block.x;
	y[0] = in_block.y;
	int size = 0;

	//make block pos
	if (in_block.type == 1)
	{
		size = 1;
	}
	else if (in_block.type == 2)
	{
		x[1] = x[0] + 1;
		y[1] = y[0];
		size = 2;
	}
	else
	{
		x[1] = x[0];
		y[1] = y[0] + 1;
		size = 2;
	}

	//move block
	int nx[2] = {-1,-1};
	int ny[2] = {-1,-1};
	bool go = true;
	while (go)
	{
		for (int i = 0; i < size; i++)
		{
			nx[i] = x[i] + dx[dir];
			ny[i] = y[i] + dy[dir];
			if (check_range(nx[i], ny[i], dir) == true)
			{
				if (map[nx[i]][ny[i]] == 0)
				{
					go &= true;
				}
				else
				{
					go &= false;
				}
			}
			else
			{
				go &= false;
			}
		}

		if (go == true)
		{
			for (int i = 0; i < size; i++)
			{
				x[i] = nx[i];
				y[i] = ny[i];
			}
		}
	}

	//save block to map & check

	for (int i = 0; i < size; i++)
	{
		map[x[i]][y[i]] = 1;
	}
	int check = 0;
	//check line and operation
	check = line_operation(x[0], y[0], dir, CHECK);
	if (check == true)
	{
		move_all_atom(x[0], y[0], dir);
		score++;
	}
	if (line_operation(x[1], y[1], dir, CHECK))
	{
		move_all_atom(x[1], y[1], dir);
		score++;
	}

	check = 0;
	if (line_operation(blue_min_x,green_min_y,dir,CHECKONLYONE))
		check += 1;
	if (line_operation(blue_min_x + 1, green_min_y + 1, dir, CHECKONLYONE))
		check += 1;
	//move a line
	for (int i =0 ; i< check ;i ++)
	{
		move_all_atom(blue_max_x-1, green_max_y-1, dir);
	}

}

void move_all_atom(int x, int y, int dir)
{
	line_operation(x, y, dir, DELETE);
	int max_x;
	int min_x;
	int max_y;
	int min_y;
	if (dir == DOWN)
	{
		max_x = green_max_x;
		min_x = green_min_x;
		max_y = y;
		min_y = green_min_y;
		for (int yi = max_y -1; yi >= min_y; yi--)
		{
			for (int xi = 0; xi < max_x; xi++)
			{
				if(xi + dx[dir]< 10 && yi + dy[dir] <10)
					map[xi + dx[dir]][yi + dy[dir]] = map[xi][yi];
			}
		}
	}
	else
	{
		max_x = x;
		min_x = blue_min_x;
		max_y = blue_max_y;
		min_y = blue_min_y;

		for (int xi = max_x -1; xi >= min_x; xi--)
		{
			for (int yi = min_y; yi < max_y; yi++)
			{
				if (xi + dx[dir] < 10 && yi + dy[dir] < 10)
					map[xi + dx[dir]][yi + dy[dir]] = map[xi][yi];
			}
		}
	}

	line_operation(min_x, min_y, dir, DELETE);
}

bool line_operation(int x, int y, int dir, int cmd)
{
	int max_x;
	int min_x;
	int max_y;
	int min_y;
	if (dir == DOWN)
	{
		max_x = green_max_x;
		min_x = green_min_x;
		max_y = y+1;
		min_y = y;
	}
	else
	{
		max_x = x + 1;
		min_x = x;
		max_y = blue_max_y;
		min_y = blue_min_y;
	}
	bool check = true;
	if (cmd == DELETE)
	{
		for (int yi = min_y; yi < max_y; yi++)
		{
			for (int xi = min_x; xi < max_x; xi++)
			{
				map[xi][yi] = 0;
			}
		}
	}
	else if(cmd == CHECK)
	{
		for (int yi = min_y; yi < max_y; yi++)
		{
			for (int xi = min_x; xi < max_x; xi++)
			{
				if (map[xi][yi] == 1)
				{
					check &= true;
				}
				else
				{
					check &= false;
				}
			}
		}
	}
	else
	{
		check = false;
		for (int yi = min_y; yi < max_y; yi++)
		{
			for (int xi = min_x; xi < max_x; xi++)
			{
				if (map[xi][yi] == 1)
				{
					check |= true;
				}
				else
				{
					check |= false;
				}
			}
		}
	}
	return check;
}

bool check_range(int x, int y, int dir)
{
	int max_x;
	int min_x;
	int max_y;
	int min_y;
	if (dir == DOWN)
	{
		max_x = green_max_x;
		min_x = green_min_x;
		max_y = green_max_y;
		min_y = 0;
	}
	else
	{
		max_x = blue_max_x;
		min_x = 0;
		max_y = blue_max_y;
		min_y = blue_min_y;
	}
	if (min_x <= x && x < max_x && min_y <= y && y < max_y)
		return true;
	else
		return false;
}

void print_map()
{
	cout << endl;
	for (int yi = 0; yi < 10; yi++)
	{
		for (int xi = 0; xi < 10; xi++)
		{
			cout << map[xi][yi] << " ";
		}
		cout << endl; 
	}
	cout << endl;
}