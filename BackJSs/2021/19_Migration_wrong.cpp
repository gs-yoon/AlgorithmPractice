#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

enum direction_e
{
	LEFT =0 ,
	UP,
	RIGHT,
	DOWN
};
void print_map(int input_map[50][50]);

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };
int N = 0;
int L = 0;
int R = 0;
int map[50][50] = { 0 };

int main()
{
	cin >> N >> L >> R;

	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> map[xi][yi];
		}
	}

	int trial = 0;
	bool move_flag = true;
	while (move_flag == true)
	{
		move_flag = false;
		//vector<vector<int*>> alias_vec;
		//vector<vector<int*>> alias_ID_vec;
		//vector<int> dead_alias_vec;
		int*** alias_vec;
		short int*** alias_ID_vec;
		int* dead_alias_vec;
		int make_size = N * N;
		alias_vec = new int** [make_size/2];
		alias_ID_vec = new short int** [make_size/2];
		dead_alias_vec = new int [make_size];
		for (int i = 0; i < make_size/2; i++)
		{
			alias_vec[i] = new int* [make_size];
			alias_ID_vec[i] = new short int* [make_size];
		}
		short int alias_vec_size[2500] = {0};
		short int alias_ID_vec_size[2500] = {0};
		short int dead_alias_vec_size = 0;

		short int alias_map[50][50] = {0};
		int alias_num = 0;
		int alias_num_idx = 0;
		for (int yi = 0; yi < N; yi++)
		{
			for (int xi = 0; xi < N; xi++)
			{
				for (int dir = 0; dir < 2; dir++)
				{
					int srh_x = xi + dx[dir];
					int srh_y = yi + dy[dir];

					if (0 <= srh_x && srh_x < N && 0 <= srh_y && srh_y < N)
					{
						int diff = abs(map[srh_x][srh_y] - map[xi][yi]);
						if (L <= diff && diff <= R)
						{
							//print_map(alias_map);
							move_flag = true;
							if (alias_map[srh_x][srh_y] == 0 && alias_map[xi][yi] == 0)
							{
								alias_num++;
								alias_map[xi][yi] = alias_num;
								alias_map[srh_x][srh_y] = alias_num;

								alias_vec[alias_num_idx][alias_vec_size[alias_num_idx]] = &map[xi][yi];
								alias_vec_size[alias_num_idx]++;
								alias_vec[alias_num_idx][alias_vec_size[alias_num_idx]] = &map[srh_x][srh_y];
								alias_vec_size[alias_num_idx]++;

								alias_ID_vec[alias_num_idx][alias_ID_vec_size[alias_num_idx]] = &alias_map[xi][yi];
								alias_ID_vec_size[alias_num_idx]++;
								alias_ID_vec[alias_num_idx][alias_ID_vec_size[alias_num_idx]] = &alias_map[srh_x][srh_y];
								alias_ID_vec_size[alias_num_idx]++;

								alias_num_idx++;

							}
 							else
							{
								int alias_id = 0;
								if (alias_map[xi][yi] == 0)
								{
									alias_id = alias_map[srh_x][srh_y];
									alias_vec[alias_id - 1][alias_vec_size[alias_id - 1]] = &map[xi][yi];
									alias_vec_size[alias_id - 1]++;
									alias_ID_vec[alias_id-1][alias_ID_vec_size[alias_id - 1]] = &alias_map[xi][yi];
									alias_ID_vec_size[alias_id - 1]++;
								}
								else if (alias_map[srh_x][srh_y] ==0)
								{
									alias_id = alias_map[xi][yi];
									alias_vec[alias_id - 1][alias_vec_size[alias_id - 1]] = &map[srh_x][srh_y];
									alias_vec_size[alias_id - 1]++;
									alias_ID_vec[alias_id - 1][alias_ID_vec_size[alias_id - 1]] = &alias_map[srh_x][srh_y];
									alias_ID_vec_size[alias_id - 1]++;
								}
								else if (alias_map[srh_x][srh_y] != alias_map[xi][yi] )
								{
									alias_id = alias_map[srh_x][srh_y];
									int dead_alias = alias_map[xi][yi];
									dead_alias_vec[dead_alias_vec_size] = dead_alias-1;
									dead_alias_vec_size++;

									for (int ID_idx = 0; ID_idx < alias_ID_vec_size[dead_alias - 1]; ID_idx++)
									{
										*alias_ID_vec[dead_alias - 1][ID_idx] = alias_id;
										alias_ID_vec[alias_id - 1][alias_ID_vec_size[alias_id - 1]] = alias_ID_vec[dead_alias - 1][ID_idx];
										alias_ID_vec_size[alias_id - 1]++;
										alias_vec[alias_id - 1][alias_vec_size[alias_id - 1]] = alias_vec[dead_alias - 1][ID_idx];
										alias_vec_size[alias_id - 1]++;
									}
								}
								else
								{
									alias_id = alias_map[xi][yi];
								}
								alias_map[xi][yi] = alias_id;
								alias_map[srh_x][srh_y]= alias_id;

							}
						}
					}
				}
			}
		}

		if (move_flag == true)
		{
			int success = 1;
			for (int alias_id = 0; alias_id < alias_num; alias_id++)
			{
				for (int dead_idx = 0; dead_idx < dead_alias_vec_size; dead_idx++)
				{
					if (alias_id == dead_alias_vec[dead_idx])
					{
						success = 0;
						break;
					}
				}
				if (success)
				{
					int sum = 0;
					for (int included_idx = 0; included_idx < alias_vec_size[alias_id]; included_idx++)
					{
						sum += *alias_vec[alias_id][included_idx];
					}
					int avg = sum / alias_vec_size[alias_id];

					for (int included_idx = 0; included_idx < alias_vec_size[alias_id]; included_idx++)
					{
						*alias_vec[alias_id][included_idx] = avg;
					}
				}
			}
			trial++;
			//print_map(alias_map);
			//print_map(map);
		}
	}

	cout << trial;
	return 0;
}

void print_map(int input_map[50][50])
{
	cout << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cout << input_map[xi][yi] << " ";
		}
		cout << endl;
	}
	cout << endl;
}