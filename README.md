# Bank Management System

## Overview
The **Bank Management System** is a comprehensive software solution designed to manage banking operations, user accounts, and client transactions efficiently. Built using C++, the system includes a variety of features such as managing clients, transactions, user roles, and more, all encapsulated within a modular and extendable codebase.

---

## Features

### Clients Management
- **Add New Client**: Add a new client to the system with details such as name, email, phone, and account balance.
- **Update Client**: Modify existing client information.
- **Delete Client**: Remove clients from the system.
- **View Client List**: Display all registered clients with their details.
- **Find Client**: Search for a specific client by their account number.

### Transactions
- **Deposit Funds**: Deposit money into a client account.
- **Withdraw Funds**: Withdraw money from a client account, ensuring sufficient balance.
- **Transfer Funds**: Transfer money between client accounts.
- **Transaction Log**: View a log of all transfers, including details such as sender, receiver, amount, and date.
- **View Total Balances**: Display the total balance across all client accounts.

### User Management
- **Add New User**: Register new system users with specific roles and permissions.
- **Update User**: Edit details of existing users.
- **Delete User**: Remove users from the system.
- **View User List**: Display all users with their respective roles and permissions.
- **Login Register**: Monitor user login activities and permissions.

---

## Classes and Their Responsibilities

### Core Classes
- **clsBankClient**: Manages client details, including account number, PIN code, and balance. Handles client-related operations such as adding, updating, and deleting clients.
- **clsUser**: Manages system users and their permissions, login activities, and authentication.
- **clsScreen**: Base class providing shared functionalities for different screen types.

### Screens
- **clsMainMenuScreen**: The main interface for accessing various features of the system.
- **clsTransactionMenuScreen**: Handles transaction-related functionalities, including deposits, withdrawals, and transfers.
- **clsClientListScreen**: Displays a list of all clients.
- **clsAddNewClientScreen**: Manages the addition of new clients.
- **clsDeleteClientScreen**: Handles client deletion.
- **clsUpdateClientScreen**: Allows updating of client information.
- **clsFindClientScreen**: Enables searching for a client by account number.
- **clsManageUsersScreen**: Provides functionalities for managing system users.
- **clsDepositScreen**: Manages deposit operations.
- **clsWithdrawScreen**: Handles withdrawal transactions.
- **clsTransferScreen**: Manages fund transfers between accounts.
- **clsTransferRegisterScreen**: Displays a detailed log of all fund transfers.

### Utility Classes
- **clsInputRead**: Provides methods for reading and validating user inputs.
- **clsInputValidate**: Contains validation logic for user inputs, such as name, email, phone number, and PIN code.
- **clsString**: Offers string manipulation utilities, such as case conversion, trimming, and splitting.
- **clsUtil**: Includes helper methods for mathematical calculations, text conversions, and date utilities.

---

## Technical Details

### File Management
- **Clients.txt**: Stores client information persistently.
- **TransferLog.txt**: Logs all transfer transactions.

### Enumerations
- **clsBankClient::enSaveResults**: Defines the results of save operations (e.g., succeeded, failed due to empty object, failed due to duplicate account).
- **clsUtil::enPrimeOrNotPrime**: Determines if a number is prime.
- **clsUtil::enCharacterType**: Specifies types of characters for generating random strings.

### Features Breakdown

#### Client Operations
- `clsBankClient::AddNewClient`: Creates a new client with initial balance.
- `clsBankClient::UpdateClient`: Updates client details such as email and phone.
- `clsBankClient::DeleteClient`: Flags a client for deletion and removes them from persistent storage.

#### Transaction Operations
- `clsBankClient::Deposit`: Increases the account balance by a specified amount.
- `clsBankClient::Withdraw`: Decreases the account balance, ensuring sufficient funds are available.
- `clsBankClient::Transfer`: Transfers a specified amount to another client account and logs the transaction.

#### User Operations
- `clsUser::AddNewUser`: Registers a new system user with permissions.
- `clsUser::UpdateUser`: Edits user information.
- `clsUser::DeleteUser`: Removes a user from the system.
- `clsUser::Login`: Authenticates a user based on username and password.