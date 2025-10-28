#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

#define X first
#define Y second

char board[1002][1002];
int firedist[1002][1002];
int jihundist[1002][1002];

int n,m;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill(firedist, firedist + 1002, -1);
    fill(jihundist, jihundist + 1002, -1);
    
    pair <int, int> j_location, f_location;
    cin >> n >> m;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> board[i][j];
            if(board[i][j] == 'J') //지훈이 자리 미리 세이브
            {
                j_location = {i, j};
            }
            if(board[i][j] == 'F') //불 자리
            {
                f_location = {i, j};
            }
        }
    }


    //#: 벽
    //.: 지나갈 수 있는 공간
    //J: 지훈이 위치
    //F: 불난곳
    //불을 bfs 시켜줌.
    queue<pair<int, int>> Q;

    //불 위치부터 삽입
    firedist[f_location.X][f_location.Y] = 1; 
    Q.push({f_location.X, f_location.Y});

    while(!Q.empty())
    {
        pair <int, int> cur = Q.front();
        Q.pop();
        for(int dir = 0; dir < 4; dir++)
        {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m || board[nx][ny] ==  '#') { continue; } //#일 경우 컨티뉴 하는것을 추가
            if(firedist[nx][ny] >= 0) { continue; }
            firedist[nx][ny] = firedist[cur.X][cur.Y] + 1;
            Q.push({nx, ny});
        }
    }

    //지훈이 삽입
    //vis = 1, 좌표 큐에 푸쉬
    jihundist[j_location.X][j_location.Y] = 1;
    Q.push({j_location.X, j_location.Y});
    //.일때만 지나갈 수 있음. 다른 문제에서 1과 동일함
    while (!Q.empty())
    {
        pair<int, int> cur = Q.front();
        Q.pop();
        for (int dir = 0; dir < 4; dir++)
        {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || board[nx][ny] == '#') { continue; } //위랑 똑같이 #이 올경우 컨티뉴
            {
                continue;
            }
            if (dist[nx][ny] || board[nx][ny] != 1)
            {
                continue;
            }
            vis[nx][ny] = 1;
            Q.push({nx, ny});
        }
    }
    return 0; 
}