// GROUP:   4
// ID:      20150204
// Assign:  11
// Assign:  EditDist
// UVA:     526
// Name:    Mohamed Ashraf AbdElHady
// UVA Username: mohamedrefaie

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;


char a[82];
char b[82];
int N,M;
int D[81][81]; // D[][] is the same for all versions (no memory reduction)



int T1[81][81];
int EditDist1(int n, int m)
{
    if(n==N&&m==M)return 0;
    int ret=T1[n][m];
    if(ret!=-1)return ret;
    ret=10000000;
    if(n==N)
    {
        ret=1+EditDist1(n,m+1);
        D[n][m]=2;
        return T1[n][m]=ret;
    }
    if(m==M)
    {
        ret=1+EditDist1(n+1,m);
        D[n][m]=1;
        return T1[n][m]=ret;
    }
    if(a[n]==b[m])
        return T1[n][m]=EditDist1(n+1,m+1);
    int choiceindx=-1;
    int choice1=1+EditDist1(n+1,m);    //delete
    int choice2=1+EditDist1(n,m+1);    //insert
    int choice3=1+EditDist1(n+1,m+1);  // replace
    if(choice3<ret)
    {
        ret=choice3;
        choiceindx=3;
    }
    if(choice1<ret)
    {
        ret=choice1;
        choiceindx=1;
    }
    if(choice2<ret)
    {
        ret=choice2;
        choiceindx=2;
    }

    D[n][m]=choiceindx;
    return T1[n][m]=ret;

}
int ComputeEditDist1(int N, int M) // Recursive - memoization - initialize T then call EditDist1(N,M);
{
    memset(T1,-1,sizeof T1);
    memset(D,-1,sizeof D);
    EditDist1(0,0);
}


int T2[81][81];
int ComputeEditDist2(int N, int M); // Bottom-up, do not save space


int T3[2][81];
int ComputeEditDist3(int N, int M); // Bottom-up, use two rows only


int T4[81];
int ComputeEditDist4(int N, int M); // Bottom-up, save maximum space


struct Oper
{
    int n,m;
    int oper;
};

Oper opers[81];

int EditDistSol(int N, int M) // Print the solution using D[][]
{
    int i=0,j=0,op=0;
    while(i!=N||j!=M) {
        if (D[i][j]!=-1) {
            Oper newOperation;
            newOperation.oper=D[i][j];
            newOperation.n = i;
            // save operation char if insert or replace.
            if (newOperation.oper == 2 || newOperation.oper == 3)
                newOperation.m = b[j];

            // add to list.
            opers[op++] = newOperation;
        }

        // iterate.
        if (D[i][j] == 1)
            ++i;
        else if (D[i][j] ==2)
            j++;
        else
            ++i, ++j;
    }

    //used to offset indexes after insert/delete .
    int deleteCount = 0;
    int insertCount = 0;

    // print and
    cout << op << endl;
    for (int i = op - 1; i >= 0; --i) {
        cout << op - i << " ";
        if (opers[i].oper == 0)
            cout << "Insert " << opers[i].n + 1 - deleteCount + insertCount++ << "," << (char) opers[i].m << endl;
        else if (opers[i].oper == 1)
            cout << "Delete " << opers[i].n - deleteCount++ + insertCount << endl;
        else
            cout << "Replace " << opers[i].n - deleteCount + insertCount << "," << (char) opers[i].m << endl;

    }
    return 0;
}


int ComputeEditDist(int N, int M) // Here we can choose the method
{
    return ComputeEditDist1(N,M);
    //return ComputeEditDist2(N,M);
    //return ComputeEditDist3(N,M);
//    return ComputeEditDist4(N,M);
}

// This function does not need any modification:
void Compute() // Get input and call ComputeEditDist() whenever needed
{
    int cas=0;
    while(true)
    {
        a[0]=0; b[0]=0;
        if(!fgets(a,82,stdin)) break; fgets(b,82,stdin);
        a[strlen(a)-1]=0;
        b[strlen(b)-1]=0;
        if(cas) cout<<endl; // print an empty line between test cases
        N=strlen(a), M=strlen(b);
        ComputeEditDist(N,M);
        cout<<N<<" "<<M<<endl;
        EditDistSol(N,M);
        cas++;
    }
}


int main()
{
    freopen("input.in", "r", stdin);
    Compute();
    return 0;
}

