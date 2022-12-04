// Airps.cpp : Software Engineering Group Project
//

#include <iostream>
#include <iomanip>
#include<fstream>
#include <string>
#include<string.h>
using namespace std;

class NewUser {
private:
    string USERNAME;
    string PASSWORD;
        
    void AssignUsername() {
        string username;
        cout << "Enter Username: ";
        cin.ignore();
        getline(cin, username);
        USERNAME = username;
    }

    void AssignPassword() {
        string password;
        cout << "Enter Password: ";
        getline(cin, password);
        PASSWORD = password;
        ofstream CredentialsUpdater;
        CredentialsUpdater.open("Credentials_" + USERNAME + ".txt");
        CredentialsUpdater << PASSWORD;

    }

    bool IsFileEmpty() {
        string temp;
        ifstream USERNAME_LIST;
        USERNAME_LIST.open("UserList.txt");

        getline(USERNAME_LIST, temp);

        if (temp == "") {
            return 1;
        }
        else {
            return 0;
        }

        USERNAME_LIST.close();
    }

    void CreateFiles() {
        ofstream NewIDlist;
        ofstream NewOrderStatus;
        ofstream NewOutAddress;
        ofstream NewAddress;
        ofstream Credetentials;

        string IDlistName = "IDlist_" + USERNAME + ".txt";
        string OrderStatusName = "Order Status_" + USERNAME + ".txt";
        string OutAddressName = "Outgoing Address_" + USERNAME + ".txt";
        string RetAddressName = "User Address_" + USERNAME + ".txt";
        string CredentialsName = "Credentials_" + USERNAME + ".txt";


        NewIDlist.open(IDlistName);
        NewOrderStatus.open(OrderStatusName);
        NewOutAddress.open(OutAddressName);
        NewAddress.open(RetAddressName);
        Credetentials.open(CredentialsName);

        NewIDlist.close();
        NewOrderStatus.close();
        NewOutAddress.close();
        NewAddress.close();
        Credetentials.close();

    }

    void UpdateUsernameDatabase() {
        ofstream USERNAME_LIST;
        USERNAME_LIST.open("UserList.txt", ios::app);

        if (!IsFileEmpty()) {
            USERNAME_LIST << endl;
        }
        USERNAME_LIST << USERNAME;
        USERNAME_LIST.close();
    }

public:
    NewUser() {
        AssignUsername();
        CreateFiles();
        AssignPassword();
        UpdateUsernameDatabase();
        
        
    }
     
    
};

class UserPasswordManager {
private:
    string USERNAME;
    string PASSWORD;

    void PasswordChanger() {
        cout << endl << endl;
        cout << "Enter New Password: ";
        getline(cin, PASSWORD);

        ofstream NEWPASSWORD;
        NEWPASSWORD.open("Credentials_" + USERNAME + ".txt");
        NEWPASSWORD << PASSWORD;

        NEWPASSWORD.close();
    }

public:
    UserPasswordManager(string username) {
        USERNAME = username;
        PasswordChanger();
    }
};

class NewOrder {

private:
    string USERNAME;
    string Package_Name;
    string ID;
    string Order_Status;

    string Out_Street_Address;
    string Out_ZIP;
    string Out_City;
    string Out_State;

    string Street_Address;
    string ZIP;
    string City;
    string State;

public:
    //Constructor
    NewOrder(string pckge_name, string username){
        Package_Name = pckge_name;
        Order_Status = "Initiated";
        USERNAME = username;
    } 

    //Sets PAckage Name
    void SetName(string Name) {
        Package_Name = Name;
    }

    //Generates ID for package.
    void generate_ID() {
        fstream IDlist;
        IDlist.open("IDlist_" + USERNAME + ".txt");
        string x;
        int y = 0;
        if (IDlist) {
            for (int i = 0; !IDlist.eof(); i++) {

                getline(IDlist, x);
                y = i + 1;

            }
        }

        ID = to_string(y);

        IDlist.close();
    }

    //Return's Package ID.
    string getID() {
        return ID;
    }

    //Sets Receipients' Address.
    void SetOutAddress(string OutStreet, string OutCity, string OutState, string OutZIP) {
        Out_Street_Address = OutStreet;
        Out_City = OutCity;
        Out_State = OutState;
        Out_ZIP = OutZIP;
    }

    //Sets Return Address.
    void SetUserAddress(string User_Street, string User_City, string User_State, string User_ZIP) {
       Street_Address = User_Street;
       City = User_City;
       State = User_State;
       ZIP = User_ZIP;
    }

    //Updates all text files.
    void UpdateFiles() {

        //Updating ID and Package Name in IDlist.txt

        ofstream O_IDlist;
                              
        O_IDlist.open("IDlist_" + USERNAME + ".txt", ios_base::app);
        
        O_IDlist << ID <<"$"<< Package_Name<<endl;

        O_IDlist.close();
        

        //Updating Addresses in Outgoing Address.txt

        
        ofstream O_OutAddresslist;
 
        O_OutAddresslist.open("Outgoing Address_" + USERNAME + ".txt", ios_base::app);

        O_OutAddresslist << Out_Street_Address << "$" << Out_City << "$" << Out_State << "$" << Out_ZIP << endl;

        O_OutAddresslist.close();

        //Updates Addresses in User Address.txt

        ofstream O_Addresslist;

        O_Addresslist.open("User Address_" + USERNAME + ".txt", ios_base::app);

        O_Addresslist << Street_Address << "$" << City << "$" << State << "$" << ZIP << endl;

        O_Addresslist.close();

        //Updates Order Status in Order Status.txt

        
        ofstream O_OrderStatus;
        
        O_OrderStatus.open("Order Status_" + USERNAME + ".txt", ios_base::app);

        O_OrderStatus << ID << "$" << Order_Status << endl;

        O_OrderStatus.close();

    }
       
 
};

class UserUI {

private:
    void AddOrder() {
        
        string Name;
        cout << "Enter Package Name: ";
        getline(cin, Name);

        NewOrder nuggets(Name,USERNAME);
        nuggets.generate_ID();

        
        string Address = "";
        string city = "";
        string state = "";
        string ZIP = "";


        cout << "Enter Delivery Address:" << endl;
        cout << "Street Address: ";
        
        getline(cin, Address);
        cout << "City: ";
        getline(cin, city);
        cout << "State: ";
        getline(cin, state);
        cout << "ZIP: ";
        getline(cin, ZIP);

        nuggets.SetOutAddress(Address, city, state, ZIP);

        Address = "";
        city = "";
        state = "";
        ZIP = "";

        cout << "Enter Return Address:" << endl;
        cout << "Street Address: ";
        getline(cin, Address);
        cout << "City: ";
        getline(cin, city);
        cout << "State: ";
        getline(cin, state);
        cout << "ZIP: ";
        getline(cin, ZIP);


        nuggets.SetUserAddress(Address, city, state, ZIP);

        nuggets.UpdateFiles();
    }
    
    void ViewOrder() {
        ifstream USERDATA_ID;
        ifstream USERDATA_OutAdd;
        ifstream USERDATA_RetAdd;
        ifstream USERDATA_OS;

        USERDATA_ID.open("IDlist_" + USERNAME + ".txt");
        USERDATA_OutAdd.open("Outgoing Address_" + USERNAME + ".txt");
        USERDATA_RetAdd.open("User Address_" + USERNAME + ".txt");
        USERDATA_OS.open("Order Status_" + USERNAME + ".txt");

        string tempstr = "";

        int LISTSIZE = list_size();

        cout << endl << endl << "ID\t" << "Name\t\t\t\t\t" << "Delivery Address\t\t\t\t" << "Return Address \t\t\t\t\t\t\t" << "Order Status"<<endl<<endl;

        for (int i = 0; i < LISTSIZE -1; i++) {
            
            getline(USERDATA_ID, tempstr, '$');
            cout << tempstr<< "\t";

            getline(USERDATA_ID, tempstr);
            cout << tempstr<<"\t\t";

            getline(USERDATA_OutAdd, tempstr, '$');
            cout << tempstr<<", ";

            getline(USERDATA_OutAdd, tempstr, '$');
            cout << tempstr << ", ";

            getline(USERDATA_OutAdd, tempstr, '$');
            cout << tempstr << ", ";

            getline(USERDATA_OutAdd, tempstr);
            cout << tempstr << "." <<"\t\t\t";


            getline(USERDATA_RetAdd, tempstr, '$');
            cout << tempstr << ", ";

            getline(USERDATA_RetAdd, tempstr, '$');
            cout << tempstr << ", ";

            getline(USERDATA_RetAdd, tempstr, '$');
            cout << tempstr << ", ";

            getline(USERDATA_RetAdd, tempstr);
            cout << tempstr << "." << "\t\t\t";


            getline(USERDATA_OS, tempstr, '$');
            getline(USERDATA_OS, tempstr);
            cout << tempstr;

            cout << endl;

        }

        USERDATA_ID.close();

    }

    int list_size() {
        fstream IDlist;
        IDlist.open("IDlist_" + USERNAME+ ".txt");
        string x;
        int y = 0;
        if (IDlist) {
            for (int i = 0; !IDlist.eof(); i++) {

                getline(IDlist, x);
                y = i + 1;

            }
        }

        return y;

        IDlist.close();
    }
    
    string USERNAME;

public:
    UserUI(string username){
        USERNAME = username;
    }

    void Menu() {
        bool controller = 1;
        string UserAnswer = "n";
        string MenuNumber = "0";
        do {

            cout << endl << endl;
            cout << "What would you like to do:" << endl;
            cout << " 1 - Add Order"<<endl;
            cout << " 2 - View Order" << endl;
            cout << " 3 - Change Password" << endl;
            cout << " 4 - Exit" << endl;
            
            cout << endl <<"Enter Number: ";
            getline(cin, MenuNumber);

            if (MenuNumber == "1") {
                AddOrder();
            }
            else if(MenuNumber == "2"){
                ViewOrder();
            }
            else if (MenuNumber == "3") {
                UserPasswordManager CurrentUser(USERNAME);
            }
            else if (MenuNumber == "4") {
                break;
            }


            cout << "Would you like to do something else? (Answer y or n)" << endl;
            getline(cin, UserAnswer);
            if (UserAnswer == "y" || UserAnswer == "Y") {
                controller = 1;
            }
            else {
                controller = 0;
            }

        } while (controller);
        
    }

    
};

class PilotUI {
private:
    string USERNAME;

    int AmountOfUsers;
    
    bool isFileEmpty(string fileName) {
        ifstream file(fileName);
        file.seekg(0, ios::end); // points to the end of file
        int length = file.tellg(); // returns the end of file's index , if its 0 then the file is empty

        if (length == 0) {
            return 1;
        }
        else {
            return 0;
        }
    
    }

    void DisplayOptions() {
        ifstream USERDATA_ID;
        ifstream USERDATA_OutAdd;
        ifstream USERNAMELIST;

        string tempstr = "";
        string customerUsername = "";

        USERNAMELIST.open("UserList.txt");

        cout << endl << endl <<"Option\t" << "Name\t\t" << "Delivery Address\t\t\t\t" << endl << endl;

       
        for (int i = 0; !USERNAMELIST.eof(); i++) {

            getline(USERNAMELIST, customerUsername);

            USERDATA_ID.open("IDlist_" + customerUsername + ".txt");
            USERDATA_OutAdd.open("Outgoing Address_" + customerUsername + ".txt");



            if (!isFileEmpty("IDlist_" + customerUsername + ".txt")) {

                for (int j = 0; !USERDATA_ID.eof(); j++) {

                                                            

                    getline(USERDATA_ID, tempstr, '$');

                    if (tempstr != "") {
                        cout << i + 1 << " - " << j + 1 << "\t";
                        getline(USERDATA_ID, tempstr);


                        cout << tempstr << "\t\t";

                        getline(USERDATA_OutAdd, tempstr, '$');
                        cout << tempstr << ", ";
                        getline(USERDATA_OutAdd, tempstr, '$');
                        cout << tempstr << ", ";
                        getline(USERDATA_OutAdd, tempstr, '$');
                        cout << tempstr << ", ";
                        getline(USERDATA_OutAdd, tempstr);
                        cout << tempstr << ".";

                        cout << endl;
                    }
                }

                USERDATA_ID.close();
                USERDATA_OutAdd.close();
            }
        }
        USERNAMELIST.close();

    }

    void PickPackage() {
        ofstream PICKEDPACKAGE;
        ifstream UserPackageList;
        ifstream UserOutAddressList;
        ifstream USERLIST;

        USERLIST.open("UserList.txt");
        PICKEDPACKAGE.open("PickedPackages_" + USERNAME + ".txt", ios_base::app);

        
        string option;
        string temp;
        int username_Number;
        string customer_username;
        int packageID;
        string packageName;
        string packageAddress;
        
        cout << endl << "Pick Option: ";
        getline(cin, option);


        for (int i = 0; i < AmountOfUsers; i++) {
            for (int j = 0; j < 100; j++) {
                if ((to_string(i + 1) + " - " + to_string(j + 1)) == option) {
                    username_Number = i + 1;
                    packageID = j + 1;
                }
            }
        }

        for (int i = 0; !USERLIST.eof(); i++) {
            getline(USERLIST, temp);
            if (i == (username_Number - 1)) {
                customer_username = temp;
            }
        }

        
        UserPackageList.open("IDlist_" + customer_username + ".txt");
        UserOutAddressList.open("Outgoing Address_" + customer_username + ".txt");
        
        
        for (int i = 0; !UserPackageList.eof(); i++) {

            getline(UserPackageList, temp,'$');
            
            getline(UserPackageList, temp);

            if (i == (packageID - 1)) {
                packageName = temp;
            }

        }

        for (int i = 0; !UserOutAddressList.eof(); i++) {
            getline(UserOutAddressList, temp,'$');
            if (i == (packageID - 1)) {
                packageAddress = temp;
            }
            getline(UserOutAddressList, temp, '$');
            if (i == (packageID - 1)) {
                packageAddress += ", ";
                packageAddress += temp;
            }
            getline(UserOutAddressList, temp, '$');
            if (i == (packageID - 1)) {
                packageAddress += ", ";
                packageAddress += temp;
            }
            getline(UserOutAddressList, temp);
            if (i == (packageID - 1)) {
                packageAddress += ", ";
                packageAddress += temp;
                packageAddress += ".";
            }

        }
        cout << endl << "Name: " << packageName << "\t Address: " << packageAddress << endl;

        // Update Order Status

        ofstream ORDERSTATUS;
        ifstream I_ORDERSTATUS;
        ofstream TEMP;
        ifstream I_TEMP;

        I_ORDERSTATUS.open("Order Status_" + customer_username + ".txt");        
        TEMP.open("TEMP.txt");
        for (int i = 0;!I_ORDERSTATUS.eof();i++) {
            getline(I_ORDERSTATUS, temp);
            if (i == packageID-1) {
                temp = to_string(i + 1) + "$Accepted By Pilot";
            }
            if (i == 0) {
                TEMP << temp;
            }
            else {
                TEMP << endl << temp;
            }
        }

        

        ORDERSTATUS.open("Order Status_" + customer_username + ".txt");
        I_TEMP.open("TEMP.txt");

        for (int i = 0;!I_TEMP.eof();i++) {
            getline(I_TEMP, temp);
            if (i == 0) {
                ORDERSTATUS << temp;
            }
            else {
                ORDERSTATUS << endl << temp;
            }
        }

        PICKEDPACKAGE << packageName <<"$" << packageAddress << endl;

        UserPackageList.close();
        UserOutAddressList.close();
        PICKEDPACKAGE.close();
        USERLIST.close();
        ORDERSTATUS.close();
        TEMP.close();
    }

    void DislayOrders() {
        ifstream PILOTORDERS;
        PILOTORDERS.open("PickedPackages_"+ USERNAME +".txt");

        string temp;
        

        cout << endl << "Order Name\t\t" << "Destination Address" << endl<<endl;
        for (int i = 0;!PILOTORDERS.eof();i++) {
            getline(PILOTORDERS, temp, '$');
            cout << temp<<"\t\t";
            getline(PILOTORDERS, temp);
            cout << temp << endl;

        }

        PILOTORDERS.close();

    }

public:
    PilotUI(string username) {
        USERNAME = username;

        string temp;
        
        ifstream USERLIST;
        USERLIST.open("UserList.txt");
        
        AmountOfUsers = 0;
        for (int i = 0; !USERLIST.eof(); i++){
            getline(USERLIST, temp);
            AmountOfUsers = i + 1;
        }
        USERLIST.close();

    }

    void Menu() {
        bool controller = 1;
        string UserAnswer = "n";
        string MenuNumber = "0";
        while (controller) {

            cout << endl << endl;
            cout << "What would you like to do:" << endl;
            cout << " 1 - Pick Package" << endl;
            cout << " 2 - View Orders" << endl;
            cout << " 3 - Exit" << endl;

            cout << endl << "Enter Number: ";
            getline(cin, MenuNumber);

            if (MenuNumber == "1") {
                DisplayOptions();
                PickPackage();
            }
            else if (MenuNumber == "2") {
                DislayOrders();
            }
            else {
                break;
            }


            cout << "Would you like to do something else? (Answer y or n)" << endl;
            getline(cin, UserAnswer);
            if (UserAnswer == "y" || UserAnswer == "Y") {
                controller = 1;
            }
            else {
                controller = 0;
            }

        } 

    }

};

class UserLogin {
private:
    string USERNAME;
    string PASSWORD;

    bool isUsernameValid(string username) {

        string temp;

        ifstream PusernameLIST;
        PusernameLIST.open("UserList.txt");

        for (int i = 0; !PusernameLIST.eof();i++) {
            getline(PusernameLIST, temp);
            if (temp == username) {
                PusernameLIST.close();
                return 1;
            }

        }

        PusernameLIST.close();
        return 0;
    }
       
public:
    UserLogin() {
        string temp;
                
        cin.ignore();
        
        do {
            cout << "Username: ";
            getline(cin, temp);

            if (isUsernameValid(temp)) {
                USERNAME = temp;
            }
            else {
                cout << "Invalid Username. Please try again." << endl << endl;
            }


        } while (!isUsernameValid(temp));


        ifstream passwordExtractor;

        passwordExtractor.open("Credentials_" + USERNAME + ".txt");
        getline(passwordExtractor, PASSWORD);
    }
    bool passwordValidifier() {
        string UserInput;
        cout << "Password: ";
        getline(cin, UserInput);

        if (UserInput == PASSWORD) {
            return 1;
        }
        else {
            return 0;
        }
    }
    string GetUsername() {
        return USERNAME;
    }
};

class PilotLogin {
private:
    string USERNAME;
    string PASSWORD;

    bool isUsernameValid(string username) {

        string temp;

        ifstream PusernameLIST;
        PusernameLIST.open("PilotUsernameList.txt");

        for (int i = 0; !PusernameLIST.eof();i++) {
            getline(PusernameLIST, temp);
            if (temp == username) {
                PusernameLIST.close();
                return 1;
            }
            
        }

        PusernameLIST.close();
        return 0;
    }


public:
    PilotLogin() {

        string temp = "";

        
        cin.ignore();
       

        do {
            cout << "Username: ";
            getline(cin, temp);

            if (isUsernameValid(temp)) {
                USERNAME = temp;
            }
            else {
                cout << "Invalid Username. Please try again." << endl << endl;
            }


        }while (!isUsernameValid(temp));

        ifstream passwordExtractor;

        passwordExtractor.open("Credentials_" + USERNAME + ".txt");
        getline(passwordExtractor, PASSWORD);
        passwordExtractor.close();


    }
    bool passwordValidifier() {
        string UserInput;
        cout << "Password: ";
        getline(cin, UserInput);

        if (UserInput == PASSWORD) {
            return 1;
        }
        else {
            return 0;
        }
    }
    string GetUsername() {
        return USERNAME;
    }
};

class EmployeeLogin {
private:
    string USERNAME;
    string PASSWORD;

    bool isUsernameValid(string username) {

        string temp;

        ifstream PusernameLIST;
        PusernameLIST.open("EmployeeUsernameList.txt");

        for (int i = 0; !PusernameLIST.eof();i++) {
            getline(PusernameLIST, temp);
            if (temp == username) {
                PusernameLIST.close();
                return 1;
            }

        }

        PusernameLIST.close();
        return 0;
    }

public:
    EmployeeLogin() {
        string temp = "";

        cin.ignore();
        
        do {
            cout << "Username: ";
            getline(cin, temp);

            if (isUsernameValid(temp)) {
                USERNAME = temp;
            }
            else {
                cout << "Invalid Username. Please try again." << endl << endl;
            }


        } while (!isUsernameValid(temp));

        ifstream passwordExtractor;

        passwordExtractor.open("Credentials_" + USERNAME + ".txt");
        getline(passwordExtractor, PASSWORD);
        passwordExtractor.close();

    }
    bool passwordValidifier() {
        string UserInput;
        cout << "Password: ";
        getline(cin, UserInput);

        if (UserInput == PASSWORD) {
            return 1;
        }
        else {
            return 0;
        }
    }

    string GetUsername() {
        return USERNAME;
    
    }

};

class EmployeeUI {
private:
    string USERNAME;
    int AmountOfUsers;

    bool isFileEmpty(string fileName) {
        ifstream file(fileName);
        file.seekg(0, ios::end); // points to the end of file
        int length = file.tellg(); // returns the end of file's index , if its 0 then the file is empty

        if (length == 0) {
            return 1;
        }
        else {
            return 0;
        }

    }

    void DisplayOptions() {
        ifstream USERDATA_ID;
        ifstream USERDATA_OutAdd;
        ifstream USERNAMELIST;
        ifstream ORDERSTATUSLIST;

        string tempstr = "";
        string customerUsername = "";

        USERNAMELIST.open("UserList.txt");

        cout << endl << endl << "Option\t" << "Name\t\t\t\t" << "Delivery Address\t\t\t\t"<< "Order Status" << endl << endl;


        for (int i = 0; !USERNAMELIST.eof(); i++) {

            getline(USERNAMELIST, customerUsername);

            USERDATA_ID.open("IDlist_" + customerUsername + ".txt");
            USERDATA_OutAdd.open("Outgoing Address_" + customerUsername + ".txt");
            ORDERSTATUSLIST.open("Order Status_" + customerUsername + ".txt");


            if (!isFileEmpty("IDlist_" + customerUsername + ".txt")) {

                for (int j = 0; !USERDATA_ID.eof(); j++) {



                    getline(USERDATA_ID, tempstr, '$');

                    if (tempstr != "") {
                        cout << i + 1 << " - " << j + 1 << "\t";
                        getline(USERDATA_ID, tempstr);


                        cout << tempstr << "\t\t";

                        getline(USERDATA_OutAdd, tempstr, '$');
                        cout << tempstr << ", ";
                        getline(USERDATA_OutAdd, tempstr, '$');
                        cout << tempstr << ", ";
                        getline(USERDATA_OutAdd, tempstr, '$');
                        cout << tempstr << ", ";
                        getline(USERDATA_OutAdd, tempstr);
                        cout << tempstr << ".\t\t\t";

                        getline(ORDERSTATUSLIST, tempstr, '$');

                                                  
                        getline(ORDERSTATUSLIST, tempstr);
                        cout << tempstr;

                        

                        cout << endl;
                    }
                }

                USERDATA_ID.close();
                USERDATA_OutAdd.close();
                ORDERSTATUSLIST.close();
            }
        }
        USERNAMELIST.close();

    }

    void EditMenu() {

        ifstream USERLIST;        
        USERLIST.open("UserList.txt");

        string temp;
        int username_Number;
        string customer_username;
        int packageID;
        string option;
        string ChangeOption;
        string newOrderStatus;

        cout << endl << "Pick Option: ";
        getline(cin, option);
        cout << "1 - Cancelled" << endl;
        cout << "2 - En Route" << endl;
        cout << "3 - Delivered" << endl;

        cout << endl << "Pick Option: ";
        getline(cin,ChangeOption);

        if (ChangeOption == "1") {
            newOrderStatus = "Cancelled";
        }
        else if (ChangeOption == "2") {
            newOrderStatus = "En Route";
        }
        else if (ChangeOption == "3") {
            newOrderStatus = "Delivered";
        }


        for (int i = 0; i < AmountOfUsers; i++) {
            for (int j = 0; j < 100; j++) {
                if ((to_string(i + 1) + " - " + to_string(j + 1)) == option) {
                    username_Number = i + 1;
                    packageID = j + 1;
                }
            }
        }

        for (int i = 0; !USERLIST.eof(); i++) {
            getline(USERLIST, temp);
            if (i == (username_Number - 1)) {
                customer_username = temp;
            }
        }

        ofstream ORDERSTATUS;
        ifstream I_ORDERSTATUS;
        ofstream TEMP;
        ifstream I_TEMP;

        I_ORDERSTATUS.open("Order Status_" + customer_username + ".txt");
        TEMP.open("TEMP.txt");
        for (int i = 0;!I_ORDERSTATUS.eof();i++) {
            getline(I_ORDERSTATUS, temp);
            if (i == packageID - 1) {
                temp = to_string(i + 1) + "$" + newOrderStatus; 
            }
            if (i == 0) {
                TEMP << temp;
            }
            else {
                TEMP << endl << temp;
            }
        }



        ORDERSTATUS.open("Order Status_" + customer_username + ".txt");
        I_TEMP.open("TEMP.txt");

        for (int i = 0;!I_TEMP.eof();i++) {
            getline(I_TEMP, temp);
            if (i == 0) {
                ORDERSTATUS << temp;
            }
            else {
                ORDERSTATUS << endl << temp;
            }
        }
        

        USERLIST.close();
        ORDERSTATUS.close();

    }


public:
    EmployeeUI(string username) {

        USERNAME = username;

        string temp;

        ifstream USERLIST;
        USERLIST.open("UserList.txt");

        AmountOfUsers = 0;
        for (int i = 0; !USERLIST.eof(); i++) {
            getline(USERLIST, temp);
            AmountOfUsers = i + 1;
        }
        USERLIST.close();

    }

    void Menu() {
        bool controller = 1;
        string UserAnswer = "n";
        string MenuNumber = "0";
        while (controller) {

            cout << endl << endl;
            cout << "What would you like to do:" << endl;
            cout << " 1 - Update Package Status" << endl;
            cout << " 2 - Exit" << endl;

            cout << endl << "Enter Number: ";
            getline(cin, MenuNumber);

            if (MenuNumber == "1") {
                DisplayOptions();
                EditMenu();
            }
            else {
                break;
            }


            cout << "Would you like to do something else? (Answer y or n)" << endl;
            getline(cin, UserAnswer);
            if (UserAnswer == "y" || UserAnswer == "Y") {
                controller = 1;
            }
            else {
                controller = 0;
            }

        }

    }
};

class MasterUI {
private:

public:
    MasterUI() {
        int selection = MENU();
        int selection_2;
        
        if (selection == 1) {
            cout << endl << endl;
            cout << "1 - LOGIN"<<endl;
            cout << "2 - NEW USER" << endl;
            cout << "Enter Number: ";
            cin >> selection_2;
            if (selection_2 == 1) {
                UserLogin CurrentUser;
                if (CurrentUser.passwordValidifier()) {
                    UserUI LoggedUser(CurrentUser.GetUsername());
                    LoggedUser.Menu();
                }
                else {
                    cout << "Invalid Password" << endl;
                }
            }
            else if (selection_2 == 2) {
                NewUser RegisteringUser;

            }

        }
        else if (selection == 2) {
            PilotLogin CurrentPilot;
            if (CurrentPilot.passwordValidifier()) {
                PilotUI LoggedPilot(CurrentPilot.GetUsername());
                LoggedPilot.Menu();
            }
            else {
                cout << "Invalid Password" << endl;
            }
        }
        else if (selection == 3) {
            
            EmployeeLogin CurrentEmployee;
            if (CurrentEmployee.passwordValidifier()) {
                EmployeeUI LoggedEmployee(CurrentEmployee.GetUsername());
                LoggedEmployee.Menu();
            }
            else {
                cout << "Invalid Password" << endl;
            }
            
        }

    }

    int MENU() {
        int selection;
        cout << "1 - USER" << endl;
        cout << "2 - Pilot" << endl;
        cout << "3 - Employee" << endl;
        cout << "Enter Number: ";
        cin >> selection;
        return selection;
    }

};





int main()
{
      
    MasterUI newsession;

}