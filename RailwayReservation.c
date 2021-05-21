#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "conio2.h"
#include "RailwayReservation.h"

/* A function to print all the activities on the console */
int enterchoice()
{
    int choice;
    int i;
    gotoxy(25,1);
    textcolor(YELLOW);
    printf("***RAILWAY RESERVATION SYSTEM***\n");
    for(i=0;i<80;i++)
        printf("-");
    printf("\n\nSelect an option: ");
    printf("\n\n1- View Trains");
    printf("\n2- Book Ticket");
    printf("\n3- View Ticket");
    printf("\n4- Search Ticket No");
    printf("\n5- View All Bookings");
    printf("\n6- View Train Bookings");
    printf("\n7- Cancel Ticket");
    printf("\n8- Cancel Train");
    printf("\n9- Quit");
    printf("\n\nEnter choice: ");
    fflush(stdin);
    scanf("%d",&choice);
    return choice;
}
/* End of function enterchoice() */

/* A function to add trains in the file alltrains.dat */
void add_trains()
{
    FILE *fp=fopen("F://RailwayReservationSystem//alltrains.dat","rb");
    if(fp==NULL)
    {
        Train alltrains[6]={
        {"123","BPL","GWA",1500,1000},
        {"456","BPL","DEL",2000,1500},
        {"789","SWN","BPL",3000,2500},
        {"101","PNBE","BPL",4000,3500},
        {"102","SWN","PUNE",5000,4000},
        {"103","DEL","PUNE",6000,5000}
                    };
        fp=fopen("F://RailwayReservationSystem//alltrains.dat","wb");
        fwrite(alltrains,6*sizeof(Train),1,fp);
        printf("File created and saved.");
        fclose(fp);
    }
    else
    {
        printf("File already present.");
        fclose(fp);
    }

}
/* End of function add_trains() */

/* A function to view trains list from the file alltrains.dat */
void view_trains()
{
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FAIR\tSECOND AC FAIR\n");
    for(i=0;i<80;i++)
        printf("-");
    FILE *fp=fopen("F://RailwayReservationSystem//alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    }
    printf("\n\n\n\n");
    fclose(fp);
    printf("Press any key to go back to the main menu...");
}
int check_train_no(char *trainno)
{
    FILE *fp=fopen("F://RailwayReservationSystem//alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        if(strcmp(tr.train_no,trainno)==0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
/* End of function view_trains() */

/* A function to book ticket */
int book_ticket(Passenger p)
{
    if(get_booked_ticket_count(p.train_no,p.p_class)==2)
    {
        textcolor(LIGHTRED);
        printf("\nAll seats are full in %c class of train no %s.",p.p_class,p.train_no);
        return -1;
    }
    p.ticket_no=last_ticket_no()+1;
    FILE *fp=fopen("F://RailwayReservationSystem//allbookings.dat","ab");
    if(fp==NULL)
    {
        printf("Sorry! File cannot be opened.");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return p.ticket_no;
}
/* End of function book_ticket() */

/* A function to check if mobile no inputted by the user is valid or not */
int check_mob_no(char *p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;
    while(*p_mob!='\0')
    {
        if(isdigit(*p_mob)==0)
            return 0;
        p_mob++;
    }
    return 1;
}
/* End of function check_mob_no() */

/* A function to accept mobile no from the user */
char * accept_mob_no()
{
    clrscr();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit.");
    gotoxy(1,1);
    textcolor(YELLOW);
    static char mob_no[11];
    int valid;
    int length;
    length=printf("Enter mobile no: ");
    do
    {
        gotoxy(length+1,1);
        textcolor(YELLOW);
        fflush(stdin);
        scanf("%s",mob_no);
        if(strcmp(mob_no,"0")==0)
        {
            clrscr();
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Cancelling input. Please wait...");
            sleep(3);
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid==0)
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Invalid mobile no.");
            getch();
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(length+1,1);
            printf("\t\t");
        }
    }while(valid==0);
    clrscr();
    return mob_no;
}
/* End of function accept_mob_no() */

/* A function to accept ticket no from the user */
int accept_ticket_no()
{
    clrscr();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit.");
    gotoxy(1,1);
    textcolor(YELLOW);
    int valid;
    int ticket_no;
    int length;
    length=printf("Enter ticket no: ");
    do
    {
        valid=1;
        fflush(stdin);
        if(scanf("%d",&ticket_no)==1)
        {
            if(ticket_no==0)
            {
                clrscr();
                gotoxy(1,25);
                textcolor(LIGHTRED);
                printf("Cancelling input. Please wait...");
                sleep(3);
                textcolor(YELLOW);
                clrscr();
                return 0;
            }
            if(ticket_no<0)
            {
                gotoxy(1,25);
                textcolor(LIGHTRED);
                printf("Error! Ticket number should be positive.");
                valid=0;
                getch();
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t\t");
                gotoxy(length+1,1);
                printf("\t\t\t\t");
                gotoxy(length+1,1);
                textcolor(YELLOW);
            }
        }
        else
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Ticket number should be positive.");
            valid=0;
            getch();
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(length+1,1);
            printf("\t\t\t\t");
            gotoxy(length+1,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return ticket_no;
}
/* End of function accept_ticket_no() */

/* A function to view tickets from the file allbookings.dat */
void view_ticket(int ticket_no)
{
    FILE *fp=fopen("F://RailwayReservationSystem//allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo tickets found!");
        return;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(ticket_no==pr.ticket_no)
        {
            printf("\nNAME: %s\nGENDER: %c\nTRAIN NO: %s\nCLASS : %c\nADDRESS: %s\nAGE: %d\nMOBILE NO: %s\nTICKET NO: %d",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticket_no);
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    textcolor(LIGHTRED);
    printf("\nDetails of ticket no %d is not found!",ticket_no);
    return;
}
/* End of function view_ticket() */

/* A function to accept passenger's detail from the user */
Passenger *get_passenger_details()
{
    /* Inputting passenger's name */
    clrscr();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit.");
    gotoxy(1,1);
    textcolor(YELLOW);
    static Passenger pr;
    printf("Enter passenger's name: ");
    fflush(stdin);
    fgets(pr.p_name,20,stdin);
    char *pos;
    pos=strchr(pr.p_name,'\n');
    *pos='\0';
    if(strcmp(pr.p_name,"0")==0)
    {
        clrscr();
        gotoxy(1,25);
        textcolor(LIGHTRED);
        printf("Reservation cancelled!");
        textcolor(GREEN);
        printf("\n\nThank you for visiting us...\n");
        sleep(3);
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }

    /* Inputting Gender */
    int length;
    int valid;
    length=printf("Enter gender(M/F): ");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&pr.gender);
        if(pr.gender=='0')
        {
            clrscr();
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Reservation cancelled!");
            textcolor(GREEN);
            printf("\n\nThank you for visiting us...\n");
            sleep(3);
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(pr.gender!='M'&&pr.gender!='F')
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Gender should be M or F in uppercase.");
            valid=0;
            getch();
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(length+1,2);
            printf("\t\t\t\t");
            gotoxy(length+1,2);
            textcolor(YELLOW);
        }
    }while(valid==0);

    /* Inputting train no */
    length=printf("Enter train no: ");
    do
    {
        gotoxy(length+1,3);
        fflush(stdin);
        scanf("%s",pr.train_no);
        if(strcmp(pr.train_no,"0")==0)
        {
            clrscr();
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Reservation cancelled!");
            textcolor(GREEN);
            printf("\n\nThank you for visiting us...\n");
            sleep(3);
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_train_no(pr.train_no);
        if(valid==0)
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Invalid train no.");
            getch();
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(length+1,3);
            printf("\t\t");
            textcolor(YELLOW);
        }
    }while(valid==0);

    /* Inputting travelling class */
    length=printf("Enter travelling class(First AC-F,Second AC-S): ");
    do
    {
        valid=1;
        gotoxy(length+1,4);
        fflush(stdin);
        scanf("%c",&pr.p_class);
        if(pr.p_class=='0')
        {
            clrscr();
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Reservation cancelled!");
            textcolor(GREEN);
            printf("\n\nThank you for visiting us...\n");
            sleep(3);
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(pr.p_class!='F'&&pr.p_class!='S')
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Class should be F or S in uppercase.");
            valid=0;
            getch();
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(length+1,4);
            printf("\t\t");
            textcolor(YELLOW);
        }
    }while(valid==0);

    /* Inputting address */
    printf("Enter address: ");
    fflush(stdin);
    fgets(pr.address,100,stdin);
    char *p=strchr(pr.address,'\n');
    *p='\0';
    if(strcmp(pr.address,"0")==0)
    {
        clrscr();
        gotoxy(1,25);
        textcolor(LIGHTRED);
        printf("Reservation cancelled!");
        textcolor(GREEN);
        printf("\n\nThank you for visiting us...\n");
        sleep(3);
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }

    /* Inputting age */
    length=printf("Enter age: ");
    do
    {
        valid=1;
        gotoxy(length+1,6);
        fflush(stdin);
        if(scanf("%d",&pr.age)==1)
        {
            if(pr.age==0)
            {
                clrscr();
                gotoxy(1,25);
                textcolor(LIGHTRED);
                printf("Reservation cancelled!");
                textcolor(GREEN);
                printf("\n\nThank you for visiting us...\n");
                sleep(3);
                textcolor(YELLOW);
                clrscr();
                return NULL;
            }
            if(pr.age<0||pr.age>140)
            {
                valid=0;
                gotoxy(1,25);
                textcolor(LIGHTRED);
                printf("Error! Invalid age.");
                getch();
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t\t");
                gotoxy(length+1,6);
                printf("\t\t");
                textcolor(YELLOW);
            }
        }
        else
        {
            valid=0;
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Invalid age.");
            getch();
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(length+1,6);
            printf("\t\t");
            textcolor(YELLOW);
        }
    }while(valid==0);

    /* Inputting mobile no */
    length=printf("Enter mobile no: ");
    do
    {
        gotoxy(length+1,7);
        textcolor(YELLOW);
        fflush(stdin);
        scanf("%s",pr.mob_no);
        if(strcmp(pr.mob_no,"0")==0)
        {
            clrscr();
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Reservation cancelled!");
            textcolor(GREEN);
            printf("\n\nThank you for visiting us...\n");
            sleep(3);
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_mob_no(pr.mob_no);
        if(valid==0)
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Invalid mobile no.");
            getch();
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(length+1,7);
            printf("\t\t");
        }
    }while(valid==0);

    printf("\n\n\nPassenger's details added successfully. Press any key to continue...");
    getch();
    clrscr();
    return &pr;
}

/* Getting ticket count from the file allbookings.dat */
int get_booked_ticket_count(char *train_no, char tc)
{
    FILE *fp=fopen("F://RailwayReservationSystem//allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger psr;
    int count=0;
    while(fread(&psr,sizeof(psr),1,fp)==1)
    {
        if(strcmp(psr.train_no,train_no)==0&&psr.p_class==tc)
            count++;
    }
    fclose(fp);
    return count;
}
/* End of function get_booked_ticket_count() */

/* A function to get last ticket no from the file allbookings.dat */
int last_ticket_no()
{
    FILE *fp=fopen("F://RailwayReservationSystem//allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger psr;
    fseek(fp,-1L*sizeof(psr),SEEK_END);
    fread(&psr,sizeof(psr),1,fp);
    fclose(fp);
    return psr.ticket_no;
}
/* End of function last_ticket_no() */

/* A function to generate ticket no */
int *get_ticket_no(char *p_mob_no)
{
    FILE *fp=fopen("F://RailwayReservationSystem//allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File can't be opened.");
        fclose(fp);
        return NULL;
    }
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
            count++;
    }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    int *p=(int *)malloc((count+1)*sizeof(int));
    rewind(fp);
    count=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
            p[count]=pr.ticket_no;
            count++;
        }
    }
    p[count]=-1;
    fclose(fp);
    return p;
}
/* End of function get_ticket_no() */

/* A Function to view tickets */
void view_all_tickets(char *pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! No tickets booked for mobile no %s",pmob_no);
        textcolor(YELLOW);
        printf("\nPress any key to go back to the main menu...");
        textcolor(YELLOW);
        return;
    }
    printf("Following are tickets booked for the mobile no %s",pmob_no);
    int i;
    printf("\n\nTICKET NUMBERS");
    printf("\n--------------------------");
    for(i=0;pticket_no[i]!=-1;i++)
        printf("\n%d",pticket_no[i]);
    printf("\n\nPress any key to go back to the main menu...");
    getch();
    free(pticket_no);
}
/* End of function view_all_tickets() */

/* A function to accept train no from the user */
char *accept_train_no()
{
    clrscr();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit.");
    gotoxy(1,1);
    textcolor(YELLOW);
    static char train_no[10];
    int length;
    int valid;
    length=printf("Enter train no: ");
    do
    {
        gotoxy(length+1,1);
        fflush(stdin);
        scanf("%s",train_no);
        if(strcmp(train_no,"0")==0)
        {
            clrscr();
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Cancelling input. Please wait...");
            textcolor(YELLOW);
            sleep(3);
            clrscr();
            return NULL;
        }
        valid=check_train_no(train_no);
        if(valid==0)
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Invalid train no.");
            getch();
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(length+1,1);
            printf("\t\t");
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return train_no;
}
/* End of function accept_train_no() */

/* A function to view booking details from the file allbookings.dat */
void view_bookings(char *train_no)
{
    int found=0;
    FILE *fp=fopen("F://RailwayReservationSystem//allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings found in train no %s!",train_no);
        textcolor(YELLOW);
        printf("\n\nPress any key to go back to the main menu...");
        getch();
        return;
    }
    Passenger pr;
    printf("TICKET NO\tCLASS\tNAME\t\t\tGENDER\tAGE\tMOBILE NO\n");
    int i;
    for(i=0;i<80;i++)
        printf("-");
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            printf("%d\t\t%c\t%s",pr.ticket_no,pr.p_class,pr.p_name);
            gotoxy(49,row);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            row++;
            found=1;
        }
    }
    if(found==0)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("\n\nNo details of bookings in train no %s found",train_no);
    }
    textcolor(YELLOW);
    printf("\n\nPress any key to go back to the main menu...");
    getch();
    fclose(fp);
}
/* End of function view_bookings() */

/* A function to cancel a booked ticket */
int cancel_ticket(int ticket_no)
{
    int result;
    FILE *fp1=fopen("F://RailwayReservationSystem//allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo ticket found for ticket no %d",ticket_no);
        return -1;
    }
    FILE *fp2=fopen("E://RailwayReservationSystem//temp.dat","wb");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticket_no==ticket_no)
            found=1;
        else
            fwrite(&pr,sizeof(pr),1,fp2);
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("F://RailwayReservationSystem//temp.dat");
    }
    else
    {
        result=remove("F://RailwayReservationSystem//allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("F://RailwayReservationSystem//temp.dat","F://RailwayReservationSystem//allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;

}
/* End of function cancel_ticket() */

/* A function to view all bookings from the file allbookings.dat */
void view_all_bookings()
{
    clrscr();
    FILE *fp=fopen("F://RailwayReservationSystem//allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings found!");
        textcolor(YELLOW);
        printf("\n\nPress any key to go back to the main menu...");
        getch();
        return;
    }
    Passenger pr;
    printf("TICKET NO\tCLASS\tNAME\t\t\tGENDER\tAGE\tMOBILE NO\n");
    int i;
    for(i=0;i<80;i++)
        printf("-");
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        printf("%d\t\t%c\t%s",pr.ticket_no,pr.p_class,pr.p_name);
        gotoxy(49,row);
        printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
        row++;
    }
    textcolor(YELLOW);
    printf("\n\nPress any key to go back to the main screen...");
    getch();
    fclose(fp);
    clrscr();
}
/* End of function view_all_bookings() */

/* A function to cancel a train */
int cancel_train(char *train_no)
{
    int result;
    FILE *fp1=fopen("F://RailwayReservationSystem//allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet!");
        return -1;
    }
    FILE *fp2=fopen("F://RailwayReservationSystem//temp.dat","wb");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
            found=1;
        else
            fwrite(&pr,sizeof(pr),1,fp2);
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
        remove("F://RailwayReservationSystem//temp.dat");
    else
    {
        result=remove("F://RailwayReservationSystem//allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("F://RailwayReservationSystem//temp.dat","F://RailwayReservationSystem//allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;
}
/* End of function cancel_train() */
