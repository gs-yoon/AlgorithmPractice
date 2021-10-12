#include <iostream>
#include <utility>
#include <vector>

using namespace std;

enum qube_e
{
	UP =0,
	DOWN,
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

enum side_e
{
	C_LEFTSIDE = 0,
	C_RIGHTSIDE = 2,
	R_UPSIDE = 0,
	R_DOWNSIDE = 2
};

void print_up();
void getBlcoks(int junction, char* out_jucntion_side[12]);
void rotateBlock(int aspect, char dir);

int test_max = 0;
int* n;
vector<vector<pair<char, char>>> case_vector;

char g_qube[6][3][3];
char corlor_arr[] = { 'w','y','o','r','g','b' };

int main()
{
	cin >> test_max;
	n = new int[test_max];

	for (int test_idx = 0; test_idx < test_max; test_idx++)
	{
		cin >> n[test_idx];
		vector<pair<char, char>> rotate_case_vector;
		for (int rotate_idx = 0; rotate_idx < n[test_idx]; rotate_idx++)
		{
			pair<char, char> rotate_dir;
			cin >> rotate_dir.first >> rotate_dir.second;
			if (rotate_dir.first == 'F')
				rotate_dir.first = 'B';
			else if (rotate_dir.first == 'B')
				rotate_dir.first = 'F';
			rotate_case_vector.push_back(rotate_dir);
		}
		case_vector.push_back(rotate_case_vector);
	}


	for (int trial = 0; trial < case_vector.size(); trial++)
	{
		for (int aspect = 0; aspect < 6; aspect++)
		{
			for (int row = 0; row < 3; row++)
			{
				for (int col = 0; col < 3; col++)
				{
					g_qube[aspect][row][col] = corlor_arr[aspect];
				}
			}
		}
		for (int rt_num = 0; rt_num < case_vector[trial].size(); rt_num++)
		{
			char aspect = case_vector[trial][rt_num].first;
			char dir = case_vector[trial][rt_num].second;
			int asp;
			if (aspect == 'U')
				asp = UP;

			if (aspect == 'D')
				asp = DOWN;

			if (aspect == 'F')
				asp = FRONT;

			if (aspect == 'B')
				asp = BACK;

			if (aspect == 'L')
				asp = LEFT;

			if (aspect == 'R')
				asp = RIGHT;

			rotateBlock(asp, dir);
		}
		print_up();
	}

}

void rotateBlock(int aspect, char dir)
{
	
	char* junction_side[12];
	getBlcoks(aspect, junction_side);
	char rotated_aspect[3][3];
	char rotated_junction_side[12];
	



	if (dir == '+')
	{
		for (int row_idx = 0; row_idx < 3; row_idx++)
		{
			for (int col_idx = 0; col_idx < 3; col_idx++)
			{
				int r_col = (col_idx - 1) * 0 + (row_idx - 1) * (-1) + 1;
				int r_row = (col_idx - 1) * (1) + (row_idx - 1) * 0 +1;
				rotated_aspect[r_row][r_col] = g_qube[aspect][row_idx][col_idx];
			}
		}

		for (int i = 0; i < 12; i++)
		{
			int rt = (i+3) % 12;

			rotated_junction_side[rt] = *junction_side[i];
		}

	}
	else
	{
		for (int row_idx = 0; row_idx < 3; row_idx++)
		{
			for (int col_idx = 0; col_idx < 3; col_idx++)
			{
				int r_col = (col_idx - 1) * 0 + (row_idx - 1) * (1) + 1;
				int r_row = (col_idx - 1) * (-1) + (row_idx - 1) * 0 + 1;
				rotated_aspect[r_row][r_col] = g_qube[aspect][row_idx][col_idx];
			}
		}

		for (int i = 0; i < 12; i++)
		{
			int rt = (i - 3);
			if (rt < 0)
			{
				rt = 12 + rt;
			}
			rotated_junction_side[rt] = *junction_side[i];
		}
	}

	for (int row = 0 ; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			g_qube[aspect][row][col]= rotated_aspect[row][col];
		}
	}

	for (int i = 0; i < 12; i++)
	{
		*junction_side[i] = rotated_junction_side[i];
	}
}



void getBlcoks(int junction, char* out_jucntion_side[12])
{
	if (junction == UP)
	{
		//out_aspect = g_qube[UP];
		int turning_side[4] = { LEFT, FRONT, RIGHT, BACK};
		int juction_side_idx = 0;
		for (int side_idx = 0; side_idx < 4; side_idx++)
		{
			int junction_side = turning_side[side_idx];

			if (junction_side == FRONT)
			{
				for (int i = 0; i < 3; i++)
				{
					out_jucntion_side[juction_side_idx] = &g_qube[junction_side][R_DOWNSIDE][i];
					juction_side_idx++;
				}
			}
			else
			{
				for (int i = 2; i >= 0; i--)
				{
					out_jucntion_side[juction_side_idx] = &g_qube[junction_side][R_UPSIDE][i];
					juction_side_idx++;
				}
			}

		}
	}
	if (junction == DOWN)
	{
		int turning_side[4] = { LEFT, BACK, RIGHT, FRONT };
		int juction_side_idx = 0;
		for (int side_idx = 0; side_idx < 4; side_idx++)
		{
			int junction_side = turning_side[side_idx];

			if (junction_side == FRONT)
			{
				for (int i = 2; i >= 0; i--)
				{
					out_jucntion_side[juction_side_idx] = &g_qube[junction_side][R_UPSIDE][i];
					juction_side_idx++;
				}
			}
			else
			{
				for (int i = 0; i < 3; i++)
				{
					out_jucntion_side[juction_side_idx] = &g_qube[junction_side][R_DOWNSIDE][i];
					juction_side_idx++;
				}
			}

		}
	}
	if (junction == LEFT)
	{
		int turning_side[4] = { UP, BACK, DOWN, FRONT };
		int juction_side_idx = 0;
		for (int side_idx = 0; side_idx < 4; side_idx++)
		{
			int junction_side = turning_side[side_idx];

			for (int i = 0; i < 3; i++)
			{
				out_jucntion_side[juction_side_idx] = &g_qube[junction_side][i][C_LEFTSIDE];
				juction_side_idx++;
			}
		}
	}
	if (junction == RIGHT)
	{
		int turning_side[4] = { UP, FRONT, DOWN, BACK};
		int juction_side_idx = 0;
		for (int side_idx = 0; side_idx < 4; side_idx++)
		{
			int junction_side = turning_side[side_idx];

			for (int i = 2; i >= 0; i--)
			{
				out_jucntion_side[juction_side_idx] = &g_qube[junction_side][i][C_RIGHTSIDE];
				juction_side_idx++;
			}
		}
	}
	if (junction == FRONT)
	{
		int turning_side[4] = { UP, LEFT, DOWN, RIGHT};
		int juction_side_idx = 0;
		for (int side_idx = 0; side_idx < 4; side_idx++)
		{
			int junction_side = turning_side[side_idx];

			if (junction_side == UP )
			{
				for (int i = 2; i >=0; i--)
				{
					out_jucntion_side[juction_side_idx] = &g_qube[junction_side][R_UPSIDE][i];
					juction_side_idx++;
				}
			}
			else if(junction_side == LEFT)
			{
				for (int i = 0; i < 3; i++)
				{
					out_jucntion_side[juction_side_idx] = &g_qube[junction_side][i][C_LEFTSIDE];
					juction_side_idx++;
				}
			}
			else if (junction_side == DOWN)
			{
				for (int i = 0; i < 3; i++)
				{
					out_jucntion_side[juction_side_idx] = &g_qube[junction_side][R_DOWNSIDE][i];
					juction_side_idx++;
				}
			}
			else if (junction_side == RIGHT)
			{
				for (int i = 2; i >= 0; i--)
				{
					out_jucntion_side[juction_side_idx] = &g_qube[junction_side][i][C_RIGHTSIDE];
					juction_side_idx++;
				}
			}
		}
	}
	if (junction == BACK)
	{
		int turning_side[4] = { UP, RIGHT, DOWN, LEFT};
		int juction_side_idx = 0;
		for (int side_idx = 0; side_idx < 4; side_idx++)
		{
			int junction_side = turning_side[side_idx];

			if (junction_side == UP)
			{
				for (int i = 0; i < 3; i++)
				{
					out_jucntion_side[juction_side_idx] = &g_qube[junction_side][R_DOWNSIDE][i];
					juction_side_idx++;
				}
			}
			else if (junction_side == RIGHT)
			{
				for (int i = 0; i < 3; i++)
				{
					out_jucntion_side[juction_side_idx] = &g_qube[junction_side][i][C_LEFTSIDE];
					juction_side_idx++;
				}
			}
			else if (junction_side == DOWN)
			{
				for (int i = 2; i >=0; i--)
				{
					out_jucntion_side[juction_side_idx] = &g_qube[junction_side][R_UPSIDE][i];
					juction_side_idx++;
				}
			}
			else if (junction_side == LEFT)
			{
				for (int i = 2; i >= 0; i--)
				{
					out_jucntion_side[juction_side_idx] = &g_qube[junction_side][i][C_RIGHTSIDE];
					juction_side_idx++;
				}
			}
		}
	}

}


void print_up()
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			cout << g_qube[UP][row][col];
		}
		cout << endl;
	}
}