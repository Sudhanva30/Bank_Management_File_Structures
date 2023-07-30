#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;


class account
{
    int acno;
    char name[50];
    int deposit;
    char type;

public:
    void create_account();
    void show_account() const;
    void modify();
    void dep(int);
    void draw(int);
    void report() const;
    int retacno() const;
    int retdeposit() const;
    char rettype() const;
};

void account::create_account(){
    cout << "\n\tEnter the Account No. :";
    cin >> acno;
    cout << "\n\n\tEnter the Name of the Account Holder : ";
    cin.ignore();
    cin.getline(name,50);
    cout << "\n\tEnter Type of the Account (Current/Savings) : ";
    cin >> type;
    type = toupper(type);
    cout << "\n\tEnter the Initial deposit amount(>500 for Savings ac. and >=1000 for current) : ";
    cin >> deposit;
    cout << "\n\n\n\t --------------------------Account Created--------------------------";
    cout << "\n\n\n\t ########################### Click Enter ###########################";
}

void account:: show_account() const{
    cout << "\n\tAccount Number :" << acno; 
    cout << "\n\tAccount Holder Name : ";
    cout << name;
    cout << "\n\tType of Account : " << type;
    cout << "\n\tBalance amount : " << deposit;
}

void account::modify(){
    cout << "\n\tAccount No. : " << acno;
    cout << "\n\tModify Account Holder Name: ";
    cin.ignore();
    cin.getline(name,50);
    cout << "\n\tModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\n\tModify Balance amount : ";
    cin >> deposit;
}

void account::dep(int x){
    deposit += x;
}

void account::draw(int x){
    deposit -= x;
}

void account::report() const
{
    cout <<"\t" << acno << setw(10) << "\t" << name << setw(10) << "\t" << type <<"\t"<< deposit << endl;
}

int account::retacno() const{
    return acno;
}

int account::retdeposit() const{
    return deposit;
}

char account::rettype() const{
    return type;
} 


void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();

int main(){
    char ch;
    int num;
    intro();
    do{
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t1. NEW ACCOUNT";
        cout << "\n\n\t2. DEPOSIT AMOUNT";
        cout << "\n\n\t3. WITHDRAW ACCOUNT";
        cout << "\n\n\t4. BALANCE ACCOUNT";
        cout << "\n\n\t5. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t6. CLOSE AN ACCOUNT";
        cout << "\n\n\t7. MODIFY AN ACCOUNT";
        cout << "\n\n\t8. EXIT";
        cout << "\n\n\t Enter your service : ";
        cin >> ch;
        system("cls");
        switch(ch){
            case '1':
                write_account();
                break;
            case '2':
                cout << "\n\n\tEnter the Account Number :"; cin >> num;
                deposit_withdraw(num, 1);
                break;
            case '3':
                cout << "\n\n\tEnter The Account Number :"; cin >> num;
                deposit_withdraw(num, 2);
                break;
            case '4':
                cout << "\n\n\tEnter The Account Number :"; cin >> num;
                display_sp(num);
                break;
            case '5':
                display_all();
                break;
            case '6':
                cout << "\n\n\tEnter The Account Number :"; cin >> num;
                delete_account(num);
                break;
            case '7':
                cout << "\n\n\tEnter The Account Number :"; cin >> num;
                modify_account(num);
                break;
            case '8':
                cout << "\n\n\t--------------Thank You for using BANK Services--------------";
                break;
            default:cout << "\a";
        }
        cin.ignore();
        cin.get();
    }while(ch!= '8');
    return 0;
}

void write_account(){
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
    outFile.close();
}

void display_sp(int n){
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile)
    {
        cout<<"File not found !! ----  Please Press any key ----";
        return;
    }
    cout << "\n\t--------------BALANCE DETAILS--------------\n";
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
    {
        if(ac.retacno() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if(flag == false)
        cout << "\n\n-------------------Account number does not exist-------------------";
}


void modify_account(int n)
{
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if(!File)
    {
        cout << "File not found !! ----  Please Press any key ----";
        return;
    }
    while(!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if(ac.retacno() == n)
        {
            ac.show_account();
            cout << "\n\n\tEnter the New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout<<"\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if(found == false)
        cout << "\n\n\t Record Not Found.....!!!";
}

void delete_account(int n){
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile){
        cout << "File not found !! ----  Please Press any key ----";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
    {
        if(ac.retacno() != n)
        {
            outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n\n\t Record Deleted..";
}

void display_all(){
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile){
        cout << "File not found !! ----  Please Press any key ----";
        return;
    }
    cout << "\n\n\t\t--------------ACCOUNT HOLDER LIST--------------\n\n";
    cout << "\t===============================================================\n";
    cout << "\tA/c no.       Name                     Type    Balance\n";
    cout << "\t===============================================================\n";
    while(inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
    {
        cout<<"\n";
        ac.report();
    }
    inFile.close();
}


void deposit_withdraw(int n,int option){
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if(!File)
    {
        cout << "File not found !! ----  Please Press any key ----";
        return;
    }
    while(!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if(ac.retacno() == n)
        {
            ac.show_account();
            if(option == 1)
            {
                cout << "\n\n\t --------------TO DEPOSIT AMOUNT--------------";
                cout << "\n\n\t Enter the amount to be deposited: ";
                cin >> amt;
                ac.dep(amt);
            }
            if(option == 2)
            {
                cout << "\n\n\t --------------TO WITHDRAW AMOUNT-------------- ";
                cout << "\n\n\t Enter the amount to be withdraw: ";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype()  == 'C'))
                    cout <<"\n\n\t --------------Insufficient balance--------------";
                else
                    ac.draw(amt);
            }
            int pos = (-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout << "\n\n\t --------------Record Updated--------------";
            found = true;
            }
    }
    File.close();
    if(found == false)
        cout << "\n\n Record Not Found";
}

void intro(){
    cout<<"\n\n\n\t\t\tBANK";
    cout<<"\n\n\t\t\tMANAGEMENT";
    cout<<"\n\n\t\t\t  SYSTEM";
    cout<<"\n\n\n\n\tMADE BY : Sudhanva K S (1JB20IS072)\n \t\t  Tharun S (1JB20IS080)";
    cout<<"\n\n\tCourse : 6th Sem (ISE) 'B' Section";
    cout<<"\n\n\tCollege : SJB Institute of Technology";
    cin.get();
}
