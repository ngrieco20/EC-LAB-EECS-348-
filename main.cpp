#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>  // for formatting a double precision number given in rubric 

using namespace std;

double extractNumeric(const string& input) {
    bool hasDecimalPoint = false;
    bool hasDigits = false;
    double result = 0.0;
    int sign = 1;
    size_t i = 0;
    double dec_place = 1.0;

    // if statement used for + or - sign
    if (input[i] == '+' || input[i] == '-') {
        if (input[i] == '-') {
            sign = -1;
        }
        i++;  // skips the sign 
    }

    // reads and processes digits and decial points 
    while (i < input.size() && (isdigit(input[i]) || input[i] == '.')) {
        if (isdigit(input[i])) {
            hasDigits = true;
            if (hasDecimalPoint) {
                result = result + (input[i] - '0') * dec_place;
                dec_place /= 10;
            } else {
                result = result * 10 + (input[i] - '0');
            }
        } else if (input[i] == '.') {
            if (hasDecimalPoint) {
                return -999999.99;  // makes it so that more than 1 decimal point is invalid 
            }
            hasDecimalPoint = true;
            dec_place= 0.1;
        }
        i++;
    }

    if (hasDecimalPoint) {
        double dec_place = 0.1; // starts with 0.1 for decimal places 
        while (i < input.size() && isdigit(input[i])) { 
            result += (input[i] - '0') * dec_place;
            dec_place /= 10;  // moves onto next deciaml palce 
            i++;
        }
    }

    // error handling 
    if (!hasDigits) {
        return -999999.99;
    }

    // makes sure whole string is read with no incorrect characters 
    while (i < input.size() && isspace(input[i])) {
        i++;  // skips spaces at the end 
    }

    if (i != input.size()) {
        return -999999.99;  // handles extra characters in string 
    }

    return result * sign;
}

//main function given in rubric 
int main() {
    string input;

    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;

        if (input == "END") {
            break;
        }

        double result = extractNumeric(input);
        if (result != -999999.99) {
            // output result matches rubric 
            cout << "The input is: " << fixed << setprecision(4) << result << endl;
        } else {
            cout << "The input is invalid." << endl;
        }
    }

    return 0;
}
