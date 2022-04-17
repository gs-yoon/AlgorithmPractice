#include<iostream>
#include<utility>
#include<queue>
#include<list>


using namespace std;

#define MAX 100
#define TURN_RIGHT 'D'
#define TURN_LEFT 'L'



enum direction_e
{
    LEFT =0,
    UP,
    RIGHT,
    DOWN
};

struct pos
{
    int x =0;
    int y =0;
};
#define APPLE 1

int dx[] = { -1, 0, 1 ,0 };
int dy[] = { 0, -1, 0 ,1 };
int N =0;
int apple_num =0 ;
bool g_map[MAX][MAX] = { 0 };
int apple_x[100] = {0};
int apple_y[100] = {0};
int direction_num =0;
pair<int,char> direction_info[100];
int global_time = 0;

int turn(int dir, char turn_dir);
void print_snake(list<pos> input_snake);


int main()
{
    cin >> N;
    cin >> apple_num;
    for (int i =0 ; i < apple_num ;i ++)
    {
        cin >> apple_y[i];
        apple_y[i]--;

        cin >> apple_x[i];
        apple_x[i]--;
        g_map[apple_x[i]][apple_y[i]] = APPLE;
    }
    cin >> direction_num;
    for (int i =0 ; i< direction_num ; i++)
    {
        cin >> direction_info[i].first;
        cin >> direction_info[i].second;
    }
    list<pos> snake;

    pos start_point;
    start_point.x=0;
    start_point.y=0;

    snake.push_back(start_point);
    int last_dir = RIGHT;
    bool keep_going=true;
    int dir = RIGHT;
    int dir_idx = 0;
    while(true)
    {
        int turning_time = 99999;
        keep_going = true;
        if (dir_idx < direction_num)
        {
            turning_time = direction_info[dir_idx].first;
        }
        pos head_pos = snake.back();

        while (keep_going)
        {
            global_time++;

            head_pos.x += dx[dir];
            head_pos.y += dy[dir];

            // dead?
            if (head_pos.x < 0 || head_pos.y < 0 || head_pos.x >= N || head_pos.y >= N)
            {
                keep_going = false;
                cout << global_time;
                return 0;
            }
            else
            {
                for (list<pos>::iterator itr = snake.begin(); itr != snake.end(); itr++)
                {
                    if (itr->x == head_pos.x && itr->y == head_pos.y)
                    {
                        keep_going = false;
                        cout << global_time;
                        return 0;
                    }
                }
                snake.push_back(head_pos);

                // if no apple
                if (g_map[head_pos.x][head_pos.y] != APPLE)
                {
                    if (!snake.empty())
                    {
                        snake.pop_front();
                    }
                    else
                    {
                        cout << "list empty error" << endl;
                    }
                }
                else
                {
                    g_map[head_pos.x][head_pos.y] = 0;
                }
                if (turning_time == global_time)
                {
                    dir = turn(dir, direction_info[dir_idx].second);
                    keep_going = false;
                }
                //print_snake(snake);
            }

        }
        dir_idx++;
    }

    cout << global_time;
}


void print_snake(list<pos> input_snake)
{
    char map[MAX][MAX];
    cout << "time : " << global_time << endl;
    for (int yi = 0; yi < N; yi++)
    {
        for (int xi = 0; xi < N; xi++)
        {
            if (g_map[xi][yi] == APPLE)
                map[xi][yi] = 'a';
            else
            {
                map[xi][yi] = '.';
            }
        }
    }

    for (list<pos>::iterator itr = input_snake.begin(); itr != input_snake.end(); itr++)
    {
        map[itr->x][itr->y] = 'x';
    }
    for (int yi = 0; yi < N; yi++)
    {
        for (int xi = 0; xi < N; xi++)
        {
            cout << map[xi][yi];
        }
        cout << endl;
    }
    cout << endl;
}

int turn(int dir, char turn_dir)
{
    if (turn_dir == TURN_RIGHT)
    {
        dir++;
        dir = dir % 4;
    }
    else if (turn_dir == TURN_LEFT)
    {
        dir--;
        if (dir < 0)
        {
            dir = DOWN;
        }
    }
    else
    {
        cout << "turning error" << endl;
    }
    return dir;
}