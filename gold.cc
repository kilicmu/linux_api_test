#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = (1 << 30);
int n, val[11111]; //金块个数,每块金块的重量
void Bin(int l, int r, int &_max, int &_min, int &cnt_max, int &cnt_min)
{
    if (l == r)
    {
        _max = _min = val[l];
        cnt_max = cnt_min = l;
        return;
    }
    if (l + 1 == r)
    {
        if (val[l] > val[r])
        {
            _max = val[l], cnt_max = l;
            _min = val[r], cnt_min = r;
        }
        else
        {
            _max = val[r], cnt_max = r;
            _min = val[l], cnt_min = l;
        }
        return;
    }
    int mid = (l + r) >> 1;
    int ha, la, hb, lb;
    int cnt_ha, cnt_la, cnt_hb, cnt_lb;
    Bin(l, mid, ha, la, cnt_ha, cnt_la);
    Bin(mid + 1, r, hb, lb, cnt_hb, cnt_lb);
    if (ha > hb)
        _max = ha, cnt_max = cnt_ha;
    else
        _max = hb, cnt_max = cnt_hb;
    if (la < lb)
        _min = la, cnt_min = cnt_la;
    else
        _min = lb, cnt_min = cnt_lb;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    int _max, _min;
    int cnt_max, cnt_min;
    _max = -inf, _min = inf;
    Bin(1, n, _max, _min, cnt_max, cnt_min);
    cout << cnt_max << " " << _max << " " << cnt_min << " " << _min << endl;
    return 0;
}