#include <iostream>
#include <vector>


using namespace std;

#define CHICKENSTORE 2
#define HOUSE 1

struct pos
{
	int x = 0;
	int y = 0;
};

void selectChicken(vector<int> selected_chk_idx_vec, int last_select_idx, int trial);
int calcDistance_atom(pos house, pos chicken);
void print_map(vector<int> selected_chk_idx_vec);

int N = 0;
int M = 0;
int map[50][50] = { 0 };
vector<pos> chicken_store_vec;
vector<pos> house_vec;
vector<int> house_chk_dst_vec;
int g_chk_num = 0;
int g_min = 9999;
int main()
{
	cin >> N >> M;
	
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> map[xi][yi];
			if (map[xi][yi]== CHICKENSTORE)
			{
				pos chk;
				chk.x = xi;
				chk.y = yi;
				chicken_store_vec.push_back(chk);
			}
			else if (map[xi][yi] == HOUSE)
			{
				pos house;
				house.x = xi;
				house.y = yi;
				house_vec.push_back(house);
				house_chk_dst_vec.push_back(300);
			}
		}
	}
	g_chk_num = chicken_store_vec.size();
	vector<int> selected_chk_idx_vec;
	selectChicken(selected_chk_idx_vec, -1, 0);
	cout << g_min;
}


int calcDistance_atom(pos house, pos chicken)
{
	int dx = house.x - chicken.x;
	int dy = house.y - chicken.y;

	return abs(dx) + abs(dy);
}

void selectChicken(vector<int> selected_chk_idx_vec, int last_select_idx, int trial)
{
	if (trial < M)
	{
		trial++;
		for (int selected_idx = last_select_idx + 1; selected_idx < g_chk_num; selected_idx++)
		{
			vector<int> selected_chk_idx_local_vec;
			selected_chk_idx_local_vec = selected_chk_idx_vec;

			selected_chk_idx_local_vec.push_back(selected_idx);
			selectChicken(selected_chk_idx_local_vec, selected_idx, trial);
		}
	}
	else
	{
		vector<int> house_chk_dst_vec_local;
		house_chk_dst_vec_local = house_chk_dst_vec;

		for (int house_idx = 0; house_idx < house_vec.size(); house_idx++)
		{
			for (int i = 0; i < selected_chk_idx_vec.size(); i++)
			{
				int chk_idx = selected_chk_idx_vec.at(i);

				pos chk_pos = chicken_store_vec.at(chk_idx);
				pos house_pos = house_vec.at(house_idx);
				int dst = calcDistance_atom(house_pos, chk_pos);

				if (dst < house_chk_dst_vec_local.at(house_idx))
					house_chk_dst_vec_local[house_idx] = dst;
			}
		}
		int sum = 0;
		for (int i = 0; i < house_chk_dst_vec_local.size(); i++)
		{
			sum += house_chk_dst_vec_local.at(i);
		}
		if (sum < g_min)
			g_min = sum;
		//cout <<endl<< sum;
		//print_map(selected_chk_idx_vec);
	}

}

void print_map(vector<int> selected_chk_idx_vec)
{
	cout << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			if (map[xi][yi] == CHICKENSTORE)
			{
				bool isChk = false;
				for (int i = 0; i < selected_chk_idx_vec.size(); i++)
				{
					pos chk_pos = chicken_store_vec.at(selected_chk_idx_vec.at(i));
					if (chk_pos.x == xi && chk_pos.y == yi)
					{
						isChk = true;
						break;
					}
				}
				if (isChk == true)
						cout << CHICKENSTORE << " ";
				else
				{
					cout << 0 << " ";
				}
			}
			else
			{
				cout << map[xi][yi] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}