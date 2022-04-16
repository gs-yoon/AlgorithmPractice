#include <iostream>
#include <vector>
#include <list>

using namespace std;

int N = 0;
int M = 0;
int K = 0;
struct Pos
{
	int x = 0;
	int y = 0;
};

struct FireBall
{
	int x = 0;
	int y = 0;
	int m = 0;
	int dir = 0;
	int v = 0;
};
void moveFireBall();

int dx[] = {  0, 1, 1, 1, 0, -1, -1, -1 };
int dy[] = { -1,-1, 0, 1, 1,  1,  0, -1 };

vector<list<FireBall>::iterator> idx_map[50][50];
list<FireBall> fireball_list;

int main()
{
	cin >> N >> M >> K;


	for (int i = 0; i < M; i++)
	{
		FireBall in_fireball;
		cin >> in_fireball.y;
		cin >> in_fireball.x;
		cin >> in_fireball.m;
		cin >> in_fireball.v;
		cin >> in_fireball.dir;
		in_fireball.y--;
		in_fireball.x--;
		fireball_list.push_back(in_fireball);
	}

	for (int i = 0; i < K; i++)
	{
		moveFireBall();
	}
	int sum = 0;
	for (list<FireBall>::iterator fi = fireball_list.begin(); fi != fireball_list.end(); fi++)
	{
		sum += fi->m;
	}
	cout << sum;
}


void moveFireBall()
{
	bool visited[50][50] = { 0 };
	vector<Pos> merging_vec;

	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			idx_map[xi][yi].clear();
		}
	}

	//일단이동
	for (list<FireBall>::iterator fi = fireball_list.begin(); fi != fireball_list.end(); fi++)
	{
		int dir = fi->dir;
		int cv = fi->v;
		int cx = fi->x;
		int cy = fi->y;
		int nx = cx + dx[dir]*cv;
		int ny = cy + dy[dir]*cv;

		if (!(0 <= nx && nx < N && 0 <= ny && ny < N))
		{
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
		}

		if (0 <= nx && nx < N && 0 <= ny && ny < N)
		{
			fi->x = nx;
			fi->y = ny;

			if (idx_map[nx][ny].size() ==0 )
			{
				idx_map[nx][ny].push_back(fi);
			}
			else
			{
				idx_map[nx][ny].push_back(fi);

				if (visited[nx][ny] == 0)
				{
					visited[nx][ny] = 1;
					Pos mpos;
					mpos.x = nx;
					mpos.y = ny;

					merging_vec.push_back(mpos);
				}
			}
		}
		else
		{
			cout << "fatal_error\n";
		}

	}

	//합쳐진 것들
	for (int i = 0; i < merging_vec.size(); i++)
	{
		int mx = merging_vec[i].x;
		int my = merging_vec[i].y;

		FireBall merged_fire_ball;
		merged_fire_ball.m = 0;
		merged_fire_ball.v = 0;
		int num = 0;
		bool iseven = true;
		bool isodd = true;
		for (int mi = 0; mi < idx_map[mx][my].size(); mi++)
		{
			list<FireBall>::iterator mitr = idx_map[mx][my][mi];
			merged_fire_ball.m += mitr->m;
			merged_fire_ball.v += mitr->v;
			num++;
			if (mitr->dir % 2 == 0)
			{
				iseven &= 1;
				isodd &= 0;
			}
			else
			{
				iseven &= 0;
				isodd &= 1;
			}

			fireball_list.erase(mitr);
		}
		//맵에서 기존에 있던거 다 지우기
		//idx_map[mx][my].clear();
		//4개로나누기
		for (int ni = 0; ni < 4; ni++)
		{
			FireBall div_fire_ball;
			div_fire_ball.m = merged_fire_ball.m / 5;
			if (div_fire_ball.m <= 0)
				break;

			div_fire_ball.x = mx;
			div_fire_ball.y = my;
			div_fire_ball.v = merged_fire_ball.v / num;
			if (isodd || iseven)
			{
				div_fire_ball.dir = ni * 2;
			}
			else
			{
				div_fire_ball.dir = (ni+1) * 2 -1;
			}
			fireball_list.push_back(div_fire_ball);
		}
	}
}