#ifndef ORDER_H
#define ORDER_H
 
#include <string>
 
class Order {
private:
    std::string customerName;
    int orderNumber;
    int numberOfWidgets;
 
public:
    // Default constructor
    Order();
 
    // Parameterized constructor
    Order(std::string name, int num, int widgets);
 
    // Getters
    std::string getCustomerName() const;
    int getOrderNumber() const;
    int getNumberOfWidgets() const;
 
    // Setters
    void setCustomerName(std::string name);
    void setOrderNumber(int num);
    void setNumberOfWidgets(int widgets);
 
    // For printing
    void printOrder() const;
};
 
#endif

#include <iostream>

Order::Order() : customerName(""), orderNumber(0), numberOfWidgets(0) {}

Order::Order(std::string name, int num, int widgets)
    : customerName(name), orderNumber(num), numberOfWidgets(widgets) {}

std::string Order::getCustomerName() const {
    return customerName;
}

int Order::getOrderNumber() const {
    return orderNumber;
}

int Order::getNumberOfWidgets() const {
    return numberOfWidgets;
}

void Order::setCustomerName(std::string name) {
    customerName = name;
}

void Order::setOrderNumber(int num) {
    orderNumber = num;
}

void Order::setNumberOfWidgets(int widgets) {
    numberOfWidgets = widgets;
}

void Order::printOrder() const {
    std::cout << "Order Number: " << orderNumber 
              << ", Customer: " << customerName 
              << ", Widgets: " << numberOfWidgets << std::endl;
}

#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main() {
    queue<Order> orderQueue;
    int choice;
    int nextOrderNum = 1; // To auto-assign order numbers

    do {
        cout << "\nFactory Order Management System\n";
        cout << "1. Add an order\n";
        cout << "2. Remove an order\n";
        cout << "3. Check how many orders are waiting to be processed\n";
        cout << "4. Print a list of the orders\n";
        cout << "5. Process the next pending order\n";
        cout << "6. Change the number of widgets in an order\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: { // Add an order
                string name;
                int widgets;
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter number of widgets: ";
                cin >> widgets;
                Order newOrder(name, nextOrderNum++, widgets);
                orderQueue.push(newOrder);
                cout << "Order added successfully. Order Number: " << newOrder.getOrderNumber() << endl;
                break;
            }
            case 2: { // Remove an order
                if (orderQueue.empty()) {
                    cout << "No orders to remove.\n";
                    break;
                }
                int orderNum;
                cout << "Enter order number to remove: ";
                cin >> orderNum;
                queue<Order> tempQueue;
                bool found = false;
                while (!orderQueue.empty()) {
                    Order ord = orderQueue.front();
                    orderQueue.pop();
                    if (ord.getOrderNumber() == orderNum) {
                        found = true;
                        cout << "Order " << orderNum << " removed.\n";
                    } else {
                        tempQueue.push(ord);
                    }
                }
                while (!tempQueue.empty()) {
                    orderQueue.push(tempQueue.front());
                    tempQueue.pop();
                }
                if (!found) {
                    cout << "Order number " << orderNum << " not found.\n";
                }
                break;
            }
            case 3: // Check number of orders
                cout << "Number of pending orders: " << orderQueue.size() << endl;
                break;
            case 4: { // Print pending orders
                if (orderQueue.empty()) {
                    cout << "No pending orders.\n";
                    break;
                }
                cout << "Pending Orders:\n";
                queue<Order> tempQueue = orderQueue; // Copy to print without destroying
                while (!tempQueue.empty()) {
                    Order ord = tempQueue.front();
                    tempQueue.pop();
                    ord.printOrder();
                }
                break;
            }
            case 5: { // Process next order
                if (orderQueue.empty()) {
                    cout << "No orders to process.\n";
                    break;
                }
                Order next = orderQueue.front();
                orderQueue.pop();
                cout << "Processing order:\n";
                next.printOrder();
                break;
            }
            case 6: { // Change number of widgets
                if (orderQueue.empty()) {
                    cout << "No orders to modify.\n";
                    break;
                }
                int orderNum, newWidgets;
                cout << "Enter order number: ";
                cin >> orderNum;
                cout << "Enter new number of widgets: ";
                cin >> newWidgets;
                queue<Order> tempQueue;
                bool found = false;
                while (!orderQueue.empty()) {
                    Order ord = orderQueue.front();
                    orderQueue.pop();
                    if (ord.getOrderNumber() == orderNum) {
                        ord.setNumberOfWidgets(newWidgets);
                        tempQueue.push(ord);
                        found = true;
                        cout << "Order " << orderNum << " updated to " << newWidgets << " widgets.\n";
                    } else {
                        tempQueue.push(ord);
                    }
                }
                while (!tempQueue.empty()) {
                    orderQueue.push(tempQueue.front());
                    tempQueue.pop();
                }
                if (!found) {
                    cout << "Order number " << orderNum << " not found.\n";
                }
                break;
            }
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

