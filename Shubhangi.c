#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<time.h>
#include<unistd.h>
#include<ctype.h>

#define SIZE 1024
#define CLEAR "clear"

struct BOOK {
	int id;
	char name[256];
	char Author[256];
	int quantity;
	float Price;
	int rackno;
	char *cat;
};
struct BOOK book;   

char Branches[][15] = {"Computer", "Mechanical", "Civil", "Chemical", "Instrumentation", "Electrical"};
void addBooks(void);
void deleteBooks(void);
void searchBooks(void);
void viewBooks(void);
void editBooks(void);
void mainMenu(void);
void returnfunc(void);
int  getdata(int);
int  checkid(int);
void t_display(void);
void closeApp(void);
void add_window(void);
void returnfunc() {
	printf(" \n Press ENTER to return to Main Menu  ");
	getchar();
	a: 
		if(getchar() == '\n') 
			mainMenu();
		else
			goto a;
}

/* Description :  Exit from the application. */
void closeApp() {
	system(CLEAR);
	t_display();
	printf("Exiting in 1 second...........>\n");
	sleep(1);	
	exit(0);
}


/* Displays the current date and time */
void t_display(void) {
	time_t t;
	time(&t);
	printf("\nDate and time: %s\n", ctime(&t));
}

/* Displays menu for selecting branch */
void add_window(){
   	printf("\n ====================  SELECT CATEGORIES  ==================== \n");
	printf(" ========== 1. Computer\n");
	printf(" ========== 2. Mechanical\n");
	printf(" ========== 3. Civil\n");
	printf(" ========== 4. Chemical\n");
	printf(" ========== 5. Instrumentation\n");
	printf(" ========== 6. Electrical\n");
	printf(" ========== 7. Back to main menu\n");
	printf(" ============================================================\n");
}

/*
	Input : Choice number of selected Branch 
	Output : Returns flag for checking unique id
	Description : The function reads information of BOOK type if ID is valid
*/
int getdata(int choice) {
	int bookID;
	printf("\nEnter the Information Below\n");
	printf("\n Category: ");
	printf("%s", Branches[choice - 1]);
	printf("\n Book ID: ");
	scanf("%d", &bookID);
	if(checkid(bookID) == 0) {
		return 0;
	}
	else {
		book.id = bookID;
		getchar();
		printf("\n Book Name: ");
		fflush(stdout);
		fgets(book.name, 256, stdin);
		fflush(stdin);
	
		printf("\n Author: ");
		fflush(stdout);
		fgets(book.Author, 256, stdin);	
		fflush(stdin);	
		
		printf("\n Quantity: ");
		scanf("%d", &book.quantity);
		printf("\n Price: ");
		scanf("%f", &book.Price);
		printf("\n Rack No: ");
		scanf("%d", &book.rackno);
		return 1;
	}
}

/*
	Input : ID of the book entered by user
	Output: Returns an integer 1 if book ID is valid and 0 if it is invalid (ID must be unique for every book)
*/

int checkid(int t) { 
	FILE *temp;
	temp = fopen("Record.dat", "rb+");
	while(fread(&book, sizeof(book), 1, temp) == 1) {
		if(book.id == t) {
		    fclose(temp);
		    return 0;
		}
	}
        fclose(temp);
        return 1;
}

/*
	Input :	Password and reset password string
	Output : Flag to check for valid input
	Description : Sign up for first time
*/
int adminsignup(char *password, char *temp) {
	FILE *login;
	login = fopen("password.txt", "w");
	if(!strcmp(password, temp)) {
		fwrite(password, 1, sizeof(password), login);
		fclose(login);		
		return 0;
	}
	else {	
		return 1;
	}
}

/* 
	Input : Password string
	Output : Boolean value to check for the valif password
	Description :Login for an administrator every time when using the application 
	
*/
int adminsignin(char *password) {
	FILE *login;
	char tmp[10];
	int cnt;
	login = fopen("password.txt", "r");
	cnt = fread(tmp, sizeof(char), 10, login);	
	tmp[cnt] = '\0';
	if(strcmp(password, tmp) == 0) {	
		return 0;
	}
	else {	
		return 1;
	}
}
void mainMenu() {
	int ch;
	while(1) {
		system(CLEAR);
		t_display();
		printf("\n=======  Library Management System ========\n\n");
		printf("========== 1. Add Books \n");
		printf("========== 2. Delete Books \n");
		printf("========== 3. Search Book \n");
		printf("========== 4. View Book List \n");
		printf("========== 5. Edit Book Record \n");       
		printf("========== 6. Close Application \n");
		printf("\n===========================================\n");
		printf("Enter your choice: ");
		scanf("%d", &ch);
		switch(ch) {
			case 1:
				addBooks();
				break;
		    	case 2:
				deleteBooks();
				break;
		    	case 3:
				searchBooks();
				break;
		    	case 4:
				viewBooks();
				break;
		    	case 5:
				editBooks();
				break;
		    	case 6:
		        	closeApp();
				break;
			default:        	
				break;
        }
    }
}

/*  Add record of book into the file Record.dat */
void addBooks(void) {    
	system(CLEAR);
	FILE *fp;
	int i, choice;
	add_window();
	printf("Enter your choice: ");
	scanf("%d", &choice);
	if(choice == 6) 
		mainMenu();
	system(CLEAR);
	fp = fopen("Record.dat", "ab+");
	if(getdata(choice) == 1) {
		book.cat = Branches[choice - 1];
		fseek(fp, 0, SEEK_END);
		fwrite(&book, sizeof(book), 1, fp);
		fclose(fp);
		printf("The record is sucessfully saved\n");
		printf("Add any more?(Y / N): ");
		getchar();
		if(getchar() == 'n' || 'N')
		    mainMenu();
		else {
		    system(CLEAR);
		    addBooks();
		}
	}
	else {
		getchar();
		printf("The book ID already exists");		
		getchar();
	}
	fclose(fp);
}

/* Delete the record of the book issued from file Record.dat */
void deleteBooks() {    
	FILE *ft, *fp;
	system(CLEAR);
	int book_id, flag = 0;
	printf("\n Enter the Book ID to issue:");
	scanf("%d", &book_id);
	fp = fopen("Record.dat", "rb+");
	if(fp == NULL) {
		printf("No record exists.");
		mainMenu();
	}	
	while(fread(&book, sizeof(book), 1, fp) == 1) {
		if(book.id == book_id) {
			printf("Book name is %s\n", book.name);
			printf("Rack No. is %d\n", book.rackno); 
			flag = 1;
			break;
		}
	}
	ft = fopen("test.dat", "wb+");  //temporary file to save data			
	rewind(fp);
	while(fread(&book, sizeof(book), 1, fp) == 1) {
		if(book.id != book_id) {
		    fwrite(&book, sizeof(book), 1, ft); //write all in tempory file except that we want to delete               
		}
	}
	fclose(fp);
	fclose(ft);
	remove("Record.dat");
	rename("test.dat", "Record.dat"); 
	if(flag == 0) {
		printf("\nNo record is found");		
	}
	else {
		printf("\nThe record is successfully deleted");		
	}	
	printf("\nIssue any more?(Y / N): ");
	getchar();
	if(getchar() == 'n' || 'N')
	    mainMenu();
	else {
	    system(CLEAR);
	    deleteBooks();
	}	
}

/* This function search for the book available in the library by name or by ID */
void searchBooks() {
	system(CLEAR);
	int ch, book_id, flag;
	FILE *fp;
	printf(" ****************** Search Books ********************** \n");
	printf("1. Search By ID\n");
	printf("2. Search By Name\n");
	printf("Enter Your Choice : ");
	scanf("%d", &ch);
	switch(ch) {
		case 1:
			printf(" \n **** Search Books By Id **** \n");
			printf("Enter the book id: ");	
			scanf("%d", &book_id);
			flag = 0;			
			fp = fopen("Record.dat", "rb+");		
			while(fread(&book, sizeof(book), 1, fp) == 1) {		
				if(book.id == book_id) {					
					printf("\n The Book is available \n");
					printf("ID: %d\n", book.id);
					printf("Name: %s\n", book.name);
					printf("Author: %s\n", book.Author);
					printf("Quantity: %d\n", book.quantity);
					printf("Price: Rs.%.2f\n", book.Price);
					printf("Rack No: %d\n", book.rackno);
					flag = 1;
				}	
			}
			if(flag == 0) {  
				printf("\n No Record Found ");
			}
			fclose(fp);
			break;
		case 2:
			flag = 0;
			char book_name[256];
			printf("\n **** Search Books By Name **** \n");
			getchar();
			printf("Enter Book Name: ");
			fflush(stdout);
			fgets(book_name, 256, stdin);
			fflush(stdin);
			fp = fopen("Record.dat", "rb+");
			while(fread(&book, sizeof(book), 1, fp) == 1) {
				if(strcasecmp(book.name, (book_name)) == 0) { 
					printf("\n The book is available \n");
					printf("ID: %d\n", book.id);
					printf("Name: %s\n", book.name);
					printf("Author: %s\n", book.Author);
					printf("Quantity: %d\n", book.quantity);
					printf("Price: Rs.%.2f\n", book.Price);
					printf("Rack No: %d\n", book.rackno);
					flag = 1;	
				}
			}			
			if(flag == 0) {
				printf("\n No Record Found ");
			}		
			fclose(fp);
		    	break;
		default:			
			break;	    
	}
	printf("\nSearch any more? (Y / N): ");
	getchar();
	if(getchar() != 'n') {
		system(CLEAR);
		searchBooks();
	}
	else {
		mainMenu();	
	}
}

/*  This function displays the record of books available in the library */
void viewBooks(void) {  	 
	FILE *fp;
	int  len1, len2, i;	
	char *bn, *ba; 
	system(CLEAR);
	printf(" \n ********************************* Book List *******************************\n\n");
	fp = fopen("Record.dat", "rb");	
	while(fread(&book, sizeof(book), 1, fp) == 1) {			
    		len1 = strlen(book.name); 	
		bn = (char *)malloc(len1 - 1);
		for(i = 0; i < len1; i++) {
			if(book.name[i] == '\n')
				bn[i] = '\0';
			else 
				bn[i] = book.name[i];
    		}
		len2 = strlen(book.Author); 	
		ba = (char *)malloc(len2 - 1); 
		for(i = 0; i < len2; i++) {
			if(book.Author[i] == '\n')
				ba[i] = '\0';
			else
				ba[i] = book.Author[i];
    		}				
		printf(" [%-13s]  [%-3d]  [%-*s]  [%-*s]   [%-5d]   [%-5.2f]   [%-5d] \n", book.cat, book.id, (len1 - 1), bn, (len2 - 2), ba, book.quantity, book.Price, book.rackno);
		free(bn);	
		free(ba); 
	}
	fclose(fp);    
	returnfunc();
}

/* This function updates the information of the book */
void editBooks(void) { 
	system(CLEAR);
	FILE *fp;
	int flag = 0, book_id;
	printf("\n*********  Edit Books Section ********\n");		
	printf("Enter Book Id to be edited: ");
	scanf("%d", &book_id);
	fp = fopen("Record.dat", "rb+");
	while(fread(&book, sizeof(book), 1, fp) == 1) {
		if(checkid(book_id) == 0) {
			printf("\n The book is availble\n");
			printf("The Book ID: %d\n", book.id);
			getchar();
			printf("Enter new name: ");
			fflush(stdout);
			fgets(book.name, 256, stdin);
			fflush(stdin);
			printf("\nEnter new Author: ");
			fflush(stdout);
			fgets(book.Author, 256, stdin);
			fflush(stdin);
			printf("\nEnter new quantity: ");
			scanf("%d", &book.quantity);
			printf("\nEnter new price: ");
			scanf("%f",&book.Price);
			printf("\nEnter new rackno: ");
			scanf("%d",&book.rackno);
			printf("\nThe record is modified");
			fseek(fp, ftell(fp) - sizeof(book), 0);
			fwrite(&book, sizeof(book), 1, fp);
			fclose(fp);
			flag = 1;
		}
	}
	if(flag == 0) {
		printf("\nNo Record Found\n");
	}
	printf("\nModify another Record?(Y/N) :");
	getchar();
	if(getchar() != 'n') {
		system(CLEAR);
		editBooks();
	}
	else {
		mainMenu();	
	}	
}

int main() {
	FILE *login;
	char password[10], temp[10], *t, pwd[10], *tmp;
	int n;
	system(CLEAR);
	login = fopen("password.txt", "rw+");
	if(login == NULL) {		
		printf("\n Database Do not exits. Be an adminstrator. Sign Up\n");
		t = getpass("\nEnter Password :");
		strcpy(password, t);
		t = getpass("\nRe Enter Password :");
		strcpy(temp, t);
		memset(t, 0, strlen(t));
		n = adminsignup(password, temp);
		while(n == 1) {
			system(CLEAR);
			printf("\n Password did not matched! \n");
			t = getpass("\nEnter Password :");
			strcpy(password, t);
			t = getpass("\nRe Enter Password :");
			strcpy(temp, t);
			memset(t, 0, strlen(t));
			n = adminsignup(password, temp);
		}		
	}
	else {	
		t_display();
		printf("\n =========== LOG IN =======================\n");	
		t = getpass("\n Enter Password : ");
		strcpy(pwd, t);
		memset(t, 0, strlen(t));
		n = adminsignin(pwd);
		while(n == 1) {
			printf("\n Password did not matched! \n");
			t = getpass("\nEnter Password :");
			strcpy(pwd, t);
			memset(t, 0, strlen(t));
			n = adminsignin(pwd);	
		}		
	}
	mainMenu();
	return 0;
}
