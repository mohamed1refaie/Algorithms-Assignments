// GROUP:   4
// ID1:     20150204
// ID2:     20150337
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name1:   Mohamed Ashraf AbdElHady
// Name2:   Mohamed Sayed Mohamed
// UVA Username: mohamedrefaie

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



template<class Elem>
struct Heap
{
    Array<Elem> a;
    int* pos; // pos[v]=i where a[i].v=v, otherwise pos[v]=-1
    int next=0;
    int sz;
    int size() {
        return sz;
    }
    bool (*IsBefore)(Elem&, Elem&);
    void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n)
    {
        a.Initialize();
        IsBefore=_IsBefore;
        sz=n;
        pos= new int[n];
    }
    void Destroy()
    {
        a.Destroy();
    }
    int Child(int i)
    {
        return (2*i)+1;
    }
    int Parent(int i)
    {
        return (i-1)/2;
    }
    int  MoveUp(int ind)
    {
        swap(a[ind],a[Parent(ind)]);
        return Parent(ind);
    }
    void MoveDown(int ind)
    {
        int child1=Child(ind);
        int child2=child1+1;
        int small=ind;
        if (child1 < sz && IsBefore(a[child1], a[small])) {
            small=child1;
        }
        if(child2< sz && IsBefore(a[child2],a[small]))
            small=child2;
        if(small!=ind)
        {
            Elem e=a[small];
            Elem e2=a[ind];
            pos[e.v]=ind;
            pos[e2.v]=small;
            swap(a[ind],a[small]);
            MoveDown(small);
        }

    }
    void decreasekey(int v,int dist)
    {
        int i=pos[v];
        a[i].w=dist;
        while(i>=0&&a[i].w<a[Parent(i)].w)
        {
            pos[a[i].v]=Parent(i);
            pos[a[Parent(i)].v]=i;
            i=MoveUp(i);
        }
    }
    bool isInHeap(int v)
    {
        int x=pos[v];
        return pos[v]<sz;
    }
    void Add(Elem e)
    {
        a.AddLast(e);
        next++;
        int cur=next-1;
        while(cur!=0)
        {
            if(IsBefore(a[Parent(cur)],a[cur]))break;
            else
                cur=MoveUp(cur);
        }
    }
    Elem GetFirst()
    {
        if(sz!=0)
            return a[0];
    }
    Elem RetrieveFirst()
    {
        if(sz==0);
        else if (sz==1)
        {
            sz--;
            Elem ret=a[0];
            a.RemoveLast();
            return ret;
        }
        Elem ret=a[0];
        sz--;
        a[0]=a[sz];
        pos[a[sz].v]=0;

        a.RemoveLast();
        MoveDown(0);
        return  ret;
    }
};



struct Edge
{
    int		v;
    int		w;
};

struct Node
{
    Array<Edge>adj;
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
    Node *nodes;

    void Initialize(int _n) {
        n = _n ;
        nodes = new Node[n];
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


bool IsBefore(Edge& a, Edge& b)
{
    return a.w<b.w;
}

int dijkstra(Graph& g , int src,int dest)
{
    int v=g.n;
    int *dist=new int[v];

    Heap<Edge>h;
    h.Initialize(IsBefore,v);
    for(int i=0;i<v;i++)
    {
        dist[i]=1000000000;
        h.a.AddLast({i,dist[i]});
       // h.Add({i,dist[i]});
        h.pos[i]=i;
    }
    dist[src]=0;
    h.decreasekey(src,0);
    while(h.size()>0)
    {
        Edge e=h.RetrieveFirst();
        int v=e.v;
        for(int i=0;i<g.nodes[v].adj.size();i++)
        {
            int child=g.nodes[v].adj[i].v;
            int childcost=g.nodes[v].adj[i].w;
            bool first=h.isInHeap(child);
            bool second=dist[v]!=1000000000;
            bool third=childcost+dist[v]<dist[child];
            if(h.isInHeap(child)&&dist[v]!=1000000000&&childcost+dist[v]<dist[child])
            {
                int tst=childcost+dist[v];
                dist[child]=childcost+dist[v];
                h.decreasekey(child,dist[child]);
            }
        }
    }
    return dist[dest];
}


int main()
{
   // freopen("input.in","rt",stdin);
   // freopen("output.txt","wt",stdout);
    int t;
    cin>>t;
    int cnt=0;
    while(t--) {
        cnt++;
        int n, m,s,e,x,y,c;
        cin>>n>>m>>s>>e;
        Graph graph;
        graph.Initialize(n);
        for(int i=0;i<m;i++)
        {
            cin>>x>>y>>c;
            graph.nodes[x].adj.AddLast({y,c});
            graph.nodes[y].adj.AddLast({x,c});

        }

        cout<<"Case #"<<cnt<<": ";
        int ans=dijkstra(graph,s,e);
        if(ans==1000000000)cout<<"unreachable";
        else cout<<ans;
        cout<<endl;
    }
    return 0;
}


