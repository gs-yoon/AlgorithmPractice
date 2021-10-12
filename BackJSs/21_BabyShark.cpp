#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

struct shark {
	int x = 0;
	int y = 0;
	int elapsed_time = 0;
	int trial = 0;
};

enum direction_e
{
	UP=0,
	LEFT,
	RIGHT,
	DOWN
};

bool cmp(int x, int y)
{
	return x > y;
}
bool move_shark();
void print_map();

int dx[] = { 0,-1,1,0 };
int dy[] = { -1,0,0,1 };

vector<int> other_shark_age;
int N = 0;
int g_map[20][20];
int g_baby_shark_age = 2;
int g_baby_shark_feeding = 0;
shark g_baby_shark;
int elapsed_time = 0;

int main()
{
	other_shark_age.reserve(400);
	cin >> N;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> g_map[xi][yi];
			if (g_map[xi][yi] == 9)
			{
				g_baby_shark.x = xi;
				g_baby_shark.y = yi;
				g_map[xi][yi] = 0;
			}
			else if (g_map[xi][yi] > 0)
			{
				other_shark_age.push_back(g_map[xi][yi]);
			}
		}
	}
	sort(other_shark_age.begin(), other_shark_age.end(),cmp);

	bool keep_going = true;
	while(keep_going)
	{
		keep_going = false;
		if (other_shark_age.size() > 0)
		{
			if (other_shark_age.at(other_shark_age.size() - 1) < g_baby_shark_age)
			{
				keep_going = move_shark();
				//print_map();
			}
		}
	}
	
	cout << g_baby_shark.elapsed_time;

}

bool move_shark()
{
	queue<shark> baby_shark_q;
	shark target;
	target.y = 99;
	target.x = 99;
	baby_shark_q.push(g_baby_shark);
	bool visited[20][20] = { 0 };
	int success = false;
	int trial = 9999;
	while (!baby_shark_q.empty())
	{
		shark cur_shark = baby_shark_q.front(); baby_shark_q.pop();
		if ( 0 < g_map[cur_shark.x][cur_shark.y]  && g_map[cur_shark.x][cur_shark.y] < g_baby_shark_age)
		{
			if (cur_shark.trial <= trial)
			{
				if (cur_shark.y < target.y)
				{
					target = cur_shark;
				}
				else if (cur_shark.y == target.y)
				{
					if (cur_shark.x < target.x)
					{
						target = cur_shark;
					}
				}
				success = true;
				trial = target.trial;
			}
		}

		if (success == false)
		{
			for (int dir = 0; dir < 4; dir++)
			{
				shark next_shark;
				next_shark.x = cur_shark.x + dx[dir];
				next_shark.y = cur_shark.y + dy[dir];
				next_shark.elapsed_time = cur_shark.elapsed_time + 1;
				next_shark.trial = cur_shark.trial + 1;

				if (0 <= next_shark.x && next_shark.x < N && 0 <= next_shark.y && next_shark.y < N && g_map[next_shark.x][next_shark.y] <= g_baby_shark_age && visited[next_shark.x][next_shark.y] == 0)
				{
					visited[next_shark.x][next_shark.y] = 1;
					baby_shark_q.push(next_shark);
				}
			}
		}
	}

	if (success)
	{
		g_baby_shark_feeding++;
		if (g_baby_shark_feeding == g_baby_shark_age)
		{
			g_baby_shark_age++;
			g_baby_shark_feeding = 0;
		}
		g_baby_shark = target;

		vector<int>::iterator itr;
		itr = find(other_shark_age.begin(), other_shark_age.end(), g_map[target.x][target.y]);
		other_shark_age.erase(itr);

		g_map[target.x][target.y] = 0;
		return true;
	}
	else
	{	
		return false;
	}
}

void print_map()
{
	cout << endl;
	cout << g_baby_shark_age << endl;;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			if (g_baby_shark.x == xi && g_baby_shark.y == yi)
				cout << "s" << " ";
			else
				cout << g_map[xi][yi] << " ";
		}
		cout << endl;
	}
	cout << endl;

}