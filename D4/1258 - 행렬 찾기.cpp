#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

struct mat {
    int r;
    int c;
    int s; //크기

    bool operator <(const mat &ano) const {

        if(s == ano.s) {
            return r < ano.r;
        }
        return s < ano.s;

    }
};
mat m[21];

int n;
int visit[101][101];
int board[101][101];

void get_row(int t, int x, int y)
{
    int rr = x, cc = y;

    while(board[rr][cc + 1] != 0) {

        if(cc + 1 <= n) {
            cc++;
            visit[rr][cc] = 1;
        }
        else {
            break;
        }
    }

    while(board[rr + 1][y] != 0) {
        if(rr + 1 <= n) {
            rr++;
            for(int j = y; j <= cc; j++) {
                visit[rr][j] = 1;
            }
        }
        else { break; }
    }


    rr = rr - x + 1;
    cc = cc - y + 1;

    m[t].r = rr;
    m[t].c = cc;
    m[t].s = rr * cc;

}

int main()
{
    int tc;
    scanf("%d", &tc);

    for(int c = 1; c <= tc; c++) {
        scanf("%d", &n);

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                scanf("%d", &board[i][j]);
            }
        }

        int t = 0;

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(board[i][j] != 0 && visit[i][j] == 0) {
                    get_row(t, i, j);
                    t++;
                    visit[i][j] = 1;
                }
            }
        }

        sort(m, m + t);
        printf("#%d %d ", c, t);

        for(int i = 0; i < t; i++) {
            printf("%d %d ", m[i].r, m[i].c);
        }
        printf("\n");

        memset(visit, 0, sizeof(visit));
        memset(board, 0, sizeof(board));
    }

    return 0;
}
