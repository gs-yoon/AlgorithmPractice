#include <iostream>
#include <vector>

using namespace std;

#define NONE -2
#define BLACK -1
#define RAINBOW 0

struct Group
{
	int num = 0;
	int rp_x = 0;
	int rp_y = 0;
	int size = 0;
	int color = 0;

	int rainbow_num = 0;
};

void rotate();
void apply_gravity();
void move_down_atom(int cx, int cy);
bool make_group(int cx, int cy, int group_map[20][20], Group& group);
void clear_map(int in[20][20], int n);
void print_map(int in[20][20]);

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };
int N = 0;
int M = 0;

int map[20][20] = { 0 };
long int grade = 0;
int visited[20][20] = { 0 };

int main()
{
	cin >> N >> M;

	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> map[xi][yi];
		}
	}

	int group_num = 1;
	int group_map[20][20] = { 0 };
	while (true)
	{
		group_num = 1;
		clear_map(group_map, 0);
		vector<Group> group_vec;
		for (int yi = 0; yi < N; yi++)
		{
			for (int xi = 0; xi < N; xi++)
			{
				bool make_flag= false;
				Group group;
				if (map[xi][yi] > 0 && group_map[xi][yi] == 0)
				{
					clear_map(visited, 0);
					group.num = group_num;
					group.rp_x = xi;
					group.rp_y = yi;
					group.color = map[xi][yi];
					make_flag = make_group(xi, yi, group_map, group);
					if (group.size < 2)
						make_flag = false;
				}
				if (make_flag)
				{
					group_num++;
					group_vec.push_back(group);
				}
			}
		}
		int block_max = -1;
		int rainbow_max = -1;
		int block_x = -1;
		int block_y = -1;
		Group big_group;
		if (group_vec.size() > 0)
		{
			for (int vi = 0; vi < group_vec.size(); vi++)
			{
				if (block_max < group_vec[vi].size)
				{
					rainbow_max = group_vec[vi].rainbow_num;
					block_max = group_vec[vi].size;
					big_group = group_vec[vi];
					block_x = group_vec[vi].rp_x;
					block_y = group_vec[vi].rp_y;
				}
				else if(block_max == group_vec[vi].size)
				{
					if (rainbow_max < group_vec[vi].rainbow_num)
					{
						rainbow_max = group_vec[vi].rainbow_num;
						block_max = group_vec[vi].size;
						big_group = group_vec[vi];
						block_x = group_vec[vi].rp_x;
						block_y = group_vec[vi].rp_y;
					}
					else if (rainbow_max == group_vec[vi].rainbow_num)
					{
						if (block_y < group_vec[vi].rp_y)
						{
							rainbow_max = group_vec[vi].rainbow_num;
							block_max = group_vec[vi].size;
							big_group = group_vec[vi];
							block_x = group_vec[vi].rp_x;
							block_y = group_vec[vi].rp_y;
						}
						else if (block_y == group_vec[vi].rp_y)
						{
							if (block_x < group_vec[vi].rp_x)
							{
								rainbow_max = group_vec[vi].rainbow_num;
								block_max = group_vec[vi].size;
								big_group = group_vec[vi];
								block_x = group_vec[vi].rp_x;
								block_y = group_vec[vi].rp_y;
							}
						}
					}
				}
			}
			if (big_group.size < 2)
				break;

			//if not stop game
			clear_map(visited, 0);
			clear_map(group_map, 0);
			big_group.size = 0;
			big_group.rainbow_num = 0;
			make_group(big_group.rp_x,big_group.rp_y, group_map, big_group);
			//print_map(visited);
			int num = 0;
			for (int yi = 0; yi < N; yi++)
			{
				for (int xi = 0; xi < N; xi++)
				{
					if (visited[xi][yi] == 1)
					{
						visited[xi][yi] = 0;
						num++;
						map[xi][yi] = NONE;
					}
				}
			}
			grade += (num * num);
			//print_map(map);
			apply_gravity();
			//print_map(map);
			rotate();
			//print_map(map);
			apply_gravity();
			//print_map(map);
		}
		else
		{
			break;
		}
	}
	cout << grade;
}



void clear_map(int in[20][20], int n)
{
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			in[xi][yi] =n;
		}
	}
}

bool make_group(int cx, int cy, int group_map[20][20], Group& group)
{
	if (!(0 <= cx && cx < N && 0 <= cy && cy < N))
		return false;
	if (group_map[cx][cy] > 0)
		return false;
	if (map[cx][cy] == BLACK)
		return false;
	if (visited[cx][cy] != 0)
		return false;
	
	if (map[cx][cy] == RAINBOW || map[cx][cy] == group.color)
	{
		if (map[cx][cy] == RAINBOW)
		{
			group.rainbow_num += 1;
		}
		else if (map[cx][cy] > 0)
		{
			group_map[cx][cy] = group.num;
		}
		group.size++;
		visited[cx][cy] = 1;
		for (int dir = 0; dir < 4; dir++)
		{
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];
			make_group(nx, ny, group_map, group);
		}

		return true;
	}
	return false;
}

void move_down_atom(int cx, int cy)
{
	int ny = 0;
	while (true)
	{
		ny = cy + 1;
		if (map[cx][ny] == NONE)
		{
			map[cx][ny] = map[cx][cy];
			map[cx][cy] = NONE;
			cy = ny;
		}
		else
		{
			break;
		}
	}
}

void apply_gravity()
{
	for (int xi = 0; xi < N; xi++)
	{
		for (int yi = N - 1; yi >= 0; yi--)
		{
			if (map[xi][yi] > BLACK)
			{
				move_down_atom(xi, yi);
			}
		}
	}
}

void rotate()
{
	float mx = (float)(N-1) / 2.0;
	float my = (float)(N-1) / 2.0;
	int temp_map[20][20] = { 0 };

	clear_map(temp_map, NONE);

	for (float yi = 0; yi < N; yi+=1)
	{
		for (float xi = 0; xi < N; xi+=1)
		{

			float nx = (xi - mx) * ( 0) + (yi - mx) * ( 1);
			float ny = (xi - my) * (-1) + (yi - my) * ( 0);

			nx += mx;
			ny += my;

			temp_map[(int)nx][(int)ny] = map[(int)xi][(int)yi];
		}
	}

	for (int yi = 0; yi < N; yi += 1)
	{
		for (int xi = 0; xi < N; xi += 1)
		{
			map[xi][yi] = temp_map[xi][yi];
		}
	}
}

void print_map(int in[20][20])
{
	cout << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			if (in[xi][yi] == -2)
				cout << "* ";
			else if (in[xi][yi] == -1)
				cout << "- ";
			else
				cout << in[xi][yi] << " ";
		}
		cout << endl;
	}
	cout << endl;
}