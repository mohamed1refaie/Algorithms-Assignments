// GROUP:   4
// ID:      20150204
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Mohamed Ashraf Abdelhady

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
    bool Union(int i, int j)
    {
        int a=Find(i);
        int b=Find(j);
        if(a==b)
        {
            return false;
        }
        if(num_nodes[a]>=num_nodes[b])
        {
            parent[b]=a;
            num_nodes[a]+=num_nodes[b];
            return true;
        }
        else
        {
            parent[a]=b;
            num_nodes[b]+=num_nodes[a];
            return true;
        }
    }
};


template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid=(n-1)/2;
    int firstsz=mid+1;
    int secondsz=n-(mid+1);
    Type *firstarr= new Type[firstsz];
    Type *secondarr=new Type [secondsz];
    int i=0;
    for(;i<firstsz;i++)
    {
        firstarr[i]=a[i];
    }
    for(int j=0;j<secondsz;j++,i++)
        secondarr[j]=a[i];
    i=0;
    int j=0,k=0;
    while(i<firstsz&&j<secondsz)
    {
        if(IsBefore(secondarr[j],firstarr[i]))
        {
            a[k++]=secondarr[j++];
        }
        else
        {
            a[k++]=firstarr[i++];
        }
    }
    while (i < firstsz)
    {
        a[k++] = firstarr[i++];
    }
    while(j<secondsz)
    {
        a[k++]= secondarr[j++];
    }

}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    if(n>1)
    {
        int mid=(n-1)/2;
        int firstsz=mid+1;
        int secondsz=n-(mid+1);
        Type *firstarr= new Type[firstsz];
        Type *secondarr=new Type [secondsz];
        int i=0;
        for(;i<firstsz;i++)
        {
            firstarr[i]=a[i];
        }
        for(int j=0;j<secondsz;j++,i++)
            secondarr[j]=a[i];
        MergeSort(firstarr,firstsz,IsBefore);
        MergeSort(secondarr,secondsz,IsBefore);
        i=0;
        for(;i<firstsz;i++)
        {
            a[i]=firstarr[i];
        }
        for(int j=0;j<secondsz;j++,i++)
            a[i]=secondarr[j];
        Merge(a,n,IsBefore);
    }
    
}


struct Edge
{
    int u, v;
    int w;
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
    return a.w<b.w;
}



int main()
{

   // freopen("input.in","rt",stdin);
  //  freopen("output.out","wt",stdout);
    int n,m;
    while(cin>>n>>m)
    {
        if(n==0&&m==0)break;
        DisjointSets ds;
        ds.Initialize(n);
        Edge *edges=new Edge[m];
        Edge x;
        int total=0;
        for(int i=0;i<m;i++)
        {
            cin>>x.u>>x.v>>x.w;
            total+=x.w;
            edges[i]=x;
        }
        MergeSort(edges,m,&IsBeforeEdge);
        int mst=0;
        for(int i=0;i<m;i++)
        {
            if(ds.Union(edges[i].u,edges[i].v))mst+=edges[i].w;
        }
        cout<<total-mst<<endl;
    }



    return 0;
}


