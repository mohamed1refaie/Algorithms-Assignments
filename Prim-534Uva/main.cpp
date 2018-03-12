// GROUP:   4
// ID:      20150204
// ID2:     20150337
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name1:   Mohamed Ashraf AbdElHady
// Name2:   Mohamed Sayed Mohamed
// UVA Username: mohamedrefaie

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>

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


struct Edge
{
    int		v;  // id of the adjacent node
    double	w;  // edge weight = distance between the two nodes
};

struct node
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

template<class Elem>
struct Heap
{
    Array<Elem> a;
    int next=0;
    int size() {
        return next;
    }
    bool (*IsBefore)(Edge&, Edge&);
    void Initialize(bool (*_IsBefore)(Edge&, Edge&))
    {
        a.Initialize();
        IsBefore=_IsBefore;
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
        if (child1 < next && IsBefore(a[child1], a[small])) {
            small=child1;
        }
        if(child2< next&& IsBefore(a[child2],a[small]))
            small=child2;
        if(small!=ind)
        {
            swap(a[ind],a[small]);
            MoveDown(small);
        }

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
        if(next!=0)
            return a[0];
    }
    Elem RetrieveFirst()
    {
        if(next==0);
        else if (next==1)
        {
            next--;
            Elem ret=a[0];
            a.RemoveLast();
            return ret;
        }
        Elem ret=a[0];
        next--;
        a[0]=a[next];
        a.RemoveLast();
        MoveDown(0);
        return  ret;
    }
};
bool IsBefore(Edge& a, Edge& b)
{
    return a.w<b.w;
}

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100);

double distance(int x1,int y1,int x2,int y2)
{
    return sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
}

struct Pair
{
    int f,s;
};

double prim(Graph g)
{
    Heap<Edge>pq;
    bool *vis=new bool[g.n];
    double *distance=new double[g.n];
    memset(vis, 0, sizeof(bool) * g.n);
    pq.Initialize(&IsBefore);
    Edge e={0,0};
    pq.Add(e);
    double total=0;
    while(pq.size()>0)
    {
        double frontcost=pq.GetFirst().w;
        int frontidx=pq.GetFirst().v;
        pq.RetrieveFirst();
        if(vis[frontidx]++)continue;
        total+=frontcost;
        for(int i=0;i<g.nodes[frontidx].adj.size();i++)
        {
            int child=g.nodes[frontidx].adj[i].v;
            double cost=g.nodes[frontidx].adj[i].w;
            e={child,cost};
            if(!vis[child])pq.Add(e);
        }
    }
    return total;
}



int main()
{
    freopen("input.in","rt",stdin);
    int n,x,y;
    while(cin>>n&&n) {
        Graph g;
        g.Initialize(n);
        Pair* arr=new Pair[n];
        for(int i=0;i<n;i++) {
            cin >> x >> y;
            arr[i]={x,y};
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i==j)continue;
                double dist=distance(arr[i].f,arr[i].s,arr[j].f,arr[j].s);
                Edge e={j,dist};
                cout<<i<<" - "<<j<<" "<<dist<<endl;
                g.nodes[i].adj.AddLast(e);
            }
        }
        cout<<prim(g)<<endl;
        string s;
        cin.ignore();
        getline(cin,s);

    }

    return 0;
}


