# Bank Management System in C++

This is a **console-based bank management system** written in **C++** that allows you to manage client information and perform basic banking transactions such as deposit, withdraw, and balance inquiry. All client data is stored in a local text file (`clientsList.txt`).

---

## Features

- Show all clients
- Add new clients (with validation)
- Delete clients
- Update client info
- Find a specific client
- Deposit & Withdraw money
- View total balances across all clients
- Data persistence using file I/O (`clientsList.txt`)

---

## Project Structure

```bash
.
├── ClientsProblems.sln
├── clientsList.txt       
├── README.md       
```

---

## 🧾 clientsList.txt Format

Each client is stored in a single line in the following format:

```
AccountNumber#//#PinCode#//#FullName#//#Phone#//#Balance
```

Example:
```
12345#//#0000#//#John Doe#//#555-1234#//#2500.75
```

---

## Notes

- All client data is stored in a simple text file.
- Records are updated by rewriting the file (with logical deletion using a `mark` flag).
- The interface is entirely CLI-based with input validation and confirmation prompts.
- Works on Windows, Linux, and macOS.

---


## Author

Developed by [Ahmad Atiyeh].
