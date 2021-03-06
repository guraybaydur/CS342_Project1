#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "function.h"
	


double giveToChild(double v,double subInterval , int k)
{
	//double subInterval = (v - u) / ( (double)k ); 
	double resultOfChild = 0.0;
	
	for(int j = 1; j <= k;j++)
	{
		resultOfChild = subInterval * ((compute_f(v + (j - 1) * subInterval) + compute_f(v + j * subInterval))) / 2;
	}

	return resultOfChild;			
}

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
  	printf ("The N value entered is %d.\n\n",intN);
	

	pid_t parentId = getpid();
	printf("parentId: %ld\n", (long)parentId);	

	double interval = ((double)intU - (double)intL) / (double)intN ;
	printf("the interval is: %f\n\n", interval);
	
	double overallCalculation = 0.0;

	//initialize a filedescription pointer
	int fileDes[intN][2];

	//Create N child process
	for(int i = 1; i <= intN; i++)
	{
		printf("going on i:  %d\n\n",i);

		

		if(pipe(fileDes[i-1])== -1)
		{
			printf("pipe creation failed\n");
		}
		else 
		{
			printf("pipe creation successful\n");
		}

		pid_t child = fork();
		
		if(child == 0)//if child is created
		{
			double childsResult = 0.0;

			printf("Child Created\n");
			
			//closing read end
			if(close(fileDes[i-1][0]) == 0)
			{	
				printf("Read end of child closed\n\n");
			}
			else{printf("error while closing the child\n\n");}
			
			//compute the subinterval specific for child
			double subInterval = ((intL + ((double)(i))*(interval)) - (intL + ((double)(i-1))*(interval))) / (double) intK ;						   printf("subInterval is : %f \n\n", subInterval);			
			
			//call child process function 
			childsResult = giveToChild( (intL + ((double)(i-1))*(interval)), subInterval ,intK);
			printf("result of child %d is: %f\n", i ,childsResult);
			int res = write(fileDes[i-1][1],&childsResult,sizeof(childsResult));

			//write(send) the child's result to parent
			if(res == -1)
			{
				printf("write operation failed \n");
			}
			else{printf("successfully written!!! Num of bytes: %d\n",res );}
			
			exit(0);	
		}
		else if(child < 0)
		{
			printf("Child creation failed\n");
			exit(-1);
		}
		else //if no error exists and in parent
		{
			//close(fileDes[1]);
			

			//Close write end
			for(int p = 1; p < intN; p++)
			{
				double y = 0.0;
				double *x = &y;
				
				int child = 0;
			//	int *childId = &child;	
				
				int finishedpid = waitpid(child,NULL, 0);
				
				//long chId = (long)childId;
				printf("terminated child: %d\n", finishedpid) ;
				
				//int cId = (int)chId;
				int index = finishedpid - parentId-1;
				printf("index is: %d\n", index);				

	
				read(fileDes[index][0],x, sizeof(double));
				printf("x: %f\n", *x);
				close(fileDes[index][1]);
				overallCalculation = overallCalculation + *x;	
			}
			
			printf("Overall Calculation: %f\n\n", overallCalculation);			
		}
	}  

	return 0;
	/*
	int l = argv[]
	double y; 

	y = compute_f(10);
	printf ("%lf\n", y); 
	*/
}
