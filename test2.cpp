#include <iostream>

int main() {
   int userNum;

   std::cout << "Enter integer:" << std::endl;
   std::cin >> userNum;
   
   std::cout << "You entered: " << userNum << std::endl;
   std::cout << userNum << " squared is " << userNum * userNum << std::endl;
   std::cout << "And " << userNum << " cubed is " << userNum * userNum * userNum << "!!" << std::endl;

   return 0;
}
