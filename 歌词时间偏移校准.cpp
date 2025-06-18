#pragma GCC optimize(1,2,3,"Ofast","inline")
#include<cstdio>
#include<cerrno>
#include<cstring>
#include<unistd.h>
char s[100],s1[100],lyric[300][200];
int line,a0,b0,c0,t0,a1,b1,c1,t1,stdin_backup;
int main()
{
	stdin_backup=dup(fileno(stdin));
	printf("Drop your file here in the window.\n");
	scanf("%[^\n]",s);
	FILE* result=freopen(s,"r",stdin);
	if(result==nullptr)printf("ERROR:%s\n",strerror(errno));
	else
	{
		int result1;
		char c;
		do
		{
			result1=scanf("%[^\n]\n",lyric+line);
//			printf("DEBUG %d: %s\n",line,lyric[line]);
			++line;
		}
		while(result1!=EOF);
		--line;
//		printf("DEBUG: lines=%d\n",line);
		dup2(stdin_backup,fileno(stdin));
		close(stdin_backup);
		printf("Enter the starting time of the first lyric. (eg: 00:01.14)\n");
		scanf("%2d:%2d.%2d",&a0,&b0,&c0);
		t0=a0*6000+b0*100+c0;
//		printf("DEBUG: %2d:%2d.%2d; %d\n",a0,b0,c0,t0);
		strcpy(s1,s);
		int len=strlen(s);
		char* i=s1+len+1;
		do
		{
			*(i+1)=*i;
			--i;
		}while(*i!='.');
		*i='1',*(i+1)='.';
//		printf("DEBUG: %s\n",s1);
		freopen(s1,"w",stdout);
		bool k=true;
		for(int i=0;i^line;++i)
		{
			if(lyric[i][1]<='9'&&lyric[i][1]>='0')
			{
				a1=(lyric[i][1]-'0')*10+(lyric[i][2]-'0');
				b1=(lyric[i][4]-'0')*10+(lyric[i][5]-'0');
				c1=(lyric[i][7]-'0')*10+(lyric[i][8]-'0');
				t1=a1*6000+b1*100+c1;
				if(k)t0-=t1,k=false;
				t1+=t0;
				a1=t1/6000;
				b1=t1/100%60;
				c1=t1%100;
				lyric[i][1]=a1/10+'0';
				lyric[i][2]=a1%10+'0';
				lyric[i][4]=b1/10+'0';
				lyric[i][5]=b1%10+'0';
				lyric[i][7]=c1/10+'0';
				lyric[i][8]=c1%10+'0';
			}
			printf("%s\n",lyric[i]);
		}
	}
	return 0;
}