#include<bits/stdc++.h>
using namespace std;

bool ignore;      //���Դ��� 
const int Max_weight = 5;               //����Ȩ�� 
unsigned int len;
string formals, s;
string formal[100][100];

struct number               //������ 
{
	unsigned int a, b;    //a���ӣ�b��ĸ 
	bool zhengfu;
}num;
string str;                //���ʽ 

inline void Output()                     //�����ܽ��� 
{
	cout << "������Ա��fanhy(Luogu U51229)��QuantumCheshireCat(Luogu U54591)��\n\n";
	cout << "���������ڼ��㲻����ĸ�ı��ʽ��\n";
	cout << "�ݲ�֧��ָ����Ϊ���������㡣\n";
	cout << "�ݲ�֧�ָ��ຯ����\n";
	cout << "�ݲ�֧��λ���㡣\n";
	cout << "�ݲ�֧��10������������㡣\n";
	cout << "�뱣֤�������ݼ������е����ݡ�({-2^31,2^31-1} �� Q)�������� int ��Χ�ڵ���������\n";
	cout << "�ݲ�֧�ִ��������롣\n";
	cout << "֧�ְٷֺ� % ��\n";
	cout << "% ����Ϊ�� �ٷֺţ�������Ϊ��ȡģ���š�\n";
	cout << "ȡģ������ʹ��a\\b��ʾa%b��\n";
	cout << "�׳�����ֻ�ܼ���Ǹ�������\n";
	cout << "�����������ֻ�ܼ�����������\n";
	cout << "����a@b��ʾA(a,b)��P(a,b)����a#b��ʾC(a,b)��\n";
	cout << "����a$b��ʾgcd(a,b)����a&b��ʾlcm(a,b)��\n";
	cout << "gcd��lcm�����ֻ�ܼ�����������\n";
	cout << "��ʾ������Ҫ������$��&���߼����ţ���Ϊ$ &�����ȼ��ϸߡ�\n";
	cout << "֧��> < = ���㣬��� true �� false ��\n";
	cout << "ע�⣺����֤���ݷ�Χ��������ʱ�ᱨ��\n";
	cout << "�벻Ҫ�ڱ��ʽ����ӿո�\n";
	cout << "����Ӣ�����뷨���룬����end��������\n";
	cout << "\n";
	cout << "���������������߼����š�\n";
}

inline void Error(string s1, string s2)                      //������ʾ  s1���������ͣ�s2������ԭ�� 
{
	if (ignore) return;
	char ch;
	cout << "����:\n-----------------------\n";
	cout << s1 << endl;
	cout << "����ԭ��" << s2 << endl;
	if (s1 == "ϵͳ����") { cout << "�뽫�����ⱨ�濪���Ŷӣ����ǻᾡ����������⡣\n"; exit(0); }                     //������ʾ 
	if (s1 != "ϵͳ����") cout << "���û�д������뿪���Ŷӷ��������ǻᾡ����������⡣\n";                     //������ʾ 
	cout << "��ȷ��Ҫ��������������ܵ��´���Ľ�������ص�ϵͳ����Y/N�����������д�������A��:";
	cin >> ch;
	if (ch == 'Y') return;
	if (ch == 'A') { ignore = true; return; }
	else exit(0);                   //�������� 
}

void check_kuohao(unsigned int a, unsigned int b)
{
	int sum = 0;
	for (int i = a; i <= b; i++)
	{
		if (str[i] == '(') sum++;          //�����ż� 
		else if (str[i] == ')') sum--;         //�����ż� 
		if (sum < 0) Error("�������", "���ʽ���Ų�ƥ��");       //�����ű������Ŷ� 
	}
	if (sum != 0) Error("�������", "���ʽ���Ų�ƥ��");      //���Ų�ƥ�� 
	return;
}

inline number resetnum(number a)                  //����number�� 
{
	a.a = 0;
	a.b = 1;
	a.zhengfu = 1;
	return a;
}

inline unsigned int Weight(char ch)                   //������������ȼ� 
{
	if (ch == '+' || ch == '-') return 1;
	else if (ch == '*' || ch == '/') return 2;
	else if (ch == '!' || ch == '@' || ch == '#' || ch == '$' || ch == '&' || ch == '\\') return 3;                   //�׳ˡ�������ϡ�gcd��lcm��ȡģ
	else if (ch == '^') return 4;                   //�˷� 
	else Error("�������", "δ�ܱ�ʶ����ַ�");                    //������֧�ֵ������ 
}

inline unsigned int gcd(unsigned int a, unsigned int b)                 //���Լ�� 
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

inline unsigned int lcm(unsigned int a, unsigned int b)                 //��С������ 
{
	return a * b / gcd(a, b);
}

inline number yuefen(number x)                  //Լ�� 
{
	if (x.a == 0) { x.b = 1; return x; }
	int s = gcd(x.a, x.b);
	x.a /= s, x.b /= s;                 //������󹫱���     
	return x;
}

inline number calculate(number a1, number a2, char ch)               //����1�����ʽ 
{
	number ans;  ans = resetnum(ans);                 //��� 
	unsigned int s;
	if ((ch == '+' || ch == '-') && a1.b != a2.b)                    //ͨ�� 
	{
		s = lcm(a1.b, a2.b);
		a1.a *= s / a1.b;
		a2.a *= s / a2.b;
	}
	else if ((ch == '+' || ch == '-') && a1.b == a2.b) s = a1.b;
	switch (ch)
	{
		case '+':                 //�ӷ� 
			if (a1.zhengfu != a2.zhengfu)                   //���Ų�ͬ 
			{
				if (a1.a >= a2.a) ans.zhengfu = a1.zhengfu, ans.a = a1.a - a2.a;
				else ans.zhengfu = a2.zhengfu, ans.a = a2.a - a1.a;
			}
			else ans.a = a1.a + a2.a;                   //������ͬ 
			ans.b = s;
			return ans;
		case '-':                //����  
			//�������۷��ŵ�4�����
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
		case '*':                  //�˷� 
			if (a1.zhengfu != a2.zhengfu) ans.zhengfu = 0;                   //������ 
			else ans.zhengfu = 1;
			ans.a = a1.a*a2.a;
			ans.b = a1.b*a2.b;
			return ans;
		case '/':                 //���� 
			if (a1.zhengfu != a2.zhengfu) ans.zhengfu = 0;
			else ans.zhengfu = 1;
			ans.a = a1.a*a2.b;
			ans.b = a1.b*a2.a;
			return ans;
		case '!':                 //�׳� 
			if (a1.zhengfu == 0) Error("�﷨����", "�޷����㸺���Ľ׳�");
			a1 = yuefen(a1);
			if (a1.a == 0) return ans;
			if (a1.b != 1) Error("�﷨����", "�޷�����������Ľ׳�");
			ans.a = 1;
			for (int i = a1.a; i >= 1; i--) ans.a *= i;
			return ans;
		case '@':              //���� 
			if (a1.zhengfu == 0 || a2.zhengfu == 0 || a2.a == 0) Error("�﷨����", "�������㲻�ܼ��������");
			if (a1.a == 0) { ans.a = 1; return ans; }
			a1 = yuefen(a1), a2 = yuefen(a2);
			if (a1.b != 1 && a2.b != 1) Error("�﷨����", "�������㲻�ܼ������");
			if (a1.a > a2.a) Error("�﷨����", "��������ʱ��ǰ�����ܱȺ�����");
			ans.a = 1;
			for (int i = a2.a; i >= a2.a - a1.a + 1; i--)
				ans.a *= i;
			return ans;
		case '#':             //��� 
			if (a1.zhengfu == 0 || a2.zhengfu == 0 || a2.a == 0) Error("�﷨����", "������㲻�ܼ��������");
			if (a1.a == 0) { ans.a = 1; return ans; }
			a1 = yuefen(a1), a2 = yuefen(a2);
			if (a1.b != 1 && a2.b != 1) Error("�﷨����", "������㲻�ܼ������");
			if (a1.a > a2.a) Error("�﷨����", "��������ʱ��ǰ�����ܱȺ�����");
			ans.a = 1;
			for (int i = a2.a; i >= a2.a - a1.a + 1; i--)
				ans.a *= i;
			for (int i = 1; i <= a1.a; i++) ans.b *= i;
			return ans;
		case '$':         //gcd 
			if (a1.zhengfu == 0 || a2.zhengfu == 0 || a1.a == 0 || a2.a == 0) Error("�﷨����", "gcd���ܼ��������");
			a1 = yuefen(a1), a2 = yuefen(a2);
			ans.a = gcd(a1.a, a2.a);
			ans.b = lcm(a1.b, a2.b);
			ans = yuefen(ans);
			return ans;
		case '&':         //lcm 
			if (a1.zhengfu == 0 || a2.zhengfu == 0 || a1.a == 0 || a2.a == 0) Error("�﷨����", "lcm���ܼ��������");
			a1 = yuefen(a1), a2 = yuefen(a2);
			ans.a = lcm(a1.a, a2.a);
			ans.b = gcd(a1.b, a2.b);
			ans = yuefen(ans);
			return ans;
		case '\\':
			if (a2.zhengfu == 0 || a2.a == 0) Error("�﷨����", "ȡģ��������Ϊ����");
			if (a2.b != 1) Error("�﷨����", "ȡģ��������Ϊ����");
			if (a1.b != 1) Error("�﷨����", "��ȡģ��������Ϊ����");
			if (a1.zhengfu == 0)
			{
				int x = ceil(abs(a1.a) / a2.a);
				a1.a += x * a2.a;
			}
			ans.a = a1.a%a2.a;
			return ans;
		case '^':                //�˷� 
			if (a1.a == 0 && a2.a == 0) Error("�﷨����", "������ı��ʽ");
			a2 = yuefen(a2);
			if (a2.b != 1) Error("�������", "ָ����Ϊ����");
			ans.a = 1;
			if (a2.zhengfu == 0)                  //ָ��Ϊ�� 
				for (int i = 0; i < a2.a; i++)
					ans.b *= a1.a, ans.a *= a1.b;
			else
				for (int i = 0; i < a2.a; i++)
					ans.a *= a1.a, ans.b *= a1.b;
			if (a1.zhengfu == 0 && a2.a % 2 == 1) ans.zhengfu = 0;
			return ans;
		default:
			Error("�������", "δ�ܱ�ʶ��������");
	}
}

inline number getnum(int start, int end)
{
	num = resetnum(num);
	bool point = false;               //С���� 
	bool baifen = false;              //�ٷֺ� 
	bool fu = false;
	for (int i = start; i <= end; i++)
		if ((str[i] == '(' || str[i] == ')')) continue;
		else if (str[i] >= '0' && str[i] <= '9')         //���� 
		{
			num.a = num.a * 10 + str[i] - '0';
			if (point) num.b *= 10;
		}
		else if (str[i] == '.')          //С���� 
		{
			if (point) Error("�﷨����", "С�����������");
			point = true;
		}
		else if (str[i] == '%')          //�ٷֺ� 
		{
			if (baifen) Error("�﷨����", "�ٷֺŸ�������");
			baifen = true; num.b *= 100;
		}
		else if ((str[i] == '+' || str[i] == '-') && str[i - 1] == '(') { if (str[i] == '-') num.zhengfu = 0; }          //������ 
		else break;
	num = yuefen(num);
	return num;
}

inline int judge(int start, int end)            //�жϱ��ʽ���� 
{
	int sum = 0;
	for (int i = start; i <= end; i++)
	{
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '(' && str[i] != ')' && str[i] != '.' && str[i] != '%') sum++;
		if ((str[i] == '+' || str[i] == '-') && str[i - 1] == '(') sum--;
		if (sum > 1) return 2;       //2�����ʽ������1�������������ֱ�Ӽ��� 
	}
	if (sum == 1) return 1;      //1�����ʽ�� ֻ��һ�����������ֱ�Ӽ��� 
	else return 0;        //0�����ʽ��û�������
}

inline number work(int start, int end)
{
	int type = judge(start, end);
	if (type == 0)     //0�����ʽ 
	{
		//ֱ�ӷ��� 
		number a = getnum(start, end);
		return a;
	}
	else if (type == 1)      //1�����ʽ 
	{
		bool bo = false;
		if (str[start] == '(' && str[end] == ')') start++, end--, bo = true;
		number a1, a2, ans;
		a1 = resetnum(a1), a2 = resetnum(a2), ans = resetnum(ans);
		int i;
		char ch;    //����� 
		a1 = getnum(start, end);     //��ȡ��1������ 
		for (i = start; i <= end; i++)    //Ѱ������� 
			if ((!(str[i] >= '0' && str[i] <= '9') && str[i] != '(' && str[i] != ')' && str[i] != '.' && str[i] != '%') && 
				(str[i - 1] >= '0' && str[i - 1] <= '9' || str[i - 1] == ')' || str[i - 1] == '%') && i != 0)
			{
				ch = str[i];
				break;
			}
		if (i == end && ch != '!') Error("�﷨����", "�������ı��ʽ");    //�������ĩβ 
		if (ch != '!') a2 = getnum(i + 1, end);    //��ȡ��2������ 
		ans = calculate(a1, a2, ch);           //���� 
		if (ans.b == 0) Error("�﷨����", "����0");     //��ĸΪ0 
		ans = yuefen(ans);
		if (bo) start--, end++;
		//��ʾ�м���� 
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
	else if (type == 2)      //2�����ʽ 
	{
		bool bo = false;
		if (str[start] == '(' && str[end] == ')') start++, end--, bo = true;
		char ch;
		int x;
		int now = 0;
		int minn = 0x7ffffff;
		for (int i = start; i <= end; i++)      //Ѱ��Ȩֵ��С������� 
		{
			if (str[i] >= '0' && str[i] <= '9') continue;
			else if (str[i] == '.' || str[i] == '%') continue;
			else if ((str[i] == '+' || str[i] == '-') && str[i - 1] == '(') continue;   //������ 
			else if (str[i] == '(') now += Max_weight;       //������Ȩֵ�ӳ� 
			else if (str[i] == ')') now -= Max_weight;       //������ 
			else if (now + Weight(str[i]) <= minn) x = i, minn = now + Weight(str[i]), ch = str[i];      //���¸�ֵ 
		}
		//�ֿ����� 
		number a = work(start, x - 1);      //��� 
		number b = work(x + 1, end);       //�ұ� 
		number ans = calculate(a, b, ch);       //���� 
		ans = yuefen(ans);
		//��ʾ�м���� 
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
	else Error("ϵͳ����", "��������ͷ���ֵ");
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
		cout << "\n����һ�����ʽ��\n ";
		cin >> str;
		if (str == "end")        //���� 
		{
			cout << "��л����ʹ�á�\n";
			cout << "�����ʹ�����⣬����ϵCalculator Dev Team��fanhy(U51229)��QuantumCheshireCat(U54591)��\n";
			return 0;
		}
		len = str.length();
		check_kuohao(0, len - 1);    //����ƥ�� 
		bool other = false;
		for (int i = 0; i < len; i++)
			if (str[i] == '<')         //С�ں� 
			{
				check_kuohao(0, i - 1);    //������� 
				check_kuohao(i + 1, len - 1);
				number a1 = work(0, i - 1);     //�� 
				if (s != "") str = s;
				for (int j = 0; j < len; j++) if (str[j] == '<') { i = j; break; }
				len = str.length();
				number a2 = work(i + 1, len - 1);    //�� 
				unsigned int s = lcm(a1.b, a2.b);    //ͨ�� 
				a1.a *= s / a1.b;
				a2.a *= s / a2.b;
				a1.b = a2.b = s;
				if (a1.zhengfu < a2.zhengfu) cout << "true.\n";         //���ж������� 
				else if (a1.zhengfu > a2.zhengfu) cout << "false.\n";
				else   //������ͬ������ 
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
			else if (str[i] == '=')             //���ں� 
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
			else if (str[i] == '>')             //���ں� 
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
		if (other) continue;       //> = <���� 
		number answer = work(0, len - 1);
		if (answer.b == 0) Error("�﷨����", "����0");
		if (answer.zhengfu == 0) printf("-");
		if (answer.b != 1) printf("%.8lf\n", double(answer.a) / double(answer.b));
	}
	return 0;
}
