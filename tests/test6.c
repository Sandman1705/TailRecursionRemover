int fun(int a, float b, int c);

int x;
const float PI = 3.14;

int fun(int a, float b, int c)
{
	if (a>0)
		return fun(a+1,b+2.5,3+c);
	else
		return fun(a+1,a+1,a+1);
}
