

#include <iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;


string const FileName = "clientsData.txt";

// Structs and enums
enum enOperation
{
    ShowClientListOp = 1,
    AddNewClientOp = 2,
    DeleteClientOp = 3,
    UpdateClientInfoOp=4,
    FindClientOp=5,
    Transactions=6,
    ExitOp=7,

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


//function decleration
void ShowMainMenueScreen();
void PerformMainMenueScreenOp();
void PerformTransactionOp();
vector<stClientInfo> LoadDataFromFile();
string ReadAccountNumber();
bool FindClientByAccountNo(string AccountNo, stClientInfo& client1);
stClientInfo GetClientInfoStruct(string DataLine);
string GetDataLine(stClientInfo client, string Delim = "#//#");


//OUTPUT FUNCTIONS 
void BackToMenue() {
    cout << "Press any key to go back to Menue....";
    system("pause>0");
    ShowMainMenueScreen();
}
void ShowClientListScreen()

{
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
void ShowAddNewClientScreen() {
    cout << "_______________________________\n";
    cout << "\t   Add New Clients Screen \n";
    cout << "_______________________________\n";
}
void ShowDeleteClientScreen() {
    cout << "_______________________________\n";
    cout << "\t  Delete  Client Screen \n";
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
    cout << "\t [7] Exit.\n";
    cout << "================================================\n";
    PerformMainMenueScreenOp();

}
void ShowTransactionMenueScreen() {
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
void BackToTransactionMenue()
{
    cout << "Press any key to go back to Transactions Menue ...";
    system("pause>0");
    ShowTransactionMenueScreen();
}


//
void  FindClientInfo() {
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
vector<string> Split(string DataLine, string Delim="#//#")
{
    int pos;
    vector<string> vData;
    string S1;

    while ((pos = DataLine.find(Delim)) != std::string::npos)
    {
        S1 = DataLine.substr(0, pos);
        if (S1 != " ")
        {
            vData.push_back(S1);
        }
        DataLine.erase(0, pos + Delim.length());


    }
    if (DataLine != " ")
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
            vFileData.push_back(GetClientInfoStruct(DataLine));

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


// READ INPUT FUNCTIONS 
enOperation ReadUserOption()
{
    int c;
    do {
        cout << "Choose what do you want to do ? [1 to 7]? ";
        cin >> c;
        if (c < 1 || c>7)
        {
            cout << "invalid number !";
        }
    } while (c < 1 || c>7);

    return (enOperation)c;
    
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
    getline(cin>>ws, client.PinCode);
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
string GetDataLine(stClientInfo client, string Delim)
{
    string DataLine;
    DataLine = client.AccountNo + Delim + client.PinCode + Delim + client.Name + Delim + client.Phone + Delim + to_string(client.AccountBalance);
    return DataLine;

}


//transcation functionspm
void DepositAmountInClientAcc(string AccountNo,double DepoistAmmount)
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
    else{
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


// Add New Client Functions
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
    ShowAddNewClientScreen();
    char agree = 'n';
    do {
        AddNewClient();
        cout << "Client Added Successfully, do you want to add more clients? Y/N? ";
        cin >> agree;
        
    } while (toupper(agree) == 'Y');
}

// Update Client Information functions
void UpdatClientInfo() {
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

//Delete Client Account
void MarkClientForDeletion(string AccountNo, vector <stClientInfo>&vClientsData) {
  
    for (stClientInfo& client : vClientsData)
    {
        if (client.AccountNo == AccountNo)
        {
            client.MarkForDelete = true;
            return;
        }
    }

}
void DeleteClientAccount() {
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
            MarkClientForDeletion(AccountNo,vClientsData);
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
        case Transactions:
        {
            system("cls");
            ShowTransactionMenueScreen();

        }

        case ExitOp:
        {
            system("cls");
            ShowExitScreen();
            return;
            break;
        }


        }
    }


int main()
{
    ShowMainMenueScreen();
  
}

