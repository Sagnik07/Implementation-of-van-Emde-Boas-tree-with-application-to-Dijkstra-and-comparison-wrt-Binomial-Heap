#include<bits/stdc++.h> 
using namespace std; 
#define li list<node*>

class node  {
    public:
    int data;
    int degree;
    node *parent,*leftchild,*rightsibling;
    public:
    node()  {
        data=degree=0;
        parent=leftchild=rightsibling=NULL;
    }
};
class BinomialHeap  {
    public:
    li bino_heap;
    public:
    node* makenode(int);
    li insert(li,int);
    node* getmin(li);
    void check(li,li::iterator,li::iterator,li::iterator);
    li unionheap(li,li);
    li make_bin_heap(li); 
    li extractmin(li);
    void printTree(node *);
    void printHeap(li);
};

node* BinomialHeap::makenode(int val)   {
    node *newnode=new node();
    newnode->data=val;
    newnode->degree=0;
    newnode->parent=NULL;
    newnode->leftchild=NULL;
    newnode->rightsibling=NULL;
    return newnode;
}

li BinomialHeap::insert(li heap,int key) {
    li heap1;
    node *newnode=makenode(key);   
    heap1.push_back(newnode);
    heap1=unionheap(heap,heap1);
    if(heap1.size()>1)
        heap1=make_bin_heap(heap1);
    return heap1;
}

node* BinomialHeap::getmin(li heap)    {
    if(heap.empty()){return NULL;}
    node *ptr=*(heap.begin());
    for(auto it:heap)   {
        if(ptr->data>=it->data)
            ptr=it;
    }
    return ptr;
}

li BinomialHeap::unionheap(li heap1,li heap2)  {
    li heap; 
    li::iterator it1,it2;
    it1=heap1.begin();
    it2=heap2.begin();
    while (it1!=heap1.end() && it2!=heap2.end())       {
        int a=((*it1)->degree);
        int b=((*it2)->degree);
        if(a>b) {
            heap.push_back(*it2);
            it2++;
        }
        else    {
            heap.push_back(*it1);
            it1++;
        }
    } 
    if(it1!=heap1.end())      {
        while(it1!=heap1.end())    {
            heap.push_back(*it1);
            it1++;
        }
    }
    if(it2!=heap2.end())    {
        while(it2!=heap2.end()) {
            heap.push_back(*it2);
            it2++;
        }
    }
    return heap;
}

void BinomialHeap::check(li heap,li::iterator prev,li::iterator current,li::iterator next)  {
    if(heap.size()>2)   {
        current++;
        next=current;
        next++;
    }
    else    {
        current=prev;
        current++;
        next=heap.end();
    }
}

li BinomialHeap::make_bin_heap(li heap)  {
    li new_heap;
    li::iterator prev,current,next;
    prev=current=next=heap.begin();
  
    check(heap,prev,current,next);
    while (prev != heap.end())   {
        if (current!=heap.end())    {
            if(next!=heap.end() && ((*prev)->degree)==((*current)->degree) && ((*prev)->degree==(*next)->degree)) {
                current++;
                prev++;
                next++;
            }
            else if((*prev)->degree==(*current)->degree)  {
                if((*current)->data<(*prev)->data)  {
                    node *c;
                    node* a=(*current);
                    node* b=(*prev);
                    c=a;
                    a=b;
                    b=c;
                }
                node* a=(*prev);
                node* b=(*current);
                node *c=(a->leftchild);
                b->rightsibling=c;
                b->parent=a;
                c=b;
                a->degree++;
                (*prev)=a;
                current=heap.erase(current);
                if(next!=heap.end())
                    next++;
            } 
            else if(((*prev)->degree)<((*current)->degree))   {
                current++;
                prev++;
                if(next!=heap.end())
                    next++;
            }
        }
        else
            prev++;
    }
    return heap;
}

li BinomialHeap::extractmin(li heap)  {
    li heap1,heap2;
    if(heap.empty()){return heap1;}    
    node *minm,*temp,*ptr;
    minm=getmin(heap);
    for(auto it:heap)   {
        if(it==minm)
            continue;
        else
            heap1.push_back(it);
    }
    temp=minm->leftchild;  
    while(temp)    {
        ptr=temp;
        ptr->rightsibling=NULL;
        temp=temp->rightsibling;
        heap2.push_front(ptr);
    }
    heap1=unionheap(heap1,heap2);
    if(heap1.size()>1)
        heap1=make_bin_heap(heap1);
    return heap1;
}