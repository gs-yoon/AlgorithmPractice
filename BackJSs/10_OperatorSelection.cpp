#include <iostream>

using namespace std;

#define MAX 11
#define NUMAMX 1000000000

enum operator_e
{
	PLUS =0,
	MINUS,
	MULTIPLE,
	DIVISION
};
void operatorSelection_dfs(int input_opt_arr[], long int sum, int selection, int trial);

int N = 0;
int operand_arr[MAX] = {0};
int operator_arr[4] = { 0 };
long int g_max = -NUMAMX;
long int g_min = NUMAMX;
int main()
{
	cin >> N;
	for (int i = 0; i < N; i ++ )
	{
		cin >> operand_arr[i];
	}
	for (int i = 0; i < 4; i++)
	{
		cin >> operator_arr[i];
	}

	operatorSelection_dfs(operator_arr, operand_arr[0], PLUS, 0);
	operatorSelection_dfs(operator_arr, operand_arr[0], MINUS, 0);
	operatorSelection_dfs(operator_arr, operand_arr[0], MULTIPLE, 0);
	operatorSelection_dfs(operator_arr, operand_arr[0], DIVISION, 0);

	cout << g_max << endl;
	cout << g_min << endl;
}

//연산자 어레이, 값(누적), 트라이얼
void operatorSelection_dfs(int input_opt_arr[], long int sum, int selection, int trial)
{
	if (input_opt_arr[selection] > 0)
	{
		trial++;
		//copy
		int local_opt_arr[4] = { 0 };
		for (int i = 0; i < 4; i++)
		{
			local_opt_arr[i] = input_opt_arr[i];
		}
		local_opt_arr[selection]--;

		//operation
		switch (selection)
		{
		case PLUS:
			sum += operand_arr[trial];
			break;
		case MINUS:
			sum -= operand_arr[trial];
			break;
		case MULTIPLE:
			sum *= operand_arr[trial];
			break;
		case DIVISION:
			if (operand_arr[trial] != 0)
				sum /= operand_arr[trial];
			else
				cout << "error :: division with 0 " << endl;
			break;
		default:
			cout << "error :: selection error " << endl;
			break;
		}

		if (trial < N-1)
		{
			//recursion
			for (int opt_s = 0; opt_s < 4; opt_s++)
			{
				operatorSelection_dfs(local_opt_arr, sum, opt_s, trial);
			}
		}
		else
		{
			if (g_max < sum)
			{
				g_max = sum;
			}
			if (g_min > sum)
			{
				g_min = sum;
			}
		}
	}
}
