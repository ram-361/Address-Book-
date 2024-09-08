#include<stdio.h>
#include<string.h>
#include<ctype.h>
struct address_book
{
    char name[20];
    char mobile[11];
    char mail_id[30];
    int serial;
    
};
void create(struct address_book contact,FILE *fp);
int search(struct address_book contact,FILE *fp);
void edit(struct address_book contact,FILE *fp);
void delete(struct address_book contact,FILE *fp);
void list(struct address_book contact,FILE *fp);
int my_isalpha(char a[]);
int my_isnum(char a[]);
int number_cmp(struct address_book a,FILE *fp,char *str);
int mail_cmp(struct address_book a,FILE *fp,char *str);
int valid_number(char str[]);
int valid_mail(char contact[]);
int select_search();
int search_found(struct address_book a,char *str,int sel,FILE *fp);
int select_edit();
void edit_details(struct address_book contact,FILE *fp);
void edit_details1(struct address_book contact,FILE *fp,int n);
void delete_details(struct address_book contact,FILE *fp);
void delete_details1(struct address_book contact,FILE *fp,int s);
int count;
long int pos=0;
int main()
{
    struct address_book details;
    struct address_book temp;
    int select=0;
    FILE *fp;
    fp=fopen("addressbook.dat","ab+");
    if(fp==NULL)
    {
        printf("File does not exist\n");
        return -1;
    }
    else
    {
        while((fread(&details,sizeof(details),1,fp)==1))
        {
            count++;
        }
    }
    fclose(fp);
    do 
    {
        printf("1.Create contact\n2.Search contact\n3.Edit contact\n4.Delete contact\n5.List the contact\n6.Exit\n");
        printf("Select the number between 1 to 6 :");
        scanf("%d",&select);
            if(select==1)
            {
                create(details,fp);
            }
            if(select==2)
            {
                search(details,fp);
            }
            if(select==3)
            {
                edit(details,fp);
            }
            if(select==4)
            {
                delete(details,fp);
            }
            if(select==5)
            {
                list(details,fp);
            }
            if(select==6)
            {
                break;
            }
            getchar();
        // printf("Wrong selection !\n");
        // continue;
    }while(select>=1&&select<=6);  
}
void create(struct address_book contact,FILE *fp)
{
    //int flag=1;
    contact.serial=++count;
    while(1)
    {
        printf("Enter name :");
        scanf(" %[^\n]",contact.name);
        if(my_isalpha(contact.name)==0)
        {
            printf("Enter a valid name !\n");
            continue;
        }
        else
        {
            break;
        }
    }
    while(1)
    {
        printf("Enter mobile number :");
        scanf(" %[^\n]",contact.mobile);
        char str[11];
        strcpy(str,contact.mobile);

        if(valid_number(contact.mobile)==0)
        {
            printf("please enter 10 digits !\n");
            continue;
        }
        if(number_cmp(contact,fp,str)==0)
        {
            printf("Enter unique number !\n");
            continue;
        }
        break;
    }
    while(1)
    {
        printf("Enter mail id :");
        scanf(" %[^\n]",contact.mail_id);
        char str[30];
        strcpy(str,contact.mail_id);
        if(valid_mail(contact.mail_id)==0)
        {
            printf("Enter valid mail !\n");
            continue;
        }
        if(mail_cmp(contact,fp,str)==0)
        {
            printf("Enter unique Email id !\n");
            continue;
        }
        else
        {   
            break;
        }
        break;
    }
    fp=fopen("addressbook.dat","ab");
    fwrite(&contact,sizeof(contact),1,fp);
    fclose(fp);
    
}
int search(struct address_book contact,FILE *fp)
{
    char str[30];
    int sel=0;
    do
    {
        sel=select_search();
        //getchar();
    } while (!(sel>=1&&sel<=3));
    if(sel==1)
    {
        while(1)
        {
            printf("Enter name to search :");
            scanf(" %[^\n]",str);
            if(my_isalpha(str)==0)
            {
                printf("Enter a valid name !\n");
                continue;
            }
            break;
        }   
    }
    if(sel==2)
    {
        while(1)
        {
           printf("Enter number to search :");
           scanf(" %[^\n]",str);
           if(valid_number(str)==0)
            {
                printf("please enter 10 digits !\n");
                continue;
            }
            break;
        }       
    }
    if(sel==3)
    {
        while(1)
        {
        printf("Enter mail_id to search :");
        scanf(" %[^\n]",str);
        if(valid_mail(str)==0)
        {
            printf("Enter correct Email id !\n");
            continue;
        }
        break;
        }
    }
    int n=search_found(contact,str,sel,fp);
    return n;
}
void edit(struct address_book contact,FILE *fp)
{
    while(1)
    {
        int n=search(contact,fp);
        printf("%d",n);
    if(n==0)
    {
        printf("enter correct choice\n");
        continue;
    }
    if(n==1)
    {
        edit_details(contact,fp);
        break;
    }
    if(n>1)
    {
        int choice=0,s;
        printf("1.re enter !\n2.select S.No\nselect between these 2\n");
        scanf("%d",&choice);
        if(choice==1)
        {
            continue;
        }
        else if(choice==2)
        {
            printf("Enter S.NO\n");
            scanf("%d",&s);
        }
        else
        {
            printf("Enter correct choice\n");
            continue;
        }
        edit_details1(contact,fp,s);
        break;
    }
    }
}
void delete(struct address_book contact,FILE *fp)
{
    int s;
    while(1)
    {
        int n=search(contact,fp);
        if(n==0)
        {
        printf("enter correct choice\n");
        continue;
        }
        if(n==1)
        {
        delete_details(contact,fp);
        printf("Contact Removed !\n");
        break;
        }
        if(n>1)
        {
            int choice=0;
            printf("1.re enter !\n2.select S.No\nselect between these 2\n");
            scanf("%d",&choice);
            if(choice==1)
            {
                continue;
            }
            else if(choice==2)
            {
                printf("Enter S.NO\n");
                scanf("%d",&s);
            }
            else
            {
                printf("Enter correct choice\n");
                continue;
            }
            delete_details1(contact,fp,s);
            printf("Contact Removed !\n");
            break;    
        }
    }
}
void list(struct address_book contact,FILE *fp)
{
    printf("----------------------------------------------------------------------\n");
    printf("| %-8s%-15s%-13s%-30s |\n","S.NO","NAME","MOBILE NO","MAIL ID");
    printf("----------------------------------------------------------------------\n");
    fp=fopen("addressbook.dat","rb");
    while(fread(&contact,sizeof(contact),1,fp)==1)
    {
        printf("| %-8d%-15s%-13s%-30s |\n",contact.serial,contact.name,contact.mobile,contact.mail_id);
    }
    printf("----------------------------------------------------------------------\n");
    fclose(fp);
}