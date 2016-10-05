int fun(int a, float b, int c);

int x;
const float PI = 3.14;

int fun(int a, float b, int c)
{
	/*START OF FUNCTION*/
	int repeat;
	do
	{
	repeat = 0;
	/*DONE*/
	if (a>0)
		{
		//TAIL RECURSION REMOVED
		int _tmp_a = a;
		float _tmp_b = b;
		int _tmp_c = c;
		a = _tmp_a + 1;
		b = _tmp_b + 2.5;
		c = 3 + _tmp_c;
		repeat = 1;
		}
	else
		{
		//TAIL RECURSION REMOVED
		int _tmp_a = a;
		float _tmp_b = b;
		int _tmp_c = c;
		a = _tmp_a + 1;
		b = _tmp_a + 1;
		c = _tmp_a + 1;
		repeat = 1;
		}
	/*END OF FUNCTION*/
	}
	while(repeat);
	/*DONE*/
}
