#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int dist[200002];

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k; // N : 수빈이 위치, K : 동생위치

    if (n == k)
    {
        cout << 0;
        return 0;
    }
    fill(dist, dist + 200002, -1);

    queue<int> Q;
    dist[n] = 0;
    Q.push(n);

    while (!Q.empty())
    {
        int cur = Q.front();
        Q.pop();
        // -1, +1, n * 2로 이동해야함.
        int next[3] = {cur - 1, cur + 1, cur * 2};
        for (int move : next)
        {
            if (move < 0 || move >= 200002)
            {
                continue;
            }
            if (dist[move] >= 0)
            {
                continue;
            } // 방문한적이 있는경우 스킵
            if (move == k)
            {
                cout << dist[cur] + 1;
                return 0;
            }
            dist[move] = dist[cur] + 1;
            Q.push(move);
        }
    }

    return 0;
}