#include <iostream>
#include <vector>

using namespace std;

#define DEBUG 1

struct AllyInfo
{
	int num_of_country = 0;
	int num_of_population = 0;
	int avg_of_population = 0;
};

int do_population_movement(int map[50][50], int ally_map[50][50], vector<AllyInfo>* ally_vec);
int check_population(int prev, int cur);
int check_ally__(int x, int y, int prev_population, int map[50][50], int in_ally_map[50][50], int ally_num, AllyInfo* ally_info);
bool check_ally(int map[50][50], int ally_map[50][50], vector<AllyInfo>* ally_vec);
void print_map(int map[50][50], const char* msg);

enum DIR
{
	UP =0,
	LEFT,
	DOWN,
	RIGHT
};

int dx[] = { 0, -1, 0, 1 };
int dy[] = { -1, 0, 1, 0 };

int L = 0;
int R = 0;
int N = 0;
int map[50][50] = { 0 };

int main()
{
	cin >> N >> L >> R;

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> map[x][y];
		}
	}

	bool condition = true;
	int elapsed_day = 0;
	print_map(map, "INPUT MAP");
	while (condition)
	{
		int ally_map[50][50] = { 0 };
		vector<AllyInfo> ally_vec;
		int status = 0;

		status = check_ally(map, ally_map, &ally_vec);
		print_map(ally_map, "ALLY MAP");

		if (status > 0)
		{
			do_population_movement(map, ally_map, &ally_vec);
			print_map(map, "AFTER MOVMENT");
			elapsed_day++;
		}
		else
		{
			condition = false;
		}
	}

	cout << elapsed_day;
}

bool check_ally(int map[50][50], int ally_map[50][50], vector<AllyInfo>* ally_vec)
{
	int ally_num = 1;
	bool rst = 0;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (ally_map[x][y] == 0)
			{
				AllyInfo ally_info;
				int status = 0;
				status = check_ally__(x, y, -1 , map, ally_map, ally_num ,&ally_info);

				if (status > 0)
				{
					ally_num++;
					ally_vec->push_back(ally_info);
				}
			}
		}
	}
	if (ally_num -1 != ally_vec->size())
	{
		rst = false;
		cout << "!!ERROR is occured while checking allias. !!" << endl;
		cout << "!!ERROR ally_num = " << ally_num << "\nsize of ally_vec = " << ally_vec->size() << endl;
	}
	else
	{
		if (ally_vec->size() > 0)
			rst = true;
	}
	return rst;
}

int check_ally__(int x, int y, int prev_population ,int map[50][50], int ally_map[50][50], int ally_num , AllyInfo *ally_info)
{
	int status = 1;

	// find ally
	if ( prev_population == -1 || check_population(prev_population, map[x][y]))
	{
		ally_map[x][y] = ally_num;
		ally_info->num_of_country += 1;
		ally_info->num_of_population += map[x][y];

		for (int dir = 0; dir < 4; dir++)
		{
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (0 <= nx && nx < N && 0 <= ny && ny < N)
			{
				if (ally_map[nx][ny] == 0)
				{
					check_ally__(nx, ny, map[x][y], map, ally_map, ally_num, ally_info);
				}
			}
		}
	}

	// if no ally
	if (ally_info->num_of_country == 1) //revert
	{
		ally_map[x][y] = 0;
		status = 0;
	}
	return status;
}

int check_population(int prev, int cur)
{
	int diff = abs(prev - cur);
	if (L <= diff && diff <= R)
		return true;
	else
		return false;
}

int do_population_movement(int map[50][50], int ally_map[50][50], vector<AllyInfo> *ally_vec)
{
	int status = true;
	int total_ally_country= 0;

	//pre_calc of avg
	for (int vi = 0; vi < ally_vec->size(); vi++)
	{
		ally_vec->at(vi).avg_of_population = ally_vec->at(vi).num_of_population / ally_vec->at(vi).num_of_country;
		total_ally_country += ally_vec->at(vi).num_of_country;
	}

	//popluation movemnt algo
	int cnt_for_err_check = 0;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			int ally_idx = ally_map[x][y] -1;
			if (0<= ally_idx && ally_idx < ally_vec->size())
			{
				map[x][y] = ally_vec->at(ally_idx).avg_of_population;
				cnt_for_err_check++;
			}
			else if (ally_idx >= (int)ally_vec->size())
			{
				cout << "ERROR, idx of ally_vec has overflow\n";
				cout << "ERROR, x =" << x << " y = " << y << " ally num = " << ally_map[x][y] << " ally vec size " << ally_vec->size() << "\n";
				print_map(ally_map, "ERROR ALLY MAP");
			}
		}
	}

	//error check
	if (cnt_for_err_check == total_ally_country)
	{
		status = true;
	}
	else
	{
		cout << "!!ERROR in population movemnet !!\n";
		status = false;
	}

	return status;
}

void print_map(int map[50][50], const char* msg)
{
#if DEBUG
	cout << msg << endl;

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cout << map[x][y] << " ";
		}
		cout << endl;
	}
	cout << endl;
#endif
}