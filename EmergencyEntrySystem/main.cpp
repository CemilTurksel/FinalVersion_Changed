#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cctype>
#include <type_traits>
#include <regex>
#include <sstream>
#include <string>
#include <windows.h>
using namespace std;
//The Class For Patients.
class Patient{
    //Private patient attributes(Data)
    private:
        string name;
        string surname;
        string address;
        string illness;
        string colourCode;
        int urgencyLevel;
    public:
        //Setter implementations.
        void set_name(string name){
            this->name=name;
        }
        void set_surname(string surname){
            this->surname=surname;
        }
        void set_address(string address){
            this->address=address;
        }
        void set_illness(string illness){
            this->illness=illness;
        }
        void set_colourCode(string colourCode){
            this->colourCode=colourCode;
        }
        void set_urgencyLevel(int urgencyLevel){
            this->urgencyLevel=urgencyLevel;
        }
        //--------------------------------
        //Getter implementations.
        string get_name(){
            return this->name;
        }
        string get_surname(){
            return this->surname;
        }
        string get_address(){
            return this->address;
        }
        string get_illness(){
            return this->illness;
        }
        string get_colourCode(){
            return this->colourCode;
        }
        int get_urgencyLevel(){
            return this->urgencyLevel;
        }
        //----------------------------------
};
//The Class For Health Personnel.
//Object Array.
Patient Patients[100];
//Object Vector.
vector<Patient> classified;
class Personnel{
    private:
        //Private Attributes of The Personnel To Check When Trying To Open System
        string Username="example-user";
        string Password="example-password";
        //-----------------------------------------------------------------------
    public:
        //Personnel's Public Data.
        string Name;
        string Surname;
        int Age;
        string Gender;
        int ExperiencePoints=0;
        //The Constructor
        Personnel(string name,string surname,int age,string gender,int experience_points=0){
            this->Name=name;
            this->Surname=surname;
            this->Age=age;
            this->Gender=gender;
            this->ExperiencePoints=experience_points;
        }
        //Getter Methods For User Name And Password.
        string Get_UserName(){
            return this->Username;
        }
        string Get_Password(){
            return this->Password;
        }
        //------------------------------------------
};
//The Class For Additional Personnel.
class Additional_Personnel:public Personnel{
    public:
        string Name;
        string Surname;
        int Age;
        string Gender;
        Additional_Personnel(string name,string surname,int age,string gender):Personnel(name,surname,age,gender){
            this->Name=name;
            this->Surname=surname;
            this->Age=age;
            this->Gender=gender;
        }
        void Give_Starting_Info(){
            cout<<"The new personnel "<<this->Name<<" "<<this->Surname<<" Has started to work.\n";
        }
        void change_department(){
            int choice;
            cout<<"Select the department that new employee will be appointed to: \n";
            cout<<"-> EMS (Ambulance) Coordination Center.(1)\n";
            cout<<"-> Consultation Rooms.(2)\n";
            cout<<"-> Major Trauma / Medical Areas.(3)\n";
            cout<<"-> Major Operating Room.(4)\n";
            cout<<"-> Injection Room.(5)\n\n";
            cin>>choice;
            if(cin.fail()){
                cout<<"\n";
                cout<<"ERROR-You did not enter a valid choice.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout<<"\n";
            }
            switch(choice){
                case 1:
                    cout<<"Employee has been appointed to EMS (Ambulance) Coordination Center.\n";
                    break;
                case 2:
                    cout<<"Employee has been appointed to Consultation Rooms\n";
                    break;
                case 3:
                    cout<<"Employee has been appointed to Major Trauma / Medical Areas.\n";
                    break;
                case 4:
                    cout<<"Employee has been appointed to Major Operating Room.\n";
                    break;
                case 5:
                    cout<<"Employee has been appointed to Injection Room.\n";
                    break;
            }
        }
};
//----------The Main Operations That Will Be Used In The Project----------
/*ListEntries(),AddEntry(),DeleteEntry(),SearchEntries(),ClassifyEntries()*/
//------------------------------------------------------------------------
//--------------------Additional Methods for The Project------------------
void GiveSearchInfo(int *search_choice){
    cout<<"To act quicker, searching via colour code is recommended."<<endl;;
    cout<<"Press 1 to confirm searching via colour code:(Compulsory)"<<endl;
    scanf("%d",search_choice);
    cout<<"\n";
}
//------------------------------------------------------------------------
//--------------------------METHOD DECLATRATIONS--------------------------
//-----------------
void ListEntries(){//Completed.
    int entry_counter=1;
    FILE *ptrList;
    ptrList=fopen("Entries.txt","r");
    //Error Management.
    if(ptrList==NULL){
        perror("Error opening...");
    }else{
        char a_name;
        a_name=getc(ptrList);
        printf("Informations of the %d. patient:\n\n",entry_counter);
        //Checks whether the end of the file.
        while(a_name!=EOF){
            printf("%c",a_name);
            a_name=getc(ptrList);
            if(a_name=='-'){
                a_name='\n';
                printf("%c",a_name);
                a_name=getc(ptrList);
                entry_counter++;
                printf("Informations of the %d. patient:\n",entry_counter);
            }
        }
    }
    fclose(ptrList);
}
//-------------------
Patient AddEntry(){//In Progress(Handle with the situation that first letters are lower.).
    static int i=0;
    string name,surname,address,illness,colourCode;
    ofstream AddEnt;
    AddEnt.open("Entries.txt",ios::app);
    printf("Enter the informations of the new entrance respectively: \n");
    printf("Name-Surname-Address-Illness-Colour Code:(First Letters Uppercase)\n");
    cin>>name>>surname>>address>>illness>>colourCode;
    //Checking whether the first letters are lower case and converting to upper case.
    name[0]=toupper(name[0]);
    surname[0]=toupper(surname[0]);
    address[0]=toupper(address[0]);
    illness[0]=toupper(illness[0]);
    colourCode[0]=toupper(colourCode[0]);
    //-------------------------------------------------------------------------------
    AddEnt<<name<<" "<<surname<<endl;
    AddEnt<<address<<endl;
    AddEnt<<illness<<endl;
    AddEnt<<colourCode<<endl;
    AddEnt.close();
    //Creating New Patient.
    Patient patient;
    patient.set_name(name);
    patient.set_surname(surname);
    patient.set_address(address);
    patient.set_illness(illness);
    patient.set_colourCode(colourCode);
    if(patient.get_colourCode()=="Green"){
        patient.set_urgencyLevel(1);
    }
    else if(patient.get_colourCode()=="Yellow"){
        patient.set_urgencyLevel(2);
    }
    else if(patient.get_colourCode()=="Red"){//3 is the highest urgency level.
        patient.set_urgencyLevel(3);
    }
    Patients[i]=patient;
    i++;
    classified.push_back(patient);
    return patient;
}
//--------------------
void DeleteEntry(int line_number){//Completed.
    int lineNumber=line_number;
    string fileName="Entries.txt";
    fstream read_file;
    read_file.open(fileName);
    if(read_file.fail()){
        perror("Opening File...");
    }
    vector<string> lines;
    string line;
    while(getline(read_file,line)){
        lines.push_back(line);
    }
    read_file.close();
    if(lineNumber>lines.size()){
        perror("Error!");
    }
    ofstream write_file;
    write_file.open(fileName);
    if(write_file.fail()){
        perror("Error Opening...");
    }
    lineNumber--;
    for(int i=0;i<lines.size();i++){
        if(i!=lineNumber){
            write_file<<lines[i]<<endl;
        }
    }
}
//----------------------
//Notes For This Function:
/*
As the system has to act fast and precise, SearchEntries function lists the urgency status of the patients.
Only the entries that added by using AddEntry function can be listed via SearchEntry function.
Because the main purpose of the creation of the system is not getting data from somewhere else, you add an entry and other
operations should be connected to those entries.
Yes, if you want to pull data from another resource, this feature is not going to work but that is what should be for this system.
Addition to these, via this feature we can guarantee the necessary quickness and data security.
*/
void SearchEntries(int choice){//Completed.
    if(choice==1){
        for(int i=0;i<=100;i++){
            if(Patients[i].get_urgencyLevel()==1){
                cout<<Patients[i].get_name()<<" "<<Patients[i].get_surname()<<":"<<endl;
                cout<<"\nThe urgency level is lowest for this patient.\n"<<endl;
                cout<<"The illness of the patient is: "<<Patients[i].get_illness()<<"\n"<<endl;
            }
            else if(Patients[i].get_urgencyLevel()==2){
                cout<<Patients[i].get_name()<<" "<<Patients[i].get_surname()<<":"<<endl;
                cout<<"\nThe urgency level is medium for this patient, inform the service.\n"<<endl;
                cout<<"The illness of the patient is: "<<Patients[i].get_illness()<<"\n"<<endl;
            }
            else if(Patients[i].get_urgencyLevel()==3){
                cout<<Patients[i].get_name()<<" "<<Patients[i].get_surname()<<":"<<endl;
                cout<<"\nThe urgency level is HIGHEST for this patient, necessary preparations must be done immediately!\n"<<endl;
                cout<<"The illness of the patient is: "<<Patients[i].get_illness()<<"\n"<<endl;
            }
        }
    }else{
        cout<<"\nError! Please make sure that you confirmed the search by pressing 1."<<endl;
    }
};
//This Function Creates a Table That Makes Easier Classifying Patients By Looking Their Illness.
//Mostly, Other Functions Give Detailed Data, This is a More Quick Classifying As a Table.
void ClassifyEntries(int a){//Fix The problem: shows deleted records.
    cout<<"\t\t\t\tName-Surname:";
    cout<<"\t\t\t\t";
    cout<<"Illness:\n\n";
    for(int i=0;i<a;i++){
        cout<<"\t\t\t\t";
        cout<<classified[i].get_name();
        cout<<" ";
        cout<<classified[i].get_surname();
        cout<<"\t\t\t\t";
        cout<<classified[i].get_illness();
        cout<<endl;
        cout<<"\n";
    }
}
//-------------------------
//The main function.
int main()
{
    //Text Colour Changing.
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,11);
    //---------------------
    //This System Have to Work With The Data That Only Written While The Application Runs, So If There Are Another Data ->
    //On The Entries.text(txt), Program Has to Clean That Data Before Doing Necessary Operations.
    //Clearing The Text File At The Beginning:
    FILE* ptr;
    ptr=fopen("Entries.txt","w");
    char check_clear;
    check_clear=getc(ptr);
    while(check_clear!=EOF){
        check_clear=getc(ptr);
        if(check_clear!=EOF){
            DeleteEntry(1);
        }
        if(check_clear==EOF){
            break;
        }
    }
    fclose(ptr);
    //----------------------------------------
    string username;
    string password;
    //One Personnel Will Be Responsible For The System Use, So We Create Only One Personnel Instance.
    Personnel personnel("Trial","Employee",30,"Female");
    //System Security Enter.
    printf("To enter the system, you have to enter user name and password.(username:example-user , password:example-password)\n\n");
    printf("User Name: ");
    cin>>username;
    printf("Password: ");
    cin>>password;
    //---------------------
    //The Loop For Checking Correct User Name and Password.
    while(1){
        if((personnel.Get_UserName()!=username && personnel.Get_Password()==password) || (personnel.Get_UserName()==username && personnel.Get_Password()!=password) ||
           (personnel.Get_UserName()!=username && personnel.Get_Password()!=password)){
            printf("\nWrong User Name and Password! Try Again.\n\n");
            printf("User Name: ");
            cin>>username;
            printf("Password: ");
            cin>>password;
            continue;
        }
        else{
            break;
        }
    }
    //----------------------------------------------------
    cout<<"\n";
    //After Password and User Name Entered Correctly.
    int choice;
    //The Main Loop For Taking Actions.
    while(choice!=7)
    {
        int counter=0;//Counter for calculating experience of the personnel.
        int static current_entry_counter=0;//Counter for checking whether there is a need for more personnel.
        int static personnel_number=1;
        printf("Welcome to the Emergency Entry System.\n\n");
        printf("Here are the quick operations to use:\n\n");
        printf(" 1-List Entries.\n 2-Add Entry.\n 3-Complete(Delete) First Entry.\n 4-Search Entries(Information and Urgency).\n");
        printf(" 5-Classify Entries.(Quick Look Table)\n 6-Open Personnel Management. \n 7-Exit. \n 8-Clear The Console.\n\n");
        printf("Enter your choice:(Must be a number 1-8)\n");
        cin>>choice;
        //Exception Handling.
        if(cin.fail()){
            cout<<"\n";
            cout<<"ERROR-You did not enter a number\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"\n";
            continue;
        }
        if(choice==1 || choice==2 || choice==3 || choice==4 || choice==5 || choice==6 || choice==7 || choice==8){
            choice=(int)choice;
        }
        else{
            cout<<"\n";
            printf("Choice must be a number 1-8\n\n");
            continue;
        }
        //--------------------
        //List
        if(choice==1){//Lists Entries.
            ListEntries();
            FILE *file_ptr;
            file_ptr=fopen("Entries.txt","r");
            char control;
            control=getc(file_ptr);
            if(control==EOF){
                printf("There is no entry yet.\n\n");
            }
            counter+=1;
            fclose(file_ptr);
        }
        //Add.
        else if(choice==2){//Adds An Entry;
            AddEntry();
            ofstream fixS;
            fixS.open("Entries.txt",ios::app);
            char fixSign='-';
            fixS<<fixSign;
            fixS<<'\n';
            fixS.close();
            counter+=2;
            current_entry_counter+=1;
            system("cls");
        }
        //Delete.
        else if(choice==3){//Delete The Completed Entry(First Entry Should Be Treated First).
            //Exception Handling For Deleting Even If There Is No Data.
            FILE *file_ptr;
            file_ptr=fopen("Entries.txt","r");
            char control;
            control=getc(file_ptr);
            if(control==EOF){
                printf("\nEmpty entry file: There is not any entry in the system.(Nothing to complete/delete)\n\n");
            }
            //-------------------------------------
            else{
                int recordNumber=1;
                for(int i=1;i<=5;i++){
                    DeleteEntry(recordNumber);
                }
                counter+=3;
                current_entry_counter--;
            }
            fclose(file_ptr);
            vector<Patient>::iterator it;
            it=classified.begin();
            classified.erase(it);
        }
        //Search.
        else if(choice==4){//Searches An Entry Via Colour Code.
            system("cls");
            int search_choice;
            GiveSearchInfo(&search_choice);
            SearchEntries(search_choice);
            counter++;
        }
        //Classify.
        else if(choice==5){//Classifies Entries.
            ClassifyEntries(current_entry_counter);
        }
        //Operations on personnel data.
        else if(choice==6){//It Opens The Personnel Information Screen.
            system("cls");
            printf("\n\n");
            printf("Here are the informations of the responsible personnel for this system(currently): \n\n");
            cout<<"Name: ";
            cout<<personnel.Name<<endl;
            cout<<"Surname: ";
            cout<<personnel.Surname<<endl;
            cout<<"Gender: ";
            cout<<personnel.Gender<<endl;
            cout<<"Age: ";
            cout<<personnel.Age<<endl;
            cout<<"\n";
            if(personnel.ExperiencePoints <= 20){
                printf("This personnel has not much experience with the system.\n");
                if(personnel.Gender=="Male"){
                    printf("His experience points: ");
                    cout<<personnel.ExperiencePoints<<endl;
                    cout<<"\n";
                }
                else{
                    printf("Her experience points: ");
                    cout<<personnel.ExperiencePoints<<endl;
                    cout<<"\n";
                }
            }
            else if(20<personnel.ExperiencePoints<=60){
                printf("This is an experienced personnel\n");
                if(personnel.Gender=="Male"){
                    printf("His experience points: ");
                    cout<<personnel.ExperiencePoints<<endl;
                    cout<<"\n";
                }
                else{
                    printf("Her experience points: ");
                    cout<<personnel.ExperiencePoints<<endl;
                    cout<<"\n";
                }
            }
            else if(60<personnel.ExperiencePoints<=100 || personnel.ExperiencePoints>100){
                printf("This is an expert personnel\n");
                if(personnel.Gender=="Male"){
                    printf("His experience points: ");
                    cout<<personnel.ExperiencePoints<<endl;
                    cout<<"\n";
                }
                else{
                    printf("Her experience points: ");
                    cout<<personnel.ExperiencePoints<<endl;
                }
            }
            cout<<"\nIf there are too many entries, you will have a choice to appoint additional personnel for the system.\n\n";
            if(current_entry_counter>=2){
                //Checking Whether There is a Need For Additional Personnel.
                char answer;
                printf("Seemingly there are lots of entries...\n\n");
                printf("It may be more than one personnel can be able to deal with. Is another personnel necessary? ");
                printf("Y/n\n");
                cin>>answer;
                if(answer=='y'){
                    answer=toupper(answer);
                }
                if(answer=='Y'){
                    //Creating Additional Personnel.
                    string name;
                    string surname;
                    string gender;
                    int age;
                    printf("\nAppoint another personnel.\n");
                    printf("Enter the name of the second responsible personnel: ");
                    cin>>name;
                    name[0]=toupper(name[0]);
                    cout<<"\n";
                    printf("Surname: ");
                    cin>>surname;
                    surname[0]=toupper(surname[0]);
                    cout<<endl;
                    printf("Gender: ");
                    cin>>gender;
                    gender[0]=toupper(gender[0]);
                    cout<<endl;
                    printf("Age: ");
                    cin>>age;
                    cout<<endl;
                    Additional_Personnel additional_personnel(name,surname,age,gender);
                    //Introducing New Personnel.
                    cout<<"Here are the information of the new personnel: \n";
                    cout<<"Name: ";
                    cout<<additional_personnel.Name<<endl;
                    cout<<"Surname: ";
                    cout<<additional_personnel.Surname<<endl;
                    cout<<"Gender: ";
                    cout<<additional_personnel.Gender<<endl;
                    cout<<"Age: ";
                    cout<<additional_personnel.Age<<endl;
                    current_entry_counter=0;
                    cout<<"\n\n";
                    personnel_number++;
                    //Note: Only one additional personnel can be appointed.
                    //Check If Any Additional Personnel is Appointed and Let Using Additional Functionalities.
                    if(personnel_number==2){//ON PROGRESS
                        additional_personnel.Give_Starting_Info();
                        char appoint_choice;
                        //Gender based if condition.
                        if(additional_personnel.Gender=="Female"){
                            cout<<"She can be appointed to any other section.\n"<<endl;
                            cout<<"Do you want her to work in another department? If you do not want , she will work in current (Emergency Recording/Emergency Reception), Y/n ?\n"<<endl;
                            cin>>appoint_choice;
                            if(appoint_choice=='y'){
                                appoint_choice=toupper(appoint_choice);
                            }
                            if(appoint_choice=='Y'){
                                additional_personnel.change_department();
                            }
                            else{
                                cout<<"She will not work in another department."<<endl;
                            }
                        }
                        //Gender based if condition.
                        else if(additional_personnel.Gender=="Male"){
                            cout<<"He can be appointed to any other section."<<endl;
                            cout<<"Do you want him to work in another department? If you do not want , she will work in current (Emergency Recording/Emergency Reception), Y/n ?\n"<<endl;
                            cin>>appoint_choice;
                            if(appoint_choice=='y'){
                                appoint_choice=toupper(appoint_choice);
                            }
                            if(appoint_choice=='Y'){
                                additional_personnel.change_department();
                            }
                            else{
                                cout<<"He will not work in another department."<<endl;
                            }
                        }
                    }
                    //----------------------------------------------------------------------------------------
                }
            }
        }
        //Exit.
        else if(choice==7){//Finishes The Application.
            printf("Program finished.");
            exit(0);
        }
        //Clear.
        else if(choice==8){//Clear The Console.
            system("cls");
        }
        //After Any Operation Is Done, The Points Are Added To The Experience Points Of The Current Responsible Employee By The Code Below.
        personnel.ExperiencePoints+=counter;
    }
    return 0;
}
