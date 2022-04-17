#include <iostream>

using namespace std;

#define MAX 100

enum direction_e
{
	UP=0,
	DOWN,
	LEFT,
	RIGHT
};
bool make_ramp(int start_x, int start_y, int dir);
void print_map();

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

int N = 0;
int L = 0;
int map[MAX][MAX] = { 0 };
bool ramp_map[MAX][MAX] = { 0 };

int main()
{
	cin >> N;
	cin >> L;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> map[xi][yi];
		}
	}
	
	//make ramp
	//right
	int road_num = 0;
	for (int yi = 0; yi < N; yi++)
	{
		bool goSuccess = true;
		int last_hegiht = map[0][yi];
		for (int xi = 1; xi < N; xi++)
		{
			if ( (map[xi][yi] - last_hegiht) == 1)
			{
				goSuccess &= make_ramp(xi-1, yi, LEFT);
			}
			else if ( (map[xi][yi] - last_hegiht) == -1)
			{
				goSuccess &= make_ramp(xi, yi, RIGHT);
			}
			else if ( (map[xi][yi] - last_hegiht) <= -2 || (map[xi][yi] - last_hegiht) >= 2)
			{
				goSuccess = false;
				break;
			}
			last_hegiht = map[xi][yi];

			if (goSuccess == false)
				break;
		}
		if (goSuccess == true)
		{
			road_num++;
			print_map();
		}
		for (int xi = 0; xi < N; xi++)
			ramp_map[xi][yi] = false;
	}

	//down
	for (int xi = 0; xi < N; xi++)
	{
		bool goSuccess = true;
		int last_hegiht = map[xi][0];
		for (int yi = 1; yi < N; yi++)
		{
			if ((map[xi][yi] - last_hegiht) == 1)
			{
				goSuccess &= make_ramp(xi, yi-1, UP);
			}
			else if ((map[xi][yi] - last_hegiht) == -1)
			{
				goSuccess &= make_ramp(xi, yi, DOWN);
			}
			else if ((map[xi][yi] - last_hegiht) <= -2 || (map[xi][yi] - last_hegiht) >= 2)
			{
				goSuccess = false;
				break;
			}
			last_hegiht = map[xi][yi];

			if (goSuccess == false)
				break;
		}
		if (goSuccess == true)
		{
			road_num++;
			print_map();
		}
		for (int yi = 0; yi < N; yi++)
			ramp_map[xi][yi] = false;
	}

	cout << road_num;
}

bool make_ramp(int start_x, int start_y, int dir)
{
	bool success = true;
	if (ramp_map[start_x][start_y] == true)
		return false;

	int next_x = start_x;
	int next_y = start_y;
	for (int i = 1; i < L; i++)
	{
		next_x = next_x + dx[dir];
		next_y = next_y + dy[dir];
		if (0 <= next_x && next_x < N && 0 <= next_y && next_y < N)
		{
			if (map[start_x][start_y] == map[next_x][next_y] && ramp_map[next_x][next_y] == false)
			{
				success &= true;
			}
			else
			{
				success &= false;
				break;
			}
		}
		else
		{
			success &= false;
			break;
		}
	}
	if (success)
	{
		next_x = start_x;
		next_y = start_y;
		for (int i = 1; i < L; i++)
		{
			next_x = next_x + dx[dir];
			next_y = next_y + dy[dir];

			if (map[start_x][start_y] == map[next_x][next_y])
			{
				ramp_map[next_x][next_y] = true;
			}
			else
			{
				success = false;
				break;
			}
		}
		ramp_map[start_x][start_y] = true;
	}
	return success;
}

void print_map()
{
	cout << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cout << ramp_map[xi][yi];
		}
		cout << endl;
	}
	cout << endl;
}