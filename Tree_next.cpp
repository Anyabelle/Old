#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;

int root, treesize;

struct Node
{
    int x, y;
    int l, r;
    Node()
    {
        y = rand();
        l = -1;
        r = -1;
    }
};

Node tree[500000];

int merge(int l, int r)
{
    if (l == -1)
        return r;
    if (r == -1)
        return l;
    if (tree[l].y > tree[r].y)
    {
        tree[l].r = merge(tree[l].r, r);
        return l;
    }
    else
    {
        tree[r].l = merge(l, tree[r].l);
        return r;
    }
}

pair <int, int> split(int root, int a)
{
    pair <int, int> b;
    pair <int, int> c;
    if (root == -1)
        return(make_pair(-1, -1));
    if (tree[root].x > a)
    {
        b = split(tree[root].l, a);
        c.first = b.first;
        tree[root].l = b.second;
        c.second = root;
    }
    else
    {
        b = split(tree[root].r, a);
        c.second = b.second;
        tree[root].r = b.first;
        c.first = root;
    }
    return c;
}

void add(int v)
{
    treesize++;
    tree[treesize - 1].x = v;
    tree[treesize - 1].y = rand();
    tree[treesize - 1].l = -1;
    tree[treesize - 1].r = -1;
    pair <int, int> a;
    a = split(root, v);
    a.first = merge(a.first, treesize - 1);
    root = merge(a.first, a.second);
}

bool find(int root, int a)
{
    if (root == -1)
        return false;
    if (tree[root].x == a)
    {
        return true;
    }
    if (tree[root].x > a)
    {
        return find(tree[root].l, a);
    }
    else
    {
        return find(tree[root].r, a);
    }
}

int next(int root, int a, int last)
{
    if (root == -1)
    {
        return last;
    }
    if (tree[root].x == a)
    {
        return a;
    }
    if (tree[root].x > a)
    {
        return next(tree[root].l, a, tree[root].x);
    }
    else
    {
        return next(tree[root].r, a, last);
    }
}

void print(int root, int h)
{
    if (root != -1)
    {
        print(tree[root].l, h + 1);
        for (int i = 0; i < h; i++)
            cout << "**";
        cout << tree[root].x << " " << tree[root].y << " " << h << endl;
        print(tree[root].r, h + 1);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    treesize = 0;
    srand(time(0));
    root = -1;
    string s;
    int a;
    int n;
    char last = '+';
    int lastres = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        cin >> a;
        if (s == "+")
        {
            if (last == '+')
            {
                if (! find(root, a))
                {
                    add(a);
                }
            }
            else
            {
                a = (a + lastres) % 1000000000;
                if (! find(root, a))
                {
                    add(a);
                }
            }
            last = '+';
        }
        if (s == "?")
        {
            lastres = next(root, a, -1);
            last = '?';
            cout << lastres << endl;
        }
    }
    return 0;
}
