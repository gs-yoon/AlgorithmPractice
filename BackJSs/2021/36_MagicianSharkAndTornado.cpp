#include <iostream>

using namespace std;

enum direction_e {
	LEFT =0,
	DOWN,
	RIGHT,
	UP
};

struct Pos
{
	int x = 0;
	int y = 0;
};

bool is_out_range(int x, int y, int sand);
Pos move(int cx, int cy, int dir);
void print_map();

int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

int N =0;
int map[500][500];
Pos tornado_pos;
int out_sand = 0;
int main()
{
	cin >> N;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> map[xi][yi];
		}
	}

	int tx = N / 2;
	int ty = N / 2;
	tornado_pos.x = tx;
	tornado_pos.y = ty;
	int dir = -1;
	int cnt = 0;
	int inc = 0;
	while (!(tx == 0 && ty == 0))
	{
		if (cnt % 2 == 0)
			inc += 1;
		dir ++;
		dir %= 4;
		for (int i = 0; i < inc; i++)
		{
			tornado_pos = move(tx, ty, dir);
			tx = tornado_pos.x;
			ty = tornado_pos.y;
			if (tx == 0 && ty == 0)
				break;
		}
		cnt++;
	}
	cout << out_sand;
}

void print_map()
{
	cout << endl;
	cout << "out : " << out_sand << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			if (tornado_pos.x == xi && tornado_pos.y == yi)
			{
				cout << "t ";
			}
			else
			{
				cout << map[xi][yi]<<" ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

Pos move(int cx, int cy, int dir)
{
	int nx = cx + dx[dir];
	int ny = cy + dy[dir];

	int sand = map[nx][ny];

	int vndir = (dir + 1) % 4;
	int vpdir = (dir + 3) % 4;

	int sx = 0;
	int sy = 0;
	int sum_sand = 0;
	if (sand > 0)
	{
		// 7%
		sx = nx + dx[vndir];
		sy = ny + dy[vndir];
		if (is_out_range(sx, sy, sand * 7 / 100) == false)
			map[sx][sy] += sand * 7 / 100;
		sum_sand += sand * 7 / 100;

		//10%
		sx = sx + dx[dir];
		sy = sy + dy[dir];
		if (is_out_range(sx, sy, sand * 10 / 100) == false)
			map[sx][sy] += sand * 10 / 100;
		sum_sand += sand * 10 / 100;

		//2%
		sx = nx + dx[vndir] * 2;
		sy = ny + dy[vndir] * 2;
		if (is_out_range(sx, sy, sand * 2 / 100) == false)
			map[sx][sy] += sand * 2 / 100;
		sum_sand += sand * 2 / 100;

		//7%
		sx = nx + dx[vpdir];
		sy = ny + dy[vpdir];
		if (is_out_range(sx, sy, sand * 7 / 100) == false)
			map[sx][sy] += sand * 7 / 100;
		sum_sand += sand * 7 / 100;

		//10%
		sx = sx + dx[dir];
		sy = sy + dy[dir];
		if (is_out_range(sx, sy, sand * 10 / 100) == false)
			map[sx][sy] += sand * 10 / 100;
		sum_sand += sand * 10 / 100;

		//2%
		sx = nx + dx[vpdir] * 2;
		sy = ny + dy[vpdir] * 2;
		if (is_out_range(sx, sy, sand * 2 / 100) == false)
			map[sx][sy] += sand * 2 / 100;
		sum_sand += sand * 2 / 100;

		//5%
		sx = nx + dx[dir] * 2;
		sy = ny + dy[dir] * 2;
		if (is_out_range(sx, sy, sand * 5 / 100) == false)
			map[sx][sy] += sand * 5 / 100;
		sum_sand += sand * 5 / 100;

		//1%
		sx = cx + dx[vndir];
		sy = cy + dy[vndir];
		if (is_out_range(sx, sy, sand * 1 / 100) == false)
			map[sx][sy] += sand * 1 / 100;
		sum_sand += sand * 1 / 100;

		//1%
		sx = cx + dx[vpdir];
		sy = cy + dy[vpdir];
		if (is_out_range(sx, sy, sand * 1 / 100) == false)
			map[sx][sy] += sand * 1 / 100;
		sum_sand += sand * 1 / 100;

		//a%
		int rmn_sand = sand - sum_sand;
		sx = nx + dx[dir];
		sy = ny + dy[dir];
		if (is_out_range(sx, sy, rmn_sand) == false)
			map[sx][sy] += rmn_sand;
	}
	map[nx][ny] = 0;

	tornado_pos.x = nx;
	tornado_pos.y = ny;
	return tornado_pos;
}

bool is_out_range(int x , int y, int sand)
{
	if (0 <= x && x < N && 0 <= y && y < N)
	{
		return false;
	}
	else
	{
		out_sand += sand;
		return true;
	}
}