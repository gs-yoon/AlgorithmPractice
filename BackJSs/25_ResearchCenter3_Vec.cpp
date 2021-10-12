#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define MAX 50

struct Virus
{
	int x = 0;
	int y = 0;
	int time = 0;
};
enum direction_e
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};

void selection_spread(int last_idx, vector<Virus> selected, int trial);
void print_map(bool visited_map[MAX][MAX]);


int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
int N = 0;
int M = 0;
int g_map[MAX][MAX];
int g_min = 9999;
int empty_space_num = 0;
vector<Virus> virus_vec;

int main()
{
	cin >> N >> M;

	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			cin >> g_map[xi][yi];
			if (g_map[xi][yi] == 2)
			{
				Virus input_virus;
				input_virus.x = xi;
				input_virus.y = yi;

				virus_vec.push_back(input_virus);
			}
			else if (g_map[xi][yi] == 0)
			{
				empty_space_num++;
			}
		}
	}
	if (empty_space_num == 0)
	{
		cout << 0;
		return -0;
	}

	vector<Virus> dummy_selected;
	selection_spread(-1, dummy_selected, 0);

	if (g_min == 9999)
		g_min = -1;
	cout << g_min;

	return 0;
}

void selection_spread(int last_idx, vector<Virus> selected, int trial)
{
	//select
	if (trial < M)
	{
		trial++;
		vector<Virus> selected_local;
		for (int i = last_idx + 1; i < virus_vec.size(); i++)
		{
			selected_local = selected;
			selected_local.push_back(virus_vec.at(i));
			selection_spread(i, selected_local, trial);
		}
	}
	//spread
	else
	{
		vector<Virus> cur_virus_vec;
		vector<Virus> next_virus_vec;
		cur_virus_vec.reserve(2500);
		next_virus_vec.reserve(2500);
		bool visited[MAX][MAX] = { 0 };
		bool keep_going = true;

		for (int i = 0; i < selected.size(); i++)
		{
			next_virus_vec.push_back(selected.at(i));
			visited[selected.at(i).x][selected.at(i).y] = true;
		}

		int local_empty_space_num = empty_space_num;
		int elapssed_time = 0;
		while (keep_going)
		{
			cur_virus_vec.clear();
			cur_virus_vec = next_virus_vec;
			next_virus_vec.clear();
			keep_going = false;

			if (g_min <= elapssed_time)
				return;

			for (int idx =0 ; idx < cur_virus_vec.size() ; idx ++)
			{
				Virus cur_virus = cur_virus_vec.at(idx);

				for (int dir = 0; dir < 4; dir++)
				{
					int nx = cur_virus.x + dx[dir];
					int ny = cur_virus.y + dy[dir];

					if (0 <= nx && nx < N && 0 <= ny && ny < N && g_map[nx][ny] != 1 && visited[nx][ny] != 1)
					{
						Virus next_virus;
						next_virus.x = nx;
						next_virus.y = ny;
						keep_going |= true;
						visited[nx][ny] = 1;
						next_virus_vec.push_back(next_virus);
						if (g_map[nx][ny] != 2)
							local_empty_space_num--;
					}
				}
			}
			if (keep_going == false)
				break;

			elapssed_time++;
			//print_map(visited);

			if (local_empty_space_num == 0)
				break;
		}

		if (local_empty_space_num == 0)
		{
			if (g_min > elapssed_time)
				g_min = elapssed_time;
		}
	}
}

void print_map(bool visited_map[MAX][MAX])
{
	cout << endl;
	for (int yi = 0; yi < N; yi++)
	{
		for (int xi = 0; xi < N; xi++)
		{
			if (visited_map[xi][yi] == 1)
				cout << 2 << " ";
			else
			{
				cout << g_map[xi][yi] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}