//                                   ---------------------------- RETAIL MANAGEMENT SYSTEM ---------------------------

#include <stdio.h>
#include <windows.h> //This header file contains the SetConsoleCursorPosition(HANDLE,COORD) which handles the cursor position on the screen
#include <stdlib.h>  //This header file has  system("CLS") which clears the console screen
#include <conio.h>
#include <ctype.h>
#include <time.h>

typedef struct       //Structure used for storing the product name, quanity, price and ID
{
    char name[30], code[5];
    float rate;
    int quantity;
} rec;
rec item;

struct id_entry      //Structure used for storing the id's the customer selected to purchase
{
    int id[50];
} c;

//Global Variables
FILE *fp, *fp1, *famt, *fname; //file pointers
int no_of_items;               //number of items customer chose to buy
int final_amount;              //final amount of the products purchased
char name[30];                 //customer name
char phone_number[10];         //customer phone number

void outputcursorposition(int x, int y); //user-defined function for the desired cursor position on the output screen

void welcome_options();

//retailer and customer entry point
void entry_customer(); // Taking the customer details
void login_retailer(); //login page of retailer

//display functions
void display_main();             //main display function
void display_heading();          //sub-function of display(headings)
void display_file(int i, int j); //retreiving from file and displaying
void thankyou_display();         //Thank-you display function

//Retailer use-case functions
void display_retailer();  //main menu of the retailer
void add_stock();         //adding the stock to products
void add();               //adding new products to the stock
void add_check(char y[]); //checking whether the code already exists in the catalogue or not
void search_main();       //main function of searching ,displaying the options available for search
void search_id();         //searching by id of product
void search_price();      //searching by price of the product
void search_quantity();   //searching by quantity of the product
void search_name();       //search by name of the product

//Customer use-case functions
void customer_menu();           //main menu of the customer
int item_menu_customer();       //displaying items to the customer
void cus_item_display();        //retrieving items from file to display to customer
void deduct_stock(int, char[]); //deducting the user entered stock
int check_quantity(int);        //checks the stock of the particular ID of product
void customer_purchase(int);    //purchasing the selected items
int calculate_amt(int, char[]); //caluclates the total amount of the iteams purchased
void box_invoice();             //borders of the invoice function
void display_invoice();         //customer invoice main function

void outputcursorposition(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void welcome_options()
{
    system("CLS");

    int choice;
    
    outputcursorposition(74, 15);
    printf("    \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN-MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(74, 18);
    printf("\t\t   1. RETAILER   ");
    
    outputcursorposition(74, 20);
    printf("\t\t   2. CUSTOMER    ");
    
    outputcursorposition(74, 22);
    printf("\t\t   3. EXIT   ");
    
    outputcursorposition(74, 25);
    printf("    \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    outputcursorposition(74, 28);
    printf("    ENTER YOUR CHOICE : ");
    scanf("%d", &choice);
    
    switch (choice)
    {
    case 1:
        login_retailer();
        break;

    case 2:
        entry_customer();
        break;

    case 3:
        thankyou_display();
        break;

    default:
        printf("INVALID ENTRY!");
        break;
    }
}

void entry_customer()
{
    system("CLS");

    char temp_ph[10];
    int counter = 1;
    
    outputcursorposition(74, 15);
    printf("    \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SIGN-IN \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(74, 24);
    printf("    \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(74, 17);
    printf("            Please enter your details");
    
    outputcursorposition(74, 19);
    printf("      Enter your name: ");
    getchar();
    gets(name);
    
    outputcursorposition(74, 21);
    printf("      Enter your phone number: ");
    gets(phone_number);
    
    
    strcpy(temp_ph, phone_number);
    
    for (int i = 0; temp_ph[i] != '\0'; i++)
    {
        if (temp_ph[i] == '0' || temp_ph[i] == '1' || temp_ph[i] == '2' || temp_ph[i] == '3' || temp_ph[i] == '5' || temp_ph[i] == '6' || temp_ph[i] == '7' || temp_ph[i] == '8' || temp_ph[i] == '9')
        {
            counter = counter + 1;
        }
    }
    
    if (counter == 10 && strlen(temp_ph)) 
    {
        outputcursorposition(74, 26);
        printf("      Press any key to view the catalogue: ");
        getch();
        
        customer_menu();
    }
    
    else
    {
        outputcursorposition(68, 26);
        printf("       INVALID PHONE NUMBER, ENTER YOUR DETAILS AGAIN !");
        
        outputcursorposition(74, 28);
        printf("\t   PRESS ANY KEY TO ENTER AGAIN : ");
        getchar();
        
        entry_customer();
    }
}

void login_retailer()
{
    system("CLS");
    
    char pass[13] = "miniproject", inputpass[30], input_char;
    int counter = 0, count = 0;
    
    outputcursorposition(74, 15);
    printf("    \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 LOGIN \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(74, 23);
    printf("    \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    

    outputcursorposition(72, 18);
    printf("\t         ENTER THE PASSWORD ");
    
    outputcursorposition(92, 20);
    while (input_char != 13)
    {
        input_char = getch();
        
        if (input_char != 13 && input_char != 8)
        {
            printf("*");
            inputpass[counter] = input_char;
            counter++;
        }
        
        else if (input_char == 8) //backspace ASCII
        {
            if (counter > 0)
            {
                counter--;
                inputpass[counter] = '\0';
                printf("\b \b"); // \b is a backspace
            }
        }
        
        if (input_char == 13) //CR(carriage return) , which is not supposed to be a password character
        {
            break;
        }
    }
    
    inputpass[counter] = '\0';
    outputcursorposition(74, 31);
    
    if (strcmp(inputpass, pass) == 0)
    {
        display_retailer();
    }

    else
    {
        outputcursorposition(74, 26);
        printf("\t\tINCORRECT PASSWORD !!");
        
        outputcursorposition(60, 28);
        printf("\t\t      PRESS ANY KEY TO RE-ENTER THE PASSWORD : ");
        getch();
        login_retailer();
    }
}

void display_retailer()
{
    system("CLS");

    int choice;

    outputcursorposition(64, 11);
    printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 OPTION-CATALOGUE \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(64, 14);
    printf("\t\t\t  1. VIEW STOCK");
    
    outputcursorposition(64, 16);
    printf("\t\t\t  2. ADD NEW PRODUCTS");
    
    outputcursorposition(64, 18);
    printf("\t\t\t  3. SEARCH A PRODUCT");
    
    outputcursorposition(64, 20);
    printf("\t\t\t  4. ADD STOCK ");
    
    outputcursorposition(64, 22);
    printf("\t\t\t  5. GO BACK TO MAIN");
    
    outputcursorposition(64, 24);
    printf("\t\t\t  6. EXIT");
    
    outputcursorposition(64, 27);
    printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(70, 30);
    printf("ENTER YOUR CHOICE : ");
    scanf("%d", &choice);
    
    switch (choice)
    {
    case (1):
        display_main();
        break;

    case (2):
        add();
        break;

    case (3):
        search_main();
        break;

    case (4):
        add_stock();
        break;

    case (5):
        welcome_options();
        break;

    case (6):
        thankyou_display();
        break;

    default:
        printf("INVALID ENTRY!");
        break;
    }
}

void display_heading()
{
    int i;
    
    outputcursorposition(64, 9);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ITEM DETAILS \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(64, 14);
    printf("   S.No.     Item Name     Item ID        Price       Quantity left");
}

void display_file(int i, int j)
{
    outputcursorposition(64, i - 10);
    printf("%4d", j);
    printf("%17s", item.name);
    printf("%12s", item.code);
    printf("%14.2f", item.rate);
    printf("%13d", item.quantity);
}

void display_main()
{
    system("CLS");

    int i = 26, j = 1;
    FILE *file;
    
    display_heading();
    
    file = fopen("record.txt", "rb");
    rewind(file);
    fflush(file);
    
    while (fread(&item, sizeof(item), 1, file))
    {
        display_file(i, j);
        i++;
        j++;
    }

    if (i == 26)
    {
        outputcursorposition(65, 20);
        printf("\t\t\tSTOCK IS EMPTY");
    }

    fclose(file);
    
    outputcursorposition(64, 33);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(64, 36);
    printf("Press any key to go back to catalogue: ");
    getch();
    
    display_retailer();
}

void add_stock()
{
    system("CLS");

    FILE *file;
    char id[20];
    int stock;
    
    outputcursorposition(64, 11);
    printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ADDING STOCK \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    file = fopen("record.txt", "rb+");
    rewind(file);
    
    outputcursorposition(64, 14);
    printf("      Enter product ID: ");
    scanf("%s", id);
    fflush(file);
    
    while (fread(&item, sizeof(item), 1, file) == 1)
    {
        if ((strcmp(item.code, id) == 0))
        {
            outputcursorposition(64, 17);
            printf("      Stock available is: %d", item.quantity);
            
            outputcursorposition(64, 20);
            printf("      Would you like to add stock [Y/N]: ");
            
            if (toupper(getche()) == 'Y')
            {
                outputcursorposition(64, 22);
                printf("      Enter the new stock to be added: ");
                scanf("%d", &stock);
                
                int size = sizeof(item.quantity);
                item.quantity += stock;
                
                fseek(file, -size, 1);
                fwrite(&item.quantity, sizeof(item.quantity), 1, file);
                fclose(file);
                
                outputcursorposition(64, 25);
                printf("      Stock available now is: %d", item.quantity);
                
                outputcursorposition(64, 28);
                printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            }
            
            else
            {
                break;
            }
        }
        else
        {
            outputcursorposition(64, 17);
            printf("      PRODUCT NOT FOUND");
        }
    }

    outputcursorposition(74, 31);
    printf("      Press any key to go back to catalogue: ");
    getch();
    display_retailer();
}

void add()
{
    system("CLS");

    FILE *file;
    char y[20], x[12];

    outputcursorposition(64, 11);
    printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ADD NEW PRODUCT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(64, 14);
    printf("      Would you like to add a new product [Y/N]: ");

    while (toupper(getche()) == 'Y')
    {
        getchar();
        Sleep(1500);
        getchar();
        
        file = fopen("record.txt", "ab");
        
        system("CLS");
        
        add_check(y);
        
        strcpy(item.code, y);
        
        outputcursorposition(64, 17);
        printf("      Enter name of the item: ");
        scanf("%s", item.name);
        
        outputcursorposition(64, 19);
        printf("      Enter rate of the item: ");
        scanf("%f", &item.rate);
        
        outputcursorposition(64, 21);
        printf("      Enter quantity of the item: ");
        scanf("%d", &item.quantity);
        
        outputcursorposition(64, 24);
        printf("      New product added !!");

        outputcursorposition(64, 27);
        printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        
        fseek(file, 0, SEEK_END);
        fwrite(&item, sizeof(item), 1, file);
        fclose(file);
        
        outputcursorposition(64, 30);
        printf("      Would you like to add another product [Y/N]: ");
    }
    
    display_retailer();
}

void add_check(char y[])
{
    int flag;
    FILE *file;
    file = fopen("record.txt", "rb");
    
    while (1)
    {
        system("CLS");
        
        flag = 1;

        outputcursorposition(64, 11);
        printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ADD PRODUCT DETAILS \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        
        rewind(file);
        
        outputcursorposition(64, 14);
        printf("      Enter ID of the product: ");
        scanf(" %[^\n]", y);
        
        while (fread(&item, sizeof(item), 1, file) == 1)
        {
            if (strcmp(y, item.code) == 0)
            {
                flag = 0;
                
                outputcursorposition(64, 16);
                printf("      Code already exists...");
                
                outputcursorposition(64, 20);
                printf("      Press any key to enter a different ID: ");
                getch();
                
                break;
            }
        }
        
        if (flag == 1)
        {
            break;
        }
    }
    
    fclose(file);
}

void search_main()
{
    system("CLS");

    char ch;
    int choice;

    outputcursorposition(64, 11);
    printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SEARCHING A PRODUCT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(64, 14);
    printf("\t\t\t   1. SEARCH BY ID");
    
    outputcursorposition(64, 16);
    printf("\t\t\t   2. SEARCH BY PRICE");
    
    outputcursorposition(64, 18);
    printf("\t\t\t   3. SEARCH BY QUANTITY");
    
    outputcursorposition(64, 20);
    printf("\t\t\t   4. SEARCH BY NAME");
    
    outputcursorposition(64, 22);
    printf("\t\t\t   5. GO BACK TO CATALOGUE");
    
    outputcursorposition(64, 25);
    printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(64, 28);
    printf("      ENTER YOUR CHOICE : ");
    scanf("%d", &choice);
    
    switch (choice)
    {
    case (1):
        search_id();
        break;

    case (2):
        search_price();
        break;

    case (3):
        search_quantity();
        break;

    case (4):
        search_name();
        break;

    case (5):
        display_retailer();
        break;

    default:
        break;
    }
}

void search_id()
{
    system("CLS");

    int i = 26, j = 1;
    char x[10] = {0};
    FILE *file;
    
    outputcursorposition(64, 11);
    printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SEARCHING BY ID \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    file = fopen("record.txt", "rb");
    rewind(file);
    
    outputcursorposition(64, 14);
    printf("      Enter item code: ");
    scanf("%s", x);
    
    fflush(file);
    
    while (fread(&item, sizeof(item), 1, file))
    {
        if ((strcmp(item.code, x) == 0))
        {
            system("CLS");
            display_heading();
            display_file(i, j);
            i++;
            j++;
        }
    }
    
    if (i == 26)
    {
        outputcursorposition(64, 17);
        printf("      PRODUCT NOT FOUND...");
    }
    
    outputcursorposition(74, 23);
    printf("      Enter any key to go back  : ");
    getch();
    
    fclose(file);
    
    search_main();
}

void search_price()
{
    system("CLS");

    int i = 26, j = 1;
    float a, b;
    FILE *file;
    
    outputcursorposition(64, 11);
    printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SEARCHING BY PRICE \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    file = fopen("record.txt", "rb");
    rewind(file);
    
    outputcursorposition(64, 14);
    printf("      Enter lower limit of range of price: ");
    scanf("%f", &a);

    outputcursorposition(64, 16);
    printf("      Enter upper limit of range of price: ");
    scanf("%f", &b);
    
    fflush(file);

    system("CLS");
    
    while (fread(&item, sizeof(item), 1, file))
    {
        if (item.rate >= a && item.rate <= b )
        {
            display_heading();
            display_file(i, j);
            i++;
            j++;
        }
    }
    
    if (i == 26)
    {
        outputcursorposition(64, 11);
        printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SEARCHING BY PRICE \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        outputcursorposition(64, 15);
        printf("      PRODUCT NOT FOUND");
    }
    
    outputcursorposition(74, 25);
    printf("      Press any key to go to back  : ");
    getch();
    
    fclose(file);
    
    search_main();
}

void search_quantity()
{
    system("CLS");
    
    int i = 26, j = 1;
    int a, b;
    FILE *file;

    outputcursorposition(64, 11);
    printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SEARCHING BY QUANTITY \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    file = fopen("record.txt", "rb");
    rewind(file);
    
    outputcursorposition(64, 14);
    printf("      Enter lower limit of range of quantity: ");
    scanf("%d", &a);

    outputcursorposition(64, 16);
    printf("      Enter upper limit of range of quantity: ");
    scanf("%d", &b);
    
    fflush(file);

    system("CLS");
    
    while (fread(&item, sizeof(item), 1, file))
    {
        if (item.quantity >= a && item.quantity <= b )
        {
            display_heading();
            display_file(i, j);
            i++;
            j++;
        }
    }
    
    if (i == 26)
    {
        outputcursorposition(64, 11);
        printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SEARCHING BY QUANTITY \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        outputcursorposition(64, 15);
        printf("      PRODUCT NOT FOUND");
    }

    outputcursorposition(74, 25);
    printf("      Press any key to go back  : ");
    getch();
    
    fclose(file);

    search_main();
}

void search_name()
{
    system("CLS");

    int i = 26, j = 1;
    char name[10];
    FILE *file;
    
    outputcursorposition(64, 11);
    printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SEARCHING BY NAME \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    file = fopen("record.txt", "rb");
    rewind(file);
    
    outputcursorposition(64, 14);
    printf("      Enter item name: ");
    scanf("%s", name);
    
    fflush(file);
    
    while (fread(&item, sizeof(item), 1, file))
    {
        if ((strcmp(item.name, name) == 0))
        {
            system("CLS");    
            display_heading();
            display_file(i, j);
            i++;
            j++;
        }
    }
    
    if (i == 26)
    {
        outputcursorposition(64, 17);
        printf("      PRODUCT NOT FOUND...");
    }
    
    outputcursorposition(74, 23);
    printf("      Enter any key to go back  : ");
    getch();
    
    fclose(file);
    
    search_main();
}

void customer_menu()
{
    system("CLS");
    
    struct id_entry c;
    int input_choice, x;
    
    outputcursorposition(64, 11);
    printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 OPTION-CATALOGUE \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(64, 14);
    printf("\t\t   1. VIEW THE CATALOGUE OF ITEMS    ");
    
    outputcursorposition(64, 16);
    printf("\t\t   2. PURCHASE SECTION OF SELECTED ITEMS   ");
    
    outputcursorposition(64, 18);
    printf("\t\t   3. GET INVOICE  ");
    
    outputcursorposition(64, 20);
    printf("\t\t   4. GO BACK TO MAIN  ");
    
    outputcursorposition(64, 22);
    printf("\t\t   5. EXIT  ");
    
    outputcursorposition(64, 25);
    printf("      \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    outputcursorposition(64, 28);
    printf("      ENTER YOUR CHOICE : ");
    scanf("%d", &input_choice);
    
    switch (input_choice)
    {
    case 1:
        item_menu_customer();
        break;

    case 2:
        customer_purchase(no_of_items);
        break;

    case 3:
        display_invoice();
        break;
    case 4:
        welcome_options();
        break;
    case 5:
        thankyou_display();
        break;
    default:
        printf("INVALID ENTRY!");
        break;
    }
}

int item_menu_customer()
{
    system("CLS");
    
    int in;

    outputcursorposition(60, 5);
    cus_item_display();
    
    outputcursorposition(60, 32);
    printf("\t\t     WOULD YOU LIKE TO MAKE PURCHASE ? [Y/N] : ");

    if (getchar() == 'Y' || getchar() == 'y')
    {
        fname = fopen("item_name.txt", "w+");
        famt = fopen("item_amounts.txt", "w+");
        
        fclose(fname);
        fclose(famt);
        
        outputcursorposition(60, 35);
        printf("\t ENTER THE NUMBER OF ITEMS YOU WANT TO PURCHASE : ");
        scanf("%d", &no_of_items);
        
        outputcursorposition(60, 37);
        printf("\t ENTER THE PRODUCT ID(s) : ");
        
        for (int i = 0; i < no_of_items; i++)
        {
            scanf("%d", &c.id[i]);

        }

        outputcursorposition(60, 39);
        printf("\t PRESS 1 TO PROCEED TO PURCHASE SECTION, PRESS 2 TO RETURN BACK TO THE CATALOGUE : ");
        scanf("%d", &in);
        
        if (in == 1)
        {
            customer_purchase(no_of_items);
        }
        
        else
        {
            customer_menu();
        }
    }
    
    else
    {
        outputcursorposition(64, 34);
        printf("      PRESS ANY KEY TO RETURN BACK TO MAIN MENU :");
        getch();

        customer_menu();
    }
    
    return no_of_items;
}

void cus_item_display()
{
    FILE *fp, *file;
    int i = 26, j = 1;
    
    fopen("record.txt", "rb");

    display_heading();

    file = fopen("record.txt", "rb");
    rewind(file);
    fflush(file);
    
    while (fread(&item, sizeof(item), 1, file))
    {
        display_file(i, j);
        i++;
        j++;
        
        if ((j % 20) == 0)
        {
            outputcursorposition(64, 30);
            printf("Press any key to see more....");
            
            getch();
            system("CLS");
            
            display_heading();
            
            i = 26;
            
            continue;
        }
    }

    if (i == 26)
    {
        outputcursorposition(60, 18);
        printf("\t\t\tSTOCK IS EMPTY");
    }
    
    fclose(file);
    
    outputcursorposition(64, 30);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
}

void deduct_stock(int stock, char temp[10])
{
    fp = fopen("record.txt", "rb+");
    
    while (fread(&item, sizeof(item), 1, fp) == 1)
    {
        if (strcmp(item.code, temp) == 0)
        {
            int size = sizeof(item.quantity);
            
            item.quantity -= stock;
            
            fseek(fp, -size, 1);
            fwrite(&item.quantity, sizeof(item.quantity), 1, fp);
            
            fclose(fp);
        }
    }
}

int check_quantity(int i)
{
    char code[10], temp[10];
    
    itoa(c.id[i], code, 10);
    strcpy(temp, code);
    
    fp = fopen("record.txt", "rb");
    
    while (fread(&item, sizeof(item), 1, fp))
    {
        if (strcmp(item.code, temp) == 0)
        {
            return item.quantity;
        }
    }
    
    fclose(fp);
}

void customer_purchase(int num)
{
    system("CLS");

    char code[10], temp[10];
    int input, ypos = 15;

    fp1 = fopen("inputquantity.txt", "w+");
    
    outputcursorposition(62, 11);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PURCHASE \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    outputcursorposition(64, 14);
    printf("             ENTER THE QUANITY OF ITEMS YOU WISH TO PURCHASE : ");

    outputcursorposition(64, 16);
    for (int i = 0; i < num; i++)
    {
    stock:
        ypos = ypos + 2;
        outputcursorposition(62, ypos);
        printf(" ITEM ID: %d  -  QUANTITY AVAILABLE : %d ", c.id[i], check_quantity(i));
        printf("  ------>  ENTER QUANTITY : ");
        scanf("%d", &input);
        
        itoa(c.id[i], code, 10);
        strcpy(temp, code);

        if (check_quantity(i) < input)
        {
            outputcursorposition(64, ypos + 2);
            printf(" \t           STOCK INSUFFICIENT !!");
            
            outputcursorposition(64, ypos + 4);
            printf("\t  WOULD YOU LIKE TO MAKE CHANGES IN THE QUANTITY YOU ENTERED? [Y/N] ");

            if (getchar() == 'Y' || getchar() == 'y')
            {
                ypos = ypos + 4;
                goto stock;
            }
            
            else
            {
                ypos = ypos + 4;
                printf("_______________________________________________________________________");
                
                continue;
            }
        }
        
        else if (check_quantity(i) >= input)
        {
            ypos = ypos + 2;
            
            outputcursorposition(64, ypos);
            printf("_______________________________________________________________________");
            fprintf(fp1, "%d\n", input);
            
            deduct_stock(input, temp);
            calculate_amt(input, temp);
        }
    }
    outputcursorposition(64,32);
    printf("Press any key to go back to main : ");
    getch();
    customer_menu();
    
    fclose(fp1);
}

int calculate_amt(int stock, char id[10])
{
    int item_amt = 0;
    
    fp = fopen("record.txt", "rb+");
    famt = fopen("item_amounts.txt", "a+");
    fname = fopen("item_name.txt", "a+");

    while (fread(&item, sizeof(item), 1, fp) == 1)
    {
        if (strcmp(item.code, id) == 0)
        {
            item_amt = stock * item.rate;
            
            fprintf(famt, "%d\n", item_amt);
            fprintf(fname, "%s\n", item.name);
            
            fclose(fp);
            fclose(famt);
            fclose(fname);
        }
    }
    
    final_amount += item_amt;
}

void box_invoice()
{
    system("CLS");
    
    int i;
    
    outputcursorposition(76, 3);
    printf("--------------- INVOICE ---------------");

    outputcursorposition(66, 7);
    printf("NAME: %s", name);

    outputcursorposition(105, 7);
    printf(" DATE: %s", __DATE__);

    outputcursorposition(66, 9);
    printf("CONTACT NO.: %s", phone_number);

    outputcursorposition(105, 9);
    printf(" TIME: %s", __TIME__);

    outputcursorposition(65, 11);
    for (int i = 0; i < 60; i++)
    {
        printf("\xcd");
    }

    outputcursorposition(65, 12);
    for (i = 0; i < 19; i++)
    {
        outputcursorposition(65, i + 12);
        printf("\xba");
    }

    outputcursorposition(65, 31);
    for (int i = 0; i < 60; i++)
    {
        printf("\xcd");
    }

    outputcursorposition(125, 12);
    for (i = 0; i < 19; i++)
    {
        outputcursorposition(125, i + 12);
        printf("\xba");
    }

    outputcursorposition(65, 11);
    printf("\xc9");

    outputcursorposition(125, 11);
    printf("\xbb");

    outputcursorposition(65, 31);
    printf("\xc8");

    outputcursorposition(125, 31);
    printf("\xbc");

    outputcursorposition(66, 13);
    for (int i = 0; i < 59; i++)
    {
        printf("\xcd");
    }

    outputcursorposition(66, 12);
    printf(" S.NO.\t\tPRODUCT NAME\t\t  TOTAL PRICE");
}

void display_invoice()
{

    char names[20][20], id[20][20], name[20];
    int amount[20], i = 0, j = 0, k = 0;
    int amt, ypos = 15, ypos1 = 15;
    float total;

    fname = fopen("item_name.txt", "r");
    famt = fopen("item_amounts.txt", "r");

    while (fgets(name, sizeof(name), fname) != NULL)
    {
        strcpy(names[i], name);
        i++;
    }
    
    while (fscanf(famt, "%d\n", &amt) != EOF)
    {
        amount[k] = amt;
        k++;
    }
    
    fclose(fname);
    fclose(famt);

    box_invoice();

    for (int q = 0; q < i; q++)
    {
        outputcursorposition(66, ypos);
        printf("%4d %24s", q + 1, names[q]);
        
        ypos = ypos + 2;
    }
    
    for (int q = 0; q < i; q++)
    {
        outputcursorposition(105, ypos1);
        printf("%13d", amount[q]);
        
        ypos1 = ypos1 + 2;
    }

    outputcursorposition(66, 27);
    {
        for (i = 0; i < 59; i++)
        {
            printf("-");
        }
    }
    
    total = final_amount;

    outputcursorposition(76, 29);
    printf("        TOTAL AMOUNT : %.2f", total);

    outputcursorposition(70, 33);
    printf("------------ THANK YOU FOR PURCHASING -------------");
    
    outputcursorposition(72, 37);
    printf("Press any key to go back to Option-Catalogue : ");
    getch();
    
    customer_menu();
}

void thankyou_display()
{

    system("CLS");

    for (int i = 5; i <= 40; i++)
    {
        outputcursorposition(15, i);
        printf("\xB2");
        
        outputcursorposition(15, i);
        printf("\xB2");
        
        outputcursorposition(170, i);
        printf("\xB2");
        
        outputcursorposition(170, i);
        printf("\xB2");
    }

    for (int i = 15; i < 170; i++)
    {
        outputcursorposition(i, 5);
        printf("\xB2\xB2");
        
        outputcursorposition(i, 5);
        printf("\xB2\xB2");
        
        outputcursorposition(i, 40);
        printf("\xB2\xB2");
        
        outputcursorposition(i, 40);
        printf("\xB2\xB2");
    }

    outputcursorposition(32, 15);
    Sleep(150);
    printf("   ==================\n");
    
    outputcursorposition(32, 16);
    printf("           ||        \n");
    
    outputcursorposition(32, 17);
    printf("           ||        \n");
    
    outputcursorposition(32, 18);
    printf("           ||        \n");
    
    outputcursorposition(32, 19);
    printf("           ||        \n");
    
    outputcursorposition(32, 20);
    printf("           ||        \n");
    
    outputcursorposition(32, 21);
    printf("           ||        \n");
    
    outputcursorposition(32, 22);
    printf("           ||        \n");
    
    outputcursorposition(32, 23);
    printf("           ||        \n");

    outputcursorposition(52, 15);
    Sleep(150);
    printf("    ||             ||\n");
    
    outputcursorposition(52, 16);
    printf("    ||             ||\n");
    
    outputcursorposition(52, 17);
    printf("    ||             ||\n");
    
    outputcursorposition(52, 18);
    printf("    ||             ||\n");
    
    outputcursorposition(52, 19);
    printf("    || =========== ||\n");
    
    outputcursorposition(52, 20);
    printf("    ||             ||\n");
    
    outputcursorposition(52, 21);
    printf("    ||             ||\n");
    
    outputcursorposition(52, 22);
    printf("    ||             ||\n");
    
    outputcursorposition(52, 23);
    printf("    ||             ||\n");

    outputcursorposition(73, 15);
    Sleep(150);
    printf("      ============\n");
    
    outputcursorposition(73, 16);
    printf("    ||            ||\n");
    
    outputcursorposition(73, 17);
    printf("    ||            ||\n");
    
    outputcursorposition(73, 18);
    printf("    ||            ||\n");
    
    outputcursorposition(73, 19);
    printf("    ||============||\n");
    
    outputcursorposition(73, 20);
    printf("    ||            ||\n");
    
    outputcursorposition(73, 21);
    printf("    ||            ||\n");
    
    outputcursorposition(73, 22);
    printf("    ||            ||\n");
    
    outputcursorposition(73, 23);
    printf("    ||            ||\n");

    outputcursorposition(93, 15);
    Sleep(150);
    printf("    || \\\\         ||\n");
    
    outputcursorposition(93, 16);
    printf("    ||  \\\\        ||\n");
    
    outputcursorposition(93, 17);
    printf("    ||   \\\\       ||\n");
    
    outputcursorposition(93, 18);
    printf("    ||    \\\\      ||\n");
    
    outputcursorposition(93, 19);
    printf("    ||     \\\\     ||\n");
    
    outputcursorposition(93, 20);
    printf("    ||      \\\\    ||\n");
    
    outputcursorposition(93, 21);
    printf("    ||       \\\\   ||\n");
    
    outputcursorposition(93, 22);
    printf("    ||        \\\\  ||\n");
    
    outputcursorposition(93, 23);
    printf("    ||         \\\\ ||\n");

    outputcursorposition(113, 15);
    Sleep(150);
    printf("    ||     //\n");
    
    outputcursorposition(113, 16);
    printf("    ||    //\n");
    
    outputcursorposition(113, 17);
    printf("    ||   //\n");
    
    outputcursorposition(113, 18);
    printf("    ||  //\n");
    
    outputcursorposition(113, 19);
    printf("    || //\n");
    
    outputcursorposition(113, 20);
    printf("    ||  \\\\\n");
    
    outputcursorposition(113, 21);
    printf("    ||   \\\\\n");
    
    outputcursorposition(113, 22);
    printf("    ||    \\\\\n");
    
    outputcursorposition(113, 23);
    printf("    ||     \\\\\n");

    outputcursorposition(132, 15);
    Sleep(150);
    printf("    ||             ||\n");
    
    outputcursorposition(132, 16);
    printf("    ||             ||\n");
    
    outputcursorposition(132, 17);
    printf("    ||             ||\n");
    
    outputcursorposition(132, 18);
    printf("    ||             ||\n");
    
    outputcursorposition(132, 19);
    printf("    ||             ||\n");
    
    outputcursorposition(132, 20);
    printf("    ||             ||\n");
    
    outputcursorposition(132, 21);
    printf("    ||             ||\n");
    
    outputcursorposition(132, 22);
    printf("    ||             ||\n");
    
    outputcursorposition(132, 23);
    printf("      =============\n");

    outputcursorposition(132, 42);
}

int main()
{
    system("CLS");

    for (int i = 5; i <= 40; i++)
    {
        outputcursorposition(15, i);
        printf("\xB2");
        
        outputcursorposition(15, i);
        printf("\xB2");
        
        outputcursorposition(170, i);
        printf("\xB2");
        
        outputcursorposition(170, i);
        printf("\xB2");
    }

    for (int i = 15; i < 170; i++)
    {
        outputcursorposition(i, 5);
        printf("\xB2\xB2");
        
        outputcursorposition(i, 5);
        printf("\xB2\xB2");
        
        outputcursorposition(i, 40);
        printf("\xB2\xB2");
        
        outputcursorposition(i, 40);
        printf("\xB2\xB2");
    }

    Sleep(400);
    outputcursorposition(32, 15);
    printf("||          ||\n");
    
    outputcursorposition(32, 16);
    printf("||          ||\n");
    
    outputcursorposition(32, 17);
    printf("||          ||\n");
    
    outputcursorposition(32, 18);
    printf("||          ||\n");
    
    outputcursorposition(32, 19);
    printf("||          ||\n");
    
    outputcursorposition(32, 20);
    printf("||   //\\\\   ||\n");
    
    outputcursorposition(32, 21);
    printf("||  //  \\\\  ||\n");
    
    outputcursorposition(32, 22);
    printf("|| //    \\\\ ||\n");
    
    outputcursorposition(32, 23);
    printf("||//      \\\\||\n");

    outputcursorposition(49, 15);
    Sleep(400);
    printf(" ============\n");
    
    outputcursorposition(49, 16);
    printf("||           \n");
    
    outputcursorposition(49, 17);
    printf("||           \n");
    
    outputcursorposition(49, 18);
    printf("||           \n");
    
    outputcursorposition(49, 19);
    printf("||=======    \n");
    
    outputcursorposition(49, 20);
    printf("||           \n");
    
    outputcursorposition(49, 21);
    printf("||           \n");
    
    outputcursorposition(49, 22);
    printf("||           \n");
    
    outputcursorposition(49, 23);
    printf(" ============\n");

    outputcursorposition(64, 15);
    Sleep(400);
    printf("||                    \n");
    
    outputcursorposition(64, 16);
    printf("||                    \n");
    
    outputcursorposition(64, 17);
    printf("||                    \n");
    
    outputcursorposition(64, 18);
    printf("||                    \n");
    
    outputcursorposition(64, 19);
    printf("||                    \n");
    
    outputcursorposition(64, 20);
    printf("||                    \n");
    
    outputcursorposition(64, 21);
    printf("||                    \n");
    
    outputcursorposition(64, 22);
    printf("||                    \n");
    
    outputcursorposition(64, 23);
    printf("  ============== \n");

    outputcursorposition(82, 15);
    Sleep(400);
    printf("  =========== \n");
    
    outputcursorposition(82, 16);
    printf("||                   \n");
    
    outputcursorposition(82, 17);
    printf("||                   \n");
    
    outputcursorposition(82, 18);
    printf("||                   \n");
    
    outputcursorposition(82, 19);
    printf("||                   \n");
    
    outputcursorposition(82, 20);
    printf("||                   \n");
    
    outputcursorposition(82, 21);
    printf("||                   \n");
    
    outputcursorposition(82, 22);
    printf("||                   \n");
    
    outputcursorposition(82, 23);
    printf("  ===========  \n");

    outputcursorposition(99, 15);
    Sleep(400);
    printf("  ============== \n");
    
    outputcursorposition(99, 16);
    printf("||              ||\n");
    
    outputcursorposition(99, 17);
    printf("||              ||\n");
    
    outputcursorposition(99, 18);
    printf("||              ||\n");
    
    outputcursorposition(99, 19);
    printf("||              ||\n");
    
    outputcursorposition(99, 20);
    printf("||              ||\n");
    
    outputcursorposition(99, 21);
    printf("||              ||\n");
    
    outputcursorposition(99, 22);
    printf("||              ||\n");
    
    outputcursorposition(99, 23);
    printf("  ============== \n");

    outputcursorposition(120, 15);
    Sleep(400);
    printf("||\\\\        //||\n");
    
    outputcursorposition(120, 16);
    printf("|| \\\\      // ||\n");
    
    outputcursorposition(120, 17);
    printf("||  \\\\    //  ||\n");
    
    outputcursorposition(120, 18);
    printf("||   \\\\  //   ||\n");
    
    outputcursorposition(120, 19);
    printf("||    \\\\//    ||\n");
    
    outputcursorposition(120, 20);
    printf("||            ||\n");
    
    outputcursorposition(120, 21);
    printf("||            ||\n");
    
    outputcursorposition(120, 22);
    printf("||            ||\n");
    
    outputcursorposition(120, 23);
    printf("||            ||\n");

    outputcursorposition(139, 15);
    Sleep(400);
    printf(" ============\n");
    
    outputcursorposition(139, 16);
    printf("||           \n");
    
    outputcursorposition(139, 17);
    printf("||           \n");
    
    outputcursorposition(139, 18);
    printf("||           \n");
    
    outputcursorposition(139, 19);
    printf("||=======    \n");
    
    outputcursorposition(139, 20);
    printf("||           \n");
    
    outputcursorposition(139, 21);
    printf("||           \n");
    
    outputcursorposition(139, 22);
    printf("||           \n");
    
    outputcursorposition(139, 23);
    printf(" ============\n");
    Sleep(1800);
    
    welcome_options();

    return 0;
}