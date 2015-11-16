#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<time.h>
#include<unistd.h>
#include<ctype.h>

#define SIZE 1024
#define CLEAR "clear"
#define RETURNTIME 15

struct meroDate
{
int mm,dd,yy;
};

struct BOOK {
	int id;
	char name[256];
	char Author[256];
	int quantity;
	float Price;
	int rackno;
	char *cat;
	char findbook;
	char password[10];
	struct meroDate issued;
	struct meroDate duedate;
};

struct BOOK book;   

char Branches[][15] = {"Computer", "Mechanical", "Civil", "Chemical", "Instrumentation", "Electrical"};
void addBooks(void);
void deleteBooks(void);
void searchBooks(void);
void issueBooks(void);
void editBooks(void);
void mainMenu(void);
void issuerecord(void);
void returnfunc(void);
int  getdata(int);
int  checkid(int);
void t_display(void);
void closeApp(void);
void add_window(void);
void Password();
void get_password(char *);
void loaderanim();

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
void issuerecord()  //display issued book's information
{
	struct BOOK a;
	system(CLEAR);
	printf("The Book has taken by Mr. %s",a.name);
	printf("Issued Date:%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
	printf("Returning Date:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
}

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
/*void get_password(char *pass)
{
	char temp_passP[25];
	int i=0;
	while(1) 
	{
        	temp_passP[i] = pass[i];
		/*if(temp_passP[i] == 13) 
		{
			break;	
        	}
	        else if(temp_passP[i] == 8)
	        {
	                if(i!=0) {
	                printf("\b \b");
	                i--;
		        }
			else
			{
				printf("\a");
			}
               }
	        else
		{
		       // printf("*");
	                (pass+i) = temp_passP[i];
	                i++;
	        //}
                //*(pass+i)='\0';
        }
}*/

int change_password() {
	system(CLEAR);
	FILE *login;
    	char password[10];
	char old_pass[10], new_pass[10];
	printf("Enter Old password: ");
	scanf("%s", old_pass);
	printf("\nOld Passwd is : %s", old_pass);
	//get_password(old_pass);
	printf("Enter New password: ");
	scanf("%s", new_pass);
	printf("\n New Passwd is : %s", new_pass);
	//get_password(new_pass);
	//login = fopen("password.dat","ab+");
	//while(fread(&password,sizeof(password),1,login) == 1) {
       // if(strcmp(old_pass,password) == 0) {
           // strcpy(password,new_pass);
           // fseek(login,-sizeof(password),SEEK_CUR);
            //fwrite(&password,sizeof(password),1,login);
            //fclose(login);
            printf("\n*** Password successfully changed! ***");
          return 1;
       // } 
	//else {
            //printf("Password changing process failed!");
           return 0;




}
/*void loaderanim()
{
int loader;
system(CLEAR);
printf("\n\n");
for(loader=1;loader<20;loader++)
{
Sleep(100);
printf("%c",219);}
}*/
void mainMenu() {
	int ch;
	while(1) {
		system(CLEAR);
		t_display();
		printf("\n=======  Library Management System ========\n\n");
		printf("========== 1. Add Books \n");
		printf("========== 2. Delete Books \n");
		printf("========== 3. Search Book \n");
		printf("========== 4. Issue Books\n");
		printf("========== 5. Edit Book Record \n");
		printf("========== 6. Change password\n");       
		printf("========== 7. Close Application \n");
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
				issueBooks();
				break;
			case 5:
				editBooks();
				break;
			case 6:
				change_password();
				printf("press any key to continue....");
				break;
		    	case 7:
		        	closeApp();
				break;
			case 8: 
				system(CLEAR);
				printf("\t LIBRARY MANAGEMENT SYSTEM");
				printf("\t MINI PROJECT IN C");
				printf("\t is brought to you by");
				printf("\t code with C");
				printf("\t ************************");
				printf("\t ************************");
				printf("\t ************************");
				printf("\t Existing in 2 seconds");
				exit(0);
				
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
	fp = fopen("Record.dat", "rb+");
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
	char c;
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
			char c;
			char book_name[256];
			printf("\n **** Search Books By Name **** \n");
			scanf("%c", &c);
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
			{
			mainMenu();	
		        }	
		default:			
			break;	    
			}
			printf("\nSearch any more? (Y / N): ");
			scanf("%c", &c);
			if(c != 'n') {
			system(CLEAR);
			searchBooks();
			}
		else {
			mainMenu();	
		}
}

void issueBooks(void)  //function that issue books from library
{
	int t, x;
	char c;
	struct BOOK a;
	system(CLEAR);
	printf("\n********************************ISSUE SECTION**************************\n\n");
	printf(" 1. Issue a Book \n");
	printf(" 2. View Issued Book\n");
	printf(" 3. Search Issued Book\n");
	printf(" 4. Remove Issued Book\n");
	printf("Enter a Choice:");
	scanf("%d", &x);
	switch(x)
	{
		case 1:  //issue book
			{
			system(CLEAR);
			int c=0;
			int t;
			FILE *fp;
			FILE *fs;
			char another = 'y';
			//while(another == 'y') {
				system(CLEAR);
				printf("***Issue Book section***\n");
				printf("\nEnter the Book Id\n");	
				scanf("%d",&t);
				fp = fopen("Record.dat","ab+");
				fs = fopen("Issue.dat","ab+");
				if(c == 0) //issues those which are present in library
				{
					printf("\nThe book record is available");
					printf("\nThere are %d unissued books in library ",a.quantity);
					printf("\nThe name of book is %s",a.name);
					printf("\nEnter student name:");
					scanf("%s",a.name);
					//struct dosdate_t d; //for current date
					//getdate(&d);	
					//a.issued.dd=d.day;	
					//a.issued.mm=d.month;
					//a.issued.yy=d.year;
					//printf("Issued date = %d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
					printf("\nThe BOOK of ID %d is issued",t);
					//a.duedate.dd = a.issued.dd+RETURNTIME;   //for return date
					//a.duedate.mm = a.issued.mm;
					//a.duedate.yy = a.issued.yy;
					//if(a.duedate.dd > 30) {
					//	a.duedate.mm += a.duedate.dd/30;
					//	a.duedate.dd -= 30;
	//
	//				}
	//				if(a.duedate.mm > 12) {
	//					a.duedate.yy += a.duedate.mm/12;
	//					a.duedate.mm -= 12;
	//				}
	//				printf("To be return:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
					fseek(fs,sizeof(a),SEEK_END);
					fwrite(&a,sizeof(a),1,fs);
					fclose(fs);
				 }
				if(c != 0)
				{
					printf("No record found");
				}
				fclose(fp);
			

				break;
			}
		case 2:  //show issued book list
			{
			system(CLEAR);
			FILE *fs;
			int j=4;
			printf("*******************************Issued book list*******************************\n");
			printf("STUDENT NAME    CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE");
			fs=fopen("Issue.dat","rb");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
				printf("%s",a.name);
				printf("%s",a.cat);
				printf("%d",a.id);
				printf("%s",a.name);
				printf("%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy );
				printf("%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
			//struct dosdate_t d;
			//_dos_getdate(&d);
			//            printf("Current date=%d-%d-%d",d.day,d.month,d.year);
			j++;

			}
			fclose(fs);
			returnfunc();
			}
			break;
		case 3:   //search issued books by id
			{
			system(CLEAR);
			printf("Enter Book ID:");
			scanf("%d", &a.id);
			int p;//c = 0;
			FILE *fs;
			char another = 'y';
			while(another == 'y')
			{

			scanf("%d",&p);
			fs = fopen("Issue.dat","rb");
			while(fread(&a,sizeof(a),1,fs) == 1)
			{
			if(a.id == p)
			{
			issuerecord();
			printf("Press any key.......");
			scanf("%c", &c);
			issuerecord();
			c = 1; 
			}

			}
			fclose(fs);
			if(c == 0)
			{
			printf("No Record Found");
			}
			printf("Try Another Search?(Y/N)");
			scanf("%c", &c);
			another = c;
			}
			}
			break;
		case 4:  //remove issued books from list
			{
			system(CLEAR);
			int b;
			char findbook;
			FILE *fg;  //declaration of temporary file for delete
			char another = 'y';
			while(another == 'y')
			{
			printf("Enter book id to remove:");
			scanf("%d",&b);
			struct meroDate issued;
			struct meroDate duedate;
			fg = fopen("Bibek.dat","a+");
			while(fread(&a,sizeof(a),1,fg) == 1)
			{
			if(a.id == b)
			{
			issuerecord();
			findbook = 't';
			}
			if(findbook == 't')
			{
			printf("Do You Want to Remove it?(Y/N)");
			scanf("%c", &c);
			if(c == 'y')
			{
			fg = fopen("Bibek.dat","a+");
			rewind(fg);
			while(fread(&a,sizeof(a),1,fg) == 1)
			{
			if(a.id != b)
			{
			fseek(fg,0,SEEK_CUR);
			fwrite(&a,sizeof(a),1,fg);
			}
			}
			fclose(fg);
			fclose(fg);
			remove("Issue.dat");
			rename("Bibek.dat","Issue.dat");
			printf("The issued book is removed from list");

			}

			}
			if(findbook != 't')
			{
			printf("No Record Found");
			}
			}
			printf("Delete any more?(Y/N)");
			scanf("%c", &c);
			another = c;
			}
			}
		default:
			printf("\aWrong Entry!!");
			scanf("%c", &c);
			issueBooks();
			break;
}
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
		printf("\n Database Do not exits. Be an administrator. Sign Up\n");
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
	else
            {	
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

