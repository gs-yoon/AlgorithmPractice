#include<iostream>
#include<vector>

using namespace std;

#define CLOCKWISE 0
#define COUNTERCLOCKWISE 1

int N = 0;
int M = 0;
int T = 0;

vector<int> stencil_vec[50];
int command[50][3] = { 0 };
int twv_idx_arr[50] = {0};

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

}

int rotate_idx(int twelve_idx, int dir)
{
	if (dir == CLOCKWISE)
	{
		twelve_idx++;
		twelve_idx %= M;
	}
	else
	{
		twelve_idx--;
		if (twelve_idx<0)
		{
			twelve_idx = M - 1;
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
		int clock_idx = twv_idx_arr[stencil_idx];
		for (int i = 0; i < M; i++)
		{
			clock_idx += i;
			clock_idx %= M;

			int near_bigger_clock_idx = rotate_idx(clock_idx, CLOCKWISE);
			int near_lower_clock_idx = rotate_idx(clock_idx, COUNTERCLOCKWISE);

			int number = stencil_vec[stencil_idx][clock_idx];
			if (number != 0)
			{
				//cmp clock
				//	모든 원판이 같을 때는?
				if (number == stencil_vec[stencil_idx][near_bigger_clock_idx])
				{
					tmp_stencil_vec[stencil_idx][clock_idx] = 0;
					tmp_stencil_vec[stencil_idx][near_bigger_clock_idx] = 0;
					operated = true;
				}
				if (number == stencil_vec[stencil_idx][near_lower_clock_idx])
				{
					tmp_stencil_vec[stencil_idx][near_lower_clock_idx] = 0;
					tmp_stencil_vec[stencil_idx][clock_idx] = 0;
					operated = true;
				}

				//cmp stencil
				if (near_stencil_bigger_idx < N)
				{
					if (number == stencil_vec[near_stencil_bigger_idx][(twv_idx_arr[near_stencil_bigger_idx] + i) % M])
					{
						tmp_stencil_vec[near_stencil_bigger_idx][(twv_idx_arr[near_stencil_bigger_idx] + i) % M] = 0;
						tmp_stencil_vec[stencil_idx][clock_idx] = 0;
					}
				}
				if (near_stencil_lower_idx >= 0)
				{
					if (number == stencil_vec[near_stencil_lower_idx][(twv_idx_arr[near_stencil_lower_idx] + i) % M])
					{
						tmp_stencil_vec[near_stencil_lower_idx][(twv_idx_arr[near_stencil_lower_idx] + i) % M] = 0;
						tmp_stencil_vec[stencil_idx][clock_idx] = 0;
					}
				}
			}
		}
	}
}