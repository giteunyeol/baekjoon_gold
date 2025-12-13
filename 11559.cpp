#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

#define X first
#define Y second

char board[12][6];             // row : 12, column : 6
bool boom[12][6];              // 이번턴에 터트릴지, 안터트릴지가 중요하지 거리는 판별하지 않기때문에 vis으로 만들필요 없음.
bool vis[12][6];
int ans = 0; // 답 카운트할 변수

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

bool stop()
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (boom[i][j] == true)
            {
                return false;
            } // 터칠 뿌요가 있다면 false를 리턴함.
        }
    }
    return true; // 다 순회했다면 터칠게 없다는 뜻이니 트루를 리턴
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cin >> board[i][j];
        }
    }

    while (true)
    {
        // BFS
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (board[i][j] != '.' && boom[i][j] == false) // 색깔일 경우 , 폭탄이 방문하지 않은 경우 bfs를 돌림
                {
                    char cur_color = board[i][j]; // 현재 컬러를 cur_color에 저장
                    vector<pair<int, int>> over_4; // 4개 이상인지 판별해줄 벡터.각 좌표를 세이브함
                    queue<pair<int, int>> Q;
                    vis[i][j] = true;
                    Q.push({i, j});
                    over_4.push_back({i, j});
                    while (!Q.empty())
                    {
                        pair<int, int> cur = Q.front();
                        Q.pop();
                        for (int dir = 0; dir < 4; dir++)
                        {
                            int nx = cur.X + dx[dir];
                            int ny = cur.Y + dy[dir];
                            if (nx < 0 || nx >= 12 || ny < 0 || ny >= 6)
                            {
                                continue;
                            } // 배열의 바깥을 벗어나는 경우 continue;
                            if (vis[nx][ny] || board[nx][ny] != cur_color)
                            {
                                continue;
                            } // 현재 좌표의 색이 판별해야할 색과 다르면! 컨티뉴
                            vis[nx][ny] = true;
                            Q.push({nx, ny});
                            over_4.push_back({nx, ny});
                        }
                    }
                    //벡터 사이즈가 4 이상이면 좌표들을 트루로 덮어씌움.
                    if (over_4.size() >= 4)
                    {
                        for (int k = 0; k < over_4.size(); k++)
                        {
                            boom[over_4[k].X][over_4[k].Y] = true;
                        }
                    }
                    memset(vis, false, sizeof(vis)); // 방문했던 기록 초기화
                }
            }
        }
        if (stop())     // 종료할지 말지 판별하는 함수
        {
            cout << ans;
            return 0;
        }
        else // 아니면 답을 하나 더해준다.
        {
            ans++;
        }
        // 뿌요 이동. BFS를 돌면서 현재 터트려야할곳은 boom[i][j]의 값이 true로 돼있음.
        // 아래로만 밀면 돼잖아?
        for (int column = 0; column < 6; column++) // 각 열을 차례대로 판별함.
        {
            vector<char> color_str;
            for (int row = 11; row >= 0; row--)
            {
                if (boom[row][column] == false) // 터트리지 않는 색이라면.
                {
                    color_str.push_back(board[row][column]); // color에 푸쉬
                }
            }
            // 한줄을 입력받았으니 덮어쓰기
            for (int k = 11; k > 11 - color_str.size(); k--)
            {
                board[k][column] = color_str[11-k];
            }
            for (int k = 11 - color_str.size(); k >= 0; k--)
            {
                board[k][column] = '.';
            }
        }
        // 한턴이 끝났으니 초기화
        memset(boom, false, sizeof(boom)); // boom의값들 초기화
    }
    return 0;
}