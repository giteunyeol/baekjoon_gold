#include <iostream>
#include <algorithm>

using namespace std;

#define X first // 행과 열
#define Y second

int n, m, k;                      // n은 노트북의 행, m은 열, k는 스티커의 갯수
int notebook[42][42];             // 그냥 여유롭게 notebook의 크기 선언
int sticker[102][12][12];         // [n번째 스티커][n번째 스티커의 행][n번째 스티커의 열]
int temp_sticker[12][12];         // change_angle을 할때 배열을 담아줄 임시변수
pair<int, int> sticker_size[102]; // 각 스티커의 행과 열 세이브. sticker_size[input]값에 행, 열의 크기가 세이브 돼있음.
int ans = 0;                      // 스티커가 붙은 칸의 수

void change_angle(int stc) // 90도 회전 함수. 아... 90도 회전하면 sticker_size행 열 체인지도 해줘야하네;; 걍 구현 지옥이다
{
    int row_old = sticker_size[stc].X; //원형의
    int column_old = sticker_size[stc].Y;
    
    for(int r = 0; r < row_old; r++)
    {
        for(int c = 0; c < column_old; c++)
        {
            temp_sticker[c][row_old -1 -r] = sticker[stc][r][c];
        }
    }

    sticker_size[stc] = {column_old, row_old};

    int row = sticker_size[stc].X;
    int column = sticker_size[stc].Y; 
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            sticker[stc][i][j] = temp_sticker[i][j];
        }
    }
}

// 현재 스티커를 노트북에 채울 수 있는지 없는지 판별하는 함수.
bool detect(int r, int c, int stc) // 현재 스티커의 좌표와 노트북을 비교해주는 함수.
{
    // 현재 스티커의 크기만큼 비교
    for (int i = 0; i < sticker_size[stc].X; i++)
    {
        for (int j = 0; j < sticker_size[stc].Y; j++)
        {
            if (sticker[stc][i][j] == 1 && notebook[r + i][c + j] == 1)
            {
                return false;
            } // 현재 스티커의 i, j행이 1일때(채워져 있을때), 노트북도 1이면. false 리턴
        }
    }
    return true; // 다 통과하면 채울 수 있다는 뜻이니 true를 리턴함.
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> k; // n : 노트북의 세로, m : 노트북의 가로, k : 스티커의 갯수

    for (int input = 0; input < k; input++) // 입력받음
    {
        int r, c; // input번째 스티커의 행, 열
        cin >> r >> c;
        sticker_size[input] = {r, c}; // row, low 세이브
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                cin >> sticker[input][i][j];
            }
        }
    }

    for (int stc = 0; stc < k; stc++) // 스티커의 갯수
    {
        bool flag = false;
        for (int angle = 0; angle < 4; angle++) // angle이 0일때는 0도, 1일때는 90, 2 -> 180, 3 -> 270.
        {
            for (int row = 0; row <= n - sticker_size[stc].X; row++) // 현재 스티커가 검사 시작할 좌상단 좌표
            {
                for (int column = 0; column <= m - sticker_size[stc].Y; column++)
                {
                    // 현재좌상단 시작 좌표 : (row, column).
                    if (detect(row, column, stc)) // 현재 좌상단좌표와, 현재 스티커가 몇번째인지 넘겨줌
                    {
                        // detect를 넘겼는데 true가 나온경우.(채울 수 있는 경우.). false가 나온경우 그냥 다음 좌표로 넘어가면 되기 때문에 생략
                        flag = true;
                        for (int i = 0; i <  sticker_size[stc].X; i++) // i는 노트북에 채울 행 좌표, y는 열
                        {
                            for (int j = 0; j < sticker_size[stc].Y; j++)
                            {
                                if (sticker[stc][i][j] == 1)
                                {
                                    notebook[row + i][column + j] = 1; // notebook에 덮어씌우기
                                }
                            }
                        }
                    }
                    if (flag == true)
                    {
                        break;
                    } // flag가 트루가 되면 이번 스티커는 채웠다는거니 탈출
                }
                if (flag == true)
                {
                    break;
                }
            }
            if (flag == true)
            {
                break;
            }
            change_angle(stc); // 90도 회전
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (notebook[i][j] == 1) // 노트북에 스티커가 붙어있으면
            {
                ans++;
            }
        }
    }
    cout << ans;
    return 0;
}