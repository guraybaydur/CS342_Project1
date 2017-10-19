

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "function.h"

//double

int main(int argc, char *argv[])
{
	int intL,intU,intK,intN;

  	intL = atoi (argv[1]);
  	intU = atoi (argv[2]);
  	intK = atoi (argv[3]);
  	intN = atoi (argv[4]);

  	printf ("The l value entered is %d.\n",intL);
  	printf ("The U value entered is %d.\n",intU);
  	printf ("The K value entered is %d.\n",intK);
  	printf ("The N value entered is %d.\n",intN);
	

//	pid_t parent = getpid();
	double interval = ((double)intU - (double)intL) / (double)intN ;
	printf("the interval is: %f\n", interval);

	//Create N child process
	for(int i = 1; i <= intN; i++)
	{
		pid_t child = fork();
		if(child == 0)
		{
			//call child process function 
			//giveToChild( (intL + ((double)(i-1))*(interval)),  (intL + ((double)(i))*(interval)),intK);
			
			exit(0);	
		} 
		printf("going on\n");
	}  

	return 0;
	/*
	int l = argv[]
	double y; 

	y = compute_f(10);
	printf ("%lf\n", y); 
	*/
}
