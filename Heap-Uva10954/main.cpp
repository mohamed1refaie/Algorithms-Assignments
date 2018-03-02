// GROUP:   4
// ID:      20150204
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
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
	void Initialize()
	{
		n=0;
		sz=100005;
        arr=new Value[sz];
	}
	void Destroy()
	{
		n=0;
	}
	void AddLast(Value v)
	{
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
    int next=0;
    int size() {
        return next;
    }
	bool (*IsBefore)(int&, int&);
	void Initialize(bool (*_IsBefore)(int&, int&))
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
        else return -1;
    }
	Elem RetrieveFirst()
    {
        if(next==0)return -1;
        else if (next==1)
        {
            next--;
            int ret=a[0];
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
bool IsBeforeInt(int& a, int& b)
{
    return a<b;
}


int main()
{
    int n,x,first,second,sum,cost;
    Heap<int>h;
    h.Initialize(&IsBeforeInt);
    while(true) {
        cin>>n;
        if(n==0)break;
        cost=0;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            h.Add(x);
        }
        while(h.size()!=1)
        {
             first=h.RetrieveFirst();
             second=h.RetrieveFirst();
             sum=first+second;
            cost+=sum;
            h.Add(sum);
        }
        h.RetrieveFirst();
        cout<<cost<<endl;
    }

	return 0;
}


