#include<iostream>

using namespace std;

struct  lh_string
{
	char *s;
	int length;
};
typedef lh_string* link;

void get_next(const link p,int *next)
{
	int j = 0, i = 1;
	next[1] = 0;
	while (i < p->length - 1)
	{
		if (0 == j || p->s[i] == p->s[j])
		{
			i++; j++;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}

int KMP(link n, link p)
{
	int i = 1, m = 1,l = 1,flag = 1,flag2 = 0;
	int leng = n->length + 1;
	int *arry = new int[100];
	get_next(p, arry);
	for (int y = 0; y <10; y++)
		cout << arry[y] << endl;
	cout << "------------------" << endl;
	while (n->length != (i - p->length))
	{
		while (flag)
		{
			if (n->s[l] == p->s[m])
			{
				l++;
				m++;
				if (p->length == m - 1)
				{
					delete[] arry;
					if (flag2)
						return (i - flag2);
					//cout<< "   " << flag2<<endl;
					return i;
				}
			}
			else
			{
				flag = 0;
				flag2 = 0;
				if (m > 1)
				{
					i = i + m - 2;
					flag2 = m - arry[m];
					m = arry[m];
				}
				else
				{
					m = 1;
				}
			}
		}
		flag = 1;
		i++; 
		l = i; 
	}
	delete[] arry;
	return -1;
}


int main(void)
{
	int index;
	lh_string n, p;
	n.s = " www.";
	p.s = " ww.";
	n.length = strlen(n.s);
	p.length = strlen(p.s);
	index = KMP(&n, &p);
	cout << index << endl;
	system("pause");
}
