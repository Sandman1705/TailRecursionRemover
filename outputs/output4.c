int factorial(int input,int *answer)
{
	/*START OF FUNCTION*/
	int repeat;
	do
	{
	repeat = 0;
	/*DONE*/
	if ( input ==0 )        
	{                       
		return 0;
	}

	*answer  = *answer * input;
	//TAIL RECURSION REMOVED
	int _tmp_input = input;
	int * _tmp_answer = answer;
	input = _tmp_input - 1;
	answer = _tmp_answer;
	repeat = 1;   // nema return u ne void funkciji
	/*END OF FUNCTION*/
	}
	while(repeat);
	/*DONE*/
}
