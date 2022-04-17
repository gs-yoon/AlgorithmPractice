#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Fish
{
	int num = 0;
	int dir = 0;
};

struct Pos
{
	int x = 0;
	int y = 0;
};

void progress(Fish in_map[4][4], vector<Pos> in_pos_vec, Fish in_shark, Pos in_shark_pos);
void print_map(Pos shark_pos,Fish shark, Fish map[4][4]);
bool cmp(Pos a, Pos b);


int dx[] = { 0, -1, -1, -1, 0, 1, 1,  1 };
int dy[] = { -1 ,-1,  0,  1, 1, 1, 0, -1 };

Fish fish_map[4][4];
vector<Pos> fish_pos_vec;
Fish shark;
Pos shark_pos;
int g_max = 0;
int main()
{
	fish_pos_vec.reserve(16);
	for (int yi = 0; yi < 4; yi++)
	{
		for (int xi = 0; xi < 4; xi++)
		{
			cin >> fish_map[xi][yi].num >> fish_map[xi][yi].dir;

			Pos fish_pos;
			fish_pos.x = xi;
			fish_pos.y = yi;
			fish_map[xi][yi].dir--;
			fish_pos_vec.push_back(fish_pos);
		}
	}
	sort(fish_pos_vec.begin(), fish_pos_vec.end(), cmp);
	shark.num = 0;
	shark.dir = 0;
	shark_pos.x = 0;
	shark_pos.y = 0;
	progress(fish_map, fish_pos_vec, shark, shark_pos);
	cout << g_max;
}

void progress(Fish in_map[4][4], vector<Pos> in_pos_vec, Fish in_shark, Pos in_shark_pos)
{
	//copy to local var
	Fish local_map[4][4];
	for (int yi = 0; yi < 4; yi++)
	{
		for (int xi = 0; xi < 4; xi++)
		{
			local_map[xi][yi] = in_map[xi][yi];
		}
	}
	vector<Pos> local_pos_vec;
	local_pos_vec = in_pos_vec;
	Fish local_shark = in_shark;
	Pos local_shark_pos = in_shark_pos;

	int sx = local_shark_pos.x;
	int sy = local_shark_pos.y;

	//algo start
	//shark move
	local_shark.num += local_map[sx][sy].num;
	local_shark.dir = local_map[sx][sy].dir;
	
	local_pos_vec[local_map[sx][sy].num - 1].x = -1;
	local_pos_vec[local_map[sx][sy].num - 1].y = -1;
	local_map[sx][sy].num = 0;

	if (g_max < local_shark.num)
		g_max = local_shark.num;
	//cout << "num = " << local_shark.num << endl;
	//print_map(local_shark_pos, local_shark, local_map);
	//fish move
	for (int i = 0; i < local_pos_vec.size(); i++)
	{
		int cx = local_pos_vec.at(i).x;
		int cy = local_pos_vec.at(i).y;
		int nx = 0;
		int ny = 0;
		int dir = 0;
		if (cx < 0)
			continue;
		if (local_map[cx][cy].num != 0)
		{
			dir = local_map[cx][cy].dir;
			nx = cx + dx[dir];
			ny = cy + dy[dir];
			while ( !(0 <= nx && nx < 4 && 0 <= ny && ny < 4) || ( nx == sx && ny == sy))
			{
				dir += 1;
				dir %=8;
			
				nx = cx + dx[dir];
				ny = cy + dy[dir];
			}
			local_map[cx][cy].dir = dir;
			local_pos_vec[i].x = nx;
			local_pos_vec[i].y = ny;
			if (local_map[nx][ny].num != 0)
			{
				local_pos_vec[local_map[nx][ny].num - 1].x = cx;
				local_pos_vec[local_map[nx][ny].num - 1].y = cy;
			}

			Fish temp = local_map[cx][cy];
			local_map[cx][cy] = local_map[nx][ny];
			local_map[nx][ny] = temp;

		}
	}
	//print_map(local_shark_pos, local_shark,local_map);

	//choice a next shark pos 
	for (int i = 1; i <= 3; i++)
	{
		int nsx = sx + dx[local_shark.dir]*i;
		int nsy = sy + dy[local_shark.dir]*i;

		if (local_map[nsx][nsy].num != 0 && (0 <= nsx && nsx < 4 && 0 <= nsy && nsy < 4))
		{
			local_shark_pos.x = nsx;
			local_shark_pos.y = nsy;
			progress(local_map, local_pos_vec, local_shark, local_shark_pos);
		}
	}
}
bool cmp(Pos a, Pos b)
{
	return fish_map[a.x][a.y].num < fish_map[b.x][b.y].num;
}

char dirchar[8] = { 'U', 'U','L','L','D','D','R','R' };
char dirchar2[8] = { 'U', 'L','L','D','D','R','R','U' };

void print_map(Pos shark_pos, Fish in_shark,Fish map[4][4])
{
	cout << endl;
	for (int yi = 0; yi < 4; yi++)
	{
		for (int xi = 0; xi < 4; xi++)
		{
			if (shark_pos.x == xi && shark_pos.y == yi)
			{
				cout << "s";
				cout << dirchar[in_shark.dir] << dirchar2[in_shark.dir] << " ";
			}
			else
			{
				cout << map[xi][yi].num;
				cout << dirchar[map[xi][yi].dir] << dirchar2[map[xi][yi].dir] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
