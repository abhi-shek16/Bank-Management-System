# 🏦 Bank Management System

## 💡 Description

Developed a command-line based banking system using C++ that simulates real-world financial operations for both **Savings** and **Current** accounts. Implemented core Object-Oriented Programming concepts including **inheritance**, **polymorphism**, and **abstraction** to create modular account types.

Utilized **STL containers** like `map` and `vector` for efficient account management. Features include:

- Interest calculation for Savings accounts
- Overdraft protection for Current accounts
- Complete transaction history logging

## 🛠️ Technologies Used

- C++
- Object-Oriented Programming (OOP)
- STL (`map`, `vector`)
- OS Concepts
- File Handling (can be added)

## 🚀 Features

- Create Savings or Current accounts
- Deposit and withdraw money
- Interest calculation for Savings accounts (4% static)
- Overdraft limit (₹10,000) for Current accounts
- Unique account number tracking using `map`
- Display account details
- View full transaction history

## 🔧 How to Compile and Run

```bash
g++ bank_management_system.cpp -o bank_system
./bank_system
