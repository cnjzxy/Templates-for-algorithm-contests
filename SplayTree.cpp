//support insert an element and reverse a series of numbers
//can be modified to support different kinds of interval operations
#include<cstdio>

struct Splay_tree
{
    int val,siz,tag;
    Splay_tree *ls,*rs,*fa;

    inline Splay_tree():val(0),siz(1),tag(0),ls(NULL),rs(NULL),fa(NULL){}
    inline Splay_tree(const int&x):val(x),siz(1),tag(0),ls(NULL),rs(NULL),fa(NULL){}

    inline void New_node(int x)
    {
        *this=Splay_tree(x);
    }
    inline void push_down()
    {
        if(this->tag)
        {
            Splay_tree*temp=this->ls;
            this->ls=this->rs;
            this->rs=temp;
            if(this->ls!=NULL)this->ls->tag^=1;
            if(this->rs!=NULL)this->rs->tag^=1;
            this->tag=0;
        }
    }
    inline void LR()
    {
        Splay_tree*f=this->fa;
        f->siz-=this->siz;
        this->siz+=f->siz;
        f->rs=this->ls;
        if(f->fa!=NULL)
            if(f->fa->ls==f)
                f->fa->ls=this;
            else
                f->fa->rs=this;
        this->fa=f->fa;
        f->fa=this;

        if(f->rs!=NULL)
        {
            f->rs->fa=f;
            f->siz+=f->rs->siz;
        }
        this->ls=f;
    }
    inline void RR()
    {
        Splay_tree*f=this->fa;
        f->siz-=this->siz;
        this->siz+=f->siz;
        f->ls=this->rs;
        if(f->fa!=NULL)
            if(f->fa->ls==f)
                f->fa->ls=this;
            else
                f->fa->rs=this;
        this->fa=f->fa;
        f->fa=this;

        if(f->ls!=NULL)
        {
            f->ls->fa=f;
            f->siz+=f->ls->siz;
        }
        this->rs=f;
    }
    inline void Splay()
    {
        while(this->fa!=NULL)
        {
            Splay_tree*f=this->fa;
            if(f->fa==NULL)
            {
                if(this==f->ls)this->RR();
                else this->LR();
            }
            else
            {
                if(f==f->fa->ls)
                {
                    if(this==f->ls)
                    {f->RR();this->RR();}
                    else
                    {this->LR();this->RR();}
                }
                else
                {
                    if(this==f->ls)
                    {this->RR();this->LR();}
                    else
                    {f->LR();this->LR();}
                }
            }
        }
    }
    inline Splay_tree*Insert(int x)
    {
        Splay_tree*prv=NULL,*now=this;
        while(now!=NULL)
        {
            now->siz++;
            prv=now;
            if(x<now->val)
                now=now->ls;
            else
                now=now->rs;
        }
        now=new Splay_tree;
        now->New_node(x);
        now->fa=prv;
        if(prv!=NULL)
            if(x<prv->val)prv->ls=now;
            else prv->rs=now;
        now->Splay();
        return now;
    }
    inline Splay_tree*Get_kth(int x)
    {
        Splay_tree*p=this;
        while(x)
        {
            p->push_down();
            if(p->ls!=NULL)
                if(x<=p->ls->siz)
                {
                    p=p->ls;
                    continue;
                }
                else
                    x-=p->ls->siz;
            x--;
            if(x)p=p->rs;
        }
        p->Splay();
        return p;
    }

    inline void Splay1()//for rev
    {
        while(this->fa->fa!=NULL)
        {
            Splay_tree*f=this->fa;
            if(f->fa->fa==NULL)
            {
                if(this==f->ls)this->RR();
                else this->LR();
            }
            else
            {
                if(f==f->fa->ls)
                {
                    if(this==f->ls)
                    {f->RR();this->RR();}
                    else
                    {this->LR();this->RR();}
                }
                else
                {
                    if(this==f->ls)
                    {this->RR();this->LR();}
                    else
                    {f->LR();this->LR();}
                }
            }
        }
    }
    inline Splay_tree*Get_kth1(int x)//for rev
    {
        Splay_tree*p=this;
        while(x)
        {
            p->push_down();
            if(p->ls!=NULL)
                if(x<=p->ls->siz)
                {
                    p=p->ls;
                    continue;
                }
                else
                    x-=p->ls->siz;
            x--;
            if(x)p=p->rs;
        }
        p->Splay1();
        return p;
    }
    inline Splay_tree*rev(int x,int y)
    {
        Splay_tree*now=this;
        now=now->Get_kth(x);
        now=now->Get_kth1(y+2);
        now->ls->tag^=1;
        return now->fa;
    }
}*root;

int main()
{
    /*
    root=root->Insert(_NUM);
    root=root->Get_kth(_NUM);
    root=root->rev(_L,_R);
    */
    return 0;
}
