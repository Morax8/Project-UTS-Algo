#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Added for boolean support

typedef struct User
{
    char username[50];
    char password[50];
    int point;
} User;

typedef struct Cart
{
    char name[50];
    char code[20];
    float price;
    int quantity;
    struct Cart *prev, *next;
} Cart;

// Function to display products from a category file
void displayProducts(const char *categoryFile)
{
    FILE *file = fopen(categoryFile, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", categoryFile);
        return;
    }

    char name[100], code[100];
    float price;

    printf("\nAvailable Products:\n");
    printf("╔═══════════════════════╦═════════════╦══════════════╗\n");
    printf("║ %-21s ║ %-11s ║ %-12s ║\n", "Product Name", "Code", "Price");
    printf("╠═══════════════════════╬═════════════╬══════════════╣\n");

    while (fscanf(file, " %[^#]#%[^#]#%f\n", name, code, &price) != EOF)
    {
        printf("║ %-21s ║ %-11s ║ Rp %-9.0f ║\n", name, code, price);
    }

    printf("╚═══════════════════════╩═════════════╩══════════════╝\n");
    fclose(file);
}

// Function for category selection
void viewProducts()
{
    int subChoice;
    const char *categories[] = {
        "Data/Drinks.txt", "Data/Snacks.txt", "Data/Foods.txt",
        "Data/FrozenFood.txt", "Data/FruitsVeggies.txt",
        "Data/CleaningSupplies.txt"};

    printf("\nProduct Categories:\n");
    printf("1. Drinks\n2. Snacks\n3. Foods\n4. Frozen Food\n");
    printf("5. Fruits & Vegetables\n6. Cleaning Supplies\n");
    printf("0. Back to Menu\n");

    printf("Select a category: ");
    scanf("%d", &subChoice);

    if (subChoice >= 1 && subChoice <= 6)
    {
        displayProducts(categories[subChoice - 1]);
    }
    else if (subChoice == 7)
    {
        printf("Returning to main menu...\n");
    }
    else
    {
        printf("Invalid selection!\n");
    }
}

void menu(char *username, int point)
{
    int choice;
    while (1)
    {
        printf("\n===============================\n");
        printf("         AEON STORE MENU       \n");
        printf("==================================\n");
        printf("Welcome %s!\n", username);
        printf("Your points: %d\n", point);
        printf("==================================\n");
        printf("1. View Products\n2. Add to Cart\n3. View Cart\n");
        printf("4. Checkout\n5. Logout\n===========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewProducts();
            break;
        case 2:
            printf("Adding to cart...\n");
            break;
        case 3:
            printf("Viewing cart...\n");
            break;
        case 4:
            printf("Proceeding to checkout...\n");
            break;
        case 5:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }
}

bool login()
{
    User user;
    char inputUser[50], inputPass[50];
    bool loginSuccess = false;
    FILE *users = fopen("Data/User.txt", "r");
    if (users == NULL)
    {
        printf("Error opening file.\n");
        return false;
    }

    printf("===========================\n");
    printf("           Login           \n");
    printf("===========================\n");

    printf("Enter username: ");
    scanf("%s", inputUser);
    printf("Enter password: ");
    scanf("%s", inputPass);

    while (fscanf(users, " %[^#]#%[^#]#%d", user.username, user.password, &user.point) != EOF)
    {
        if (strcmp(inputUser, user.username) == 0 && strcmp(inputPass, user.password) == 0)
        {
            printf("Login successful!\n");
            loginSuccess = true;
            break;
        }
    }

    fclose(users);

    if (loginSuccess)
    {
        menu(user.username, user.point);
        return true;
    }
    else
    {
        printf("Invalid username or password.\n");
        return false;
    }
}

bool regist()
{
    User user;
    FILE *users = fopen("Data/User.txt", "a+");
    if (users == NULL)
    {
        printf("Error opening file.\n");
        return false;
    }

    printf("===========================\n");
    printf("Register \n");
    printf("===========================\n");
    printf("Enter username: ");
    scanf("%s", user.username);
    printf("Enter password: ");
    scanf("%s", user.password);

    user.point = 0; // Initialize points to 0

    fprintf(users, "%s#%s#%d\n", user.username, user.password, user.point);
    fclose(users);
    printf("Registration successful!\n");
    printf("Please login with your new account.\n");
    return true;
}

int main()
{
    while (1)
    {
        printf("=====================================");
        printf("\n      Welcome to AEON Store        \n");
        printf("=====================================\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("=====================================\n");
        printf("Please select an option: ");
        int option;
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Login selected.\n");
            login();
            break;
        case 2:
            printf("Register selected.\n");
            if (regist())
            {
                // If registration is successful, proceed to login
                printf("Redirecting to login...\n");
                login();
            }
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }
}