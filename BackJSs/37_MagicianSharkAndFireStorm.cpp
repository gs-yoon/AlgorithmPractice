#include<iostream>
#include<math.h>
using namespace std;

enum direction_e
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};

int melting_down(int in_map[64][64], int x, int y);
void fire_storm(int LL);
void print_map(int in_map[64][64]);
void check_dfs(int x, int y);
void check_ice_num();

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
bool visited[64][64] = { 0 };
int g_max = 0;
int N = 0;
int g_cnt=0;

int map[64][64] = { 0 };
int Q = 0;
int* cmd_arr;
int NN = 0;
int QQ = 0;
// c -s
// s c
// 0 -1
// 1 0
int main()
{
	cin >> N >> Q;
	NN = (int)pow(2.0, double(N));
	cmd_arr = new int[Q];

	for (int yi = 0; yi < NN; yi++)
	{
		for (int xi = 0; xi < NN; xi++)
		{
			cin >> map[xi][yi];
		}
	}

	for (int i = 0; i < Q; i++)
	{
		int cmd = 0;
		cin >> cmd;
		cmd_arr[i] = (int)pow(2.0, (double)cmd);
	}

	for (int i = 0; i < Q; i++)
	{
		fire_storm(cmd_arr[i]);
	}
	check_ice_num();

	long int sum = 0;
	for (int yi = 0; yi < NN; yi++)
	{
		for (int xi = 0; xi < NN; xi++)
		{
			sum += map[xi][yi];
		}
	}
	cout << sum<<endl;
	cout << g_max;
	return 0;
}

void fire_storm(int LL)
{
	int lx = 0;
	int ly = 0;
	int rx = 0;
	int ry = 0;
	int n_map[64][64] = { 0 };
	for (ly =0; ly < NN; ly += LL)
	{
		for (lx=0; lx < NN; lx += LL)
		{
			rx = lx + LL - 1;
			ry = ly + LL - 1;

			float mx = (float)(lx + rx) / 2;
			float my = (float)(ly + ry) / 2;


			for (float yi = ly; yi <= ry; yi += 1)
			{
				for (float xi = lx; xi <= rx; xi += 1)
				{
					float nx = 0*xi + (-1) * (yi - my);
					float ny = (1) * (xi - mx) + 0*yi;

					nx += mx;
					ny += my;

					n_map[(int)nx][(int)ny] = map[(int)xi][(int)yi];
				}
			}

		}
	}
	//print_map(n_map);
	for (int yi = 0; yi < NN; yi++)
	{
		for (int xi = 0; xi < NN; xi++)
		{
			map[xi][yi] = melting_down(n_map, xi, yi);
		}
	}
	//print_map(map);
}

int melting_down(int in_map[64][64],int x ,int y)
{
	int cnt = 0;
	for (int dir = 0; dir < 4; dir++)
	{
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		if (0 <= nx && nx < NN && 0 <= ny && ny < NN)
		{
			if (in_map[nx][ny] > 0)
			{
				cnt++;
			}
		}
	}

	if (cnt < 3 && in_map[x][y] >0)
	{
		return in_map[x][y]-1;
	}
	else
	{
		return in_map[x][y];
	}
}


void check_ice_num()
{
	for (int yi = 0; yi < NN; yi++)
	{
		for (int xi = 0; xi < NN; xi++)
		{
			g_cnt = 0;
			check_dfs(xi, yi);
			if (g_cnt > g_max)
			{
				g_max = g_cnt;
			}
		}
	}
}
void check_dfs(int x, int y)
{
	if (visited[x][y] == 1)
		return;
	visited[x][y] = 1;
	if (map[x][y] == 0)
		return;

	g_cnt++;

	for (int dir = 0; dir < 4; dir++)
	{
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		if (0 <= nx && nx < NN && 0 <= ny && ny < NN)
		{
			check_dfs(nx, ny);
		}
	}
}

void print_map(int in_map[64][64])
{
	cout << endl;
	for (int yi = 0; yi < NN; yi++)
	{
		for (int xi = 0; xi < NN; xi++)
		{
			cout << in_map[xi][yi] << " ";
		}
		cout << endl;
	}
	cout << endl;
}