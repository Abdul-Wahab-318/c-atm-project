#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<iomanip>
using namespace std;
int i=0; // explained later. 
class Bank{
	public:
	long int c_id;
	char name[30];
	char cnic[20];
	char type[15];
	char password[10];
	float balance;
	public:
		
	void getData()
{
	cout<<"Enter Customer ID(6digits): ";
	cin>>this->c_id;
	cout<<"Enter CNIC: ";
	cin>>this->cnic;
	cout<<"Enter password: ";
	cin>>this->password;
	cout<<"Enter Name: ";
	cin>>this->name;
	cout<<"Enter Account type: ";
	cin>>this->type;
	cout<<"Enter Balance: ";
	cin>>this->balance;
	
	
}
	void showAllData()
{
	cout<<"\nCustomer ID: ";
	cout<<this->c_id;
	cout<<"\nCNIC: ";
	cout<<this->cnic;
	cout<<"\nPassword: ";
	cout<<this->password;
	cout<<"\nName: ";
	cout<<this->name;
	cout<<"\nAccount type: ";
	cout<<this->type;
	cout<<"\nBalance: ";
	cout<<this->balance<<"\n";
	
}
    void showData()
{
	cout<<this->c_id<<setw(15)<<this->cnic<<setw(15)<<this->password<<setw(15)<<this->name<<setw(15)<<this->type<<setw(15)<<this->balance<<"\n";
	
}

    void writeRecord()
{
	ofstream out;
	out.open("1dec.dat",ios::app|ios::out|ios::binary);
	out.write((char*)this, sizeof(*this));
	cout<<"\nSaved\n";
	
}
    
    void readRecord()
{
	ifstream in;
	in.open("1dec.dat",ios::in|ios::binary);
	in.read((char*)this,sizeof(*this));
	while(!in.eof())
	{
	//showAllData();//shows data in different way
	showData();  //shows data in single row
	in.read((char*)this,sizeof(*this));
    }
}

    void search(long int c_id)
{
	ifstream in;
	in.open("1dec.dat",ios::in|ios::binary);
	in.read((char*)this,sizeof(*this));
	while(!in.eof())
	{
		if(this->c_id==c_id)
		{
			i++;
			cout<<"Record Found\n";
			this->showData();
		}
		in.read((char*)this,sizeof(*this));
	}
	if(i<1)  // basically i will get incremented if record is found . When record wont be found it will stay =0
	{
		cout<<"Record not found "<<endl;
	}
    i=0;
}

	void copyFile(char *f1, char *f2)
{
	ifstream fin;
	ofstream fout;
	char c;
	
	fin.open(f1,ios::in|ios::binary);
	fout.open(f2,ios::app|ios::out|ios::binary);
	c=fin.get();
	while(!fin.eof())
	{
		fout<<c;
		c=fin.get();
		
	}
	fin.close();
	fout.close();
	
}

	void deleteRecord(long int c_id)
	{
		ifstream fin;
		ofstream fout;
		fin.open("1dec.dat", ios::in| ios::binary);

	    fout.open("tempFile.dat", ios::out|ios::binary);
	   	fin.read((char*)this, sizeof(*this));
	   	while(!fin.eof())
	   	{
	    	if(this->c_id!=c_id)
	    	{
	    	fout.write((char*)this, sizeof(*this));
	    	}
	    	if(this->c_id==c_id)
	    	cout<<"\nRecord Deleted\n";
	    	fin.read((char*)this, sizeof(*this));
		}
	   	fin.close();
	    fout.close();
	    remove("1dec.dat");
	    rename("tempFile.dat","1dec.dat");	
    }
	
	void updateRecord(long int c_id)
	{
		fstream f;
		f.open("1dec.dat",ios::in|ios::out|ios::ate|ios::binary);
		f.seekg(0);
		f.read((char*)this, sizeof(*this));
		while(!f.eof())
		{
			if(this->c_id==c_id)
			{
				cout<<"\nRecord found !\n";
				showData();
				getData();
				f.seekp(f.tellp()-sizeof(*this));
				f.write((char*)this, sizeof(*this));
			}
			f.read((char*)this, sizeof(*this));
		}
		
		
	}
	void transaction(long int c_id, char *p,float withdraw)
	{
		bool flag=false;
		fstream f;
		f.open("1dec.dat",ios::in|ios::out|ios::ate|ios::binary);
		f.seekg(0);
		f.read((char*)this, sizeof(*this));
		while(!f.eof())
		{
			if(this->c_id==c_id && !strcmp(p,password))
			{
				flag=true;
				cout<<"\nRecord found !\n";
				cout<<"Bank Balance: "<<balance<<endl;
				cout<<"Enter the withdrawal amount: ";
				cin>>withdraw;
				if(withdraw>balance)
				{
					cout<<"Withdrawal amount exceeds bank balance\n";
				}
				else
				{
					balance-=withdraw;
					cout<<"Transaction Complete\n";
				}
				
				f.seekp(f.tellp()-sizeof(*this));
				f.write((char*)this, sizeof(*this));
			}
			f.read((char*)this, sizeof(*this));
		}
		if(flag==false)
		{
			cout<<"Wrong ID or Password"<<endl;
		}
	}
};


int main()
{
	int choice;
	char op;
	float withdraw;
	char password[10];
	long int c_id;
	Bank b;
	do
	{
		system("color 8b");
		cout<<"1. Enter Customer Details		\n2. Display All Customers		\n3. Search Customer Record            	\n4. Delete a Record	 \n5. Update a Record  \n6. Withdraw Cash ";
		cout<<"\n\nEnter your choice: ";
		cin>>choice;
		if(choice==1)
		{
			b.getData();
			b.writeRecord();
		}
		else if(choice==2)
		{
			b.readRecord();
		}
		else if(choice==3)
		{
			cout<<"Enter Customer ID: ";
			cin>>c_id;
			b.search(c_id);
		}
		else if(choice==4)
		{
			cout<<"Enter the ID of the record you want to delete: ";
			cin>>c_id;
			b.deleteRecord(c_id);
		}
		else if(choice==5)
		{
			cout<<"Enter the ID of the record you want to Update: ";
			cin>>c_id;
			b.updateRecord(c_id);
		}
		else if(choice==6)
		{
			cout<<"Enter the ID and Password of your Account: \n";
			cout<<"Customer ID(6-digits): ";
			cin>>c_id;
			cout<<"Password: ";
			cin>>password;
			b.transaction(c_id,password,withdraw);
		}
		else
		{
			system("color 40");
			cout<<"\nInvalid Choice\n";
		}
		cout<<"Return to Main Menu? (y/n): ";
		cin>>op;
		
	}while(op!='n');
	
}
