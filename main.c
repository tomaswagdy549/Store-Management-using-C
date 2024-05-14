#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
//initialize the required data structures

struct product
{
    char name[25];
    int price;
    int quantity;
    int category_ID;
};
struct SuperMarket
{
    char name[25];
    char** categories;
    unsigned int numofcategories;
    struct product* product;
    unsigned int numofproducts;
};

//finished initializing

// functions of categories

void insert_category(struct SuperMarket* sportMarket)
{
    printf("how many categories you want : \n");
    int num;
    scanf("%d",&num);
    //checking if it is the first time to insert category or not
    if(sportMarket->numofcategories==0)
    {
        sportMarket->categories=(char**)malloc(num*sizeof(char*));
    }
    else
    {
        //resizing the array of categories
        struct SuperMarket* copy = malloc(sizeof(struct SuperMarket));
        (copy)->categories = (char**)malloc((num+(sportMarket)->numofcategories) * sizeof(char*));
        for (int i = 0; i < (sportMarket)->numofcategories; i++)
        {
            copy->categories[i] = strdup(sportMarket->categories[i]);
        }
        for (int i = 0; i < sportMarket->numofcategories; i++)
        {
            free(sportMarket->categories[i]);
        }
        free(sportMarket->categories);
        sportMarket->categories = copy->categories;
        free(copy);
    }
    //insert the required categories after resizing the array
    for(int i=sportMarket->numofcategories; i<(num+sportMarket->numofcategories); i++)
    {
        printf("the %d category name : ",i+1);
        char categoryName[50];
        scanf("%s",categoryName);
        (sportMarket->categories[i])=(char*)malloc(strlen(categoryName)*sizeof(char));
        strcpy((sportMarket->categories[i]),categoryName);
    }
    //change the number of categories to the new value
    sportMarket->numofcategories += num;
    printf("%d \n",sportMarket->numofcategories);
}
void display_category(struct SuperMarket* sportMarket)
{
    printf("the category list : \n");
    for(int i=0; i<sportMarket->numofcategories; i++)
    {
        printf(" %d -  %s \n",i+1,sportMarket->categories[i]);
    }
}

void edit_category(struct SuperMarket* sportMarket)
{
    display_category(sportMarket);
    printf("Which category you want to edit ? \n");
    char required[50];
    scanf("%s",required);
    int sensor=0,count=0; //sensor to detect the required category name
    //checking if the required category to be edit exist or not
    while(sensor==0&&count<sportMarket->numofcategories)
    {
        if(!strcmp(sportMarket->categories[count],required))
        {
            printf("found it , what do you want to rename ? \n");
            scanf("%s",sportMarket->categories[count]);
            sensor=1;
            printf("successfully edited \n");
        }
        count++;
    }
    //detect if the entered category is not found
    if(sensor==0)
    {
        printf("you entered a not found category , try again ...(y/n) \n");

        char choice;
        choice=getch();
        if(choice=='y')
        {
            edit_category(sportMarket);
        }
        else
        {
            return;
        }
    }

}
void remove_category(struct SuperMarket* sportMarket)
{
    display_category(sportMarket);
    printf("enter the number of which category you want to delete ... \n");
    int choice;
    scanf("%d",&choice);
    choice--;
    for(int i=choice; i+1<sportMarket->numofcategories; i++)
    {
        strcpy(sportMarket->categories[i],sportMarket->categories[i+1]);
    }
    free(sportMarket->categories[--sportMarket->numofcategories]);
}

//functions of categories finished

//functions of products

void insert_products(struct SuperMarket* sportMarket)
{
    //checking the number of required product to be inserted
    printf("how many products you want ? \n");
    int num;
    scanf("%d",&num);
    if(sportMarket->numofproducts==0)
    {
        sportMarket->product=(struct product*)malloc(num*sizeof(struct product));
    }
    else
    {
        //resizing the array of products due to the size of number of new inserted products
        struct SuperMarket* copy = malloc(sizeof(struct SuperMarket));
        (copy)->product = (struct product*)malloc((num+(sportMarket)->numofproducts)* sizeof(struct product));
        for(int i=0; i<sportMarket->numofproducts; i++)
        {
            (copy)->product[i]=sportMarket->product[i];
        }
        free(sportMarket->product);
        sportMarket->product = copy->product;
        free(copy);
    }
    //we begin to input the details of the new required inserted products
    for(int i=sportMarket->numofproducts; i<(num+sportMarket->numofproducts); i++)
    {
        printf("the %d product : \n",i+1);
        printf("what is this category \n");
        char name[25];
        scanf("%s",name);
        int found=0;
        int count=0;
        //checking if the category we require to insert it is found or not
        while (found == 0 && count < sportMarket->numofcategories)
        {
            if (!strcmp(name, sportMarket->categories[count]))
            {
                found = 1;
                break;
            }
            count++;
        }
        //if we did not find the required edit category , we assign the size with the only the inserted products
        if (found == 0)
        {
            printf("Category not found , the previous products have been inserted \n");
            sportMarket->numofproducts += (i-sportMarket->numofproducts);
            return;
        }
        else
        {
            //assign the category_ID to the index of the found element in array of categories
            // , then we add the remaining details
            sportMarket->product[i].category_ID = count;
            printf("enter the product name \n");
            scanf("%s",sportMarket->product[i].name);
            printf("enter the price \n");
            scanf("%d",&(sportMarket->product[i].price));
            printf("how many you have : \n");
            scanf("%d",&(sportMarket->product[i].quantity));
        }
    }
    //assign the number of products of the sportmarket
    sportMarket->numofproducts=sportMarket->numofproducts + num;

}
void display_products(struct SuperMarket* sportMarket)
{
    printf("the product list : \n");
    for(int i=0; i<sportMarket->numofproducts; i++)
    {
        printf(" %d category : %s name : %s the quantity : %d the price : %d \n",i+1,
               sportMarket->categories[sportMarket->product[i].category_ID], //display the category of product due to its category_ID
               sportMarket->product[i].name,
               sportMarket->product[i].quantity,
               sportMarket->product[i].price);
    }

}
void edit_product_attributes(struct SuperMarket* sportMarket, int count)
{
    printf("found product \n \n");
    printf("1- name \n");
    printf("2- category \n");
    printf("3- price \n");
    printf("4- quantity \n \n");
    printf("enter number of what you want to edit \n");
    int choice;
    scanf("%d",&choice);
    //detect what the user want to edit due to its choice
    switch(choice)
    {
    case 1: //edit the name
        printf("enter the name you want to give \n");
        char edited_name[50];
        scanf("%s",edited_name);
        strcpy(sportMarket->product[count].name,edited_name);
        printf("successfully done \n");
        break;
    case 2: //edit the category
        display_category(sportMarket); //we display the category list to make him choose one of them
        printf("which number of category you want to assign \n");
        int new_category_ID;
        scanf("%d",&new_category_ID);
        sportMarket->product[count].category_ID=new_category_ID-1;
        break;
    case 3: //edit the price
        printf("enter the price you want to edit \n");
        scanf("%d",&sportMarket->product[count].price);
        printf("successfully done \n");
        break;
    case 4: //edit the quantity
        printf("what is your new quantity");
        scanf("%d",&sportMarket->product[count].quantity);
        printf("successfully done \n");
        break;
    default:
        printf("wrong choice , try again ... ? (y/n) \n");
        char choose;
        choose=getch();
        if(choose=='y')
        {
            edit_product_attributes(sportMarket,count);
        }
        else
        {
            return;
        }
        break;
    }
    printf("you want to edit another attributes ?(y/n) \n");
    char choose;
    choose=getch();
    if(choose=='y')
    {
        edit_product_attributes(sportMarket,count);
    }
    else
    {
        return;
    }
}
void edit_product(struct SuperMarket* sportMarket)
{
    printf("select the product name \n");
    char edited[50];
    scanf("%s",edited);
    int sensor=0,count=0;
    //checking if the name inserted exist in the products
    while(sensor==0&&count<sportMarket->numofproducts)
    {
        if(!strcmp(sportMarket->product[count].name,edited))
        {
            sensor=1;
            edit_product_attributes(sportMarket, count);  //go to function edit_product_attributes we start the edit if we found the required name of the product
        }
        count++;
    }
    if(sensor==0)
    {
        printf("you entered a wrong name , try again ... ?(y/n) \n");
        char choose;
        choose=getch();
        if(choose=='y')
        {
            edit_product(sportMarket);
        }
        else
        {
            return;
        }
    }
    printf("finished editing \n");
}
void remove_product(struct SuperMarket* sportMarket)
{
    display_products(sportMarket); //we use this function to display the products to show all the available products
    printf("select which one you want to delete \n");
    int choice;
    scanf("%d",&choice); //the user choose the number of the product in the list of products
    choice--;
    //we resize the array of products beacause we will decrease the required product
    struct SuperMarket* copy = malloc(sizeof(struct SuperMarket));
    (copy)->product = (struct product*)malloc((sportMarket->numofproducts-1)* sizeof(struct product));
    //we copy the elements from the old list to the new list except the required product to delete
    for(int i=0; i<sportMarket->numofproducts; i++)
    {
        if(i<choice)
        {
            (copy)->product[i]=sportMarket->product[i];
        }
        else if(i>choice)
        {
            (copy)->product[i-1]=sportMarket->product[i];
        }
    }
    //decrease the number of products
    sportMarket->numofproducts--;
    //deallocate the old list and assign the new one
    free(sportMarket->product);
    sportMarket->product = copy->product;
    free(copy);
    printf("product deleted \n");
}
//functions of products finished

COORD coord = {0, 0};
void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
// functions of menus

//function to display the menu related to displaying categories and products
void display_menu(struct SuperMarket* sportmarket)
{
    int  choice=1;
    int  maxChoice=3;
    int  ch;
    while (1)
    {
        system("cls");
        for (int i = 1; i <= maxChoice; i++)
        {
            gotoxy(30, 6 + i);
            if (i == choice)
            {
                SetColor(12);
            }
            else
            {
                SetColor(15);
            }
            printf(i == choice ? ">> %d. " : "%d. ", i);

            switch (i)
            {
            case 1:
                printf("Display Categories");
                break;
            case 2:
                printf("Display Products");
                break;
            case 3:
                printf("End");
                break;
            default:
                break;
            }
        }

        gotoxy(30, 13);
        printf("Use the arrow keys to navigate, and press Enter to select.");

        ch = _getch();
        switch (ch)
        {
        case 72:
            if (choice > 1)
            {
                choice--;
            }
            break;
        case 80:
            if (choice < maxChoice)
            {
                choice++;
            }
            break;
        case 13:
            switch (choice)
            {
            case 1:
                system("cls");
                display_category(sportmarket);
                system("pause");
                break;
            case 2:
                system("cls");
                display_products(sportmarket);
                system("pause");
                break;
            case 3:
                system("cls");
                return;
                system("pause");
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

//function to insert any thing related to the categories and products
void insert_menu(struct SuperMarket* sportmarket)
{
    int  choice=1;
    int  maxChoice=3;
    int  ch;
    while (1)
    {
        system("cls");
        for (int i = 1; i <= maxChoice; i++)
        {
            gotoxy(30, 6 + i);
            if (i == choice)
            {
                SetColor(12);
            }
            else
            {
                SetColor(15);
            }
            printf(i == choice ? ">> %d. " : "%d. ", i);

            switch (i)
            {
            case 1:
                printf("insert Categories");
                break;
            case 2:
                printf("insert Products");
                break;
            case 3:
                printf("End");
                break;
            default:
                break;
            }
        }
        gotoxy(30, 13);
        printf("Use the arrow keys to navigate, and press Enter to select.");

        ch = _getch();
        switch (ch)
        {
        case 72:
            if (choice > 1)
            {
                choice--;
            }
            break;
        case 80:
            if (choice < maxChoice)
            {
                choice++;
            }
            break;
        case 13:
            switch (choice)
            {
            case 1:
                system("cls");
                insert_category(sportmarket);
                system("pause");
                break;
            case 2:
                system("cls");
                insert_products(sportmarket);
                system("pause");
                break;
            case 3:
                system("cls");
                return;
                system("pause");
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

//function to display a menu related to editing categories or products
void edit_menu(struct SuperMarket* sportmarket)
{
    int  choice=1;
    int  maxChoice=3;
    int  ch;
    while (1)
    {
        system("cls");
        for (int i = 1; i <= maxChoice; i++)
        {
            gotoxy(30, 6 + i);
            if (i == choice)
            {
                SetColor(12);
            }
            else
            {
                SetColor(15);
            }
            printf(i == choice ? ">> %d. " : "%d. ", i);

            switch (i)
            {
            case 1:
                printf("Edit Categories");
                break;
            case 2:
                printf("Edit Products");
                break;
            case 3:
                printf("End");
                break;
            default:
                break;
            }
        }
        gotoxy(30, 13);
        printf("Use the arrow keys to navigate, and press Enter to select.");

        ch = _getch();
        switch (ch)
        {
        case 72:
            if (choice > 1)
            {
                choice--;
            }
            break;
        case 80:
            if (choice < maxChoice)
            {
                choice++;
            }
            break;
        case 13:
            switch (choice)
            {
            case 1:
                system("cls");
                edit_category(sportmarket);
                system("pause");
                break;
            case 2:
                system("cls");
                edit_product(sportmarket);
                system("pause");
                break;
            case 3:
                system("cls");
                return;
                system("pause");
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

//function related to removing categories or products
void remove_menu(struct SuperMarket* sportMarket)
{
    int  choice=1;
    int  maxChoice=3;
    int  ch;
    while (1)
    {
        system("cls");
        gotoxy(30, 5);
        SetColor(14);
        printf("remove what you want .... !");
        SetColor(15);

        for (int i = 1; i <= maxChoice; i++)
        {
            gotoxy(30, 6 + i);
            if (i == choice)
            {
                SetColor(12);
            }
            else
            {
                SetColor(15);
            }
            printf(i == choice ? ">> %d. " : "%d. ", i);
            switch (i)
            {
            case 1:
                printf("Remove Categories");
                break;
            case 2:
                printf("Remove Products");
                break;
            case 3:
                printf("End");
                break;
            default:
                break;
            }

        }
        gotoxy(30, 13);
        printf("Use the arrow keys to navigate, and press Enter to select.");

        ch = _getch();
        switch (ch)
        {
        case 72:
            if (choice > 1)
            {
                choice--;
            }
            break;
        case 80:
            if (choice < maxChoice)
            {
                choice++;
            }
            break;
        case 13:
            switch (choice)
            {
            case 1:
                system("cls");
                remove_category(sportMarket);
                system("pause");
                break;
            case 2:
                system("cls");
                remove_product(sportMarket);
                system("pause");
                break;
            case 3:
                system("cls");
                return;
                system("pause");
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}
// functions of menus finished

// ordering function
void order(struct SuperMarket* sportmarket)
{
    display_products(sportmarket);
    char ch='y';
    int payment=0;
    int choice;
    while(ch=='y')
    {
        printf("choose your products... \n");
        scanf("%d",&choice);
        printf("you choosed %s , there are %d available quantity , how many you want ? \n",
               sportmarket->product[choice-1].name,
               sportmarket->product[choice-1].quantity);
        int required_quantity;
        scanf("%d",&required_quantity);
        if(required_quantity>sportmarket->product[choice-1].quantity)
        {
            printf("out of stock \n");
        }
        else
        {
            sportmarket->product[choice-1].quantity -= required_quantity;
            payment=payment+required_quantity*sportmarket->product[choice-1].price;
        }
        printf("the total  payment is %d , you want to continue ?(y/n) \n",payment);

        ch=getch();
    }
    printf("finished ordering \n");
}
// finished function

int main()
{
    struct SuperMarket sportMarket;
    sportMarket.numofcategories=0;
    sportMarket.numofproducts=0;
    int choice = 1;
    int maxChoice = 6;
    int ch;

    while (1)
    {
        system("cls");

        gotoxy(30, 5);
        SetColor(14);
        printf("Welcome to our market , how can i help you ?");
        SetColor(15);


        for (int i = 1; i <= maxChoice; i++)
        {
            gotoxy(30, 6 + i);
            if (i == choice)
            {
                SetColor(12);
            }
            else
            {
                SetColor(15);
            }
            printf(i == choice ? ">> %d. " : "%d. ", i);

            switch (i)
            {
            case 1:
                printf("Insert");
                break;
            case 2:
                printf("Display");
                break;
            case 3:
                printf("Edit");
                break;
            case 4:
                printf("Ordering");
                break;
            case 5:
                printf("Remove");
                break;
            case 6:
                printf("End");
                break;
            default:
                break;
            }
        }

        gotoxy(30, 13);
        printf("Use the arrow keys to navigate, and press Enter to select.");

        ch = _getch();
        switch (ch)
        {
        case 72:
            if (choice > 1)
            {
                choice--;
            }
            break;
        case 80:
            if (choice < maxChoice)
            {
                choice++;
            }
            break;
        case 13:
            switch (choice)
            {
            case 1:
                system("cls");
                insert_menu(&sportMarket);
                system("pause");
                break;
            case 2:
                system("cls");
                display_menu(&sportMarket);
                system("pause");
                break;
            case 3:
                system("cls");
                edit_menu(&sportMarket);
                system("pause");
                break;
            case 4:
                system("cls");
                order(&sportMarket);
                system("pause");
                break;
            case 5:
                system("cls");
                remove_menu(&sportMarket);
                system("pause");
                break;
            case 6:
                exit(0);
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}
