#include <iostream>
#include <list>
using namespace std;
//시계방향 90회전
//  c90 s90
// -s90 c90
//  0 -1
//  1 0


enum direction_e
{
	RIGHT =0,
	UP,
	LEFT,
	DOWN
};

struct pos
{
	int x = 0;
	int y = 0;
};

void rotate_atom(pos& data);
void rotate(list<pos>& curv_list, pos end_pos);
void print_map();

int N = 0;
int curve_arr[20][4];
bool map[101][101] = { 0 };
int dx[] = { 1,0,-1,0 };
int dy[] = { 0,-1,0,1 };
int g_rectangle_num = 0;

int main()
{
	cin >> N;
	for (int i = 0; i < N ; i++)
		for (int j = 0; j < 4; j++)
			cin >> curve_arr[i][j];

	// 끝점 기준 회전
	//1세대 만들기 : 끝점 - 시작점 -> 회전 -> 회전점 + 끝점 
	// 네모 구하기 : 컨볼루션

	for (int crv_idx = 0; crv_idx < N; crv_idx++)
	{
		pos start_pos;
		pos end_pos;
		start_pos.x = curve_arr[crv_idx][0];
		start_pos.y = curve_arr[crv_idx][1];
		int dir = curve_arr[crv_idx][2];
		int gen_goal = curve_arr[crv_idx][3];

		//generate for 0 gen
		list<pos> curve_list;
		curve_list.push_back(start_pos);

		end_pos.x = start_pos.x + dx[dir];
		end_pos.y = start_pos.y + dy[dir];

		//generate
		curve_list.push_back(end_pos);
		for (int gen_num = 1; gen_num <= gen_goal; gen_num++)
		{
			rotate(curve_list, end_pos);
			list<pos>::iterator itr = curve_list.end();
			itr--;
			end_pos.x = itr->x;
			end_pos.y = itr->y;
		}
		//marking
		for (list<pos>::iterator itr = curve_list.begin(); itr != curve_list.end(); itr++)
		{
			if(0 <= itr->x && itr->x <= 100 && 0 <= itr->y && itr->y <= 100)
				map[itr->x][itr->y] = 1;
		}
		//print_map();

	}
	for (int yi = 0; yi < 100; yi++)
	{
		for (int xi = 0; xi < 100; xi++)
		{
			bool isRectangle = 1;
			isRectangle &= map[xi][yi];
			isRectangle &= map[xi+1][yi];
			isRectangle &= map[xi][yi+1];
			isRectangle &= map[xi+1][yi+1];
			if (isRectangle)
				g_rectangle_num++;
		}
	}
	cout << g_rectangle_num;
}

void rotate_atom(pos& data)
{
	int temp_x = data.x;
	data.x = data.x * 0 + data.y * (-1);
	data.y = temp_x * 1 + data.y * 0;
}

void rotate(list<pos>& curv_list, pos end_pos)
{
	int len = curv_list.size();
	list<pos>::iterator itr = curv_list.end();
	itr--;
	itr--;
	for (int loop=0 ; loop<len -1 ; loop++)
	{
		pos transformed_pos;
		transformed_pos.x = itr->x - end_pos.x;
		transformed_pos.y = itr->y - end_pos.y;
		
		rotate_atom(transformed_pos);
		transformed_pos.x += end_pos.x;
		transformed_pos.y += end_pos.y;
		curv_list.push_back(transformed_pos);
		if(itr != curv_list.begin())
			itr--;
	}
}

void print_map()
{
	cout << endl;
	for (int yi = 0; yi <= 100; yi++)
	{
		for (int xi = 0; xi <= 100; xi++)
		{
			cout << map[xi][yi];
		}
		cout << endl;
	}
	cout << endl;
}