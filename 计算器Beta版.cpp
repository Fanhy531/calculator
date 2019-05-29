#include<bits/stdc++.h>
using namespace std;

bool ignore;      //忽略错误 
const int Max_weight = 5;               //括号权重 
unsigned int len;
string formals, s;
string formal[100][100];

struct number               //存数字 
{
	unsigned int a, b;    //a分子，b分母 
	bool zhengfu;
}num;
string str;                //表达式 

inline void Output()                     //程序功能介绍 
{
	cout << "开发人员：fanhy(Luogu U51229)，QuantumCheshireCat(Luogu U54591)。\n\n";
	cout << "本程序用于计算不含字母的表达式。\n";
	cout << "暂不支持指数不为整数的运算。\n";
	cout << "暂不支持各类函数。\n";
	cout << "暂不支持位运算。\n";
	cout << "暂不支持10进制以外的运算。\n";
	cout << "请保证所有数据及计算中的数据∈({-2^31,2^31-1} ∩ Q)。（即在 int 范围内的有理数）\n";
	cout << "暂不支持带分数输入。\n";
	cout << "支持百分号 % 。\n";
	cout << "% 被认为是 百分号，不被认为是取模符号。\n";
	cout << "取模运算请使用a\\b表示a%b。\n";
	cout << "阶乘运算只能计算非负整数。\n";
	cout << "排列组合运算只能计算正整数。\n";
	cout << "请用a@b表示A(a,b)或P(a,b)；用a#b表示C(a,b)。\n";
	cout << "请用a$b表示gcd(a,b)，用a&b表示lcm(a,b)。\n";
	cout << "gcd与lcm运算均只能计算正整数。\n";
	cout << "提示：如需要，请在$或&两边加括号，因为$ &的优先级较高。\n";
	cout << "支持> < = 运算，输出 true 或 false 。\n";
	cout << "注意：不保证数据范围超过限制时会报错。\n";
	cout << "请不要在表达式间添加空格。\n";
	cout << "请用英语输入法输入，输入end结束程序。\n";
	cout << "\n";
	cout << "负数请在左右两边加括号。\n";
}

inline void Error(string s1, string s2)                      //错误提示  s1：错误类型，s2：错误原因 
{
	if (ignore) return;
	char ch;
	cout << "警告:\n-----------------------\n";
	cout << s1 << endl;
	cout << "错误原因：" << s2 << endl;
	if (s1 == "系统错误") { cout << "请将此问题报告开发团队，我们会尽快解决这个问题。\n"; exit(0); }                     //反馈提示 
	if (s1 != "系统错误") cout << "如果没有错误，请与开发团队反馈。我们会尽快解决这个问题。\n";                     //反馈提示 
	cout << "您确定要继续运行吗？这可能导致错误的结果或严重的系统错误（Y/N）（忽略所有错误请输A）:";
	cin >> ch;
	if (ch == 'Y') return;
	if (ch == 'A') { ignore = true; return; }
	else exit(0);                   //结束运行 
}

void check_kuohao(unsigned int a, unsigned int b)
{
	int sum = 0;
	for (int i = a; i <= b; i++)
	{
		if (str[i] == '(') sum++;          //左括号加 
		else if (str[i] == ')') sum--;         //右括号减 
		if (sum < 0) Error("输入错误", "表达式括号不匹配");       //左括号比右括号多 
	}
	if (sum != 0) Error("输入错误", "表达式括号不匹配");      //括号不匹配 
	return;
}

inline number resetnum(number a)                  //重置number类 
{
	a.a = 0;
	a.b = 1;
	a.zhengfu = 1;
	return a;
}

inline unsigned int Weight(char ch)                   //计算运算符优先级 
{
	if (ch == '+' || ch == '-') return 1;
	else if (ch == '*' || ch == '/') return 2;
	else if (ch == '!' || ch == '@' || ch == '#' || ch == '$' || ch == '&' || ch == '\\') return 3;                   //阶乘、排列组合、gcd、lcm、取模
	else if (ch == '^') return 4;                   //乘方 
	else Error("输入错误", "未能被识别的字符");                    //其他不支持的运算符 
}

inline unsigned int gcd(unsigned int a, unsigned int b)                 //最大公约数 
{
	if (a == 0 || b == 0) return 1;
	if (a < b) swap(a, b);
	unsigned int temp = 1;
	while (true)
	{
		temp = a % b;
		if (!temp) return b;
		a = b; b = temp;
	}
}

inline unsigned int lcm(unsigned int a, unsigned int b)                 //最小公倍数 
{
	return a * b / gcd(a, b);
}

inline number yuefen(number x)                  //约分 
{
	if (x.a == 0) { x.b = 1; return x; }
	int s = gcd(x.a, x.b);
	x.a /= s, x.b /= s;                 //除以最大公倍数     
	return x;
}

inline number calculate(number a1, number a2, char ch)               //计算1级表达式 
{
	number ans;  ans = resetnum(ans);                 //结果 
	unsigned int s;
	if ((ch == '+' || ch == '-') && a1.b != a2.b)                    //通分 
	{
		s = lcm(a1.b, a2.b);
		a1.a *= s / a1.b;
		a2.a *= s / a2.b;
	}
	else if ((ch == '+' || ch == '-') && a1.b == a2.b) s = a1.b;
	switch (ch)
	{
		case '+':                 //加法 
			if (a1.zhengfu != a2.zhengfu)                   //符号不同 
			{
				if (a1.a >= a2.a) ans.zhengfu = a1.zhengfu, ans.a = a1.a - a2.a;
				else ans.zhengfu = a2.zhengfu, ans.a = a2.a - a1.a;
			}
			else ans.a = a1.a + a2.a;                   //符号相同 
			ans.b = s;
			return ans;
		case '-':                //减法  
			//分类讨论符号的4种情况
			if (a1.zhengfu == 1 && a2.zhengfu == 1)
			{
				if (a1.a >= a2.a) ans.zhengfu = 1, ans.a = a1.a - a2.a;
				else ans.zhengfu = 0, ans.a = a2.a - a1.a;
			}
			else if (a1.zhengfu == 1 && a2.zhengfu == 0)
				ans.zhengfu = 1, ans.a = a1.a + a2.a;
			else if (a1.zhengfu == 0 && a2.zhengfu == 1)
				ans.zhengfu = 0, ans.a = a1.a + a2.a;
			else
			{
				if (a1.a >= a2.a) ans.zhengfu = 0, ans.a = a1.a - a2.a;
				else ans.zhengfu = 1, ans.a = a2.a - a1.a;
			}
			ans.b = s;
			return ans;
		case '*':                  //乘法 
			if (a1.zhengfu != a2.zhengfu) ans.zhengfu = 0;                   //异号相乘 
			else ans.zhengfu = 1;
			ans.a = a1.a*a2.a;
			ans.b = a1.b*a2.b;
			return ans;
		case '/':                 //除法 
			if (a1.zhengfu != a2.zhengfu) ans.zhengfu = 0;
			else ans.zhengfu = 1;
			ans.a = a1.a*a2.b;
			ans.b = a1.b*a2.a;
			return ans;
		case '!':                 //阶乘 
			if (a1.zhengfu == 0) Error("语法错误", "无法计算负数的阶乘");
			a1 = yuefen(a1);
			if (a1.a == 0) return ans;
			if (a1.b != 1) Error("语法错误", "无法计算非整数的阶乘");
			ans.a = 1;
			for (int i = a1.a; i >= 1; i--) ans.a *= i;
			return ans;
		case '@':              //排列 
			if (a1.zhengfu == 0 || a2.zhengfu == 0 || a2.a == 0) Error("语法错误", "排列运算不能计算非正数");
			if (a1.a == 0) { ans.a = 1; return ans; }
			a1 = yuefen(a1), a2 = yuefen(a2);
			if (a1.b != 1 && a2.b != 1) Error("语法错误", "排列运算不能计算分数");
			if (a1.a > a2.a) Error("语法错误", "排列运算时，前数不能比后数大");
			ans.a = 1;
			for (int i = a2.a; i >= a2.a - a1.a + 1; i--)
				ans.a *= i;
			return ans;
		case '#':             //组合 
			if (a1.zhengfu == 0 || a2.zhengfu == 0 || a2.a == 0) Error("语法错误", "组合运算不能计算非正数");
			if (a1.a == 0) { ans.a = 1; return ans; }
			a1 = yuefen(a1), a2 = yuefen(a2);
			if (a1.b != 1 && a2.b != 1) Error("语法错误", "组合运算不能计算分数");
			if (a1.a > a2.a) Error("语法错误", "排列运算时，前数不能比后数大");
			ans.a = 1;
			for (int i = a2.a; i >= a2.a - a1.a + 1; i--)
				ans.a *= i;
			for (int i = 1; i <= a1.a; i++) ans.b *= i;
			return ans;
		case '$':         //gcd 
			if (a1.zhengfu == 0 || a2.zhengfu == 0 || a1.a == 0 || a2.a == 0) Error("语法错误", "gcd不能计算非正数");
			a1 = yuefen(a1), a2 = yuefen(a2);
			ans.a = gcd(a1.a, a2.a);
			ans.b = lcm(a1.b, a2.b);
			ans = yuefen(ans);
			return ans;
		case '&':         //lcm 
			if (a1.zhengfu == 0 || a2.zhengfu == 0 || a1.a == 0 || a2.a == 0) Error("语法错误", "lcm不能计算非正数");
			a1 = yuefen(a1), a2 = yuefen(a2);
			ans.a = lcm(a1.a, a2.a);
			ans.b = gcd(a1.b, a2.b);
			ans = yuefen(ans);
			return ans;
		case '\\':
			if (a2.zhengfu == 0 || a2.a == 0) Error("语法错误", "取模的数必须为正数");
			if (a2.b != 1) Error("语法错误", "取模的数必须为整数");
			if (a1.b != 1) Error("语法错误", "被取模的数必须为整数");
			if (a1.zhengfu == 0)
			{
				int x = ceil(abs(a1.a) / a2.a);
				a1.a += x * a2.a;
			}
			ans.a = a1.a%a2.a;
			return ans;
		case '^':                //乘方 
			if (a1.a == 0 && a2.a == 0) Error("语法错误", "无意义的表达式");
			a2 = yuefen(a2);
			if (a2.b != 1) Error("输入错误", "指数不为整数");
			ans.a = 1;
			if (a2.zhengfu == 0)                  //指数为负 
				for (int i = 0; i < a2.a; i++)
					ans.b *= a1.a, ans.a *= a1.b;
			else
				for (int i = 0; i < a2.a; i++)
					ans.a *= a1.a, ans.b *= a1.b;
			if (a1.zhengfu == 0 && a2.a % 2 == 1) ans.zhengfu = 0;
			return ans;
		default:
			Error("输入错误", "未能被识别的运算符");
	}
}

inline number getnum(int start, int end)
{
	num = resetnum(num);
	bool point = false;               //小数点 
	bool baifen = false;              //百分号 
	bool fu = false;
	for (int i = start; i <= end; i++)
		if ((str[i] == '(' || str[i] == ')')) continue;
		else if (str[i] >= '0' && str[i] <= '9')         //数字 
		{
			num.a = num.a * 10 + str[i] - '0';
			if (point) num.b *= 10;
		}
		else if (str[i] == '.')          //小数点 
		{
			if (point) Error("语法错误", "小数点个数过多");
			point = true;
		}
		else if (str[i] == '%')          //百分号 
		{
			if (baifen) Error("语法错误", "百分号个数过多");
			baifen = true; num.b *= 100;
		}
		else if ((str[i] == '+' || str[i] == '-') && str[i - 1] == '(') { if (str[i] == '-') num.zhengfu = 0; }          //正负号 
		else break;
	num = yuefen(num);
	return num;
}

inline int judge(int start, int end)            //判断表达式类型 
{
	int sum = 0;
	for (int i = start; i <= end; i++)
	{
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '(' && str[i] != ')' && str[i] != '.' && str[i] != '%') sum++;
		if ((str[i] == '+' || str[i] == '-') && str[i - 1] == '(') sum--;
		if (sum > 1) return 2;       //2级表达式，超过1个运算符，不可直接计算 
	}
	if (sum == 1) return 1;      //1级表达式， 只有一个运算符，可直接计算 
	else return 0;        //0级表达式，没有运算符
}

inline number work(int start, int end)
{
	int type = judge(start, end);
	if (type == 0)     //0级表达式 
	{
		//直接返回 
		number a = getnum(start, end);
		return a;
	}
	else if (type == 1)      //1级表达式 
	{
		bool bo = false;
		if (str[start] == '(' && str[end] == ')') start++, end--, bo = true;
		number a1, a2, ans;
		a1 = resetnum(a1), a2 = resetnum(a2), ans = resetnum(ans);
		int i;
		char ch;    //运算符 
		a1 = getnum(start, end);     //获取第1个参数 
		for (i = start; i <= end; i++)    //寻找运算符 
			if ((!(str[i] >= '0' && str[i] <= '9') && str[i] != '(' && str[i] != ')' && str[i] != '.' && str[i] != '%') && 
				(str[i - 1] >= '0' && str[i - 1] <= '9' || str[i - 1] == ')' || str[i - 1] == '%') && i != 0)
			{
				ch = str[i];
				break;
			}
		if (i == end && ch != '!') Error("语法错误", "不完整的表达式");    //运算符在末尾 
		if (ch != '!') a2 = getnum(i + 1, end);    //获取第2个参数 
		ans = calculate(a1, a2, ch);           //计算 
		if (ans.b == 0) Error("语法错误", "除以0");     //分母为0 
		ans = yuefen(ans);
		if (bo) start--, end++;
		//显示中间过程 
		number ans2;
		ans2.zhengfu = ans.zhengfu, ans2.a = ans.a, ans2.b = ans.b;

		string s1 = (formal[0][max(0, start - 1)] == "unknown" ? str.substr(0, start) : formal[0][max(0, start - 1)]);
		string s2 = (formal[end + 1][len - 1] == "unknown" ? str.substr(end + 1, len - end) : formal[end + 1][len - 1]);
		string s3 = "";
		if (ans2.a == 0) s3 = "0";
		else
		{
			if (ans.b != 1)
			{
				while (ans2.b) s3 = char(ans2.b % 10 + '0') + s3, ans2.b /= 10;
				s3 = '/' + s3;
			}
			while (ans2.a) s3 = char(ans2.a % 10 + '0') + s3, ans2.a /= 10;
			if (ans2.zhengfu == 0) s3 = "(-" + s3 + ")";
			if (str[start] == '(' && str[end] != ')') s3 = '(' + s3;
			if (str[end] == ')' && str[start] != '(' && str[i + 1] != '(') s3 = s3 + ')';
		}
		formal[start][end] = s3;
		if (start != 0) if (str[start - 1] != '(') formal[start - 1][end] = str[start - 1] + s3;
		if (end != len) if (str[end + 1] != '%' && str[end + 1] != '!' && str[end + 1] != ')') formal[start][end + 1] = s3 + str[end + 1];
		s = s1 + s3 + s2;
		if (s != formals) cout << '=' << s << endl;
		formals = s;
		return ans;
	}
	else if (type == 2)      //2级表达式 
	{
		bool bo = false;
		if (str[start] == '(' && str[end] == ')') start++, end--, bo = true;
		char ch;
		int x;
		int now = 0;
		int minn = 0x7ffffff;
		for (int i = start; i <= end; i++)      //寻找权值最小的运算符 
		{
			if (str[i] >= '0' && str[i] <= '9') continue;
			else if (str[i] == '.' || str[i] == '%') continue;
			else if ((str[i] == '+' || str[i] == '-') && str[i - 1] == '(') continue;   //正负号 
			else if (str[i] == '(') now += Max_weight;       //括号内权值加成 
			else if (str[i] == ')') now -= Max_weight;       //括号外 
			else if (now + Weight(str[i]) <= minn) x = i, minn = now + Weight(str[i]), ch = str[i];      //重新赋值 
		}
		//分开计算 
		number a = work(start, x - 1);      //左边 
		number b = work(x + 1, end);       //右边 
		number ans = calculate(a, b, ch);       //计算 
		ans = yuefen(ans);
		//显示中间过程 
		if (bo) start--, end++;
		number ans2;
		ans2.zhengfu = ans.zhengfu, ans2.a = ans.a, ans2.b = ans.b;
		string s1 = (formal[0][max(0, start - 1)] == "unknown" ? str.substr(0, start) : formal[0][max(0, start - 1)]);
		string s2 = (formal[end + 1][len - 1] == "unknown" ? str.substr(end + 1, len - end) : formal[end + 1][len - 1]);
		string s3 = "";
		if (ans2.a == 0) s3 += '0';
		else
		{
			if (ans.b != 1)
			{
				while (ans2.b) s3 = char(ans2.b % 10 + '0') + s3, ans2.b /= 10;
				s3 = '/' + s3;
			}
			while (ans2.a) s3 = char(ans2.a % 10 + '0') + s3, ans2.a /= 10;
			if (ans2.zhengfu == 0) s3 = "(-" + s3 + ")";
		}

		formal[start][end] = s3;
		if (start != 0) if (str[start - 1] != '(') formal[start - 1][end] = str[start - 1] + s3;
		if (end != len - 1) if (str[end + 1] != '%' && str[end + 1] != '!' && str[end + 1] != ')') formal[start][end + 1] = s3 + str[end + 1];
		s = s1 + s3 + s2;
		if (s != formals) cout << '=' << s << endl;
		formals = s;
		return ans;
	}
	else Error("系统错误", "错误的类型返回值");
}

int main()
{
	Output();
	while (true)
	{
		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
				formal[i][j] = "unknown";
		ignore = false;
		len = -1;
		s = formals = str = "";
		cout << "\n输入一个表达式：\n ";
		cin >> str;
		if (str == "end")        //结束 
		{
			cout << "感谢您的使用。\n";
			cout << "如果有使用问题，请联系Calculator Dev Team：fanhy(U51229)，QuantumCheshireCat(U54591)。\n";
			return 0;
		}
		len = str.length();
		check_kuohao(0, len - 1);    //括号匹配 
		bool other = false;
		for (int i = 0; i < len; i++)
			if (str[i] == '<')         //小于号 
			{
				check_kuohao(0, i - 1);    //检查括号 
				check_kuohao(i + 1, len - 1);
				number a1 = work(0, i - 1);     //左 
				if (s != "") str = s;
				for (int j = 0; j < len; j++) if (str[j] == '<') { i = j; break; }
				len = str.length();
				number a2 = work(i + 1, len - 1);    //右 
				unsigned int s = lcm(a1.b, a2.b);    //通分 
				a1.a *= s / a1.b;
				a2.a *= s / a2.b;
				a1.b = a2.b = s;
				if (a1.zhengfu < a2.zhengfu) cout << "true.\n";         //先判断正负号 
				else if (a1.zhengfu > a2.zhengfu) cout << "false.\n";
				else   //符号相同看分子 
					if (a1.zhengfu == 0)
					{
						if (a1.a > a2.a) cout << "true.\n";
						else cout << "false.\n";
					}
					else
					{
						if (a1.a < a2.a) cout << "true.\n";
						else cout << "false.\n";
					}
				other = true; break;
			}
			else if (str[i] == '=')             //等于号 
			{
				check_kuohao(0, i - 1);
				check_kuohao(i + 1, len - 1);
				number a1 = work(0, i - 1);
				if (s != "") str = s;
				for (int j = 0; j < len; j++) if (str[j] == '<') { i = j; break; }
				len = str.length();
				number a2 = work(i + 1, len - 1);
				unsigned int s = lcm(a1.b, a2.b);
				a1.a *= s / a1.b;
				a2.a *= s / a2.b;
				a1.b = a2.b = s;
				if (a1.zhengfu != a2.zhengfu) cout << "false.\n";
				else
				{
					if (a1.a == a2.a) cout << "true.\n";
					else cout << "false.\n";
				}
				other = true; break;
			}
			else if (str[i] == '>')             //大于号 
			{
				check_kuohao(0, i - 1);
				check_kuohao(i + 1, len - 1);
				number a1 = work(0, i - 1);
				if (s != "") str = s;
				for (int j = 0; j < len; j++) if (str[j] == '<') { i = j; break; }
				len = str.length();
				number a2 = work(i + 1, len - 1);
				unsigned int s = lcm(a1.b, a2.b);
				a1.a *= s / a1.b;
				a2.a *= s / a2.b;
				a1.b = a2.b = s;
				if (a1.zhengfu > a2.zhengfu) cout << "true.\n";
				else if (a1.zhengfu < a2.zhengfu) cout << "false.\n";
				else
					if (a1.zhengfu == 0)
					{
						if (a1.a < a2.a) cout << "true.\n";
						else cout << "false.\n";
					}
					else
					{
						if (a1.a > a2.a) cout << "true.\n";
						else cout << "false.\n";
					}
				other = true; break;
			}
		if (other) continue;       //> = <运算 
		number answer = work(0, len - 1);
		if (answer.b == 0) Error("语法错误", "除以0");
		if (answer.zhengfu == 0) printf("-");
		if (answer.b != 1) printf("%.8lf\n", double(answer.a) / double(answer.b));
	}
	return 0;
}
