// module_2_lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
using namespace std;
int perevirka(char s[256]) {
	int l;
	if (s[0] >= '0' && s[0] <= '9') l = 1;
	if (s[0] >= 'a' && s[0] <= 'z') l = 2;
	if ((strcmp(s, "exp") == 0)) l = 7;
	if ((strcmp(s, "+") == 0)) l = 3;
	if ((strcmp(s, "-") == 0)) l = 8;
	if ((strcmp(s, "/") == 0)) l = 4;
	if ((strcmp(s, "(") == 0)) l = 5;
	if ((strcmp(s, ")") == 0)) l = 6;
	return l;
}
struct parts {
	char ryadok[256];
};
struct st {
	const int h1 = 256;
	parts* arr1 = new parts[h1];
	int i = -1;

	void push(char n[256]) {
		strcpy(arr1[++i].ryadok, n);
	}
	char* pop() {
		char* chp1 = new char[256];
		strcpy(chp1, arr1[i--].ryadok);
		return chp1;
	}
	char* top() {
		char* cht1 = new char[256];
		strcpy(cht1, arr1[i].ryadok);
		return cht1;
	}
	char size() {
		return i + 1;
	}
};
struct vr {

	const int h1 = 256;
	parts* arr2 = new parts[h1];
	int i = -1;

	void push(char n[256]) {
		strcpy(arr2[++i].ryadok, n);
	}
	char* pop() {
		char* chp = new char[256];
		strcpy(chp, arr2[i--].ryadok);
		return chp;
	}
	char* top() {
		char* cht = new char[256];
		strcpy(cht, arr2[i].ryadok);
		return cht;

	}
	char size() {
		return i + 1;
	}
};
struct my_stack {
private:
	double arr[50];
	int i = -1;
public:
	void push(double n) {
		arr[++i] = n;
	}
	double pop() {
		return arr[i--];
	}
	double top() {
		return arr[i];
	}
	double size() {
		return i + 1;
	}
};
double number(char s[256]) {
	double n;
	double m;
	n = strlen(s);
	m = 0;
	int q = 1;
	for (int i = n - 1; i >= 0; i--) {
		m = m + ((int)s[i] - '0') * q;
		q = q * 10;
	}
	return m;
}
double zapyt(char s[256]) {
	cout << "vvedit znachennya zminnoi " << s << ": ";
	double v;
	cin >> v;
	return v;
}
int main()
{
	st stack1;
	vr stack2;
	my_stack stack;
	const double e = 2.7182818284;
	const int h = 256;
	parts* A = new parts[h];
	double m;
	double m1;
	char elem[256];
	char plus[10] = { '+' };
	char minus[10] = { '-' };
	char dil[10] = { '/' };
	char dugka1[10] = { '(' };
	char dugka2[10] = { ')' };
	char expon[10] = "exp";
	char ss[256];
	cout << "vvedit vyraz: ";
	gets_s(ss);
	char word[256] = {};          //Буфер для считывания строки
	stringstream x;        //Создание потоковой переменной
	x << ss;                //Перенос строки в поток
	int o = 0;
	while (x >> word) {
		strcpy(A[o].ryadok, word);
		o = o + 1;
	}
	char t[256];
	for (int y = 0; y < o; y++) {
		int m = perevirka(A[y].ryadok);
		if (m == 1 || m == 2) { stack2.push(A[y].ryadok); }
		if (m == 7) stack1.push(A[y].ryadok);
		if (m == 5) stack1.push(A[y].ryadok);
		if (m == 6) {
			while (strcmp(stack1.top(), dugka1) != 0 && stack1.size()>0) {
				stack2.push(stack1.pop());
			}
			
			stack1.pop();
			if (strcmp(stack1.top(), expon) == 0) {

				stack2.push(stack1.pop());
			}
			
		}

		if (m == 3 || m == 8 || m == 4) {
			while (((strcmp(stack1.top(), expon) == 0)) || (strcmp(stack1.top(), dil) == 0)) {
				stack2.push(stack1.pop());
			}
			stack1.push(A[y].ryadok);
		}
	}
	while (stack2.size() > 0) {
		stack1.push(stack2.pop());
	}
	/*while (stack1.size() > 0) {
		cout << stack1.pop();
	}	*/

	char b[256];
	char c[256];
	int k;

	while (stack1.size() > 0) {
		strcpy(elem, stack1.pop());
		
		if ((strcmp(elem, plus) == 0)) {
			m1 = stack.pop();
			m = stack.pop();
			m = m + m1;
			stack.push(m);
		}
		if ((strcmp(elem, minus) == 0)) {
			m1 = stack.pop();
			m = stack.pop();
			m = m - m1;
			stack.push(m);
		}
		if ((strcmp(elem, dil) == 0)) {
			m1 = stack.pop();
			m = stack.pop();
			m = m / m1;
			stack.push(m);
		}
		if ((strcmp(elem, minus) != 0) && (strcmp(elem, dil) != 0) && (strcmp(elem, plus) != 0)) {
			if (elem[0] >= 'a' && elem[0] <= 'z') {
				if ((strcmp(elem, expon) == 0)) {
					m = stack.pop();
					m = pow(e, m);
				}
				else m = zapyt(elem);
			}
			if (elem[0] >= '0' && elem[0] <= '9') {
				m = number(elem);
			}
			stack.push(m);
		}
	}
	
	cout << stack.top();
}

