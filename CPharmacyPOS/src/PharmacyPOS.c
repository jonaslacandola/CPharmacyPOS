#include <stdio.h>
#include <string.h>
#include <Windows.h>
//Constant MAX 
#define MAX 100
//Function prototypes 
void displayProduct(char userInput);
int isEqual(char typeOf[], char toCompare[]);
void addtoCart();
void displayCart();
int Cashier(int discount);
//A collection of variables, created to access them easily
struct Items {

    int code;
    double price;
    char item[MAX];
    char type[10];
    int quantity;

    double subtotal[20];
    double total;
};
//counts the item added in the cart
int counter;
//An instance of the collection type "Items" as a product array
//These are the products
struct Items products[20] = {

        {1, 8.75, "Tylenol Paracetamol 650mg 1 Extended Release Caplet", "Medicine"},
        {2, 129.75, "Paracetamol 250 mg/5 mL Strawberry-Flavored Oral Suspension 60 mL", "Medicine"},
        {3, 7.50, "Fern C Plus+ 500mg/10mg capsule 1s", "Medicine"},
        {4, 490.00, "Puritans Pride (Heart Health) Garlic Odorless 1000mg 100 Softgels", "Medicine"},
        {5, 7.50, "Potencee (Kids Vitamins) +ZN (Ascorbic Acid + Zinc) 500mg/10mg 1 Capsule (sold per piece)", "Medicine"},
        {6, 19.50, "Ponstan Mefenamic Acid 250mg 1 Capsule", "Medicine"},
        {7, 15.00, "Cetirizine hydrochloride 10mg 1 Tablet", "Medicine"},
        {8, 15.00, "Glucosamine Tablet 1500mg x 30 Tablet", "Medicine"},
        {9, 83.00, "United TIKI-TIKI B Complex; Vitamins A; C; D and E Drops 30ml", "Medicine"},
        {10, 316.00, "Stresstabs Multivitamins + Iron 30 Tablets", "Medicine"},
        {1, 109.00, "PUREDERM Make up Remover Cleansing Tissue Argan Oil 30sheets", "Beauty"},
        {2, 165.00, "ChicBobbie Baby-doll Eyes Bold Liquid Eyeliner 1.6gv", "Beauty"},
        {3, 185.00, "ChicBobbie Beauty Tools- Make-up Blending Sponge", "Beauty"},
        {4, 248.00, "NIVEA Body Lotion Intensive Moisture Body Milk for dry skin 250ml", "Beauty"},
        {5, 157.00, "Johnsons & Johnsons Regular Lotion 200ml", "Beauty"},
        {6, 229.00, "Maybelline Fit Me Flawless Natural Concealer - 10 Light", "Beauty"},
        {7, 30.00, "COLLAGEN WS Moisturising and Repairing Serum 30ml", "Beauty"},
        {8, 152.00, "NIVEA Lip Caring Lip Scrub with Rosehip Oil 5.5ml", "Beauty"},
        {9, 69.00, "WATSONS Anti - Wrinkle Serum Mask 1 sheet", "Beauty"},
        {10, 97.00, "PONDS Acne Clear Facial Foam with Scrub 50g", "Beauty"}
    };
//An instance of the collection type "Items" as a cart array
//This is where we're going to put the items chosen by the user
struct Items cart[40];
//An instance of the collection type "Items" as a cashier
struct Items cashier;

int main() {
    //variable for user inputs
    char userInput = 'D', cartInput = 'D', input;
    int code, quantity;

    system("cls");
    printf("===========================\n\tWatsons\n===========================\n\n");
    //The algorithm will loop until 'E'
    while (userInput != 'E')
    {
        printf("Press 'A' to Medicine Section\nPress 'B' to Beauty Section\nPress 'C' to Cart\nPress 'E' to Exit\n- ");
        userInput = getchar();
        //A switch statement to select which section to display
        //A for Medicine Section, B for Beauty Section, C for Cart, E for Exit
        switch (userInput)
        {
            case 'A':
                //Medicine Section
                system("cls");
                printf("\nMedicine Section\n\n");
                displayProduct(userInput);

                printf("\nPlease select an item: ");
                scanf("%d", &code);
                printf("\nEnter the quantity: ");
                scanf("%d", &quantity);

                if (isEqual(products[code - 1].type, "MEDICINE")) {
                    addtoCart(products[code - 1], quantity);
                }
                counter++;
                break;

            case 'B':
                //Beauty and Make Up Section
                system("cls");
                printf("\nBeauty Section\n\n");
                displayProduct(userInput);

                printf("\nPlease select an item: ");
                scanf("%d", &code);
                printf("\nEnter the quantity: ");
                scanf("%d", &quantity);

                if (isEqual(products[code + 9].type, "BEAUTY")) {

                    addtoCart(products[code + 9], quantity);
                }
                counter++;
                break;
            case 'C':
                //Cart Section
                do {
                    if (cart[0].code != 0) {
                        system("cls");
                        printf("\nCart:\n\n");
                        displayCart();
                        printf("\nPress 'E' to exit\n- ");
                        cartInput = getchar();
                    } else {

                        system("cls");
                        printf("\nCart:\n\n");
                        printf("You don't have any items.\n");
                        printf("\nPress 'E' to Exit\n- ");
                        cartInput = getchar();
                    }

                } while (cartInput != 'E');

                cartInput = 'D';
            }

            system("cls");
            printf("\nItem added to cart!\n\n");
    }
    //if the user exited and cart is not equal null, else program exit
    if (cart[0].code != 0) {
        //if true, ask if the user are a member of the following; PWD, PREGNANT, SENIOR/ELDERLY
        system("cls");
        printf("Are you a PWD, PREGNANT, SENIOR/ELDERLY? [y/n] : ");
        input = getche();
        //if true discount will be apply, else no discount
        //if purchase is greater than 1000 and is true, discount is 25%
        //if purchase is less than 1000 and is true, discount is 20%
        //if purchase is greater than 1000 and is false, discount is 5%, else no discount
        if (input == 'y' || input == 'Y') {
            printf("\n\n");
            Cashier(1);
        } else if (input == 'n' || input == 'N'){
            printf("\n\n");
            Cashier(0);
        }
    }
}
// A function, looping through the product array to display the products
void displayProduct(char userInput) {
    for (int x = 0; x < 20; x++) {
        //Checks if the user typed 'A' and if the products are of type "Medicine"
        if (isEqual(products[x].type, "MEDICINE") && userInput == 'A') {
            printf("\n%d....%s....P%.3f\n", products[x].code, products[x].item, products[x].price);
        //Checks if the user typed 'B' and if the products are of type "Beauty"
        } else if (isEqual(products[x].type, "BEAUTY") && userInput == 'B') {
            printf("\n%d....%s....P%.3f\n", products[x].code, products[x].item, products[x].price);
        }
    }
}
//A function to check if the string typeOf is equal toCompare
int isEqual(char typeOf[], char toCompare[]) {

    int bool;
    //if true bool = 0, else bool = 1
    if (strcmpi(toCompare, typeOf)) {
        bool = 0;
    } else {
        bool = 1;
    }
    return bool;
}
//A function to add items chosen by the user into the cart
void addtoCart(struct Items product, int quantity) {

    cart[counter] = product;
    cart[counter].quantity = quantity;

    printf("\nItem added to cart!\n\n");
}
//A function to display every items in the cart
void displayCart() {
    //A loop to display items in the cart, not greater than the counter
    for (int x = 0; x < counter; x++) {
        printf("%s\n", cart[x].item);
        printf("%d\t\t%.3f\t\t\t\t%.3f\n", cart[x].quantity, cart[x].price, (cart[x].price * cart[x].quantity));
    }
}
//A function Cashier to pay the items in the cart
int Cashier(int discount) {

    double discountedTotal, VAT, userCash, userChange;
    //Calculate the subtotal of each item in the cart
    for (int x = 0; x < counter; x++) {
        cashier.subtotal[x] = cart[x].price * cart[x].quantity;
    }
    //Calculate the total
    for (int y = 0; y < counter; y++) {
        cashier.total += cashier.subtotal[y];
    }
    //Calculate and add the VAT to the total
    VAT = cashier.total * 0.12;
    cashier.total += cashier.total * 0.12;
    //if true discount will be apply, else no discount
    //if purchase is greater than 1000 and is true, discount is 25%
    //if purchase is less than 1000 and is true, discount is 20%
    //if purchase is greater than 1000 and is false, discount is 5%, else no discount
    if (discount && cashier.total > 1000) {
        discountedTotal = cashier.total - (cashier.total * 0.25);
    } else if (discount && cashier.total < 1000) {
        discountedTotal = cashier.total - (cashier.total * 0.20);
    } else if (discount == 0 && cashier.total > 1000) {
        discountedTotal = cashier.total - (cashier.total * 0.05);
    }
    //Display the items in the cart, and display the total, discount
    displayCart();
    printf("\nTotal: \t\t\t\t\t\t%.3f\n", cashier.total);
    printf("Discounted: \t\t\t\t\t%.3f\n", discountedTotal);
    //Prompts the user to pay for the total items
    printf("Cash:\t\t\t\t\t\t");
    scanf("%lf", &userCash);
    //If user does not enter a valid cash amount, 
    //prompts the user to enter a valid cash amount
    while (userCash < cashier.total) {
        printf("Enter a valid cash amount!\n");
        printf("Cash:\t\t\t\t\t\t");
        scanf("%lf", &userCash);
    }
    //if discounted, initialize discounted total to total
    if (discount)
        cashier.total = discountedTotal;
    //Get the change of the user
    userChange = userCash - cashier.total;
    //Display the change, vatable amount, and VAT
    printf("Change: \t\t\t\t\t%.3f\n", userChange);
    printf("\nVatable: \t\t\t\t\t%.3f\n", cashier.total);
    printf("VAT: \t\t\t\t\t\t%.3f\n", VAT);
}
