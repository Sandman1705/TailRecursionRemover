int fact(int a, int b, int c)
{
	int temp = a+b;
	if (a>0)
		return fact(a-5,b*b,c);
	else
	{
		a= a-4;
		return huio(a,b);  // greska: vraca void
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
	int result = 3;
	return result;
}

