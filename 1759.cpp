#include <iostream>
#include <algorithm>

using namespace std;

char str[20];
char arr[20]; // 문자를 넣었다 뺐다 할 배열
int l, c;     // L개는 몇개를 고르는지, C개는 총 몇번 입력받는지
// 한개의 모음 이상, 두개의 자음 이상.
int consonants, vowel; // 자음이랑 모음 카운트

// 조합임. 순열 X
void solve(int cur, int start)
{
    if (cur == l) // basecase
    {
        for (int i = 0; i < l; i++)
        {
            if (arr[i] == 'a' || arr[i] == 'e' || arr[i] == 'i' || arr[i] == 'o' || arr[i] == 'u')
            {
                consonants++;
            }
            else
            {
                vowel++;
            }
        }
        if (consonants >= 1 && vowel >= 2)
        {
            for (int i = 0; i < l; i++)
            {
                cout << arr[i];
            }
            cout << "\n";
        }
        //초기화
        consonants = 0, vowel = 0;
        return;
    }

    // 문자열 갯수를 채우지 못했다면
    for (int i = start; i < c; i++)
    {
        arr[cur] = str[i];
        solve(cur + 1, i + 1);
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> l >> c;
    for (int i = 0; i < c; i++)
    {
        cin >> str[i];
    }
    sort(str, str + c);
    solve(0, 0);

    return 0;
}