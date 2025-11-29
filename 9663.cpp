#include <iostream>

using namespace std;

//행이 x, y는 열
bool used1[50]; // 열을 카운트. isused1의 좌표 : y
bool used2[50]; // 우상을 향하는 대각선 판별 : x + y
bool used3[50]; // 우하를 향하는 대각선 판별 : x - y + n - 1

int n; //놓아야할 퀸의 갯수
int cnt; // 시작 카운트는 0

void solve(int cur) 
{
    if(cur == n) // 현재 상태가 퀸을 다 뒀을때
    {
        cnt++;
        return;
    }
    // 다 두지 않았을때
    for(int i = 0; i < n; i++) 
    {
        if(used1[i] || used2[i + cur] || used3[cur - i + n - 1]) { continue; }
        used1[i] = true;
        used2[i + cur] = true;
        used3[cur - i + n - 1] = true;
        solve(cur + 1);
        used1[i] = false;
        used2[i + cur] = false;
        used3[cur - i + n - 1] = false;
    }
    
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    solve(0);
    cout << cnt;

    return 0;
}