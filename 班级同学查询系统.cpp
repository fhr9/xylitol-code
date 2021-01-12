#include <iostream>
#include <string>  //字符串处理
#include <fstream> //文件流
using namespace std;
ifstream fin("/Users/mac/list.txt");
struct student //定义学生结构体
{
   string ykt;  //一卡通号
   string id;   //个人学号
   int pureid;  //纯数字学号，就是没有d
   int Class;   //班级，c不能小写否则会是关键字类
   string name; //姓名
   student *next;
};
student *create() //创建链表
{
   string c;        //我们准备通过一行一行读取，c是存放第一行一卡通号 学号 姓名几个字的
   getline(fin, c); //读取一行，这样一卡通号 学号 姓名几个字就会留在c，然后文件的正式读取会从第二行开始
   char d[7];       //定义一个长度为7的数组，待会把带d的学号转换为不带d的学号
   student *head = NULL, *p1, *p2;
   p1 = new student;//建立第一个节点，开辟存储空间
   while (!fin.eof())//尚未读到文件尾时
   {
      fin >> p1->ykt;//输入一卡通号
      fin >> p1->id;//输入学号
      int t = 0;//构建纯数字学号
      for (int i = 0; p1->id[i] != '\0'; ++i)//把数字一个一个放进d的数组中
      {
         if (p1->id[i] >= '0' && p1->id[i] <= '9')
            d[t++] = p1->id[i];
      }
      p1->pureid = (d[0] - '0') * 1000000 + (d[1] - '0') * 100000 + (d[2] - '0') * 10000 + (d[3] - '0') * 1000 + (d[4] - '0') * 100 + (d[5] - '0') * 10 + (d[6] - '0') * 1;
      //对，就是这么笨的办法，把它转换成int型纯数字，这样待会才好排序
      p1->Class = (d[0] - '0') * 10000 + (d[1] - '0') * 1000 + (d[2] - '0') * 100 + (d[3] - '0') * 10 + (d[4] - '0') * 1;
      //同理orz
      fin >> p1->name;//输入名字
      if (head == NULL)//如果建立的结点点是头结点
         head = p1;//赋值链表头指针
      else
         p2->next = p1;//如果不是头结点，将p1结点与p2结点链接起来
      p2 = p1;
      p1 = new student;//继续建立新的结点
      fin >> p1->ykt;
      fin >> p1->id;
      fin >> p1->name;
   }
   p2->next = NULL;//建立完全部结点，设置链表结束标志
   return head;//返回新建链表的头指针
}
student *sort(student *head)//排序
{
   student *p1, *p2, *q1, *q2;
   p1 = head;//p1指向head
   p2 = p1->next;//p2指向p1的next 也就是下一个结点
   while (p2)//如果不是末尾结点
   {
      if (p1->pureid <= p2->pureid)//若第i个结点（i从2开始）的成员 学号 大于或等于第i-1个结点的值，则保持第i个结点在链表中的位置不变
      {
         p1 = p2;//p1指向下一个结点
         p2 = p2->next;//p2指向下一个结点的next，也就是第三个结点，以此类推
      }
      else
      {
         p1->next = p2->next;//否则将第i个结点从链表中删除（使第i-1个结点的指针指向第i+1个结点）
         q1 = head;//将已脱离链表的第i-1个结点插入到链表列表的钱i-1个结点中，并保持插入结点后链表前i个结点有序
         q2 = q1->next;
         if (p2->pureid < head->pureid)//p2现在仍指向已经脱离链表的结点 如果它比第一个还小，就把它放在第一个
         {
            p2->next = head;//p2的next指向head，也就是把p2放在最前面，屁股后面跟着head
            head = p2;//再把head挪到前面
         }
         else
         {
            q1 = head;//如果比开头大要把它放在适当的位置
            q2 = head->next;
            while (p2->pureid > q2->pureid)//当p2的值比q2大时，q1，q2是去找位置的指针
            {
               q1 = q2;//都往后一个
               q2 = q2->next;
            }
            p2->next = q2;//while不执行后，就是它应该在的位置，把p2放进去，把其和前后连接起来
            q1->next = p2;
         }
         p2 = p1->next;//一个弄完了，往下一个
      }
   }
   return head;
}
void seekclass(student *head, int a)//班级查询
{
   student *p;//p用来查找
   int flag = 0;//后面看是否有这个班级在
   p = head;//p指向头
   while (p != NULL)//没到末尾时
   {
      if (p->Class == a)//如果class和你输入的相等，输出全部信息
      {
         cout << p->ykt << '\t' << p->id << '\t' << p->name << endl;
         flag++;//让flag不再等于1
      }
      p = p->next;//指向下一个
   }
   if (flag == 0)//如果flag没变过，说明没有这个班级的学生
   {
      cout << "查无此班" << endl;
   }
}
void seek(student *head, string a)//个人查询
{
   student *p;
   p = head;
   while (p->id != a)//没找到这个学号的话
   {
      p = p->next;//往下找
      if (p == NULL)//如果到最后一个都没找到，输出查无此人
      {
         cout << "查无此人" << endl;
         break;//退出循环
      }
   }
   if (p != NULL)//如果找到了这个学号的话，输出全部信息
      cout << p->ykt << '\t' << p->id << '\t' << p->name << endl;
}
void print(student *head)//显示
{
   student *p = head;
   while (p != NULL)
   {
      cout << p->ykt << '\t' << p->id << '\t' << p->name << '\t' /*<<p->Class*/ /*<<'\t'<<p->pureid*/ << endl;
      p = p->next;
   }
}
int main()
{
   student *head, *p0;
   head = create();
   sort(head);//排序
   int key;//输入相应数字进入相应项目
   while (true)//用死循环来做到重复查询
   {
      system("cls"); //清屏，苹果电脑上是clear；Windows上是cls
      cout << "主菜单" << endl;//主菜单样式
      cout << "输入数字进入相应查询，输入4退出查询" << endl;
      cout << "1 个人查询" << endl;
      cout << "2 班级查询" << endl;
      cout << "3 全体查询" << endl;
      cin >> key;//输入key
      switch (key)
      {
      case 1:
         cout << "输入学号以查询，按0回到主菜单，按4退出查询" << endl;
         while (true)//用死循环做到重复查询
         {
            string a;//用string类因为学号带d，用了string类==被重载，可以直接判断字符串是否相等
            cin >> a;
            if (a == "0")//如果是0就退出case的这个循坏
               break;
            else if (a == "4")//4的话退出程序
               exit(0);
            else
               seek(head, a);
         }
         break;//一break switch就结束，回到大循环，也就是主菜单页面
      case 2:
         cout << "输入前五位学号以查询，按0回到主菜单，按4退出查询" << endl;
         while (true)//同case 1理
         {
            int a;
            cin >> a;
            if (a == 0)
               break;
            else if (a == 4)
               exit(0);
            else
               seekclass(head, a);
         }
         break;
      case 3:
      {
         cout << "一卡通号" << '\t' << "学号" << '\t' << '\t' << "姓名" << endl;//好看一点
         print(head);
         string a;
         cout << "按0回到主菜单，按4退出查询" << endl;
         cin >> a;
         if (a == "0")
            break;
         else if (a == "4")
            exit(0);
      }
      break;
      case 4:
         exit(0);
      }
   }
   //此循坏只能按4退出
}