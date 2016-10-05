int fact(int a, int b, int c)
{
	/*START OF FUNCTION*/
	int repeat;
	do
	{
	repeat = 0;
	/*DONE*/
	int temp = a+b;
	if (a>0)
		{
		//TAIL RECURSION REMOVED
		int _tmp_a = a;
		int _tmp_b = b;
		int _tmp_c = c;
		a = _tmp_a - 5;
		b = _tmp_b * _tmp_b;
		c = _tmp_c;
		repeat = 1;
		}
	else
	{
		a= a-4;
		return huio(a,b);  // greska: vraca void
	}
	/*END OF FUNCTION*/
	}
	while(repeat);
	/*DONE*/
}

void huio(int a, int b)
{
	/*START OF FUNCTION*/
	int repeat;
	do
	{
	repeat = 0;
	/*DONE*/
	if (b>5)
	{
		if (a>10)
			return;	
		b=b-10;
		//TAIL RECURSION REMOVED
		int _tmp_a = a;
		int _tmp_b = b;
		a = _tmp_a + 1;
		b = _tmp_b++;
		repeat = 1;
	}	
	/*END OF FUNCTION*/
	}
	while(repeat);
	/*DONE*/
}

int main(void) {
	int result = 3;
	return result;
}

