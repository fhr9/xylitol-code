#include<iostream>
#include<fstream>//文件流
#include<string>//字符串处理
using namespace std;
int x,y;//定义全局变量行列数
void swap(char &a,char &b)//交换，引用型，ab可以当做实参
{
   char t;
   t=a;
   a=b;
   b=t;
}
void getxy(char a[10][10])//获取行列数
{
    y = 0;//行数初始化
for (int i=0;i<10;i++)//遍历全部数组，获取行数
{
   if (a[i][0] !='\0')//如果开头不是空，说明这一行不是空
      y++;
}
 x=strlen(a[0]);//一行里的长度就是列数
}
void h(char a[10][10])//水平翻转
{
   int i,m,n=x-1;//i是行数,mn是交换时的定位,x是列数但数组是从0开始的所以最后一个是x-1
   for(i=0;i<y;i++)//一行一行来
   {
      for(m=0;m<n;m++,n--)//你书上的
      swap(a[i][m],a[i][n]);
      n=x-1;//n复位
   }
   getxy(a);//实时获取a的大小
}
void c(char a[10][10])//顺时针
{
   int i,m,t=y-1;//i是行数，m是列数，t是赋值时的定位
   char b[10][10]={};//初始化数组，={}的意思是让全部都为'\0'，要不然会显示出奇奇怪怪的东西
   char c[10][10]={};//同理
   for(i=0;i<y;i++)//复制一个a数组，方便进行赋值操作
   strcpy(b[i],a[i]);
   for(i=0;i<x;i++)//一行一行来，这里行数取x，因为你转了以后列数就变成了行数
   {
      for(m=0;m<y;m++)//一列一列来
      {
         c[i][m]=b[t--][i];//这个你具体跟着走一遍，我说不清楚，就是把第一列的最后一个给a[0][0]，然后往上那一个给a[0][1]这样子
      }
      t=y-1;//t复位
   }
   for(int q=0;q<y;q++)//将a数组清空，因为不是初始化所以不能用={}
    {
       for(int w=0;w<x;w++)
       a[q][w]='\0';
    }
   getxy(c);
   for(i=0;i<y;i++)//最后把c数组复制到a里面
   strcpy(a[i],c[i]);
   getxy(a);//这个步骤可有可无，因为c和a的数组大小肯定一样
}
void v(char a[10][10])//垂直翻转，和水平翻转差不多
{
   int i,m,n=y-1;
   for(i=0;i<x;i++)
   {
      for(m=0;m<n;m++,n--)
      swap(a[m][i],a[n][i]);
      n=y-1;
   }
   getxy(a);
}
void a(char a[10][10])//逆时针
{
   int i,m,t=0,p=x-1;
   char b[10][10]={};
   char c[10][10]={};
   for(i=0;i<y;i++)
   strcpy(b[i],a[i]);
   for(i=0;i<x;i++)
   {
      for(m=0;m<y;m++)
      {
         c[i][m]=b[t++][p];//最后一列的第一个给a[0][0],往下一个给a[0][1]这样子
      }
      p--;
      t=0;
   }
for(int q=0;q<y;q++)
    {
       for(int w=0;w<x;w++)
       a[q][w]='\0';
    }
   getxy(c);
   for(i=0;i<y;i++)
   strcpy(a[i],c[i]);
}
void show(char a[10][10])//显示
{   
for(int q=0;q<y;q++)
    {
       for(int w=0;w<x;w++)
       cout<<a[q][w];
       cout<<'\n';
    }
}

int main()
{
    ifstream fin("/Users/mac/github/xylitol-code/figure.txt");
    char matrix[10][10]={};//matrix初始化，全为'\0'
    int i=0;
    while(!fin.eof())//到文件尾时停止循环
    {
        if(!fin.getline(matrix[i],10)||strlen(matrix[i])<2)//如果输入失败，相当于输入的大于10
        {
           cout<<"阵列大小有误"<<endl;
           exit(0);
        }
        i++;
    }

    y=i;
    x=strlen(matrix[0]);
    show(matrix);
    char ch;
    while(true)
    {
       cin.get(ch);
       switch(ch)
       {
          case 'h':
          h(matrix);
          cout<<"水平翻转后为："<<endl;
          show(matrix);
          break;
          case 'v':
          v(matrix);
          cout<<"垂直翻转后为："<<endl;
          show(matrix);
          break;
          case 'c':
          c(matrix);
          cout<<"顺时针旋转90度后为："<<endl;
          show(matrix);
          break;
          case 'a':
          a(matrix);
          cout<<"逆时针旋转90度后为："<<endl;
          show(matrix);
          break;
          case 'x':
          exit(0);
       }
    }
    return 0;
}