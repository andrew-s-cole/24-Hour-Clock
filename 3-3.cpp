#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

// Global variables to store the time
unsigned int hours = 12, minutes = 0, seconds = 0;

// Function to convert a number to a two-digit string
std::string twoDigitString(unsigned int n) {
    return (n < 10) ? "0" + std::to_string(n) : std::to_string(n);
}

// Function to format time in 24-hour notation
std::string formatTime24(unsigned int h, unsigned int m, unsigned int s) {
    return twoDigitString(h) + ":" + twoDigitString(m) + ":" + twoDigitString(s);
}

// Function to format time in 12-hour notation with AM/PM
std::string formatTime12(unsigned int h, unsigned int m, unsigned int s) {
    // Convert hours to 12-hour format
    unsigned int formattedHours = (h % 12 == 0) ? 12 : h % 12;

    // Determine whether it's AM or PM
    std::string amPm = (h < 12) ? "AM" : "PM";

    // Return the formatted time string
    return twoDigitString(formattedHours) + ":" + twoDigitString(m) + ":" + twoDigitString(s) + " " + amPm;
}

// Function to display both 12-hour and 24-hour clocks
void displayClocks() {
    std::cout << "12-Hour Clock: " << formatTime12(hours, minutes, seconds) << '\n'
              << "24-Hour Clock: " << formatTime24(hours, minutes, seconds) + " " + (hours < 12 ? "AM" : "PM") << "\n\n";
}

// Function to add one hour to the time
void addOneHour() {
    hours = (hours + 1) % 24;
}

// Function to add one minute to the time
void addOneMinute() {
    // Increment minutes and handle rollover to the next hour
    minutes = (minutes + 1) % 60 + (!minutes ? addOneHour(), 0 : 0);
}

// Function to add one second to the time
void addOneSecond() {
    // Increment seconds and handle rollover to the next minute
    seconds = (seconds + 1) % 60 + (!seconds ? addOneMinute(), 0 : 0);
}

// Function to set the initial time with user input
void setInitialTime() {
    std::cout << "Enter initial time:\n";

    auto inputTime = [](const std::string& label, unsigned int& value, unsigned int max) {
        do {
            std::cout << label << " (Enter a number: 0-" << max << "): ";
            if (!(std::cin >> value)) {
                std::cerr << "Invalid input. Please enter a number.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (value < 0 || value > max);
    };

    // Get hours, minutes, and seconds from the user
    inputTime("Hours", hours, 23);
    inputTime("Minutes", minutes, 59);
    inputTime("Seconds", seconds, 59);
}

// Function to get user choice from the menu
unsigned int getMenuChoice(unsigned int maxChoice) {
    unsigned int choice;
    bool isValidChoice = false;

    do {
        std::cout << "Menu:\n1. Add One Hour\n2. Add One Minute\n3. Add One Second\n4. Set Initial Time\n5. Exit\n";

        // Display the current time
        displayClocks();

        std::cout << "Enter your choice (1-" << maxChoice << "): ";
        std::cin >> choice;

        // Validate user input
        if (std::cin.fail() || choice < 1 || choice > maxChoice) {
            std::cout << "Invalid choice. Please enter a number between 1 and " << maxChoice << ".\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            isValidChoice = true;
        }

    } while (!isValidChoice);

    return choice;
}

// Main menu function to control the program flow
void mainMenu() {
    setInitialTime();

    while (true) {
        switch (getMenuChoice(5)) {
            case 1: addOneHour(); break;
            case 2: addOneMinute(); break;
            case 3: addOneSecond(); break;
            case 4: setInitialTime(); break;
            case 5: return;
            default: std::cerr << "Invalid choice. Exiting.\n"; return;
        }
    }
}

// Main function to start the program
int main() {
    mainMenu();
    return 0;
}