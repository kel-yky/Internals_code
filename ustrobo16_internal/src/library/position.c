/*
	int position_value(unsigned int readings, int size)
	{
		int sum = 0 ;
		int count = 0;
		int max = 2*size -1;
		for (int shift = 0; shift < size; shift++)
		{
			if (((readings>>shift) & 1)==1 )
			{
				sum = sum + max - (2*shift);
				count++;
			}
		}
		if ( count == 0 )
		{	return size; }
		else
		{	return(sum/count);	} //removed count
	}

int posOutput(){

	int a = 255;
	char b= 0b01101100;
	char *pb = &b;
	printf("b = %c\n", b);
	char c = b>>1;
	printf("shifted b = %d\n", c);
	unsigned int d = 1205578798;
	printf("d = %d\n", d);
	unsigned int e = d>>4;
	printf("shifted d = %d\n", e);
	if ((e&1) == 1)
	{
		printf("4th bit is 1\n");
		printf("%d", (e&1));
	}
	else
	{
		printf("4th bit is 0\n");
	}
	int n = -1*c;
	printf("%d\n", n);
	printf("Testing b= 108\n");
	int pos = position_value(b,8);
	printf("%d\n",pos);

	for (int try = 0; try <20; try++)
	{
		unsigned int b8 = try;
		int posoct = position_value(b8,8);
		printf("%d\n",posoct);
	}

	unsigned int b16= 4092;
	int pos2 = position_value(b16,16);
	printf("%d\n",pos2);

	unsigned int b16L= 51846;
	int pos3 = position_value(b16L,16);
	printf("%d\n",pos3);
	return 0;
}
*/