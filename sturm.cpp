#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

pair <long long, pair <long long, long long> > a[200000];
long long l[200000];
long long from[200000];
pair <long long, long long> tree[500000];
long long d[200000], c[200000];

struct cmp1
{
    bool operator()(pair <long long, pair<long long, long long> > a, pair <long long, pair <long long, long long> > b)
    {
        return (a.second.first < b.second.first) || ((a.second.first == b.second.first) && (a.second.second > b.second.second));
    }
};

void init(long long v, long long l, long long r)
{
    if (l == r - 1)
    {
        tree[v].first = d[l];
        tree[v].second = l;
        return;
    }
    long long m = (l + r) / 2;
    init(2 * v + 1, l, m);
    init(2 * v + 2, m, r);
    if (tree[2 * v + 1].first > tree[2 * v + 2].first)
        tree[v] = tree[2 * v + 1];
    else
        tree[v] = tree[2 * v + 2];
}

void modify(long long l, long long r, long long v, long long p, long long w)
{
    if (l == r - 1)
    {
        tree[v].first = w;
        tree[v].second = p;
        return;
    }
    long long m;
    m = (l + r) / 2;
    if (p < m)
        modify(l, m, 2 * v + 1, p, w);
    else
        modify(m, r, 2 * v + 2, p, w);
    if (tree[2 * v + 1].first > tree[2 * v + 2].first)
        tree[v] = tree[2 * v + 1];
    else
        tree[v] = tree[2 * v + 2];
}

pair <long long, long long> getmax(long long l, long long r, long long v, long long a, long long b)
{
    pair <long long, long long> x;
    if ((l >= a) && (r <= b))
    {
        x = make_pair(tree[v].first, tree[v].second);
        return (x);
    }
    if ((l >= b) || (r <= a))
        return make_pair(0, -1);
    long long m;
    pair <long long, long long> max1, max2;
    m = (l + r) / 2;
    max1 = getmax(l, m, 2 * v + 1, a, b);
    max2 = getmax(m, r, 2 * v + 2, a, b);
    if (max1.first > max2.first)
        return max1;
    else
        return max2;
}


int main()
{
    long long n, i, x, k, b, m;
    cin >> n;
    //init(0, 0, n);
    //for (i = 0; i < 4 * n; i++)
    //    cout << tree[i].first << " " << tree[i].second << endl;
    for (i = 0; i < n; i++)
        cin >> a[i].first;
    for (i = 0; i < n; i++)
        cin >> a[i].second.first;
    for (i = 0; i < n; i++)
        a[i].second.second = i;
    sort(a, a + n, cmp1());
    for (i = 0; i < n; i++)
    {
        {
            //cout << "aaa";
            d[a[i].second.second] = getmax(0, n, 0, 0, a[i].second.second).first + a[i].first;
            from[a[i].second.second] = getmax(0, n, 0, 0, a[i].second.second).second;
            modify(0, n, 0, a[i].second.second, d[a[i].second.second]);
            //for (long long j = 0; j < 3 * n; j++)
              //  cout << tree[j].first << " " << tree[j].second << " - ";
            //cout << endl;
            //cout << getmax(0, n, 0, 0, a[i].second.second).first << " " << getmax(0, n, 0, 0, a[i].second.second).second << endl;
        }
    }
    long long maxi = -200000000;
    long long num = -1;
    long long cnt = 0;
    for (i = 0; i < n; i++)
        if (d[i] > maxi)
        {
            maxi = d[i];
            num = i;
        }
    long long num1 = num;
    vector <long long> vv;
    while (num > -1)
    {
        //cout << num << endl;
        vv.push_back(num);
        cnt ++;
        num = from[num];
    }
    cout << maxi << endl;
    cout << cnt << endl;
    for (i = vv.size() - 1; i >= 0; i--)
        cout << vv[i] + 1 << " ";
    //for (i = 0; i < n; i++)
      //  cout << d[i] << " ";
    //cout << endl;
    //for (i = 0; i < n; i++)
      //  cout << from[i] << " ";
    //cout << maxi;
}
