#include<iostream>

using namespace std;

#define MAX 20


struct Dice
{
	int top = 0;
	int bottom = 0;
	int front = 0;
	int back = 0;
	int left = 0;
	int right =0;
};

enum direction_e
{
	RIGHT=1,
	LEFT,
	UP,
	DOWN
};

void rolling(int dir, Dice& input_dice);
void print_dice(Dice input);

int dx[] = { 0,1,-1,0,0 };
int dy[] = { 0,0,0,-1,1 };
int N = 0;
int M = 0;
int g_map[MAX][MAX];
int start_x = 0;
int start_y = 0;
int cmd_num = 0;
int* cmd_arr;

int main()
{
	cin >> N;
	cin >> M;
	cin >> start_y;
	cin >> start_x;
	cin >> cmd_num;
	for (int iy = 0; iy < N; iy++)
	{
		for (int ix = 0; ix < M; ix++)
		{
			cin >> g_map[ix][iy];
		}
	}
	cmd_arr = new int[cmd_num];
	for (int i = 0; i < cmd_num; i++)
	{
		cin >> cmd_arr[i];
	}

	int cmd = 0;
	Dice dice;
	int cur_x = start_x;
	int cur_y = start_y;
	for (int cmd_idx = 0; cmd_idx < cmd_num; cmd_idx++)
	{
		cmd = cmd_arr[cmd_idx];

		int next_x = cur_x + dx[cmd];
		int next_y = cur_y + dy[cmd];

		if (next_x >= 0 && next_x < M && next_y >= 0 && next_y < N)
		{
			rolling(cmd, dice);
			cur_x = next_x;
			cur_y = next_y;
			
			if (g_map[cur_x][cur_y] == 0)
			{
				g_map[cur_x][cur_y] = dice.bottom;
			}
			else
			{
				dice.bottom = g_map[cur_x][cur_y];
				g_map[cur_x][cur_y] = 0;
			}

			cout << dice.top << endl;
		}
		//print_dice(dice);
	}
}

void print_dice(Dice input)
{
	cout << endl;
	cout << "dice : "<< "t : " << input.top << " "
		<< "b : "<< input.bottom << " " 
		<< "f : "<< input.front << " " 
		<< "b : "<<input.back <<" " 
		<< "L : "<< input.left <<" " 
		<< "R : "<<input.right  << endl;
	
	for (int iy = 0; iy < N; iy++)
	{
		for (int ix = 0; ix < M; ix++)
		{
			cout << g_map[ix][iy] <<" ";
		}
		cout << endl;
	}
	cout << endl;
}

void rolling(int dir, Dice& input_dice)
{

	if (dir == LEFT)
	{
		int temp = input_dice.right;
		input_dice.right = input_dice.bottom;
		input_dice.bottom = input_dice.left;
		input_dice.left = input_dice.top;
		input_dice.top = temp;
	}
	else if (dir == RIGHT)
	{
		int temp = input_dice.top;
		input_dice.top = input_dice.left;
		input_dice.left = input_dice.bottom;
		input_dice.bottom = input_dice.right;
		input_dice.right = temp;
	}
	else if (dir == UP)
	{
		int temp = input_dice.back;
		input_dice.back = input_dice.bottom;
		input_dice.bottom = input_dice.front;
		input_dice.front = input_dice.top;
		input_dice.top = temp;
	}
	else if (dir == DOWN)
	{
		int temp = input_dice.top;
		input_dice.top = input_dice.front;
		input_dice.front = input_dice.bottom;
		input_dice.bottom = input_dice.back;
		input_dice.back = temp;
	}
	else
	{
		cout << "rolling error" << endl;
	}
}