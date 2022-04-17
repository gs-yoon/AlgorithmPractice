#include <iostream>
#include <list>
#include <vector>
#include <queue>
using namespace std;

void feedingTree();
void treeBreeding();
void print_tree_age();
void print_tree_num();

struct Tree
{
	int x = 0;
	int y = 0;
	int age = 0;
};

struct cmp
{
	bool operator()(Tree a, Tree b)
	{
		return a.age < b.age;
	}
};

list<Tree> g_tree_dq;
int g_food_map[10][10];

int N = 0;
int M = 0;
int K = 0;
int addtional_food_map[10][10];
int g_tree_num = 0;
int dx[] = { -1,1,0,0,  -1,1,1,-1 };
int dy[] = { 0,0,-1,1,  -1,-1,1,1 };


int main()
{
	priority_queue<Tree,vector<Tree>,cmp> input_pq;
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
		Tree input_tree;
		input_tree.x = tree_X;
		input_tree.y = tree_Y;
		input_tree.age = tree_age;

		input_pq.push(input_tree);
		g_tree_num++;
	}
	while (!input_pq.empty())
	{
		g_tree_dq.push_front(input_pq.top()); input_pq.pop();
	}

	for (int year_loop = 0; year_loop < K; year_loop++)
	{
		if (g_tree_num == 0)
			break;

		//spring & summer
		feedingTree();

		//atumn
		treeBreeding();
		
		//winter
		for (int yi = 0; yi < N; yi++)
		{
			for (int xi = 0; xi < N; xi++)
			{
				g_food_map[xi][yi] += addtional_food_map[xi][yi];
			}
		}
	}

	cout << g_tree_num;
}
void treeBreeding()
{
	for (list<Tree>::iterator itr = g_tree_dq.begin() ; itr != g_tree_dq.end(); itr++)
	{
		if (itr->age % 5 == 0)
		{
			for (int dir = 0; dir < 8; dir++)
			{
				int nx = itr->x + dx[dir];
				int ny = itr->y + dy[dir];
				if (0 <= nx && nx < N && 0 <= ny && ny < N)
				{
					Tree breeded_tree;
					breeded_tree.x = nx;
					breeded_tree.y = ny;
					breeded_tree.age = 1;
					g_tree_dq.push_front(breeded_tree);
					g_tree_num++;
				}
			}
		}
	}
}

void feedingTree()
{
	list<Tree> dead_tree_dq;

	for (list<Tree>::iterator itr = g_tree_dq.begin(); itr != g_tree_dq.end();)
	{
		Tree cur_tree;
		cur_tree = *itr;
		if (g_food_map[cur_tree.x][cur_tree.y] >= cur_tree.age)
		{
			g_food_map[cur_tree.x][cur_tree.y] -= cur_tree.age;
			itr->age += 1;
			itr++;
		}
		else
		{
			dead_tree_dq.push_back(*itr);
			itr = g_tree_dq.erase(itr);
			g_tree_num--;
		}
	}

	for (list<Tree>::iterator itr = dead_tree_dq.begin(); itr != dead_tree_dq.end(); itr++)
	{
		Tree dead_tree = *itr;
		g_food_map[dead_tree.x][dead_tree.y] += dead_tree.age / 2;
	}

}
/*
void print_tree_age()
{
	cout << endl;
	for (int idx = 0; idx < g_tree_dq.size(); idx++)
	{
		cout << "x = " << g_tree_dq[idx].x << "y = " << g_tree_dq[idx].y << ", tree age =";
		cout << g_tree_dq[idx].age << endl;
	}
	cout << endl;

}

void print_tree_num()
{
	cout << endl;
	cout << endl;
	int map[10][10] = { 0 };
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			for (int idx = 0; idx < g_tree_dq.size(); idx++)
			{
				if (xi == g_tree_dq[idx].x && yi == g_tree_dq[idx].y)
					map[xi][yi]++;
			}
		}
	}
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cout<< map[xi][yi]++ << " ";
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
}*/