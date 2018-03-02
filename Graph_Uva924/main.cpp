// GROUP:   4
// ID:      20150204
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Mohamed Ashraf AbdelHady

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

template<class Value>
struct Array
{
    int  n, sz;
    Value* arr;
    void expand(int newsz)
    {
        Value* newarr;
        newarr = new Value[newsz];
        for(int i=0;i<sz;i++)
            newarr[i]=arr[i];
        delete[]arr;
        arr=newarr;
        sz=newsz;
    }
    int size()
    {
        return n;
    }
    void Initialize()
    {
        n=0;
        sz=1;
        arr=new Value[sz];
    }
    void Destroy()
    {
        n=0;
        delete []arr;
    }
    void AddLast(Value v)
    {
        if(n==sz)
        {
            expand(2*sz);
        }
        arr[n++]=v;
    }
    void RemoveLast()
    {
        n--;
    }
    Value& operator[](int i)
    {
        return arr[i];
    }
};

struct node
{
    Array<int>adj;
    void Initialize()
    {
        adj.Initialize();
    }
    void Destroy()
    {
        adj.Destroy();
    }
};

struct Graph {
    int n;
    node *nodes;

    void Initialize(int _n) {
        n = _n + 1;
        nodes = new node[n];
        for (int i = 0; i < n; i++)
            nodes[i].Initialize();
    }

    void Destroy()
    {
        for(int i=0;i<n;i++)
            nodes[i].Destroy();
        delete[]nodes;
    }

};


template <class Type>
struct Queue
{
	int f, n,sz;
	Type* elems;
	void Initialize(int size)
    {
        elems=new Type[size+10];
        n=-1;
        f=-1;
        sz=size+10;
    }
	void Destroy()
    {
        delete[]elems;
    }
	void Add(Type t)
    {
        if(n!=sz-1)
        {
            elems[++n]=t;
            if(f==-1)
                f=0;
        }
    }
	Type Pop()
    {
        Type ret=elems[f];
        if(n!=-1)
        {
            if(f==n)
            {
                f=-1;
                n=-1;
            }
            else f++;
        }
        return ret;
    }
	Type Peek()
    {
        return elems[f];
    }
	int Num()
    {
        if(f==-1)return 0;
        else return (n-f)+1;
    }
};

struct couple
{
    int first,second;
};

couple bfs(Graph &g,int s) {
    Queue<int> q;
    q.Initialize(g.n);
    bool *vis = new bool[g.n + 1];
    memset(vis, 0, sizeof(bool) * g.n);
    vis[s] = 1;
    q.Add(s);
    int day = 0, sz=1, front,maxboom=0,firstday=0;
    for (; q.Num() > 0; sz = q.Num(), ++day)
    {
        if(sz>maxboom&&day>0)
        {
            maxboom=sz;
            firstday=day;
        }
        while(sz--)
        {
            front=q.Pop();
            for(int i=0;i<g.nodes[front].adj.n;i++)
            {
                int child=g.nodes[front].adj[i];
                if(!vis[child])
                {
                    vis[child]=1;
                    q.Add(child);
                }
            }
        }
    }
    couple ret;
    ret.first=maxboom;
    ret.second=firstday;
    return ret;


}

int main()
{

   // freopen("input.in","rt",stdin);
   // freopen("output.out","wt",stdout);
    Graph g;
    int n,x,y;
    cin>>n;
    g.Initialize(n);
    for(int i=0;i<n;i++)
    {
        cin>>x;
        for(int j=0;j<x;j++)
        {
            cin>>y;
            g.nodes[i].adj.AddLast(y);
        }
    }
    int q;
    cin>>q;
    while(q--)
    {
        cin>>x;
        couple ret=bfs(g,x);
        if(ret.second==0)cout<<0<<endl;
        else cout<<ret.first<<" "<<ret.second<<endl;
    }

	return 0;
}

