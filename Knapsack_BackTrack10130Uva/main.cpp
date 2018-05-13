// GROUP:   4
// ID:      20150204
// Assign:  12
// Assign:  KnapsackBT
// UVA:     10130
// Name:    Mohamed Ashraf AbdElHady
// UVA Username: mohamedrefaie

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;


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

struct Obj
{
	int v;
	int w;
};

int n;       // number of objects (input)
Obj a[1000]; // objects (input)

bool IsBefore(Obj& a, Obj& b) // return true if unit value of a is greater than unit value of b
{
    double first=a.v*1.0/a.w*1.0;
    double second=b.v*1.0/b.w*1.0;
    if(first>second)return true;
    else if(first==second)return a.v>b.v;
    else return false;
}

int best_val; // the best total value found until now

int Bound(int i, int w) // upper bound on the total value of items [i..n-1] that can fit in w
{
    int val=0;
    for(int j = i; j<n; j++)
    {
        if(a[j].w > w)
        {
            int piece=ceil(a[j].v*1.0 / a[j].w*1.0);
            val += piece*w;
            break;
        }
        else
        {
            val+=a[j].v;
            w-=a[j].w;
        }
    }
    return val;
}

void BackTrack(int i, int w, int cur_val) // starting from item i, remaining weight w, cur_value of objects[0..i-1]
{
    if(i==n)
    {
        best_val=max(best_val,cur_val);
        return;
    }
    if(cur_val+Bound(i,w)<=best_val)return;
    if(a[i].w<=w)
        BackTrack(i+1,w-a[i].w,cur_val+a[i].v);
    BackTrack(i+1,w,cur_val);
}

int ComputeKnapsack(int N, int W) // solve knapsack of N objects and W weight
{
    best_val=-1;
    BackTrack(0,W,0);
    best_val=max(best_val,0);
    return best_val;
}
void Compute()
{
    int t,g,x;
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=0;i<n;i++)
        {
            cin>>a[i].v;
            cin>>a[i].w;
        }
        int total=0;
        MergeSort(a,n,IsBefore);
        cin>>g;
        while(g--)
        {
            cin>>x;
            total+=ComputeKnapsack(0,x);
        }
        cout<<total<<endl;
    }
}



int main()
{
	//freopen("input.in", "r", stdin);
	//freopen("out.out","w",stdout);
	Compute();
	return 0;
}


