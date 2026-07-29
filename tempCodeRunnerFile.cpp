#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    string filename;
    cin >> filename;
    
    ifstream file(filename);
    if (!file.is_open()) {
        // Handle error if needed, but assume file exists
        return 1;
    }
    
    string line;
    string current_title = "";
    string current_rating = "";
    vector<string> showtimes;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        // Find first comma for showtime
        size_t comma1 = line.find(',');
        if (comma1 == string::npos) continue;
        
        string showtime = line.substr(0, comma1);
        
        // Find second comma for title and rating
        size_t comma2 = line.find(',', comma1 + 1);
        if (comma2 == string::npos) continue;
        
        string title = line.substr(comma1 + 1, comma2 - comma1 - 1);
        string rating = line.substr(comma2 + 1);
        
        // Trim possible spaces if any (though example seems clean)
        // For safety
        if (!title.empty() && title.back() == ' ') title.pop_back();
        if (!rating.empty() && rating.back() == ' ') rating.pop_back();
        
        if (title != current_title && !current_title.empty()) {
            // Output previous movie
            cout << left << setw(44) << current_title.substr(0, 44) 
                 << " | " << right << setw(5) << current_rating 
                 << " |";
            
            for (size_t i = 0; i < showtimes.size(); ++i) {
                cout << " " << showtimes[i];
            }
            cout << endl;
            
            showtimes.clear();
        }
        
        if (title != current_title) {
            current_title = title;
            current_rating = rating;
        }
        
        showtimes.push_back(showtime);
    }
    
    // Output the last movie
    if (!current_title.empty()) {
        cout << left << setw(44) << current_title.substr(0, 44) 
             << " | " << right << setw(5) << current_rating 
             << " |";
        
        for (size_t i = 0; i < showtimes.size(); ++i) {
            cout << " " << showtimes[i];
        }
        cout << endl;
    }
    
    file.close();
    return 0;
}