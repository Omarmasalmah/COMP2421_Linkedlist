#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 50
/*   ---------|------------********************-----------|--------------------------------------
              |      --------->OMAR MASALMAH<---------    |
              |       --------->1200060<---------         |
              |      --------->SECTION (1)<---------      |
              |       --------->PROJECT 1<---------       |
     ---------|------------********************-----------|--------------------------------------

*/

int num_of_pass=0;
int num_of_bus=0;

typedef char String[size];
typedef struct Passenger* ptrP;
typedef ptrP listP;
typedef struct Bus* ptrB;
typedef ptrB listB;

void ReadBusFile(listB L);
void ReadPassengerFile(listP L);
void addPassenger(ptrP p);
void trim(char s[size]);
void assignPassenger(listB L,ptrP P,listB unmatched);
int compareTime(String time_bus,String time_passenger);
void deletePassenger(listP L);
ptrB Find(int x,listB L);
void InsertBus(listB L,int id,int date,String time,String from,String to,int price,int capacity);
void InsertPassenger(listP L,int id,int date,String time,String from,String to);
void InsertUnmatchedPassenger(listB L,ptrP P);
void printBus(listB L);
listP FindPassenger(int num,listP L);
void printPassenger(listP L);
void printBusAfterAssign(listB L);
void printUnmatchedPassenger(listB unmatched);
void printSpecificBus(listB L);
void deleteBus(listB, listP);
void InsertPassengerInBus(listB L,ptrP P);
void printPassengerAfterAssign(listP L);
//void deletePassenger(listB list, listB list2, int id);

struct Passenger //struct of Passenger
{

    int ID;
    int Date;
    String Time;
    String From;
    String To;

    ptrP Next;
};

struct Bus  //struct of Bus
{

    int ID;
    int  Date;
    String  Time;
    String From;
    String To;
    int Price;
    int Capacity;
    int counter;
    ptrB Next;
    ptrP NextPassenger;

};
int main()
{

    listP P=(ptrP)malloc(sizeof(struct Passenger));//create passenger list
    ptrB Unmatched ;
    Unmatched = (ptrB)malloc(sizeof(struct Bus));//create unmatched list
    Unmatched->Next=NULL;//initializing it to pointing to null
    Unmatched->NextPassenger = NULL;
    listB b =(ptrB)malloc(sizeof(struct Bus));//create bus list
    b->Next = NULL;
    P->Next=NULL;

    ptrP pos,temp; //declare passenger pointers

    int number;
    printf("-*-*-*-* WELCOME TO MY PROJECT -*-*-*-*\n");

    while(number!=9)  //menu to display to the user
    {
        printf("-------------------------------------------------------------------------------------------------\n");
        printf(" 1- Load the bus information file\n");
        printf(" 2- Load the passenger information file\n");
        printf(" 3- Assign passengers and print assignment information \n");
        printf(" 4- Print a specific bus information along with its passengers information (names and IDs)\n");
        printf(" 5- Print unmatched passengers\n");
        printf(" 6- Add new passenger\n");
        printf(" 7- Delete passenger\n");
        printf(" 8- Delete bus number\n");
        printf(" 9- Exit\n");

        scanf("%d",&number);


        switch(number)  //switch case
        {

        case 1:
            ReadBusFile(b);
            printBus(b);
            break;
        case 2:
            ReadPassengerFile(P);
            printPassenger(P);
            break;
        case 3:
            pos = P->Next;
            while(pos != NULL)
            {
                temp = pos->Next;
                assignPassenger(b,pos,Unmatched);
                pos = temp ;
            }
            printBusAfterAssign(b);

            break;
        case 4:
            printSpecificBus(b);
            break;
        case 5:
            printUnmatchedPassenger(Unmatched);
            break;
        case 6:
            addPassenger(P);
            pos = P->Next;
            while(pos != NULL)
            {
                temp = pos->Next;
                assignPassenger(b,pos,Unmatched);
                pos = temp ;
            }
            printBusAfterAssign(b);

            break;
        case 7:

        deletePassenger(P);
            break;

        case 8:
            deleteBus(b,Unmatched);
            break;
        case 9:
            printf("Exit the program.\n");
            break;
        default:
            printf("Wrong input!! Please try again.\n\n");

        }
    }

    return 0;
}

void ReadBusFile(listB L) //function to read busses file
{
    ptrB b =(ptrB)malloc(sizeof(struct Bus));
    b->Next = NULL;
    char line[150];

    FILE *bus;

    bus = fopen("busses.txt", "r");//open bus file to read
    if (bus ==NULL)
    {
        printf("The File is empty,Try Again");
        exit (-1) ;
    }
    int id,date;
    String  time,from,to;
    int price;
    int capacity;

    while(fgets(line,150,bus)!=NULL)
    {

        sscanf(line,"%d#%d#%[^#]#%[^#]#%[^#]#%d#%d",&id,&date,time,from,to,&price,&capacity);//to read the line and split it by #
        InsertBus(L,id,date,time,from,to,price,capacity);//call method to insert bus to list

    }
}
void ReadPassengerFile(listP L) //function to read passenger file
{
    char line[150];

    FILE *pass;

    pass = fopen("passenger.txt", "r"); //open passenger file to read
    if (pass ==NULL)
    {
        printf("The File is empty,Try Again");
        exit (-1) ;
    }
    int id;
    int date;
    String time,from,to;
    while(fgets(line,150,pass)!=NULL)
    {

        sscanf(line,"%d#%d#%[^#]#%[^#]#%[^#]#",&id,&date,time,from,to);//to read the line and split it by #
        InsertPassenger(L,id,date,time,from,to); //call method to insert passenger to list
    }
}

void printBus(listB L) //print busses informations
{
    ptrB b = L->Next;
    printf("------------------------------------------------------------------------------------------------\n");
    printf("%-12s%-15s%-15s%-17s%-17s%-10s%s\n"," ID","Date","Time","From","To","Price","Capacity");
    printf("------------------------------------------------------------------------------------------------\n");
    while(b!=NULL)

    {
        printf(" %-12d%-15d%-15s%-17s%-19s%-10d%d\n", b->ID,b->Date,b->Time,b->From,b->To,b->Price,b->Capacity);
        b=b->Next;
        printf("\n");

    }
}
void printPassenger(listP L) //print passengers informations
{
    ptrP P = L->Next;
    printf("--------------------------------------------------------------------------------------------\n");
    printf("%-12s%-15s%-15s%-17s%-17s\n"," ID","Date","Time","From","To");
    printf("--------------------------------------------------------------------------------------------\n");
    while(P!=NULL)

    {
        printf("%-12d%-15d%-15s%-17s%-19s", P->ID,P->Date,P->Time,P->From,P->To);
        P=P->Next;
        printf("\n");

    }
}

void InsertBus(listB L,int id,int date,String time,String from,String to,int price,int capacity)//insert bus to bus list
{

    if(L!=NULL)//check if the list is NULL
    {
        ptrB temp= (ptrB)malloc(sizeof(struct Bus));
        //store data to bus pointer
        temp->ID =id;
        temp->Date = date;
        strcpy(temp->Time,time);
        strcpy(temp->From,from);
        strcpy(temp->To,to);
        temp->Price=price;
        temp->Capacity=capacity;
        temp->NextPassenger=NULL;
        temp->counter=0;


        while(L->Next != NULL)
            L=L->Next;

        L->Next = temp;

        temp->Next = NULL;
        num_of_bus++;

    }
    else
        printf("Erroooooooor.The list is Null\n");
}

void InsertPassenger(listP L,int id,int date,String time,String from,String to)//insert passenger to passenger list
{

    if(L!=NULL)
    {
        ptrP temp= (ptrP)malloc(sizeof(struct Passenger));
        //store data to passenger pointer
        temp->ID =id;
        temp->Date = date;
        strcpy(temp->Time,time);
        strcpy(temp->From,from);
        strcpy(temp->To,to);


        while(L->Next != NULL)
            L=L->Next;

        L->Next = temp;

        temp->Next = NULL;
        num_of_pass++;

    }
    else
        printf("Erroooooooor.The list is Null\n");
}

void trim(char s[size])  //trim the string from \n last line
{
    for(int i=0; i<size; i++)
    {
        if(s[i]=='\n')
        {
            s[i]='\000';
        }
    }

}
int compareTime(String time_bus,String time_passenger)  //compare which time is suitable
{
    int hourBus,minuteBus,hourPassenger,minutePassenger ;
    String Timebus,Timepass;
    strcpy(Timebus,time_bus);
    strcpy(Timepass,time_passenger);

    sscanf(Timebus,"%d:%d",&hourBus,&minuteBus);//read the string and split it by : and store the values
    sscanf(Timepass,"%d:%d",&hourPassenger,&minutePassenger);


    if(hourBus == hourPassenger)
    {
        if(minuteBus < minutePassenger)
        {
            return -1;
        }
        else if(minuteBus == minutePassenger )
        {
            return 0 ;
        }
        else
        {
            return 1;
        }
    }
    else if(hourBus < hourPassenger)
    {
        return -1;
    }
    else
    {
        return 1;
    }

}
void InsertUnmatchedPassenger(listB L,ptrP P) //insert unmatching passengers to unmatched list
{
    if(L!=NULL)
    {
        ptrB temp= (ptrB)malloc(sizeof(struct Bus));

        temp->ID =P->ID;
        temp->Date = P->Date;
        strcpy(temp->Time,P->Time);
        strcpy(temp->From,P->From);
        strcpy(temp->To,P->To);


        while(L->NextPassenger != NULL)
            L=L->NextPassenger;

        L->NextPassenger = temp;

        temp->NextPassenger = NULL;
    }
    else
        printf("erroooooooor\n");
}

void InsertPassengerInBus(listB L,ptrP P) //insert matcing passenger to suitable bus
{
    if(L!=NULL)
    {
        ptrB temp= (ptrB)malloc(sizeof(struct Bus));

        temp->ID =P->ID;
        temp->Date = P->Date;
        strcpy(temp->Time,P->Time);
        strcpy(temp->From,P->From);
        strcpy(temp->To,P->To);


        while(L->NextPassenger != NULL)
            L=L->NextPassenger;

        L->NextPassenger = temp;

        temp->NextPassenger = NULL;
    }
    else
    {
        printf("Erroooooooor.The list is Null\n");
    }
}

void assignPassenger(listB L,ptrP P,listB unmatched)  //check which bus is suitable and assign passenger on it
{
    ptrB bus = L->Next;
    ptrP Passenger;
    int flag = 0;

    while(bus != NULL)
    {
        trim(P->To);
        if(bus->counter < bus->Capacity)  //if number of passenger in bus less than the capacity of bus do
        {

            if(bus->Date==P->Date && strcmp(bus->From,P->From)==0 && strcmp(bus->To,P->To)==0) //check if date,from and to of bus and passenger are equal
            {

                if(compareTime(bus->Time,P->Time) == 0 )  //if passenger time and bus are same
                {
                    flag=1;
                    Passenger = bus->NextPassenger;
                    bus->NextPassenger=P;
                    P->Next=Passenger;

                    bus->counter +=1;
                    break;

                }
                else if(compareTime(bus->Time,P->Time) == -1)  //if passenger time more the bus time
                {
                    bus = bus->Next;
                    continue;
                }
                else //if bus time are more the passenger
                {
                    Passenger = bus->NextPassenger;
                    bus->NextPassenger=P;
                    P->Next=Passenger;
                    flag =1;

                    bus->counter +=1;//number of passenger in the bus
                    break;

                }
            }
        }

        bus = bus->Next;
    }

    if(flag == 0)  // if flag ==0  assign to the unmatched list
    {

        InsertUnmatchedPassenger(unmatched,P);//call method to insert unmatched passengers

    }
}

void printPassengerAfterAssign(listP L) //method to print passenger after assinging passengers to busses
{
    ptrP P = L;
    while(P!=NULL)

    {
        printf("%-12d%-15d", P->ID,P->Date);
        P=P->Next;
        printf("\n");

    }
    printf("--------------------------------------------------------------------------------------------------------------\n");

}
void printBusAfterAssign(listB L) //print bus infotmation after assingning
{
    ptrB b = L->Next;
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("%-12s%-15s%-15s%-17s%-12s%-10s%-12s%s\n"," ID","Date","Time","From","To","Price","Capacity","Number of Passengers");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    while(b!=NULL)

    {
        printf(" %-12d%-15d%-15s%-17s%-15s%-10d%-12d%d\n", b->ID,b->Date,b->Time,b->From,b->To,b->Price,b->Capacity,b->counter);
        printf("\n");
        if(b->NextPassenger!=NULL)
        {
            printPassengerAfterAssign(b->NextPassenger) ;
        }
        b=b->Next;

    }
}
void printUnmatchedPassenger(listB unmatched)//print unmatching passengers
{
    ptrB U = unmatched->NextPassenger;
    printf("--------------------------------------------------------------------------------------------\n");
    printf("%-12s%-15s%-15s%-17s%-17s\n"," ID","Date","Time","From","To");
    printf("--------------------------------------------------------------------------------------------\n");
    while(U!=NULL)

    {
        printf("%-12d%-15d%-15s%-17s%-19s", U->ID,U->Date,U->Time,U->From,U->To);
        U=U->NextPassenger;
        printf("\n");
    }
}
ptrB Find(int x,listB L)  //find bus by his ID
{

    ptrB p= L->Next;

    while(p != NULL && p->ID !=x)
        p=p->Next;

    if(p==NULL)
    {
        printf("There is no bus has this ID\n");
    }
    return p;

}
void printSpecificBus(listB L)  //print specific bus information
{
    int num;
    ptrB B;
    printf("Enrer the ID of the bus\n");
    scanf("%d",&num);

    B=Find(num,L);//call Find method
    while(B==NULL)
    {
        printf("Wrong ID!!Enter correct ID or -1 to exit\n");
        scanf("%d",&num);
        if(num ==-1)
        {
            main();
        }
        else
            B=Find(num,L);
    }

    if(B!=NULL)
    {
        printf("---------------------------------------------------------------------------------------------------------------------\n");
        printf("%-12s%-15s%-15s%-17s%-12s%-10s%-12s%s\n"," ID","Date","Time","From","To","Price","Capacity","Number of Passengers");
        printf("--------------------------------------------------------------------------------------------------------------------\n");

        printf(" %-12d%-15d%-15s%-17s%-15s%-10d%-12d%d\n\n", B->ID,B->Date,B->Time,B->From,B->To,B->Price,B->Capacity,B->counter);
        printPassengerAfterAssign(B->NextPassenger) ;//call method to print passenger information after assigning

    }

}

void addPassenger(ptrP p) //add new passenger
{

    int id;
    int date;
    String time,from,to;
    printf("Enter ID,Date,Time,From and To of the passenger\n");
    scanf("%d%d%s%s%s",&id,&date,time,from,to);
    InsertPassenger(p,id,date,time,from,to);


}
listP FindPrevPassenger(listP list, int id)
{
    ptrP pos = list->Next;
    if (pos->ID == id)
    {
        return list;// the prev is the head
    }
    while (pos->Next != NULL && pos->Next->ID != id)
    {
        pos = pos->Next;
    }
    return pos;
}
int IsLast(listP ptr)
{
    return ptr->Next == NULL;
}

void deletePassenger(listP L){//delete passenger from list
    ptrP p,temp;
    int key;
    printf("Enter the ID of passenegr to delete it\n");
    scanf("%d",&key);
    p = FindPrevPassenger(L,key);
    if(!IsLast(p)){
        temp = p->Next;
        p ->Next = temp->Next;
        free(temp);
    }

  }
listB FindPrevBus(listB list, int number)
{
    ptrB pos = list->Next;
    if (pos->ID == number)
    {
        return list; // the prev is the header
    }
    while (pos->Next != NULL && pos->Next->ID != number)
    {
        pos = pos->Next;
    }
    return pos;
}
listP FindPassenger(int num,listP L)//find passenger
{
    listP P;
    P = L;
    while(P!=NULL && P->ID != num)
    {
        P = P->Next;
    }
    return P;
}
void deleteBus (listB L, listP unmatched)
{
    int k;
    printf("Please enter the number of the bus you would to delete it:\n");
    scanf("%d",&k);

    listB temp1,temp2,result;
    listP t;

    temp1=L;
    temp2=L->Next;

    result = FindPrevBus(temp1,k);
    if (result ->Next != NULL)
    {
        t=result->Next->NextPassenger;
        if (t==NULL)
            printf("There's no passengers in the bus");
        else
            InsertUnmatchedPassenger(unmatched,t);
    }

    if (result->Next == NULL)
        printf("Sorry,but this bus does not exist.\n");
    else if(result->Next==temp1)
    {
        listB t1 = result->Next;
        result->Next = t1->Next;
        free (t1);
        printBusAfterAssign(L);
        printf("\n");

    }
    else
    {
        if(!IsLastB(L,result))
        {
            temp2 = result->Next;
            result->Next = temp2->Next;
            free (temp2);
            printf("Buses after delete one of them:\n");
            printBusAfterAssign(L);
            printf("\n");
        }
    }


}
int IsLastB (listB L, ptrB temp)
{
    return temp->Next == NULL;
}
