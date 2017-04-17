#include<bits/stdc++.h>
using namespace std;
#define outside 0
#define inside 1
#define pibit 2

int maxrl=3;
int rl=-1;
int prev=-1;
int rd=0;
int rd_th=4;
int maxsize=8;
int s=4;
int pos=0;
int ends=0;
std::vector<int> input;
std::vector<int> output;
std::vector<int> fifo;
int originalsize;
int mod(int x)
{
	if(x<0)
		return (-x);
	else
		return (x);
}

int getdata()
{
	return input[pos++];
}

void put_data(int x)
{
	output.push_back(x);
}

void append_fifo(int x)
{
	fifo.push_back(x);
}

void update_rl(int x)
{
	if (rl==-1)
	{
		rl=1;
		::prev=x;
	}
	else if(x==::prev)
	{
		rl++;
	}
	else
	{
		rl=1;
		::prev=x;
	}
}

void update_rd()
{
	rd=0;
	for (int i = 0; i < pos; ++i)
	{
		if(input[i]==0)
			rd--;
		else
			rd++;
	}
}

int decode_rl()
{
	int x=getdata();
	update_rl(x);
	if(::rl==maxrl)
	{
		int y=getdata();
		update_rl(y);
	}
	return x;
}

int calculate_rd()
{
	int rdfifo=0;
	for(int i=0;i<fifo.size();i++)
	{
		if(fifo[i]==0)
			rdfifo--;
		else
			rdfifo++;
	}
	return rdfifo;
}

void invertfifo()
{
	for(int i=0;i<fifo.size();i++)
	{
		if(fifo[i]==0)
			fifo[i]=1;
		else
			fifo[i]=0;
	}
}

void decode()
{
	int mode=outside;
	int z;
	int count=0;
	while(true)
	{
		if(pos==maxsize)
			break;
		int x=decode_rl();
		if(mode==outside)
		{
			put_data(x);
			update_rd();
			if(mod(rd)==rd_th)
			{
				mode=inside;
				count=0;
				fifo.clear();
			}
		}
		else if(mode==inside)
		{
			count++;
			append_fifo(x);
			if(count==s-1)
			{
				mode=pibit;
			}
		}
		else if(mode==pibit)
		{
			append_fifo(x);
		
			int rdfifo=calculate_rd();
			if(rdfifo!=0)
			{
				x=decode_rl();
				if(x==1)
				{
					invertfifo();
				}
			}
			for(int i=0;i<fifo.size();i++)
			{
				put_data(fifo[i]);
			}
			update_rd();
			
			while(mod(rd)>rd_th)
			{

				int x=decode_rl();
				update_rd();
			}
			
			if(mod(rd)==rd_th)
			{
				mode=inside;
				count=0;
				fifo.clear();
			}
			else
			{
				mode=outside;
			}
		}
	}
}

int main()
{
	cout<<"Enter the value of MAX_RL.\n";
	cin>>maxrl;
	cout<<"Enter the value of RD_TH.\n";
	cin>>rd_th;
	cout<<"Enter the size of the S-Block.\n";
	cin>>s;
	cout<<"Enter the size of the original sequence\n";
	cin>>originalsize;
	cout<<"Enter the size of the input encoded sequence.\n";
	cin>>maxsize;
	cout<<"Enter the string encoded by the algorithm bit by bit.\n";
	for(int i=0;i<maxsize;i++)
	{
		int x;
		cin>>x;
		input.push_back(x);
	}	
	decode();
	cout<<"The output decoded sequence is : \n";
	for (int i = 0; i < originalsize; ++i)
	{
		cout<<output[i];
	}
	cout<<"\n";
}
