#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

#define X first
#define Y second

string board[1002];
int jihun_dist[1002][1002];
int fire_dist[1002][1002];

int n, m;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> board[i];
    }

    for (int i = 0; i < n; i++)
    {
        fill(jihun_dist[i], jihun_dist[i] + m, -1);
        fill(fire_dist[i], fire_dist[i] + m, -1);
    }

    queue<pair<int, int>> Q_fire;
    queue<pair<int, int>> Q_jihun;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] == 'J')
            {
                jihun_dist[i][j] = 0;
                Q_jihun.push({i, j});
            }
            if(board[i][j] == 'F')
            {
                fire_dist[i][j] = 0;
                Q_fire.push({i, j});
            }
        }
    }

    while (!Q_fire.empty())
    {
        pair<int, int> cur = Q_fire.front();
        Q_fire.pop();
        for (int dir = 0; dir < 4; dir++)
        {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
            {
                continue;
            }
            if (fire_dist[nx][ny] >= 0 || board[nx][ny] == '#')
            {
                continue;
            }
            fire_dist[nx][ny] = fire_dist[cur.X][cur.Y] + 1;
            Q_fire.push({nx, ny});
        }
    }

    while (!Q_jihun.empty())
    {
        pair<int, int> cur = Q_jihun.front();
        Q_jihun.pop();
        for(int dir = 0; dir < 4; dir++)
        {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) 
            {
                cout << jihun_dist[cur.X][cur.Y] + 1;
                return 0;
            }
            if(jihun_dist[nx][ny] >= 0 || board[nx][ny] == '#')
            {
                continue;
            }
            if(fire_dist[nx][ny] != -1 && jihun_dist[cur.X][cur.Y] + 1 >= fire_dist[nx][ny])
            {
                continue;
            }
            jihun_dist[nx][ny] = jihun_dist[cur.X][cur.Y] + 1;
            Q_jihun.push({nx, ny});  
        }
    }
    cout << "IMPOSSIBLE";

    return 0;
}