#include <iostream>
#include <vector>

using namespace std;

#define DEBUG 0

int calc_tree();
void atumnAndWinter();
void springAndSummer();
void print_tree_num();
void print_map(int map[10][10]);
void print_debug(const char* msg);

enum DIR
{
	UP =0,
	LEFT,
	DOWN,
	RIGHT,
	UP_LEFT,
	DOWN_LEFT,
	DOWN_RIGHT,
	UP_RIGHT
};

int dx[] = { 0, -1, 0 ,1, -1,-1,1,1 };
int dy[] = { -1, 0, 1, 0,-1,1,1,-1 };

int N = 0;
int M = 0;
int K = 0;
vector<int> tree_map[10][10];
int feed_map[10][10] = { 0 };
int A[10][10] = { 0 };

int main()
{
	cin >> N >> M >> K;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> A[x][y];
			feed_map[x][y] = 5;
		}
	}

	for (int i = 0; i < M; i++)
	{
		int x;
		int y;
		int age;
		cin >> y >> x >> age;
		tree_map[x-1][y-1].push_back(age);
	}

	print_debug("initial");
	for (int year = 0; year < K; year++)
	{
		//spring
		//summer
		springAndSummer();
		print_debug("after summer");

		//atumn
		//winter
		atumnAndWinter();
		print_debug("after winter");
	}
	cout << calc_tree();
}

void springAndSummer()
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (tree_map[x][y].size() > 0)
			{
				bool dead_flg = false;
				for (vector<int>::iterator itr = tree_map[x][y].end()-1; itr >= tree_map[x][y].begin(); itr-- )
				{
					int age = *itr;
					//feeding
					if (feed_map[x][y] >= age && dead_flg == false)
					{
						feed_map[x][y] -= age;
						*itr = age +1;
					}
					//die
					else
					{
						dead_flg = true;
						feed_map[x][y] += age/2;
						itr = tree_map[x][y].erase(itr);
					}
					if (itr == tree_map[x][y].begin())
					{
						break;
					}
				}
			}
		}
	}
}


void atumnAndWinter()
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			//breeding
			if (tree_map[x][y].size() > 0)
			{
				for (vector<int>::iterator itr = tree_map[x][y].begin(); itr != tree_map[x][y].end(); itr++)
				{
					if (*itr % 5 == 0)
					{
						for (int dir = 0; dir < 8; dir++)
						{
							int nx = x + dx[dir];
							int ny = y + dy[dir];
							if (0 <= nx && nx < N && 0 <= ny && ny < N)
							{
								tree_map[nx][ny].push_back(1);
							}
						}
					}
				}
			}

			//robot working
			feed_map[x][y] += A[x][y];
		}
	}
}

int calc_tree()
{
	int sum_of_tree = 0;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			sum_of_tree += tree_map[x][y].size();
		}
	}
	return sum_of_tree;
}

void print_tree_num()
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cout << tree_map[x][y].size() << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void print_map(int map[10][10])
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cout << map[x][y] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void print_debug(const char* msg)
{
#if DEBUG
	cout << msg << endl;
	print_tree_num();
	print_map(feed_map);
#endif
}