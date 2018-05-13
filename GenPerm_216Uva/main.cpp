// GROUP:   4
// ID:      20150204
// Assign:  13
// Assign:  GenPerm
// UVA:     216
// Name:    Mohamed Ashraf AbdElHady
// UVA Username: mohamedrefaie

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>      // use built-in sqrt()
#include <iostream>
#include <iomanip>

using namespace std;



void swap(int& a, int& b)
{
    int temp=b;
    b=a;
    a=temp;
}



#define MAX_COMPUTERS 8



struct Point{int x,y;};
double Dist(Point& a, Point& b)
{
    return sqrt(((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y)));
}



int		n; // number of computers (input)
Point	com[MAX_COMPUTERS]; // locations of computers (input)
double	dist[MAX_COMPUTERS][MAX_COMPUTERS]; // dist[i][j]=distance from com[i] to com[j] (pre-computed)



double	best_val; // best value until now
int		best_sol[MAX_COMPUTERS]; // best solution until now (a permutation)

int		s[MAX_COMPUTERS]; // s is current permutation. s[i]=index of the ith computer in this permutation.



void UpdateSol() // evaluate the permutation s, then update best_val and best_sol if necessary
{
    double cur=0;

    for(int i=0;i<n-1;i++)
    {
        cur+=(dist[s[i]][s[i+1]])+16;
    }
    if(cur<best_val)
    {
        best_val=cur;
        for(int i=0;i<n;i++)
            best_sol[i]=s[i];
    }
}



void Backtrack0(int i) // backtrack using swaps
{
    if(i==n)
    {
        UpdateSol();
        return;
    }
    for(int j=i;j<n;j++)
    {
        swap(s[i],s[j]);
        Backtrack0(i+1);
        swap(s[i],s[j]);
    }
}
void Compute0() // do necessay initializations and call Backtrack0()
{
    for(int i=0;i<n;i++)
        s[i]=i;
    Backtrack0(0);
}



bool v[MAX_COMPUTERS]; // v[i]=true if com[i] already taken in the permutation

void Backtrack1(int i) // backtrack using the v[] array
{
    if(i==n)
    {
        UpdateSol();
        return;
    }
    for(int j=0;j<n;j++)
    {
        if(!v[j])
        {
            v[j]=true;
            s[i]=j;
            Backtrack1(i+1);
            v[j]=false;
        }
    }
}
void Compute1() // do necessay initializations and call Backtrack1()
{
    memset(v,0,sizeof v);
    Backtrack1(0);
}


// Dancing Links:

int F[MAX_COMPUTERS+1]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_COMPUTERS+1]; // B[0]=n, B[1]=0
void Remove(int i) {F[B[i]]=F[i]; B[F[i]]=B[i];}
void Restore(int i) {B[F[i]]=i; F[B[i]]=i;}
void InitDancingLinks(int n)
{
	int i;
	for(i=0;i<n;i++) F[i]=i+1; F[n]=0;
	for(i=n;i>0;i--) B[i]=i-1; B[0]=n;
}
// for(i=F[0];i!=0;i=F[i]) iterate on available list indexes



void Backtrack2(int i); // backtrack using dancing links
void Compute2(); // do necessay initializations and call Backtrack2()


void ComputeCore()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            dist[i][j]=Dist(com[i],com[j]);
        }
    }
    best_val=1000000000;
	// do necessay initializations of dist[][] and best_val
	//Compute0();
	Compute1();
	//Compute2();
}



void Compute() // get input and then call ComputeCore(); then print output
{
    int test=0;
    while(true)
    {
        test++;
        cin>>n;
        if(n==0)break;
        for(int i=0;i<n;i++)
        {
            cin>>com[i].x>>com[i].y;
        }
        ComputeCore();
        cout<<"**********************************************************"<<endl;
        cout<<"Network #"<<test<<endl;
        for(int i=0;i<n-1;i++)
        {
            cout<<"Cable requirement to connect ("<<com[best_sol[i]].x<<","<<com[best_sol[i]].y<<") to ("<<com[best_sol[i+1]].x<<","<<com[best_sol[i+1]].y<<") is "<<fixed<<setprecision(2)<<(dist[best_sol[i]][best_sol[i+1]])+16<<" feet."<<endl;
        }
        cout<<"Number of feet of cable required is "<<fixed<<setprecision(2)<<best_val<<"."<<endl;
    }

}



int main()
{
	//freopen("input.in", "r", stdin);
	//freopen("out.out","w",stdout);
	Compute();
	return 0;
}


