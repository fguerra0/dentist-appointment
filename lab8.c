#include <stdio.h>
#include <string.h>

void schedule(void); // declaration of the scheduling function
void cancel(void); // declaration of the cancellation function
void list(void); // declaration of the listing function

int i; // global int variable of i for all the loops later on
char names[6][20]; // array of strings created globally
int counter = 6; // number of open appointments counter created globally
int appts[6] = {0, 0, 0, 0, 0, 0}; // array to represent open/closed appointments in the system

int main()
{
	int entry; // user's choice
	printf("Welcome to Dr. Kavorkian's Dental Office! How may we HELP you?\n");
	while(1)
	{
		printf("Enter a 1 to schedule an appointment, 2 to cancel an appointment, 3 to list the appointments for the day or any other number to exit out of the system.\n");
		scanf("%d", &entry); // choice of user has been entered
		switch (entry) 
		{
			case 1: 
			{
				schedule(); // if user chooses to schedule, the schedule function will be called
				break;
			}
			case 2:
			{
				cancel(); // if user chooses to cancel their appointment, the cancellation function will be called
				break;
			}
			case 3:
			{
				list(); // if the user chooses to list all the appointments scheduled in the system, the listing function will be called
				break;
			}
			default:
			{
				return 0; // any other number entered into the system will cause the program to exit out of the main function and quit out
				break;
			}
		}
	}
}

void
schedule(void) // schedule function's code is written here
{
	char compare[20]; // another string to make sure the user does not enter a duplicate name into the system
	if(counter == 0) // if the dentist is busy, the user will be informed
	{
		printf("Sorry, all appointments are full at this time. Please check again later.\n");
	}
	if(counter != 0)
	{
		printf("Please type in your first name: \n"); // if the dentist has room, the user will be asked to enter his or her name
		scanf("%s", compare); // user's name stored into the compare array to check first
		for(i = 0; i < 6; i++)
		{
			if(appts[i] == 0) // if an appointment is open
			{
				strcpy(names[i], compare); // the entered name will then be copied and stored into the array of strings that the system keeps for the list of appointments
				appts[i] = 1; // appointment is closed off
				printf("Thank you %s, you are scheduled for the %d to %d pm hour.\n", names[i], i + 1, i + 2);
				counter--; // one less open appointment
				break;
			}
			if(appts[i] == 1) // if an appointment is closed
			{
				if(strcmp(names[i], compare) == 0) // if the closed appointment has the same name as the entered user name, the system will let the user know they cannot enter a name twice
				{
					printf("Sorry, that name has already been used and entered into our system and we cannot accommodate your request. We apologize for any inconvenience.\n");
					break;
				}
			}
		}
	}
	return;
}

void
cancel(void) // the cancellation function's code is written here
{
	char search[20]; // array made to take user's entered name and see if it is in the system so it can be cancelled
	printf("Please enter your name to confirm your cancellation: \n");
	scanf("%s", search); // user's name stored in the search string
	for(i = 0; i < 6; i++)
	{
		if(strcmp(names[i], search) == 0 && appts[i] == 1) // determines if there is a match up between the entered name and a name saved in the system
		{
			appts[i] = 0; // closed appointment opened up
			printf("Thank you %s, your appointment has been cancelled.\n", names[i]);
			counter++; // one more open appointment
			for(; i < 5; i++)
			{
				strcpy(names[i], names[i + 1]); // takes the remaining strings in the array of strings and moves them up to fill the hole left by the cancelled appointment
				appts[i] = appts[i + 1]; // fills in the gap in the array of open/closed appointments
			}
			if(i == 5) // this special case accounts for the second to last and last names in the array of strings if they are the ones cancelled and fills up the holes left
			{
				names[i][0] = '\0';
				appts[i] = 0;
			}
			break;
		}
	}
	if(i == 6 && counter != 6) // if no name is found and there is at least one closed appointment 
	{
		printf("Sorry, could not find any corresponding appointment, please check your records again.\n");
	}
	if(i == 6 && counter == 6) // if no name is found and all appointments are open for scheduling
	{
		printf("Sorry, no appointments are currently scheduled and the day is completely open.\n");
	}
	return;
}

void
list(void) // the listing function's code is written here
{
	if(counter == 1) // if there is only one open appointment, for grammar purposes
	{
		printf("The following is the schedule list for the day for Dr. Kavorkian's appointments. There is 1 open appointment.\n");
	}
	else // if there is more than one open appointment or no open appointments 
	{
		printf("The following is the schedule list for the day for Dr. Kavorkian's appointments. There are %d open appointments.\n", counter);
	}
	if(counter == 6) // if all the appointments are open, the user is informed
	{
		printf("All slots are open for scheduling an appointment today.\n");
	}
	else // if at least one appointment is closed, the list is created for the user 
	{
		for(i = 0; i < 6; i++)
		{
			if(appts[i] == 0) // prints out all the free appointments and their time slots
			{
				printf("%d to %d pm hour client: (free)\n", i + 1, i + 2);
			}
			else if(appts[i] == 1) // prints out all the filled appointments along with their time slots and client's name
			{
				printf("%d to %d pm hour client: %s (full)\n", i + 1, i + 2, names[i]);
			}
		}
	}
	return;
}



	






































	
























 
