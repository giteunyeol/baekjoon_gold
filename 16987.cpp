#include <iostream>
#include <algorithm>

using namespace std;

int n;
int d[10], w[10]; // 각 계란의 durability, weight;
int max_broken_egg, broken_egg; //최대로 부쉈던 계란과 현재 다 부서진 계란 

//순열 변형
void solve(int cur) // 현재 들고있는 계란
{
    if(cur == n) // 가장 오른쪽 계란 도착
    {
        max_broken_egg = max(max_broken_egg, broken_egg);
        return;
    }
    if(d[cur] <= 0 || broken_egg == n - 1) // 2번조건
    {   
        solve(cur + 1); 
        return; 
    }
    //백트래킹
    for(int i = 0; i < n; i++) // i: 현재 때릴 계란 인덱스
    {
        if(cur == i || d[i] <= 0) { continue; } // 손에 든 계란과 때릴 계란이 같거나, 때릴 계란이 깨졌으면
        d[cur] -= w[i];
        d[i] -= w[cur];
        if(d[i] <= 0) { broken_egg++; } // 깨지면
        if(d[cur] <= 0) { broken_egg++; }
        solve(cur + 1);
        if(d[i] <= 0) { broken_egg--; }
        if(d[cur] <= 0) { broken_egg--; }
        d[cur] += w[i]; //다시 돌아옴
        d[i] += w[cur]; 
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> d[i] >> w[i];
    }

    solve(0);
    cout << max_broken_egg;

    return 0;
}
