#include <stdio.h>

int main()
{
    //Part B: named constants
    const double TAX_RATE = 0.14;
    const int BONUS = 50;

    // Part C: Variables
    char name[50];
    double payRate;
    double hoursWorked;
    double grossPay;
    double tax;
    double netpay;

    // Part D
    printf("Enter last name: ");
    scanf("%49s", name);

    printf("Enter hourly pay rate: ");
    scanf("%lf", &payRate);

    printf("Enter hours worked this week: ");
    scanf("%lf", &hoursWorked);

    grossPay = payRate * hoursWorked;
    tax = grossPay * TAX_RATE;
    netpay = grossPay - tax + BONUS;

    printf("Gross Pay: $%.2f\n", grossPay);
    printf("Tax (14%%): $%.2f\n", tax);
    printf("Net Pay (after tax + $50 bonus): $%.2f\n", netpay);
    return 0;
}