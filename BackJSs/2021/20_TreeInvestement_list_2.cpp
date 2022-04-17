#include <iostream>
#include <list>
#include <vector>
using namespace std;

void feedingTree(int sx, int sy);
void treeBreeding(int sx, int sy);
void print_tree_age();
void print_tree_num();

list<int> g_tree_map[10][10];
int g_food_map[10][10];
int age_sum_map[10][10];

int N = 0;
int M = 0;
int K = 0;
int addtional_food_map[10][10];
int g_tree_num = 0;

int dx[] = { -1,1,0,0,  -1,1,1,-1 };
int dy[] = { 0,0,-1,1,  -1,-1,1,1 };

int main()
{
	cin >> N >> M >> K;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> addtional_food_map[xi][yi];
			g_food_map[xi][yi] = 5;
		}
	}
	for (int i = 0; i < M; i++)
	{
		int tree_X;
		int tree_Y;
		int tree_age;

		cin >> tree_Y >> tree_X >> tree_age;
		tree_X--;
		tree_Y--;
		g_tree_map[tree_X][tree_Y].push_front(tree_age);
		age_sum_map[tree_X][tree_Y] += tree_age;
		g_tree_num++;
	}

	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			g_tree_map[xi][yi].sort();
		}
	}

	for (int year_loop = 0; year_loop < K; year_loop++)
	{
		if (g_tree_num == 0)
			break;

		//spring & summer
		for (int yi = 0; yi < N; yi++)
		{
			for (int xi = 0; xi < N; xi++)
			{
				if (g_tree_map[xi][yi].size() != 0)
					feedingTree(xi, yi);
			}
		}

		//atumn && winter
		for (int yi = 0; yi < N; yi++)
		{
			for (int xi = 0; xi < N; xi++)
			{
				if (0 != g_tree_map[xi][yi].size())
					treeBreeding(xi, yi);
				g_food_map[xi][yi] += addtional_food_map[xi][yi];
			}
		}
	}

	cout << g_tree_num;
}


void treeBreeding(int sx, int sy)
{
	list<int>::iterator itr = g_tree_map[sx][sy].end();
	itr--;
	while(true)
	{
		if (*itr % 5 == 0)
		{
			for (int dir = 0; dir < 8; dir++)
			{
				int nx = sx + dx[dir];
				int ny = sy + dy[dir];
				if (0 <= nx && nx < N && 0 <= ny && ny < N)
				{
					g_tree_map[nx][ny].push_front(1);
					g_tree_num++;
					age_sum_map[nx][ny]++;
				}
			}
		}
		else if (*itr < 5)
			break;
		if (itr == g_tree_map[sx][sy].begin())
			break;
		itr--;
	}

}

void feedingTree(int sx, int sy)
{
	int dead_tree_sum = 0;
	for (list<int>::iterator itr = g_tree_map[sx][sy].begin(); itr != g_tree_map[sx][sy].end();)
	{
		int tree_age = *itr;
		if (g_food_map[sx][sy] >= tree_age)
		{
			g_food_map[sx][sy] -= tree_age;
			age_sum_map[sx][sy]++;
			*itr += 1;

			itr++;
		}
		else
		{
			dead_tree_sum += tree_age / 2;
			itr = g_tree_map[sx][sy].erase(itr);
			g_tree_num--;
		}
	}
	g_food_map[sx][sy] += dead_tree_sum;
}

void print_tree_age()
{
	cout << endl;
	for (int sy = 0; sy < N; sy++)
	{
		for (int sx = 0; sx < N; sx++)
		{
			cout << "x = " << sx << "y = " << sy << ", tree age =";
			for (list<int>::iterator itr = g_tree_map[sx][sy].begin(); itr != g_tree_map[sx][sy].end(); itr++)
			{
				cout << *itr << " ";
			}
			cout << endl;
		}
	}

}

void print_tree_num()
{
	cout << endl;
	cout << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cout << g_tree_map[xi][yi].size() << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cout << g_food_map[xi][yi] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
}