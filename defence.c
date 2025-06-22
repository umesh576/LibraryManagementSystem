#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>

struct library{
	int bookno;
	char name[20];
	char writer[20];
}l[100];
struct issuse
{
	int bookno;
	char bookname[20];
	char studentname[20];
	int iday;
	int imonth;
	char writername[50];
	int iyear;
	int bday;
	int bmonth;
	char studentaddress[20];
	long long int studentno;
	int byear;
}p[100];

#define MAX_LENGTH 100

char admin_username[50];
char admin_password[50];








// for login page
int loginUser() {
    char storedUsername[MAX_LENGTH];
    char storedPassword[MAX_LENGTH];
    char inputUsername[MAX_LENGTH];
    char inputPassword[MAX_LENGTH]; 
    char ch3;
    int i=0;

    FILE *file = fopen("login.txt", "r");
    if (file == NULL) {
        printf("\nError in opening of login file.\n");
        exit(1);
    }

    fgets(storedUsername, MAX_LENGTH, file);
    fgets(storedPassword, MAX_LENGTH, file);
    storedUsername[strcspn(storedUsername, "\n")] = '\0'; // Remove newline character
    storedPassword[strcspn(storedPassword, "\n")] = '\0'; // Remove newline character
    fclose(file);
	
    printf("\nEnter username: ");
    fgets(inputUsername, MAX_LENGTH, stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
	while(1)
		{
			ch3=getch();
			if(ch3==13)//13 for assi value for enter
			{
				inputPassword[i]='\0';
				break;
			}
			else if(ch3==8)//8 for for ascci value for backspace key
			{
				if(i>0)
				printf("\b \b");
				i--;	
			}
			else
			{
				inputPassword[i]=ch3;
					printf("*");
					i++;
			}
		}

    if (strcmp(storedUsername, inputUsername) == 0 && strcmp(storedPassword, inputPassword) == 0) {
        return 1; // Login successful
    } 
	else 
	{
        return 0; // Login failed
    }
}

//for issuse book from library

void issuse() {
    FILE *libraryFile, *issueFile, *tempFile;
    struct library book;
    struct issuse newIssue;
    int bookFound = 0;

    // Open the library file for reading
    libraryFile = fopen("umesh.txt", "r");
    if (libraryFile == NULL) {
        printf("Error opening library file.\n");
        return;
    }

    // Create a temporary file for updating the library
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(libraryFile);
        return;
    }

    // Open the issue file for appending
    issueFile = fopen("umesh1.txt", "a");
    if (issueFile == NULL) {
        printf("Error opening issue file.\n");
        fclose(libraryFile);
        fclose(tempFile);
        return;
    }

    printf("Books available in the library:\n\n");
    while (fscanf(libraryFile, "%d\t\t\t%s\t\t\t%s\n", &book.bookno, book.name, book.writer) != EOF) {
        printf("%d\t\t%s\t\t\t%s\n", book.bookno, book.name, book.writer);
    }
    rewind(libraryFile); // Reset file pointer to the beginning

    printf("\nThese books are available for issueing.\n");

    // Input the book to be issued
    printf("\nEnter the Book ID to issue: ");
    scanf("%d", &newIssue.bookno);
    getchar(); // Consume newline character

    // Read through the library file
    while (fscanf(libraryFile, "%d\t\t\t%s\t\t\t%s\n", &book.bookno, book.name, book.writer) != EOF) {
        if (book.bookno == newIssue.bookno) {
            // Book found in library, prepare to issue
            bookFound = 1;
            strcpy(newIssue.bookname, book.name);

            printf("Enter student name: ");
            fgets(newIssue.studentname, sizeof(newIssue.studentname), stdin);
            newIssue.studentname[strcspn(newIssue.studentname, "\n")] = '\0'; // Remove newline character
            
            int len=0;
            char ch4 = 'a';
            char numberStr[20];
            long long int newnumber;
            do
            {
            	printf("Enter student phone number: ");
        		scanf("%lld",&newIssue.studentno);

				newnumber = newIssue.studentno;
				sprintf(numberStr,"%lld",newnumber);
				int len = strlen(numberStr);
				if(len == 10)
				{
					getchar();
		        	printf("Enter student address: ");
		        	fgets(newIssue.studentaddress,sizeof(newIssue.studentaddress),stdin);
		        	newIssue.studentaddress[strcspn(newIssue.studentaddress,"\n")] = '\0';
		            
		            char ch3 = 'y';
					do
					{
						printf("Enter issuse date: \n");
						printf("Enter issue day: ");
						scanf("%d",&newIssue.iday);
						printf("Enter issue month: ");
						scanf("%d",&newIssue.imonth);
						printf("Enter issue year: ");
						scanf("%d",&newIssue.iyear);
						printf("\n");
					
			            printf("Enter return date: \n");
			            printf("Enter return day: ");
						scanf("%d",&newIssue.bday);
						printf("Enter return month: ");
						scanf("%d",&newIssue.bmonth);
						printf("Enter return year: ");
						scanf("%d",&newIssue.byear);
		
						if(newIssue.imonth<=12&&newIssue.iday<=32&&newIssue.bmonth<=12&&newIssue.bday<=32 && newIssue.iday != 0 && newIssue.bday !=0 && newIssue.byear>=2000 && newIssue.iyear >= 2000)
						{
							if(newIssue.iyear<newIssue.byear)
							{
								fprintf(issueFile, "%d\t\t%s\t\t%s\t\t%s\t\t%lld\t\t%d/%d/%d\t%d/%d/%d\n", newIssue.bookno, newIssue.bookname, newIssue.studentname,newIssue.studentaddress,newIssue.studentno,newIssue.iyear,newIssue.imonth,newIssue.iday,newIssue.byear,newIssue.bmonth,newIssue.bday);
						    	break;
							}
							else if(newIssue.iyear==newIssue.byear)
							{
								if(newIssue.imonth<newIssue.bmonth)
								{
									fprintf(issueFile, "%d\t\t%s\t\t%s\t\t%s\t\t%lld\t\t%d/%d/%d\t%d/%d/%d\n", newIssue.bookno, newIssue.bookname, newIssue.studentname,newIssue.studentaddress,newIssue.studentno,newIssue.iyear,newIssue.imonth,newIssue.iday,newIssue.byear,newIssue.bmonth,newIssue.bday);
						    		break;
								}
								else if(newIssue.imonth == newIssue.bmonth)
								{
									if(newIssue.bday>=newIssue.iday)
									{
										fprintf(issueFile, "%d\t\t%s\t\t%s\t\t%s\t\t%lld\t\t%d/%d/%d\t%d/%d/%d\n", newIssue.bookno, newIssue.bookname, newIssue.studentname,newIssue.studentaddress,newIssue.studentno,newIssue.iyear,newIssue.imonth,newIssue.iday,newIssue.byear,newIssue.bmonth,newIssue.bday);
						    			break;
									}
									else
									{
										printf("If your year and month are same then your return date must be greater than issue date\nPlease renter the date.\n\n");
										
									}
									break;
								}
								else
								{
									printf("If you year are same you return month must be higher than issue month\nplease enter date again.\n\n");
									break;
								}
							}
							else
							{
								printf("\nyour issue date is greater than return date.\nPlease re enter a new date.\n\n");
							}
							break;
						}
						else
						{
							printf("\n\nyou enter a wrong date.\n please enter a correct date\n\n");
							printf("Please re enter a issue and return date\n\n");
						}
					}while(ch3 == 'y' || ch3 == 'Y');
					break;
					
				}
				else
				{
					printf("\n your phone number must be a 10 digits.");
					printf("please re enter your number.\n");
				
				}
				len=0;
			}while(ch4 =='a' || ch4 == 'a');
        	
        	
            // Write the new issue to the issue file   
        } 
		else {
            // Write the book to the temp file (book not issued)
            fprintf(tempFile, "%d\t\t\t%s\t\t\t%s\n", book.bookno, book.name, book.writer);
        }
    }

    // Close the files
    fclose(libraryFile);
    fclose(issueFile);
    fclose(tempFile);
    if (bookFound)
	{
        // Replace the original library file with the updated temp file
        remove("umesh.txt");
        rename("temp.txt", "umesh.txt");
        printf("Book issued successfully.\n");
    } else {
        // No book found, clean up temp file
        remove("temp.txt");
        printf("Book not found in the library.\n");
    }

    
}

//function for a see issuse book

void seeissuse()
{
	FILE *fp;
	char ch;
	char ch3;
	fp=fopen("umesh1.txt","r");
	if (fp == NULL) {
        printf("File is not found!\n");
        return;
    }
	while(ch != EOF)
	{
		printf("%c",ch);
		ch=fgetc(fp);
	}
}

//function for a see book avaliable in library

void see()
{
	char ch;
	char ch3;
	FILE *fp1;
	fp1=fopen("umesh.txt","r");
	if (fp1 == NULL) {
        printf("File is not found!\n");
        return;
    }
    printf("These are the avalaible book in library.\n\n");
	while(ch != EOF){
		printf("%c",ch);
		ch=fgetc(fp1);
	}
	fclose(fp1);
	printf("\n");
}


//function for a search a book avaliable ina library

void search()
{
	char searchName[20];
    int found = 0;
    printf("Enter the name of the book to search: ");
    getchar(); 
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; 

    FILE *fp = fopen("umesh.txt", "r");
    if (fp == NULL) {
        printf("Error opening library file.\n");
        return;
    }

    printf("\nSearch results:\n\n");
    while (fscanf(fp, "%d\t\t\t%s\t\t\t%s\n", &l[0].bookno, l[0].name, l[0].writer) != EOF) {
        if (strcmp(l[0].name, searchName) == 0) 
		{
			printf("Book no\t\tBook name\t\tWriter name\n");
			printf("%d\t\t%s\t\t\t%s",l[0].bookno,l[0].name,l[0].writer);
            found = 1;
        }
    }

    if (!found)
	{
        printf("Book not found in the library.\n");
    }

    fclose(fp);
}



void add() {
    FILE *fp;
    struct library new_book;
    int n, i;

    fp = fopen("umesh.txt", "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
	char ch;
	char ch5='b';
	int new_book1;
	char numberStr[20];
	do
	{
		printf("Enter the number of books to add: ");
	    scanf("%d", &n);
	    getchar(); // Consume newline character
	
	    for (i = 0; i < n; i++) 
		{
	        
	        do
	        {
	        	printf("\nEnter book number: ");
		        scanf("%d", &new_book.bookno);
		        getchar(); // Consume newline character
		        
		        new_book1 = new_book.bookno;
		        		         
		        
		        sprintf(numberStr, "%d", new_book1);

			    // Measure the length of the string using strlen
			    int len = strlen(numberStr);
				if( len == 4)
				{
					// Check if the book already exists
			        FILE *check_fp = fopen("umesh.txt", "r");
			        if (check_fp == NULL) {
			            printf("Error opening file.\n");
			            fclose(fp);
			            return;
			        }
			        int duplicate = 0;
			        while (fscanf(check_fp, "%d\t\t\t%s\t\t\t%s\n", &l[0].bookno, l[0].name, l[0].writer) != EOF) {
			            if (new_book.bookno == l[0].bookno) {
			                printf("Book with the same number already exists.\n");
			                duplicate = 1;
			                break;
			            }
			        }
			        fclose(check_fp);
			
			        if (!duplicate) {
			            printf("Enter book name: ");
			            fgets(new_book.name, sizeof(new_book.name), stdin);
			            new_book.name[strcspn(new_book.name, "\n")] = '\0'; // Remove newline character
			
			            printf("Enter writer name: ");
			            fgets(new_book.writer, sizeof(new_book.writer), stdin);
			            new_book.writer[strcspn(new_book.writer, "\n")] = '\0'; // Remove newline character
			
			            fprintf(fp, "%d\t\t\t%s\t\t\t%s\n", new_book.bookno, new_book.name, new_book.writer);
			            printf("Book added successfully.\n");
			        }
			        printf("\n");
			        break;
				}
				else
				{
					printf("Book no must be a 4 digits.");
					printf("please re enter book no.");
				}
				len =0;
			}while(ch5 == 'b' || ch5 == 'B');
	        
	
	        
	    }
	
	    fclose(fp);
	    printf("\n\nDo you want to added more book.\n");
	    printf("If yes press y otherwise continue?\n");
	    ch = getche();
	}while(ch == 'y' || ch == 'Y');
    
}

//for delete a book from library

void deletebook()
{
	char ch;
	do
	{
		FILE *fp1, *fp2;
	    char bookname[20];
	    int found = 0;
	
	    fp1 = fopen("umesh.txt", "r");
	    fp2 = fopen("tempnew.txt", "w");
	
	    if (fp1 == NULL || fp2 == NULL) {
	        printf("Error in file handling!\n");
	        return;
	    }
		
		printf("These are the avaliable book in the library.\n\n");
    	see();
    printf("only these book are alble to delete.");
    printf("\n\n\n");
    
	    printf("Enter the name of the book to delete: ");
	    getchar(); 
	    fgets(bookname, sizeof(bookname), stdin);
	    bookname[strcspn(bookname, "\n")] = '\0'; 
	    
	    while (fscanf(fp1, "%d\t\t\t%s\t\t\t%s\n", &l[0].bookno, l[0].name, l[0].writer) != EOF) {
	        if (strcmp(l[0].name, bookname) != 0)
			{
	            fprintf(fp2, "%d\t\t\t%s\t\t\t%s\n", l[0].bookno, l[0].name, l[0].writer);
	        } 
			else
			{
	            found = 1;
	        }
	    }
	
	    fclose(fp1);
	    fclose(fp2);
	
	    if (found) {
	        remove("umesh.txt");
	        rename("tempnew.txt", "umesh.txt");
	        printf("Book deleted successfully.\n");
	    } else {
	        remove("tempnew.txt");
	        printf("Book not found.\n");
	    }
	    printf("\n\nCan you want to delete another book.\n");
	    printf("If yes then enter y other wise continue.\n\n");
	    ch=getche();
	}while(ch == 'Y'||ch == 'y');
    
}

void returnBook() {
    int bookID;
    char bookName[50];
    char writerName[50];
    int found = 0;
    printf("These are the issue book from library only these book can returned from the students: \n\n");
    seeissuse();
    printf("\n\n");

    printf("Enter the Book ID to return: ");
    scanf("%d", &bookID);
    getchar(); // Consume newline character

    printf("Enter the Book Name to return: ");
    fgets(bookName, sizeof(bookName), stdin);
    bookName[strcspn(bookName, "\n")] = '\0'; // Remove newline character

    FILE *issueFile = fopen("umesh1.txt", "r");
    FILE *tempFile = fopen("temp1.txt", "w");

    if (issueFile == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct issuse issue;

    while (fscanf(issueFile, "%d\t\t%s\t\t%s\t\t%s\t\t%lld\t\t%d/%d/%d\t%d/%d/%d\n", 
            &issue.bookno, issue.bookname, issue.studentname, issue.studentaddress, &issue.studentno,
            &issue.iyear, &issue.imonth, &issue.iday, &issue.byear, &issue.bmonth, &issue.bday) != EOF) {
        if (issue.bookno == bookID && strcmp(issue.bookname, bookName) == 0) {
            found = 1;
            printf("Book returned successfully!\n");
        } else {
            fprintf(tempFile, "%d\t\t%s\t\t%s\t\t%s\t\t%lld\t\t%d/%d/%d\t%d/%d/%d\n", 
                    issue.bookno, issue.bookname, issue.studentname, issue.studentaddress, issue.studentno,
                    issue.iyear, issue.imonth, issue.iday, issue.byear, issue.bmonth, issue.bday);
        }
    }

    fclose(issueFile);
    fclose(tempFile);

    if (found) {
        remove("umesh1.txt");
        rename("temp1.txt", "umesh1.txt");

        // Prompt the user to enter the writer's name for the returned book
        printf("Enter the Writer's Name for the returned book: ");
        fgets(writerName, sizeof(writerName), stdin);
        writerName[strcspn(writerName, "\n")] = '\0'; // Remove newline character

        // Add the returned book back to the library file
        FILE *libraryFile = fopen("umesh.txt", "a");
        if (libraryFile == NULL) {
            printf("Error opening library file!\n");
            return;
        }

        // Add book details (ID, name, writer name) to the library file
        fprintf(libraryFile, "%d\t\t%s\t\t%s\n", bookID, bookName, writerName);
        fclose(libraryFile);
    } else {
        remove("temp1.txt");
        printf("Book not found in the issued list!\n");
    }
}


//function for update book
void updatebook() {
    FILE *fp, *temp;
    int id;
    char new_name[100];
    char new_writer[100];
    char line[256];
    int found = 0;

    printf("Enter the Book ID to update: ");
    scanf("%d", &id);
    printf("Enter the new Book Name: ");
    scanf(" %[^\n]", new_name);  // Use %[^\n] to read the entire line including spaces
    printf("Enter the new Writer Name: ");
    scanf(" %[^\n]", new_writer);

    fp = fopen("umesh.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        int book_id;
        char book_name[100];
        char writer_name[100];

        sscanf(line, "%d %[^\t] %[^\n]", &book_id, book_name, writer_name);

        if (book_id == id) {
            fprintf(temp, "%d\t%s\t%s\n", book_id, new_name, new_writer);
            found = 1;
        } else {
            fprintf(temp, "%d\t%s\t%s\n", book_id, book_name, writer_name);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("umesh.txt");
    rename("temp.txt", "umesh.txt");

    if (found) {
        printf("Book name and writer name updated successfully.\n");
    } else {
        printf("Book ID not found.\n");
    }
}

//save password and username in a file

void saveCredentials() {
    FILE *file = fopen("login.txt", "w");
    if (file == NULL) {
        printf("Error saving credentials.\n");
        return;
    }

    fprintf(file, "%s\n%s\n", admin_username, admin_password);
    fclose(file);
}

//enter new password and userrname

void setting() {
    char username[50], password[50];
    printf("Enter new username: ");
    scanf("%s", username);
    printf("Enter new password: ");
    scanf("%s", password);

    strcpy(admin_username, username);
    strcpy(admin_password, password);
    saveCredentials();
    printf("Credentials updated successfully.\n");
}



int main()
{

	char ch;
	int ch1;
	system("cls");
	printf("\n\n\t\t\t********Welcome to the Library mangement system*********\n\n");
	printf("\n\n\t\t\tEnter the password and username for login\n\n\n");
	do
	{
		FILE *file= fopen("login.txt", "r");
	    if (file == NULL)
		{
	        // File does not exist, prompt user to create credentials
	        printf("No existing login file found. Please register:\n");
	        
	        char username[MAX_LENGTH];
		    char password[MAX_LENGTH];
			
			getchar();
		    printf("Enter username: ");
		    fgets(username, MAX_LENGTH, stdin);
		    username[strcspn(username, "\n")] = '\0'; // Remove newline character
		
		    printf("Enter password: ");
		    fgets(password, MAX_LENGTH, stdin);
		    password[strcspn(password, "\n")] = '\0'; // Remove newline character
		
		    FILE *file = fopen("login.txt", "w");
		    if (file == NULL) {
		        printf("Error creating login file.\n");
		        exit(1);
		    }
		
		    fprintf(file, "%s\n%s\n", username, password);
		    fclose(file);
		    printf("Registration successful!\n");
		    break;
	    }
		else
		{
	        fclose(file);
	    }
	    if(loginUser())
	    {
	    	system("cls");
	    	printf("\n\n\n\n\n\t\t\t\t*************************************");
			printf("\n\t\t\t\t* Please enter any key for starting *");
			printf("\n\t\t\t\t*************************************");
			getch();
			do
			{
				system("cls");
				printf("\n\n\t\t\t********Welcome to the library management system*********\n\n");
				printf("\n\n\t\t\tWelcome to the home page.");
				printf("\n\n\n");
				printf("\n\nEnter your choice: \n\n\n");
				printf("ENTER 1: for issuse book page.\n");
				printf("ENTER 2: for return book.\n");
				printf("ENTER 3: for search book.\n");
				printf("ENter 4: for update books.\n");
				printf("ENTER 5: for change book list.\n");
				printf("ENTER 6: for change setting.\n");
				printf("ENTER 7: for exit.\n");
				printf("\n\nEnter the correct choice: ");
				scanf("%d",&ch1);
				switch(ch1)
				{
					case 1:
						{
							char ch;
							do
							{
								int d;
								system("cls");
								printf("\n\n\t\t\t********Welcome to the library management system*********\n\n");
								printf("\t\t\t\t*****Welcome to the issuse page.*****\n\n\n");
								printf("\n\t\t\tENTER 1: For issuse book. ");
								printf("\n\t\t\tENTER 2: For see issuse list. ");
								printf("\n\t\t\tENTER 3: exit.\n");
								printf("\nPlease enter a correct choice.\n");
								scanf("%d",&d);
								switch(d)
								{
									case 1:
										{
											system("cls");
											issuse();
											break;
										}
									case 2:
										{
											system("cls");
											seeissuse();
											break;
										}
									case 3:
										{
											system("cls");
											printf("\t\t\tQuit the program");
											printf("\n\n\t\t\t***Thankyou for using library management system.***\n\n\n");
											exit(0);
											break;
										}
									default:
									{
										printf("\n Error found 404!.\n");
										printf("Please enter the correct choice.\n");
										break;
									}
								}							
							printf("\n\n\n\nDo you want to continue from issuse page?\n");
							printf("please enter y for continue\n\n");
							ch=getche();	
							}while(ch=='y'||ch=='Y');
							break;
						}
					case 2:
						{
							system("cls");
							returnBook();
							break;
						}
					case 3:
						{
							system("cls");
							search();
							break;
						}
					case 4:
						{
							system("cls");
							updatebook();
							break;
						}
					case 5:
						{
							char ch2;
							do
							{
								system("cls");
								printf("\n\n\t\t\t\t***Welcome to the change book list page.****\n\n\n");
								printf("\nENTER 1: for add book in library.\n");
								printf("ENTER 2: for remove book from library.\n");
								printf("ENTER 3: for see book of library.\n");
								printf("ENTER 4: for exit.\n");
								scanf("%d",&ch2);
								switch(ch2)
								{
									case 1:
										{
											system("cls");
											printf("\n\n\t\t\t\t***Welcome to the book add page.****\n\n\n");
											add();	
											break;
										}
									case 2:
										{
											system("cls");
											deletebook();
											break;
										}
									case 3:
										{
											system("cls");
											see();
											break;
										}
									case 4:
										{
											system("cls");
											printf("\t\t\tQuit the program");
											printf("\n\n\t\t\t***Thankyou for using library management system.***\n\n\n");
											break;
										}
									default:
										{
											system("cls");
											printf("\n\n\n\n\n\t\t\t\t Error found 404!.\n");
											printf("\n\n\n\n\n\t\t\t\tEnter the correct choice.\n");
											break;
										}
								}
								printf("\nDo you want to continue in change book list page.?\n");
								printf("If yes then Press y for continue.\n");
								printf("Otherwise press another button.");
								ch=getche();
							}while(ch=='y' || ch=='Y');
							break;
						}
					case 6:
						{
							system("cls");
							setting();
							break;
						}
					case 7:
						{
							system("cls");
							printf("\n\t\t\tQuit the program");
							printf("\n\n\t\t\t***Thankyou for using Library management system.***\n\n\n");
							exit(0);
							break;
						}
					default:
						{
							system("cls");
							printf("\n\nInvalid choice.\n");
							printf("\nplease enter your correct choice.\n");
							break;
						}
						
						
				}
				printf("\n\nDont you want to continue  from home page.\n");
				printf("Press y for continue\n");
				ch1=getche();
			}while(ch1 == 'y' || ch1 == 'Y');
		}
		else
		{
			printf("\n\nIncorrect username and password\n");
			printf("\n\nDont you want to re login.\n");
			printf("Press y for continue\n");
			ch=getche();	
		}
	}while(ch =='y' || ch == 'Y');
	
	
	return 0;	
}
