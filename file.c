#include <stdio.h>
#include "file.h"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.txt", "w");
    if(fp == NULL) {
        printf(RED"Error: Unable to open file for saving.\n"RESET);
        return;
    }
    
    // Save all contacts
    fprintf(fp, "%d\n", addressBook->contactCount);
    for(int i = 0; i < addressBook->contactCount; i++) {
       fprintf(fp, "%s\n", addressBook->contacts[i].name);
       fprintf(fp, "%s\n", addressBook->contacts[i].phone);
       fprintf(fp, "%s\n", addressBook->contacts[i].email);       
    }
    fclose(fp);
    printf(GREEN"Saved %d contacts to 'contacts.txt'.\n"RESET, addressBook->contactCount);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen("contacts.txt", "r");
    if(fp == NULL)
    {
        addressBook->contactCount = 0;
        return;
    }
    int fileCount;
    if(fscanf(fp, "%d", &fileCount) != 1)
    {
        addressBook->contactCount = 0;
        fclose(fp);
        return;
    }
    if(fileCount < 0 || fileCount > MAX_CONTACTS)
    {
        printf(RED"Error: Invalid contact count in file.\n"RESET);
        fclose(fp);
        return;
    }
    
    // Reset contact count to 0 to avoid duplicates
    addressBook->contactCount = 0;
    
    for(int i = 0; i < fileCount && addressBook->contactCount < MAX_CONTACTS; i++) {
        if(fscanf(fp, " %[^\n]", addressBook->contacts[addressBook->contactCount].name) != 1 || 
           fscanf(fp, " %[^\n]", addressBook->contacts[addressBook->contactCount].phone) != 1 ||
           fscanf(fp, " %[^\n]", addressBook->contacts[addressBook->contactCount].email) != 1) 
           {
            printf(RED"Error reading contact #%d from file.\n"RESET, i + 1);
            break;
        }
        addressBook->contactCount++;
    }
    fclose(fp);
    printf(GREEN"Loaded %d contacts from file.\n"RESET, addressBook->contactCount);
}

   


