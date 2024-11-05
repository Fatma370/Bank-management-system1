# Bank management system
 
This repository contains a C++ console application for managing basic banking operations. The program allows users to perform actions such as viewing client lists, adding and deleting clients, updating client information, searching for clients, and managing transactions. It reads and writes client data from/to a text file, ensuring data persistence across sessions.


## Features

-  Client Management:
View a comprehensive list of clients, including account number, PIN, name, phone, and account balance.
Add new clients, ensuring unique account numbers.
Delete clients, marking accounts for removal from the file.
Update client information (PIN, name, phone, balance).
Transaction Management

- Transactions:
1-Deposit
Allows you to add money to a client’s account. Simply enter the client’s account number and the amount to deposit. The new balance is updated in the data file after the transaction.

2-Withdraw:

Lets you withdraw money from a client’s account, as long as the balance is sufficient. Enter the account number and the amount to withdraw, and the program will update the balance if the transaction is possible.

3-View Total Balances:

Shows a summary of balances across all clients. This includes each account’s balance, along with the total balance for all clients combined.

## Important Note for Custom Data Files

If you wish to run this program with a different data file (other than clientsData.txt) or change the delimiter format, please follow these steps:

- Changing the Data File:

In the source code, locate the line at the top where the FileName constant is defined
```
string const FileName = "clientsData.txt";
```
Modify ```"clientsData.txt"``` to the path and name of your desired file, ensuring it matches the format used by the program.

- Using the Correct Delimiter:
The program reads client data from the file by splitting each line based on a specific delimiter ```(#//#)```, which separates client attributes such as ```AccountNo```, ```PinCode```, ```Name```, ```Phone```, and ```Balance```.


Ensure that the data file you use has client details separated by ```#//#```  
(e.g., ```AccountNo#//#PinCode#//#Name#//#Phone#//#Balance```).

-  If you want to use a different delimiter, you can change the Delim parameter in the code. Locate the following lines:
```
vector<string> Split(string DataLine, string Delim="#//#")
```

and 
```
string GetDataLine(stClientInfo client, string Delim = "#//#");
```
Update``` #//#``` to your preferred delimiter in these functions.

Following these steps allows you to customize the data source and delimiter to suit your own files or formats.


