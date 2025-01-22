# Bank Client Management System

The Bank Client Management System is a C++ application designed to manage bank clients, their accounts, transactions, and user permissions. It provides functionalities such as client registration, account updates, deposits, withdrawals, fund transfers, and user authentication with role-based access control.

## Features
### Main Menue Screen (clsMainMenueScreen)
 - **List Clients**
 - **Add New Client**
 - **Delete Client**
 - **Update Client Information**
 - **Find Client**
 - **Transactions**
 - **Manage Users**
 - **Login/Register**
 - **Logout**

### Client Management
- **Add new clients**: Create new client profiles with details such as first name, last name, email, phone, account number, PIN code, and balance.
- **Update client details**: Modify client information (e.g., name, email, phone, PIN code, account balance).
- **Delete clients**: Remove clients from the system after confirmation.
- **Search for clients**: Find clients by account number or PIN code.
- **View client list**: Display a formatted list of all clients in the system.

### Account Operations
- **Deposit funds**: Add funds to a client's account.
- **Withdraw funds**: Deduct funds from a client's account (if sufficient balance is available).
- **Transfer funds**: Move funds between two accounts.
- **View total balances**: Display the total balance of all clients in the system.

### Transaction Logging
- **Transfer logs**: Maintain a log of all fund transfers, including sender, receiver, amount, and timestamps.

### User Management (clsUser)
- **User authentication**: Log in with a username and password.
- **Role-based permissions**: Assign permissions to users (e.g., manage clients, view logs, perform transactions).
- **User registration**: Add new users with specific permissions.
- **Login logs**: Track user login activity with timestamps.

### Add New Client Screen (clsAddNewClientScreen)
- **Input validation**: Validate user input for fields such as name, email, phone, PIN code, and account balance.
- **Add new client**: Save new client details to the system after validation.
- **Duplicate account check**: Ensure that the account number is unique.

### Client List Screen (clsClientListScreen)
- **View client list**: Display a formatted table of all clients in the system.
- **Access control**: Only users with the `pListClients` permission can view the client list.

### Delete Client Screen (clsDeleteClientScreen)
- **Delete clients**: Remove a client from the system after confirming the action.
- **Access control**: Only users with the `pDeleteClient` permission can delete clients.
- **Client details**: Display the client's details before deletion for confirmation.

### Find Client Screen (clsFindClientScreen)
- **Search for clients**: Find a client by their account number.
- **Display client details**: Show the client's full details, including name, email, phone, account number, PIN code, and balance.
- **Access control**: Only users with the `pFindClient` permission can access this screen.
- **User validation**: Ensure the username exists before displaying the user's information.
- **Error handling**: Catch any errors during the search and display an appropriate message.

### Update Client Screen (clsUpdateClientScreen)
- **Update client details**: Modify a client's information, including name, email, phone, PIN code, and account balance.
- **Input validation**: Validate user input for fields such as name, email, phone, PIN code, and account balance.
- **Access control**: Only users with the `pUpdateClient` permission can access this screen.

### Transaction Menu Screen (clsTransactionMenueScreen)
- **Deposit funds**: Add funds to a client's account.
- **Withdraw funds**: Deduct funds from a client's account (if sufficient balance is available).
- **Transfer funds**: Move funds between two accounts.
- **View transfer logs**: Display a log of all fund transfers.
- **View total balances**: Display the total balance of all clients in the system.
- **Access control**: Only users with the `pTransactions` permission can access this screen.

### Deposit Screen (clsDepositScreen)
- **Deposit funds**: Add funds to a client's account.
- **Client details**: Display the client's details before and after the deposit.
- **Confirmation**: Confirm the deposit transaction before proceeding.
- **Access control**: Only users with the `pTransactions` permission can access this screen.

### Withdraw Screen (clsWithdrawScreen)
- **Withdraw funds**: Deduct funds from a client's account (if sufficient balance is available).
- **Client details**: Display the client's details before and after the withdrawal.
- **Confirmation**: Confirm the withdrawal transaction before proceeding.
- **Access control**: Only users with the `pTransactions` permission can access this screen.

### Transfer Screen (clsTransferScreen)
- **Transfer funds**: Move funds between two client accounts.
- **Client details**: Display the details of both the sender and receiver before and after the transfer.
- **Confirmation**: Confirm the transfer transaction before proceeding.
- **Access control**: Only users with the `pTransactions` permission can access this screen.

### Transfer Register Screen (clsTransferRegisterScreen)
- **View transfer logs**: Display a log of all fund transfers, including sender, receiver, amount, and timestamps.
- **Access control**: Only users with the `pTransferRegister` permission can access this screen.

### Total Balances Screen (clsTotalBalanccesScreen)
- **View total balances**: Display a formatted table of all clients' balances and the total balance of the system.
- **Access control**: Only users with the `pTransactions` permission can access this screen.

### Login Screen (clsLoginScreen)
- **User authentication**: Log in with a username and password.
- **Failed login attempts**: Limit the number of failed login attempts to 3 before locking the user out.
- **Access control**: Redirects authenticated users to the main menu.
- **Login error handling**: If a user enters an incorrect username or password, they are allowed 3 trials before being locked out.

### Manage Users Screen (clsManageUsersScreen)
- **Manage users**: Perform operations such as listing, adding, deleting, updating, and finding users.
- **Access control**: Only users with the `pManageUser` permission can access this screen.

### Person Management (clsPerson)
- **Store personal details**: Manage first name, last name, email, and phone number.
- **Communication methods**: Send emails, faxes, and SMS (currently placeholders for future implementation).
- **Full name retrieval**: Get the full name of a person by combining first and last names.

### Add New User Screen (clsAddNewUserScreen)
- **User Registration**: Add new users to the system with a unique username.
- **Permission Assignment**: Assign role-based permissions (e.g., view clients, add clients, delete clients).
- **Input validation**: Ensure valid input for user details such as name, email, phone, and password.
- **User information display**: Show user details after successful creation.

### Increase Client Balance (clsIncrease)
- **Increase balance**: Modify the balance of a client's account by adding a specified amount.
- **Access control**: Only users with the `pIncreaseBalance` permission can access this screen.
- **Confirmation**: Confirm the increase in balance transaction before proceeding.

### Find User Screen (clsFindUserScreen)
- **Search for users**: Find a user by their username.
- **Display user details**: Show the user's full details, including username, full name, email, phone, password, and permissions.
- **Access control**: Only users with the `pFindUser` permission can access this screen.
- **User validation**: Ensure the username exists before displaying the user's information.
- **Error handling**: Catch any errors during the search and display an appropriate message.

### List Users Screen (clsListUsersScreen)
- **List all users**: Display a formatted table with all users in the system.
- **User details**: Show each user's username, full name, phone number, email, password, and permissions.
- **No users check**: Display a message if no users are available in the system.
- **Formatted output**: The user list is printed in a neat, tabular format using `setw` for proper alignment.

### Delete User Screen (clsDeleteUserScreen)
- **Delete users**: Remove a user from the system after confirming the action.
- **User details**: Display the user's details before deletion for confirmation.
- **Confirmation**: Ask for confirmation before proceeding with the deletion.
- **Error handling**: Catch any errors during the deletion process and display an appropriate message.
- **Access control**: Only users with the `pDeleteUser` permission can delete users.

### Login Register Screen (clsLoginRegisterScreen)
- **View login register records**: Display a formatted list of login attempts, including date/time, username, password, and permissions.
- **Access control**: Only users with the `pLoginRegister` permission can view login register records.
- **Formatted output**: The login register records are printed in a neat, tabular format using `setw` for proper alignment.
- **No records check**: Display a message if no login records are available in the system.

## Technologies Used
- C++
- Object-Oriented Programming (OOP)
- Input Validation Techniques
- File Handling for Saving User and Client Data
