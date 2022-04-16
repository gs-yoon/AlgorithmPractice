#include <iostream>
#include <vector>
using namespace std;

enum direction_e
{
	UP =0,
	DOWN,
	LEFT,
	RIGHT
};

struct Pos
{
	int x = -1;
	int y = -1;
};

struct Preference
{
	int self_num = 0;
	int preference[4] = { 0 };
};

int find_empty_space_atom(int x, int y);
Pos find_best_pos(vector<Pos>& bf_pos);
bool find_bf_near(vector<Pos>& bf_pos, vector<Pos> bf_near[4]);
int calc_bf_near(int nx, int ny, vector<Pos>& bf_pos);
int is_bf_pos(int x, int y, vector<Pos>& bf_pos);
bool find_bf(int pref[4], vector<Pos>& bf_pos);
void print_map();

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

int N = 0;
int NN = 0;
int map[20][20] = {0};
Preference preference_arr[400];
Pos firends_pos[400];

int main()
{
	cin >> N;
	NN = N * N;
	for (int si = 0; si < NN; si++)
	{
		cin >> preference_arr[si].self_num;
		for (int pi = 0; pi < 4; pi++)
		{
			cin >> preference_arr[si].preference[pi];
		}
	}
	for (int si = 0; si < NN; si++)
	{
		Pos best_pos;
		vector<Pos> bf_pos_vec;
		bool found;
		int s_num = preference_arr[si].self_num;
		found = find_bf(preference_arr[si].preference, bf_pos_vec);

		if (found)
		{
			vector<Pos> bf_near_vec[4];

			if (find_bf_near(bf_pos_vec, bf_near_vec) == true)
			{
				for (int near_idx = 3; near_idx >= 0; near_idx--)
				{
					if (bf_near_vec[near_idx].size() > 0)
					{
						best_pos = find_best_pos(bf_near_vec[near_idx]);
						break;
					}
				}
			}
			else
			{
				found = false;
			}
		}
		if(!found)
		{
			int empty_max = -1;
			int empty_num = 0;
			bool going = true;
			for (int yi = 0; yi < N && going; yi++)
			{
				for (int xi = 0; xi < N && going; xi++)
				{
					if (map[xi][yi] != 0)
						continue;
					empty_num = find_empty_space_atom(xi, yi);

					if (empty_max < empty_num)
					{
						empty_max = empty_num;
						best_pos.x = xi;
						best_pos.y = yi;
						if (empty_max == 4)
						{
							going = false;
						}
					}
				}
			}
		}
		map[best_pos.x][best_pos.y] = s_num;
		firends_pos[s_num - 1] = best_pos;
		//print_map();
	}

	int grade = 0;
	for (int si = 0; si < NN; si++)
	{
		int self = preference_arr[si].self_num;

		int sx = firends_pos[self - 1].x;
		int sy = firends_pos[self - 1].y;

		int bf_num = 0;

		for (int dir = 0; dir < 4; dir++)
		{
			int nx = sx + dx[dir];
			int ny = sy + dy[dir];
				
			if (0 <= nx && nx < N && 0 <= ny && ny < N)
			{
				for (int pi = 0; pi < 4; pi++)
				{
					if (preference_arr[si].preference[pi] == map[nx][ny])
					{
						bf_num++;
					}
				}
			}
		}
		if (bf_num == 0)
		{
			grade += 0;
		}
		else if (bf_num == 1)
		{
			grade += 1;

		}
		else if (bf_num == 2)
		{
			grade += 10;
		}
		else if (bf_num == 3)
		{
			grade += 100;

		}
		else if (bf_num == 4)
		{
			grade += 1000;
		}
	}
	cout << grade;
}

bool find_bf(int pref[4], vector<Pos>& bf_pos )
{
	bool found = false;
	for (int pi = 0; pi < 4; pi++)
	{
		if (firends_pos[pref[pi] - 1].x >= 0)
		{
			bf_pos.push_back(firends_pos[pref[pi] - 1]);
			found = true;
		}
	}
	return found;
}

int is_bf_pos(int x, int y , vector<Pos>& bf_pos)
{
	int num = 0;
	for (int vi = 0; vi < bf_pos.size(); vi++)
	{
		if (bf_pos[vi].x == x && bf_pos[vi].y == y)
		{
			num++;
		}
	}
	if (num > 1)
		cout << "fatal_is_bf_pos\n";
	return num;
}

int calc_bf_near(int nx, int ny, vector<Pos>& bf_pos)
{
	int num = 0;
	for (int dir = 0; dir < 4; dir++)
	{
		int nbx = nx + dx[dir];
		int nby = ny + dy[dir];
		num += is_bf_pos(nbx, nby, bf_pos);
	}
	return num;
}

bool find_bf_near(vector<Pos>& bf_pos, vector<Pos> bf_near[4])
{
	bool found = false;
	for (int vi = 0; vi < bf_pos.size(); vi++)
	{
		int cx = bf_pos[vi].x;
		int cy = bf_pos[vi].y;
		for (int dir = 0; dir < 4; dir++)
		{
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];

			if (0 <= nx && nx < N && 0 <= ny && ny < N)
			{
				if (map[nx][ny] == 0)
				{
					int bf_near_num = 0;
					bf_near_num = calc_bf_near(nx, ny, bf_pos);
					if (bf_near_num == 0)
						cout << "fatal calc_bf_near\n";

					Pos near_pos;
					near_pos.x = nx;
					near_pos.y = ny;
					bf_near[bf_near_num - 1].push_back(near_pos);
					found = true;
				}
			}
		}
	}
	return found;
}


Pos find_best_pos(vector<Pos>& bf_pos)
{
	int empty_max = -1;
	int empty_num = 0;
	int bestX = 0;
	int bestY = 0;
	for (int vi = 0; vi < bf_pos.size(); vi++)
	{
		empty_num = find_empty_space_atom(bf_pos[vi].x, bf_pos[vi].y);
		if (empty_num > empty_max)
		{
			empty_max = empty_num;
			bestX = bf_pos[vi].x;
			bestY = bf_pos[vi].y;
		}
		else if (empty_num == empty_max)
		{
			if (bf_pos[vi].y < bestY)
			{
				empty_max = empty_num;
				bestX = bf_pos[vi].x;
				bestY = bf_pos[vi].y;
			}
			else if (bf_pos[vi].y == bestY)
			{
				if (bf_pos[vi].x < bestX)
				{
					empty_max = empty_num;
					bestX = bf_pos[vi].x;
					bestY = bf_pos[vi].y;
				}
			}

		}
	}
	Pos best_pos;
	best_pos.x = bestX;
	best_pos.y = bestY;
	return best_pos;
}


int find_empty_space_atom(int x, int y)
{
	int empty_num = 0;
	for (int dir = 0; dir < 4; dir++)
	{
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		if (0 <= nx && nx < N && 0 <= ny && ny < N)
		{
			if (map[nx][ny] == 0 )
			{
				empty_num++;
			}
		}
	}
	return empty_num;
}

void print_map()
{
	cout << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cout << map[xi][yi] << " ";
		}
		cout << endl;
	}
	cout << endl;
}