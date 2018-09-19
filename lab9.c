#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void schedule(void); // declaration of the scheduling function
void cancel(void); // declaration of the cancellation function
void list(void); // declaration of the listing function
void emergency(void); // declaration of the emergency scheduling function
int count_letter(char); // declaration of the letter counting function

int i, j; // global int variables for use in all loops later on
int appts[6] = {0, 0, 0, 0, 0, 0}; //array to represent open/closed appointments in the system
char names[6][20]; // array of strings created globally
int counter = 6; // number of open appointments counter created globally
char letter;

int main()
{
	int entry; // user's choice
	printf("Welcome to Dr. Kavorkian's Dental Office! How may we HELP you?\n");
	while(1)
	{
		printf("Enter a 1 to schedule an appointment, 2 to cancel an appointment, 3 to list the appointments, 4 if you have an emergency and need to be first on the list, 5 to count a certain letter or any other number to exit out of the system.\n");
		scanf("%d", &entry);
		switch (entry)
		{
			case 1: // if the user chooses 1, the scheduling function will be called
			{
				schedule();
				break;
			}
			case 2: // if the user chooses 2, the cancellation function will be called
			{
				cancel();
				break;
			}
			case 3: // if the user chooses 3, the listing function will be called
			{
				list();
				break;
			}
			case 4: // if the user chooses 4, the emergency scheduling function will be called
			{
				emergency();
				break;
			}
			case 5: // if the user chooses 5, they will be asked a letter which will then call the letter counting function and return the number of times that letter is in the array of strings
			{
				printf("What letter do you want to count at this time?\n");
				fpurge(stdin);
				scanf("%c", &letter);
				fpurge(stdin);
				int total = count_letter(letter);
				printf("There are %d occurrences of the letter %c in the system at this time.\n", total, letter);
				break;
			}
			default: // anything else chosen by the user will exit out of the system and end the program
			{
				return 0;
			}
		}
	}
}

void
schedule(void)
{
	char compare[20]; // another string to make sure the user does not enter a duplicate name into the system
	if(counter == 0) // if the dentist is busy, the user will be informed
	{
		printf("Sorry, all appointments are full at this time. Please try again later.\n");
	}
	if(counter != 0)
	{
		printf("Please type in your first name: \n");
		scanf("%s", compare); // user's name stored into the compare array to check first
		for(i = 0; i < 6; i++)
		{
			if(appts[i] == 0)
			{
				strcpy(names[i], compare); // entered name will be stored into the array of strings that the system keeps for the list of appointments
				appts[i] = 1; // appointment time is closed off
				printf("Thank you %s, your are scheduled for the %d to %d pm hour.\n", names[i], i + 1, i + 2);
				counter--; // one less open appointment
				break;
			}
			if(appts[i] == 1)
			{
				if(strcmp(names[i], compare) == 0) // if the closed appointment has the same name as entered user name, the system will let the user know they cannot enter a name twice
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
cancel(void)
{
	char search[20]; // array made to take user's entered name and see if it is in the system so it can be cancelled
	printf("Please enter your name to confirm your cancellation: \n");
	scanf("%s", search);
	for(i = 0; i < 6; i++)
	{
		if(strcmp(names[i], search) == 0 && appts[i] == 1) // sees if there is a match between the entered name and a name saved in the system
		{
			appts[i] = 0; // closed appointment time opened up
			printf("Thank you %s, your appointment has been cancelled.\n", names[i]);
			counter++; // one more open appointment
			for(; i < 5; i++)
			{
				strcpy(names[i], names[i + 1]); // moves remaining strings up to closed the hole left by the cancelled appointment
				appts[i] = appts[i + 1]; // fills in the gap in the array of appointments
			}
			if(i == 5) // special case makes sure that the penultimate and last names in the string array are accounted for and fills the hole left
			{
				names[i][0] = '\0';
				appts[i] = 0;
			}
			break;
		}
	}
	if(i == 6 && counter != 6) // if no name found and there is at least one closed appointment
	{
		printf("Sorry, could not find any corresponding appointment, please check your records again.\n");
	}
	if(i == 6 && counter == 6) // if no name is found and all appointments are open
	{
		printf("Sorry, no appointments are scheduled currently and the day is completely open.\n");
	}
	return;
}

void
list(void)
{
	if(counter == 1) // only one open appointment for grammar purposes
	{
		printf("The following is the schedule list for the day for Dr. Kavorkian's appointments. There is 1 open appointment.\n");
	}
	else // if more than one or no appointments are open
	{
		printf("The following is the schedule list for the day for Dr. Kavorkian's appointments. There are %d open appointments.\n", counter);
	}
	if(counter == 6) // if all appointments are open, the user is informed
	{
		printf("All slots are open for scheduling an appointment today.\n");
	}
	else // if at least one appointment is closed, the list is created for the user
	{
		for(i = 0; i < 6; i++)
		{
			if(appts[i] == 0) // prints out all the free appointments and their time slots
			{
				printf("%d to %d pm hour client:  (free)\n", i + 1, i + 2);
			}
			else if(appts[i] == 1) // prints out all the filled appointments along with their time slots and client's name
			{
				printf("%d to %d pm hour client: %s (full)\n", i + 1, i + 2, names[i]);
			}
		}
	}
	return;
}

void
emergency(void)
{
	char compare[20]; // extra array created so that entered name is not a duplicate
	printf("Since it is an emergency, we will fit you in the schedule and give you first priority. Please enter your first name: \n");
	scanf("%s", compare);
	for(i = 0; i < 6; i++)
	{
		if(strcmp(names[i], compare) == 0) // if the name is a duplicate, user is informed and program returns to while loop
		{
			printf("Sorry, but that name is already entered in our system and we cannot take in your name and cannot accommodate your request. Sorry for any incidents that may occur as a result.\n");
			return;
		}
	}
	if(counter == 0) // if the emergency name is entered with no open appointments, the user is informed they are in and the last person was deleted
	{
		printf("You are now scheduled for the 1 to 2 pm hour, %s.\n", compare);
		printf("Unfortunately, the last person, %s, has been kicked from the system. We here at Dr. Kavorkian's Dental Office hope that %s will understand the nature of this emergency.\n", names[5], names[5]);
	}
	for(i = 4; i >= 0; i--) // names and appointment availabilities are all shifted down one in their respective arrays
	{
		strcpy(names[i + 1], names[i]);
		appts[i + 1] = appts[i];
	}
	strcpy(names[0], compare); // emergency name is first on the list
	appts[0] = 1; // first appointment is closed
	if(counter != 0)
	{
		printf("You are now scheduled for the 1 to 2 pm hour, %s.\n", compare);
		counter--; // counter is only decreased if the names list was not full when the emergency name was entered
	}
}

int
count_letter(char ch)
{
	char *p; // character pointer created
	int tally = 0; // letter counter created
	for(i = 0; i < 6; i++)
	{
		p = names[i];
		while(*p != '\0') // p starts at beginning of each name string and moves down until the end
		{
			if(*p == ch) // if the letter is present, the counter increases by 1
			{
				tally++;
			}
			p++;
		}
	}
	return tally; // letter total is returned to the main function
}	
		





























































































































































































