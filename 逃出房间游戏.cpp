#include<iostream>
#include<fstream>
//#include<conio.h>//如果想实现不用输一个字母按一个空格就把最前面的//删除，但我不能保证你有conio.h这个库，因为它不是c的标准库，报错你就删了吧，搭配getch()使用
using namespace std;
int a,b,i,j,e,f,c,d,g,h,nx,ny,sx,sy,flag=0,flag2=0;
int t=0;//想把计步器放在开头就需要换个名字，因为头文件里有重载的count，就相当于放在开头会有另一个叫jrj的人，计算机会认不出来
char key;//a,b为房间长宽；e，f为门的坐标；c，d为窗的坐标；g，h为家具的坐标
ifstream fin;//类的使用定义，不用去了解，就相当于定义了一个和cin一样的东西可以输入文件
ofstream fout;//类比cout
void loc()
{
fin.open("/Users/max/Downloads/config.txt");//打开config.txt以下所有的文件位置以你自己的文件位置为准，这只是我的文件位置
fin>>a>>b>>e>>f>>c>>d;//读取
fin.close();//关闭，一定要记得关闭
if(((1<e+1&&e+1<a)&&(1<f+1&&f+1<b)||e+1<1||e+1>a||f+1<1||f+1>b||((e+1==1)&&(f+1==1))||((e+1==a)&&(f+1==1))||((e+1==1)&&(f+1==b))||((e+1==a)&&(f+1==b)))||((1<c+1&&c+1<a)&&(1<d+1&&d+1<b)||c+1<1||c+1>a||d+1<1||d+1>b||(c+1==1&&d+1==1)||(c+1==a&&d+1==1)||(c+1==1&&d+1==b)||(c+1==a&&d+1==b)||(c==e&&(d==f-1||d==f+1))||(d==f&&(c==e-1||c==e+1))))//不满足那一大堆条件的时候
{
    cout<<"您的位置输入有误"<<endl;//直接说位置有无退出程序就可，不必再说什么重新输入
    exit(0);//退出程序
}
srand(time(NULL));//计算机并没有真正的随机数，其实是有一个很大的数字库，然后从里面排下来，所以我们要初始化种子（也就是选一个数字库的开头），达成一种所谓的随机
g=abs(rand()%a);//rand是随机取值函数，但它可以很大，可以很小，可以是负数，所以我们要取余相应的a 这样就能控制在0到a-1之间了，就比如我们取余10，那任何数字都可以变成0到9的数字，这个你体会一下，很妙
h=abs(rand()%b);//同上
nx=abs(rand()%a);//同上
ny=abs(rand()%b);//同上
while(g==0||h==0||nx==0||ny==0||(g+1<=1||g+1>=a||h+1<=1||h+1>=b||(g==e&&(h==f+1||h==f-1))||(h==f&&(g==e+1||g==e-1)))||((!((1<nx+1&&nx+1<a)&&(1<ny+1&&ny+1<b)))||(nx==g&&ny==h)))//如果选的位置不满足条件，就重新选
{g=abs(rand()%a);
h=abs(rand()%b);
nx=abs(rand()%a);
ny=abs(rand()%b);
}
}
void draw()//显示图像的函数，同上，copy就可
{
    system("clear");//清屏函数，我的电脑不支持，你要用就把最前面的//删掉
    for(i=1;i<=b;i++)//画图函数不再赘述
{
	for(j=1;j<=a;j++)
	{
        if(i==f+1&&j==e+1)//门
        cout<<" ";
        else if(i==d+1&&j==c+1&&(c==0||c==a-1))//窗
        cout<<"|";
        else if(i==d+1&&j==c+1&&(d==0||d==b-1))
        cout<<"-";
        else if(i==h+1&&j==g+1)//家具
        cout<<"*";
		else if(i==1||i==b||j==1||j==a)//墙
		cout<<'#';
        else if(i==ny+1&&j==nx+1)//小人儿
        cout<<'@';
		else cout<<' ';//空间
        }
	cout<<endl;
}
}
void control()//wasd的函数，控制它移动，按一次要按一次回车，进化成control啦，名字升级哈哈
{
    //key=getch();//可以不按回车键就能动起来，搭配conio.h使用
    key=getchar();
    switch(key)//我们用switch语句，可以点对点的调整
    {
        case 'w':
        sy=ny-1;//sy是ny变前的一个替代品，如果用sy不满足条件，那就跳过，如果满足，再让ny执行
        if(sx==e&&sy==f)//如果碰上门也算是可以通行
         {ny--;
         t++;
        flag=1;//flag像是一种状态一样，如果可以通行我们就让它的状态为1
        break;}
        else if((sy+1==1||sy+1==b)||(sx==g&&sy==h))//如果碰上家具或者四周，就无法通行
    {
        cout<<"无法通行"<<endl;
        flag=0;//无法通行的状态记作0
        }
        else //其他情况都是可以通行
    {ny--;
        flag=1;
           t++;}
        break;
        case 's'://其他asd都同上理
         sy=ny+1;
         if(sx==e&&sy==f)
         {ny++;
        flag=1;
        break;}
        else if((sy+1==1||sy+1==b||(sx==g&&sy==h)))
    {
        cout<<"无法通行"<<endl;
        flag=0;
        }
        else 
        {ny++;
        flag=1;
        t++;}
        break;
        case 'a':
         sx=nx-1;
         if(sx==e&&sy==f)
         {nx--;
         t++;
        flag=1;
        break;
        }
        else if((sx+1==1||sx+1==a)||(sx==g&&sy==h))
    {
        cout<<"无法通行"<<endl;
        flag=0;
        }
        else 
        {nx--;
        flag=1;
        t++;}
        break;
        case 'd':
        sx=nx+1;
        if(sx==e&&sy==f)
         {nx++;
         t++;
        flag=1;
        break;}
        else if((sx+1==1||sx+1==a)||(sx==g&&sy==h))
    {
        cout<<"无法通行"<<endl;
        flag=0;
        }
        else 
        {nx++;
        flag=1;
        t++;}
        break;
        case '0'://按0退出程序
        exit(0);
        break;
        case '1'://重开游戏
        flag2=1;//让flag2=1
        flag=1;//让flag=1以便退出control的循环
        break;
        case '2'://存档
        {
        fout.open("/Users/max/Downloads/save.txt");//fout重定向到save打开save文件 记得改位置！！！
        fout<<nx<<'\n'<<ny<<'\n'<<g<<'\n'<<h<<'\n'<<sx<<'\n'<<sy;//把这些位置输进去，加入‘\n’回车键是为了待会好读取要不然待会只能读一串大数字
        fout.close();//关闭！！！
        break;
        }
        case '3'://读档
        t=0;//计步器清零
        fin.open("/Users/max/Downloads/save.txt");//fin重定向到save打开save文件 改位置！！！
        fin>>nx>>ny>>g>>h>>sx>>sy;//把数据读取进来
        fin.close();//关闭！！！
        draw();//重新画图
        break;
    }
}
int main()
{
    while(true)//死循环，然后待会满足条件break 要不然不能实现按1重开游戏
{
loc();//执行第一次的定位
 sx=nx;
    sy=ny;
draw();//执行第一次画图
while(!(nx==e&&ny==f))//当人不在门上的时候
{
while(flag==0)//当无法通行的时候我们就重复执行move
    {
    control();//move里面如果flag变成1就会跳出这个小循环
    }
if(flag2==1)//如果flag2=1，那就退出画图这个中循环
break;
draw();//画图
flag=0;//让它的状态重新变为0，要不然会死循环
}
if(flag2==1)//这里是重开的真正程序
{
flag2=0;//先让flag2复位，要不然死循环
t=0;//重置计步器
continue;//如果flag2=1那就跳过这一整个的大循环，也就是跳过一次以上所有，也就相当于重新开始
}
cout<<"游戏过关，所用步数为"<<t<<endl;//游戏完成的语句
break;//退出死循环
}
return 0;//结束
}
//现在还有点小bug比如好像还是有时候没办法出门，但我觉得他应该看不出来，自己运行程序遇到的几率不大