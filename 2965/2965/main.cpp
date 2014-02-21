#include <iostream>
#include <queue>
#include <string>
using namespace std;
struct mac
{
	char a[4][4];
	int depth;
	int num;
	string path; 
};

bool deter(char a[4][4])
{
	bool open=true;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(a[i][j]=='+')
				open=false;
	return open;
}

char** move(char b[4][4],int num)
{
	char * cp=new char[4];
	char ** dcp=new char*[4];
	int x=num/4;
	int y=num%4;
	char a[4][4];
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			a[i][j]=b[i][j];
	for(int i=0;i<4;i++)
		if(a[i][y]=='-')
			a[i][y]='+';
		else
			a[i][y]='-';
	for(int j=0;j<4;j++)
		if(a[x][j]=='-')
			a[x][j]='+';
		else
			a[x][j]='-';
	if(a[x][y]=='-')
			a[x][y]='+';	
	else
			a[x][y]='-';
	for(int i=0;i<4;i++)
	{	
		cp=new char[4];
		for(int j=0;j<4;j++)
			cp[j]=a[i][j];
		dcp[i]=cp;
	}
	return dcp;
}



mac recu(queue <mac>mq,int count)
{
	int count_f=0;
	if(count==1&&mq.front().num==15)
		return mq.front();
	for(int i=0;i<count;i++)
	{
		mac mca=mq.front();		
		mq.pop();
		for(int j=mca.num+1;j<16;j++)
		{
			char ** p=move(mca.a,j);
			mac mcb;
			for(int ii=0;ii<4;ii++)
				for(int jj=0;jj<4;jj++)
					mcb.a[ii][jj]=p[ii][jj];
			mcb.depth=mca.depth+1;
			mcb.num=j;
			int x=mcb.num/4+1;
			int y=mcb.num%4+1;
			char x_c[4];
			char y_c[4];
			_itoa_s(x,x_c,10);
			_itoa_s(y,y_c,10);
			string x_s=x_c;
			string y_s=y_c;
			mcb.path=mca.path+x_s+y_s;
			if(deter(mcb.a))			
				return mcb;
			mq.push(mcb);
			count_f++;
		}
	}
	return recu(mq,count_f);
}

int main()
{
	mac mc;
	mc.depth=0;
	mc.num=-1;
	mc.path="";
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			cin>>mc.a[i][j];
	queue<mac> mq;
	mq.push(mc);
	mac mc_r=recu(mq,1);
	cout<<mc_r.depth<<"\n";
	int path_l=mc_r.path.length();
	for(int i=0;i<path_l;i=i+2)
		cout<<mc_r.path[i]<<" "<<mc_r.path[i+1]<<"\n";
	system("pause");
	return 1;
}