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


int main(void) {
	int result = -1, val = 4;
	do_math(&val);
	return result;
}



