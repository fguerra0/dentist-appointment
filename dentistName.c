#include <stdio.h>
#include <string.h>

int main()
{
	int i; // initializing the variables
	int temp;
	char names[6][20]; // creating an empty array of strings
	int counter = 6; // number of appointments open
	int entry;
	int emptyCounter;
	int appts[6]; // array to tell if appointment is open or not
	char search[20]; // array used to find the entered name in the array of strings
	for(i = 0; i < 6; i++) // start with all open appointments
	{
		appts[i] = 0;
	}
	printf("Welcome to Dr. Kavorkian's Dental Office! How may we HELP you?\n");
	while(1)
	{
		printf("Enter a 1 to schedule an appointment, 2 to cancel an appointment, 3 to list the appointments or any other number to exit out of the system.\n");
		scanf("%d", &entry); // what the user's choice is
		switch (entry)
		{
			case 1: // if they choose 1 to schedule an appointment
			{
				if(counter != 0) // open appointments
				{
					printf("Please type in your first name: \n");
					for(i = 0; i < 6; i++) // going through and seeing which is the earliest open appointment and giving that to the user
					{
						if(appts[i] == 0)
						{
							scanf("%s", names[i]); // name entered into array of strings
							appts[i] = 1; // appointment now closed
							printf("Thank you %s, you are scheduled for the %d to %d pm hour.\n", names[i], i + 1, i + 2);
							counter--; // one less open appointment
							break;
						}
					}
				}
				if(i == 6 && counter == 0) // dentist is busy and has no open slots for an appointment
				{
					printf("Sorry, all appointments are full at this time. Please check again later.\n");
				}
				break;
			}
			case 2: // if they choose 2 to cancel an appointment
			{
				printf("Please enter your name to confirm your cancellation: \n");
				scanf("%s", search); // takes name from user and stores into another string
				for(i = 0; i < 6; i++)
				{
					if(strcmp(names[i], search) == 0 && appts[i] == 1) // going through the array of strings and checking if the newly entered string name matches any names currently in the array of strings
					{
						appts[i] = 0; // appointment now open
						printf("Thank you %s, your appointment has been cancelled.\n", names[i]);
						counter++; // one more appointment open
						for(; i < 5; i++)
						{
							strcpy(names[i], names[i + 1]); // shifts all names up in the array of strings
							appts[i] = appts[i + 1]; // shifts the availability of the appointments in the array of appointments
						}
						if(i == 5)
						{
							names[i][0] = '\0'; // makes sure the end of the array is accounted for if the second to last entry is erased
							appts[i] = 0; // opens up appointment if the second to last appointment is cancelled
						}
						break;
					}
				}
				if(i == 6 && counter != 6) // no match found
				{
					printf("Sorry could not find any corresponding appointment, please check your records again.\n");
				}
				if(i == 6 && counter == 6) // no match found because the schedule is empty
				{
					printf("Sorry, no appointments are currently scheduled and the day is completely open.\n");
				}
				break;
			}
			case 3: // if they choose 3 to display the list of appointments for the day
			{
				printf("The following is the schedule list for the day for Dr. Kavorkian's appointments. There are %d open appointments.\n", counter); // how many appointments are currently open at the moment
				if(counter == 6) // entire schedule is empty and open
				{
					printf("All slots are open for scheduling an appointment today.\n");
				}
				else // at least one appointment is full
				{ 
					for(i = 0; i < 6; i++)
					{
						if(appts[i] == 0) // going through and checking which appointments are open and free
						{
							printf("%d to %d pm hour client: none (free)\n", i + 1, i + 2);
						}
						else if(appts[i] == 1) // going through and checking which appointments are closed and filled with a certain client
						{
							printf("%d to %d pm hour client: %s (full)\n", i + 1, i + 2, names[i]);
						}
					}
				}
				break;
			}
			default: // any other number chosen results in the switch statement being terminated while at the same time terminating the entire main function including the forever while loop using a return statement
			{
				return 0; 
				break;
			}
		}
	}
}
