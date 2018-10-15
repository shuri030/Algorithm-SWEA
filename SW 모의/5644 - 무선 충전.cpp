#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;

typedef struct Person {
    int x; //행
    int y; //열
    int sum;
}Person;

Person p[2];

vector<int> board[12][12];
int move_a[102];
int move_b[102];
int M, A;
int perform[10];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

bool isin(int x, int y) {
    if (x < 1 || y < 1 || x > 10 || y > 10)
        return false;
    return true;

}
//충전범위 계산
void cal_charge_Range(int x, int y, int con, int bc_num)
{
    int visit[12][12] = { 0, };
    int xx, yy, nx, ny;
    queue<pair<int, int> > q;
    q.push({ x, y });
    visit[x][y] = 1;

    while (!q.empty()) {
        xx = q.front().first; yy = q.front().second;
        q.pop();

        for (int k = 0; k < 4; k++) {
            nx = xx + dx[k]; ny = yy + dy[k];
            if (isin(nx, ny) && visit[nx][ny] == 0) {
                if (visit[xx][yy] < con + 1) {
                    visit[nx][ny] = visit[xx][yy] + 1;
                    q.push({ nx, ny });
                }
            }
        }
    }

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            if (visit[i][j] != 0) {
                board[i][j].push_back(bc_num);
            }
        }
    }
}

//사람 이동
void move(int k, int n)
{
    int m;
    if (k == 0) { m = move_a[n]; }
    else if (k == 1) { m = move_b[n]; }

    if (m == 0) { return; }
    else if (m == 1) {
        p[k].x--;
    }
    else if (m == 2) {
        p[k].y++;
    }
    else if (m == 3) {
        p[k].x++;
    }
    else if (m == 4) {
        p[k].y--;
    }
}
//이동한 사람의 위치의 충전량 비교
void compare(int t)
{
    int ax, ay, bx, by, n, max_a = 0, max_b = 0;
    int aa[9] = { 0, };
    int bb[9] = { 0, };

    ax = p[0].x; ay = p[0].y;
    bx = p[1].x; by = p[1].y;


    for (int i = 0; i < board[ax][ay].size(); i++) {
        n = board[ax][ay][i];
        aa[n] = perform[n];
    }

    for (int i = 0; i < board[bx][by].size(); i++) {
        n = board[bx][by][i];
        bb[n] = perform[n];
    }

    int max_sum = 0;

    for (int i = 1; i <= A; i++) {
        for (int j = 1; j <= A; j++) {
            if (i == j && aa[i] != 0 && bb[j] != 0) {
                if (aa[i] > max_sum) {
                    max_sum = aa[i];
                    max_a = aa[i] / 2; max_b = bb[j] / 2;
                }
            }
            else {
                if (aa[i] + bb[j] > max_sum) {
                    max_sum = aa[i] + bb[j];
                    max_a = aa[i]; max_b = bb[j];
                }
            }
        }
    }

    p[0].sum += max_a;
    p[1].sum += max_b;
}
int main()
{
    int tc, m, r, c, con, per;
    scanf("%d", &tc);

    for (int t = 1; t <= tc; t++) {

        scanf("%d %d", &M, &A);

        for (int i = 1; i <= M; i++) {
            scanf("%d", &move_a[i]);
        }

        //이동 방향 저장
        for (int i = 1; i <= M; i++) {
            scanf("%d", &move_b[i]);
        }

        //출발 위치 지정
        p[0].x = 1; p[0].y = 1;
        p[1].x = 10; p[1].y = 10;
        p[0].sum = p[1].sum = 0;

        for (int i = 1; i <= A; i++) {
            scanf("%d %d %d %d", &c, &r, &con, &per);
            perform[i] = per;
            cal_charge_Range(r, c, con, i); //충전범위 계산
        }

        int i = 0; //초
        while (i <= M) {

            //이동
            for (int k = 0; k < 2; k++) {
                move(k, i);
            }
            //bc 비교
            compare(i);

            i++;
        }

        printf("#%d %d\n", t, p[0].sum + p[1].sum);
        p[0].sum = p[1].sum = 0;
        memset(perform, 0, sizeof(perform));
        memset(move_a, 0, sizeof(move_a));
        memset(move_b, 0, sizeof(move_b));
        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                board[i][j].clear();
            }
        }
    }

    return 0;
}
