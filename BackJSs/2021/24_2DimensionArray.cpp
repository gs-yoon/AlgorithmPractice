#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define X 0
#define Y 1

struct info
{
	int val =0;
	int* ptr = nullptr;
};

void print_map();
void sorting(int sel);
bool cmp(info x, info y)
{
	if (*x.ptr < *y.ptr)
		return true;
	else if (*x.ptr > *y.ptr)
		return false;
	else
	{
		return x.val < y.val;
	}
}

int target_Y = 0;
int target_X = 0;
int K = 0;
int arr_map[100][100] = { 0 };
int size_x = 3;
int size_y = 3;
int trial = 0;
int main()
{
	cin >> target_Y >> target_X>> K;
	target_X--;
	target_Y--;
	for (int yi = 0; yi < 3; yi++)
	{
		for (int xi = 0; xi < 3; xi++)
		{
			cin >> arr_map[xi][yi];
		}
	}

	while (arr_map[target_X][target_Y] != K)
	{
		if (trial > 100)
		{
			trial = -1;
			break;
		}
		if (size_y >= size_x)
		{
			sorting(X);
		}
		else
		{
			sorting(Y);
		}
		//print_map();

		trial++;
	}
	cout << trial;
}

void sorting(int sel)
{
	if (sel == X)
	{
		for (int yi = 0; yi < size_y; yi++)
		{
			int hash_arr[101] = {0};
			vector<info> ptr_vec;
			ptr_vec.reserve(100);

			//find
			for (int xi = 0; xi < size_x; xi++)
			{
				int val = arr_map[xi][yi];
				if (val == 0)
					continue;

				if (hash_arr[val] == 0)
				{
					info nfo;
					nfo.val = val;
					nfo.ptr = hash_arr + val;
					ptr_vec.push_back(nfo);
				}
				hash_arr[val] += 1;
			}
			sort(ptr_vec.begin(), ptr_vec.end(), cmp);

			//re-write to map
			int search_max = ptr_vec.size();
			if (search_max > 50)
				search_max = 50;

			for (int vec_num = 1; vec_num <= search_max; vec_num++)
			{
				arr_map[vec_num * 2 - 2][yi] = ptr_vec.at(vec_num - 1).val;
				arr_map[vec_num * 2 - 1][yi] = *ptr_vec.at(vec_num - 1).ptr;

				if (search_max * 2 > size_x)
				{
					size_x = search_max * 2;
				}
			}
			for (int i = search_max * 2; i <size_x; i++)
				arr_map[i][yi] = 0;
		}
	}
	else
	{
		for (int xi = 0; xi < size_x; xi++)
		{
			int hash_arr[101] = { 0 };
			vector<info> ptr_vec;
			ptr_vec.reserve(100);

			//find
			for (int yi = 0; yi < size_y; yi++)
			{
				int val = arr_map[xi][yi];
				if (val == 0)
					continue;

				if (hash_arr[val] == 0)
				{
					info nfo;
					nfo.val = val;
					nfo.ptr = hash_arr + val;
					ptr_vec.push_back(nfo);
				}
				hash_arr[val] += 1;
			}
			sort(ptr_vec.begin(), ptr_vec.end(), cmp);

			//re-write to map
			int search_max = ptr_vec.size();
			if (search_max > 50)
				search_max = 50;

			for (int vec_num = 1; vec_num <= search_max; vec_num++)
			{
				arr_map[xi][vec_num * 2 - 2] = ptr_vec.at(vec_num - 1).val;
				arr_map[xi][vec_num * 2 - 1] = *ptr_vec.at(vec_num - 1).ptr;

				if (search_max * 2 > size_y)
				{
					size_y = search_max * 2;
				}
			}
			for (int i = search_max * 2; i < size_y; i++)
				arr_map[xi][i] = 0;
		}
	}
}

void print_map()
{
	cout << endl;
	for (int yi = 0; yi < size_y; yi++)
	{
		for (int xi = 0; xi < size_x; xi++)
		{
			cout << arr_map[xi][yi] << " ";
		}
		cout << endl;
	}
	cout << endl;
}