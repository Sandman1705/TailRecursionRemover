void ifmadness(int a)
{
	if (a > 5)
	{
		if (a > 10)
			ifmadness(3);		
		else	
		{
			ifmadness(7);			
		}	
	}
	else
	{
		ifmadness(4);
	}
}


int main(void) {
	int result = 1;
	return result;
}




