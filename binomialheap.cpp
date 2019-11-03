#include<bits/stdc++.h>
using namespace std;

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
    node(int data,int degree)   {
        this->data=data;
		this->degree=degree;
		this->parent=NULL;
		this->leftchild=NULL;
		this->rightsibling=NULL;
    }
};

class BinomialHeap  {
    public:
    node* root;
    public:
    BinomialHeap();
    void insert(int);
    void initmerge(node *,node *,node *);
    void mergesamedegree(node *,node *,node *);
    void union1(BinomialHeap);
    stack<node*> reverselist(node *);
    node *extractmin();
    void display();
    int findmin();
    node *findminwithprev();
};
BinomialHeap::BinomialHeap()    {
    root=NULL;
}
void BinomialHeap::insert(int val)  {
    node *newnode = new node(val,0);
    BinomialHeap bh;
    bh.root=newnode;
    union1(bh);
}
void BinomialHeap::initmerge(node *head,node *current,node *next)   {
    if(head==NULL && current==NULL)
        return;
    else    {
        while(head!=NULL && current!=NULL) {
            if(current->degree<head->degree)    {
                next->rightsibling=current;
                current=current->rightsibling;
            }
            else    {
                next->rightsibling=head;
                head=head->rightsibling;
            }
            next=next->rightsibling;
        }
        while(head!=NULL)    {
            next->rightsibling=head;
            head=head->rightsibling;
            next=next->rightsibling;
        }
        while(current!=NULL) {
            next->rightsibling=current;
            current=current->rightsibling;
            next=next->rightsibling;
        }
    }
}
void BinomialHeap::mergesamedegree(node *current,node *next,node *temp)	{
    if(next==NULL)
        return;
    else    {
        node *prev=NULL;
        while(next!=NULL)   {
            if((next->rightsibling!=NULL && current->degree==next->rightsibling->degree)||(current->degree!=next->degree)) {
                prev=current;
                current=next;
            }
            else    {
                if(current->data>next->data)    {
                    if(prev!=NULL)
                        prev->rightsibling=next;
                    else
                        temp=next;
                    current->rightsibling=next->leftchild;
                    current->parent=next;
                    next->degree++;
                    next->leftchild=current;
                    current=next;
                }
                else    {
                    current->rightsibling=next->rightsibling;
                    next->rightsibling=current->leftchild;
                    next->parent=current;
                    current->degree++;
                    current->leftchild=next;
                
                } 
            }
            next=current->rightsibling;
        }
    }
}

void BinomialHeap::union1(BinomialHeap bh)  {
    node *head=root;
    node *current=bh.root;
    node *next=NULL,*temp=NULL;
    if(head->degree>current->degree)    {
        next=current;
        current=current->rightsibling;
    }
    else    {
        next=head;
        head=head->rightsibling;
    }
    temp=next;
    initmerge(head,current,next);
    next=temp;
	mergesamedegree(next,next->rightsibling,temp);
	this->root=temp;
}
int BinomialHeap::findmin() {
	node *ptr=root,*minnode=NULL;
    int minm;
    minm=INT_MAX;
	while(ptr!=NULL)    {
		if(ptr->data<minm)  {
			minnode=ptr;
            minm=ptr->data;
		}
		ptr=ptr->rightsibling;
	}
	return minm;
}
node* BinomialHeap::findminwithprev() {
	node *ptr=root,*minnode=NULL;
    int minm;
    minm=INT_MAX;
	while(ptr!=NULL)    {
		if(ptr->data<minm)  {
			minnode=ptr;
            minm=ptr->data;
		}
		ptr=ptr->rightsibling;
	}
	return minnode;
}
stack<node*> BinomialHeap::reverselist(node* minnode)	{
	stack<node*> s;
	node* child=minnode->leftchild;
	while(child!=NULL)  {
		s.push(child);
		child=child->rightsibling;
	}
	return s;
}

node* BinomialHeap::extractmin() {
    BinomialHeap bh;
    int min;
	node *current = root;
	node *prev=NULL,*preptr=NULL,*minnode=NULL;
    min=INT_MAX;
	while(current!=NULL)    {
		if(min>=current->data)  {
			prev=preptr;
			minnode=current;
            min=current->data;
		}
		preptr=current;
		current=current->rightsibling;
	}
    if(prev!=NULL)     {
		if(!(minnode->rightsibling))
			prev->rightsibling=NULL;
		else
			prev->rightsibling=minnode->rightsibling;			
	}
	node* child=minnode->leftchild;
	while(child!=NULL)  {
		child->parent=NULL;
		child=child->rightsibling;
	}

	stack<node*> s1;
	s1=reverselist(minnode);
	current=s1.top();
	node* temp=current;
	s1.pop();

	while(!s1.empty())  {
        node *node1=s1.top();
		current->rightsibling=node1;
		current=current->rightsibling;
        s1.pop();
	}
	current->rightsibling=NULL;
	bh.root=temp;
	union1(bh);
	return minnode;
}

void BinomialHeap::display() {
	node* current=root;
	while(current!=NULL)	{
        cout<<"\n";
		node* ptr=current;
		cout<<"Tree "<<ptr->degree<<"\n";
		cout<<"Number of nodes in Tree "<<ptr->degree<<" is: "<<pow(2, ptr->degree)<<"\n";
		queue<node*> q1;
		q1.push(ptr);
		while(!q1.empty())  {
            cout<<q1.front()->data<<" ";
			node* temp=q1.front();
			q1.pop();
			if(temp->leftchild!=NULL)   {
				node* thisnode=temp->leftchild;
				while(thisnode!=NULL) {
					q1.push(thisnode);
					thisnode=thisnode->rightsibling;
				}
			} 
		}
		cout<<"\n";
		current=current->rightsibling;
	}
}

int main() {
	BinomialHeap heap1;
	BinomialHeap heap2;

    node* node1=new node(5,0);
	heap1.root=node1;

	node* node2=new node(6,2);
	node* node3=new node(12,1);
	node* node4=new node(34,0);
	node* node5=new node(33,0);
	node2->leftchild=node3;
	node3->parent=node2;
	node4->parent=node2;
	node3->leftchild=node5;
	node3->rightsibling=node4;
	node5->parent=node3;


	node1->rightsibling=node2;

	node* node6=new node(1,3);
	node* node7=new node(2,2);
	node* node8=new node(12,1);
	node* node9=new node(6,0);
	node* node10=new node(4,1);
	node* node11=new node(33,0);
	node* node12=new node(28,0);
	node* node13=new node(17,0);
	node6->leftchild=node7;
	node7->parent=node6;
	node8->parent=node6;
	node7->parent=node6;
	node7->leftchild=node10;
	node7->rightsibling=node8;
	node8->leftchild=node12;
	node8->rightsibling=node9;
	node10->parent=node7;
	node11->parent=node7;
	node12->parent=node8;
	node10->leftchild=node13;
	node10->rightsibling=node11;
	node13->parent=node10;

	node2->rightsibling=node6;
    heap1.display();



    node* node14=new node(28,1);
	node* node15=new node(45,0);
	node14->leftchild=node15;
	node15->parent=node14;
	heap2.root=node14;

	node* node16=new node(20,2);
	node* node17=new node(23,1);
	node* node18=new node(97,0);
	node* node19=new node(62,0);
	node16->leftchild=node17;
	node17->parent=node16;
	node18->parent=node16;
	node17->leftchild=node19;
	node17->rightsibling=node18;
	node19->parent=node17;

	node14->rightsibling=node16;



    heap1.union1(heap2);
	heap1.display();
	cout<<"Min: "<<heap1.findmin()<<endl;
	heap1.extractmin();
	heap1.display();
	cout<<"Min: "<<heap1.findmin()<<endl;
    heap1.display();
	cout<<"Min: "<<heap1.findmin()<<endl;
	heap1.extractmin();
	heap1.display();
	cout<<"Min: "<<heap1.findmin()<<endl;
	return 0;
}