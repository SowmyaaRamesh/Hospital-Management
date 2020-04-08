#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <collectc/hashtable.h>
#include <collectc/array.h>
#include <ctype.h>

HashTable *symptom; 
Array *diagnosis;

struct checkin_date
{
    int dd;
    int mm;
    int yy;
};

struct checkout_date
{
    int dd;
    int mm;
    int yy;
};
struct ward
{

    char type[10];
    char status;
    char p_name[20];//patient name
    char d_name[20];//doctor name
    char a_name[20];//attender name
    struct checkin_date in;
    struct checkout_date out;
    int days;
    float fee;//fee per day


};


void ward();
void type();
void check_in();
void check_out();
void display_ward();
long int* days_calculate(int *mm,int *dd, int *yy);
long int ndays; //declared as a global variable as returning the address of a local variable shows warning

struct bloodbank
{
    char group[20];
    int units;
};

struct medicalrecords
{
	float RBCcount;
	float bloodpressure;
	float bloodsugar;
};

struct address
{
                int hno;
                char street[40];
                char city[40];
                char state[40];
};

struct patient
{
                char name[40];
                char fname[40];
                int age;
                char bg[3];
                char gender;
                char regn[10];
                struct address a;
                char ph[10];
                char disease[60];
                char doc_name[40];
                char history[200];
                char date[10];
                char treatment[40];
                char med[40];
                struct medicalrecords m;
};
void donor_search();
void blood_bank();
void add_bloodgroup();
void display_units();
void update_units();
void pat(void);
void pharmacy();
void billing();
void inpatient();
void outpatient();

struct diagnosisElement
{
    char* disease;
    int score;
};

void house();
void load();
char** getAllSymptoms();
void maintain_score(char* disease_pass);
void getusersyms();
void sortdiseases();


int main()
{
    char choice;
    printf("\n\t\t*************************************************");
    printf("\n\t\t  *** WELCOME TO HOSPITAL MANAGEMENT SYSTEM ***");
    printf("\n\t\t*************************************************\n");
    do
    {
    printf("\n\t\t** ** *MENU* ** **\n");
    printf("\t\t1.PATIENT DETAILS");
    printf("\n\t\t2.WARD DETAILS");
    printf("\n\t\t3.PHARMACY DETAILS");
    printf("\n\t\t4.BLOOD BANK DETAILS");
    printf("\n\t\t5.SYMPTOM-AILMENT MATCH");
    printf("\n\t\t6.BILLING");
    printf("\n\t\t7.EXIT");
    printf("\n\n\tEnter your choice: ");
    fflush(stdin);
    choice=getchar();
    switch(choice)
    {
        case '1':{
                    pat();
                    break;
                 }
        case '2':{
                    ward();
                    break;
                 }
		case '3':{
					pharmacy();
					break;
				 }
        case '4':{
                    blood_bank();
                    break;
                 }
        case '5':{
                    house();
                    break;
                }
		case '6':{
					billing();
					break;
		         }
        case '7':{
                    exit(1);
                 }
    }
    }while(1);

    return 0;
}

/* MODULE FOR PATIENTS */

void pat()
{
                FILE *fp,*ft;
                char another,ch;
                char reg[20],pname[40];
                int iF=0;
                long int recsize;
                struct patient p;


                fp=fopen("pat.DAT","rb+");
                if(fp==NULL)
                {
                                fp=fopen("pat.DAT","wb+");
                                if(fp==NULL)
                                {
                                                puts("\nSorry!! Cannot open file");
                                                exit(1);
                                }
                }
                recsize=sizeof(p);
                while(1)
                {


/* DISPLAY OF OPTIONS */

                                printf("\n\n\t\t\tPATIENT");
                                printf("\n\t\t1.Enter a New Entry");
                                printf("\n\t\t2.Modify Existing");
                                printf("\n\t\t3.Search an Entry by name");
                                printf("\n\t\t4.Listing of records");
                                printf("\n\t\t5.Delete an Entry");
                                printf("\n\t\t6.Main Menu");
                                printf("\n\n\t\tEnter your choice here: ");
                                fflush(stdin);
                                ch=getchar();

                                switch(ch)
                                {

/* ADDITION OF RECORDS */

                                                case '1':

                                                                fseek(fp,0,SEEK_END);
                                                                another='Y';
                                                                while(another=='Y'||another=='y')
                                                                {
                                                                w:
                                                                printf("\n\n\nEnter Registration Number (Use only digits): ");
                                                                scanf(" %s",reg);
                                                                rewind(fp);

/* CHECKING FOR REGISTRATION NUMBER */

                                                                while(fread(&p,recsize,1,fp)==1)
                                                                {

                                                                                if(strcmp(p.regn,reg)==0)
                                                                                {
                                                                                                iF=1;
												printf("\n\t\tTHIS REGISTRATION NUMBER ALREADY EXISTS. ENTER ANOTHER ONE");
                                                                                                goto w;
                                                                                }
                                                                }
                                                                if(iF==0||fread(&p,recsize,1,fp)==0)
                                                                {
                                                                                fseek (fp,0,SEEK_END);
                                                                                strcpy(p.regn,reg);
                                                                                fflush(stdin);
                                                                                printf("\nEnter the name of the patient: ");
                                                                                scanf(" %[^\n]",p.name);
                                                                                printf("\nEnter the name of the Guardian: ");
                                                                                scanf(" %[^\n]",p.fname);
										/*printf("\nEnter the gender of the patient(M for male or F for female): ");
                                                                                scanf(" %s",p.gender);*/
                                                                                printf("\nEnter the Blood group of the patient: ");
                                                                                scanf(" %s",p.bg);
                                                                                printf("\nEnter the age of the patient: ");
                                                                                scanf("%d",&p.age);
                                                                                printf("\nEnter the address of the patient:\n");
                                                                                printf("\n\tEnter the house number: ");
                                                                                scanf("%d",&p.a.hno);
                                                                                fflush(stdin);
                                                                                printf("\n\tEnter the street/colony: ");
                                                                                scanf(" %[^\n]",p.a.street);
                                                                                fflush(stdin);
                                                                                printf("\n\tEnter the city: ");
                                                                                scanf(" %[^\n]",p.a.city);
                                                                                fflush(stdin);
                                                                                printf("\n\tEnter the state: ");
                                                                                scanf(" %[^\n]",p.a.state);
                                                                                fflush(stdin);
                                                                                printf("\nEnter the phone number of the patient: ");
                                                                                scanf(" %[^\n]",p.ph);
                                                                                fflush(stdin);
								                printf("\nEnter the Disease or problem for which he/she wants treatment: ");
                                                                                scanf(" %[^\n]",p.disease);
                                                                                fflush(stdin);
                                        		                        printf("\nEnter the name of the Doctor to which he/she being referred: ");
                                                                                scanf(" %[^\n]",p.doc_name);
                                                                                fflush(stdin);
										printf("\nEnter the history, if any, related to treatment of the patient(otherwise write NOT AVAILABLE): ");
                                                                                scanf(" %[^\n]",p.history);
                                                                                fflush(stdin);
                                                                                printf("Enter the date: ");
                                                                                scanf(" %[^\n]",p.date);
                                                                                fflush(stdin);
                                                                                printf("Enter the treatment given: ");
                                                                                scanf(" %[^\n]",p.treatment);
                       								                            fflush(stdin);
                                                                                printf("Enter the medicines prescribed: ");
                                                                                scanf(" %[^\n]",p.med);
										                                        fflush(stdin);
                                                                                printf("\nEnter the RBC count of the patient:");
                                                                                scanf("%f",&p.m.RBCcount);
                                                                                printf("\nEnter the blood pressure of the patient:");
                                                                                scanf("%f",&p.m.bloodpressure);
                                                                                printf("\nEnter the blood sugar level of the patient:");
                                                                                scanf("%f",&p.m.bloodsugar);

                                                                                fwrite(&p,recsize,1,fp);
                                                                                printf("\n----------------------------------------------------");
                                                                                printf("\nWant to add entry of the another Patient(Y/N): ");
                                                                                fflush(stdin);
                                                                                another=getchar();
                                                                }
                                                }
                                                                break;

/* MODIFICATION OF EXISTING RECORDS */

                                                case '2':

                                                                another='Y';
                                                                while(another=='Y'||another=='y')
                                                                {
										printf("\nEnter the Registration number of the patient to modify: ");
                                                                                scanf(" %s",reg);
                                                                                rewind(fp);
                                                                                while(fread(&p,recsize,1,fp)==1)
                                                                                {
                                                                                                if(strcmp(p.regn,reg)==0)
                                                                                                {

														printf("\nEnter the new name of the patient: ");
                                                                                                                scanf(" %[^\n]",p.name);
                                                                                                                fflush(stdin);
														printf("\nEnter the new name of the Guardian: ");
                                                                                                                scanf(" %[^\n]",p.fname);
                                                                                                                fflush(stdin);
														printf("\nEnter the new Blood group of the patient: ");
                                                                                                                scanf(" %[^\n]",p.bg);
                                                                                                                fflush(stdin);
														printf("\nEnter the new age of the patient: ");
                                                                                                                scanf("%d",&p.age);
														printf("\nEnter the new address of the patient:\n");
                                                                                                                printf("\n\tEnter the house number: ");
                                                                                                                scanf("%d",&p.a.hno);
                                                                                                                fflush(stdin);
                                                                                                                printf("\n\tEnter the street/colony: ");
                                                                                                                scanf(" %[^\n]",p.a.street);
                                                                                                                fflush(stdin);
                                                                                                                printf("\n\tEnter the city: ");
                                                                                                                scanf(" %[^\n]",p.a.city);
                                                                                                                fflush(stdin);
                                                                                                                printf("\n\tEnter the state: ");
                                                                                                                scanf(" %[^\n]",p.a.state);
                                                                                                                fflush(stdin);
														printf("\nEnter the new phone number of the patient: ");
                                                                                                                scanf(" %[^\n]",p.ph);
                                                                                                                fflush(stdin);
														printf("enter the date of treatment given: ");
                                                                                                                scanf(" %[^\n]",p.date);
                                                                                                                fflush(stdin);
                                                                                                                printf("Enter the disease: ");
                                                                                                                scanf(" %[^\n]",p.disease);
                                                                                                                fflush(stdin);
														printf("\nEnter the detail of treatment given: ");
                                                                                                                scanf(" %[^\n]",p.treatment);
                                                                                                                fflush(stdin);
                                                                                                                printf("\nEnter the medicines prescribed: ");
                                                                                                                scanf(" %[^\n]",p.med);
                                                                                                                fflush(stdin);

                                                                                                                fseek(fp,-recsize,SEEK_CUR);
                                                                                                                fwrite(&p,recsize,1,fp);
                                                                                                                break;
                                                                                                }
                                                                                }
                                                                                 printf("\n----------------------------------------------------");
                                                                                 printf("\nModify another Record(Y/N): ");
                                                                                 fflush(stdin);
                                                                                 another=getchar();
                                                                }
                                                                break;

/*SEARCHING A PARTICULAR ENTRY (BY NAME) */

                                                case '3':

                                                                another='Y';
                                                                while(another=='Y'||another=='y')
                                                                {
                                                                                printf("\nEnter name to search: ");
                                                                                gets(pname);
                                                                                rewind(fp);
                                                                                while(fread(&p,recsize,1,fp)==1)
                                                                                {
                                                                                                if(strcmp(p.name,pname)==0)
                                                                                                {
														printf("\nRegistration Number of the Patient : ");
                                                                                                                puts( p.regn);
                                                                                                                printf("\nName of the Patient : ");
                                                                                                                puts( p.name);
                                                                                                                printf("\nName of the Guardian : ");
                                                                                                                puts( p.fname);
                                                                                                                printf("\nAge : %d",p.age);
                                                                                                                /*printf("\nGender : %s",p.gender);*/
                                                                                                                printf("\nBlood group: %s",p.bg);
														printf("\nAddress  : %d,%s,%s,%s",p.a.hno,p.a.street,p.a.city,p.a.state);
                                                                                                                printf("\nphone number : +91-%s",p.ph);
                                                                                                                printf("\nDisease : %s",p.disease);
                                                                                                                printf("\nEarlier History : ");
                                                                                                                puts( p.history);
														printf("\nDetails of treatment given and medicine prescribed:");
										printf("\nDATE\t\t TREATMENT GIVEN\t\t\tMEDICINE PRESCRIBED\n");
                                                                                printf("%s\t %-39s%s\n",p.date,p.treatment,p.med);
                                                                                fflush(stdout);
                                                                                printf("\nName of the Doctor : ");
                                                                                puts(p.doc_name);

                                                                                printf("\n----------------------------------------------------\n");
                                                                 printf("\nSearch another Entry(Y/N): ");
                                                                 fflush(stdin);
                                                                 another=getchar();
                                                                }
                                                                                }
                                                                }
                                                                break;

/* LISTING OF ALL RECORDS */

                                                case '4':

                                                                rewind(fp);
                                                                while(fread(&p,recsize,1,fp)==1)
                                                                {
                                                                                printf("\nRegistration Number of the Patient : ");
                                                                                puts( p.regn);
                                                                                printf("\nName of the Patient : ");
                                                                                puts( p.name);
                                                                                printf("\nName of the Guardian : ");
                                                                                puts( p.fname);
                                                                                printf("\nAge : %d",p.age);
                                                                                /*printf("\nGender : %s",p.gender);*/
                                                                                printf("\nBlood group: %s",p.bg);
										printf("\nAddress  : %d,%s,%s,%s",p.a.hno,p.a.street,p.a.city,p.a.state);
                                                                                fflush(stdout);
                                                                                printf("\nphone number : +91-%s",p.ph);
                                                                                fflush(stdout);
                                                                                printf("\nDisease : %s",p.disease);
                                                                                printf("\nEarlier History : ");
                                                                                puts( p.history);
										printf("\nDetails of treatment given and medicine prescribed:");
										printf("\nDATE\t\t TREATMENT GIVEN\t\t\tMEDICINE PRESCRIBED\n");
                                                                                printf("%s\t %-39s%s\n",p.date,p.treatment,p.med);
                                                                                fflush(stdout);
                                                                                printf("\nName of the Doctor : ");
                                                                                puts(p.doc_name);
                                                                                printf("\nRBC count:");
                                                                                printf("%.2f million mcL",p.m.RBCcount);
                                                                                printf("\nBlood pressure:%.2f mmHg",p.m.bloodpressure);
                                                                                printf("\nBlood sugar level:%.2f mg/dL",p.m.bloodsugar);

                                                                                printf("\n----------------------------------------------------\n");

                                                                }
                                                                //getch();
                                                                break;

/* DELETION OF RECORD */

                                case '5':

                                another='Y';
                                while(another=='Y'||another=='y')
                                {
										printf("\nEnter the Registration number of the Patient to be deleted: ");
                                                                                scanf("%s",reg);
                                                                                ft=fopen("temp.DAT","wb+");
                                                                                rewind(fp);
                                                                                while(fread(&p,recsize,1,fp)==1)
                                                                                {
                                                                                                if(strcmp(p.regn,reg)!=0)
                                                                                                	fwrite(&p,recsize,1,ft);
                                                                                                else
													printf("\nThe Record has been Deleted Successfully.");
                                                                                }

                                                                                fclose(fp);
                                                                                fclose(ft);
                                                                                remove("pat.DAT");
                                                                                rename("temp.DAT","pat.DAT");
                                                                                fp=fopen("pat.DAT","rb+");

                                                                                printf("\nDelete another record?(Y/N): ");
                                                                                fflush(stdin);
                                                                                another=getchar();
                                                                }
                                                 break;

                case '6':
                                {
                                fclose(fp);

                                main();
                                }
                                break;
                  }
                }
}


//Function to assist with the blood bank department
void blood_bank()
{
    int ch;
    char choice;

    do
    {

        printf("\n\n**Menu**\n");
        printf("1.Add Blood group\n");
        printf("2.Display units\n");
        printf("3.Update units\n");
        printf("4.Donor Search\n");
        printf("\nEnter choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:{add_bloodgroup();
                    break;
                    }
            case 2:{display_units();
                    break;
                    };
            case 3:{
                     update_units();
                     break;
                   }
            case 4:{
                     donor_search();
                     break;
                    }
            default:{
                     printf("**Enter valid choice**\n");
                    }
        };
        printf("Press 'n' to leave the blood bank system and any other character to continue:");
        scanf("%s",&choice);
    }while(choice!='n');

}

//Function to add a new blood group to the existing data base along with the available units of blood
void add_bloodgroup()
{
    FILE *fp;
    struct bloodbank b;
    int i,N;
    char ch;

    fp=fopen("bloodbank.dat","ab");
    printf("Enter the number of records:");
    scanf("%d",&N);
    for(i=0;i<N;i++)
    {
        printf("\nEnter group:");
        ch=getchar();
        gets(b.group);
        printf("Enter units:");
        scanf("%d",&b.units);
        fwrite(&b,sizeof(b),1,fp);
    }


    fclose(fp);

}


//Function to update the units of blood in blood bank storage
void update_units()
{

    FILE *fp,*f;
    struct bloodbank b,temp;
    char group[10];
    int i,found=0,pos,incr,decr,ch;

    fp=fopen("bloodbank.dat","rb");


    printf("Enter the name of the blood group to be updated:");
    ch=getchar();
    gets(group);

    while(fread(&b,sizeof(b),1,fp))
    {
        if(found!=0)
            break;
        pos=ftell(fp);
        pos=pos-sizeof(b);



        if(strcmp(b.group,group)==0)
        {
            //increment or decrement the units by accepting user choice
            printf("Do you want to increase(1) or decrease(2) the no. of units?:");
            scanf("%d",&ch);
            switch(ch)
            {
                case 1: { printf("\nHow many units are to be added?:");
                            scanf("%d",&incr);
                            strcpy(temp.group,b.group);
                            temp.units=b.units+incr;
                            break;
                          }
                case 2: { printf("\nHow many units are to be subtracted?:");
                            scanf("%d",&decr);
                            strcpy(temp.group,b.group);
                            temp.units=b.units-decr;
                            break;
                         }
            }

            fclose(fp);

            f=fopen("bloodbank.dat","rb+");
            //update the record by overwriting previous file content
            fseek(f,pos,0);
            fwrite(&temp,sizeof(temp),1,f);
            fclose(f);
            printf("\n Record Updated\n");
            found = 1;
            break;
        }

    }

    if (found == 0)
        printf("\n Record Not Found\n ");


}

//Function to search for a potential donor from the patient records and displaying their details.
void donor_search()
{

    FILE *fp;
    char group[10],ch;
    struct patient p;
    struct bloodbank b;
    int found=0;


    fp=fopen("pat.DAT","rb");

    printf("Enter the blood group to search for:");
    ch=getchar();
    gets(group);

    printf("Name\t\tPhone number\n");
    while(fread(&p,sizeof(p),1,fp))
    {

        if(strcmp(group,p.bg)==0)
        {

            if(p.age>=18)
            {

                if(p.m.RBCcount>=4.2 && p.m.RBCcount<=6.1)//checking for normal RBC count so that blood donation can be done
                    {
                        printf("%-16s%s\n",p.name,p.ph);
                        found=1;
                    }

            }
        }
    }
    fclose(fp);


    if(found==0)
    {
        printf("No donors found\n");
    }

}


void display_units()
{
    FILE *fp;
    int i;
    struct bloodbank b;

    printf("\nNow the blood bank file contains the following records:\n");

    fp=fopen("bloodbank.dat","rb");
    printf("Blood group\tNo.of Units\n");

    //display the records
    while( fread(&b,sizeof(b),1,fp))
    {

        printf("%-6s\t\t%5d\n",b.group,b.units);
    }

    fclose(fp);
}

//The ward function assists with the ward functions
void ward()
{
    int ch;
    char choice;

    type();
    do
    {

        printf("\n\t****Menu****\n");
        printf("1.Check in\n");
        printf("2.Check out\n");
        printf("3.Display ward details\n");

        printf("\nEnter choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:{check_in();
                    break;
                    }

            case 2:{
                     check_out();
                     break;
                   }
            case 3:{

                     display_ward();
                     break;

                    }
        };
        printf("Press 'n' to leave the Ward system and any other character to continue:");
        scanf("%s",&choice);
    }while(choice!='n');

    }

//Function to allot the type of room(AC/Non AC) to the available room

void type()
{
    FILE *fp;
    struct ward w;
    int i,N;
    char ch;

    fp=fopen("ward.dat","wb");

    for(i=0;i<20;i++)
    {

        w.status='v';
        fwrite(&w,sizeof(w),1,fp);
    }

    fclose(fp);

}

void check_in()
{
    FILE *fp,*f;
    struct ward w,temp;
    int i=0;
    char ch,type[10],pos,found=0;

    fp=fopen("ward.dat","rb");
    printf("Enter the type of room(AC/Non AC):");
    ch=getchar();
    scanf(" %[^\n]",type);
    while(i<20)
    {
        fread(&w,sizeof(w),1,fp);

        pos=ftell(fp);
        pos=pos-sizeof(w);
        if(w.status=='v')
        {
            found=1;
            strcpy(temp.type,type);
            temp.status='o';
            printf("\nEnter details:\n");
            printf("Enter Patient name:");
            //ch=getchar();
            scanf("%s",temp.p_name);

            printf("Enter Doctor's Name:");
            ch=getchar();
            gets(temp.d_name);
            printf("Enter Attender's Name:");
            scanf("%s",temp.a_name);
            printf("Enter Check in date:\n");
            printf(" Enter day:");
            scanf("%d",&temp.in.dd);
            printf(" Enter month:");
            scanf("%d",&temp.in.mm);
            printf(" Enter year:");
            scanf("%d",&temp.in.yy);
            if(strcmp(type,"AC")==0)
                temp.fee=1500;
            else
            {
                temp.fee=1000;
            }

            temp.out.dd=0;
            break;
        }
        
        

        i++;
    }
    if(found==0)
    {
            printf("NO ROOMS AVAILABLE!\n");
    }
    fclose(fp);

            f=fopen("ward.dat","rb+");
            fseek(f,pos,0);
            fwrite(&temp,sizeof(temp),1,f);
            fclose(f);

}

//function to aid the check-out process of patient
void check_out()
{
    FILE *fp,*f;
    struct ward w,temp;
    int i=0,*start,*end,s,temp_date;
    char ch,name[20],pos,found=0;

    fp=fopen("ward.dat","rb");
    printf("Enter the name of patient:");
    ch=getchar();
    gets(name);
    while(i<20)
    {
        fread(&w,sizeof(w),1,fp);

        pos=ftell(fp);
        pos=pos-sizeof(w);
        if(strcmp(w.p_name,name)==0)
        {
            found=1;
            printf("Enter the check-out date:\n");
            printf(" Enter day:");
            scanf("%d",&temp.out.dd);
            printf(" Enter month:");
            scanf("%d",&temp.out.mm);
            printf(" Enter year:");
            scanf("%d",&temp.out.yy);
            temp.in.dd=w.in.dd;
            temp.in.mm=w.in.mm;
            temp.in.yy=w.in.yy;
            strcpy(temp.p_name,w.p_name);
            strcpy(temp.a_name,w.a_name);
            strcpy(temp.d_name,w.d_name);
            strcpy(temp.type,w.type);
            temp.status=w.status;
            temp.fee=w.fee;
            temp_date=temp.in.yy;//since the function changes the value of date(call by reference)
            start=days_calculate(&temp.in.mm,&temp.in.dd,&temp_date);
            s=*start;
            temp_date=temp.out.yy;
            end=days_calculate(&temp.out.mm,&temp.out.dd,&temp_date);
            temp.days=(*end)-s+1;
            break;
        }
        
        
        i++;
    }

    if(found==0)
    {
           printf("Record not found\n");
    }
    fclose(fp);

            f=fopen("ward.dat","rb+");
            fseek(f,pos,0);
            fwrite(&temp,sizeof(temp),1,f);
            fclose(f);

}




//pharmacy
typedef struct
{
	char name[20];
	char ardate[10];
	char expdate[10];
	int price;
	int quantity;
}med;


void display(int pos); //display record of one medicine

void read (int m); //input new stock

void out (int m); //display complete stock

int search(); //search for a particular stock

void change(int pos); //change quantity

void pharmacy()
{

	printf("\n\tPHARMACY\n\n");

	int n,i,m,j,ch;

	do
	{

		printf("\nMENU:\n1.Add new Arrival\n2.Display stock\n3.Search \n4.Update stock\n5.exit\nEnter choice:");scanf("%d",&ch);

		if(ch==1)
		{
			printf("Enter the number of medicines to be appended:");
			scanf("%d",&m);
			read(m);
		}

		else if (ch==2)
		{
			out(m);

		}

		else if(ch==3)
		{
			int p;
			p=search();
			if (p==-1)
				continue;
			else
				display(p);
		}
		else if(ch==4)
		{
			int p=search();
			if (p==-1)
				continue;
			else
				change(p);
		}
		else if(ch==5)
			break;

	}while(ch!=5);

}

//Display the details stored in single record
void display(int pos)
{
	FILE *fp;
	med p;
	fp=fopen("pharm.dat","r");
	if (fp==NULL)
	{
		printf("Error in opening file \n");
		exit(0);
	}
	fseek(fp,pos,SEEK_SET);
	fread(&p,sizeof(med),1,fp);
	printf("\nName:%s\nArrival Date:%s\nExpiry Date:%s\nPrice:%d\nQuantity:%d\n",p.name,p.ardate,p.expdate,p.price,p.quantity);
	fclose(fp);

}

//Search the record

int search()
{
	FILE *fp;
	med t;
	char string[20];
	printf("Enter the name of the medicine:");
	scanf("%s",string);

	fp=fopen("pharm.dat","r+");
	if (fp==NULL)
	{
		printf("Error in opening file\n");
		exit(0);
	}

	int size=sizeof(med),flag=-1;
	while(fread(&t,size,1,fp)==1)
	{

		if (strcmp(t.name,string)==0)
		{
			fseek(fp,-size,SEEK_CUR);
			flag++;

			break;
		}

	}

	if (flag==-1)
	{
		printf ("Record not found\n");
		fclose(fp);
		return -1;
	}
	else
	{
		int l=ftell(fp);
		fclose(fp);
		return l;
	}
}

void change(int pos)
{
	FILE *fp;
	int ot,extra;
	med t;
	fp=fopen("pharm.dat","r+");
	if (fp==NULL)
	{
		printf("Error in opening file\n");
		exit(0);
	}
	int size=sizeof(med);
	fseek(fp,pos,SEEK_SET);
	display(pos);
	fread(&t,size,1,fp);
	printf("\nEnter the change in stock quantity:");
	scanf("%d",&extra);
	t.quantity+=extra;
	fseek(fp,-size,SEEK_CUR);
	fwrite(&t,size,1,fp);
	fclose(fp);
}



void read (int m)
{
	FILE *fp;
	med t;
	fp=fopen("pharm.dat","a");
	if (fp==NULL)
	{
		printf("Error in opening file\n");
		exit(0);
	}
	int j;
	for (j=0;j<m;j++)
	{

		printf("\nEnter the name of the medicine:");
		scanf("%s",t.name);

		printf("Enter the Arrival date:");
		scanf("%s",t.ardate);

		printf("Enter the Expiry date:");
		scanf("%s",t.expdate);

		printf("Enter the Price:");
		scanf("%d",&t.price);


		printf("Enter the quantity:");
		scanf("%d",&t.quantity);

		fwrite(&t,sizeof(med),1,fp);

	}
	fclose(fp);

}


void out(int m)
{
	FILE *fp;
	med p;
	fp=fopen("pharm.dat","r");
	if (fp==NULL)
	{
		printf("Error in opening file\n");
		exit(0);
	}
	int i,j;

	printf("Name\t\tArrival Date   Expiry Date   Price   Quantity\n");


	fread(&p,sizeof(med),1,fp);
	while(!feof(fp))
	{
		printf("%-9s",p.name);
		printf("%16s",p.ardate);
		printf("%15s",p.expdate);
		printf("%9d",p.price);
		printf("%9d",p.quantity);
		printf("\n");
		fread(&p,sizeof(med),1,fp);
	}

}





/*function to calculate the number of days in between the date passed as parameter and the base date, January 1,1900*/
long int* days_calculate(int *mm,int *dd, int *yy)
{

    long int ncycles;
    long int nyears;

    *yy-=1900;
    ndays=(long)(30.42 * ((*mm)-1)+(*dd));

    if(*mm==2)
      ++(ndays);
    if((*mm>2) && (*mm<8))
      --(ndays);
    if((*yy%4==0) && (*mm>2))
      ++ndays;

    ncycles=*yy/4;
    ndays+=(ncycles)*1461;
    nyears=(*yy)%4;
    if(nyears>0)
      ndays+=365 * (nyears)+1;
    if(ndays>59)
      --(ndays);

    return &ndays;

}

void display_ward()
{
    FILE *fp,*f;
    int i,pos;
    struct ward w,temp;



    fp=fopen("ward.dat","rb");

    printf("\n**DETAILS OF WARD**\n");


    printf("Patient Name   Doctor Name   Attender Name   Room type   Check-in date   Check-out date   No.Of Days    Fee per day\n");

    //display the records
    while( fread(&w,sizeof(w),1,fp))
    {

        pos=ftell(fp);
        pos=pos-sizeof(w);
        if(w.status=='o')
        {

            printf("%-15s%-14s%-16s%-12s",w.p_name,w.d_name,w.a_name,w.type);
            printf("%02d/%02d/%d",w.in.dd,w.in.mm,w.in.yy);
            printf("%8s%02d/%02d/%d"," ",w.out.dd,w.out.mm,w.out.yy);
            printf("%8s%2d%5s    Rs.%.2f\n"," ",w.days," ",w.fee);
            temp.status='v';
        }

    }

    fclose(fp);
    f=fopen("ward.dat","rb+");
    fseek(f,pos,0);
    fwrite(&temp,sizeof(temp),1,f);
    fclose(f);


}
void billing()
{
	int ch;
	p:
	printf("\nMenu\n1.Inpatient\n2.Outpatient\n3.Exit\nEnter choice:");
	scanf("%d",&ch);
	switch (ch)
	{
		case 1:
		{
			inpatient();
			goto p;
		}
		case 2:
		{
			outpatient();
			goto p;
		}
		case 3:
		{
			printf("Thank you");
			break;
		}
		default:
		{
			printf("Enter valid choice");
			goto p;
		}
	}
}

void inpatient()
{
	FILE *w,*p;
	char name[20];
	int a,fee,l;
	struct ward s;
	med t;

	w=fopen("ward.dat","rb");
	p=fopen("pharm.dat","rb");
	printf("Enter name of the patient:");
	scanf("%s",name);
	printf("Doctor fee:\n");
	printf("Doctor Requirement:\n1.Specialist\n2.General\nEnter choice: ");
	scanf("%d",&a);
	if(a==1)
		fee=1200;
	else if(a==2)
		fee=700;
	int size=sizeof(s),flag=-1;
	while(fread(&s,size,1,w)==1)
	{

		if (strcmp(s.p_name,name)==0)
		{
			fseek(w,-size,SEEK_CUR);
			flag++;

			break;
		}

	}

	if (flag==-1)
	{
		printf ("Record not found\n");
		fclose(w);
	}
	else
	{

		l=ftell(w);
		fclose(w);
	}
	fseek(w,l,SEEK_SET);
	fread(&s,sizeof(s),1,w);
	printf("Doctor name:%s\nDoctor fees:Rs.%d\n",s.d_name,fee);


    int days,dc;
	days=s.days;
	dc=days*s.fee; //room charge
	fclose(w);

	//mess charge
	int mc;
	mc=days*250;
	int i=5,qty,total=0;

    //scans
	printf("Scan Charges:\n");
	char k;
	printf("Were any scans taken (y/n): ");
	scanf(" %c",&k);
	int sc=0;
	if(k=='y')
	{
		int q;
		printf("Number of scans:");
		scanf(" %d",&q);
		sc=q*1500;
	}
	else if(k=='n')
		printf("No scans were taken.\n");


    //surgery
	printf("Surgery Charges:\n");
	char g;
	printf("Were any surgeries performed (y/n): ");
	scanf(" %c",&g);
	int oc=0;
	if(g=='y')
	{
		int u;
		printf("Number of surgeries:");
		scanf(" %d",&u);
		oc=u*15000;
	}
	else if(g=='n')
		printf("No surgeries were performed.\n");



	//int i=5,qty,total=0;
	char mname[10],c;

	printf("Pharmacy bill:\n");
	read:
	printf("Enter Medicine name:");
	scanf("%s", mname);
	printf("Quantity required:");
	scanf("%d",&qty);

	int sze=sizeof(med);
	while(fread(&t,sze,1,p)==1)
	{
		if (strcmp(t.name,mname)==0)
		{
			fseek(p,-sze,SEEK_CUR);
			break;
		}

	}
	l=ftell(p);
	fclose(p);
	fseek(p,l,SEEK_SET);
	fread(&t,sizeof(med),1,p);
	total=total+((t.price)*qty);
	printf("Pharmacy fee:Rs.%d\n",total);
	printf("Enter n to add medicine/any other character to continue:");
	scanf(" %c",&c);
	if(c=='n')
	goto read;
	/*
	printf("\n---------------------\n");
	total=total+fee;
	printf("Total bill:Rs.%d\n\n",total);*/
    printf("\n\n---------------------\n\n");
	printf("Charges		Bill\n");
	printf("Doctor's Fee	%d\n",fee);
	printf("Pharmacy Bill	%d\n",total);
	printf("Room Charges	%d\n",dc);
	printf("Mess Charges	%d\n",mc);
	printf("Scan Charges	%d\n",sc);
	printf("Surgery Charges %d\n",oc);
	printf("---------------------\n");

	int sum=fee+total+sc+dc+mc+oc;
	printf("Total\t	 Rs.%d\n\n",sum);


}


void outpatient()
{
	FILE *w,*p;
	char name[20];
	int a,fee,l,total=0;
	//struct ward s;
	med t;

	//w=fopen("ward.dat","r");
	p=fopen("pharm.dat","r");
	printf("Enter name of the patient:");
	scanf("%s",name);
	printf("Doctor's fee\n");
	printf("Doctor Requirement:\n1.Specialist\n2.General\nEnter choice: ");
	scanf("%d",&a);
	//doctor fee
	if(a==1)
		fee=1200;
	else if(a==2)
		fee=700;
	//int size=sizeof(s),flag=-1;
	/*while(fread(&s,size,1,w)==1)
	{

		if (strcmp(s.p_name,name)==0)
		{
			fseek(w,-size,SEEK_CUR);
			flag++;

			break;
		}

	}

	if (flag==-1)
	{
		printf ("Record not found\n");
		fclose(w);
	}
	else
	{

		l=ftell(w);
		fclose(w);
	}
	fseek(w,l,SEEK_SET);
	fread(&s,sizeof(s),1,w);*/
	printf("Doctor fees:Rs.%d\n",fee);
	/*int days,dc;
	days=s.days;
	dc=days*s.fee; //room charge
	fclose(w);

	//mess charge
	int mc;
	mc=days*250;
	int i=5,qty,total=0;*/

	//scans
	printf("Scan Charges:\n");
	char k;
	printf("Were any scans taken (y/n): ");
	scanf(" %c",&k);
	int sc=0;
	if(k=='y')
	{
		int q;
		printf("Number of scans:");
		scanf(" %d",&q);
		sc=q*1500;
	}
	else if(k=='n')
		printf("No scans were taken.\n");

/*
	//surgery
	printf("Surgery Charges:\n");
	char g;
	printf("Were any surgeries performed (y/n): ");
	scanf(" %c",&g);
	int oc=0;
	if(g=='y')
	{
		int u;
		printf("Number of surgeries:");
		scanf(" %d",&u);
		oc=u*15000;
	}
	else if(g=='n')
		printf("No surgeries were performed.\n");*/


	//pharmacy bill
	printf("Pharmacy Bill:\n");
	char mname[10],c;
    int qty;
	read:
	printf("Enter Medicine name:");
	scanf("%s",mname);
	printf("Quantity required:");
	scanf("%d",&qty);

	int sze=sizeof(med);
	while(fread(&t,sze,1,p)==1)
	{
		if (strcmp(t.name,mname)==0)
		{
			fseek(p,-sze,SEEK_CUR);
			break;
		}

	}
	l=ftell(p);
	fclose(p);
	fseek(p,l,SEEK_SET);
	fread(&t,sizeof(med),1,p);
	total=total+((t.price)*qty);
	printf("Pharmacy fee:Rs.%d\n",total);
	printf("Enter n to add medicine/any other character to continue:");
	scanf(" %c",&c);
	if(c=='n')
	goto read;



	printf("\n\n---------------------\n\n");
	printf("Charges		Bill\n");
	printf("Doctor's Fee	%d\n",fee);
	printf("Pharmacy Bill	%d\n",total);
	//printf("Room Charges	%d\n",dc);
	//printf("Mess Charges	%d\n",mc);
	printf("Scan Charges	%d\n",sc);
	//printf("Surgery Charges %d\n",oc);
	printf("---------------------\n");

	int sum=fee+total+sc;
	printf("Total	%d\n\n",sum);


}

void house()
{
    if (array_new(&diagnosis) != CC_OK) 
    {
        // something went wrong
        printf("ERROR at creating array");
        exit(-1);
    }
    load();// modifies file to symptoms to disease dictionary;
    char** symptoms = getAllSymptoms();//displays all possible symptoms
    int i = 0;
    
    while(symptoms[i] != NULL) {
        printf("%-40s",symptoms[i]);
        if(i%4==0)
            printf("\n");
        i++;
    }
    
    printf("\nenter your symptoms,x to exit\n" );
    getusersyms();//inputs symptoms from user and updates diagnosis
    sortdiseases();
    printf("done with sorting\n");
    for( i=0; i<array_size(diagnosis); i++)
    {
        struct diagnosisElement* d;
        array_get_at(diagnosis, i , (void*) &d);
        printf("Disease: %s importance level: %d\n", d->disease, d->score);
    }
}

void load()
{
    if (hashtable_new(&symptom) != CC_OK) {
        // something went wrong
        printf("error");
        exit(-1);
    }
    FILE *fp;
    fp=fopen("kk.txt","r");
    //TBD to check for error
    char line[100];
    char *sym, *dis;
    fscanf(fp,"%[^\n]", line);
    fgetc(fp);
    while (!feof(fp))
    {
        char* lineN = malloc(strlen(line));
        strcpy(lineN,line);
        char* token = strtok(lineN, ","); 
        dis = token;
        token = strtok(NULL,",");
        sym = token;
        //printf("Disease: %s, Symptom: %s\n", dis, sym);
        if (hashtable_contains_key(symptom, sym) == 0)//it doesnt already exist
        {
            Array *ar;
            if (array_new(&ar) != CC_OK) 
            {
                // something went wrong
                printf("ERROR at creating array");
                exit(-1);
            }
            enum cc_stat status = array_add(ar, dis);
            if (status != CC_OK) 
            {
                printf("ERROR at adding array\n");
                exit(-1);
            }   
            hashtable_add(symptom, sym, ar);
        }
        else
        {
            Array *ar;
            enum cc_stat status = hashtable_get( symptom, sym , (void*) &ar);
            if (status != CC_OK) 
            {
                printf("ERROR at getting array\n");
                exit(-1);
            }   
            // add to array
            status = array_add(ar, dis);
            if (status != CC_OK) 
            {
                printf("ERROR at adding array\n");
                exit(-1);
            }   
        }
        fscanf(fp,"%[^\n]", line);
        fgetc(fp);
    }
    fclose(fp);
}



char** getAllSymptoms() {
    Array *ar;
    hashtable_get_keys(symptom,(void*) &ar);
    char** symptoms = malloc((array_size(ar)+1)*sizeof(char *));
    int i=0;
    for(i=0;i<array_size(ar);i++) {
        char *foo;
        array_get_at(ar, i, (void*) &foo);
        symptoms[i]=foo;
    }
    symptoms[array_size(ar)]=NULL;
    return symptoms;
}

void maintain_score(char* disease_pass)
{   
    for(int i = 0; i < array_size(diagnosis); i++)
    {
        struct diagnosisElement* d;
        array_get_at(diagnosis, i , (void*) &d);
        if( strcmp(d->disease, disease_pass) == 0)
        {
            d->score++;
            return;
        }
    }
    struct diagnosisElement* d = malloc(sizeof(struct diagnosisElement));
    d->disease = disease_pass;
    d->score = 1;
    array_add(diagnosis , d);
}

void getusersyms()
{

    Array *Sym;
    if (array_new(&Sym) != CC_OK) 
    {
        // something went wrong
        printf("ERROR at creating array");
        exit(-1);
    }
    char symp[100];
    scanf("%[^\n]", symp);
    while ((getchar()) != '\n'); 
    while (strcmp(symp,"x") !=0)
    {
        char* t = malloc(strlen(symp));
        strcpy(t, symp);
        enum cc_stat status = array_add(Sym, t);
        if (status != CC_OK) 
        {
            printf("ERROR at adding array\n");
            exit(-1);
        }
        scanf("%[^\n]", symp);
        while ((getchar()) != '\n'); 
    }
    Array *Syms;
    hashtable_get_keys(symptom,(void*) &Syms);  
    for (int size = 0 ; size < array_size(Sym) ; size ++ )
    {
        char* sym1;
        array_get_at(Sym, size , (void*) &sym1);
        for(int SIZE = 0; SIZE < array_size(Syms); SIZE ++ )
        {
            char* sym2;
            array_get_at(Syms, SIZE , (void*) &sym2);
            if( strcmp ( sym1,sym2 ) == 0)
            {
                Array *Dis;
                hashtable_get(symptom, sym1, (void*) &Dis);
                for(int pass = 0; pass < array_size(Dis); pass++)
                {
                    char* disease_pass;
                    array_get_at(Dis, pass , (void*) &disease_pass);
                    maintain_score( disease_pass );
                    //TBD break the loop
                }
            }
        }
    }
}

void sortdiseases()
{
    for(int i=0; i < array_size(diagnosis); i++)
    {
        for( int j= i+1; j < array_size(diagnosis); j++)
        {
            struct diagnosisElement* d1;
            struct diagnosisElement* d2;
            array_get_at(diagnosis, i , (void*) &d1);
            array_get_at(diagnosis, j , (void*) &d2);
            if ( d1->score < d2->score)
            {
                array_swap_at(diagnosis, i, j);
            }
        }
    }
}


