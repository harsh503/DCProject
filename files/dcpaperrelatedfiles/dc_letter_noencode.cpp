#include<bits/stdc++.h>
#include<math.h>
#include<cstring>
using namespace std;
int bit_count;
struct sort_pred {
    bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
        return left.second < right.second;
    }
};

int cost_cal(int x)
{
	int temp;
	temp=x;
	int dc,rl;
	int prev;
	int crl;
	prev=-1;
	crl=0;
	rl=0;
	dc=0;
	int t=8;
	while(t--)
	{
		int val;
		val=temp%2;
		temp=temp/2;
		
		if(crl==0)
		{
			crl=1;
			prev=val;
		}
		else if(val==prev)
		{
			prev=val;
			crl++;
		}
		else{
			prev=val;
			crl=1;
		}
		if(crl>rl)
		{
			rl=crl;
		}

		if(val==1)
		{
			dc++;
		}
		else{
			dc--;
		}

	}

	int cost=dc*dc+rl*rl;
	return(cost);
}

int main()
{
	//cout<<"bit count:8\n";
	bit_count=8;
	int t;
	string order="etaoinshrdlcumwfgypbvkjxqz";
	std::vector<pair<int,int>> v;
	for (int i = 0; i < pow(2,bit_count); ++i)
	{
		int cost=cost_cal(i);
		v.push_back(std::make_pair(i,cost));
	}
	std::sort(v.begin(), v.end(), sort_pred());

int matrix[256];
int mark[256];
for(int i=0;i<256;i++)
{
	matrix[i]=i;
	mark[i]=0;
}

for(int i=0;i<order.length();i++)
{
	if(mark[(int)order[i]]==0&&mark[v[i].first]==0)
	{
	matrix[(int)order[i]]=v[i].first;
	matrix[v[i].first]=(int)order[i];
	mark[(int)order[i]]=1;
	mark[v[i].first]=1;
	}
	//cout<<order[i]<<" "<<matrix[(int)order[i]]<<endl;
}

for(int i=0;i<256;i++)
{
	matrix[i]=i;
	mark[i]=0;
}
/*for(int i=0;i<256;i++)
{
	if(matrix[i]!=i)
	{
		if(matrix[matrix[i]]==matrix[i]&&(i>='a'&&i<='z'))
		{
			matrix[matrix[i]]=i;
			//cout<<"hello"<<matrix[matrix[i]]<<endl;
		}
	}
	
}
*/

std::vector<int> buff;
char str[10240];
cin.getline(str,10240);
for(int i=0;i<strlen(str);i++)
{
	int temp=matrix[(int)str[i]];
	int t=bit_count;
	buff.clear();
	while(t--)
	{
		buff.push_back(temp%2);
		temp=temp/2;
	}
	reverse(buff.begin(),buff.end());
	for(int j=0;j<bit_count;j++)
	{
		cout<<buff[j]<<endl;
	}
	
}

}
