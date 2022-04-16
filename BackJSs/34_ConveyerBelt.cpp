#include<iostream>
#include<vector>

using namespace std;

int getAbsRobotIdx(int rlt_idx);
void moveBelt();
bool jumpDownRobot();
void putOnRobot();
void moveRobot();
void print_();


int N = 0;
int K = 0;
int belt[200] = { 0 };
int put_on_idx = 0;
int jump_down_idx = 0;
vector<int> robot_idx_vec;
int g_broken_num = 0;
int main()
{
	cin >> N >> K;
	put_on_idx = 0;
	jump_down_idx = N - 1;
	for (int i = 0; i < 2 * N; i++)
	{
		cin >> belt[i];
	}

	int trial = 0;
	while (true)
	{
		trial++;
		moveBelt();
		moveRobot();
		putOnRobot();
		if (g_broken_num >= K)
			break;
	}
	cout << trial;

}

void moveRobot()
{
	for (int i = 0; i < robot_idx_vec.size(); i++)
	{
		int robot_belt_idx = robot_idx_vec.at(i);

		//상대적 다음 위치 로봇 있나
		if (i > 0)
		{
			if (robot_idx_vec.at(i - 1) == (robot_belt_idx + 1) % (2*N))
			{
				continue;
			}
		}
		//내구성 0보다 큰가
		int next_abs_idx = getAbsRobotIdx(robot_belt_idx + 1);
		if (belt[next_abs_idx] > 0)
		{
			//로봇상대위치인덱스 앞으로
			robot_belt_idx += 1;
			robot_idx_vec.at(i) = robot_belt_idx% (2*N);
			//벨트 내구성 감소
			belt[next_abs_idx] -= 1;
			if (belt[next_abs_idx] == 0)
			{
				g_broken_num++;
			}
		}

		//이동 후, 0번 로봇은 뛰어내릴 수 있는가? (idx에러 조심)
		if (i == 0)
		{
			if (jumpDownRobot() == true)
			{
				i--;
			}
		}
	}
}

void putOnRobot()
{
	if (belt[put_on_idx] > 0)
	{
		robot_idx_vec.push_back(put_on_idx);
		belt[put_on_idx]--;
		{
			if (belt[put_on_idx] == 0)
			{
				g_broken_num++;
			}
		}
	}
}

bool jumpDownRobot()
{
	if (robot_idx_vec.size() > 0)
	{
		if (getAbsRobotIdx(robot_idx_vec[0]) == jump_down_idx)
		{
			robot_idx_vec.erase(robot_idx_vec.begin());
			return true;
		}
	}
	return false;
}

void moveBelt()
{
	put_on_idx--;
	if(put_on_idx < 0)
		put_on_idx = (2 * N) -1;

	jump_down_idx--;
	if(jump_down_idx <0)
		jump_down_idx = (2 * N) -1;

	jumpDownRobot();
}

int getAbsRobotIdx(int rlt_idx)
{
	return rlt_idx % (2*N);
}

void print_()
{
	int idx = put_on_idx;
	cout << endl;
	for (int loop = 0; loop < 2 * N; loop++)
	{
		cout << belt[idx] << " ";
		idx++;
		idx %= (2 * N);
	}
	cout << endl;
}
