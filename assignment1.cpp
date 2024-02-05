#include <iostream>
#include <string>
#include <cmath> // Log function

using namespace std;

// Global variables
string GENDER;
int AGE;
float WEIGHT;
float WAIST;
float NECK;
float HEIGHT;
string LIFESTYLE;
float HIP_SIZE = -1; // May not be initialized in main, but is passed to arg

bool is_number(string input) {

    // Using float conversion function to check is input is a number
    try {
        float num = stof(input);

        // Able to parse to number
        return true;

    // Unable to convert to a float
    } catch (const std::invalid_argument& ia) {
        
        return false;
    }
} // end is_number

void getUserDetails() {

    // Gender
    string gender;
    cout << "Enter your gender [Male or Female]: ";
    cin >> gender;

    // Input validation
    if (is_number(gender)) {
        cout << "Bad input.";
        exit(1);
    }
    GENDER = gender; // Is string

    // Ensuring gender input is lowercase for comparison
    for (int i = 0; i < GENDER.size(); i++) {
        GENDER[i] = tolower(GENDER[i]);
    }

    // Checking to see if is valid
    if (GENDER != "male" && GENDER != "female") {
        cout << "Please enter either male of female.";
        exit(1);
    }

    // Age
    string age;
    cout << "Enter your age: ";
    cin >> age;
    
    // Input validation
    if (!is_number(age)) {
        cout << "Bad input.";
        exit(1);
    }
    AGE = stof(age);

    // Weight
    string weight;
    cout << "Enter your weight: ";
    cin >> weight;

    // Input validation
    if (!is_number(weight)) {
        cout << "Bad input.";
        exit(1);
    }
    WEIGHT = stof(weight); 

    // Waist
    string waist;
    cout << "Enter your waist size: ";
    cin >> waist;

    // Input validation
    if (!is_number(waist)) {
        cout << "Bad input.";
        exit(1);
    }
    WAIST = stof(waist);

    // Neck
    string neck;
    cout << "Enter your neck size: ";
    cin >> neck;

    // Input validation
    if (!is_number(neck)) {
        cout << "Bad input.";
        exit(1);
    }
    NECK = stof(neck);

    // Height
    string height;
    cout << "Enter your height: ";
    cin >> height;

    // Input validation
    if (!is_number(height)) {
        cout << "Bad input.";
        exit(1);
    }

    // Lifestyle
    string lifestyle;
    cout << "Enter your lifestyle [sedentary, moderate, moderately active, active]: ";
    cin >> lifestyle;

    // Input validation
    if (is_number(lifestyle)) {
        cout << "Bad input.";
        exit(1);
    }
    LIFESTYLE = lifestyle;

    // Ensuring lifestyle input is lowercase for comparison
    for (int i = 0; i < LIFESTYLE.size(); i++) {
        LIFESTYLE[i] = tolower(LIFESTYLE[i]);
    }

    // Secondary input validation
    if (LIFESTYLE != "sedentary" && LIFESTYLE != "moderate" && LIFESTYLE != "moderately actuve" && LIFESTYLE != "active") {
        cout << "Please enter either sedentary, moderate, moderately active or active.";
        exit(1);
    }

    // If user is female
    if (GENDER == "female") {
        string hip_size;
        cout << "Enter your hip size: ";
        cin >> hip_size;

        if (!is_number(hip_size)) {
            cout << "Bad input.";
            exit(1);
        }
        HIP_SIZE = stof(hip_size);
    }
} // end getUserData

pair<int, string> get_bfp(double waist, double neck, double height, double hip, string gender, int age) {
    int bfp;
    string group;

    // Male
    if (gender == "male") {
        bfp = static_cast<int>(495 / (1.0324 - 0.19077 * log10(waist - neck) + 0.15456 * log10(height)) - 450);

        // Returning bfp group
        if (20 <= age && age < 40) {

            if (bfp < 8) {
                group = "low";
            } else if (8 <= bfp && bfp < 20) {
                group = "normal";
            } else if (20 <= bfp && bfp < 25) {
                group = "high";
            } else {
                group = "very high";
            }

        } else if (40 <= age && age < 60) {

            if (bfp < 11) {
                group = "low";
            } else if (11 <= bfp && bfp < 22) {
                group = "normal";
            } else if (22 <= bfp && bfp < 28) {
                group = "high";
            } else {
                group = "very high";
            }
        
        } else if (60 <= age) {

            if (bfp < 13) {
                group = "low";
            } else if (13 <= bfp && bfp < 25) {
                group = "normal";
            } else if (25 <= bfp && bfp < 30) {
                group = "high";
            } else {
                group = "very high";
            }
        }

    // Female
    } else {
        bfp = static_cast<int>(495 / (1.29579 - 0.35004 * log10(waist + hip - neck) + 0.22100 *log10(height)) - 450);

        // Returning bfp group
        if (20 <= age && age < 40) {

            if (bfp < 21) {
                group = "low";
            } else if (21 <= bfp && bfp < 33) {
                group = "normal";
            } else if (33 <= bfp && bfp < 40) {
                group = "high";
            } else {
                group = "very high";
            }

        } else if (40 <= age && age < 60) {

            if (bfp < 23) {
                group = "low";
            } else if (23 <= bfp && bfp < 34) {
                group = "normal";
            } else if (34 <= bfp && bfp < 40) {
                group = "high";
            } else {
                group = "very high";
            }
        
        } else if (60 <= age) {

            if (bfp < 24) {
                group = "low";
            } else if (24 <= bfp && bfp < 36) {
                group = "normal";
            } else if (36 <= bfp && bfp < 42) {
                group = "high";
            } else {
                group = "very high";
            }
        }
    }

    pair<int, string> res;
    res.first = bfp;
    res.second = group;
    return res;
} // end get_bfp

int get_daily_calories(double age, string gender, string lifestyle) {
    int calories;

    // Male
    if (gender == "male") {

        // 19-30
        if (19 <= age && age < 31) {

            if (lifestyle == "sedentary") {
                calories = 2400;
            } else if (lifestyle == "moderately active") {
                calories = 2600;
            } else {
                calories = 3000;
            }

        // 31-51
        } else if (31 <= age && age < 51) {

            if (lifestyle == "sedentary") {
                calories = 2200;
            } else if (lifestyle == "moderately active") {
                calories = 2400;
            } else {
                calories = 2800;
            }

        // 51+
        } else {
            
            if (lifestyle == "sedentary") {
                calories = 2000;
            } else if (lifestyle == "moderately active") {
                calories = 2200;
            } else {
                calories = 2400;
            }
        }

    // Female
    } else {

        // 19-30
        if (19 <= age && age < 31) {

            if (lifestyle == "sedentary") {
                calories = 2000;
            } else if (lifestyle == "moderately active") {
                calories = 2000;
            } else {
                calories = 2400;
            }

        // 31-51
        } else if (31 <= age && age < 51) {

            if (lifestyle == "sedentary") {
                calories = 1800;
            } else if (lifestyle == "moderately active") {
                calories = 2000;
            } else {
                calories = 2200;
            }

        // 51+
        } else {
            
            if (lifestyle == "sedentary") {
                calories = 1600;
            } else if (lifestyle == "moderately active") {
                calories = 1800;
            } else {
                calories = 2000;
            }
        }

    }

    return calories;
} // end get_daily_calories

int main() {

    // Getting all relevant user information
    getUserDetails();

    // Getting bfp
    get_bfp(WAIST, NECK, HEIGHT, HIP_SIZE, GENDER, AGE);

    return 0;
} // end main