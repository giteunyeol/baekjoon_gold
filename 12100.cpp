#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int input_board[22][22]; // board의 크기 여유롭게 22 * 22로 줌. 가장 처음에 세팅돼있는 보드
int use_board[22][22];
bool fusion[22][22]; // 각 트라이마다 합쳐졌는지 판별할 변수. 처음에는 false로 초기화돼있음.
int n;
int max_block = 0; // 답

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1}; // board 이동 방향. 남, 동, 북, 서 순서 bfs랑 같음

bool out_of_bound(int row, int column) // 보드의 경계에 닿았는지 판별해주는 함수. 트루를 리턴하면 닿은거임.
{
    if (row < 0 || row >= n || column < 0 || column >= n)
    {
        return true;
    }
    return false; // else
}

// 진짜로 use_board의 좌표를 갱신함. 여러칸 가는 경우 한칸마다 좌표를 갱신하면 비효율적이니 시간복잡도 딸리면 나중에 리팩토링해도 될듯
void move(int new_r, int new_c, int past_r, int past_c) 
{
    use_board[new_r][new_c] = use_board[past_r][past_c]; // 갱신해줌
    use_board[past_r][past_c] = 0; // 이전 수가 있던 곳은 0으로 갱신해줌. 
}

void move_block(int row, int column, int dir) // 각 블럭을 움직이는 함수
{
    int new_r = row + dx[dir];    // 이 함수에서 사용할 새로운 변수 선언
    int new_c = column + dy[dir]; // new는 움직였을때 좌표, past는 이전 좌표 세이브 ***new 변수는 다음 움직였을때 어떻게 될지 판별하는거임!!***
    int past_r = row;
    int past_c = column;

    while (true)
    {
        // 멈춰야 하는 경우들
        // 경계선을 찍으면 더 움직일 필요가 없으니 현 상태에서 리턴
        if (out_of_bound(new_r, new_c)) { return; } 
        //다음 가야할 수가 0이면, 그대로 이동
        if(use_board[new_r][new_c] == 0)
        {
            move(new_r, new_c, past_r, past_c);
            past_r = new_r;
            past_c = new_c;
            new_r = past_r + dx[dir];
            new_c = past_c + dy[dir];
            continue; // 한칸 움직이고 다음 행동으로 점프
        }
        //두 수가 다르면 멈추면 되니 현 상태에서 리턴. 0일때는 이미 판별했음
        if (use_board[new_r][new_c] != use_board[past_r][past_c]) { return; }
        //use_board[new_r][new_c] == use_board[past_r][past_c] 이거랑 같음. 같은 수를 만난 경우
        if (fusion[new_r][new_c]) { return; } //합한적 있는 경우. 트루일때
        else //합한적 없을때
        {
            use_board[new_r][new_c] = use_board[past_r][past_c] * 2; // 2배로 곱해줌.
            fusion[new_r][new_c] = true;                             // 합해준지를 트루로 바꿈
            use_board[past_r][past_c] = 0;                           // 원래 좌표 초기화해줌.
            return; // 더해주고 돌아감
        }
    }
}

void move_board(int dir)
{
    // 각 방향마다 블럭을 옮기는 순서가 달라야함.
    // 각 블럭들을 순서대로 옮겨줌.
    if (dir == 0) // 남
    {
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j < n; j++)
            {
                if(use_board[i][j] != 0) //숫자가 들어있는 경우만 실행시켜줌
                move_block(i, j, dir);
            }
        }
    }
    else if (dir == 1) // 동. 행/열이 바뀐 순서로 순회해야함
    {
        for (int j = n - 1; j >= 0; j--)
        {
            for (int i = 0; i < n; i++)
            {
                if (use_board[i][j] != 0) // 숫자가 들어있는 경우만 실행시켜줌
                move_block(i, j, dir);
            }
        }
    }
    else if (dir == 2) // 북
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (use_board[i][j] != 0) // 숫자가 들어있는 경우만 실행시켜줌
                move_block(i, j, dir);
            }
        }
    }
    else // dir == 3 // 서. 행/열이 바뀐 순서로 순회해야함
    {
        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < n; i++)
            {
                if (use_board[i][j] != 0) // 숫자가 들어있는 경우만 실행시켜줌
                move_block(i, j, dir);
            }
        }
    }
}

int main(void)
{

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> input_board[i][j];
        }
    }

    for (int attempt = 0; attempt < (1 << (2 * 5)); attempt++) // n번째 시도. 4의 5제곱. 상하좌우 각 5번씩이니.
    {
        // 모든 경우의 수를 다 방문해야하니 굳이 백트래킹을 하지 않고 진법으로 풀면 됨.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                use_board[i][j] = input_board[i][j]; // 현재 시도하는 보드를 처음 세팅값 복사해옴.
            }
        }
        int cur_max_block = use_board[0][0]; // 현재 최댓값 블록을 보드 0, 0으로 세팅
        int atp = attempt;
        for (int go = 0; go < 5; go++) // 5번을 이동함.
        {
            int cur_dir = atp % 4; // 4진수 제일 아래자리를 따옴. 0 1 2 3중 하나
            atp = atp / 4;         // 제일 아래자리수를 날려버림(4진수표현에서)
            move_board(cur_dir);   // 보드 이동
            memset(fusion, false, sizeof(fusion)); // fusion의 불리언값 초기화. 
        }

        // 이동을 다 끝낸 후 현재 맥스값갱신
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cur_max_block = max(cur_max_block, use_board[i][j]);
            }
        }
        max_block = max(cur_max_block, max_block); // 최종 답 갱신!
    }

    cout << max_block;

    return 0;
}