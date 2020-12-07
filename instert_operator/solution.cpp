#include<iostream>

using namespace std;

#define SUM 0
#define SUB 1
#define MUL 2
#define DIV 3


int n = 0;
int arr[100] = { 0 };
int oprs[4] = { 0 };
int gmax = -1000000000 ;
int gmin =  1000000000;

void dfs(int sum, int level, int in_opr, int in_oprs[4])
{
	bool end = true;
	level++;
	int local_oprs[4] = { 0 };
	for (int i = 0; i < 4; i++)
		local_oprs[i] = in_oprs[i];
	local_oprs[in_opr]--;
	switch (in_opr)
	{
		case SUM:
			sum += arr[level];
			break;
		case SUB:
			sum -= arr[level];
			break;
		case MUL:
			sum *= arr[level];
			break;
		case DIV:
			if (sum != 0)
				sum /= arr[level];
			//else
			//	cout << "divided by 0" << endl;
			break;
	}

	for (int i = 0; i < 4; i++)
	{
		if (local_oprs[i] > 0)
		{
			end = false;
			dfs(sum, level, i, local_oprs);
		}
	}

	if (level == n-1)
	{
		if (sum > gmax)
			gmax = sum;
		if (sum < gmin)
			gmin = sum;
	}

}
void search(int in_oprs[4])
{
	for (int i = 0; i < 4; i++)
	{
		if (in_oprs[i] > 0)
		{
			dfs(arr[0], 0, i, in_oprs);
		}
	}
}
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	for (int i = 0; i < 4; i++)
		cin >> oprs[i];


	search(oprs);
	cout << gmax << endl;
	cout << gmin << endl;

}