#include<iostream>
#include<vector>

using namespace std;

struct CMD
{
	int dir = 0;
	int v = 0;
};
struct Pos
{
	int x = 0;
	int y = 0;
};

void make_cloud(vector<Pos>& cloud, vector<Pos>& past_cloud);
void copy_water(vector<Pos>& cloud);
void rain(vector<Pos>& cloud);
void move_cloud(vector<Pos>& cloud, CMD cmd);
void move_atom(int& cx, int& cy, CMD cmd);
void print_map();
void print_vec(vector<Pos> clouds);

int dx[] = { -1,-1,0,1,1,1,0,-1 };
int dy[] = { 0,-1,-1,-1,0,1,1,1 };

int N = 0;
int M = 0;
int map[50][50];
vector<CMD> cmd_vec;
vector<Pos> cloud_vec;

int main()
{
	cin >> N >> M;

	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi ++ )
		{
			cin >> map[xi][yi];
		}
	}

	for (int i = 0; i < M; i++)
	{
		CMD in_cmd;
		cin >> in_cmd.dir >> in_cmd.v;
		in_cmd.dir--;
		cmd_vec.push_back(in_cmd);
	}

	Pos cloud;
	cloud.x = 0;
	cloud.y = N - 2;
	cloud_vec.push_back(cloud);
	cloud.x = 1;
	cloud.y = N - 2;
	cloud_vec.push_back(cloud);
	cloud.x = 0;
	cloud.y = N - 1;
	cloud_vec.push_back(cloud);
	cloud.x = 1;
	cloud.y = N - 1;
	cloud_vec.push_back(cloud);

	vector<Pos> past_clouds;
	for (int cmd_idx = 0; cmd_idx < cmd_vec.size(); cmd_idx++)
	{
		CMD cmd = cmd_vec[cmd_idx];

		move_cloud(cloud_vec, cmd);
		rain(cloud_vec);
		past_clouds = cloud_vec;
		cloud_vec.clear();
		copy_water(past_clouds);
		make_cloud(cloud_vec, past_clouds);
	}

	int sum = 0;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			sum += map[xi][yi];
		}
	}
	cout << sum;
	return 0;
}

void move_atom(int& cx, int& cy , CMD cmd)
{
	int dir = cmd.dir;
	int v = cmd.v;

	int nx = cx + dx[dir] * v;
	int ny = cy + dy[dir] * v;

	nx %= N;
	ny %= N;
	if (nx < 0)
	{
		nx = N + nx;
	}
	if (ny < 0)
	{
		ny = N + ny;
	}

	cx = nx;
	cy = ny;
}

void move_cloud(vector<Pos>& cloud, CMD cmd)
{
	for (int vi = 0; vi < cloud_vec.size(); vi++)
	{
		move_atom(cloud[vi].x, cloud[vi].y, cmd);
	}
}

void rain(vector<Pos>& cloud)
{
	for (int vi = 0; vi < cloud_vec.size(); vi++)
	{
		int x = cloud[vi].x;
		int y = cloud[vi].y;

		map[x][y] ++;
	}
}


void copy_water(vector<Pos>& cloud)
{
	for (int vi = 0; vi < cloud.size(); vi++)
	{
		int cx = cloud[vi].x;
		int cy = cloud[vi].y;
		int sum = 0;
		for (int dir = 1; dir < 8; dir += 2)
		{
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];

			if (0 <= nx && nx < N && 0 <= ny && ny < N)
			{
				if(map[nx][ny] > 0)
					sum++;
			}
		}
		map[cx][cy] += sum;
	}
}

void make_cloud(vector<Pos>& cloud, vector<Pos>& past_cloud)
{
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			if (map[xi][yi] >= 2)
			{
				bool newpoint = true;
				for (int pi = 0; pi < past_cloud.size(); pi++)
				{
					if (!(past_cloud[pi].x == xi && past_cloud[pi].y == yi))
					{
						newpoint &= true;
					}
					else
					{
						newpoint &= false;
					}
				}
				if (newpoint == true)
				{
					Pos cloud_pos;
					cloud_pos.x = xi;
					cloud_pos.y = yi;
					cloud.push_back(cloud_pos);
					map[xi][yi] -= 2;
				}
			}
		}
	}
}


void print_vec(vector<Pos> clouds)
{
	cout << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			bool cl = false;
			for (int vi = 0; vi < clouds.size(); vi++)
			{
				if (clouds[vi].x == xi && clouds[vi].y == yi)
				{
					cout << "c ";
					cl = true;
				}
			}
			if (cl == false)
			{
				cout << "* ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void print_map()
{
	cout << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cout << map[xi][yi] << " ";
		}
		cout << endl;
	}
	cout << endl;
}