void do_math(int *x) {
	*x += 5;
	*x -= 3;
}

int huio(int a, int b)
{
	/*START OF FUNCTION*/
	int repeat;
	do
	{
	repeat = 0;
	/*DONE*/
	if (a>10)
	{
		return huio(a+5,b) + 4;	
	}
	else
		return 3;
	{
	//TAIL RECURSION REMOVED
	int _tmp_a = a;
	int _tmp_b = b;
	a = _tmp_a + 1;
	b = _tmp_b + 2;
	repeat = 1;
	}
	/*END OF FUNCTION*/
	}
	while(repeat);
	/*DONE*/
}

void huio2(int a, int b)
{
	/*START OF FUNCTION*/
	int repeat;
	do
	{
	repeat = 0;
	/*DONE*/
	if (a>10)
	{
		 huio2(a+5,b);	
	}
	else
	{	
	 	a=a+3;
	}
	//TAIL RECURSION REMOVED
	int _tmp_a = a;
	int _tmp_b = b;
	a = _tmp_a;
	b = _tmp_b;
	repeat = 1;
	/*END OF FUNCTION*/
	}
	while(repeat);
	/*DONE*/
}


int main(void) {
	int result = -1, val = 4;
	do_math(&val);
	return result;
}



