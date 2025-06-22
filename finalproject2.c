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
	char date[20];
	char backdate[20];
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
	
	getchar();
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

// for issuse a new book from library

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

    printf("\nThese books are available for issuing.\n");

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

            printf("Enter issue date (DD/MM/YYYY): ");
            fgets(newIssue.date, sizeof(newIssue.date), stdin);
            newIssue.date[strcspn(newIssue.date, "\n")] = '\0'; // Remove newline character

            printf("Enter return date (DD/MM/YYYY): ");
            fgets(newIssue.backdate, sizeof(newIssue.backdate), stdin);
            newIssue.backdate[strcspn(newIssue.backdate, "\n")] = '\0'; // Remove newline character

            // Write the new issue to the issue file
            fprintf(issueFile, "%d\t\t%s\t\t%s\t\t%s\t\t%s\n", newIssue.bookno, newIssue.bookname, newIssue.studentname, newIssue.date, newIssue.backdate);
        } else {
            // Write the book to the temp file (book not issued)
            fprintf(tempFile, "%d\t\t\t%s\t\t\t%s\n", book.bookno, book.name, book.writer);
        }
    }

    // Close the files
    fclose(libraryFile);
    fclose(issueFile);
    fclose(tempFile);

    if (bookFound) {
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

// Function for returning a book

void returnBook() {
    FILE *issueFile, *tempIssueFile, *libraryFile;
    struct issuse issue;
    struct library newBook;
    int bookFound = 0;

    issueFile = fopen("umesh1.txt", "r");
    if (issueFile == NULL) {
        printf("Error opening issue file.\n");
        return;
    }

    tempIssueFile = fopen("tempIssue.txt", "w");
    if (tempIssueFile == NULL) {
        printf("Error creating temporary issue file.\n");
        fclose(issueFile);
        return;
    }

    libraryFile = fopen("umesh.txt", "a");
    if (libraryFile == NULL) {
        printf("Error opening library file.\n");
        fclose(issueFile);
        fclose(tempIssueFile);
        return;
    }

    printf("Issued books:\n");
    while (fscanf(issueFile, "%d\t\t%s\t\t%s\t\t%s\t\t%s\n", &issue.bookno, issue.bookname, issue.studentname, issue.date, issue.backdate) != EOF) {
        printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\n", issue.bookno, issue.bookname, issue.studentname, issue.date, issue.backdate);
    }
    rewind(issueFile); // Reset file pointer to the beginning

    printf("\nEnter the Book ID to return: ");
    scanf("%d", &newBook.bookno);
    getchar(); // Consume newline character

    printf("Enter writer name: ");
    fgets(newBook.writer, sizeof(newBook.writer), stdin);
    newBook.writer[strcspn(newBook.writer, "\n")] = '\0'; // Remove newline character

    while (fscanf(issueFile, "%d\t\t%s\t\t%s\t\t%s\t\t%s\n", &issue.bookno, issue.bookname, issue.studentname, issue.date, issue.backdate) != EOF) {
        if (issue.bookno == newBook.bookno) {
            bookFound = 1;
            strcpy(newBook.name, issue.bookname);
            fprintf(libraryFile, "%d\t\t\t%s\t\t\t%s\n", newBook.bookno, newBook.name, newBook.writer);
        } else {
            fprintf(tempIssueFile, "%d\t\t%s\t\t%s\t\t%s\t\t%s\n", issue.bookno, issue.bookname, issue.studentname, issue.date, issue.backdate);
        }
    }

    fclose(issueFile);
    fclose(tempIssueFile);
    fclose(libraryFile);

    if (bookFound) {
        remove("umesh1.txt");
        rename("tempIssue.txt", "umesh1.txt");
        printf("Book returned successfully.\n");
    } else {
        remove("tempIssue.txt");
        printf("Book not found in the issued list.\n");
    }
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
	while(ch != EOF){
		printf("%c",ch);
		ch=fgetc(fp1);
	}
	fclose(fp1);
	printf("\n");
}

//for a adding a new book in library

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
	do
	{
		printf("Enter the number of books to add: ");
	    scanf("%d", &n);
	    getchar(); // Consume newline character
	
	    for (i = 0; i < n; i++) 
		{
	        
	        printf("Enter book number: ");
	        scanf("%d", &new_book.bookno);
	        getchar(); // Consume newline character
	
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
		
		printf("These are the avaliable book in the library.");
    	see();
    printf("only these book are able to delete.");
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


//main funtion

int main()
{
	int s;
	char ch;
	char ch1,ch2;
	printf("Login is necessary for a enter in LMS.\n\n");
	printf("\n\n\tENTER 1: for login.");
	printf("\n\tENTER 2: for exit.\n");
	printf("please enter a correct choice: ");
	scanf("%d",&s);
	switch(s)
	{
		case 1:
			{
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
				    //attemp login
				    if(loginUser())
				    {
//				    	printf("login sucessfully.");
//				    	sleep(2);
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
							printf("ENTER 1: for issuse book.\n");
							printf("ENTER 2: for return book.\n");
							printf("ENTER 3: for search book.\n");
							printf("ENTER 4: for update book list.\n");
							printf("ENTER 5: for change setting.\n");
							printf("ENTER 6: for exit program\n");
							printf("\n\n Enter the correct choice: ");
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
											printf("\n\n\t\t\t********Welcome to the car rental system*********\n\n");
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
										do
										{
											system("cls");
											printf("\n\n\t\t\t\t***Welcome to the book update page.****\n\n\n");
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
											printf("\nDo you want to continue in book update page.?\n");
											printf("If yes then Press y for continue.\n");
											printf("Otherwise press another button.");
											ch=getche();
										}while(ch=='y' || ch=='Y');
										break;
									}
								case 5:
									{
										system("cls");
										setting();
										break;
									}
								case 6:
									{
										system("cls");
										printf("\t\t\tQuit the program");
										printf("\n\n\t\t\t***Thankyou for using library management system.***\n\n\n");
										exit(0);
									}
								default:
								{
									printf("\n Error found 404!.\n");
									printf("please enter the correct choice");
								}
							}
							printf("\n\nDont you want to continue  from home page.\n");
							printf("Press y for continue\n");
							ch=getche();
						}while(ch=='y'||ch=='Y');
					}
					else
					{
						printf("\n\nDo you want to re login.\n");
						printf("If yest then press Y otherwise continue.\n");
					}
					ch=getche();
				}while(ch == 'y' || ch == 'Y');
				
				printf("\n\t\t\tQuit the program");
				printf("\n\n\t\t\t***Thankyou for using Car rental system.***\n\n\n");
				break;
			}
		case 2:
			{
				system("cls");
				printf("\n\t\t\tQuit the program");
				printf("\n\n\t\t\t***Thankyou for using Car rental system.***\n\n\n");
				exit(0);
				break;
			}
		default:
			{
				printf("\n\nEnter correct choice.\n");
			}
	}
	
	
	
	return 0;
}
