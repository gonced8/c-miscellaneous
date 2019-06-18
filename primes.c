#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h>

int list_primes (int n1, int show);
int get_prime (int option, int limit);
int count_digits(unsigned long int num);
int is_prime(unsigned long int number);


int main ( int argc, char **argv )
{
	int mode=-1;
	int arg2, arg3;
	unsigned long int number;
	
	printf("\nModes:\n");
	printf("0 - list_primes: >program <mode> <number> <1/0:show>\n");
	printf("1 - get_prime: >program <mode> <option: 0/1> <0:time|1:digits>\n");
	printf("2 - is_prime: >program <mode> <number>");
	
	if(argc>1)
	{
		sscanf(argv[1], "%d", &mode);
		
		switch (mode)
		{
			case 0:
				printf("\nlist_primes\n");
				if(argc!=4)
				{
					printf("\nInvalid input. Try again\n");
					return 1;
				}
				sscanf(argv[2], "%d", &arg2);
				sscanf(argv[3], "%d", &arg3);
				printf("\nrun\n\n");
				list_primes (arg2, arg3);
				break;
				
			case 1:
				printf("\nget_prime\n");
				if(argc!=4)
				{
					printf("\nInvalid input. Try again\n");
					return 1;
				}
				sscanf(argv[2], "%d", &arg2);
				sscanf(argv[3], "%d", &arg3);
				printf("\nrun\n\n");
				get_prime(arg2, arg3);
				break;
				
			case 2:
				printf("\nis_prime\n");
				if(argc!=3)
				{
					printf("\nInvalid input. Try again\n");
					return 1;
				}
				sscanf(argv[2], "%lu", &number);
				printf("\nrun\n\n");
				is_prime(number);
				break;
				
			default:
				printf("Mode '%d' not recognized\n", mode);
				return 1;
		}
	}
	else
	{
		printf("\n");
		scanf("%d", &mode);
		
		switch (mode)
		{
			case 0:
				printf("\nlist_primes\n");
				if( scanf("%d %d", &arg2, &arg3)==0 )
				{
					printf("\nInvalid input. Try again\n");
					return 1;
				}
				printf("\nrun\n\n");
				list_primes (arg2, arg3);
				break;
				
			case 1:
				printf("\nget_prime\n");
				if( scanf("%d %d", &arg2, &arg3)==0 )
				{
					printf("\nInvalid input. Try again\n");
					return 1;
				}
				printf("\nrun\n\n");
				get_prime(arg2, arg3);
				break;
			
			case 2:
				printf("\nis_prime\n");
				if( scanf("%lu", &number)==0 )
				{
					printf("\nInvalid input. Try again\n");
					return 1;
				}
				printf("\nrun\n\n");
				is_prime(number);
				break;
				
			default:
				printf("\nInvalid input. Try again\n");
				return 1;
		}
	}
	
	getchar();
	
	return 0;
}

	
int list_primes (int n1, int show)
{
	int t, count=0;
	clock_t tic, toc;
	
	unsigned long int  i, j, n3;
	/*
	int i, j;
	*/
	
	tic = clock();
	
	/* Separated with if to maximize speed due to 'show' parameter evaluation */
	if(show)
	{
		for(i=2; i<=n1; i=i+1)
		{
			t=0;
			
			n3=(unsigned long int)(sqrt(i));
			
			
			for(j=2; j<=n3; j=j+1)
			{
				if(i%j==0)
				{
					t=1;
					break;
				}
			}
			
			if(!t)
			{
				count=count+1;
				if (show)
					printf("%lu \n", i);
				/*
				getchar();
				*/
			}
		}
	}
	else
	{
		for(i=2; i<=n1; i=i+1)
		{
			t=0;
			
			n3=(unsigned long int)(sqrt(i));
			
			
			for(j=2; j<=n3; j=j+1)
			{
				if(i%j==0)
				{
					t=1;
					break;
				}
			}
			
			if(!t)
			{
				count=count+1;
				/*
				getchar();
				*/
			}
		}
	}
	
	toc = clock();
	
	printf("number of primes\t%d\n", count);
	printf("time\t%f\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	return 0;
}


int get_prime (int option, int limit)
{
	mpz_t integ, lim, ver, stop;
	mpz_init (integ);
	mpz_init (lim);
	mpz_init (ver);
	mpz_init (stop);
	
	char *res = NULL;
	
	int t;
	clock_t tic, toc;
	int check;
	double elapsed_time;
	
	unsigned long int i, j, n3, number;
	
	getchar();
	
	tic = clock();
	
	if(option==0)
	{
		check=100000*limit;
		
		for(i=2; ; i=i+1)
		{		
			t=0;
			
			n3=(unsigned long int)(sqrt(i));
			
			for(j=2; j<=n3; j=j+1)
			{
				if(i%j==0)
				{
					t=1;
					break;
				}
			}
			
			if(!t)
			{			
				number = i;
			}
			
			if(i%check==0)
			{	
				toc=clock();
				elapsed_time= (double)(toc - tic) / CLOCKS_PER_SEC;
				
				if(elapsed_time>=limit)
				{
					printf("time: %f\nprime: %lu\n", elapsed_time, number);
					return number;
				}
			}
		}
	}
	else if(option==1)
	{	
		if(limit>1)
		{
			i=1;
			mpz_set_ui (integ, 1);
			for(j=1; j<limit; j=j+1)
			{
				i=i*10;
				mpz_mul_ui (integ, integ, 10);
			}
		}
		else
		{
			i=2;
			mpz_set_ui (integ, 2);
		}
		
		printf("When done, press q to exit\n\n");
		
		for(; ; mpz_add_ui (integ, integ, 1))
		{	
			t=0;
			
			mpz_sqrt (lim, integ);
			n3=(unsigned long int)(sqrt(i));
			
			for(mpz_set_ui (ver, 2); mpz_cmp (ver, lim)<=0; mpz_add_ui (ver, ver, 1))
			{
				mpz_mod (stop, integ, ver);
				
				if(mpz_cmp_ui (stop, 0)==0)
				{
					t=1;
					break;
				}
			}
			
			if(!t)
			{	
				res=mpz_get_str (res, 10, integ);
				number = i;
				
				toc=clock();
				elapsed_time= (double)(toc - tic) / CLOCKS_PER_SEC;
				printf("\ntime: %f\nprime: %s\n", elapsed_time, res);
				if(getchar()=='q')
					goto end;
				tic = clock();				
			}
		}
	}
	
	end:
	mpz_clear (integ);
	mpz_clear (lim);
	mpz_clear (ver);
	mpz_clear (stop);
	
	return 0;
}


int count_digits(unsigned long int num)
{
	if ( num < 10 )
		return 1;
	if ( num < 100 )
		return 2;
	if ( num < 1000 )
		return 3;
	if ( num < 10000 )
		return 4;
	if ( num < 100000 )
		return 5;
	if ( num < 1000000 )
		return 6;
	if ( num < 10000000 )
		return 7;
	if ( num < 100000000 )
		return 8;
	if ( num < 1000000000 )
		return 9;
	/*
	if ( num < 10000000000 )
		return 10;
	if ( num < 100000000000 )
		return 11;
	if ( num < 1000000000000 )
		return 12;
	*/
	else
		return 0;
}


int is_prime(unsigned long int number)
{
	int t;
	unsigned long int n3, j;
	clock_t tic, toc;
	
	tic=clock();
	
	t=0;
	
	n3=(unsigned long int)(sqrt(number));
	
	for(j=2; j<=n3; j=j+1)
	{
		if(number%j==0)
		{
			t=1;
			break;
		}
	}
	
	toc=clock();
	
	printf("time\t%f\n", (double)(toc - tic) / CLOCKS_PER_SEC);
	
	if(!t)
		printf("%lu\tis prime\n", number);
    else
        printf("%lu\tis NOT prime\n", number);
	
	return 0;
}