#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

#define X first
#define Y second

string board[1002][1002];
int firedist[1002][1002];
int jihundist[1002][1002];

int n,m;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++)
    {
        fill(firedist[i], firedist[i] + m, -1);
        fill(jihundist[i], jihundist[i] + m, -1);
    }

    queue <pair<int, int>> Q_fire;
    queue <pair<int, int>> Q_jihun; 

    while(!Q_fire.empty())
    {
        pair <int, int> cur = Q_fire.front();
        Q_fire.pop();
        for(int dir = 0; dir < 4; dir++)
        {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) { continue; } //#일 경우 컨티뉴 하는것을 추가
            if(firedist[nx][ny] >= 0) { continue; }
            firedist[nx][ny] = firedist[cur.X][cur.Y] + 1;
            Q_fire.push({nx, ny});
        }
    }

    while(!Q_jihun.empty())
    {
        pair <int, int> cur = Q_jihun.front();
        Q_jihun.pop();
        for(int dir = 0; dir < 4; dir++)
        {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) // 가장자리 닿을 경우 현재 거리에서 + 1을 출력하고 종료
            {
                cout << jihundist[cur.X][cur.Y] + 1;
                return 0; 
            }
            if(jihundist[nx][ny] >= 0 || board[nx][ny] != "#")
            {
                
            }
        }
    }

    return 0; 
}