#include <stdio.h>

int main()
{
	int counter = 6; // initializing the number of appointments available to sign up for
	int appts[6]; // array of appointments all starting out as 0
	printf("Welcome to Dr. Kavorkian's Dental Office. How may we HELP you today?\n");
	while(1)
	{
		int entry;
		printf("Enter 1 to schedule and appointment, 2 to cancel an appointment, 3 to view the list of appointments or some other number to quit out.\n");
		scanf("%d", &entry);
		int i;
		int id;
		if(entry == 1) // if the user wants to schedule an appointment
		{
			for(i = 0; i < 6; i++) // going through the array and checking to see if any appointments are available and assigning the earliest one
			{
				if(appts[i] == 0) // appointment is open
				{
					appts[i] = 1; // appointment is taken
					printf("Thank you, you are scheduled for the %d to %d pm hour. Your appointment id is %d.\n", i + 1, i + 2, i + 1);
					counter--;
					break;
				}
			}
			if(counter == 0 && i == 6) // no open appointments left and already checked by the system
			{
				printf("Sorry, there are no available appointments for today. Please try again later.\n");
			}
		}
		else if(entry == 2) // if the user wants to cancel an appointment
		{
			printf("Please enter your appointment id to cancel your appointment: ");
			scanf("%d", &id); // receiving the appointment id
			for(i = 0; i < 6; i++)
			{
				if(appts[i] == 1 && id == i + 1) // going through and checking if the appointment with that appointment id is full and changing it to open
				{
					appts[i] = 0; // appointment is now open
					printf("Thank you, your appointment has been cancelled.\n");
					counter++; 
					break;
				}
			}
			if(i == 6) // if nothing could be found or matched up, the loop happens and the user has to check again
			{
				printf("Sorry, could not find the corresponding appointment, please check again.\n");
			}
		} 
		else if(entry == 3) // if the user wants to see the list of appointments
		{
			printf("The following is the schedule list for the day for Dr. Kavorkian's appointments. There are %d open appointments.\n", counter);
			if(counter == 6) // all appointments are open
			{
				printf("All slots are open for scheduling an appointment.\n");
			}
			else // if at least one appointment is filled it will list them all out
			{
				for(i = 0; i < 6; i++)
				{
					if(appts[i] == 0) // appointment is free
					{
						printf("%d to %d pm hour id: 0 (free)\n", i + 1, i + 2);
					}
					else if(appts[i] == 1) // appointment is filled
					{
						printf("%d to %d pm hour id: %d (full)\n", i + 1, i + 2, i + 1);
					}
				}
			}
		}
		else if(entry < 1 || entry > 3) // if the user wants to quit out of the appointment system the while loop is broken here by any other number
		{
			break;
		}
	}
	return 0; 
}











