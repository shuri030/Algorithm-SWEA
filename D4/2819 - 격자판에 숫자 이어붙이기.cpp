#include <stdio.h>
#include <iostream>
#include <set>
#include <queue>
using namespace std;

int n;
int board[4][4];
int m[7] = { 1000000, 100000, 10000, 1000, 100, 10, 1 };
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
set<int> s;

void cnt_number(int x, int y, int num, int c)
{
    if (c >= 7) {
        //num += board[x][y] * m[c];
        s.insert(num);
        return;
    }
    int xx, yy;

    for (int k = 0; k < 4; k++) {
        xx = x + dx[k]; yy = y + dy[k];
        if (xx >= 0 && yy >= 0 && xx < 4 && yy < 4) {
            num += board[xx][yy] * m[c];
            cnt_number(xx, yy, num, c + 1);
            num -= board[xx][yy] * m[c];
        }
    }
}
int main()
{
    int tc;
    scanf("%d", &tc);

    for (int t = 1; t <= tc; t++) {

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                scanf("%d", &board[i][j]);
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cnt_number(i, j, board[i][j] * m[0], 1);
            }
        }

        /*for (auto it = s.begin(); it != s.end(); it++)
        {
            std::cout << *it << ' ';
        }*/

        printf("#%d %d\n", t, s.size());
        s.clear();
    }
    return 0;
}
