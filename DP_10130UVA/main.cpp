// GROUP:   4
// ID:      20150204
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    Mohamed Ashraf AbdElHady
// UVA Username: mohamedrefaie

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

struct Obj
{
	int v; // value (price) of object
	int w; // weight of object
};

Obj a[1000];
int n;
int T1[1001][31];
int Knapsack1(int indx, int w)
{
	if(indx==n)return 0;
	int ret=T1[indx][w];
	if(ret!=-1)return ret;
	ret=Knapsack1(indx+1,w);
	if(w>=a[indx].w)
		ret=max(ret,a[indx].v+Knapsack1(indx+1,w-a[indx].w));
	return T1[indx][w]=ret;
}
int ComputeKnapsack1(int N, int W) // Recursive - memoization - initialize T then call Knapsack1(N,W);
{
	memset(T1,-1,sizeof T1);
	return Knapsack1(0,W);
}


int T2[1001][31];
int ComputeKnapsack2(int N, int W) // Bottom-up, do not save space
{
    for(int i=0;i<=30;i++)
    {
        T2[n][0]=0;
    }
    int ret;
    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<=30;j++)
        {
            ret=T2[i+1][j];
            if(j>=a[i].w)
                ret=max(ret,a[i].v+T2[i+1][j-a[i].w]);
            T2[i][j]=ret;
        }
    }
    return T2[0][W];
}

int T3[2][31];
int ComputeKnapsack3(int N, int W) // Bottom-up, use two rows only
{
    memset(T3,0,sizeof T3);
    int ret;
    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<=30;j++)
        {
            ret=T3[(i+1)%2][j];
            if(j>=a[i].w)
                ret=max(ret,a[i].v+T3[(i+1)%2][j-a[i].w]);
            T3[i%2][j]=ret;
        }
    }
    return T3[0][W];
}


int T4[31];
int ComputeKnapsack4(int N, int W) // Bottom-up, save maximum space
{
    memset(T4,0,sizeof T4);
    for(int i=0;i<=n;i++)
    {
        for(int j=W;j>=0;j--)
        {
            if(j-a[i].w>=0)
            T4[j]=max(T4[j],a[i].v+T4[j-a[i].w]);
        }
    }
    return T4[W];
}


int ComputeKnapsack(int N, int W) // Here we can choose the method
{
	//return ComputeKnapsack1(N,W);
	//return ComputeKnapsack2(N,W);
	//return ComputeKnapsack3(N,W);
	return ComputeKnapsack4(N,W);
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
	//freopen("output.out","w",stdout);
	Compute();
	return 0;
}


