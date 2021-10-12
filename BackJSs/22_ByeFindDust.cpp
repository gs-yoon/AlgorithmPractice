#include <iostream>
#include <queue>

using namespace std;

#define UPC 0
#define DOWNC 1

enum direction_e
{
	UP=0,
	RIGHT,
	DOWN,
	LEFT
};

struct pos
{
	int x = 0;
	int y = 0;
	int dust = 0;
};

void operate_cleaner();
void diffuse();
void print_map(int src[50][50]);

int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };

int ctr_clk_wise[] = {RIGHT,UP,LEFT,DOWN };
int clk_wise[] = { RIGHT,DOWN,LEFT,UP };

int y_max = 0;
int x_max = 0;
int T = 0;
int g_map[50][50] = { 0 };
pos cleaner_arr[2];
int cleaner_idx = 0;
queue<pos> diffusable_q;


int main()
{
	cin >> y_max;
	cin >> x_max;

	cin >> T;

	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			cin >> g_map[xi][yi];
			if (g_map[xi][yi] >= 5)
			{
				pos df;
				df.x = xi;
				df.y = yi;
				df.dust = g_map[xi][yi];
				diffusable_q.push(df);
			}
			else if (g_map[xi][yi] <0)
			{
				cleaner_arr[cleaner_idx].x = xi;
				cleaner_arr[cleaner_idx].y = yi;
				cleaner_idx++;
			}
		}
	}
	for (int loop = 0; loop < T; loop++)
	{
		diffuse();
		//print_map(g_map);
		operate_cleaner();
		//print_map(g_map);
	}
	int sum = 0;
	for (int yi = 0; yi < y_max; yi++)
		for (int xi = 0; xi < x_max; xi++)
			sum += g_map[xi][yi];

	sum += 2;
	cout << sum;
}


void diffuse()
{
	while (!diffusable_q.empty())
	{
		pos df_target = diffusable_q.front(); diffusable_q.pop();

		int dust = df_target.dust;
		int df_num = 0;

		//diffuse
		for (int dir = 0; dir < 4; dir++)
		{
			int nx = df_target.x + dx[dir];
			int ny = df_target.y + dy[dir];

			if (0 <= nx && nx < x_max && 0 <= ny && ny < y_max && g_map[nx][ny] != -1)
			{
				g_map[nx][ny] += dust / 5;

				df_num++;
			}
		}
		if (df_num > 0)
		{
			g_map[df_target.x][df_target.y] -= dust / 5 * df_num;
		}
	}
}


void operate_cleaner()
{
	for (int cleaner_idx = 0; cleaner_idx < 2; cleaner_idx++)
	{
		int cur_x = cleaner_arr[cleaner_idx].x;
		int cur_y = cleaner_arr[cleaner_idx].y;
		if (cleaner_idx == UPC)
		{
			cur_x += dx[ctr_clk_wise[0]];
			cur_y += dy[ctr_clk_wise[0]];
		}
		else
		{
			cur_x += dx[clk_wise[0]];
			cur_y += dy[clk_wise[0]];
		}
		int cur_dust = g_map[cur_x][cur_y];
		g_map[cur_x][cur_y] = 0;

		for (int clk_idx = 0; clk_idx < 4; )
		{
			int dir ;
			if (cleaner_idx == UPC)
			{
				dir = ctr_clk_wise[clk_idx];
			}
				else
			{
				dir = clk_wise[clk_idx];
			}

			int next_x = cur_x + dx[dir];
			int next_y = cur_y + dy[dir];
			if (g_map[next_x][next_y] == -1)
			{
				if (clk_idx < 3)
					cout << "fatal error" << endl;
				break;
			}
			else if (0 <= next_x && next_x < x_max && 0 <= next_y && next_y < y_max)
			{
				int next_dust = g_map[next_x][next_y];

				g_map[next_x][next_y] = cur_dust;

				cur_dust = next_dust;
				cur_x = next_x;
				cur_y = next_y;
			}
			else
			{
				clk_idx++;
			}
		}
	}

	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			if (g_map[xi][yi] >= 5)
			{
				pos new_dust;
				new_dust.x = xi;
				new_dust.y = yi;
				new_dust.dust = g_map[xi][yi];
				diffusable_q.push(new_dust);
			}
		}
	}
}

void print_map(int src[50][50])
{
	cout << endl;
	for (int yi = 0; yi < y_max; yi++)
	{
		for (int xi = 0; xi < x_max; xi++)
		{
			cout << src[xi][yi] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
