#include <iostream>//输入输出流
#include <cmath>//数学库
#include <iomanip>//设置小数点的库
#include <sstream>//格式转换的库
#include <string>//字符串库
using namespace std;//标准化命名空间
#define PI 3.1415926//宏定义常量π
stringstream ss;//类似ifstream fin；定义一个对象
string e = "end";//我接下来基本都用的string类做的，就是个字符串，但string类更简便
//你仍然可以用e[0]来指e e[1]来指n
int flag = 0;//pd和proc中要用到的
int flag3 = 0;//待会主函数里用到，让程序更健全，不构成三角形时直接进入提示，不再输出度数和面积
bool AllisNum(string str)//输入12时其实会分别存入1和2，这个函数判断是否全为数字；函数类型为布尔型，待会if可以直接用，如果改成int请在最后加上return 1；
{
    for (int i = 0; i < str.size(); i++)//遍历字符串，判断每一个是不是数字
    {
        int tmp = (int)str[i];//将字符数字转化为ASCII码
        if (tmp >= 48 && tmp <= 57)//ASCII码的0-9就是48-57
        {
            continue;//如果是就下一个循环
        }
        else
        {
            return false;//如果有一个不是数字就返回false，例如1r
        }
    }
    return true;//如果都是数字就返回true
}

double round(double r)//自己定义的四舍五入函数
{
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

void B(double a, double b, double c)//判断三角形形状的函数
{
    if (a + b <= c || a + c <= b || b + c <= a)
    {
        cout << "不可以构成三角形" << endl;
        flag3 = 1;//让flag3变为1，待会主函数要用
    }
    else
    {
        if (a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a)
        {
            cout << "直角三角形" << endl;
        }
        else
        {
            if (a * a + b * b > c * c && a * a + c * c > b * b && b * b + c * c > a * a)
            {
                cout << "锐角三角形" << endl;
            }
            else
            {
                cout << "钝角三角形" << endl;
            }
        }
    }
}

void J(double a, double b, double c)//角度
{
    double ja, jb, jc;
    ja = acos((c * c + b * b - a * a) / (2 * b * c)) * 180 / PI;
    jb = acos((c * c + a * a - b * b) / (2 * a * c)) * 180 / PI;
    jc = acos((b * b + a * a - c * c) / (2 * b * a)) * 180 / PI;
    cout << "三个角度数分别为" << fixed << setprecision(0) << round(ja) << '\t' << round(jb) << '\t' << round(jc) << endl;
}

void S(double a, double b, double c)//面积
{
    double s, p;
    p = (a + b + c) / 2;
    s = sqrt(p * (p - a) * (p - b) * (p - c));
    cout << "三角形面积为" << fixed << setprecision(2) << s << endl;
}
void pd(string &x1, double &x, int &flag)//判断string里面是数字 字符还是end
{
    if (AllisNum(x1))//如果全是数字
    {
        ss << x1;//将string转化为double并输入x，具体实现是库定义的，不深究
        ss >> x;
        ss.clear();//清空流里面的内容
        flag = 1;//记flag为1 待会proc要用
    }
    else if (e == x1)//如果输入的是end；注意这里的==是被string类重载过了，可以直接判断两个string类是否相等
        flag = 2;
    else//如果不是数字不是end
        flag = 3;
}
void proc(string &x1, double &x, int &flag)
{
    while (flag != 1)
    {
        if (flag == 2)
            exit(0);
        if (flag == 3)
        {
            if (x1[0] == '-')
            {
                cout << "请输入正整数！" << endl;
                cin.clear();
                cin.sync();
                cin.ignore(1024, '\n');
                cin >> x1;
                pd(x1, x, flag);
            }
            else
            {
                cout << "错误输入！请重新输入" << endl;
                cin.clear();
                cin.sync();
                cin.ignore(1024, '\n');
                cin >> x1;
                pd(x1, x, flag);
            }
        }
    }
}
int main()
{
    double a, b, c;
    string a1, b1, c1;
    int flag2 = 1;//控制程序重复运行的flag
    string d;//程序末尾end的判断
    while (flag2)//flag2=0时退出循环
    {
        cout << "请输入三角形三边长度" << endl;
        cin >> a1;
        pd(a1, a, flag);//判断
        proc(a1, a, flag);//处理
        cin >> b1;
        pd(b1, b, flag);
        proc(b1, b, flag);
        cin >> c1;
        pd(c1, c, flag);
        proc(c1, c, flag);
        B(a, b, c);
        if (flag3 == 1)//如果不构成三角形
        {
            flag3 = 0;//flag复位
            cout << "输入end结束，否则按键继续" << endl;
            cin >> d;
            if (d == e)
                exit(0);//如果输的是end就直接退出
            else
                continue;//否则进入下一个循环
        }
        J(a, b, c);
        S(a, b, c);
        cout << "输入end结束，否则按键继续" << endl;
        cin >> d;
        if (d == e)
            flag2 = 0;
        else
            continue;
    }
    return 0;
}
