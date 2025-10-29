#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100

typedef struct
{
    char item[N];
    float price;
    int qty;
}items;

typedef struct
{
    char customer[N];
    char date[N];
    int NumbeOfItems;
    items itm[N];
}orders;

void generateBillHeader(char name[N],char date[N])
{
    printf(" \n\n");
    printf(" \t   VR.Restaurant");
    printf(" \n\t ----------------");
    printf(" \nDate:%s",date);
    printf(" \nInvoice To: %s",name);
    printf(" \n");
    printf("-----------------------------------------\n");
    printf(" Items\t\t");
    printf(" Qty\t\t");
    printf(" Total\t\t");
    printf(" \n-----------------------------------------");
    printf(" \n\n");
}

void generateBillBody(char item[N],int qty,float price)
{
    if(strlen(item)>6)
    {
    printf("%s\t",item);
    }else
    {
     printf("%s\t\t",item);
    }
    printf("%d\t\t",qty);
    printf("%.2f\t\t",price*qty);
    printf("\n");
}
void generateBillFooter(float total)
{
    printf("\n");
    float dis=0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal+2*cgst;
    printf("-----------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%c\t\t\t%.2f",'%',dis);
    printf("\n\t\t\t\t---------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n-----------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n-----------------------------------------\n");
}

int main()
{
    int opt;
    orders ord;//struct variables to get and store input from user.
    orders order;//struct variables to get values stored in struct from file
    FILE *fp=NULL;
    char saveopt='s',searchname[N];
    char continueopt='s';
    time_t tm;/*To produce Current date and time*/
    time(&tm); //--->realsyntax of time
    while(continueopt=='s')
    {
        system("cls");//clears screen
    int searchfound=0;
    float total=0;
    //Dashboard
    printf("\t\t=========VR.Restaurant=========");
    printf("\n\nPlease select your prefered operation: ");
    printf("\n\n\t\t1.Generate Invoice");
    printf("\n\t\t2.Show All Invoice");
    printf("\n\t\t3.Search Invoice");
    printf("\n\t\t4.Exit");

    printf("\n\nYour choice: ");
    scanf("%d",&opt);
    fgetc(stdin);
    switch(opt)
    {
    case 1:
        
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer,N,stdin);
        ord.customer[strlen(ord.customer)-1]=0;
        strcpy(ord.date,ctime(&tm));
        printf("\nPlease enter the number of items: ");
        scanf("%d",&ord.NumbeOfItems);

        for(int i=0;i<ord.NumbeOfItems;i++)
        {
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the name of item %d: ",i+1);
            fgets(ord.itm[i].item,N,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please enter the quantity: ");
            scanf("%d",&ord.itm[i].qty);
            printf("Please enter the unit prize: ");
            scanf("%f",&ord.itm[i].price);
            total+=ord.itm[i].qty*ord.itm[i].price;
        }
        generateBillHeader(ord.customer,ord.date);
        for(int i=0;i<ord.NumbeOfItems;i++)
            {
        generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            }
        generateBillFooter(total);
        printf("\nDo you want to save the invoice[s/n]: ");
        scanf("%s",&saveopt);
        if(saveopt=='s')
        {
            fp=fopen("Bills.txt","a+");
            fwrite(&ord,sizeof(orders),1,fp);//writes full struct into file using its adress
            if(fp!=0)
                printf("\nSuccessfully saved\n\n");
            else
                printf("\nError saving");
            fclose(fp);
        }
        break;

    case 2:
        
        fp=fopen("Bills.txt","r");
        printf("\n *****Your Previous Invoices*****\n");
        while(fread(&order,sizeof(orders),1,fp))
        {
            total=0;
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.NumbeOfItems;i++)
            {
            generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
            total+=order.itm[i].qty*order.itm[i].price;
            }
            generateBillFooter(total);
        }
        fclose(fp);
            break;

    case 3:
        printf("\nEnter name of invoice to be searched: ");
        fgets(searchname,N,stdin);
        searchname[strlen(searchname)-1]=0;
        
        fp=fopen("Bills.txt","r");
        printf("\n\t *****%s Invoice*****",searchname);
        while(fread(&order,sizeof(orders),1,fp))
        {
            total=0;
            if(!strcmp(order.customer,searchname))
            {
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.NumbeOfItems;i++)
            {
            generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
            total+=order.itm[i].qty*order.itm[i].price;
            }
            generateBillFooter(total);
            searchfound=1;
            }
        }
        if(searchfound==0)
            printf("\nSorry %s invoice is not found",searchname);
        fclose(fp);
        break;

    case 4:
        printf("\n\t\tExited.\n\t\tThank you!\n");
        exit(0);
        break;

    default:
        printf("\nInvalid Choice!\n\n");
    }
    printf("\nDo you want continue[s/n]: ");
    scanf("%s",&continueopt);
    printf("\n\n");
    }

    printf("\n");

    return 0;
}