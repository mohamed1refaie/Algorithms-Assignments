// GROUP:   4
// ID:      20150204
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    Mohamed Ashraf AbdelHady
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n)
    {
        n=_n+1;
        parent= new int[n];
        num_nodes = new int[n];
        for(int i=0;i<n;i++) {
            parent[i] = -1;
            num_nodes[i]=1;
        }
    }
    void Destroy()
    {
        delete[]parent;
        delete[]num_nodes;
    }
    int Find(int i)
    {
        int p=i;
        while(parent[p]!=-1)p=parent[p];
        return p;
    }
    int Union(int i, int j)
    {
        int a=Find(i);
        int b=Find(j);
        if(a==b)
        {
            return num_nodes[a];
        }
        if(num_nodes[a]>=num_nodes[b])
        {
            parent[b]=a;
            num_nodes[a]+=num_nodes[b];
            return num_nodes[a];
        }
        else
        {
            parent[a]=b;
            num_nodes[b]+=num_nodes[a];
            return num_nodes[b];
        }
    }
};

int main()
{

    //freopen("input.in","rt",stdin);
  //  freopen("output.out","wt",stdout);
    int t,n,m,ret=0,x,y;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        ret=1;
        DisjointSets ds;
        ds.Initialize(n);
        for(int i=0;i<m;i++)
        {
            cin>>x>>y;
            ret=max(ret,ds.Union(x,y));
        }
        cout<<ret<<endl;
        ds.Destroy();
    }


    return 0;
}