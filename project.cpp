#include<iostream>
#include <fstream>
using namespace std;
class Term
{
	public:
		float coef;		//系数 
		int expn;		//指数 
		Term *next;	
};
class Poly
{
	public:
		Poly()			//构造 
		{
			
			L=new Term;
			Term *next;
			L->next=NULL;
		}
		Poly(const Poly&);//复制 
		~Poly()			//析构 
		{
			Term *p;
			while(L)
			{
				p=L->next;
				delete L;
				L=p;
			}
		}
		void createpoly(int,int*,int*);
		void SortList();
		void coeflist(int*);
		void displaypoly();
		void resolutions();
		int getlen();
		
		friend void addpoly(Poly&,Poly&);
		void mulpoly(Poly&,Term*);
		void multiplypoly(Poly&,Poly&);
	public:
		Term *L;
};
Poly::Poly(const Poly &p1)//深复制 
{
	L=new Term;
	Term *p=L,*r=p1.L->next;
	while(r)
	{
		p->next=new Term;
		p->next->coef=r->coef;
		p->next->expn=r->expn;
		p=p->next;
		r=r->next;
	}
	p->next=NULL;
}

int Poly::getlen()		//多项式长度 
{
	Term *p=L->next;
	int len=0;
	while(p)
	{
		len++;
		p=p->next;
	}
	return len;
}

void Poly::SortList()     // 
{   
    Term *p, *q, *pre;  
    p = L->next;  
    L->next = NULL;  
    while (p != NULL)  
    {  
        if (L->next == NULL)       //处理第一个结点   
        {  
            L->next = p;  
            p = p->next;  
            L->next->next = NULL;  
        }  
        else         //处理剩余其他结点  
        {  
            pre = L;  
            q = pre->next;  
            while (q && q->expn < p->expn)  
            {  
                pre = q;  
                q = q->next;  
            }  
            q = p->next;  
            p->next = pre->next;  
            pre->next = p;  
            p = q;  
        }  
    }  
}  

void Poly::createpoly(int N,int e1[],int e2[])
//输入规则：项数
//		    系数1 指数1 系数2 指数2 ... 
{
	Term *p=L,*q;
//	cout << *e1 << endl;
//	int n;
//	cout<<"Please input quantity of terms:"<<endl;
//	cin >> n;
//	cout<<"Please input the Polynomial:"<<endl;
	for(int i=0;i<N;i++)
	{
		q = new Term;
		q -> coef = e1[i];
		q -> expn = e2[i];
//		cout << e1[i] << endl;
		p -> next = q;
		p = q;
	}
	p->next=NULL;
}

void Poly::coeflist(int arr[])   //系数链表   
{  
    Term *p;
    int i=0;
    p = L->next;  
    while (p != NULL)  
    {  
    	arr[i]=p->coef;
    	i++;
    	p=p->next;
    }  
}  

void Poly::displaypoly()
{
	Term *p=L->next;
	cout<<"The Polynomial is:"<<endl;
	if(!p) return;
	while(p->next!=NULL)
	{
		if(p->expn==0)
		{
			cout<<p->coef;
			if(p->next->coef>=0) cout<<'+';
		}
		else
		{
			cout<<p->coef<<"X^"<<p->expn;
			if(p->next->coef>=0) cout<<'+';
		}
		p=p->next;
	}
	cout<<p->coef<<"X^"<<p->expn<<endl;
}
void Poly::resolutions()
{
	Term *p=L->next;
	Term *q=p->next;
	if(!p) return;
	while(p&&q)
	{
		if(p->expn==q->expn)
		{
			p->coef+=q->coef;
			p->next=q->next;
			delete q;
			q=p->next;
		}
		else
		{
			p=p->next;
			q=q->next;
		}
	}
}

void addpoly(Poly &p1,Poly &p2)	//多项式求和 
{
	Term *ha=p1.L,*hb=p2.L;
	Term *pa=ha->next,*pb=hb->next;
	while(pa&&pb)
	{
		if(pa->expn<pb->expn)
		{
			ha=pa;
			pa=pa->next;
		}
		else if(pa->expn>pb->expn)
		{
			ha->next=pb;
			hb->next=pb->next;
			pb->next=pa;
			pb=hb->next;
			ha=ha->next;
		}
		else//相等 
		{
			if(pa->coef+pb->coef!=0.0)//系数不为0 
			{
				pa->coef=pa->coef+pb->coef;
				ha=pa;
			}
			else
			{
				ha->next=pa->next;
				delete pa;
			}
			hb->next=pb->next;
			delete pb;
			pa=ha->next;
			pb=hb->next;
		}
	}
	if(pb) ha->next=pb;//若pb不为空，则将剩余接到ha后面 
	delete hb;

}

void Poly::mulpoly(Poly &po1,Term *p2)	//对A(x)进行系数加权 
{
	Term *p1=po1.L->next,*p=L;
	while(p1)
	{
		p->next=new Term;
		p->next->coef=p1->coef*p2->coef;
		p->next->expn=p1->expn+p2->expn;
		p=p->next;
		p1=p1->next;
	}
	p->next=NULL;
}
void Poly::multiplypoly(Poly &po1,Poly &po2)	//将多项式乘法分解为一系列加法运算 
{
	Poly poi;
	Term *p2=po2.L->next;
	while(p2)
	{
		poi.mulpoly(po1,p2);
		addpoly((*this),poi);
		poi.L=new Term;
		poi.L->next=NULL;
		p2=p2->next;
	}
} 

void inttoarr(int i,int arr[]){     
	int in=0,j;
	while(i)
	{
	
	arr[in]=i%10;
	in++;
	i/=10;
	//cout<< i <<endl;
	}
	
//	while(in--) cout<<arr[in]<<" ";
//	cout<<endl;
}

int num_first(int i){         //位数 
	int i_first,j;
	while(i) {
	i_first = i%10;
	i/=10;	
	}
//	cout << "i first:" << i_first << endl;
	return i_first;
}  
  
void change(int array[],int n){     //转换显示格式
    int i,temp;
    for( i=0 ; i<n/2 ; i++ ) 
    {
        temp=array[i];
        array[i]=array[n-1-i];
        array[n-1-i]=temp;
    }
}

int main()
{
	Poly p1,p2,p3,p4,p5;
	int select,N;
	int i ;
	fstream infile("f1.txt",ios::in);
	infile >> i;
	cout << "P1 : " << i << endl;
	N = num_first(i);
	int arr[N];    
    inttoarr(i,arr);
    int c1[N-1];
    change(arr,N);
    for(int j=0;j<N;j++){
    	c1[j]=arr[j];
    }
    int e1[N];
    for(int j=0;j<N;j++){
    	e1[j]=N-1-j;
    }
    int N2;
    int i2;
    fstream infile2("f2.txt",ios::in);
	infile2 >> i2;
    cout << "p2 : " << i2 << endl;
    N2 = num_first(i2);
    int arr2[N2];    
    inttoarr(i2,arr2);
    int c2[N2-1];
    change(arr2,N2);
    for(int j=0;j<N2;j++){
    	c2[j]=arr2[j];
    }
    int e2[N2];
    for(int j=0;j<N2;j++){
    	e2[j]=N2-1-j;
    }
	cout<<"Please Choose add or multi (1 = add, 2 = multi)"<< endl;
	cin >> select;
	if(select == 1)
	{
	cout << "Now is AddPoly!" << endl; 
	p1.createpoly(N,arr,e1);
 
//	p1.displaypoly();
	p2.createpoly(N2,arr2,e2);
//	p2.displaypoly();
	cout<<"P1+P2:  ";
	addpoly(p1,p2);
	p1.SortList();
	p1.resolutions();
	int N3 = p1.getlen()+1;
	int arr3[N3];
	p1.coeflist(arr3);
    arr3[N3-1]=N3-1;
    change(arr3,N3);
    for(int j=0;j<N3;j++){
    cout<<arr3[j];
    }
    cout<<endl;
//	p1.displaypoly();
	
	}
	if(select == 2)
	{
	cout << "Now is MultiPoly!" << endl;
	p3.createpoly(N,arr,e1);
//	p3.displaypoly();
	p4.createpoly(N2,arr2,e2);
//	p4.displaypoly();
	cout<<"P1*P2:  ";
	p5.multiplypoly(p3,p4);
	p5.SortList();
	p5.resolutions();
//	p5.displaypoly();
	int N3 = p5.getlen()+1;
	int arr3[N3];
	p5.coeflist(arr3);
	arr3[N3-1]=N3-1;
	change(arr3,N3);
    for(int j=0;j<N3;j++){
    cout<<arr3[j];
    }
    cout<<endl;
	}
//	else cout << "error input!" << endl;
	return 0;
}