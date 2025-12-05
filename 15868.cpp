#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

pair<int, int> arr[15];          // 현재 셀렉하고있는 치킨집 좌표
pair<int, int> chicken_save[15]; // 치킨집 좌표들 세이브
pair<int, int> house_save[102];  // 집의 최대갯수 50 * 2, 각 집의 좌표 저장

int chicken_save_flag = 0, house_save_flag = 0; // 저장할 좌표 옮기기
int n, m;
int ans = 1e9; // 마지막에 출력할 답. 시작 ans값은 완전 큰 값

// 행 : i, 열 : j

void solve(int cur, int start) // 현재 cur번째 치킨집을 가리키는중
{
    // basecase
    if (cur == m) // 치킨집을 다 고르면, 현재 arr에 m개만큼 치킨이 셀렉돼있는 상태임.
    {
        int cur_chicken_distance = 0;
        for (int i = 0; i < house_save_flag; i++) // house_save_flag에 집(1)이 몇갠지 세이브 돼 있음.
        {
            int plus_distance = 1e9; // 현재 집에서 최단거리 넣어줄 변수
            // int cur_distance;
            for (int j = 0; j < m; j++) // 각각 비교. 치킨집 순회 // j < m 부분에 chicken_save_flag를 넣으면 모든 치킨집의 갯수만큼 판별해버림. 그래서 m으로 하는게 맞나봄
            {
                // cur_distance = abs(house_save[i].first - arr[j].first) + abs(house_save[i].second - arr[j].second);
                plus_distance = min(plus_distance, abs(house_save[i].first - arr[j].first) + abs(house_save[i].second - arr[j].second));
            }
            cur_chicken_distance += plus_distance;
        }
        ans = min(ans, cur_chicken_distance); // 비교한 다음 리턴
        return;
    }

    for (int k = start; k < chicken_save_flag; k++)
    {
        arr[cur] = {chicken_save[k].first, chicken_save[k].second};
        solve(cur + 1, k + 1);
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;

    int temp; // 굳이 보드에 저장할 필요 없이 i, j좌표만 저장하면 되니까.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> temp;   // i, j입력
            if (temp == 2) // 치킨집이라면
            {
                chicken_save[chicken_save_flag] = {i, j};
                chicken_save_flag++;
            }
            else if (temp == 1) // 일반 집이라면
            {
                house_save[house_save_flag] = {i, j};
                house_save_flag++;
            }
        }
    }

    // 백트래킹으로 on off
    // 순서를 상관하지 않으니 조합 백트래킹임.
    solve(0, 0); // 0, 0부터 시작

    cout << ans;

    return 0;
}