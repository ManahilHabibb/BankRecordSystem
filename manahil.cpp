//----------------------------------------------------------------
//            BANK RECORD SYSTEM 
//----------------------------------------------------------------

//----------------------------------------------------------------
//            Header files
//----------------------------------------------------------------

#include<iostream> 
#include<fstream> 
#include<cctype>  
#include<iomanip>
using namespace std;

//----------------------------------------------------------------
//            FUNCTION DECLARATION 
//----------------------------------------------------------------

void password();
void banner();
void admin();
void customer();
void about_us();
void contact_us();
void manager();
void balance();
//float balance(float x);

//----------------------------------------------------------------
//            CLASSES
//----------------------------------------------------------------

class accounts
{
private:
    int account_number;
    char first_name[10];
    char last_name[10];
//    float balance;
public:
	  float balance;
    void read_account();
    void display_account();
    void write_record();
    void read_record();
    void search_record();
    void modify_record();
    void delete_record();
    void balance_record();
};

//----------------------------------------------------------------
//            READ ACCOUNT DETAILS
//----------------------------------------------------------------

void accounts::read_account()
{
	int choice;
    float amount;
    cout<<"\n\t Account Number: ";
    cin>>account_number;
    cout<<"\n\t First Name: ";
    cin>>first_name;
    cout<<"\n\t Last Name: ";
    cin>>last_name;
	do
    {
     system("cls");
        cout<<"\n\n\n\t\tAMOUNT";
        cout<<"\n\n\t\tSelect Your Option (1-3) ";
        cout<<"\n\n\t\t01. INITIAL AMOUNT";
        cout<<"\n\n\t\t02. CREDIT AMOUNT";
        cout<<"\n\n\t\t03. DEBIT AMOUNT";
        cout<<"\n\n\t\t04. EXIT"<<endl;
        cin>>choice;
        system("cls");
       switch(choice)
        {
        	case 1: // credit
           cout<<"\n\n\tINITITAL AMOUNT";
           cout<<"\n\n\t\tAmount :";
           cin>>amount;
//           cout<<"\n\n\t\tYour initial ammount : "<<balance;
            break;
        case 2: // credit
           cout<<"\n\n\t\tCREDIT AMOUNT";
           cout<<"\n\n\t\tAmount :";
            cin>>amount;
           if(balance<amount)
           {
           	cout<<"\n\n\t\tInsufficient balance ...!";
		   }
		   else
		   {
		   	balance=balance+amount;
		   }
        	cout<<"\n\n\t\tAmount after credit : "<<balance;
            break;
        case 3: // debit
         cout<<"\n\n\t\tDEBIT AMOUNT";
           cout<<"\n\n\t\tAmount :";
           cin>>amount;
           balance=balance-amount;
           cout<<"\n\n\t\tAmount after debit : "<<balance;
            break;
        case 4://exit
         admin();
            break;
        default:
            cout<<"\nEnter corret choice";
            exit(0);
        }
        cin.ignore(); //used to ignore or clear one or more characters from the input buffer
        cin.get(); //accessing character array
    }while(choice!='4');
    cout<<endl;
     cout<<"\n\n\n\t ***************************************"<<endl;
}

//----------------------------------------------------------------
//            DISPLAY ACCOUNT
//----------------------------------------------------------------

void accounts::display_account()
{
	
    cout<<"\tAccount Number: "<<account_number<<endl;
    cout<<"\tFirst Name: "<<first_name<<endl;
    cout<<"\tLast Name: "<<last_name<<endl;
    cout<<"\tBalance: Rs.  "<<balance<<endl;
     cout<<"\n\n\n\t ***************************************"<<endl;
}

//----------------------------------------------------------------
//            WRITE RECORD
//----------------------------------------------------------------

void accounts::write_record()
{
    ofstream outfile;
    outfile.open("account.dat", ios::binary|ios::app);
    read_account();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
}

//----------------------------------------------------------------
//            READ RECORDS 
//----------------------------------------------------------------

void accounts::read_record()
{
    ifstream infile;
    infile.open("account.dat", ios::binary);
    if(!infile)
    {
        cout<<"\n\tFile does not exist !!!"<<endl;
        return;
    }
    cout<<"\n\t**Reading data"<<endl;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            display_account();
        }
    }
    infile.close();
}

//----------------------------------------------------------------
//            SEARCH RECORD 
//----------------------------------------------------------------

void accounts::search_record()
{
    int n;
    ifstream infile;
    infile.open("account.dat", ios::binary);
    if(!infile)
    {
        cout<<"\n\tFile does not exist !!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n\t Your record number : ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    display_account();
}

//----------------------------------------------------------------
//           UPDATE RECORD
//----------------------------------------------------------------

void accounts::modify_record()
{
    int n;
    fstream iofile;
    iofile.open("account.dat", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\n\t File doest not exist !!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\n\t Your record number : ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"\tRecord "<<n<<" has following data"<<endl;
    display_account();
    iofile.close();
    iofile.open("account.dat", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\n\tEnter data to Modify "<<endl;
    read_account();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}

//----------------------------------------------------------------
//            DELETE RECORD
//----------------------------------------------------------------

void delete_record()
{
    int n;
    ifstream infile;
    infile.open("account.dat", ios::binary);
    if(!infile)
    {
        cout<<"\n\t File does exist !!!"<<endl;

    }
    infile.seekg(0,ios::end);

    cout<<"\n Enter Record Number to Delete: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bank", ios::out|ios::binary);
    infile.seekg(0);
    infile.close();
    tmpfile.close();
    remove("account.dat");
    rename("tmpfile.bank", "account.dat");
}


//----------------------------------------------------------------
//            BALANCE FUNCTION
//----------------------------------------------------------------


void accounts::balance_record()
{
    int n;
    fstream iofile;
    iofile.open("account.dat", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\n\t File doest not exist !!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\n\t Your record number : ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"\tRecord "<<n<<" has following data"<<endl;
    display_account();
    iofile.close();
    iofile.open("account.dat", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    read_account();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}

//----------------------------------------------------------------
//            MAIN FUNCTION
//----------------------------------------------------------------

int main()
{
	system("color F1");
	password();
	banner();
    accounts A;
    int choice;
    do
    {
     system("cls");
        
         cout<<"\n\n\n\t ***************************************"<<endl;
        cout<<"\n\n\n\t ***************************************"<<endl;
        cout<<"\n\n\n\t\tMAIN MENU";
        cout<<"\n\n\n\t ***************************************"<<endl;
        cout<<"\n\n\t\tSelect Your Option (1-5) ";
        cout<<"\n\n\t\t01. ADMIN";
        cout<<"\n\n\t\t02. CUSTOMER";
        cout<<"\n\n\t\t03. MANAGER";
        cout<<"\n\n\t\t04. ABOUT US";
        cout<<"\n\n\t\t05. CONTACT US";
        cout<<"\n\n\t\t06. EXIT";
        cout<<"\n\n\n\t ***************************************"<<endl;
        cout<<"\n\n\n\t ***************************************"<<endl;
        cin>>choice;
        system("cls");
       switch(choice)
        {
        case 1: // admin
           admin();
            break;
        case 2: // customer
          customer();
            break;
        case 3: // contact us
        	manager();
            break;
        case 4: //about us
          about_us();
            break;
        case 5: // contact us
            contact_us();
            break;
        case 6://exit
          exit(0);
            break;
        default:
            cout<<"\nEnter corret choice";
            exit(0);
        }
        cin.ignore(); //used to ignore or clear one or more characters from the input buffer
        cin.get(); //accessing character array
    }while(choice!='5');
    return 0;
}
    

//----------------------------------------------------------------
//            CONTACT US
//----------------------------------------------------------------

void contact_us()
{
int ch;
        cout<<"\n\n\n\t ***************************************"<<endl;
         cout<<"\n\n\n\t ***************************************"<<endl;
        cout<<"\n\n\n\t\tCONTACT US";
        cout<<"\n\n\n\t ***************************************"<<endl;
        cout<<"\n\n\t\t01 xdmanahil2003@gmail.com";
        cout<<"\n\n\t\t02. jiarajpoot71@gmail.com";
        cout<<"\n\n\t\t03. rahatqadeerbhatti@gmail.com";
       cout<<"\n\n\n\t ***************************************"<<endl;
       cout<<"\n\n\t Press 1 to exit......";
       cin>>ch;
       if(ch==1)
       {
       	system("cls");
	   }
}

//----------------------------------------------------------------
//            FEEDBACK
//----------------------------------------------------------------

void feedback()
{
	system("cls");
	int choice;
	char feed[500];
	 cout<<"\n\n\n\t ***************************************"<<endl;
        cout<<"\n\n\t\t Feedback:";
         cout<<"\n\n\n\t ***************************************"<<endl;
        cin>>feed;
         cout<<"\n\n\n\t ***************************************"<<endl;
         cout<<"\n Press 1 to exit ....";
        cin>>choice;
        if(choice==1)
        {
        	system("cls");
		}
        
}

//----------------------------------------------------------------
//            ABOUT US
//----------------------------------------------------------------

void about_us()
{
	
	int ch;
         cout<<"\n\n\n\t ***************************************"<<endl;
         cout<<"\n\n\n\t ***************************************"<<endl;
        cout<<"\n\n\n\t\tABOUT US ";
        cout<<"\n\n\n\t ***************************************"<<endl;
        cout <<"\n\t We made this management system to provide ease to customers . "<<endl;
        cout<<"\n\t To provide easy way to (CRUD) ";
        cout<<"\n\t\t >> Create Record";
        cout<<"\n\t\t >> Read Record";
        cout<<"\n\t\t >> Update Record";
        cout<<"\n\t\t >> Delete Record";
        cout<<"\n\t using file handling ."<<endl;
        cout<<"\n\t This project is made by : ";
        cout<<"\n\t\t >> Manahil Habib";
        cout<<"\n\t\t >> Rahat Qadeer";
        cout<<"\n\t\t >> Wajeeha Nadeem"<<endl;
	    cout<<"\n\t We are students of Bachelors of software engineering ."<<endl;
		cout<<"\n\t From Riphah International University ";
		 cout<<"\n\n\n\t ***************************************"<<endl;
		 cout<<"\n\t Press 1 to exit ....";
		 if(ch==1)
		 {
		 	system("cls");
		 }
}

//----------------------------------------------------------------
//            CUSTOMER 
//----------------------------------------------------------------

void customer()
{
    char ch;
    int num;
    accounts A;

    do
    {
       system("cls");
        cout<<"\n\n\n\t ***************************************"<<endl;
		cout<<"\n\n\n\t\t\t CUSTOMER";
		 cout<<"\n\n\n\t ***************************************"<<endl;
    	cout<<"\n\n\t\t(1)	Account Registration";
    	cout<<"\n\n\t\t(2)	Balance";
    	cout<<"\n\n\t\t(3)	Display Customer Account";
    	cout<<"\n\n\t\t(4)	Contact Us";
    	cout<<"\n\n\t\t(5)	Feedback";
    	cout<<"\n\n\t\t(6)	Exit";
    	 cout<<"\n\n\n\t ***************************************"<<endl;
    	cin>>ch;
   		cout<<endl;
        system("cls");
        switch(ch)
        {
        case '1': //Account registration
          A.write_record();
            break;
            
        case '2': //Display customer account
          A.read_record();
            break;
            
        case '3': //Display customer account
         A.balance_record();
            break;
            
        case '4': //contact us
       		contact_us();
            break;
            
        case '5': //feedback
            feedback();
            break;
            
         case '6': //exit
            cout<<"\n\n\tThanks for using Customer service";
             system("cls");
            break;
         default :cout<<"Invalid Input";
        }
        cin.ignore(); //used to ignore or clear one or more characters from the input buffer
        cin.get(); //accessing character array
    }while(ch!='6');
}

//----------------------------------------------------------------
//            ADMINISTRATOR
//----------------------------------------------------------------

void admin()
{
	accounts A;
    char ch; 
    int num;
    do
    {
    
       system("cls");
        cout<<"\n\n\n\t ***************************************"<<endl;
		cout<<"\n\n\n\t\t\t ADMIN";
		 cout<<"\n\n\n\t ***************************************"<<endl;
    	cout<<"\n\n\t\t(1)	Customer Registration";
    	cout<<"\n\n\t\t(2)	Update Customer Account";
    	cout<<"\n\n\t\t(3)	Delete Customer Account";
    	cout<<"\n\n\t\t(4)	Display all Account";
    	cout<<"\n\n\t\t(5)	Exit";
    	 cout<<"\n\n\n\t ***************************************"<<endl;
   		cout<<endl;
        cin>>ch;
        system("cls");
        switch(ch)
        {
        case '1':  //customer registration
         A.write_record();
            break;
            
        case '2': // update customer account
          A.modify_record();
            break;
            
        case '3': //delete customer account
			 delete_record();
            break;
            
        case '4': //display all accounts
          A.read_record();
            break;
            
        case '5': //exit
          cout<<"\n\n\tThanks for using Admin service";
             system("cls");
            break;

         default :cout<<"Invalid input";
        }
        cin.ignore(); //used to ignore or clear one or more characters from the input buffer
        cin.get(); //accessing character array
    }while(ch!='5');
}
//----------------------------------------------------------------
//            MANAGER
//----------------------------------------------------------------

void manager()
{
	accounts A;
    char ch; 
    int num;
    do
    {
    
       system("cls");
        cout<<"\n\n\n\t ***************************************"<<endl;
		cout<<"\n\n\n\t\t\t MANAGER";
		 cout<<"\n\n\n\t ***************************************"<<endl;
    	cout<<"\n\n\t\t(1)	Create Account";
    	cout<<"\n\n\t\t(2)	Read Account";
    	cout<<"\n\n\t\t(3)	Update Account";
    	cout<<"\n\n\t\t(5)	Exit";
    	 cout<<"\n\n\n\t ***************************************"<<endl;
   		cout<<endl;
        cin>>ch;
        system("cls");
        switch(ch)
        {
        case '1':  //create account
         A.write_record();
            break;
            
        case '2': // read account
          A.read_record();
            break;
            
        case '3': //update customer account
         A.modify_record();
            break;
        
        case '4': //exit
          cout<<"\n\n\tThanks for using Manager service";
             system("cls");
            break;

         default :cout<<"Invalid input";
        }
        cin.ignore(); //used to ignore or clear one or more characters from the input buffer
        cin.get(); //accessing character array
    }while(ch!='4');
}

//----------------------------------------------------------------
//            PASSWORD
//----------------------------------------------------------------

void password ()
{
    string userName;
    string userPassword;
    int loginAttempt = 0;
 
 cout<<"\n\n\n\t ***************************************"<<endl;
 cout<<"\n\t Login :";
 cout<<"\n\n\n\t ***************************************"<<endl;
    while (loginAttempt < 3)
    {
        cout << "\n\t Username : ";
        cin >> userName;
        cout << "\n\t Password : ";
        cin >> userPassword;
cout<<"\n\n\n\t ***************************************"<<endl;
        if (userName == "manahil" && userPassword == "47876")
        {
            cout << "\n\t Welcome Manahil !";
            break;
        }
        else if (userName == "rahat" && userPassword == "47234")
        {
            cout << "\n\t Welcome Rahat !";
            break;
        }
         else if (userName == "wajeeha" && userPassword == "47328")
        {
            cout << "\n\t Welcome Wajeeha !";
            break;
        }
        else
        {
            cout << "\nInvalid" << '\n';
            loginAttempt++;
        }
    }
    if (loginAttempt == 3)
    {
            cout << "Too many login attempts! The program will now terminate.";
            
    }

    system("cls");
}


//----------------------------------------------------------------
//            WELCOME BANNER
//---------------------------------------------------------------
void banner ()
{
	int choice;
cout<<endl;
cout<<endl;
 	cout<<"\t\t ######     #    #     # #    #  "<<endl;
 	cout<<"\t\t #     #   # #   ##    # #   # "<<endl;
 	cout<<"\t\t #     #  #   #  # #   # #  # "<<endl;
 	cout<<"\t\t ######  #     # #  #  # ### "<<endl;
 	cout<<"\t\t #     # ####### #   # # #  # "<<endl;
 	cout<<"\t\t #     # #     # #    ## #   # "<<endl;
 	cout<<"\t\t ######  #     # #     # #    # "<<endl;
 	cout<<endl;
 	cout<<"\t\t ######  #######  #####  ####### ######  ######  "<<endl;
 	cout<<"\t\t #     # #       #     # #     # #     # #     #  "<<endl;
 	cout<<"\t\t #     # #       #       #     # #     # #     # "<<endl;
 	cout<<"\t\t ######  #####   #       #     # ######  #     # "<<endl;
 	cout<<"\t\t #   #   #       #       #     # #   #   #     # "<<endl;
 	cout<<"\t\t #    #  #       #     # #     # #    #  #     #  "<<endl;
 	cout<<"\t\t #     # #######  #####  ####### #     # ###### "<<endl;
 	cout<<endl;
 	cout<<"\t\t  #####  #     #  #####  ####### ####### #     # "<<endl;
 	cout<<"\t\t #     #  #   #  #     #    #    #       ##   ##  "<<endl;
 	cout<<"\t\t #         # #   #          #    #       # # # # "<<endl;
 	cout<<"\t\t  #####     #     #####     #    #####   #  #  # "<<endl;
	cout<<"\t\t       #    #          #    #    #       #     # "<<endl;
 	cout<<"\t\t #     #    #    #     #    #    #       #     # "<<endl;
 	cout<<"\t\t  #####     #     #####     #    ####### #     # "<<endl;
 	cout<<endl;

 cout<<"\n\t\tPress 1 to continue...";
 cin>>choice;
 if(choice)
 {
 	system("cls");
  }                                                         
}

//----------------------------------------------------------------
//            END OF PROGRAM
//---------------------------------------------------------------
