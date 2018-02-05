//Teacher Profile Management Project By Tushar Malik XII-A
/*
   Basic Features
Class defination
Append Records
Delete Records
Modify Records
Search Records for given Teacher Id.
Search Records for given Teacher Name
Sort Records on Experience using Selection Sort
Display list of Records
*/

#include<conio.h>
#include<stdio.h>
#include<fstream.h>
#include<ctype.h>
#include<string.h>

class teacher{
	int  Teacherid;   // Identification No. for a teacher
	char Name[25];    // Name of the teacher
	char Subject[10]; // Subject taught by the teacher
	float Exp;        // Experience of the teacher in years
	char Grade;       // Grade of the teacher on the basis of No. of years of experience

	public:
	teacher() {
		Teacherid=0;
		strcpy(Name,"Null");
		strcpy(Subject,"NULL");
		Exp=20;
		Grade='A';
		}
	void getdata(){
		cout<<"\nTeacher Id: ";
		cin>>Teacherid;
		cout<<"Name: ";
		gets(Name);
		cout<<"Subject Taught : ";
		cin>>Subject;
		cout<<"No. of Years of Experience: ";
		cin>>Exp;
		if(Exp>=15)
			Grade='A';
		else if(Exp>=10)
			Grade='B';
		else if(Exp>=5)
			Grade='C';
		else if(Exp>=2)
			Grade='D';
		else
			Grade='E';
	}
	char *getname() {
		return Name;
		}
	void putdata(){
		cout<<"Teacher "<<Name<<",Teacher Id "<<Teacherid<<" has "<<Exp<<" years of experience and is in "<<Grade<<" grade."<<endl;
	}
	int getteacherid(){
		return Teacherid;
	}
	float getexp(){
		return Exp;
	}
};

void appendrec(){
	ofstream fout("aaaa.dat",ios::binary|ios::app);
	teacher t1;
	cout<<"\nEnter the details of the Teacher to be appended to the file.";
	t1.getdata();
	fout.write((char*)&t1,sizeof(t1));
	cout<<"\nRecord Added to File !\n"<<endl;
	fout.close();
}

void deleterec(){
	ifstream fin("aaaa.dat",ios::binary);
	ofstream fout("temp.dat",ios::binary);
	int Teacherid,flag=0;
	cout<<"\nEnter Teacher Id. of Teacher whose Record is to be deleted: ";
	cin>>Teacherid;
	teacher t1;
	while(fin.read((char*)&t1,sizeof(t1))){
		if(t1.getteacherid()!=Teacherid){
			fout.write((char*)&t1,sizeof(t1));
		}
		else{
			flag=1;
			cout<<"\nRecord Deleted from file!\n"<<endl;
		}
	}
	fin.close();
	fout.close();
	remove("aaaa.dat");
	rename("temp.dat","aaaa.dat");
	if(flag==0)
		cout<<"\nTeacher not found!\n"<<endl;
}

void modifyrec(){
	ifstream fin("aaaa.dat",ios::binary);
	ofstream fout("temp.dat",ios::binary);
	int Teacherid;
	teacher t1,temp;
	cout<<"Enter Teacher Id. of Teacher whose record is to be modified: ";
	cin>>Teacherid;
	int flag=0;
	while(fin.read((char*)&t1,sizeof(t1))){
		if(t1.getteacherid()!=Teacherid){
			fout.write((char*)&t1,sizeof(t1));
		}
		else{
			flag=1;
			cout<<"Teacher Found!"<<endl;
			cout<<"Enter the modified Details of Teacher Id "<<Teacherid;
			temp.getdata();
			fout.write((char*)&temp,sizeof(temp));
			cout<<"\nRecord Modified in File !\n"<<endl;
		}
	}
	fin.close();
	fout.close();
	remove("aaaa.dat");
	rename("temp.dat","aaaa.dat");
	if(flag==0)
		cout<<"\nTeacher not found!\n"<<endl;
}

void searchrecteacherid(){        //Function to search for a Teacher Id in a Binary File
	int Teacherid;
	cout<<"\nEnter Teacher Id. of Teacher whose Record is to be searched: ";
	cin>>Teacherid;
	ifstream fin("aaaa.dat",ios::binary);
	teacher t1;
	int flag=0;
	while(fin.read((char*)&t1,sizeof(t1))){
		if(t1.getteacherid()==Teacherid){
			flag=1;
			cout<<"Teacher Found!"<<endl;
			t1.putdata();
			break;
		}
	}
	if(flag==0){
		cout<<"Teacher not Found in file!"<<endl;
	}
	fin.close();
}

void searchrecname(){
	teacher t1;
	ifstream fin("aaaa.dat",ios::binary);
	cout<<"Enter the name of the teacher to be searched: ";
	char Name[20];
	gets(Name);
	int flag=0;
	while(fin.read((char*)&t1,sizeof(t1))){
		if(strcmpi(t1.getname(),Name)==0){
			flag=1;
			cout<<"Teacher Found!\n";
			t1.putdata();
			break;
		}
	}
	if(flag==0){
		cout<<"Teacher not Found!\n";
	}
	fin.close();
}


void sortrec(){
    ifstream fin("aaaa.dat",ios::binary);
    teacher t1[20];
    int i=0;

    //Read the teacher data in an array
    while(!fin.eof()){
	fin.read((char*)&t1[i],sizeof(t1[i]));
	i++;
    }
    i--;

    // Apply Selection Sort on read data
    int pos;
    teacher min,t;

    for(int p=0;p<i;p++){
	min=t1[p];
	pos=p;
	for(int j=p+1;j<i;j++){
	    if(t1[j].getexp()<min.getexp()){
		min=t1[j];
		pos=j;
	    }
	}
	t=t1[p];
	t1[p]=t1[pos];
	t1[pos]=t;
    }
    fin.close();

    //Open file again in out mode and overwrite the sorted array.
    ofstream fout("aaaa.dat",ios::binary);
    for(p=0;p<i;p++){
	fout.write((char*)&t1[p],sizeof(t1[p]));
    }
    fout.close();
}

void displaylist(){
    teacher t1;
    ifstream fin("aaaa.dat",ios::binary);
    int count=0;
    cout<<"\nList of Teachers:\n";
    while(fin.read((char*)&t1,sizeof(t1))){
	t1.putdata();
	count++;
    }
    cout<<"\nA Total of "<<count<<" Teachers Found!! \n"<<endl;
    fin.close();
}


void main(){
	clrscr();
	ofstream fout("aaaa.dat",ios::binary);
	cout<<"Welcome to Teacher Profile System for Tushar International School\n\n";
	cout<<"Enter the No. of Teachers for whom you want to enter data: ";
	int n;
	cin>>n;
	teacher t1;
	for(int i=0;i<n;i++){
	       cout<<"\nEnter Data for Teacher No. "<<i+1;
	       t1.getdata();
	       fout.write((char*)&t1,sizeof(t1));
	}
	fout.close();

	char choice='y';
	int val;
	while(choice=='y'||choice=='Y'){
		cout<<"\n       Main Menu \n"<<endl;
		cout<<"Enter 1 to Add a New Teacher."<<endl;
		cout<<"Enter 2 to Delete an Existing Teacher."<<endl;
		cout<<"Enter 3 to Modify an Existing Teacher."<<endl;
		cout<<"Enter 4 to Search for a Teacher on the basis of Teacher Id."<<endl;
		cout<<"Enter 5 to Search for a Teacher on the basis of Teacher Name."<<endl;
		cout<<"Enter 6 to Sort the Records within the file."<<endl;
		cout<<"Enter 7 to Display List of all Teachers."<<endl;

		cin>>val;

		if(val==1)
			appendrec();
		else if(val==2)
			deleterec();
		else if(val==3)
			modifyrec();
		else if(val==4)
			searchrecteacherid();
		else if(val==5)
			searchrecname();
		else if(val==6)
			sortrec();
		else if(val==7)
			displaylist();
		else
			cout<<"Invalid Choice!\n";

		cout<<"Do You Wish to Continue?(y/n): ";
		cin>>choice;
	}
	getch();
}
