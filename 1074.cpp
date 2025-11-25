#include <iostream>

using namespace std;

int Z(int n, int r, int c)
{
    int half = 1 << (n - 1);
    
    //base case
    if(n == 0) { return 0; }

    //재귀
    //좌상
    if(r < half && c < half)
    {
        return Z(n - 1, r, c);
    }
    //우상
    if(r < half && c >= half)
    {
        return half * half + Z(n-1, r, c - half);
    }
    //좌하
    if(r >= half && c < half)
    {
        return 2 * half * half + Z(n-1, r - half, c);
    }
    //우하
    return 3 * half * half + Z(n-1, r- half, c - half);
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, r, c;
    cin >> n >> r >> c;
    cout << Z(n, r, c);

    return 0;
}