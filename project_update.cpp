
#include <iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>

using namespace std;




// Structs and enums
enum enOperation
{
    ShowClientListOp = 1,
    AddNewClientOp = 2,
    DeleteClientOp = 3,
    UpdateClientInfoOp = 4,
    FindClientOp = 5,
    TransactionsOP = 6,
    ManageUsersOp = 7,
    LogOut = 8

};
enum enOpreationPermission {
    ShowClientListP = 1,
    AddNewClientP = 2,
    DeleteClientP = 4,
    UpdateClientP = 8,
    FindClient = 16,
    TransactionsP = 32,
    Manage = 64,

};
enum enManageUsersOPeration {
    ListUsersOP = 1,
    AddNewUSerOP,
    DeleteUserOP,
    UpdateUserOP,
    FindUserOP,
    MainMenueOP
};
enum enTransactionsOP {

    DepositeOp = 1,
    WithdrawOp = 2,
    TotalBalancesOp = 3,
    MainMenueOp = 4,

};
struct stClientInfo {
    string AccountNo;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};
struct stUserInfo {
    string USerName;
    string PassWord;
    short permissions;
    bool markforDeletion = 0;

};

string const FileName = "clientsData.txt";
string const UserFileName = "Users.txt";
stUserInfo user;

//function decleration

void ShowMainMenueScreen();
void ShowManageUsersMenueScreen();
vector<stUserInfo> LoadDataFromFileUsers();
void PerformManageUsersMainMenueOp();
void PerformTransactionOp();
vector<stClientInfo> LoadDataFromFile();
string ReadAccountNumber();
bool FindClientByAccountNo(string AccountNo, stClientInfo& client1);
stClientInfo GetClientInfoStruct(string DataLine);
string GetDataLine(stClientInfo client, string Delim = "#//#");
void PerformMainMenueScreenOp();
string ReadUserName();
string ReadPassWord();
bool FindUser(string userName, stUserInfo& user1);
stUserInfo GetUserInfoStruct(string DataLine);
string getUserDataLine(stUserInfo user, string Delim = "#//#");
void login();
bool CheckPermission(enOpreationPermission P);



//OUTPUT FUNCTIONS 
void BackToMenue() {
    cout << "Press any key to go back to Menue....";
    system("pause>0");
    ShowMainMenueScreen();
}
void BackToManageMenue() {
    cout << "Press any key to go back to Menue....";
    system("pause>0");
    ShowManageUsersMenueScreen();

}
void ShowAccessDeniedScreen() {
    system("cls");
    cout << "_________________________________________________\n";
    cout << "Access Denied, \n You dont Have Permission T Do this , \n Please Contact Your Admin\n";
    cout << "_________________________________________________\n";

}
void ShowLoginScreen() {
    cout << "_______________________________\n";
    cout << "\t  Login Screen \n";
    cout << "_______________________________\n";
}
void ShowClientListScreen()

{
    if (!CheckPermission(enOpreationPermission::ShowClientListP))
    {
        ShowAccessDeniedScreen();
        return;

    }
    vector<stClientInfo>vClientsData = LoadDataFromFile();

    cout << "\n \t \t\t\t          Client List(" << vClientsData.size() << ") Client(s).\n";
    cout << "____________________________________________________________________________________________________________________\n";
    cout << "|" << left << setw(20) << "Account Number";
    cout << "|" << left << setw(20) << "PinCode";
    cout << "|" << left << setw(40) << "Client Name";
    cout << "|" << left << setw(20) << "Phone";
    cout << "|" << left << setw(20) << "Balance" << endl;
    cout << "____________________________________________________________________________________________________________________\n";

    for (stClientInfo& client : vClientsData)
    {
        cout << "|" << setw(20) << left << client.AccountNo;
        cout << "|" << setw(20) << left << client.PinCode;
        cout << "|" << setw(40) << left << client.Name;
        cout << "|" << setw(20) << left << client.Phone;
        cout << "|" << setw(20) << left << client.AccountBalance << endl;

    }
    cout << "____________________________________________________________________________________________________________________\n";

}
void ShowUsersListScreen() {
    vector<stUserInfo> vUsers = LoadDataFromFileUsers();
    cout << "\n \t \t\t\t         Users List(" << vUsers.size() << ") User(s).\n";
    cout << "________________________________________________________________________\n\n";
    cout << "|" << left << setw(20) << "User Name";
    cout << "|" << left << setw(20) << "PassWord";
    cout << "|" << left << setw(20) << "Permissions";
    cout << "_________________________________________________________________________\n";
    for (stUserInfo user : vUsers)
    {
        cout << "|" << setw(20) << left << user.USerName;
        cout << "|" << setw(20) << left << user.PassWord;
        cout << "|" << setw(20) << left << user.permissions;
        cout << endl;

    }
    cout << "____________________________________________________________________________________________________________________\n";



}
void ShowAddNewClientScreen() {
    cout << "_______________________________\n";
    cout << "\t   Add New Clients Screen \n";
    cout << "_______________________________\n";
}
void ShowAddNewUserScreen() {
    cout << "_______________________________\n";
    cout << "\t   Add New User Screen \n";
    cout << "_______________________________\n";
}

void ShowDeleteClientScreen() {
    cout << "_______________________________\n";
    cout << "\t  Delete  Client Screen \n";
    cout << "_______________________________\n";
}
void ShowDeletetUserScreen() {
    cout << "_______________________________\n";
    cout << "\t  Delete  User Screen \n";
    cout << "_______________________________\n";
}
void ShowUpdateClientInfoScreen() {
    cout << "_______________________________\n";
    cout << "\t  Update  Client Screen \n";
    cout << "_______________________________\n";
}
void ShowExitScreen() {
    cout << "_______________________________\n";
    cout << "\t  Program ends ;-) \n";
    cout << "_______________________________\n";
}
void ShowFindClientScree() {
    cout << "_______________________________\n";
    cout << "\t Find Client Screen \n";
    cout << "_______________________________\n";
}
void ShowFindUserScreen() {
    cout << "_______________________________\n";
    cout << "\t Find User Screen \n";
    cout << "_______________________________\n";
}

void ShowMainMenueScreen()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t          Main Menuse Screen \t\n";
    cout << "================================================\n";
    cout << "\t [1] Show Client List.\n";
    cout << "\t [2] Add New Client.\n";
    cout << "\t [3] Delete Client.\n";
    cout << "\t [4] Update Client Information.\n";
    cout << "\t [5] Find Client.\n";
    cout << "\t [6] Transactions.\n";
    cout << "\t [7] Manage Users.\n";
    cout << "\t [8] LogOut.\n";
    cout << "================================================\n";
    PerformMainMenueScreenOp();

}
void ShowTransactionMenueScreen() {

    if (!CheckPermission(enOpreationPermission::TransactionsP))
    {
        ShowAccessDeniedScreen();
        return;

    }
    system("cls");
    cout << "\n=========================================\n";
    cout << "\t Transactions Menue Screen\n";
    cout << "\n=========================================\n";
    cout << "\t [1] Deposit.\n";
    cout << "\t [2] Withdraw.\n";
    cout << "\t [3] Total Balances.\n";
    cout << "\t [4] Main Menue.\n";
    cout << "\n=========================================\n";
    PerformTransactionOp();
}
void ShowDepositScreen()
{
    cout << "_______________________________\n";
    cout << "\t  Deposit Screen \n";
    cout << "_______________________________\n";

}
void ShowWithdrawScreen() {
    cout << "_______________________________\n";
    cout << "\t  Withdraw Screen \n";
    cout << "_______________________________\n";
}
void ShowTotalBalncesScreen() {
    vector<stClientInfo>vClientsData = LoadDataFromFile();

    cout << "\n \t \t\t\t         Balances List(" << vClientsData.size() << ") Client(s).\n";
    cout << "____________________________________________________________________________________________________________________\n";
    cout << "|" << left << setw(20) << "Account Number";
    cout << "|" << left << setw(40) << "Client Name";
    cout << "|" << left << setw(20) << "Balance" << endl;
    cout << "____________________________________________________________________________________________________________________\n";
    double SumOfBalnaces = 0;

    for (stClientInfo& client : vClientsData) {

        cout << "|" << setw(20) << left << client.AccountNo;
        cout << "|" << setw(40) << left << client.Name;
        cout << "|" << setw(20) << left << client.AccountBalance << endl;
        SumOfBalnaces += client.AccountBalance;


    }
    cout << "____________________________________________________________________________________________________________________\n";
    cout << "\t\t\t\t Total Balances =" << SumOfBalnaces << endl;



}
void PrintClientInfoCard(stClientInfo client) {
    cout << "The following are client details: \n";
    cout << "______________________________\n";
    cout << "Account Number: " << client.AccountNo << endl;
    cout << "Pin Code: " << client.PinCode << endl;
    cout << " Name : " << client.Name << endl;
    cout << "Phone : " << client.Phone << endl;
    cout << "Account Balance : " << client.AccountBalance << endl;
    cout << "______________________________\n";


}
void PrintUserINfoCard(stUserInfo user) {
    cout << "The following are User details: \n";
    cout << "______________________________\n";
    cout << "User Name: " << user.USerName << endl;
    cout << "Pass word : " << user.PassWord << endl;
    cout << "permissions: " << user.permissions << endl;
    cout << "______________________________\n";


}
void BackToTransactionMenue()
{
    cout << "Press any key to go back to Transactions Menue ...";
    system("pause>0");
    ShowTransactionMenueScreen();
}
void ShowManageUsersMenueScreen() {

    system("cls");
    if (!CheckPermission(enOpreationPermission::Manage))
    {
        ShowAccessDeniedScreen();
        return;

    }

    cout << "================================================\n";
    cout << "\t         Manage Users Menuse Screen \t\n";
    cout << "================================================\n";
    cout << "\t [1] List Users.\n";
    cout << "\t [2] Add New User.\n";
    cout << "\t [3] Delete User.\n";
    cout << "\t [4] Update User Information.\n";
    cout << "\t [5] Find User.\n";
    cout << "\t [6] Main Menue.\n";
    cout << "================================================\n";
    PerformManageUsersMainMenueOp();
}

//
void  FindClientInfo() {
    if (!CheckPermission(enOpreationPermission::FindClient))
    {
        ShowAccessDeniedScreen();
        return;

    }
    ShowFindClientScree();
    string AccountNo = ReadAccountNumber();
    stClientInfo client;
    if (FindClientByAccountNo(AccountNo, client))
    {
        PrintClientInfoCard(client);

    }
    else {
        cout << "Client with Account Number [" << AccountNo << "] Not Found!! \n";

    }
}
void FindUSerINFo()
{
    ShowFindUserScreen();
    string userNAme = ReadUserName();
    stUserInfo user;
    if (FindUser(userNAme, user))
    {
        PrintUserINfoCard(user);

    }
    else {
        cout << "User with user name [" << userNAme << "] NOT FOUND!!\n";
    }

}
vector<string> Split(string DataLine, string Delim = "#//#")
{
    int pos;
    vector<string> vData;
    string S1;

    while ((pos = DataLine.find(Delim)) != std::string::npos)
    {
        S1 = DataLine.substr(0, pos);
        if (S1 != "")
        {
            vData.push_back(S1);
        }
        DataLine.erase(0, pos + Delim.length());


    }
    if (DataLine != "")
    {
        vData.push_back(DataLine);
    }
    return vData;
}
bool checkIfAccountNumberExist(string AccountNumber) {
    vector<stClientInfo>vclientsData = LoadDataFromFile();
    for (stClientInfo& client : vclientsData)
    {
        if (AccountNumber == client.AccountNo)
        {
            return true;
        }

    }
    return false;
}
bool FindClientByAccountNo(string AccountNo, stClientInfo& client1) {
    vector<stClientInfo>vClientsData = LoadDataFromFile();
    for (stClientInfo& client : vClientsData)
    {
        if (client.AccountNo == AccountNo)
        {
            client1 = client;
            return 1;
        }
    }
    return 0;
}
bool FindUser(string userName, stUserInfo& user1)
{

    vector<stUserInfo> vUsers = LoadDataFromFileUsers();
    for (stUserInfo user : vUsers)
    {
        if (user.USerName == userName)
        {
            user1 = user;
            return true;
        }
    }
    return false;

}
bool isUserNameExist(string UserName) {
    vector<stUserInfo> vUsers = LoadDataFromFileUsers();
    for (stUserInfo user : vUsers)
    {
        if (user.USerName == UserName)
        {
            return true;
        }
    }
    return false;


}


// Data Exchange between file and vector
vector<stClientInfo> LoadDataFromFile()
{
    vector<stClientInfo>vFileData;
    fstream file;
    file.open(FileName, ios::in);
    if (file.is_open())
    {
        string DataLine;
        while (getline(file, DataLine))
        {
            if (DataLine.empty())
            {
                continue;
            }
            vFileData.push_back(GetClientInfoStruct(DataLine));

        }
        file.close();
    }
    return vFileData;
}
vector<stUserInfo> LoadDataFromFileUsers()
{
    vector<stUserInfo>vFileData;
    fstream file;
    file.open("Users.txt", ios::in);
    if (file.is_open())
    {
        string DataLine;
        while (getline(file, DataLine))

        {
            if (DataLine.empty())
            {
                continue;
            }
            vFileData.push_back(GetUserInfoStruct(DataLine));

        }
        file.close();
    }
    return vFileData;
}
void LoadDataFromVectorToFile(vector<stClientInfo>vClientsData)
{
    fstream file;
    file.open(FileName, ios::out);
    if (file.is_open())
    {
        for (stClientInfo& client : vClientsData)
        {
            if (client.MarkForDelete == false) {
                file << GetDataLine(client) << endl;
            }

        }
        file.close();
    }

}
void LoadDataFromVectorUser(vector<stUserInfo>vUsers)
{
    fstream file;
    file.open("Users.txt", ios::out);
    if (file.is_open())
    {
        for (stUserInfo& user1 : vUsers)
        {
            if (user.markforDeletion == false) {
                file << getUserDataLine(user1) << endl;
            }

        }
        file.close();
    }
}


// READ INPUT FUNCTIONS 
enOperation ReadUserOption()
{
    int c;
    do {
        cout << "Choose what do you want to do ? [1 to 8]? ";
        cin >> c;
        if (c < 1 || c>8)
        {
            cout << "invalid number !";
        }
    } while (c < 1 || c>8);

    return (enOperation)c;

}
enManageUsersOPeration ReadUserManageOPtion() {
    int c;
    do {
        cout << "Choose what do you want to do ? [1 to 7]? ";
        cin >> c;
        if (c < 1 || c>6)
        {
            cout << "invalid number !";
        }
    } while (c < 1 || c>6);

    return (enManageUsersOPeration)c;

}
stClientInfo ReadClientInfo() {
    stClientInfo client;
    cout << "\nEnter Account Number? ";
    getline(cin >> ws, client.AccountNo);
    while (checkIfAccountNumberExist(client.AccountNo)) {
        cout << "Client With Account Number [" << client.AccountNo << "] Already exists , Enter another Account Number? ";
        getline(cin >> ws, client.AccountNo);
    }
    cout << "Please enter PinCode? ";
    getline(cin, client.PinCode);
    cout << "Please enter Name? ";
    getline(cin, client.Name);
    cout << "Please enter Phone Number? ";
    getline(cin, client.Phone);
    cout << "Please enter balance ? ";
    cin >> client.AccountBalance;
    return client;
}
int ReadChoice(string message)
{
    char agree;
    cout << message;
    cin >> agree;
    if (tolower(agree) == 'y')
        return 1;
    else
        return 0;
}
short ReadPermission() {
    int access = 0;
    if (ReadChoice("Do You Want to give full access? y/n? "))
        return -1;

    else {
        cout << "Do you want to give access to : ";
        access += 1 * ReadChoice("Show Client list? y/n? ");
        access += 2 * ReadChoice("Add new client ? y/n? ");
        access += 4 * ReadChoice("Delete client ? y/n? ");
        access += 8 * ReadChoice("update client ? y/n? ");
        access += 16 * ReadChoice("find  client ? y/n? ");
        access += 32 * ReadChoice("transactions  ? y/n? ");
        access += 64 * ReadChoice("Manage Users ? y/n? ");

    }
    return access;


}
stUserInfo readUSerINfo() {
    stUserInfo user;
    user.USerName = ReadUserName();
    while (isUserNameExist(user.USerName)) {
        cout << "this user name already exist , Enter another User name? \n";
        user.USerName = ReadUserName();
    }
    user.PassWord = ReadPassWord();
    user.permissions = ReadPermission();
    return user;


}

string ReadAccountNumber() {
    string AccountNo;
    cout << "Please enter account Number? ";
    cin >> AccountNo;
    return AccountNo;
}
stClientInfo ReadUpdatedClientInfo(string AccountNo) {
    stClientInfo client;
    client.AccountNo = AccountNo;
    cout << "Please enter PinCode? ";
    getline(cin >> ws, client.PinCode);
    cout << "Please enter Name? ";
    getline(cin, client.Name);
    cout << "Please enter Phone Number? ";
    getline(cin, client.Phone);
    cout << "Please enter balance ? ";
    cin >> client.AccountBalance;
    return client;


}
enTransactionsOP ReadUserTranscationOP()
{
    short c;
    cout << "Choose what do you want to do? [1 to 4]?? ";
    cin >> c;
    return (enTransactionsOP)c;
}
double ReadNumber(string Message)
{
    double num;
    cout << Message;
    cin >> num;
    return num;
}
string ReadUserName() {
    string UserName;
    cout << "Please enter userName? ";
    cin >> UserName;
    return UserName;
}
string ReadPassWord() {
    string PassWord;
    cout << "Please enter your password? ";
    getline(cin >> ws, PassWord);
    return PassWord;
}

//Get Functions
stClientInfo GetClientInfoStruct(string DataLine) {
    vector<string>vClientData = Split(DataLine);
    stClientInfo client;
    client.AccountNo = vClientData[0];
    client.PinCode = vClientData[1];
    client.Name = vClientData[2];
    client.Phone = vClientData[3];
    client.AccountBalance = stod(vClientData[4]);
    return client;

}
stUserInfo GetUserInfoStruct(string DataLine)
{
    vector<string>vUsersData = Split(DataLine);
    stUserInfo user;
    user.USerName = vUsersData[0];
    user.PassWord = vUsersData[1];
    user.permissions = stoi(vUsersData[2]);
    return user;

}
string GetDataLine(stClientInfo client, string Delim)
{
    string DataLine;
    DataLine = client.AccountNo + Delim + client.PinCode + Delim + client.Name + Delim + client.Phone + Delim + to_string(client.AccountBalance);
    return DataLine;

}
string getUserDataLine(stUserInfo user, string Delim)
{
    string dataLine;
    dataLine = user.USerName + Delim + user.PassWord + Delim + to_string(user.permissions);
    return dataLine;
}


//transcation functionspm
void DepositAmountInClientAcc(string AccountNo, double DepoistAmmount)
{
    vector<stClientInfo>vClientsData = LoadDataFromFile();
    for (stClientInfo& client : vClientsData)
    {
        if (client.AccountNo == AccountNo)
        {
            char agree = 'n';
            cout << "Are You sure you want to perform this transaction? y/n?";
            cin >> agree;
            if (toupper(agree) == 'Y')
            {
                client.AccountBalance += DepoistAmmount;
                cout << "Done Successfully , new balance is :" << client.AccountBalance << endl;
                LoadDataFromVectorToFile(vClientsData);
                return;
            }
            else {
                cout << "transaction Process is cancelled!!";
            }

        }
    }
}
void Deposit()
{
    ShowDepositScreen();
    string AccountNo = ReadAccountNumber();
    stClientInfo client;
    if (FindClientByAccountNo(AccountNo, client))
    {
        PrintClientInfoCard(client);
        double DepositAmount = ReadNumber("Please enter deposit amount? ");
        DepositAmountInClientAcc(AccountNo, DepositAmount);
    }
    else {
        cout << "Client with Account Number [" << AccountNo << "] Not Found!!\n";

    }

}
void WithdrawAmountFromClientAccount(string AccountNo, double WithdrawAmmount)
{
    vector<stClientInfo>vClientsData = LoadDataFromFile();

    for (stClientInfo& client : vClientsData)
    {
        if (client.AccountNo == AccountNo)
        {
            while (client.AccountBalance < WithdrawAmmount)
            {
                cout << "Amount Excceds the balnance, you can withdraw up to :" << client.AccountBalance << endl;
                cout << "Please enter another amount? ";
                cin >> WithdrawAmmount;
            }
            DepositAmountInClientAcc(AccountNo, WithdrawAmmount * -1);
            return;
        }

    }
}
void Withdraw() {

    ShowWithdrawScreen();
    string AccountNo = ReadAccountNumber();
    stClientInfo client;
    if (FindClientByAccountNo(AccountNo, client))
    {
        PrintClientInfoCard(client);
        double WithdrawAmount = ReadNumber("Please enter Withdraw amount? ");
        WithdrawAmountFromClientAccount(AccountNo, WithdrawAmount);

    }
    else {
        cout << "Client with Account Number [" << AccountNo << "] Not Found!!\n";

    }
}
void PerformTransactionOp()
{
    enTransactionsOP UserOp = ReadUserTranscationOP();

    switch (UserOp)
    {
    case DepositeOp:
    {
        system("cls");
        Deposit();
        BackToTransactionMenue();

        break;
    }
    case WithdrawOp:
    {
        system("cls");
        Withdraw();
        BackToTransactionMenue();

        break;
    }
    case TotalBalancesOp:
    {
        system("cls");
        ShowTotalBalncesScreen();
        BackToTransactionMenue();
        break;
    }
    case MainMenueOp:
    {
        system("cls");
        ShowMainMenueScreen();
        break;
    }


    }
}


// Add New Client/User Functions
void AddNewClient() {


    fstream file;
    file.open(FileName, ios::app);
    if (file.is_open())
    {
        file << GetDataLine(ReadClientInfo()) << endl;
        file.close();
    }


}
void AddNewClients()
{
    if (!CheckPermission(enOpreationPermission::AddNewClientP))
    {
        ShowAccessDeniedScreen();
        return;

    }
    ShowAddNewClientScreen();
    char agree = 'n';
    do {
        AddNewClient();
        cout << "Client Added Successfully, do you want to add more clients? Y/N? ";
        cin >> agree;

    } while (toupper(agree) == 'Y');
}
void AddNewUser() {

    fstream file;
    file.open("Users.txt", ios::app);
    if (file.is_open())
    {
        file << getUserDataLine(readUSerINfo()) << endl;
        file.close();
    }



}
void AddNewUsers() {
    ShowAddNewUserScreen();
    char agree = 'n';
    do {
        AddNewUser();
        cout << "User Added Successfully, do you want to add more Users? Y/N? ";
        cin >> agree;

    } while (toupper(agree) == 'Y');

}



// Update Client Information functions
void UpdatClientInfo() {
    if (!CheckPermission(enOpreationPermission::UpdateClientP))
    {
        ShowAccessDeniedScreen();
        return;

    }
    ShowUpdateClientInfoScreen();
    string AccountNo = ReadAccountNumber();
    stClientInfo client;
    if (FindClientByAccountNo(AccountNo, client))
    {
        PrintClientInfoCard(client);
        char agree = 'n';
        cout << "Are you sure you want to update this client information??  Y/N?? ";
        cin >> agree;
        if (toupper(agree) == 'Y')
        {
            vector <stClientInfo>vClientsData = LoadDataFromFile();
            for (stClientInfo& client : vClientsData)
            {
                if (client.AccountNo == AccountNo)
                {
                    client = ReadUpdatedClientInfo(AccountNo);
                    LoadDataFromVectorToFile(vClientsData);
                    break;
                }
            }
            cout << "Client information is updated successfully! \n";


        }
        else {
            cout << "Updating Client inforamtion is cancelled! \n";
        }
    }
    else {
        cout << "Client with Account number [" << AccountNo << "] Not Found!!\n";
    }
}

//Delete Client/ser Account
void MarkClientForDeletion(string AccountNo, vector <stClientInfo>& vClientsData) {

    for (stClientInfo& client : vClientsData)
    {
        if (client.AccountNo == AccountNo)
        {
            client.MarkForDelete = true;
            return;
        }
    }

}
void MarkUserFordeletion(string UserName, vector<stUserInfo>& vUsers)
{
    for (stUserInfo& user : vUsers)
    {
        if (user.USerName == UserName)
        {
            user.markforDeletion = true;
            return;

        }
    }
}
void DeleteClientAccount() {
    if (!CheckPermission(enOpreationPermission::DeleteClientP))
    {
        ShowAccessDeniedScreen();
        return;

    }
    ShowDeleteClientScreen();

    string AccountNo = ReadAccountNumber();
    stClientInfo client;
    if (FindClientByAccountNo(AccountNo, client))
    {
        PrintClientInfoCard(client);
        char agree = 'n';
        cout << "Are YOu Sure You Want To Delete this client ?? Y/N??";
        cin >> agree;
        if (toupper(agree) == 'Y')
        {
            vector <stClientInfo>vClientsData = LoadDataFromFile();
            MarkClientForDeletion(AccountNo, vClientsData);
            LoadDataFromVectorToFile(vClientsData);
            cout << "client is deleted successfully !!\n";

        }
        else {
            cout << "Deleting Client is Cancelled!!\n ";
        }

    }
    else {
        cout << "Client with Account Number (" << AccountNo << ") is NOT FOUND !!\n";
    }


}
void DeleteUser() {

    ShowDeletetUserScreen();
    string userName = ReadUserName();
    stUserInfo user;
    if (userName == "Admin")
    {
        cout << "This user cannot be Deleted!!\n";
        return;
    }
    if (FindUser(userName, user))
    {
        PrintUserINfoCard(user);
        char agree = 'n';
        cout << "Are you sure you want to delete this user? Y/N? ";
        cin >> agree;
        if (toupper(agree) == 'Y')
        {
            vector<stUserInfo> vUsers = LoadDataFromFileUsers();
            MarkUserFordeletion(userName, vUsers);
            LoadDataFromVectorUser(vUsers);
            cout << "User is deleted successfully !!\n";
        }
        else {
            cout << "Deleting User is Cancelled!! \n";
        }
    }
    else {
        cout << "User with user name [" << userName << "] NOT FOUND!!\n";

    }



}


bool CheckPermission(enOpreationPermission P)
{
    if (user.permissions == -1)
    {
        return true;
    }
    else if ((user.permissions & P) == P)
    {
        return true;
    }
    else
        return false;
}
//
void PerformMainMenueScreenOp() {
    enOperation UserOP = ReadUserOption();

    switch (UserOP)
    {
    case ShowClientListOp:
    {
        system("cls");
        ShowClientListScreen();
        BackToMenue();
        break;
    }
    case AddNewClientOp:
    {

        system("cls");
        AddNewClients();
        BackToMenue();
        break;
    }
    case DeleteClientOp:
    {
        system("cls");
        DeleteClientAccount();
        BackToMenue();
        break;
    }
    case UpdateClientInfoOp:
    {
        system("cls");
        UpdatClientInfo();
        BackToMenue();

        break;
    }

    case FindClientOp:
    {
        system("cls");
        FindClientInfo();
        BackToMenue();
        break;
    }
    case TransactionsOP:
    {
        system("cls");
        ShowTransactionMenueScreen();
        BackToMenue();
        break;
    }
    case ManageUsersOp:
    {
        system("cls");
        ShowManageUsersMenueScreen();
        BackToMenue();
        break;

    }

    case LogOut:
    {
        system("cls");
        login();
        return;
        break;
    }


    }
}
void PerformManageUsersMainMenueOp() {
    enManageUsersOPeration UserOP = ReadUserManageOPtion();
    switch (UserOP)
    {
    case ListUsersOP:
    {
        system("cls");
        ShowUsersListScreen();
        BackToManageMenue();
    }
    case AddNewUSerOP:
    {
        system("cls");
        AddNewUsers();
        BackToManageMenue();

    }
    case DeleteUserOP:
    {
        system("cls");
        DeleteUser();
        BackToManageMenue();

    }
    case FindUserOP:
    {
        system("cls");
        FindUSerINFo();
        BackToManageMenue();

    }
    case MainMenueOP: {
        system("cls");
        ShowMainMenueScreen();

    }


    }
}
bool isPassWordCorrect(string UserName, string PassWord) {
    vector<stUserInfo>vUsers = LoadDataFromFileUsers();
    for (stUserInfo user : vUsers)
    {
        if (user.USerName == UserName)
        {
            if (user.PassWord == PassWord)
            {
                return 1;
            }
            else {
                return 0;
            }
        }

    }
    return 0;

}


void login() {
    string UserName;
    string PassWord;
    bool invalid = 0;
    do {
        invalid = 0;
        UserName = ReadUserName();
        PassWord = ReadPassWord();
        if (!(isUserNameExist(UserName)) || !(isPassWordCorrect(UserName, PassWord)))
        {
            invalid = 1;
            cout << "Invalis Username/PassWord!\n";

        }

    } while (invalid);

    FindUser(UserName, user);

    ShowMainMenueScreen();


}


int main()
{
    login();

}

