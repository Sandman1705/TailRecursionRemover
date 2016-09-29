void do_math(int *x) {
	*x += 5;
}

int fact(int a, int b, int c)
{
	int temp = a+b;
	if (a>0)
		return fact(a-5,b*b,c);
	else
	{
		a= a-4;
		return 4+a*b;
	}
}

void huio(int a, int b)
{
	if (b>5)
	{
		if (a>10)
			return;	
		b=b-10;
		huio(a+1,b++);
	}	
}

int main(void) {
	int result = -1, val = 4;
	do_math(&val);
	int a;
	a=3;
	a=a+2;
	foo(a,4,a+6);
	return result;
}

