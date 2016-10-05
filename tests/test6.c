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

int main()
{
	return 0;
}