#include<bits/stdc++.h>
using namespace std;
#define outside 0
#define inside 1

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


int min(int x,int y)
{
	if(x<y)
		return x;
	else
		return y;
}
int mod(int x)
{
	if(x<0)return(-x);
	return(x);
}

int get_data()
{
	return(input[::pos++]);
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
void apply_rl(int x)
{
	output.push_back(x);
	update_rl(x);
	if (rl==maxrl)
	{
		if (x==0)
		{
			output.push_back(1);
			rl=1;
			::prev=1;
		}
		else
		{
			output.push_back(0);
			rl=1;
			::prev=0;
		}
	}
}


void update_rd()
{
	rd=0;
	for (int i = 0; i < output.size(); ++i)
	{
		if(output[i]==0)
			rd--;
		else
			rd++;
	}
}
//changes made....padding
int calculate_rd_sblock()
{
	int rdfifo=0;
	int i;
	//padding
	while(::pos+s>maxsize)
	{
		input.push_back(0);
		maxsize++;
	}
	for (i = pos; i < ::pos+s; ++i)
	{
		if(input[i]==0)
		{
			rdfifo--;
		}
		else
		{
			rdfifo++;
		}
	}
	::ends=i;
	return(rdfifo);
}

int prepare_s_block(int rdfifo)
{
	if(rdfifo==0)
	{
		return(0);
	}
	else
	{
		if(rd==rd_th)
		{
			if(rdfifo>0)
			{
				return(1);
			}	
			else{
				return(-1);
			}
		}
		else
		{
			if(rdfifo<0)
			{
				return(1);
			}	
			else{
				return(-1);
			}
		}
	}
}

int invert(int x)
{
	if(x==0)
		return 1;
	else
		return 0;
}
void insert_indication_bit(int sflag)
{
	if(sflag==0)
	{
		return;
	}
	else if(sflag==-1)
	{
		apply_rl(0);
		return;
	}
	else
	{
		apply_rl(1);
		return;
	}
}
void rd_adjust()
{
	while(mod(rd)>rd_th)
	{
		if(rd>0)
		{
			apply_rl(0);
		}
		else
		{
			apply_rl(1);
		}
		update_rd();
	}
	return;
}
void encode()
{
	int mode=outside;
	int sflag;
	
	while(true)
	{
		if(pos==maxsize)
			break;
		int x=get_data();
		if (mode==outside)
		{
			apply_rl(x);
			update_rd();
			if (mod(rd)==rd_th)
			{
				int rdfifo;
				rdfifo=calculate_rd_sblock();
				sflag=prepare_s_block(rdfifo);
				::ends=pos+s;
				mode=inside;
			}
		}
		else if (mode==inside)
		{
			if(sflag>0)
			{
				x=invert(x);
			}
			apply_rl(x);
			if(pos==::ends)
			{
				insert_indication_bit(sflag);

				update_rd();
				rd_adjust();
				if(mod(rd)==rd_th)
				{
					int rdfifo=calculate_rd_sblock();
					sflag=prepare_s_block(rdfifo);
				}
				else
				{
					mode=outside;
				}
			}

		}
	}
}



int main(){
	
	cout<<"Enter the value of MAX_RL.\n";
	cin>>maxrl;
	cout<<"Enter the value of RD_TH.\n";
	cin>>rd_th;
	cout<<"Enter the size of the S-Block.\n";
	cin>>s;
	cout<<"Enter the size of the input sequence.\n";
	cin>>maxsize;
	cout<<"Enter the input sequence bit by bit.\n";
	for (int i = 0; i < maxsize; ++i)
	{
		int x;
		cin>>x;
		input.push_back(x);

	}
	
	encode();
	cout<<"o/p size is:"<<output.size()<<endl;
	cout<<"The outptut encoded sequence is : \n";
	for (int i = 0; i < output.size(); ++i)
	{
		cout<<output[i]<<"\n";
	}
	cout<<"\n";
	
}
