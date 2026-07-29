#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <sstream>
#include <cctype>

// ============================================================
// Transaction Class
// ============================================================
class Transaction {
private:
    int id;
    std::string type;          // "Income" or "Expense"
    double amount;
    std::string description;
    int month;                 // 1-12
    int year;
    std::string category;      // optional category (Food, Salary, etc.)

public:
    Transaction(int id, const std::string& type, double amount,
                const std::string& description, int month, int year,
                const std::string& category = "General")
        : id(id), type(type), amount(amount), description(description),
          month(month), year(year), category(category) {}

    // Getters
    int getId() const { return id; }
    std::string getType() const { return type; }
    double getAmount() const { return amount; }
    std::string getDescription() const { return description; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    std::string getCategory() const { return category; }

    // Setters (for edit)
    void setAmount(double a) { amount = a; }
    void setDescription(const std::string& d) { description = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }
    void setCategory(const std::string& c) { category = c; }
    void setType(const std::string& t) { type = t; }

    void display() const {
        std::cout << std::left
                  << std::setw(6)  << id
                  << std::setw(10) << type
                  << std::setw(12) << std::fixed << std::setprecision(2) << amount
                  << std::setw(8)  << (std::to_string(month) + "/" + std::to_string(year))
                  << std::setw(15) << category
                  << description << std::endl;
    }
};

// ============================================================
// User Class
// ============================================================
class User {
private:
    std::string name;
    std::string email;
    bool created;

public:
    User() : name(""), email(""), created(false) {}

    void createProfile() {
        std::cout << "\n=== Create User Profile ===\n";
        std::cout << "Enter your full name: ";
        std::getline(std::cin, name);
        while (name.empty()) {
            std::cout << "Name cannot be empty. Please enter your name: ";
            std::getline(std::cin, name);
        }

        std::cout << "Enter your email (optional, press Enter to skip): ";
        std::getline(std::cin, email);

        created = true;
        std::cout << "\nProfile created successfully for " << name << "!\n";
    }

    bool isCreated() const { return created; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }

    void displayInfo() const {
        if (!created) {
            std::cout << "No user profile created yet.\n";
            return;
        }
        std::cout << "\n--- User Profile ---\n";
        std::cout << "Name : " << name << "\n";
        if (!email.empty())
            std::cout << "Email: " << email << "\n";
    }
};

// ============================================================
// BudgetTracker Class (main application logic)
// ============================================================
class BudgetTracker {
private:
    User user;
    std::vector<Transaction> transactions;
    int nextId;

    // Helper: clear input buffer
    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Helper: get a valid double
    double getValidAmount(const std::string& prompt) {
        double amount;
        while (true) {
            std::cout << prompt;
            if (std::cin >> amount && amount > 0) {
                clearInput();
                return amount;
            }
            std::cout << "Invalid amount. Please enter a positive number.\n";
            clearInput();
        }
    }

    // Helper: get a valid month (1-12)
    int getValidMonth() {
        int m;
        while (true) {
            std::cout << "Enter month (1-12): ";
            if (std::cin >> m && m >= 1 && m <= 12) {
                clearInput();
                return m;
            }
            std::cout << "Invalid month. Please enter a number between 1 and 12.\n";
            clearInput();
        }
    }

    // Helper: get a valid year
    int getValidYear() {
        int y;
        while (true) {
            std::cout << "Enter year (e.g. 2026): ";
            if (std::cin >> y && y >= 2000 && y <= 2100) {
                clearInput();
                return y;
            }
            std::cout << "Invalid year. Please enter a reasonable year (2000-2100).\n";
            clearInput();
        }
    }

    // Helper: find transaction by ID
    int findTransactionIndex(int id) const {
        for (size_t i = 0; i < transactions.size(); ++i) {
            if (transactions[i].getId() == id)
                return static_cast<int>(i);
        }
        return -1;
    }

    // Helper: print table header
    void printHeader() const {
        std::cout << std::left
                  << std::setw(6)  << "ID"
                  << std::setw(10) << "Type"
                  << std::setw(12) << "Amount"
                  << std::setw(8)  << "Date"
                  << std::setw(15) << "Category"
                  << "Description" << std::endl;
        std::cout << std::string(70, '-') << std::endl;
    }

public:
    BudgetTracker() : nextId(1) {}

    // 1. Create User
    void createUser() {
        if (user.isCreated()) {
            std::cout << "\nA user profile already exists (" << user.getName() << ").\n";
            std::cout << "Do you want to overwrite it? (y/n): ";
            char choice;
            std::cin >> choice;
            clearInput();
            if (choice != 'y' && choice != 'Y') {
                std::cout << "Profile creation cancelled.\n";
                return;
            }
        }
        user.createProfile();
    }

    // 2. Add Income
    void addIncome() {
        if (!user.isCreated()) {
            std::cout << "\nPlease create a user profile first (option 1).\n";
            return;
        }

        std::cout << "\n=== Add Income ===\n";
        double amount = getValidAmount("Enter income amount: $");
        
        std::string description;
        std::cout << "Enter description: ";
        std::getline(std::cin, description);
        if (description.empty()) description = "Income";

        std::string category;
        std::cout << "Enter category (e.g. Salary, Freelance, Gift) [default: Salary]: ";
        std::getline(std::cin, category);
        if (category.empty()) category = "Salary";

        int month = getValidMonth();
        int year  = getValidYear();

        transactions.emplace_back(nextId++, "Income", amount, description, month, year, category);
        std::cout << "\nIncome of $" << std::fixed << std::setprecision(2) << amount
                  << " added successfully (ID: " << (nextId - 1) << ").\n";
    }

    // 3. Add Expense
    void addExpense() {
        if (!user.isCreated()) {
            std::cout << "\nPlease create a user profile first (option 1).\n";
            return;
        }

        std::cout << "\n=== Add Expense ===\n";
        double amount = getValidAmount("Enter expense amount: $");

        std::string description;
        std::cout << "Enter description: ";
        std::getline(std::cin, description);
        if (description.empty()) description = "Expense";

        std::string category;
        std::cout << "Enter category (e.g. Food, Rent, Transport, Entertainment) [default: General]: ";
        std::getline(std::cin, category);
        if (category.empty()) category = "General";

        int month = getValidMonth();
        int year  = getValidYear();

        transactions.emplace_back(nextId++, "Expense", amount, description, month, year, category);
        std::cout << "\nExpense of $" << std::fixed << std::setprecision(2) << amount
                  << " added successfully (ID: " << (nextId - 1) << ").\n";
    }

    // 4. View All Transactions
    void viewTransactions() const {
        if (transactions.empty()) {
            std::cout << "\nNo transactions recorded yet.\n";
            return;
        }

        std::cout << "\n=== All Transactions ===\n";
        if (user.isCreated())
            std::cout << "User: " << user.getName() << "\n\n";

        printHeader();
        for (const auto& t : transactions) {
            t.display();
        }
        std::cout << std::string(70, '-') << std::endl;
        std::cout << "Total transactions: " << transactions.size() << "\n";
    }

    // 5. Edit Transaction
    void editTransaction() {
        if (transactions.empty()) {
            std::cout << "\nNo transactions to edit.\n";
            return;
        }

        viewTransactions();
        std::cout << "\nEnter the ID of the transaction to edit: ";
        int id;
        if (!(std::cin >> id)) {
            clearInput();
            std::cout << "Invalid ID.\n";
            return;
        }
        clearInput();

        int idx = findTransactionIndex(id);
        if (idx == -1) {
            std::cout << "Transaction with ID " << id << " not found.\n";
            return;
        }

        Transaction& t = transactions[idx];
        std::cout << "\nEditing Transaction ID " << id << ":\n";
        t.display();

        std::cout << "\nWhat would you like to edit?\n";
        std::cout << "1. Amount\n";
        std::cout << "2. Description\n";
        std::cout << "3. Category\n";
        std::cout << "4. Month/Year\n";
        std::cout << "5. Type (Income <-> Expense)\n";
        std::cout << "0. Cancel\n";
        std::cout << "Choice: ";

        int choice;
        if (!(std::cin >> choice)) {
            clearInput();
            std::cout << "Invalid choice.\n";
            return;
        }
        clearInput();

        switch (choice) {
            case 1: {
                double newAmt = getValidAmount("Enter new amount: $");
                t.setAmount(newAmt);
                std::cout << "Amount updated.\n";
                break;
            }
            case 2: {
                std::string newDesc;
                std::cout << "Enter new description: ";
                std::getline(std::cin, newDesc);
                if (!newDesc.empty()) {
                    t.setDescription(newDesc);
                    std::cout << "Description updated.\n";
                }
                break;
            }
            case 3: {
                std::string newCat;
                std::cout << "Enter new category: ";
                std::getline(std::cin, newCat);
                if (!newCat.empty()) {
                    t.setCategory(newCat);
                    std::cout << "Category updated.\n";
                }
                break;
            }
            case 4: {
                int m = getValidMonth();
                int y = getValidYear();
                t.setMonth(m);
                t.setYear(y);
                std::cout << "Date updated.\n";
                break;
            }
            case 5: {
                if (t.getType() == "Income")
                    t.setType("Expense");
                else
                    t.setType("Income");
                std::cout << "Type changed to " << t.getType() << ".\n";
                break;
            }
            case 0:
                std::cout << "Edit cancelled.\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }

    // 6. Delete Transaction
    void deleteTransaction() {
        if (transactions.empty()) {
            std::cout << "\nNo transactions to delete.\n";
            return;
        }

        viewTransactions();
        std::cout << "\nEnter the ID of the transaction to delete: ";
        int id;
        if (!(std::cin >> id)) {
            clearInput();
            std::cout << "Invalid ID.\n";
            return;
        }
        clearInput();

        int idx = findTransactionIndex(id);
        if (idx == -1) {
            std::cout << "Transaction with ID " << id << " not found.\n";
            return;
        }

        std::cout << "Are you sure you want to delete this transaction?\n";
        transactions[idx].display();
        std::cout << "Confirm (y/n): ";
        char conf;
        std::cin >> conf;
        clearInput();

        if (conf == 'y' || conf == 'Y') {
            transactions.erase(transactions.begin() + idx);
            std::cout << "Transaction deleted successfully.\n";
        } else {
            std::cout << "Deletion cancelled.\n";
        }
    }

    // 7. Generate Monthly Report
    void generateMonthlyReport() {
        if (transactions.empty()) {
            std::cout << "\nNo transactions available for report.\n";
            return;
        }

        std::cout << "\n=== Generate Monthly Report ===\n";
        int month = getValidMonth();
        int year  = getValidYear();

        double totalIncome = 0.0;
        double totalExpense = 0.0;
        std::vector<Transaction> monthly;

        for (const auto& t : transactions) {
            if (t.getMonth() == month && t.getYear() == year) {
                monthly.push_back(t);
                if (t.getType() == "Income")
                    totalIncome += t.getAmount();
                else
                    totalExpense += t.getAmount();
            }
        }

        std::cout << "\n========== MONTHLY FINANCIAL REPORT ==========\n";
        if (user.isCreated())
            std::cout << "User   : " << user.getName() << "\n";
        std::cout << "Period : " << month << "/" << year << "\n";
        std::cout << "==============================================\n\n";

        if (monthly.empty()) {
            std::cout << "No transactions found for " << month << "/" << year << ".\n";
            return;
        }

        printHeader();
        for (const auto& t : monthly) {
            t.display();
        }
        std::cout << std::string(70, '-') << std::endl;

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\nSummary for " << month << "/" << year << ":\n";
        std::cout << "  Total Income  : $" << totalIncome << "\n";
        std::cout << "  Total Expenses: $" << totalExpense << "\n";
        std::cout << "  Net Balance   : $" << (totalIncome - totalExpense) << "\n";
        std::cout << "==============================================\n";
    }

    // 8. Display Balance (overall)
    void displayBalance() const {
        if (!user.isCreated()) {
            std::cout << "\nPlease create a user profile first.\n";
            return;
        }

        double totalIncome = 0.0;
        double totalExpense = 0.0;

        for (const auto& t : transactions) {
            if (t.getType() == "Income")
                totalIncome += t.getAmount();
            else
                totalExpense += t.getAmount();
        }

        double balance = totalIncome - totalExpense;

        std::cout << "\n========== FINANCIAL SUMMARY ==========\n";
        std::cout << "User            : " << user.getName() << "\n";
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Total Income    : $" << totalIncome << "\n";
        std::cout << "Total Expenses  : $" << totalExpense << "\n";
        std::cout << "---------------------------------------\n";
        std::cout << "Remaining Balance: $" << balance << "\n";
        std::cout << "=======================================\n";

        if (balance < 0)
            std::cout << "Warning: You are currently overspending!\n";
        else if (balance == 0)
            std::cout << "Balance is zero.\n";
        else
            std::cout << "You have a positive balance. Keep it up!\n";
    }

    // Utility: show current transaction count (for capacity awareness)
    size_t getTransactionCount() const {
        return transactions.size();
    }
};

// ============================================================
// Main Menu & Program Entry
// ============================================================
void displayMenu() {
    std::cout << "\n========================================\n";
    std::cout << "       PERSONAL BUDGET TRACKER\n";
    std::cout << "========================================\n";
    std::cout << "1. Create User Profile\n";
    std::cout << "2. Add Income\n";
    std::cout << "3. Add Expense\n";
    std::cout << "4. View All Transactions\n";
    std::cout << "5. Edit Transaction\n";
    std::cout << "6. Delete Transaction\n";
    std::cout << "7. Generate Monthly Report\n";
    std::cout << "8. Display Balance / Summary\n";
    std::cout << "9. Exit\n";
    std::cout << "========================================\n";
    std::cout << "Enter your choice (1-9): ";
}

int main() {
    BudgetTracker tracker;
    int choice = 0;

    std::cout << "Welcome to the Personal Budget Tracker!\n";
    std::cout << "This application helps you manage income, expenses, and monthly finances.\n";

    do {
        displayMenu();

        if (!(std::cin >> choice)) {
            std::cout << "\nInvalid input. Please enter a number between 1 and 9.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                tracker.createUser();
                break;
            case 2:
                tracker.addIncome();
                break;
            case 3:
                tracker.addExpense();
                break;
            case 4:
                tracker.viewTransactions();
                break;
            case 5:
                tracker.editTransaction();
                break;
            case 6:
                tracker.deleteTransaction();
                break;
            case 7:
                tracker.generateMonthlyReport();
                break;
            case 8:
                tracker.displayBalance();
                break;
            case 9:
                std::cout << "\nThank you for using Personal Budget Tracker. Goodbye!\n";
                break;
            default:
                std::cout << "\nInvalid menu option. Please choose between 1 and 9.\n";
        }

    } while (choice != 9);

    return 0;
}