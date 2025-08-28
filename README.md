# ATM Machine Project
## Introduction
The **ATM Machine Project** simulates a basic ATM system where users can interact with their bank accounts to perform common banking operations such as:
- Checking their balance
- Making deposits
- Withdrawing cash  

This project also supports **multi-user login**, allowing two different accounts (`12345` and `123456`) to be used for demonstration.

---
## Key Features
* Multi-user support
* Secure login with PIN (max 3 attempts)
* Withdraw, deposit, and balance inquiry
* Account lockout after failed attempts
* Ability to switch between accounts

---
## Functionality
### 1. User Validation
- **Account Number Input**
  - User enters an account number.
  - If the account exists (matches a text file), the program proceeds to ask for the **PIN code**.
  - If not, the program will keep asking until a valid account number is entered.
- **PIN Code Input**
  - After entering a valid account number, the user is asked for their **PIN code**.
  - Maximum **3 attempts** are allowed.
  - After 3 failed attempts, the account is **locked**, and the program asks if the user wants to continue with another account.

---

### 2. Main Menu
After successful login, the user can select from the following options:

1. **Withdrawal**
   - Withdraw money in multiples of **20€ or 50€**.
   - Must maintain a **minimum balance of 20€**.
   - Enter `0` to cancel.

2. **Deposit**
   - Deposit amounts between **10€ and 1000€**.
   - Maximum account balance allowed: **2000€**.
   - Enter `0` to cancel.

3. **Balance Inquiry**
   - Displays the current account balance.

9. **Quit**
   - Exit the program.

➡ Users can perform multiple operations in sequence until they choose to quit.

---

### 3. Loading a Different Account
Before exiting, the system asks:
- Press **Y/y** → Log in with another account.
- Press **N/n** → End the program.

---

## Technologies Used
- **Language:** C  
- **IDE:** Code::Blocks (but works with any C compiler)  
- **File I/O:** Account data stored and validated via text files  

---

## Future Improvements
* Add support for more accounts.
* Implement transaction history.
* Improve error handling and UI experience.
* Add encrypted account storage for better security.

---

Author: Quynh Anh Le\
Year: 2024
