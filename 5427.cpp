#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

#define X first
#define Y second

string board[1002];
int dist_fire[1002][1002];
int dist_sang[1002][1002];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int tc;
    cin >> tc;
    while (tc--)
    {
        // w : m, n : h
        int w, h;
        cin >> w >> h;
        for (int i = 0; i < h; i++)
        {
            fill(dist_fire[i], dist_fire[i] + w, -1);
            fill(dist_sang[i], dist_sang[i] + w, -1);
        }
        queue<pair<int, int>> Q_fire;
        queue<pair<int, int>> Q_sang;
        for (int i = 0; i < h; i++)
        {
            cin >> board[i];
            for (int j = 0; j < w; j++)
            {
                if (board[i][j] == '*') // 불일 경우
                {
                    dist_fire[i][j] = 0;
                    Q_fire.push({i, j});
                }
                if (board[i][j] == '@') // 상근이 시작 위치일 경우
                {
                    dist_sang[i][j] = 0;
                    Q_sang.push({i, j});
                }
            }
        }

        // 불에대한 bfs
        while (!Q_fire.empty())
        {
            auto cur = Q_fire.front();
            Q_fire.pop();
            for (int dir = 0; dir < 4; dir++)
            {
                int nx = cur.X + dx[dir];
                int ny = cur.Y + dy[dir];
                if (nx < 0 || nx >= h || ny < 0 || ny >= w)
                {
                    continue;
                }
                if (dist_fire[nx][ny] >= 0 || board[nx][ny] == '#')
                {
                    continue;
                }
                dist_fire[nx][ny] = dist_fire[cur.X][cur.Y] + 1;
                Q_fire.push({nx, ny});
            }
        }

        bool stop = false;
        // 불에대한 bfs로 불의 거리를 다 구했으니 이제 상근이를 bfs돌려 비교해서 답 출력.
        while (!Q_sang.empty())
        {
            auto cur = Q_sang.front();
            Q_sang.pop();
            for (int dir = 0; dir < 4; dir++)
            {
                int nx = cur.X + dx[dir];
                int ny = cur.Y + dy[dir];
                if (nx < 0 || nx >= h || ny < 0 || ny >= w) // 가장자리에 닿은 경우. 탈출 성공
                {
                    cout << dist_sang[cur.X][cur.Y] + 1 << "\n";
                    stop = true;
                    break;
                }
                if (dist_sang[nx][ny] >= 0 || board[nx][ny] == '#')
                {
                    continue;
                }
                if (dist_fire[nx][ny] != -1 && dist_sang[cur.X][cur.Y] + 1 >= dist_fire[nx][ny])
                {
                    continue;
                }
                dist_sang[nx][ny] = dist_sang[cur.X][cur.Y] + 1;
                Q_sang.push({nx, ny});
            }
            if (stop == true)
            {
                break;
            }
        }

        if (stop == true)
        {
            continue;
        } // 가장자리에 닿은경우, 임파서블을 출력하지 않고 와일문을 나감
        cout << "IMPOSSIBLE" << "\n";
    }
    return 0;
}