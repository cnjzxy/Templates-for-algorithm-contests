//modify maxn to the max length/9
//* can be improved
// / and % are not completely tested.
//can not support negative number
#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

const int base=1000000000;
const int maxn=500;

struct bigint
{
    int len;
    int data[maxn];
    inline bigint():len(0){}
    inline bigint(const bigint& x):len(x.len)
    {
        memcpy(data,x.data,len * sizeof(int));
    }
    inline bigint(int x):len(0)
    {
        for(;x>0;x/=base)
            data[len++]=x%base;
    }
    inline bigint& operator=(const bigint& x)
    {
        len=x.len;
        memcpy(data, x.data, len * sizeof *data);
        return *this;
    }
    inline int&operator[](int i){return data[i];}
    inline int operator[](int i) const{return i<len?data[i]:0;}
};

inline int compare(const bigint& a, const bigint& b)
{
    int i;
    if(a.len!=b.len)
        return a.len>b.len?1:-1;
    for(i=a.len-1;i>=0&&a[i]==b[i];i--);
    if(i<0)return 0;
    return a[i]>b[i]?1:-1;
}

inline bool operator==(const bigint&a,const bigint&b){return compare(a,b)==0;}
inline bool operator!=(const bigint&a,const bigint&b){return compare(a,b)!=0;}
inline bool operator> (const bigint&a,const bigint&b){return compare(a,b)>0;}
inline bool operator< (const bigint&a,const bigint&b){return compare(a,b)<0;}
inline bool operator>=(const bigint&a,const bigint&b){return compare(a,b)>=0;}
inline bool operator<=(const bigint&a,const bigint&b){return compare(a,b)<=0;}

inline bigint operator+(const bigint&a,const bigint&b)
{
    bigint c;
    int i;
    int x=0;
    for(i=0;i<a.len||i<b.len||x>0;i++)
    {
        if(i<a.len)x+=a[i];
        if(i<b.len)x+=b[i];
        if(x>=base)
        {
            x-=base;
            c[i]=x;
            x=1;
        }
        else
        {
            c[i]=x;
            x=0;
        }
    }
    c.len=i;
    return c;
}

inline bigint operator-(const bigint&a,const bigint&b)
{
    bigint c;
    int x=0;
    c.len=a.len;
    for(int i=0;i<c.len;i++)
    {
        c[i]=a[i]-x;
        if(i<b.len)c[i]-=b[i];
        if(c[i]<0)
        {
            x=1;
            c[i]+=base;
        }
        else
            x=0;
    }
    while(c.len>0&&c[c.len-1]==0)c.len--;
    return c;
}

inline bigint operator*(const bigint&a,const int b)
{
    int i;
    if(b==0)return 0;
    bigint c;
    long long x=0;
    for(i=0;i<a.len||x>0;i++)
    {
        if(i<a.len)x+=(long long)(a[i])*b;
        c[i]=x%base;
        x/=base;
    }
    c.len=i;
    return c;
}

inline bigint operator*(const bigint&a,const bigint&b)
{
    if(!b.len)return 0;
    bigint c;
    for(int i=0;i<a.len;i++)
    {
        long long x=0;
        for(int j=0;j<b.len||x>0;j++)
        {
            if(j<b.len)x+=(long long)(a[i])*b[j];
            if(i+j<c.len)x+=c[i+j];
            if(i+j>=c.len)
                c[c.len++]=x%base;
            else
                c[i+j]=x%base;
            x/=base;
        }
    }
    return c;
}

inline bigint operator/(const bigint&a,const int b)
{
    bigint c;
    long long x=0;
    for(int i=a.len-1;i>=0;i--)
    {
        x=x*base+a[i];
        c[i]=x/b;
        x%=b;
    }
    c.len=a.len;
    while(c.len>0&&c[c.len-1]==0)c.len--;
    return c;
}

inline bigint operator/(const bigint&a,const bigint&b)
{
    bigint c,x=0;
    int l,r,mid;
    for(int i=a.len-1;i>=0;i--)
    {
        x=x*base+a[i];
        l=0;
        r=base-1;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(compare(b*mid,x)<=0)
                l=mid+1;
            else
                r=mid-1;
        }
        c[i]=r;
        x=x-b*r;
    }
    c.len=a.len;
    while(c.len>0&&c[c.len-1]==0)c.len--;
    return c;
}

inline bigint operator%(const bigint&a,const bigint&b)
{
    bigint c,x;
    c=a/b;
    x=a-b*c;
    return x;
}

inline bigint gcd(bigint a,bigint b)
{
    return b==0?a:gcd(b,a%b);
}

inline istream&operator>>(istream&input,bigint& x)
{
    char c;
    for(x=0;input>>c;)
    {
        x=x*10+(c-'0');
        if(input.peek()<=' ')break;
    }
    return input;
}

inline ostream&operator<<(ostream&output,const bigint&x)
{
    output<<(x.len==0?0:x[x.len-1]);
    for(int i=x.len-2;i>=0;i--)
       for(int j=base/10;j>0;j/=10)
           output<<x[i]/j%10;
    return output;
}

bigint a,b;
int main()
{
    /*
    cin>>a>>b; //input
    cout<<a+b<<endl; //output a+b
    cout<<a-b<<endl; //output a-b
    cout<<a*b<<endl; //output a*b
    cout<<a/b<<endl; //output a/b
    cout<<a%b<<endl; //output a%b
    if(a<b)cout<<1<<endl; //compare numbers
    */
    return 0;
}
