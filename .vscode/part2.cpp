#include <iostream>
#include <string>
#include <cctype>  // for isdigit() and isalpha()
#include <limits>  // for numeric_limits

int main() {
    std::cout << "=== Part 2 — Stream Inspector ===\n\n";

    // ==================== H — peek and get ====================
    std::cout << "H — peek and get demonstration\n";
    std::cout << "Please type a line of text: ";
    
    // Peek at the first character without consuming it
    char firstChar = std::cin.peek();
    
    if (firstChar == EOF) {
        std::cout << "No input or end of file detected.\n";
    } else if (std::isdigit(static_cast<unsigned char>(firstChar))) {
        std::cout << "First character is a DIGIT.\n";
    } else if (std::isalpha(static_cast<unsigned char>(firstChar))) {
        std::cout << "First character is a LETTER.\n";
    } else {
        std::cout << "First character is neither digit nor letter (e.g., space, symbol, etc.).\n";
    }
    
    // Now read and echo the whole line
    std::string line;
    std::getline(std::cin, line);
    std::cout << "You entered: " << line << "\n\n";

    // ==================== I — ignore and getline ====================
    std::cout << "I — ignore and getline demonstration\n";
    
    int number;
    std::cout << "Enter an integer: ";
    std::cin >> number;
    
    // Discard the leftover newline character in the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::string description;
    std::cout << "Enter a full-line description: ";
    std::getline(std::cin, description);
    
    std::cout << "Integer: " << number << "\n";
    std::cout << "Description: " << description << "\n\n";

    // ==================== J — Input failure recovery ====================
    std::cout << "J — Input failure recovery demonstration\n";
    std::cout << "Enter a number (try typing letters to test failure): ";
    
    int value;
    std::cin >> value;
    
    if (std::cin.fail()) {
        std::cout << "Invalid input! The stream entered fail state.\n";
        std::cin.clear();  // Clear the error flags
        // Discard the bad input up to the newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Input has been cleared. You can try again in a real program.\n";
    } else {
        std::cout << "You entered: " << value << "\n";
        // Clean up any leftover newline for consistency
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    std::cout << "\n=== End of Stream Inspector ===\n";

    // Note on putback():
    /*
     * Realistic use case for cin.putback():
     * When parsing input where you need to "look ahead" (e.g., reading a number but then
     * discovering it's actually part of a different format like a date or identifier).
     * Example: You peek() and see a '-', decide it's a negative number, but a more complex
     * parser later needs the '-' back in the stream. You can use putback('-') to restore it.
     * This avoids complex state management when combining different parsing strategies.
     */

    return 0;
}