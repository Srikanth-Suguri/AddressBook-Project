/*
NAME:SUGURI SRIKANTH
BATCH ID:26015_B
DATE:29/08/2026
DESCRIPTION:
Address Book Management System
This is a C language project used to manage contact details. Users can create, search, edit, delete, and view contacts.
The project validates names, phone numbers, and email addresses and avoids duplicate phone numbers and emails. It also uses file handling to save contacts and load them when the program starts.
Technologies Used: C, Structures, Arrays, Functions, Strings, and File Handling.
*/
#include <stdio.h>
#include "contact.h"


#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf(CYAN"\nAddress Book Menu:\n"RESET);
        printf(YELLOW"1. Create contact\n"RESET);
        printf(YELLOW"2. Search contact\n"RESET);
        printf(YELLOW"3. Edit contact\n"RESET);
        printf(YELLOW"4. Delete contact\n"RESET);
        printf(YELLOW"5. List all contacts\n"RESET);
        printf(YELLOW"6. Exit\n"RESET);
        printf(BLUE"Enter your choice: "RESET);
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                printf(GREEN"Saving and Exiting...\n"RESET);
                saveContactsToFile(&addressBook);
                break;
            default:
                printf(RED"Invalid choice. Please try again.\n"RESET);
        }
    } while (choice != 6);
    
       return 0;
}
