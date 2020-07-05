

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
#define MAX_SIZE 362880	//9�Ľ׳�9!=362880

typedef struct node{		//������ṹ��

	int a[3][3];//�ڵ�״̬

	//�ո��±�
	int i_0;		
	int j_0;

	//������Ϣ
	int d;		//�������
	int w;		//�����Ӳ�����ȷλ�õ���Ŀ
	int f;		//�ܴ���

	struct node *father;	//ָ�򸸽ڵ�ָ��

}node,*p_node;


typedef struct list	//˳���ṹ��
{
	p_node a[MAX_SIZE];
	long length;

}list,*p_list;



static int start[3][3]={2,8,3,1,6,4,7,0,5};	//��ʼ���
/*
2	8	3
1	0	4
7	6	5
*/

static int ss_end[3][3]={1,2,3,8,0,4,7,6,5};	//Ŀ����
/*
1	2	3
8	0	4
7	6	5
*/

p_node start_node=(p_node) malloc(sizeof(node));	//��ʼ�ڵ�
p_node end_node=(p_node) malloc(sizeof(node));	//Ŀ��ڵ�

p_list OPEN  =(p_list) malloc (sizeof(list));	//OPEN��
p_list CLOSED=(p_list) malloc (sizeof(list));	//CLOSE��


bool besolve(int a[3][3],int b[3][3]);  //�ж��Ƿ��н� 
int w(p_node s);						//��������Ӳ�����ȷλ�õ���Ŀ
int f(p_node s);						//���ۺ���
void init_node();						//��ʼ��
void cout_node(p_node s);				//���������
void list_reverse(p_node &p);			//����������
void out_list(p_list &l);				//���OPEN��
bool search_list(p_list &l,p_node s);	//�Ա���в��ң��ɹ�����true
void sort_list(p_list &l);				//��OPEN��������򣨰�f��С����
void add_list(p_list &l,p_node s);		//�����㵽OPEN���л�CLOSE����
void copy_node(p_node s1,p_node &s2);	//�����µĽ�㣨��s2��ֵ��s1��
void delete_list(p_list &l);			//��OPEN���CLOSE��ɾ�����
bool is_equal(p_node s1,p_node s2);		//�ж����ڵ��Ƿ����
bool up_mov(p_node &s);					//�ո�����
bool down_mov(p_node &s);				//�ո�����
bool left_mov(p_node &s);				//�ո�����
bool right_mov(p_node &s);				//�ո�����
void move(p_node s);					//�ƶ����ڵ㲢����δ̽�����У���չ��㣩


int main()
{
	init_node();
	if(besolve(start,ss_end)==false)
		{
			cout<<"�ó�ʼ״̬��Ŀ��״̬�޽⣬�����˳�";
			return 0;
		}

	//�н�ִ�����³���
	cout<<"\n�������������£�\n";
	cout<<"=========================================================\n\n";

	while(OPEN->length!=0 )	
	{

		p_node n=OPEN->a[0];		//---------------��Open��ĵ�һ���ڵ�ȡ������Closed�����Ǹýڵ�Ϊn
		delete_list(OPEN);

		if(is_equal(n,end_node))	//����ڵ�n�Ƿ�ΪĿ��ڵ�
		{
			list_reverse(n);
		

			while(n)
			{
				
				cout<<"��"<<n->d+1<<"����\n";
				cout_node(n);
				n=n->father;
			}

			break;
		}
	
		add_list(CLOSED,n);

		move(n);//��չ���n
		
		sort_list(OPEN);

	}

	

	return 0;
}
bool besolve(int s2[3][3],int g2[3][3])
{
	//�����������������е�����ֵ��������߶���ż�������������ͨ���任����
	
	int a[9],b[9];
	int m=0;
	int sum1=0,sum2=0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			a[m]=s2[i][j];
			b[m]=g2[i][j];
			m++;
		}
		
	for(int i=8;i>=0;i--)
	{
		for(int j=i-1;j>=0;j--)
		{
			if(a[j]<a[i]&&a[j]!=0)
				sum1++;
			if(b[j]<b[i]&&b[j]!=0)
				sum2++;
		}
	}
	//cout<<sum1<<sum2;
	if(sum1%2==sum1%2)
	return true;
	else
	{
		return false;
	}
}
int f(p_node s)	//���ۺ���
{
	return (s->d+s->w);
}


void cout_node(p_node s)	//���������
{
	
	
	cout<<"-------�ո�����:"<<s->i_0<<" "<<s->j_0<<endl;
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			cout<<"  "<<s->a[i][j];
		}

		cout<<endl;
	}
	
	
	cout<<"d="<<s->d<<"  w="<<s->w<<"  f="<<s->f;
	cout<<endl<<endl;
}


void out_list(p_list &l)		//���OPEN��
{
	
	cout<<"****************************************************************\n";
	for(int i=0;i<l->length;i++)
	{
		cout_node(l->a[i]);
	}
	cout<<"****************************************************************\n";
}


int w(p_node s)		//��������Ӳ�����ȷλ�õ���Ŀ
{
	int w=0;

	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			if (s->a[i][j]!=ss_end[i][j])
			{
				w++;
			}
		}
	}

	if (s->a[1][1]==ss_end[1][1])
	{
		w+=1;
	}

	return w-1;
}

bool left_mov(p_node &s)		//�ո�����
{
	int x=s->i_0,y=s->j_0;

	if (y==0)
	{
		return false;
	}

	int t;
	t=s->a[x][y];
	s->a[x][y]=s->a[x][y-1];
	s->a[x][y-1]=t;

	--s->j_0;

	return true;
}

bool right_mov(p_node &s)	//�ո�����
{
	int x=s->i_0,y=s->j_0;

	if (y==2)
	{
		return false;
	}

	int t;
	t=s->a[x][y];
	s->a[x][y]=s->a[x][y+1];
	s->a[x][y+1]=t;
	
	++s->j_0;
	
	return true;
}

bool up_mov(p_node &s)	//�ո�����
{
	int x=s->i_0,y=s->j_0;
	
	if (x==0)
	{
		return false;
	}
	
	int t;
	t=s->a[x][y];
	s->a[x][y]=s->a[x-1][y];
	s->a[x-1][y]=t;
	
	--s->i_0;
	
	return true;
}

bool down_mov(p_node &s)	//�ո�����
{
	int x=s->i_0,y=s->j_0;
	
	if (x==2)
	{
		return false;
	}
	
	int t;
	t=s->a[x][y];
	s->a[x][y]=s->a[x+1][y];
	s->a[x+1][y]=t;
	
	++s->i_0;
	
	return true;
}

bool is_equal(p_node s1,p_node s2)	//�ж����ڵ��Ƿ����
{
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			if (s1->a[i][j]!=s2->a[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

void copy_node(p_node s1,p_node &s2)	//�����µĽ�㣨��s2��ֵ��s1��
{

	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			s1->a[i][j]=s2->a[i][j];
		}
	}

	s1->i_0=s2->i_0;
	s1->j_0=s2->j_0;
	
	s1->d=s2->d;
	s1->w=s2->w;
	s1->f=s2->f;
	s1->father=s2->father;
	
}

void add_list(p_list &l,p_node s)	//�����㵽OPEN���л�CLOSE����
{

	l->a[l->length++]=s;

}

void delete_list(p_list &l)		//��OPEN���CLOSE��ɾ�����
{
	for (int i=0;i<l->length;i++)
	{
		l->a[i]=l->a[i+1];
		
	}	
	l->length--;
}

bool search_list(p_list &l,p_node s)//�Ա���в��ң��ɹ�����true
{
	for(int i=0;i<l->length;i++)
	{
		if(is_equal(l->a[i],s))
			return true;
	}

	return false;
}

void move(p_node s)//�ƶ����ڵ㲢����δ̽�����У���չ��㣩
{

	p_node p1=(p_node) malloc(sizeof(node));
	p_node p2=(p_node) malloc(sizeof(node));
	p_node p3=(p_node) malloc(sizeof(node));
	p_node p4=(p_node) malloc(sizeof(node));
	

	copy_node(p1,s);
	copy_node(p2,s);
	copy_node(p3,s);
	copy_node(p4,s);

	p1->father=s;
	p2->father=s;
	p3->father=s;
	p4->father=s;


	//����ܹ��ƶ�����CLOSED���в����ڣ������OPEN����

	if(left_mov(p1) && !is_equal(p1,p1->father) && !search_list(CLOSED,p1) && !search_list(OPEN,p1))
	{
		add_list(OPEN,p1);
		
		p1->d+=1;
		p1->w=w(p1);
		p1->f=f(p1);
	}
	else
	{
		free(p1);
	}
	
	if(right_mov(p2) && !is_equal(p2,p2->father) && !search_list(CLOSED,p2) && !search_list(OPEN,p2))
	{
		add_list(OPEN,p2);
		
		p2->d+=1;
		p2->w=w(p2);
		p2->f=f(p2);
	}
	else
	{
		free(p2);
	}

	if(up_mov(p3) && !is_equal(p3,p3->father) && !search_list(CLOSED,p3) && !search_list(OPEN,p3))
	{
		add_list(OPEN,p3);
		
		p3->d+=1;
		p3->w=w(p3);
		p3->f=f(p3);
	}
	else
	{
		free(p3);
	}

	if(down_mov(p4) && !is_equal(p4,p4->father) && !search_list(CLOSED,p4) && !search_list(OPEN,p4))
	{
		add_list(OPEN,p4);
		
		p4->d+=1;
		p4->w=w(p4);
		p4->f=f(p4);
	}
	else
	{
		free(p4);
	}

}

void sort_list(p_list &l)	//��OPEN��������򣬲��뷨���򣨰�f��С����
{
	p_node t=(p_node) malloc (sizeof(node));

	for(int i=1;i<l->length;i++)
	{
		if(l->a[i]->f < l->a[i-1]->f)
		{	
			copy_node(t,l->a[i]);
			int j;
			for( j=i;j>0;j--)
			{
				copy_node(l->a[j],l->a[j-1]);
			}
			copy_node(l->a[j],t);
		}
	}	
}

void list_reverse(p_node &p)		//����������
{
	p_node p_pre,p_suc;

	p_pre=NULL;
	p_suc=p->father;

	while(p)
	{
		p->father=p_pre;
		p_pre=p;
		if(p_suc == NULL)
		{
			break;
		}
		p=p_suc;
		p_suc=p_suc->father;
	}
}

void init_node()	//��ʼ��
{
	//---------------------------------------��ʼ����ʼ���

	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			start_node->a[i][j]=start[i][j];

			if(start_node->a[i][j] == 0)
			{
				start_node->i_0=i;
				start_node->j_0=j;
			}
		}
	}

	start_node->d=0;
	start_node->father=NULL;
	start_node->w=w(start_node);
	start_node->f=f(start_node);

	//---------------------------------------��ʼ��Ŀ����

	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			end_node->a[i][j]=ss_end[i][j];

			if(start_node->a[i][j] == 0)
			{
				end_node->i_0=i;
				end_node->j_0=j;
			}
		}
	}

	end_node->d=0;
	end_node->w=w(end_node);
	end_node->f=f(end_node);

	OPEN->length=0;
	CLOSED->length=0;

	add_list(OPEN,start_node);	//��ʼ������OPEN����

	cout<<"��ʼ���Ϊ��\n";
	cout_node(start_node);

	cout<<"Ŀ����Ϊ��\n";
	cout_node(end_node);
}
