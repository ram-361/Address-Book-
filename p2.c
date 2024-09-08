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
struct address_book temp,temp1;
int count,n;
long int pos;
int my_isalpha(char a[])
{
    int flag=1;
    for(int i=0;a[i]!='\0';i++)
    {
        if(!(a[i]<='z'&&a[i]>='a')||(a[i]<='Z'&&a[i]>='A'))
        {
            flag=0;
            break;
        }
    }
    return flag;
}
int my_isnum(char a[])
{
    int flag=1;
    for(int i=0;a[i]!='\0';i++)
    {
        if(!(a[i]>='0'&&a[i]<='9'))
        {
            flag=0;
            break;
        }
    }
    return flag;
}
int number_cmp(struct address_book a,FILE *fp,char *str)
{
    fp=fopen("addressbook.dat","rb");
    rewind(fp);
    while((fread(&a,sizeof(a),1,fp)==1))
    {
        if (strcmp(a.mobile,str)==0)
        {
            fclose(fp);
            return 0;
        }  
    }
    fclose(fp);
    return 1;
}
int mail_cmp(struct address_book a,FILE *fp,char *str)
{
    fp=fopen("addressbook.dat","rb");
    rewind(fp);
    while((fread(&a,sizeof(a),1,fp)==1))
    {
        if (strcmp(a.mail_id,str)==0)
        {
            fclose(fp);
            return 0;
        }  
    }
    fclose(fp);
    return 1;
}
int valid_number(char str[])
{
    if(my_isnum(str)==0)
    {
        return 0;
    }
    if(strlen(str)!=10)
    {
        return 0;
    }
    
}
int valid_mail(char str[])
{
    if(strchr(str,' ')!=NULL)
        {
            //printf("enter mail without spaces !\n");
            return 0;
        }
        for(char i='A';i<='Z';i++)
        {
        if(strchr(str,i)!=NULL)
        {
            //printf("enter mail without capital letters !\n");
            return 0;
        }
        }
        char *c=strchr(str,'@');
        if(c!=NULL)
        {
            if(!(isalpha(*(c+1))||isdigit(*(c+1))&&isalpha(*(c-1))||isdigit(*(c-1))))
            {
                
                return 0;
            }
        }
        else
        {
            //printf("Enter valid mail with @ !\n");
            return 0;
        }
        int l=strlen(str);
        if(!(strstr((str+l-4),".com")))
        {
            //printf("Email must end with .com !");
            return 0;
        }
}
int select_search()
{ 
    int sel=0;
    do
    {
        printf("1.search by name :\n2.search by mobile :\n3.search by mail_id :\nselect between those 3.\n");
        scanf("%d",&sel);
        getchar();
    } while (!(sel>=1&&sel<=3));
    return sel;
}
int search_found(struct address_book a,char *str,int sel,FILE *fp)
{
    n=0;
    long int c=0;
    fp=fopen("addressbook.dat","rb");
    printf("----------------------------------------------------------------------\n");
    printf("| %-8s%-15s%-13s%-30s |\n","S.N0","NAME","MOBILE NO","MAIL ID");
    printf("----------------------------------------------------------------------\n");
    while((fread(&a,sizeof(a),1,fp)==1))
    {
        if(sel==1)
        {
        if(strcmp(a.name,str)==0)
        {
            printf("| %-8d%-15s%-13s%-30s |\n",a.serial,a.name,a.mobile,a.mail_id);
            n++;
            pos=c;
        }
        c=ftell(fp);
        }
        if(sel==2)
        {
        if(strcmp(a.mobile,str)==0)
        {
            printf("| %-5d%-20s%-13s%-30s |\n",a.serial,a.name,a.mobile,a.mail_id);
            n++;
            pos=c;
        }
        c=ftell(fp);
        }
        if(sel==3)
        {
        if(strcmp(a.mail_id,str)==0)
        {
            printf("| %-5d%-20s%-13s%-30s |\n",a.serial,a.name,a.mobile,a.mail_id);
            n++;
            pos=c;
        }
        c=ftell(fp);
        }    
    }
    printf("----------------------------------------------------------------------\n");
    fclose(fp);
    return n;
}
int select_edit()
{ 
    int sel=0;
    do
    {
        printf("1.edit name :\n2.edit mobile :\n3.edit mail_id :\nselect between those 3.\n");
        scanf("%d",&sel);
        getchar();
    } while (!(sel>=1&&sel<=3));
    return sel;
}
void edit_details(struct address_book contact,FILE *fp)
{
    char str[30];
    int sel=0;
    struct address_book new;
    do
    {
        sel=select_edit();
    } while (!(sel>=1&&sel<=3));
    fp=fopen("addressbook.dat","rb+");
    fseek(fp,pos,SEEK_SET);
    fread(&new,sizeof(new),1,fp);
    if(sel==1)
    {
        while(1)
        {
            printf("Enter name :");
            scanf(" %[^\n]",str);
            if(my_isalpha(str)==0)
            {
                printf("Enter a valid name !\n");
                continue;
            }
            break;
        }
        strcpy(new.name,str);
    }
    if(sel==2)
    {
        while(1)
        {
           printf("Enter number  :");
           scanf(" %[^\n]",str);
           if(valid_number(str)==0)
            {
                printf("please enter 10 digits !\n");
                continue;
            }
            break;
        }
        strcpy(new.mobile,str);
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
        strcpy(new.mail_id,str);
    }
    rewind(fp);
    fseek(fp,pos,SEEK_SET);
    fwrite(&new,sizeof(new),1,fp);
    fclose(fp);
}
void edit_details1(struct address_book contact,FILE *fp,int s)
{
    if(n)
    {
        fp=fopen("addressbook.dat","rb+");
        rewind(fp);
        while((fread(&contact,sizeof(contact),1,fp)==1))
        {
            if(contact.serial==s)
            {
                edit_details(contact,fp);
            }
        }
        fclose(fp);   
    }
}
int delete_details(struct address_book contact,FILE *fp)
{
    struct address_book temp,temp1;
    fp=fopen("addressbook.dat","rb+");
    fseek(fp,pos,SEEK_SET);
    fread(&temp,sizeof(temp),1,fp);
    fseek(fp,-sizeof(temp),SEEK_END);
    fread(&temp1,sizeof(temp1),1,fp);
    temp1.serial=temp.serial;
    fclose(fp);
    fp=fopen("addressbook.dat","rb+");
    fseek(fp,pos,SEEK_SET);
    fwrite(&temp1,sizeof(temp1),1,fp);
    fclose(fp);
    count--;
    fp=fopen("addressbook.dat","rb+");
    FILE *f=fopen("temp.dat","wb+");
    for(int i=0;i<count;i++)
    {
        fread(&temp1,sizeof(temp1),1,fp);
        fwrite(&temp1,sizeof(temp1),1,f);
    }
    fclose(fp);
    fclose(f);
    remove("addressbook.dat");
    rename("temp.dat","addressbook.dat");
}
void delete_details1(struct address_book contact,FILE *fp,int s)
{
    if(n)
    {
        fp=fopen("addressbook.dat","rb+");
        rewind(fp);
        while((fread(&contact,sizeof(contact),1,fp)==1))
        {
            if(contact.serial==s)
            {
                delete_details(contact,fp);
            }
        }
        fclose(fp);   
    }
}