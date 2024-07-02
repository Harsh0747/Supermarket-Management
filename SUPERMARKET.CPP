                        //SUPERMARKET BILLING SYSTEM 


//***************************************************************
// HEADER FILES USED IN PROJECT
//****************************************************************

#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
#include<string.h>
#include<time.h>
#include<windows.h>

//*************************************************************
//TO SET CURSOR POSITION AND USE GOTOXY FUNCTION
//*************************************************************

COORD coord={0,0};

void gotoxy(int x,int y)
{
  	coord.X=x;
 	coord.Y=y;
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

using namespace std;

//***************************************************************
// CLASS USED FOR PRODUCT
//****************************************************************

class product    
{
	int pno;                        //to store product number
	char name[50];                  //to store product name
	char ptype[50];                 //to store product type
	float price, qty, tax, dis;     //to store other product details

	public:

	    void create_product()       //to create product
	    {
			cout << "\nPlease Enter The PNo. of The Product ";
			cin >> pno;
			cout << "\nPlease Enter The Name of The Product ";
			cin>>name;
			cout << "\nPlease Enter The Type of The Product ";
			cin>>ptype;
			cout << "\nPlease Enter The Price of The Product ";
			cin >> price;
			cout << "\nPlease Enter The Discount (%) ";
			cin >> dis;
	    }

		void show_product()         //to show product details
		{
	    	cout << "\nNo. of The Product : " << pno;
	    	cout << "\nThe Name of The Product : ";
	    	puts(name);
		    cout << "\nThe Type of The Product : ";
		    puts(ptype);
	    	cout << "\nThe Price of The Product : " << price;
	    	cout << "\nDiscount : " << dis;
		}

		int retpno()         //to return product number
		{
		    return pno;
		}

		float retprice()      //to return product price
		{
		    return price;
		}

		char * retname()      //to return product name		
		{    
			return name;
		}

		char * retptype()    //to return product type
		
		{
		    return ptype;
		}

		int retdis()        //to return discount 
		{
		    return dis;
		}
}; //class ends here

//***************************************************************
// STRUCTURE FOR CUSTOMER
//****************************************************************

struct customer
{
	int cmno;                         //to store customer number
	char cname[20];                   //to store customer name
	long int phno;                    //to store phone number
	float camt;   	         	  //to store amount paid
	time_t dt;                        //to store date and time of purchase

	void create_cm()             //to create customer
	{
		cout << "\nPlease Enter The Customer Number ";
		cin >> cmno;
		cout << "\nPlease Enter Customer Name ";
		cin >> cname;
		cout << "\nPlease Enter Phone Number ";
		cin >> phno;
	} 

	void display_cm()          //to display customer
	{
		cout<<"\nCustomer name: ";
		puts(cname);
		cout<<"\nCustomer number: "<<cmno;
		cout<<"\nPhone no.:"<<phno;
		cout<<"\nDate and time of purchase: "<<ctime(&dt);
		cout<<"\nAmount paid: "<<camt;
	}
};//customer stucture ends here

//*****************************************************************
// global declaration for stream object, object & password variable
//*****************************************************************

fstream fp;
fstream fc;
product pr;
customer cm;
const char password[10]="csproject";

//****************************************************************
// function to write in customer file
//****************************************************************

void write_customer()
{
    fc.open("Cust.dat", ios::out | ios::app);
    cm.create_cm();
    fc.write((char * ) & cm, sizeof(customer));
    fc.close();

    cout<<"\n\nThe Customer Has Been Created! ";
    cout<<"\n\nPress any key to return to the customer menu...";
    getch();
}

//****************************************************************
// function to read all records from customer file
//****************************************************************

void display_all_customer()
{
    system("cls");
    cout << "\n\n\n\t\tDISPLAY ALL CUSTOMERS !!!\n\n";
    fc.open("Cust.dat", ios:: in );
    while (fc.read((char * ) & cm, sizeof(customer)))
    {
		cm.display_cm();
		cout << "\n\n====================================\n";
		getch();
    }
    fc.close();

    cout<<"\n\nPress any key to go back to customer menu...";
    getch();
}

//****************************************************************
// function to read specific record from customer file
//****************************************************************

int display_sc(int n)
{
    int flag = 0;
    fc.open("Cust.dat", ios:: in | ios:: binary);
    
	while(fc.read((char * ) & cm, sizeof(customer)))
    {
		if (cm.cmno == n)
		{
	    	system("cls");
	    	cm.display_cm();
	    	flag = 1;
		}
    }
    fc.close();

    if (flag == 0)
    {
		cout << "\n\nCustomer does not exist!";
		return 0;
    }

    return 1;
}

//****************************************************************
// function to modify record from customer file
//****************************************************************

void modify_customer()
{
    int no, found = 0;
    system("cls");
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Product number";
    cin >> no;

    fc.open("Cust.dat", ios:: in | ios::out);
    while (fc.read((char * ) & cm, sizeof(customer)) && found == 0)
    {
		if (cm.cmno == no)
		{
	    	cm.display_cm();
	    	cout << "\nPlease Enter The New Details of Product" << endl;
	    	cm.create_cm();
	    	int pos = -1 * sizeof(cm);
	    	fc.seekp(pos, ios::cur);
	    	fc.write((char * ) & cm, sizeof(customer));
	    	cout << "\n\n\t Record Updated";
	    	found = 1;
		}
    }
    fc.close();

    if (found == 0)
	cout << "\n\n Record Not Found ";
    cout<<"\n\nPress any key to return to the admin menu...";
    getch();
}

//****************************************************************
// function to delete record from customer file
//****************************************************************

int delete_customer()
{
    int no,inp;
    char ch;
    system("cls");
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The cno. of The Customer You Want To Delete";
    cin >> no;
    inp=display_sc(no);

    if(inp==1)
    {
		cout<<"\nDo you really want to delete this record?(y/n)";
		cin>>ch;
		if(ch=='n'||ch=='N')
		{
	    	cout<<"\nPress any key to go to the admin menu...";
	    	getch();
	    	return 0;
		}
		fc.open("Cust.dat", ios:: in | ios::out);
		fstream fc2;
		fc2.open("Temp.dat", ios::out);
		fc.seekg(0, ios::beg);
		while (fc.read((char * ) & cm, sizeof(customer)))
		{
	    	if (cm.cmno != no)
	    	{
				fc2.write((char * ) & cm, sizeof(customer));
	    	}
		}
		fc2.close();
		fc.close();
		remove("Cust.dat");
		rename("Temp.dat", "Cust.dat");
		cout << "\n\n\tRecord Deleted ..";
    }

    cout<<"\n\nPress any key to go back to the admin menu...";
    getch();
    return 1;
}

//****************************************************************
// function to write in prodcut file
//****************************************************************

void write_product()
{
    fp.open("Shop.dat", ios::out | ios::app);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(product));
    fp.close();

    cout<<"\n\nThe Product Has Been Created! ";
    cout<<"\n\nPress any key to return to the admin menu...";
    getch();
}

//****************************************************************
// function to read all records from product file
//****************************************************************

void display_all_product()
{
    system("cls");
    cout << "\n\n\n\t\tDISPLAY ALL PRODUCTS !!!\n\n";
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
		pr.show_product();
		cout << "\n\n====================================\n";
		getch();
    }
    fp.close();

    cout<<"\n\nPress any key to go back to admin menu...";
    getch();
}

//****************************************************************
// function to read specific record from product file
//****************************************************************

int display_sp(int n)
{
    int flag = 0;
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
		if (pr.retpno() == n)
		{
	    	system("cls");
	    	pr.show_product();
	    	flag = 1;
		}
    }
    fp.close();

    if (flag == 0)
    {
		cout << "\n\nRecord does not exist!";
		return 0;
    }

    return 1;
}

//****************************************************************
// function to modify record of product file
//****************************************************************

void modify_product()
{
    int no, found = 0;
    system("cls");
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Product number";
    cin >> no;

    fp.open("Shop.dat", ios:: in | ios::out);
    while (fp.read((char * ) & pr, sizeof(product)) && found == 0)
    {
		if (pr.retpno() == no)
		{
	    	pr.show_product();
	    	cout << "\nPlease Enter The New Details of Product" << endl;
	    	pr.create_product();
	    	int pos = -1 * sizeof(pr);
	    	fp.seekp(pos, ios::cur);
	    	fp.write((char * ) & pr, sizeof(product));
	    	cout << "\n\n\t Record Updated";
	    	found = 1;
		}
    }
    fp.close();

    if (found == 0)
	cout << "\n\n Record Not Found ";
    cout<<"\n\nPress any key to return to the admin menu...";
    getch();
}

//****************************************************************
// function to delete record of product file
//****************************************************************

int delete_product()
{
    int no,inp;
    char ch;
    system("cls");
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The pno. of The Product You Want To Delete";
    cin >> no;
    inp=display_sp(no);

    if(inp==1)
    {
		cout<<"\nDo you really want to delete this record?(y/n)";
		cin>>ch;
		if(ch=='n'||ch=='N')
		{
	    	cout<<"\nPress any key to go to the admin menu...";
	    	getch();
	    	return 0;
		}
		fp.open("Shop.dat", ios:: in | ios::out);
		fstream fp2;
		fp2.open("Temp.dat", ios::out);
		fp.seekg(0, ios::beg);
		while (fp.read((char * ) & pr, sizeof(product)))
		{
	    	if (pr.retpno() != no)
	    	{
				fp2.write((char * ) & pr, sizeof(product));
	    	}
		}
		fp2.close();
		fp.close();
		remove("Shop.dat");
		rename("Temp.dat", "Shop.dat");
		cout << "\n\n\tRecord Deleted ..";
    }

    cout<<"\n\nPress any key to go back to the admin menu...";
    getch();
    return 1;
}

//***************************************************************
// function to display all products price list
//****************************************************************

int display_product_menu()
{

    system("cls");
    fp.open("Shop.dat", ios:: in );
    if (!fp)
    {
		cout << "ERROR!!! FILE COULD NOT BE OPENED\n\n\n Go To Admin Menu to create File ";
		cout << "\n\n\n Press any key to retuen to admin menu....";
		getch();
		return 0;
    }

    cout << "\n\n\t\tProduct MENU\n\n";
    cout << "====================================================\n";
    cout << "P.NO.\t\tNAME\t\tTYPE\t\tPRICE\t\tDISCOUNT\n";
    cout << "====================================================\n";

    while (fp.read((char * ) & pr, sizeof(product)))
    {
		cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retptype()<<"\t\t"<<pr.retprice()<<
		"\t\t"<<pr.retdis()<<endl;
    }
    fp.close();

    cout<<"\n\nPress any key to continue...";
    getch();
    return 1;
}

//***************************************************************
// function to place order and generating bill for Products
//***************************************************************

void place_order()
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, gst, total, gtotal = 0;
    char ch = 'Y';
    
	int c_no;
	cout<<"\n\nEnter the customer number ";
	cin>>c_no;
	fc.open("Cust.dat", ios::out | ios::app);
	cm.create_cm();
	cout << "\n\nPress any key to continue...";
	getch();
	fc.close();		

	system("cls");
	display_product_menu();
    cout << "\n============================";
	cout << "\n PLACE YOUR ORDER";
	cout << "\n============================\n";
    do
    {
		cout << "\n\nEnter The PNo. Of The Product : ";
		cin >> order_arr[c];
		cout << "\nQuantity in number : ";
		cin >> quan[c];
		c++;
		cout << "\nDo You Want To Order Another Product ? (y/n)";
		cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You For Placing The Order";
    getch();
    system("cls");

    cout << "\n\n******************************** INVOICE ***************************************\n";
    time_t curr;
    curr = time(NULL);
    cout << "\n" << (ctime(&curr));
    cout << "\nGST: 18% ";
    cout << "\nPhone no.: " << cm.phno;
    cout << "\n\n________________________________________________________________________________";
    cout << "\nPr No.\tParticulars \tQty \tPrice \tDis. \tGST \tAmount  ";
    cout << "\n_______________________________________________________________________________";

    for (int x = 0; x <= c; x++)
    {
		fp.open("Shop.dat", ios:: in );
		fp.read((char * ) & pr, sizeof(product));
		while (!fp.eof())
		{
	    	if (pr.retpno() == order_arr[x])
	    	{
				damt = pr.retprice() - (pr.retprice() * (pr.retdis()/100));
				gst = damt*0.18;
				amt = damt+gst;
				cout << "\n" << order_arr[x] << "\t" << pr.retname() <<
		    	"\t\t" << quan[x] << "\t" << pr.retprice() << "\t" <<
		    	pr.retdis() << "%\t" << gst << "\t" << amt;
				gtotal += amt;
	    	}
	    	fp.read((char * ) & pr, sizeof(product));
		}
		fp.close();
    }

    cout << "\n________________________________________________________________________________";
    cout << "\n\nAll price inclusive GST. \t\tTo Pay : " << gtotal;
    cout << "\n________________________________________________________________________________";

    cm.camt = gtotal;
    cm.dt = curr;

    fc.write((char * ) & cm, sizeof(customer));
    fc.close();
    cout<<"\n\nPress any key to go back to the main menu...";
    getch();
}

//***************************************************************
// FUNCTION TO PRINT DAILY SALE
//***************************************************************

void dailysale()
{
	int dayy, mo, ye;
    float dailytotal=0;

    system("cls");
    cout << "\nEnter the date yo want to know the sale: ";
    cout << "\nEnter day: ";
    cin >> dayy;
    cout << "\nEnter month: ";
    cin >> mo;
    cout << "\nEnter year: ";
    cin >> ye;

    fc.open("Cust.dat", ios::in | ios::binary);
    fc.read((char * ) & cm, sizeof(customer));
    while (!fc.eof())
    {
	    tm *comptm = localtime(&cm.dt);
	    if ((comptm->tm_mday) == dayy && ((comptm->tm_mon)+1) == mo && ((comptm->tm_year)+1900) == ye)
	    {
			dailytotal+=cm.camt;
	    }
	    fc.read((char * ) & cm, sizeof(customer));
    }
    fc.close();

    cout<<"\nTotal sale of the day is ";
    cout<<dailytotal;
    cout<<"\n\nPress any key to continue....";
    getch();
}

//***************************************************************
// TO KNOW THE DETAILS OF A CUSTOMER
//***************************************************************

void cm_details()
{
	int ch;
    int cust_no, flag;
	system("cls");
	cout<<"\n\n\tENTER YOUR CHOICE";
    cout<<"\n\n\t1. DELETE CUSTOMER";
    cout<<"\n\n\t2. MODIFY CUSTOMER";
    cout<<"\n\n\t3. SHOW CUSTOMER DETAILS ";
	cin>>ch;
	
	if(ch==1)
		delete_customer();
	
	else if(ch==2)
		modify_customer();
	
	else if(ch==3)
	{
		cout<<"\nEnter the customer no. whose detail you want to know: ";
    	cin>>cust_no;
		display_sc(cust_no);
    	cout<<"\n\nPress any key to return to the admin menu...";
    	getch();
	}
}

//***************************************************************
// ADMINSTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
    system("cls");
    char ch2;

    cout << "\n\n\n\tADMIN MENU";
    cout << "\n\n\t1.CREATE PRODUCT";
    cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
    cout << "\n\n\t3.DISPLAY PARTICULAR PRODUCT ";
    cout << "\n\n\t4.MODIFY PRODUCT";
    cout << "\n\n\t5.DELETE PRODUCT";
    cout << "\n\n\t6.VIEW PRODUCT MENU ";
    cout << "\n\n\t7.TOTAL SALE OF A DAY ";
    cout << "\n\n\t8.CUSTOMER DETAILS";
    cout << "\n\n\t9.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-9) ";
    cin>>ch2;

    switch (ch2)
    {
	    case '1':
			system("cls");
			write_product();
			admin_menu();
			break;
    	case '2':
			display_all_product();
			admin_menu();
			break;
    	case '3':
			int num;
			system("cls");
			cout << "\n\n\tPlease Enter The PNo. ";
			cin >> num;
			display_sp(num);
			cout<<"\n\nPress any key to go back to the admin menu...";
			getch();
			admin_menu();
			break;
    	case '4':
			modify_product();
			admin_menu();
			break;
    	case '5':
			delete_product();
			admin_menu();
			break;
    	case '6':
			display_product_menu();
			admin_menu();
			break;
    	case '7':
			dailysale();
			admin_menu();
			break;
    	case '8':
			cm_details();
			admin_menu();
			break;
    	case '9':
			break;
    	default:
			cout << "\a";
			admin_menu();
    }
}

//***************************************************************
// CUSTOMER MENU FUNCTION
//***************************************************************

void customer_menu()
{
	int ch;
	system("cls");
	cout << "\n\n\n\tCUSTOMER MENU";
	cout << "\n\n\t1. ADD NEW CUSTOMER";
	cout << "\n\n\t2. DISPLAY CUSTOMER";
	cout << "\n\n\t3. PLACE ORDER";
	cout << "\n\n\t4. EXIT";
	cout << "\n\n\tPlease Select Your Option (1-4) ";
	cin>>ch;
	switch(ch)
	{
		case 1:
			system("cls");
			write_customer();
			customer_menu();
			break;	
			
		case 2:
			system("cls");
			display_all_customer();
			customer_menu();
			break;

		case 3:
			system("cls");
			place_order();
			customer_menu();
			break;

		case 4:
			break;

		default :
			cout << "\a";
			customer_menu();
	}
}

//***************************************************************
// MAIN MENU FUNCTION
//***************************************************************

void main_menu()
{
	char ch;
	do
    {
		system("cls");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t1. CUSTOMER";
		cout << "\n\n\t2. ADMINISTRATOR";
		cout << "\n\n\t3. EXIT";
		cout << "\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		switch (ch)
		{
			case '1':
	    		system("cls");
	    		customer_menu();
		 		getch();
	    		break;
			
			case '2':
	    		system("cls");
	    		char inp[20];
				int i;
	    		cout<<"Enter password: ";
	    		for(i=0;i<9;i++)
				{
					inp[i]=getch();
        			cout<<"*";
				}
				inp[i]='\0';
	    		if((strcmp(inp,password))==0)
					admin_menu();
	    		else
	    		{
		 			cout<<"Incorrect Password";
		 			cout<<"\n\npress any key to go back to main menu";
		 			getch();
	    		}
	    		break;
			
			case '3':
	    		exit(0);
				break;
			
			default:
	    		cout << "\a";
		}
    } while (ch != '3');

    system("cls");
    cout<<"THANKYOU FOR VISITING...";
    cout<<"\nPress any key to close....";
}

//***************************************************************
// NAME DISPLAYING FUNCTION
//***************************************************************

void madeby()     
{
	system("cls");
	gotoxy(30,12);
	cout<<"Project made by:";
	gotoxy(20,13);
	cout<<"ABHIJEET TIWARI AND AMIT SAINI";
	gotoxy(45,20);
	cout<<"Press any key to continue...";
	getch();
}

//***************************************************************
// PROJECT INTRODUCTION FUNCTION
//***************************************************************

void welcome()         
{
	system("cls");
	gotoxy(20,15);
	cout<<"SUPERMARKET MANAGEMENT SYSTEM";
	gotoxy(45,20);
	cout<<"Press any key to continue...";
	getch();
	madeby();
}

//***************************************************************
// THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
    welcome();
	main_menu();
    getch();
	return 0;
}

//***************************************************************
// END OF PROJECT
//***************************************************************