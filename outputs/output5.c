void ifmadness(int a)
{
	/*START OF FUNCTION*/
	int repeat;
	do
	{
	repeat = 0;
	/*DONE*/
	if (a > 5)
	{
		if (a > 10)
			{
			//TAIL RECURSION REMOVED
			int _tmp_a = a;
			a = 3;
			repeat = 1;
			}		
		else	
		{
			//TAIL RECURSION REMOVED
			int _tmp_a = a;
			a = 7;
			repeat = 1;			
		}	
	}
	else
	{
		//TAIL RECURSION REMOVED
		int _tmp_a = a;
		a = 4;
		repeat = 1;
	}
	/*END OF FUNCTION*/
	}
	while(repeat);
	/*DONE*/
}


int main(void) {
	int result = 1;
	return result;
}




