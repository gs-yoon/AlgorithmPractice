#include <iostream>

using namespace std;

#define DEPARTURE 50
#define ARRIVAL 51
#define EXTERNAL 0
#define INTERNAL 1
int dice_nums[10] = {0};

struct Cell
{
	int num = 0;
	Cell* link = nullptr;
	int map_size = 0;
	int map_flag;
};

struct Horse
{
	int num = DEPARTURE;
	int map_flag = EXTERNAL;
	int idx = 0;
	Cell* map;
};
int move_atom(Horse& target,Horse local_horses[4], int next_idx);
void move(int horse_idx, Horse target_arr[4], int dice_idx, int sum, int trial);
void print_horse(Horse inhorses[4]);

int g_max = 0;
Cell external[22];
Cell internal_10[8];
Cell internal_20[7];
Cell internal_30[8];
Horse horses[4];
int dice_num_arr[10];
int main()
{
	for (int i = 0; i < 10; i++)
	{
		cin >> dice_num_arr[i];
	}
	external[0].num = DEPARTURE;
	external[21].num = ARRIVAL;
	external[0].map_size = 22;
	external[21].map_size = 22;

	for (int i = 0; i < 4; i++)
	{
		horses[i].map = external;
	}

	for (int i = 1; i <= 20; i++)
	{
		external[i].map_size = 22;
		external[i].num = i * 2;
		if (i * 2 == 10)
		{
			external[i].link = internal_10;
		}
		else if (i * 2 == 20)
		{
			external[i].link = internal_20;
		}
		else if (i * 2 == 30)
		{
			external[i].link = internal_30;
		}
	}

	int s_10 = 13;
	int s_20 = 22;
	int s_30 = 28;
	for (int i = 0; i < 3; i++)
	{
		internal_10[i].num = s_10 + i * 3;
		internal_10[i].map_size = 8;
		internal_30[i].num = s_30 - i;
		internal_30[i].map_size = 8;
	}
	for (int i = 0; i < 2; i++)
	{
		internal_20[i].num = s_20 + i * 2;
		internal_20[i].map_size = 7;
	}
	int s = 10;
	for (int i = 3; i < 7; i++)
	{
		internal_10[i].num = s + i * 5;
		internal_20[i-1].num = s + i * 5;
		internal_30[i].num = s + i * 5;
	}
	internal_10[7].num = ARRIVAL;
	internal_20[6].num = ARRIVAL;
	internal_30[7].num = ARRIVAL;

	internal_10[0].map_flag= INTERNAL;
	internal_20[0].map_flag = INTERNAL;
	internal_30[0].map_flag = INTERNAL;
	external[0].map_flag = EXTERNAL;

	move(0,horses, 0, 0, 0);

	cout << g_max;
}


void move(int horse_idx, Horse target_arr[4], int dice_idx, int sum, int trial)
{
	if (target_arr[horse_idx].num == ARRIVAL)
		return;
	if (trial < 10)
	{
		Horse local_horses[4];
		for (int i = 0;i <4 ; i++)
		{
			local_horses[i] = target_arr[i];
		}
		Horse target = local_horses[horse_idx];
		
		trial++;
		int dice_num = dice_num_arr[dice_idx];
		dice_idx++;

		int next_idx = target.idx + dice_num;
		int rst;
		if (target.map[target.idx].link == nullptr)
		{
			rst = move_atom(target,local_horses, next_idx);
		}
		else
		{
			Cell* tempptr;
			tempptr = target.map;
			target.map = target.map[target.idx].link;
			int tempidx = target.idx;
			target.map_flag = INTERNAL;

			next_idx = dice_num - 1;
			rst = move_atom(target, local_horses, next_idx);
			if (rst < 0)
			{
				target.map_flag == EXTERNAL;
				target.map = tempptr;
				target.idx = tempidx;
			}
		}

		if (rst < 0)
			return;

		else if(rst <= 40)
		{
			sum += rst;
		}
		local_horses[horse_idx] = target;
		//print_horse(local_horses);
		for (int i = 0; i < 4; i++)
		{
			move(i ,local_horses, dice_idx, sum, trial);
		}
	}
	else
	{
		if (sum > g_max)
		{
			g_max = sum;
		}
	}
}

int move_atom(Horse& target, Horse local_horses[4], int next_idx)
{
	bool go = true;
	int next_num;
	if (next_idx < target.map->map_size-1)
	{
		next_num = target.map[next_idx].num;
		for (int i = 0; i < 4; i++)
		{
			if (local_horses[i].num == next_num && local_horses[i].map_flag == target.map->map_flag && local_horses[i].num < 40)
			{
				go &= false;
			}
			else if (local_horses[i].num ==40 && next_num == 40)
			{
				go &= false;
			}
			else
			{
				go &= true;
			}
		}
		if (go == true)
		{
			target.idx = next_idx;
			target.num = next_num;
			return next_num;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		target.num = ARRIVAL;
		target.idx = target.map->map_size - 1;
		return ARRIVAL;
	}
}

void print_horse(Horse inhorses[4])
{
	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << i << "th num : "<< inhorses[i].num << endl;;
		if(inhorses[i].map_flag == EXTERNAL)
			cout << i << "th map : EXTERNAL "<< endl;
		else
			cout << i << "th map : INTERNAL " << endl;
	}
	cout << endl;
}