// GROUP:   4
// ID:      20150204
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    Mohamed Ashraf AbdelHady

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;


long long CountInvMerge(long long* a, int n)
{
    int mid=(n-1)/2;
    int firstsz=mid+1;
    int secondsz=n-(mid+1);
    long long *firstarr= new long long[firstsz];
    long long *secondarr=new long long [secondsz];
    int i=0;
    for(;i<firstsz;i++)
    {
        firstarr[i]=a[i];
    }
    for(int j=0;j<secondsz;j++,i++)
        secondarr[j]=a[i];
    i=0;
    int j=0,k=0;
    long long ans=0;
    while(i<firstsz&&j<secondsz)
    {
        if(secondarr[j]<firstarr[i])
        {
            ans+=firstsz-i;
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
    return ans;

}
long long CountInv(long long* a, int n)
{
    if(n>1)
    {
        int mid=(n-1)/2;
        int firstsz=mid+1;
        int secondsz=n-(mid+1);
        long long *firstarr= new long long[firstsz];
        long long *secondarr=new long long [secondsz];
        int i=0;
        for(;i<firstsz;i++)
        {
            firstarr[i]=a[i];
        }
        for(int j=0;j<secondsz;j++,i++)
            secondarr[j]=a[i];
        long long ansfirst=CountInv(firstarr,firstsz);
        long long anssecond=CountInv(secondarr,secondsz);
        i=0;
        for(;i<firstsz;i++)
        {
            a[i]=firstarr[i];
        }
        for(int j=0;j<secondsz;j++,i++)
            a[i]=secondarr[j];
        long long ret=ansfirst+anssecond+CountInvMerge(a,n);
        return ret;
    }
    else if(n==1)
    {
        return 0;
    }
}



int main()
{
  //  freopen("input.in","rt",stdin);
   // freopen("output.out","wt",stdout);
    int n;
    while(cin>>n&&n)
    {
        long long *arr=new long long[n];
        for(int i=0;i<n;i++)
            cin>>arr[i];
        long long ans=CountInv(arr,n);
        cout<<ans<<endl;
    }
    return 0;
}


