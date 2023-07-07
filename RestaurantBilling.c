#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct items
{
    char item[20];
    float price;
    int qty;
};
struct orders
{
    char customer[50];
    char date[20];
    int numOfitems;
    struct items itm[50];
};

// Function to generate bills
void GenerateBillHeader(char name[50], char date[30])
{
    printf("\n\n");
    printf("\t  Shivam's Restaurant ");
    printf("\n*******************************************");
    printf("\nDate:%s", date);
    printf("\nInvoice To :  %s", name);
    printf("\n");
    printf("******************************************************\n");
    printf("Items\t\t");
    printf("Qty.\t\t");
    printf("Total\t\t\n");
    printf("******************************************************\n");
    printf("\n");
}

void GenerateBillBody(char item[30], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

void GeneratBillFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal, grandTotal = netTotal + (2 * cgst); // nettoale +sgst +cgst
    printf("******************************************************\n");
    printf("Sub Total\t\t\t%.2f\n", total);
    printf("Discount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t*************************\n");
    printf("Net Total\t\t\t%.2f\n", netTotal);
    printf("CGST @9%s\t\t\t%.2f\n", "%", cgst);
    printf("SGST @9%s\t\t\t%.2f\n", "%", cgst);
    printf("******************************************************\n");
    printf("Grand Total\t\t\t%.2f\n", grandTotal);
    printf("******************************************************\n");
}

int main()
{
    float total;
    struct orders ord;
    struct orders order;
    char savebill = 'y', contFlag = 'y';
    char name[50];
    FILE *fp;
    int opt, n;
    // deshboard
    while(contFlag == 'y'){
    float total = 0;
    int invoiceFound = 0;
    printf("**********************SHIVAM'S RESTAURANT*******************\n\n");
    printf("Please select your operation:\t\n");
    printf("1. Generate Invoice\n");
    printf("2. Show All Invoices\n");
    printf("3. Search Invoice\n");
    printf("4. Exit\n\n");

    printf("Please enter your choice:  ");
    scanf("%d", &opt);
    // printf("You have choose %d",opt);
    fgetc(stdin);

    switch (opt)
    {
    case 1:
    system("cls"); // This clear the screen
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer, 50, stdin);
        ord.customer[strlen(ord.customer) - 1] = 0;
        strcpy(ord.date, __DATE__);
        printf("\nPlease enter the number of items: ");
        scanf("%d", &n);
        ord.numOfitems = n;
        for (int i = 0; i < n; i++)
        {
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d : ", i + 1);
            fgets(ord.itm[i].item, 20, stdin);
            ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
            printf("Please enter the quantity: ");
            scanf("%d", &ord.itm[i].qty);
            printf("Please enter the unit price: ");
            scanf("%f", &ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }

        GenerateBillHeader(ord.customer, ord.date);
        for (int i = 0; i < ord.numOfitems; i++)
        {
            GenerateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
        }
        GeneratBillFooter(total);

        printf("\nDo you want to save this invoice [y/n]: ");
        scanf("%s",&savebill);

        if (savebill == 'y')
        {
            fp = fopen("RestuarantBill.dat", "w");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if (fwrite != 0)
            {
                printf("\nSuccessfully saved");
            }
            else
            {
                printf("\nError saved");
            }
            fclose(fp);
        }
        break;

        case 2:
        system("cls"); // This clear the screen
        fp = fopen("RestuarantBill.dat","r");
        printf("\n*************Your previous Invoices**********\n");
        while(fread(&order,sizeof(struct orders),1,fp))
        {
            float Total = 0;
            GenerateBillHeader(order.customer,order.date);
            for(int i=0; i<order.numOfitems; i++)
            {
                GenerateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                Total += order.itm[i].qty*order.itm[i].price;
            }
            GeneratBillFooter(Total);
        }
        fclose(fp);
        break;

        case 3:
        system("cls"); // This clear the screen
        printf("\nEnter the name of the customer: ");
        // fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1] = 0;
        fp = fopen("RestuarantBill.dat","r");
        printf("\n*************Invoice of %s*************\n",name);
        while(fread(&order,sizeof(struct orders),1,fp))
        {
            if(!strcmp(order.customer,name))
            { 
            GenerateBillHeader(order.customer,order.date);
            for(int i=0; i<order.numOfitems; i++)
            {
                GenerateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                total += order.itm[i].qty * order.itm[i].price;
            }
            GeneratBillFooter(total);
            invoiceFound = 1;
            }
        }
        if(!invoiceFound)
        {
            printf("Sorry this invoice for %s doesn't exists",name);
        }
        fclose(fp);
        break;

        case 4:
        printf("\n\t\tBye Bye \n\n");
        exit(0);
        break;

        default:
        printf("Sorry invalid option");
        break;

    }
    printf("\nDo you want to perform another opretion? [y/n]:  ");
    scanf("%s",&contFlag);
    }
    printf("\n\n");
    return 0;
}