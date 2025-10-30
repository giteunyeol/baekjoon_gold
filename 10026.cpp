#include <iostream>
#include <queue>
#include <string>

using namespace std;

#define X first 
#define Y second

string board[102];
bool vis1[102][102];
bool vis2[102][102];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main(void)
{
    //적록색약이 아닌경우: 기본 bfs를 돌려서 count를 각각 더해줌. vis1로 bfs
    //적록색약인경우: R = G인 경우로 bfs를 돌려서 count를 각각 더해줌. vis2로 bfs
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int count1 = 0;
    int count2 = 0;
    queue<pair<int, int>> Q1;
    queue<pair<int, int>> Q2;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> board[i];
    }

    //적록색약이 아닌경우
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(vis1[i][j] == 0) // 방문한 경우가 없는 경우
            {
                char start_color = board[i][j]; // 현재 문자 cur_color에 저장
                vis1[i][j] = 1;
                Q1.push({i, j});
                while(!Q1.empty())
                {
                    pair<int, int> cur = Q1.front(); Q1.pop();
                    for(int dir = 0; dir < 4; dir++)
                    {
                        int nx = cur.X + dx[dir];
                        int ny = cur.Y + dy[dir];
                        if(nx < 0 || nx >= n || ny < 0 || ny >= n) { continue; }
                        if(vis1[nx][ny] || start_color != board[nx][ny]) { continue; } //방문했거나, 시작컬러와 현재 좌표의 컬러가 다르면 컨티뉴.
                        vis1[nx][ny] = 1;
                        Q1.push({nx, ny});
                    }
                }
                count1++;
            }
        }
    }

    //적록색약인경우
    //빨강 / 초록 구분 X. R = G / B 두가지로 구분
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(vis2[i][j] == 0)
            {
                char start_color = board[i][j]; // 현재 문자 cur_color에 저장
                vis2[i][j] = 1;
                Q2.push({i, j});
                while (!Q2.empty())
                {
                    pair<int, int> cur = Q2.front();
                    Q2.pop();
                    for (int dir = 0; dir < 4; dir++)
                    {
                        int nx = cur.X + dx[dir];
                        int ny = cur.Y + dy[dir];
                        if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                        {
                            continue;
                        }
                        if (vis2[nx][ny]){ continue; } // 방문한경우 continue;
                        if(start_color == 'R') // R인경우. B인경우 스킵해야함.
                        {
                            if(board[nx][ny] == 'B') { continue; }
                        }
                        if(start_color == 'G') // G인경우. B인경우 스킵해야함
                        {
                            if (board[nx][ny] == 'B'){ continue; }
                        }
                        if(start_color == 'B') // B인경우. G,R인경우 둘다 스킵
                        {
                            if(board[nx][ny] == 'G' || board[nx][ny] == 'R') { continue; } 
                        }
                        vis2[nx][ny] = 1;
                        Q2.push({nx, ny});
                    }
                }
                count2++;
            }
        }
    }

    cout << count1 << " " << count2; 
    return 0;
}