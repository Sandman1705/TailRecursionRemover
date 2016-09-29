void do_math(int *x) {
	*x += 5;
	*x -= 3;
}

int huio(int a, int b)
{
	if (a>10)
	{
		return huio(a+5,b) + 4;	
	}
	else
		return 3;
	return huio(a+1,b+2);
}

int main(void) {
	int result = -1, val = 4;
	do_math(&val);
	int a;
	a=3;
	a=a+2;
	huio(a+5,a);
	return result;
}

void huio2(int a, int b)
{
	if (a>10)
	{
		 huio2(a+5,b);	
	}
	else
	{	
	 	a=a+3;
	}
	huio2(a,b);
}

void ifmadness(int a)
{
	if (a > 5)
	{
		if (a > 10)
		{
			if(a)
				ifmadness(2);
			ifmadness(3);		
		}		
		else	
			ifmadness(7);			
	}
	else
	{
		ifmadness(4);
	}
}


