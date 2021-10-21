#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//all of my Global Varibales and Dynamic Arrays need
int *resource = NULL;
int *avail = NULL;
int *allocated = NULL;
int *max = NULL;
int *need = NULL;

int num_of_resource;
int num_of_process;

void p_resouces(){
	printf("\nResources: \n");
	for(int i = 0; i<num_of_resource; i++){
		printf("\tr%d",i);
	}
	printf("\n");
	for(int i = 0; i<num_of_resource; i++){
		printf("\t%d", resource[i]);
	}
	printf("\n");
}

void p_available(){
	printf("\nAvailable: \n");
	for(int i = 0; i<num_of_resource; i++){
		printf("\tr%d",i);
	}
	printf("\n");
	for(int i = 0; i<num_of_resource; i++){
		printf("\t%d", avail[i]);
	}
	printf("\n");
}

void p_max(){
	printf("\nMax claim: \n");
	for(int i = 0; i<num_of_resource; i++){
		printf("\tr%d",i);
	}
	printf("\n");
	for(int i = 0; i<num_of_process; i++){
		printf("\np%d\t", i);
		for(int j = 0; j < num_of_resource; j++){
			printf("%d\t",max[i * num_of_resource + j]);
		}
	}
}

void p_allocated(){
	printf("\n\nAllocated: \n");
	for(int i = 0; i<num_of_resource; i++){
		printf("\tr%d",i);
	}
	for(int i = 0; i< num_of_process; i++){
		printf("\np%d\t", i);
		for(int j = 0; j < num_of_resource; j++){
			printf("%d\t",allocated[i * num_of_resource + j]);
		}
	}
}

void p_need(){
	printf("\n\nNeed: \n");
	for(int i = 0; i<num_of_resource; i++){
		printf("\tr%d",i);
	}
	for(int i = 0; i<num_of_process; i++){
		printf("\np%d\t", i);
		for(int j = 0; j < num_of_resource; j++){
			printf("%d\t",need[i * num_of_resource + j]);
		}
	}
	printf("\n");
}

void user_select_choice_no_1(){
	printf("Enter the Number of Processes: ");
	scanf("%d",&num_of_process);
	printf("Enter the Number of Resources: ");
    scanf("%d",&num_of_resource);

    //memory allocation for all of my arrays and vectors
	resource = (int *)malloc(num_of_resource * sizeof(int));
	avail = (int *)malloc(num_of_resource * sizeof(int));
	max = (int *)malloc(num_of_process * num_of_resource * sizeof(int));
	allocated = (int *)malloc(num_of_process * num_of_resource * sizeof(int));
	need = (int *)malloc(num_of_process * num_of_resource * sizeof(int));
	
	int unit_of_resources;
	printf("Enter number of units for resources (r%d to r%d): ", 0, num_of_resource - 1);
	for (int i = 0; i < num_of_resource; i++){
		scanf("%d", &unit_of_resources);
		resource[i] = unit_of_resources;
		avail[i] = unit_of_resources;
	}
	
	for(int i = 0; i < num_of_process; i++){
		printf("Enter maximum number of units process p%d will request from each resource (r%d to r%d): ", i, 0, num_of_resource - 1);
		for(int j = 0; j < num_of_resource; j++){
			scanf("%d",&unit_of_resources);
			max[i * num_of_resource + j] = unit_of_resources;
			need[i * num_of_resource + j] = unit_of_resources;
		}
	}
	
	for(int i = 0; i < num_of_process; i++){
		printf("Enter number of units of each resource (r%d to r%d) allocated to process p%d: ", 0, num_of_resource - 1, i);
		for(int j = 0; j < num_of_resource; j++){
			scanf("%d",&unit_of_resources);
			allocated[i * num_of_resource + j] = unit_of_resources;
			need[i * num_of_resource + j] -= unit_of_resources;
			avail[j] -=unit_of_resources;
		}
	}
	
	p_resouces();
	p_available();
	p_max();
	p_allocated();
	p_need();
	printf("\n");	
}

void user_select_choice_no_2(){
	int no_of_sequence = 0;
	int is_less_than;
	
	//create vector and allocate memory
	int *sequence = (int *) calloc(num_of_process, sizeof(int));
	while (no_of_sequence < num_of_process){
		for(int i = 0; i < num_of_process; i++){
			is_less_than = 1;
			if (sequence[i]==0){
				printf("Checking: < ");
				for (int j = 0; j < num_of_resource; j++){
					printf(" %d", need[i * num_of_resource + j]);	
			     }
				printf(" > <= <");
				for (int j = 0; j < num_of_resource; j++){
					printf(" %d", avail[j]);
				}
				printf(" > ");
				for (int j = 0; j < num_of_resource; j++){
					is_less_than &= (need[i * num_of_resource + j] <= avail[j]);
				}
				if (is_less_than == 1){
					printf(" :p%d safetly sequenced",i);
					sequence[i] = 1;
					no_of_sequence++;
					for(int j = 0; j < num_of_resource; j++){
						avail[j] += allocated[i * num_of_resource + j];
						allocated[i * num_of_resource + j]= 0;
						need[i * num_of_resource + j] = max[i * num_of_resource + j];
						
					}
			   }
			   printf("\n");		
		 }
	 }
	
  }
  printf("\n");
  free(sequence);	
}

void user_select_choice_no_3(){
	if(max != NULL)
		free(max);
}
	
void displayChoiceList(){
	printf("Banker's Algorithm\n");
	printf("------------------\n");
	printf("1)Enter parameters\n");
	printf("2)Determine safe sequence\n");
	printf("3)Quit program\n");
	
}
void main()
 {
    int mychoice;
	do {
		 displayChoiceList();
		 printf("\nEnter selection: ");
		 scanf("%d", &mychoice);
		 switch (mychoice) {
			 case 1:
			   user_select_choice_no_1();
			   break;
			 case 2:
			   user_select_choice_no_2();
			   break;
			 case 3:
			   printf("Quitting program...\n");
			   user_select_choice_no_3();
			   break;
			 default:
			     printf("\nWrong Selection !!!\n\n");
		  }
	}while (mychoice !=3);
 }