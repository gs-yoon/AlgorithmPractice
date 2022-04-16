#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Fish
{
	int x = 0;
	int y = 0;
	int num =0;
	int direction =0;
};

void solve(vector<Fish> in_fish_vec, Fish in_fish_map[4][4], Fish in_shark, int sx, int sy);
void print_map(Fish shark, Fish map[4][4]);
bool cmp(Fish x, Fish y)
{
	return x.num < y.num;
}

int dx[] = {  0, -1, -1, -1, 0, 1, 1,  1 };
int dy[] = { -1 ,-1,  0,  1, 1, 1, 0, -1 };

Fish fish_map[4][4];
vector<Fish> fish_vec;
Fish shark;
int g_max = 0;

int main()
{
	fish_vec.reserve(16);
	for (int yi = 0; yi < 4; yi++)
	{
		for (int xi = 0; xi < 4; xi++)
		{
			cin >> fish_map[xi][yi].num >> fish_map[xi][yi].direction;
			fish_map[xi][yi].x = xi;
			fish_map[xi][yi].y = yi;
			fish_map[xi][yi].direction--;
			fish_vec.push_back(fish_map[xi][yi]);
		}
	}
	sort(fish_vec.begin(), fish_vec.end(), cmp);

	solve(fish_vec, fish_map, shark, 0, 0);

	cout << g_max;
}

void solve(vector<Fish> in_fish_vec, Fish in_fish_map[4][4], Fish in_shark, int sx, int sy)
{
	if (sx < 0 || sx >= 4 || sy < 0 || sy >= 4)
		return;
	if (in_fish_map[sx][sy].num == 0)
		return;

	vector<Fish> local_fish_vec = in_fish_vec;
	Fish local_fish_map[4][4];
	for (int yi = 0; yi < 4; yi++)
		for (int xi = 0; xi < 4; xi ++)
			local_fish_map[xi][yi] = in_fish_map[xi][yi];
	Fish local_shark = in_shark;

	local_shark.x = sx;
	local_shark.y = sy;
	local_shark.num += local_fish_map[sx][sy].num;
	local_shark.direction = local_fish_map[sx][sy].direction;
	local_fish_vec.at(local_fish_map[sx][sy].num - 1).num = 0;
	local_fish_map[sx][sy].num = 0;

	if (g_max < local_shark.num)
		g_max = local_shark.num;
	
	print_map(local_shark, local_fish_map);
	cout << "==" << endl;
	for (int i = 0; i < local_fish_vec.size(); i++)
	{
		Fish cur_fish = local_fish_vec[i];
		int cx = cur_fish.x;
		int cy = cur_fish.y;
		if (local_fish_map[cx][cy].num == 0)
			continue;
		for (int dir_loop = 0; dir_loop < 8; dir_loop++)
		{
			int dir = local_fish_map[cx][cy].direction;
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];
			if (0 <= nx && nx < 4 && 0 <= ny && ny < 4 && !(nx == local_shark.x && ny == local_shark.y))
			{
				if (local_fish_map[nx][ny].num != 0)
				{
					Fish cur;
					cur = local_fish_map[cx][cy];
					local_fish_vec[cur.num - 1].x = nx;
					local_fish_vec[cur.num - 1].y = ny;
					Fish next = local_fish_map[nx][ny];
					local_fish_vec[next.num - 1].x = cx;
					local_fish_vec[next.num - 1].y = cy;

					local_fish_map[cx][cy].num = local_fish_map[nx][ny].num;
					local_fish_map[cx][cy].direction = local_fish_map[nx][ny].direction;
					local_fish_map[nx][ny].num = cur.num;
					local_fish_map[nx][ny].direction = cur.direction;
					break;
				}
				else
				{
					local_fish_map[nx][ny].num = local_fish_map[cx][cy].num;
					local_fish_map[nx][ny].direction = local_fish_map[cx][cy].direction;

					local_fish_map[cx][cy].num = 0;
					break;
				}
			}
			else
			{
				//if (dir_loop == 7)
				//	break;
				local_fish_map[cx][cy].direction++;
				local_fish_map[cx][cy].direction %= 8;
				cur_fish.direction = local_fish_map[cx][cy].direction;
			}
		}
	}
	print_map(local_shark, local_fish_map);
	int snx;
	int sny;
	for (int i = 1; i <= 3; i++)
	{
		snx = local_shark.x + dx[local_shark.direction]*i;
		sny = local_shark.y + dy[local_shark.direction]*i;
		solve(local_fish_vec, local_fish_map, local_shark, snx, sny);
	}
}

void print_map(Fish shark, Fish map[4][4])
{

	cout << endl;
	for (int yi = 0; yi < 4; yi++)
	{
		for (int xi = 0; xi < 4; xi++)
		{
			if (shark.x == xi && shark.y == yi)
				cout << "s ";
			else
				cout << map[xi][yi].num << " ";
		}
		cout << endl;
	}
	cout << endl;
}