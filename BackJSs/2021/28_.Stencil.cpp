#include<iostream>
#include<vector>

using namespace std;

#define CLOCKWISE 0
#define COUNTERCLOCKWISE 1

int result();
void avg_operation();
bool near_num_operation();
int rotate_idx(int twelve_idx, int k, int dir);
void print_vec();

int N = 0;
int M = 0;
int T = 0;

vector<int> stencil_vec[50];
int twv_idx_arr[50] = {0};
int stencil_cmd[50] = { 0 };
int amount_cmd[50] = { 0 };
int dir_cmd[50] = { 0 };

int main()
{
	cin >> N >> M >> T;

	for (int stencil_idx = 0; stencil_idx < N; stencil_idx++)
	{
		for (int num_idx = 0; num_idx < M; num_idx++)
		{
			int num = 0;
			cin >> num;
			stencil_vec[stencil_idx].push_back(num);
		}
	}

	for (int trial = 0; trial < T; trial++)
	{
		cin >> stencil_cmd[trial] >> dir_cmd[trial] >> amount_cmd[trial];
	}

	for (int trial = 0; trial < T; trial++)
	{
		int stencil_num = stencil_cmd[trial];
		int mul = 1;
		while (stencil_num *mul<= N)
		{
			int stencil_idx = stencil_num *mul -1;

			twv_idx_arr[stencil_idx] = rotate_idx(twv_idx_arr[stencil_idx], amount_cmd[trial] ,dir_cmd[trial]);

			mul++;
		}
		//print_vec();
		if (near_num_operation() == false)
		{
			avg_operation();
		}
		//print_vec();
	}

	//print_vec();
	cout << result();
	return 0;
}

int rotate_idx(int twelve_idx, int k ,int dir)
{
	if (dir == COUNTERCLOCKWISE)
	{
		twelve_idx += k;
		twelve_idx %= M;
	}
	else
	{
		twelve_idx-=k;
		if (twelve_idx<0)
		{
			twelve_idx%=M;
			twelve_idx = M + twelve_idx;
		}
	}
	return twelve_idx;
}

bool near_num_operation()
{	
	vector<int> tmp_stencil_vec[50];
	for (int i = 0; i < N; i++)
	{
		tmp_stencil_vec[i] = stencil_vec[i];
	}

	bool operated = false;
	for (int stencil_idx = 0; stencil_idx < N; stencil_idx++)
	{
		int near_stencil_bigger_idx = stencil_idx + 1;
		int near_stencil_lower_idx = stencil_idx - 1;
		for (int i = 0; i < M; i++)
		{
			int clock_idx = twv_idx_arr[stencil_idx] + i;
			clock_idx %= M;

			int near_bigger_clock_idx = rotate_idx(clock_idx, 1,CLOCKWISE);
			int near_lower_clock_idx = rotate_idx(clock_idx,1, COUNTERCLOCKWISE);

			int number = stencil_vec[stencil_idx][clock_idx];
			if (number != 0)
			{
				//cmp with clockwise
				//	모든 원판이 같을 때는?
				if (number == stencil_vec[stencil_idx][near_bigger_clock_idx])
				{
					tmp_stencil_vec[stencil_idx][clock_idx] = 0;
					tmp_stencil_vec[stencil_idx][near_bigger_clock_idx] = 0;
					operated |= true;
				}
				//cmp with couterclockwise
				if (number == stencil_vec[stencil_idx][near_lower_clock_idx])
				{
					tmp_stencil_vec[stencil_idx][near_lower_clock_idx] = 0;
					tmp_stencil_vec[stencil_idx][clock_idx] = 0;
					operated |= true;
				}

				//cmp with bigger stencil
				if (near_stencil_bigger_idx < N-1)
				{
					if (number == stencil_vec[near_stencil_bigger_idx][(twv_idx_arr[near_stencil_bigger_idx] + i) % M])
					{
						tmp_stencil_vec[near_stencil_bigger_idx][(twv_idx_arr[near_stencil_bigger_idx] + i) % M] = 0;
						tmp_stencil_vec[stencil_idx][clock_idx] = 0;
						operated |= true;
					}
				}
				//cmp with lower stencil
				if (near_stencil_lower_idx >= 0)
				{
					if (number == stencil_vec[near_stencil_lower_idx][(twv_idx_arr[near_stencil_lower_idx] + i) % M])
					{
						tmp_stencil_vec[near_stencil_lower_idx][(twv_idx_arr[near_stencil_lower_idx] + i) % M] = 0;
						tmp_stencil_vec[stencil_idx][clock_idx] = 0;
						operated |= true;
					}
				}
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		stencil_vec[i] = tmp_stencil_vec[i];
	}
	return operated;
}


void avg_operation()
{
	int sum = 0;
	int div_num = 0;
	for (int i = 0; i < N; i++)
	{
		for (int clk_idx = 0; clk_idx < M; clk_idx++)
		{
			sum += stencil_vec[i][clk_idx];
			if (stencil_vec[i][clk_idx] != 0)
			{
				div_num++;
			}
		}
	}

	float avg = (float)sum / (float)div_num;
	for (int i = 0; i < N; i++)
	{
		for (int clk_idx = 0; clk_idx < M; clk_idx++)
		{
			if ((float)stencil_vec[i][clk_idx] < avg && stencil_vec[i][clk_idx] != 0)
			{
				stencil_vec[i][clk_idx]++;
			}
			else if ((float)stencil_vec[i][clk_idx] > avg)
			{
				stencil_vec[i][clk_idx]--;
			}

		}
	}
}

int result()
{
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		for (int clk_idx = 0; clk_idx < M; clk_idx++)
		{
			sum += stencil_vec[i][clk_idx];
		}
	}
	return sum;
}

void print_vec()
{
	int sum = 0;
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		for (int clk_idx = 0; clk_idx < M; clk_idx++)
		{
			cout <<stencil_vec[i][(twv_idx_arr[i] + clk_idx) % M] << " ";
		}
		cout << endl;
	}
	cout << endl;
}