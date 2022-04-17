#include<iostream>
#include<queue>
using namespace std;

#define GOTOCUS 0
#define GOTOGOAL 1
enum driection_e
{
	UP=0,
	LEFT,
	DOWN,
	RIGHT
};

struct Customer
{
	int num = 0;
	int start_x = 0;
	int start_y = 0;
	int goal_x = 0;
	int goal_y = 0;
};

struct Taxi
{
	int x = 0;
	int y = 0;
	long int gasoline = 0;
	int moving_dist = 0;
};

bool move_taxi(Taxi in_taxi, int cur_customer_idx, int type, Taxi& rst_taxi, int& rst_customer_idx);
void print_map(Taxi taxi);

int dx[] = { 0,-1,0,1 };
int dy[] = { -1,0,1,0 };

int N = 0;
int M = 0;
long int gasoline = 0;
int map[20][20] = { 0 };
int remain_cs = 0;
Customer* customers;
Taxi taxi;
int customer_map[20][20] = { 0 };
int main()
{
	cin >> N >> M >> gasoline;
	taxi.gasoline = gasoline;
	customers = new Customer[M];
	remain_cs = M;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> map[xi][yi];
		}
	}

	cin >> taxi.y;
	cin >> taxi.x;
	taxi.y--;
	taxi.x--;

	for (int i = 0; i < M; i++)
	{
		customers[i].num = i+1;
		cin >> customers[i].start_y;
		cin >> customers[i].start_x;
		cin >> customers[i].goal_y;
		cin >> customers[i].goal_x;
		customers[i].start_y--;
		customers[i].start_x--;
		customers[i].goal_y--;
		customers[i].goal_x--;

		customer_map[customers[i].start_x][customers[i].start_y] = customers[i].num;
	}
	//print_map(taxi);

	bool keep_going = true;
	Taxi result_taxi = taxi;
	int result_cs_idx =0;
	while (keep_going)
	{
		bool success = 0;
		Taxi update_taxi = result_taxi;
		success = move_taxi(update_taxi, -1, GOTOCUS, result_taxi, result_cs_idx);
		//print_map(result_taxi);
		if (!success)
			keep_going = false;
		else
		{
			update_taxi = result_taxi;
			int update_cs_idx = result_cs_idx;
			success = move_taxi(update_taxi, update_cs_idx, GOTOGOAL, result_taxi, result_cs_idx);
			//print_map(result_taxi);
		}

		if (!success)
			keep_going = false;

		if (remain_cs == 0)
			keep_going = false;
	}

	if (remain_cs == 0)
	{
		cout << result_taxi.gasoline;
	}
	else if (remain_cs < 0)
	{
		cout << "fatalerror\n";
	}
	else
	{
		cout << -1;
	}
}


bool move_taxi(Taxi in_taxi, int cur_customer_idx, int type, Taxi& rst_taxi, int& rst_customer_idx)
{
	bool found = false;
	bool visited[20][20] = { 0 };
	queue<Taxi> taxi_q;
	Taxi result_taxi;
	Customer cur_customer;
	int goal_x = -1;
	int goal_y = -1;
	if (type == GOTOGOAL)
	{
		cur_customer = customers[cur_customer_idx];
		goal_x = cur_customer.goal_x;
		goal_y = cur_customer.goal_y;
	}
	taxi_q.push(in_taxi);
	visited[in_taxi.x][in_taxi.y] = 1;
	while (!taxi_q.empty())
	{
		Taxi cur_taxi = taxi_q.front(); taxi_q.pop();

		int cx = cur_taxi.x;
		int cy = cur_taxi.y;
		if (type == GOTOCUS)
		{
			if (customer_map[cx][cy] > 0)
			{
				found = true;
				result_taxi = cur_taxi;
				break;
			}
		}
		else
		{
			if (cx == goal_x && cy == goal_y)
			{
				found = true;
				result_taxi = cur_taxi;
				break;
			}
		}


		for (int dir = 0; dir < 4; dir++)
		{
			int nx = 0;
			int ny = 0;
			nx = cur_taxi.x + dx[dir];
			ny = cur_taxi.y + dy[dir];

			if (0 <= nx && nx < N && 0 <= ny && ny < N)
			{
				if (map[nx][ny] != 1 && visited[nx][ny] != 1)
				{
					Taxi next_taxi;
					next_taxi.x = nx;
					next_taxi.y = ny;
					next_taxi.gasoline = cur_taxi.gasoline - 1;
					next_taxi.moving_dist = cur_taxi.moving_dist + 1;

					if (next_taxi.gasoline >= 0)
					{
						visited[nx][ny] = 1;
						taxi_q.push(next_taxi);
					}
				}
			}
		}
	}

	if (found == true && type == GOTOCUS)
	{
		while (!taxi_q.empty())
		{
			Taxi cmp_taxi = taxi_q.front(); taxi_q.pop();
			int cmp_x = cmp_taxi.x;
			int cmp_y = cmp_taxi.y;
			if (result_taxi.moving_dist >= cmp_taxi.moving_dist && customer_map[cmp_x][cmp_y] > 0)
			{
				if (result_taxi.y > cmp_taxi.y)
				{
					result_taxi = cmp_taxi;
				}
				else if (result_taxi.y == cmp_taxi.y)
				{
					if (result_taxi.x > cmp_taxi.x)
					{
						result_taxi = cmp_taxi;
					}
				}
			}
		}
		rst_customer_idx = customer_map[result_taxi.x][result_taxi.y] - 1;
		customer_map[result_taxi.x][result_taxi.y] = 0;
		result_taxi.moving_dist = 0;
	}
	else if (found == true && type == GOTOGOAL)
	{
		result_taxi.gasoline += result_taxi.moving_dist * 2;
		result_taxi.moving_dist = 0;
		remain_cs--;
	}

	rst_taxi = result_taxi;
	return found;
}

void print_map(Taxi taxi)
{
	cout << endl;
	cout << "gasoline : " << taxi.gasoline << endl;
	cout << "mv_dst: " << taxi.moving_dist<< endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			if (xi == taxi.x && yi == taxi.y)
			{
				cout << "t ";
			}
			else if (map[xi][yi] == 1)
			{
				cout << "* ";
			}
			else
			{
				cout << customer_map[xi][yi] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}