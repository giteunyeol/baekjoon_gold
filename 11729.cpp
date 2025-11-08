#include <iostream>

using namespace std;

void answer(int a,int b,int n)
{
    if(n == 1)
    {
        cout << a << ' ' << b << '\n';
        return;
    }

    //rec
    answer(a, 6-a-b, n-1);
    cout << a << ' ' << b <<  '\n';
    answer(6-a-b, b, n-1);
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int n;
    cin >> n;

    //n : 몇개인지, a: 옮기는 시작 원판, b:도착하는  원판
    int count = 1;
    for(int i = 0; i < n; i++)
    {
        count = count * 2;
    }
    cout << count - 1 << "\n";
    answer(1, 3, n);
    return 0;
}