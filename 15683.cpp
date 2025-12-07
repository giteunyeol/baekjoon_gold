#include <iostream>
#include <algorithm>

using namespace std;

int n, m; //n은 행, m은 열

int board_default[10][10]; //처음에 저장을 받을 기본 배열 
int board_cur_state[10][10]; //현재 순회 상태 젖아할 배열
int cctv_count; //cctv의 총 갯수
pair <int, int> cctv_coordinate[10]; // 각 cctv의 좌표. 0개부터 시작하니 이 변수에 cctv의 갯수는 n - 1개로 세이브됨
int ans; // 최종 답

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

bool out_of_bound(int c, int l) //경계 검사 함수
{
    if(c < 0 || c >= n || l < 0 || l >= m) { return true; }
    return false;
}

void direction(int c, int l, int dir) //dir방향으로 진행하는 함수
{
    dir = dir % 4;
    while(true)
    {
        //x축은 아랫방향으로 증가, y축은 오른쪽으로 증가.
        c += dx[dir];
        l += dy[dir];
        if(out_of_bound(c, l) || board_default[c][l] == 6) { return; }// 경계에 닿았거나, 벽이면
        if (board_default[c][l] == 1 || board_default[c][l] == 2 || board_default[c][l] == 3 || board_default[c][l] == 4 || board_default[c][l] == 5) { continue; } // cctv에 닿은경우
        //다 통과한경우 일반 길이라는 뜻임.
        board_cur_state[c][l] = 7; // 감시 할 수 있는곳을 7번으로 변환.
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> board_default[i][j];
            if (board_default[i][j] == 1 || board_default[i][j] == 2 || board_default[i][j] == 3 || board_default[i][j] == 4 || board_default[i][j] == 5) 
            {   //cctv가 있을시, n-1개임.
                cctv_coordinate[cctv_count] = {i, j};
                cctv_count++;
            }
            else if(board_default[i][j] == 0) // 빈 칸
            {
                ans++;
            }
        } 
    }

    //각각의 cctv에서 회전판별
    for(int i = 0; i < (1 << (cctv_count * 2)); i++) //cctv갯수마다 4개씩 늘어나야함.
    {
        //각 경우마다 board_cur_state에 새로 복사
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < m; k++)
            {
                board_cur_state[j][k] = board_default[j][k];
            }
        }
        //i값이 0~3일때는 0번째 cctv회전, 4~7일때는 1번째cctv회전 ... 
        int k = i;
        for(int j = 0; j < cctv_count; j++)
        {
            int cur_dir = k % 4;
            k = k / 4;
            if(board_default[cctv_coordinate[j].first][cctv_coordinate[j].second] == 1) //cctv 1번일때
            {
                direction(cctv_coordinate[j].first, cctv_coordinate[j].second, cur_dir);
            }
            else if (board_default[cctv_coordinate[j].first][cctv_coordinate[j].second] == 2) 
            {
                direction(cctv_coordinate[j].first, cctv_coordinate[j].second, cur_dir);
                direction(cctv_coordinate[j].first, cctv_coordinate[j].second, cur_dir + 2);
            }
            else if (board_default[cctv_coordinate[j].first][cctv_coordinate[j].second] == 3)
            {
                direction(cctv_coordinate[j].first, cctv_coordinate[j].second, cur_dir);
                direction(cctv_coordinate[j].first, cctv_coordinate[j].second, cur_dir + 1);
            }
            else if (board_default[cctv_coordinate[j].first][cctv_coordinate[j].second] == 4)
            {
                direction(cctv_coordinate[j].first, cctv_coordinate[j].second, cur_dir);
                direction(cctv_coordinate[j].first, cctv_coordinate[j].second, cur_dir + 1);
                direction(cctv_coordinate[j].first, cctv_coordinate[j].second, cur_dir + 2);
            }
            else //5번일때
            {
                direction(cctv_coordinate[j].first, cctv_coordinate[j].second, cur_dir);
                direction(cctv_coordinate[j].first, cctv_coordinate[j].second, cur_dir + 1);
                direction(cctv_coordinate[j].first, cctv_coordinate[j].second, cur_dir + 2);
                direction(cctv_coordinate[j].first, cctv_coordinate[j].second, cur_dir + 3);
            }
        }  
        int cur_min = 0;
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < m; k++)
            {
                if(board_cur_state[j][k] == 0) {cur_min++;}
            }
        }
        ans = min(ans, cur_min);
    }

    cout << ans;
    return 0;
}