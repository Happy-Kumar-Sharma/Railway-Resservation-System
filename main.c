#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "RailwayReservation.h"
int main()
{
    int choice,ticket_no,result;
    char *pmob_no;
    int *pticket_no;
    add_trains();
    Passenger *ptr;
    char *ptrain_no;
    while(1)
    {
        choice=enterchoice();
        if(choice==9)
        {
            textcolor(GREEN);
            clrscr();
            printf("\nThank you for visiting us...\n\n");
            textcolor(WHITE);
            return 0;
        }
        switch(choice)
            {
            case 1:
                        clrscr();
                        view_trains();
                        getch();
                        clrscr();
                        break;
            case 2:
                        ptr=get_passenger_details();
                        clrscr();
                        if(ptr!=NULL)
                        {
                            ticket_no=book_ticket(*ptr);
                            if(ticket_no==-1)
                            {
                                textcolor(LIGHTRED);
                                printf(" Booking failed!");
                            }
                            else
                            {
                                textcolor(LIGHTGREEN);
                                printf("\nTicket booked successfully.");
                                printf(" Your ticket number is %d",ticket_no);
                            }
                            textcolor(YELLOW);
                            printf("\n\n\n\nPress any key to go back to the main screen...");
                            getch();
                            clrscr();
                        }
                        break;
            case 3:
                        clrscr();
                        ticket_no=accept_ticket_no();
                        if(ticket_no!=0)
                        {
                            view_ticket(ticket_no);
                            textcolor(YELLOW);
                            printf("\n\nPress any key to go back to the main screen...");
                            getch();
                        }
                        clrscr();
                        break;
            case 4:
                        clrscr();
                        pmob_no=accept_mob_no();
                        if(pmob_no!=NULL)
                        {
                            pticket_no=get_ticket_no(pmob_no);
                            if(pticket_no!=NULL)
                            {
                                view_all_tickets(pmob_no,pticket_no);
                            }
                            else
                            {
                                textcolor(LIGHTRED);
                                printf("\nNo booking found against the mobile no %s",pmob_no);
                                textcolor(YELLOW);
                                printf("\n\nPress any key to go back to the main menu...");
                                getch();
                            }
                        }
                        clrscr();
                        break;
            case 5:
                        view_all_bookings();
                        break;
            case 6:
                        clrscr();
                        ptrain_no=accept_train_no();

                        if(ptrain_no!=NULL)
                            view_bookings(ptrain_no);
                        clrscr();
                        break;
            case 7:
                        clrscr();
                        ticket_no=accept_ticket_no();
                        if(ticket_no!=0)
                        {
                            result=cancel_ticket(ticket_no);
                            if(result==0)
                            {
                                textcolor(LIGHTRED);
                                printf("Sorry! No tickets booked for the ticket no %d",ticket_no);
                            }
                            else if(result==1)
                            {
                                textcolor(LIGHTGREEN);
                                printf("\nTicket no %d successfully cancelled.",ticket_no);
                            }
                            else if(result==2)
                            {
                                textcolor(LIGHTRED);
                                printf("Sorry! Error in cancellation. Try after sometime.");
                            }
                            textcolor(YELLOW);
                            printf("\n\nPress any key to go back to the main menu...");
                            getch();
                        }
                        clrscr();
                        break;
            case 8:
                        clrscr();
                        ptrain_no=accept_train_no();
                        if(ptrain_no!=NULL)
                        {
                            result=cancel_train(ptrain_no);
                            if(result==0)
                            {
                                textcolor(LIGHTRED);
                                printf("Sorry! No trains found.");
                            }
                            else if(result==1)
                            {
                                textcolor(LIGHTGREEN);
                                printf("\nTrain no %s successfully cancelled.",ptrain_no);
                            }
                            else if(result==2)
                            {
                                 textcolor(LIGHTRED);
                                 printf("Sorry! Error in cancellation. Try after sometime.");

                            }
                            textcolor(YELLOW);
                            printf("\n\nPress any key to go back to the main menu...");
                            getch();
                        }
                        clrscr();
                        break;
            default:
                        textcolor(LIGHTRED);
                        printf("\nWrong Choice! Try Again.");
                        getch();
                        clrscr();
            }
    }
    return 0;
}
