//判断是否打开文件那只能判断你输入的文件名有没有错，或者你的txt文档有没有问题
//判断不了是不是txt文档，它就算只有个根目录也算判定成功
//所以如果你想要程序更加健全需要再弄个fileName字符串中是否含有子串txt的过程
//但这个过程最好用string来实现，但我猜你们string类也没学，因为我们也没学，所以就算了
//如果你有需要可以自行百度，算是我留给你的作业吧哈哈哈
//附加题就不做啦，真的没时间辽，待会高数课我还在帮你写程序哼
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
ifstream fin;//创建一个ifstream对象来管理输入流
int main()//函数主体，方便你弄就不另外搞函数了
{
char fileName[50];//用一串字符数组待会存放文件名数值最好调大一点，因为文件位置有时候蛮长的
cin.getline(fileName,50);//用getline读取一行字符，好处是空格也会被读进去，防止出错，文件名要包含地址噢
fin.open(fileName);//打开文档
while(fin.fail())//如果打开失败会将状态位设置为1，正常的时候为0；还有其他流状态检查方法比如isopen我就不详细介绍了了
{
    fin.clear();//如果失败我们要先将状态位恢复，否则会陷入死循环
    fin.sync();//清空流里面的内容
    cout<<"请检查您输入的文件名是否正确，并再次输入"<<endl;//提示用户错误
    cin.getline(fileName,50);//让用户再次输入
fin.open(fileName);//再次尝试打开
}
char str1[1000];//中间变量，实现逐行读取
char str[1000];//创建字符数组存放文档里的内容
while (!fin.eof())//判断是否为文件尾，用循环实现逐行读取
    {
fin.getline(str1,1000);//从文档里读取内容，并存放到str1中
strcat(str,str1);//将str1拼接到str后面
    }
char a='a';//char类型的a并将它的初始设置为a
int i;//待会用来做循环的变量
int t=0;//待会用来计数的变量
int m=0;//待会cout前面好像有个1234啥的
for(;(int)a<=122;a++)//第一个可以空也可以不空，随你122是z的ASCII码，外循环是从a到z一个个字母判断
{
for(i=0;i<strlen(str);i++)//内循环是遍历整个str看看有多少个a
{
    if(str[i]==a||str[i]==(a-32))//如果字符是a或者A a-32的ASCII码就是A
    t++;//计数+1
}
if(t)//如果t不等于0，也就是如果有这个字母
cout<<++m<<'\t'<<a<<'\t'<<t<<'\t'<< setiosflags(ios::fixed)<<setprecision(1)<<((double)t/strlen(str))*100<<"%"<<endl;
//输出语句 setiosflags(ios::fixed)<<setprecision(1)设置位数<<将t强制转化成double才能算出小数
t=0;//t复位为0，重新开始循环
}
fin.close();
}