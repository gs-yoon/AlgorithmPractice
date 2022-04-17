#include <iostream>

using namespace std;


struct Shark
{
	int x=0;
	int y=0;
	int num=0;
	int priority[4][4] = { 0 };
	int dir = 0;
};
struct Smell
{
	int shark_num = 0;
	int remain = 0;
};
enum direction_e
{
	UP =0,
	DOWN,
	LEFT,
	RIGHT
};

void move_shark(int num);
void smell_down();
void smell();
void print_map();

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };


int N = 0;
int smell_k = 0;
int shark_max = 0;
Smell smell_map[20][20];
int shark_map[20][20];
Shark* shark_arr;
int rmn_shark;

int main()
{
	cin >> N >> shark_max >> smell_k;
	rmn_shark = shark_max;
	shark_arr = new Shark[shark_max];

	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> shark_map[xi][yi];
			if (shark_map[xi][yi] > 0)
			{
				shark_arr[shark_map[xi][yi] - 1].x = xi;
				shark_arr[shark_map[xi][yi] - 1].y = yi;
				shark_arr[shark_map[xi][yi] - 1].num = shark_map[xi][yi];
			}
		}
	}
	for (int i = 0; i < shark_max; i++)
	{
		cin >> shark_arr[i].dir;
		shark_arr[i].dir--;
	}

	for (int i = 0; i < shark_max; i++)
	{
		for (int cur_dir = 0; cur_dir < 4; cur_dir++)
		{
			for (int p = 0; p < 4; p++)
			{
				cin >> shark_arr[i].priority[cur_dir][p];
				shark_arr[i].priority[cur_dir][p]--;
			}
		}
	}
	int trial = 0;
	while (trial <= 1000)
	{
		trial++;
		smell();
		//print_map();
		for (int sn = 1; sn <= shark_max; sn++)
		{
			move_shark(sn);
		}
		if (rmn_shark == 1)
			break;

		smell_down();
		//print_map();
	}
	//print_map();

	if (trial > 1000)
	{
		trial = -1;
	}
	cout << trial;
}


void smell_down()
{
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			if (smell_map[xi][yi].remain > 0)
			{
				smell_map[xi][yi].remain--;
			}
		}
	}
}

void smell()
{
	for (int si = 0; si < shark_max; si++)
	{
		int cx = shark_arr[si].x;
		int cy = shark_arr[si].y;
		int num = shark_arr[si].num;
		if (num > 0)
		{
			smell_map[cx][cy].shark_num = num;
			smell_map[cx][cy].remain = smell_k;
		}
	}
}

void move_shark(int num)
{
	int si = num - 1;
	if (shark_arr[si].num <= 0)
		return;

	else if (shark_arr[si].num != num)
		cout << "fatalerror \n";

	int cur_dir = shark_arr[si].dir;
	int nx = 0;
	int ny = 0;
	int cx = shark_arr[si].x;
	int cy = shark_arr[si].y;
	int ndir = 0;
	bool found = false;

	// find empty smell space
	for (int di = 0; di < 4; di++)
	{
		ndir = shark_arr[si].priority[cur_dir][di];
		nx = cx + dx[ndir];
		ny = cy + dy[ndir];

		if (0 <= nx && nx < N && 0 <= ny && ny < N)
		{
			if (smell_map[nx][ny].remain == 0 || smell_map[nx][ny].remain == smell_k+1)
			{
				found = true;
				break;
			}
		}
	}
	// find my smell space
	if (found == false)
	{
		for (int di = 0; di < 4; di++)
		{
			ndir = shark_arr[si].priority[cur_dir][di];
			nx = cx + dx[ndir];
			ny = cy + dy[ndir];

			if (0 <= nx && nx < N && 0 <= ny && ny < N)
			{
				if (smell_map[nx][ny].shark_num == shark_arr[si].num)
				{
					found = true;
					break;
				}
			}
		}
	}

	// not to go
	if (found == false)
	{
		cout << "not found error" << endl;
	}
	else
	{
		if (0< shark_map[nx][ny] && shark_map[nx][ny] < num)
		{
			//int deadidx = si;
			shark_arr[si].num = -1;
			shark_map[cx][cy] = 0;
			rmn_shark--;
		}
		else
		{
			shark_map[nx][ny] = num;
			shark_map[cx][cy] = 0;
		}

		shark_arr[si].x = nx;
		shark_arr[si].y = ny;
		shark_arr[si].dir = ndir;
	}
}

void print_map()
{
	cout << endl;
	cout << "shark" << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cout << shark_map[xi][yi] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "smell" << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cout << smell_map[xi][yi].shark_num << "/";
			cout << smell_map[xi][yi].remain << " ";
		}
		cout << endl;
	}
	cout << endl;
}