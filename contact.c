#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"


int validation_of_name(char *name);
int validation_of_phone_num(char *phone);
int validation_of_email(char *mail);


int search_by_name(AddressBook *addressBook);
int search_by_phone_no(AddressBook *addressBook);
int search_by_email(AddressBook *addressBook);

int search_by_name(AddressBook *addressBook)
{
    printf(BLUE"Please Enter the Name Which you want to Search: "RESET);

    char search_name[50];

    scanf(" %[^\n]", search_name);

    int flag = 0;
    int count = 0;
    int index = -1;

    // Search for the name
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].name, search_name) == 0)
        {
            printf("NAME        :%s\n", addressBook->contacts[i].name);
            printf("PHONE NUMBER:%s\n", addressBook->contacts[i].phone);
            printf("EMAIL       :%s\n", addressBook->contacts[i].email);

            flag = 1;
            count++;
            index = i;
        }
    }
    // No contact found
    if(flag == 0)
    {
        printf(RED"No Contacts Found\n"RESET);
        return -1;
    }

    // Only one contact found
    if(count == 1)
    {
        return index;
    }

    // Multiple contacts with same name found
    printf(RED"\nHere Multiple contacts found with the same name %s\n"RESET,search_name);

    char search_phone[20];

    printf(BLUE"Please Enter the Phone Number: "RESET);
    scanf(" %s", search_phone);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].name, search_name) == 0 && strcmp(addressBook->contacts[i].phone, search_phone) == 0)
        {
            printf("\nContact Found:\n");

            printf("NAME        :%s\n", addressBook->contacts[i].name);
            printf("PHONE NUMBER:%s\n", addressBook->contacts[i].phone);
            printf("EMAIL       :%s\n", addressBook->contacts[i].email);

            return i;
        }
    }

    printf(RED"No contact found with this Name and Phone Number\n"RESET);

    return -1;
}


int search_by_phone_no(AddressBook *addressBook)
{
    printf(BLUE"Please Enter the Phone Number Which you want to Search:"RESET);
    char search_phone[50];
    scanf(" %s",search_phone);
    int index=0;
    int flag=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,search_phone)==0)
        {
            printf("NAME        :%s\n",addressBook->contacts[i].name);
            printf("PHONE NUMBER:%s\n",addressBook->contacts[i].phone);
            printf("EMAIL       :%s\n",addressBook->contacts[i].email);
            flag=1;
            index=i;
        }
    }   
    if(flag==0)
    {
        printf(RED"No Contacts Found\n"RESET);
        return -1;
    }
    return index;
}

int search_by_email(AddressBook *addressBook)
{
    printf(BLUE"Please Enter the Email Which you want to Search:"RESET);
    char search_mail[50];
    scanf(" %s",search_mail);
    int flag=0;
    int index=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,search_mail)==0)
        {
            printf("NAME        :%s\n",addressBook->contacts[i].name);
            printf("PHONE NUMBER:%s\n",addressBook->contacts[i].phone);
            printf("EMAIL       :%s\n",addressBook->contacts[i].email);
            flag=1;
            index=i;
        }
    }   
    if(flag==0)
    {
        printf(RED"No Email Found\n"RESET);
        return -1;
    }
    return index;
}




void listContacts(AddressBook *addressBook) 
{
    printf(CYAN"\tSTUDENT CONTACT DETAILS\t"RESET);
    printf("\n--------------------------------------------------\n");
    printf(BLUE"\n%-20s%-20s%-30s\n", "NAME", "PHONE NUMBER", "EMAIL"RESET);
    printf("--------------------------------------------------\n");

    for(int i=0;i<addressBook->contactCount;i++)
    { 
        printf(GREEN"%-20s"RESET, addressBook->contacts[i].name);
        printf(GREEN"%-20s"RESET, addressBook->contacts[i].phone);
        printf(GREEN"%-30s"RESET, addressBook->contacts[i].email);
        printf("\n---------------------------------------------------");
        printf("\n");
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validation_of_name(char *name)
{

    int count=0;
    int flag=0;
    int flag2=0;
    for(int i=0;name[i];i++)
    {
        count+=1;
        if(!(name[i]==' '||name[i]=='.'||isalpha(name[i]))){
            flag=1;
        }
    }
    if(count<4){
        printf(RED"Error Message : Name must contain at least 4 characters\n"RESET);
        flag2=1;
        return 0;
    }
    if(flag==1){
        printf(RED"Error Message : Name should contain only alphabets\n"RESET);
        flag2=1;
        return 0;
    }
    return 1;
}




int validation_of_phone_num(char *phone)
{
    int mob_count=0;
    int flag_mob=0;
    for(int j=0;phone[j];j++)
    {
        mob_count++;
        if(!isdigit(phone[j]))
        {
            flag_mob=1;
        }
    }
    if(!(phone[0]>='6' && phone[0]<='9')){
        printf(RED"Error Message : First digit must be between 6 and 9\n"RESET);
        return 0;
    }
    if(mob_count!=10){
        printf(RED"Error Message : Phone number must contain exactly 10 digits\n"RESET);
        return 0;
    }
    if(flag_mob==1){
        printf(RED"Error Message : Other than Digits any other Character not allowed in phone number\n"RESET);
        return 0;
    }
    return 1;
}


int validation_of_email(char *mail)
{
    int e_flag = 0;
    int at_count = 0;
    int dot_count = 0;
    int at_index = 0;
    int dot_index = 0;
    for(int i = 0; mail[i]; i++)
    {
        if(!(islower(mail[i]) || isdigit(mail[i]) || mail[i] == '@' || mail[i] == '.')){
            printf(RED"Error Message : Invalid symbol\n"RESET);
            e_flag = 1;
        }
        if(mail[i] == '@'){
            at_count++;
            at_index = i;
        }
        if(mail[i] == '.'){
            dot_count++;
            dot_index = i;
        }
    }
     if(at_count == 0){
        printf(RED"Error Message : Missing @\n"RESET);
        e_flag = 1;
    }
    else if(at_count > 1){
        printf(RED"Error Message : Multiple @ symbols\n"RESET);
        e_flag = 1;
    }
    if(dot_count == 0)
    {
        printf(RED"Error Message : Missing .\n"RESET);
        e_flag = 1;
    }
    else if(dot_count > 1){
        printf(RED"Error Message : Multiple dots\n"RESET);
        e_flag = 1;
    }
    if(at_count == 1 && dot_count == 1)
    {
        if(dot_index < at_index){
            printf(RED"Error Message : Dot must appear after @\n"RESET);
            e_flag = 1;
        }
        else if(dot_index - at_index <= 1){
            printf(RED"Error Message : Missing character between @ and .\n"RESET);
            e_flag = 1;
        }
        else if(mail[dot_index + 4] != '\0'){
            printf(RED"Error Message : Extra characters after the domain\n"RESET);
            e_flag = 1;
        }
    }
    if(e_flag==1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


void  createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    for(int attempt=1;attempt<=3;attempt++){
        char name[50];
        printf(BLUE"Enter The Student Name:"RESET);
        scanf(" %[^\n]",name);
        char phone[20];
        printf(BLUE"Enter The Student Phone Number:"RESET);
        scanf(" %s",phone);
        
        char mail[50];
        printf(BLUE"Enter The Student MAIL ID:"RESET);
        scanf(" %s", mail);
        
        int valid_name=validation_of_name(name);

        int valid_phone=validation_of_phone_num(phone);

        int valid_email=validation_of_email(mail);

        int email_flag=0;
        int phone_flag=0;

        if(valid_name && valid_phone && valid_email)
        {
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].phone,phone)==0)
                {
                    printf(RED"Error Message:The Phone Number already exists\n"RESET);
                    phone_flag=1;
                }
                if(strcmp(addressBook->contacts[i].email,mail)==0)
                {
                    printf(RED"Error Message:The email already exists\n"RESET);
                    email_flag=1;
                }
            }
            if(email_flag==0 && phone_flag==0)
            {
                strcpy(addressBook->contacts[addressBook->contactCount].name, name);
                strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
                strcpy(addressBook->contacts[addressBook->contactCount].email, mail);
                addressBook->contactCount++;
                printf(GREEN "Contact Created Successfully!\n" RESET);
                return;
            }
        }
        if(attempt<3)
        {
            printf(RED"Please Try Again\n"RESET);
        }
    }
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    printf(CYAN"\nSearching Menu:\n"RESET);
    printf(YELLOW"1.Search by Name\n"RESET);
    printf(YELLOW"2.Search by Phone Number:\n"RESET);
    printf(YELLOW"3.Search by Mail Id\n"RESET);
    printf(BLUE"Enter Your Choice: "RESET);
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
        search_by_name(addressBook);
        break;
        case 2:
        search_by_phone_no(addressBook);
        break;
        case 3:
        search_by_email(addressBook);
        break;
        default:
        printf(RED"Invalid Choice\n"RESET);
    }

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    printf(CYAN"Searching Menu:\n"RESET);
    printf(YELLOW"1.Search by Name\n"RESET);
    printf(YELLOW"2.Search by Phone Number:\n"RESET);
    printf(YELLOW"3.Search by Mail Id\n"RESET);
    printf(BLUE"Enter Your Choice: "RESET);
    int choice;
    scanf("%d",&choice);
    int index=0;
    switch(choice)
    {
        case 1:
        index=search_by_name(addressBook);
        break;
        case 2:
        index=search_by_phone_no(addressBook);
        break;
        case 3:
        index=search_by_email(addressBook);
        break;
        default:
        printf(RED"Invalid Choice\n"RESET);
    }
    if(index==-1){
        printf(RED"Not Found\n"RESET);
        return;
    }


    printf(CYAN"Editing Menu:\n"RESET);
    printf(YELLOW"1.Edit by Name\n"RESET);
    printf(YELLOW"2.Edit by Phone Number:\n"RESET);
    printf(YELLOW"3.Edit by Mail Id\n"RESET);
    printf(BLUE"Enter Your Choice: "RESET);
    int edit_choice;
    scanf("%d",&edit_choice);
    switch(edit_choice)
    {
        case 1:
        char edit_name[50];
        printf(BLUE"Enter the Editable Name:"RESET);
        scanf(" %[^\n]",edit_name);
        if(validation_of_name(edit_name))
        {
            strcpy(addressBook->contacts[index].name,edit_name);
            printf(GREEN "Name Updated Successfully!\n" RESET);
        }
        break;
        case 2:
        char edit_mob[50];
        printf(BLUE"Enter the Editable Phone Number:"RESET);
        scanf(" %[^\n]",edit_mob);
        if(validation_of_phone_num(edit_mob))
        {
            strcpy(addressBook->contacts[index].phone,edit_mob);
            printf(GREEN "Phone Number Updated Successfully!\n" RESET);
        }
        break;
        case 3:
        char edit_mail[50];
        printf(BLUE"Enter the Editable Email:"RESET);
        scanf(" %[^\n]",edit_mail);
        if(validation_of_email(edit_mail))
        {
            strcpy(addressBook->contacts[index].email,edit_mail);
            printf(GREEN "Email Updated Successfully!\n" RESET);
        }
        break;
        default:
        printf(RED"Invalid Choice\n"RESET);
    }    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    printf(CYAN"Searching Menu:\n"RESET);
    printf(YELLOW"1.Search by Name\n"RESET);
    printf(YELLOW"2.Search by Phone Number:\n"RESET);
    printf(YELLOW"3.Search by Mail Id\n"RESET);
    printf(BLUE"Enter Your Choice: "RESET);
    int choice;
    scanf("%d",&choice);
    int index=0;
    switch(choice)
    {
        case 1:
        index=search_by_name(addressBook);
        break;
        case 2:
        index=search_by_phone_no(addressBook);
        break;
        case 3:
        index=search_by_email(addressBook);
        break;
        default:
        printf(RED"Invalid Choice\n"RESET);
    }
    if(index==-1)
    {
        return;
    }
     for(int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;
    printf(GREEN "Contact Deleted Successfully!\n" RESET);
}
