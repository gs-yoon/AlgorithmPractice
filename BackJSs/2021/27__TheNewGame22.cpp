#include <iostream>
#include <vector>

using namespace std;

#define FORWARD 0
#define REVERSE 1

#define WHITE 0
#define RED 1
#define BLUE 2 

struct Horse
{
	int id = 0;
	int x = 0;
	int y = 0;
	int dir = 0;
	Horse* forward = nullptr;
	Horse* back = nullptr;
};

enum direction_e
{
	RIGHT=0,
	LEFT,
	UP,
	DOWN
};


int reverse_dir(int dir);
void move_atom_reverse(int nx, int ny, int target_id, Horse* target);
void move_atom_forward(int nx, int ny, Horse* target);
int move(Horse* target);
void print_map();
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,-1,1 };

int N = 0;
int horse_max = 0;
int g_map[12][12] = { 0 };
int last_horse_map[12][12] = { 0 };
int horse_num_map[12][12] = { 0 };
Horse horse_arr[10];
int main()
{
	cin >> N >> horse_max;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> g_map[xi][yi];
			last_horse_map[xi][yi] = -1;
		}
	}

	for (int i = 0; i < horse_max; i++)
	{
		Horse in_horse;
		cin >> in_horse.y >> in_horse.x >> in_horse.dir;
		in_horse.x--;
		in_horse.y--;
		in_horse.dir--;
		in_horse.id = i;
		horse_arr[i] = in_horse;
		last_horse_map[in_horse.x][in_horse.y] = i;
		horse_num_map[in_horse.x][in_horse.y] ++;
	}
	int trial = 0;
	bool keep_going = true;
	//print_map();
	while (keep_going)
	{
		int num = 0;
		if (trial < 1000)
		{
			trial++;
			for (int horse_idx = 0; horse_idx < horse_max; horse_idx++)
			{
				num = move(&horse_arr[horse_idx]);
				//print_map();
				if (num >= 4)
				{
					keep_going = false;
					break;
				}
			}
		}
		else
		{
			trial = -1;
			break;
		}
	}
	cout << trial;
	return 0;
}

int move(Horse* target)
{
	int nx = target->x + dx[target->dir];
	int ny = target->y + dy[target->dir];


	if (nx < 0 || nx >= N || ny < 0 || ny >= N)
	{
		target->dir = reverse_dir(target->dir);
		nx = target->x + dx[target->dir];
		ny = target->y + dy[target->dir];
		if (!(nx < 0 || nx >= N || ny < 0 || ny >= N))
			if (g_map[nx][ny] != BLUE)
				move(target);
			else
				return horse_num_map[target->x][target->y];
		else
			return horse_num_map[target->x][target->y];

	}
	else if (g_map[nx][ny] == WHITE)
	{
		move_atom_forward(nx,ny,target);
	}
	else if (g_map[nx][ny] == RED)
	{
		move_atom_reverse(nx, ny,target->id, target);
	}
	else if (g_map[nx][ny] == BLUE)
	{
		target->dir = reverse_dir(target->dir);
		nx = target->x + dx[target->dir];
		ny = target->y + dy[target->dir];
		if (!(nx < 0 || nx >= N || ny < 0 || ny >= N))
			if (g_map[nx][ny] != BLUE)
				move(target);
			else
				return horse_num_map[target->x][target->y];
		else
			return horse_num_map[target->x][target->y];
	}
	else
	{
		cout << "fatal error" << endl;
	}
	return horse_num_map[nx][ny];
}

void move_atom_forward(int nx, int ny, Horse* target)
{
	horse_num_map[target->x][target->y] -= 1;
	int past_x = target->x;
	int past_y = target->y;
	target->x = nx;
	target->y = ny;
	horse_num_map[nx][ny] += 1;
	Horse* forward_horse = target->forward;
	if (forward_horse != nullptr)
	{
		forward_horse->back = nullptr;
		last_horse_map[past_x][past_y] = forward_horse->id;
	}
	else
	{
		last_horse_map[past_x][past_y] = -1;
	}
	target->forward = nullptr;

	if (last_horse_map[nx][ny] != -1)
	{
		int last_idx = last_horse_map[nx][ny];
		target->forward = &horse_arr[last_idx];
		target->forward->back = target;
	}
	last_horse_map[nx][ny] = target->id;

	if (target->back != nullptr)
	{
		target->back->forward = forward_horse;
		move_atom_forward(nx,ny, target->back);
	}
}



void move_atom_reverse(int nx, int ny, int target_id, Horse* target)
{
	int last_idx = last_horse_map[target->x][target->y];
	Horse* r_target = &horse_arr[last_idx];

	int past_x = r_target->x;
	int past_y = r_target->y;

	horse_num_map[r_target->x][r_target->y] -= 1;
	r_target->x = nx;
	r_target->y = ny;
	horse_num_map[nx][ny] += 1;
	
	Horse* remain_target =nullptr;
	if (r_target->forward != nullptr)
	{
		remain_target = r_target->forward;
		last_horse_map[past_x][past_y] = remain_target->id;
		r_target->forward->back = nullptr;
	}
	else
	{
		last_horse_map[past_x][past_y] = -1;
		if (target_id != r_target->id)
		{
			cout << "target_id " << target_id << endl;
			cout << "r_target_id " << r_target->id << endl;
			return ;
		}
	}
	r_target->forward = nullptr;

	if (last_horse_map[nx][ny] != -1)
	{
		int newlast_idx = last_horse_map[nx][ny];
		r_target->forward = &horse_arr[newlast_idx];
		r_target->forward->back = r_target;
	}
	last_horse_map[nx][ny] = r_target->id;

	if (target_id != r_target->id)
	{
		move_atom_reverse(nx, ny, target_id, remain_target);
	}
}

int reverse_dir(int dir)
{
	if (dir == LEFT)
		return RIGHT;

	else if (dir == RIGHT)
		return LEFT;

	else if (dir == UP)
		return DOWN;

	else if (dir == DOWN)
		return UP;
	else
	{
		cout << "reveser_dir error";
		return -1;
	}
}

void print_map()
{
	cout << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			int cnt = 0;
			for (int i = 0; i < horse_max; i++)
			{
				if (horse_arr[i].x == xi && horse_arr[i].y == yi)
				{
					Horse* h;
					h = &horse_arr[i];
					while (true)
					{
						if (h->forward != nullptr)
							h = h->forward;
						else
							break;
					}
					while (true)
					{
						cout << h->id;
						cnt++;
						if (h->back != nullptr)
						{
							h = h->back;
						}
						else
						{
							break;
						}
					}
					break;
				}
			}
			if (cnt == 0)
			{
				if (g_map[xi][yi] == WHITE)
					cout << "*" << "     ";
				if (g_map[xi][yi] == RED)
					cout << "*" << "     ";
				if (g_map[xi][yi] == BLUE)
					cout << "*" << "     ";

			}
			else
			{
				for (int i = cnt; i <= 5; i++)
					cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}