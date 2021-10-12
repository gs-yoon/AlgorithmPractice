#include <iostream>

using namespace std;

int N = 0;
int g_map[21][21] = { 0 };
int total_num = 0;
int g_min = 9999;
int main()
{
	cin >> N;

	for (int yi = 1; yi <= N; yi++)
	{
		for (int xi = 1; xi <= N; xi++)
		{
			cin >> g_map[xi][yi];
			total_num += g_map[xi][yi];
		}
	}
	for (int Y = 2; Y <= N; Y++)
	{
		for (int X = 1; X <= N - 2; X++)
		{
			for (int D_1 = 1; D_1 <= Y - 1; D_1++)
			{
				for (int D_2 = 1; D_2 <= N - Y; D_2++)
				{
					if (D_1 + D_2 <= N - X)
					{
						//1备开
						int sum[5] = { 0 };
						sum[0] = 0;
						sum[1] = 0;
						sum[2] = 0;
						sum[3] = 0;
						sum[4] = 0;
						int area_map[20][20] = { 0 };

						int restrictionX = X + D_1;
						for (int iy = 1; iy < Y; iy++)
						{
							if (iy >= Y - D_1)
							{
								restrictionX--;
							}
							for (int ix = 1; ix <= restrictionX; ix++)
							{
								sum[0] += g_map[ix][iy];
								area_map[ix][iy] = 1;
							}
						}
						//2备开
						restrictionX = X-1;
						for (int iy = Y; iy <= N ; iy++)
						{
							if (iy > Y + D_2)
							{
								restrictionX = X+D_2;
							}
							else if(iy <= Y+ D_2)
							{
								restrictionX++;
							}
							for (int ix = 1; ix < restrictionX; ix++)
							{
								sum[1] += g_map[ix][iy];
								area_map[ix][iy] = 2;
							}
						}
						//3备开
						restrictionX = 1;
						for (int iy = 1; iy <= Y - D_1 + D_2; iy++)
						{
							if (iy > Y - D_1)
							{
								restrictionX++;
							}
							for (int ix = X + D_1 + restrictionX; ix <= N; ix++)
							{
								sum[2] += g_map[ix][iy];
								area_map[ix][iy] = 3;
							}
						}
						//4备开
						restrictionX = -1;
						for (int iy = Y - D_1 + D_2 +1 ; iy <= N; iy++)
						{
							if (iy <= Y + D_2 +1 )
							{
								restrictionX++;
							}
							for (int ix = X+ D_1 + D_2 - restrictionX; ix <= N; ix++)
							{
								sum[3] += g_map[ix][iy];
								area_map[ix][iy] = 4;
							}
						}
						//5备开
						sum[4] = total_num - sum[0] - sum[1] - sum[2] - sum[3];

						int local_min = 9999;
						int local_max = 0;
						for (int i = 0; i < 5; i++)
						{
							if (sum[i] > local_max)
							{
								local_max = sum[i];
							}
							if (sum[i] < local_min)
							{
								local_min = sum[i];
							}
						}

						int diff = local_max - local_min;
						/*
						cout << "diff = " << diff << endl;
						cout << "total num =" << total_num << endl;
						cout << "X = " << X << endl;
						cout << "Y = " << Y << endl;
						cout << "D_1 = " << D_1 << endl;
						cout << "D_2 = " << D_2 << endl;
						cout << endl;
						
						for(int yi = 1; yi <= N; yi++)
						{
							for ( int xi = 1; xi <= N; xi++)
							{
								cout << area_map[xi][yi] << " ";
							}
							cout << endl;
						}
						cout << endl;
						*/

						if (diff < g_min)
						{
							g_min = diff;
						}

					}
				}
			}
		}
	}

	cout << g_min;
}