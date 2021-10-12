#include<iostream>
#include<vector>

using namespace std;

enum direction_e
{
	RIGHT=0,
	LEFT,
	UP,
	DOWN
};

#define WHITE 0
#define RED 1
#define BLUE 2

struct Horse
{
	int x = 0;
	int y = 0;
	int id = 0;
	int dir = 0;
};

int reverse_dir(int dir);
vector<Horse>::iterator move(int nx, int ny, int cur_x, int cur_y, vector<Horse>::iterator itr);
void move_blue(int nx, int ny, int cur_x, int cur_y, vector<Horse>::iterator first_horse_itr);
void print_vec();

int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,-1,1 };

int N = 0;
int K = 0;
int g_map[15][15];
vector<Horse> horse_map[15][15];
vector<vector<Horse>::iterator> horse_itr_vec;

int main()
{
	cin >> N >> K;

	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> g_map[xi][yi];
			horse_map[xi][yi].reserve(15);
		}
	}

	for (int i = 0; i < K; i++)
	{
		Horse input_horse;
		int y = 0;
		int x = 0;
		cin >> y >> x >> input_horse.dir;
		input_horse.dir--;
		input_horse.id = i;
		x--;
		y--;
		input_horse.x = x;
		input_horse.y = y;
		horse_map[x][y].push_back(input_horse);
		horse_itr_vec.push_back(horse_map[x][y].begin());
	}

	bool keep_going = true;
	int trial = 0;
	while (keep_going)
	{
		if (trial > 1000)
		{
			trial = -1;
			break;
		}
		//print_vec();
		trial++;
		for (int i = 0; i < horse_itr_vec.size(); i++)
		{
			vector<Horse>::iterator first_horse_itr = horse_itr_vec[i];

			int cur_x = first_horse_itr->x;
			int cur_y = first_horse_itr->y;
			int nx = cur_x + dx[first_horse_itr->dir];
			int ny = cur_y + dy[first_horse_itr->dir];

			if (nx < 0 || nx >= N || ny < 0 || ny >= N)
			{
				first_horse_itr->dir = reverse_dir(first_horse_itr->dir);
				nx = cur_x + dx[first_horse_itr->dir];
				ny = cur_y + dy[first_horse_itr->dir];
				move_blue(nx, ny, cur_x, cur_y, first_horse_itr);
			}
			else if (g_map[nx][ny] == WHITE)
			{
				for (vector<Horse>::iterator itr = first_horse_itr; itr != horse_map[cur_x][cur_y].end(); )
				{
					itr = move(nx, ny, cur_x, cur_y, itr);
				}
			}
			else if(g_map[nx][ny] == RED)
			{
				for (vector<Horse>::iterator itr = horse_map[cur_x][cur_y].end()-1; itr != first_horse_itr ; )
				{
					itr = move(nx, ny, cur_x, cur_y, itr);
					itr--;
				}
				move(nx, ny, cur_x, cur_y, first_horse_itr);
			}
			else
			{
				first_horse_itr->dir = reverse_dir(first_horse_itr->dir);
				nx = cur_x + dx[first_horse_itr->dir];
				ny = cur_y + dy[first_horse_itr->dir];
				move_blue(nx, ny, cur_x, cur_y, first_horse_itr);
			}
			if (horse_map[nx][ny].size() >= 4)
			{
				keep_going = false;
				//print_vec();
				break;
			}
		}
	}

	cout << trial;
}

vector<Horse>::iterator move(int nx, int ny,int cur_x ,int cur_y, vector<Horse>::iterator itr)
{
	itr->x = nx;
	itr->y = ny;

	//값 복사
	horse_map[nx][ny].push_back(*itr);
	//새로저장
	horse_itr_vec.at(itr->id) = horse_map[nx][ny].end() - 1;

	// itr 삭제
	itr = horse_map[cur_x][cur_y].erase(itr);
	print_vec();
	return itr;
}

void move_blue(int nx, int ny, int cur_x, int cur_y, vector<Horse>::iterator first_horse_itr)
{

	if (!(nx < 0 || nx >= N || ny < 0 || ny >= N))
	{
		if (g_map[nx][ny] == WHITE)
		{
			for (vector<Horse>::iterator itr = first_horse_itr; itr != horse_map[cur_x][cur_y].end(); )
			{
				itr = move(nx, ny, cur_x, cur_y, itr);
			}
		}
		else if (g_map[nx][ny] == RED)
		{
			for (vector<Horse>::iterator itr = horse_map[cur_x][cur_y].end() - 1; itr != first_horse_itr; )
			{
				itr = move(nx, ny, cur_x, cur_y, itr);
				itr--;
			}
			move(nx, ny, cur_x, cur_y, first_horse_itr);
		}
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

void print_vec()
{
	cout << endl;
	for (int i = 0; i < horse_itr_vec.size(); i++)
	{
		cout << "id = " << horse_itr_vec.at(i)->id << " x = " << horse_itr_vec.at(i)->x << " y = " << horse_itr_vec.at(i)->y << " dir = ";
		if( horse_itr_vec.at(i)->dir == UP)
			cout << "UP" << endl;
		if (horse_itr_vec.at(i)->dir == DOWN)
			cout << "DOWN" << endl;
		if (horse_itr_vec.at(i)->dir == RIGHT)
			cout << "RIGHT" << endl;
		if (horse_itr_vec.at(i)->dir == LEFT)
			cout << "LEFT" << endl;
	}
	cout << endl;
	for (int yi =0 ; yi < N ;yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			int s = 1;
			int cnt = 0;
			for (int i = 0; i < horse_map[xi][yi].size(); i++)
			{
				cout << horse_map[xi][yi].at(i).id;
				s = 0;
				cnt++;
			}
			if (s == 1)
			{
				if (g_map[xi][yi] == RED)
					cout << "R";
				if (g_map[xi][yi] == BLUE)
					cout << "B";
				if (g_map[xi][yi] == WHITE)
					cout << "W";
				cout << "    ";
			}
			else
			{
				for (int i = 0; i < 5 - cnt; i++)
					cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
