#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

int root, treesize;

struct Node
{
    int y, l, r, size, num, mini;
    Node()
    {
        int y = rand();
        int size = 0;
        int mini = 2000000000;
        int l = -1;
        int r = -1;
        num = 0;
    }
};

Node tree[500000];

void update(int t)
{
    if (t != -1)
    {
        tree[t].size = tree[tree[t].l].size + tree[tree[t].r].size + 1;
        tree[t].mini = tree[t].num;
        if ((tree[t].l != -1) && (tree[tree[t].l].mini < tree[t].mini))
            tree[t].mini = tree[tree[t].l].mini;
        if ((tree[t].r != -1) && (tree[tree[t].r].mini < tree[t].mini))
            tree[t].mini = tree[tree[t].r].mini;
    }
}

int merge (int t1, int t2)
{
    if (t1 == -1)
        return t2;
    if (t2 == -1)
        return t1;
    if (tree[t1].y > tree[t2].y)
    {
        tree[t1].r = merge(tree[t1].r, t2);
        update(t1);
        return t1;
    }
    else
    {
        tree[t2].l = merge(t1, tree[t2].l);
        update(t2);
        return t2;
    }
}

pair <int, int> split (int t, int k)
{
    if (t == -1)
    {
        //cout << "odjsl";
        return (make_pair(-1, -1));
    }
    if (tree[tree[t].l].size >= k)
    {
        pair <int, int> a = split(tree[t].l, k);
        tree[t].l = a.second;
        update(t);
        return (make_pair(a.first, t));
    }
    else
    {
        pair <int, int> a = split(tree[t].r, k - tree[tree[t].l].size - 1);
        tree[t].r = a.first;
        update(t);
        return(make_pair(t, a.second));
    }
}

int rmq(int t, int l, int r)
{
    pair <int, int> a = split(t, l - 1);
    pair <int, int> b = split(a.second, r - l + 1);
    int res = tree[b.first].mini;
    int c = merge(a.first, b.first);
    c = merge(c, b.second);
    return res;
}

void add(int t, int pos, int x)
{
    treesize++;
    tree[treesize - 1].y = rand();
    tree[treesize - 1].l = -1;
    tree[treesize - 1].r = -1;
    tree[treesize -1].size = 1;
    tree[treesize - 1].num = x;
    tree[treesize - 1].mini = x;
    //cout << "4 " << tree[treesize - 1].l << " " << tree[treesize - 1].r << endl;
    pair <int, int> a = split(t, pos);
    //cout << "5 " << tree[treesize - 1].l << " " << tree[treesize - 1].r << endl;
    //cout << " 1";
    int b = merge(a.first, treesize - 1);
    //cout << " 2";
    update(t);
    root = merge(b, a.second);
}

void print(int t, int h)
{
    if (t != -1)
    {
        //cout << "olo " << t << endl;
        print(tree[t].l, h + 1);
        for (int i = 0; i < h; i++)
            cout << "**";
        cout << tree[t].size << " " << tree[t].y << " " << tree[t].num << " " << tree[t].mini << endl;
        print(tree[t].r, h + 1);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    treesize = 0;
    root = -1;
    int n;
    srand(time(0));
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        int x, y;
        cin >> x >> y;
        if (s == "+")
        {
            add(root, x, y);
        }
        if (s == "?")
        {
            cout << rmq(root, x, y) << endl;;
        }
     //   cout << root << endl;
       // cout << tree[root].l << " " << tree[root].r << endl;
     //   print (root, 0);
    }
}
