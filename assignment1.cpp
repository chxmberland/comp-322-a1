#include <iostream>
#include <fstream>
#include <sstream> // String stream
#include <string>
#include <cmath> // Log function

using namespace std;

// Basic information global variables
string GENDER;
int AGE;
float WEIGHT;
float WAIST;
float NECK;
float HEIGHT;
string LIFESTYLE;
float HIP_SIZE = -1; // May not be initialized in main, but is passed to arg
vector< vector<string> > USER_DATA;

// Derived information global variables
pair<int, string> BFP_GROUP;
int DAILY_CALORIES;
double CARBS_NEEDED;
double PROTEIN_NEEDED;
double FAT_NEEDED;

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
    cout << "Enter your weight (kg): ";
    cin >> weight;

    // Input validation
    if (!is_number(weight)) {
        cout << "Bad input.";
        exit(1);
    }
    WEIGHT = stof(weight); 

    // Waist
    string waist;
    cout << "Enter your waist size (cm): ";
    cin >> waist;

    // Input validation
    if (!is_number(waist)) {
        cout << "Bad input.";
        exit(1);
    }
    WAIST = stof(waist);

    // Neck
    string neck;
    cout << "Enter your neck size (cm): ";
    cin >> neck;

    // Input validation
    if (!is_number(neck)) {
        cout << "Bad input.";
        exit(1);
    }
    NECK = stof(neck);

    // Height
    string height;
    cout << "Enter your height: (cm) ";
    cin >> height;

    // Input validation
    if (!is_number(height)) {
        cout << "Bad input.";
        exit(1);
    }
    HEIGHT = stof(height);

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
    if (LIFESTYLE != "sedentary" && LIFESTYLE != "moderate" && LIFESTYLE != "moderately active" && LIFESTYLE != "active") {
        cout << "Please enter either sedentary, moderate, moderately active or active.";
        exit(1);
    }

    // If user is female
    if (GENDER == "female") {
        string hip_size;
        cout << "Enter your hip size (cm): ";
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

void meal_prep(int calories_input, double& carbs_output, double& protein_output, double& fat_output) {
    carbs_output = (calories_input * 0.5) / 4;
    protein_output = (calories_input * 0.3) / 4;
    fat_output  = (calories_input * 0.2) / 9;
} // end meal_prep

void display() {
    cout << "BFP: " << BFP_GROUP.first << endl;
    cout << "BFP Group: " << BFP_GROUP.second << endl;
    cout << "Needed daily calories: " << DAILY_CALORIES << endl;
    cout << "Carbs needed: " << CARBS_NEEDED << endl;
    cout << "Protein needed: " << PROTEIN_NEEDED << endl;
    cout << "Fat needed: " << FAT_NEEDED << endl;
}

void serialize(string filename) {

    // Constructing file in append mode
    ofstream out_file(filename, ios::app);

    // Check if the file is open
    if (!out_file.is_open()) {
        cout << "Failed to open output file" << endl;
        exit(1);
    }

    // Structure to hold data
    string hip_size = (HIP_SIZE == -1) ? "" : to_string(HIP_SIZE);
    vector<string> data;
    data.push_back(GENDER);
    data.push_back(to_string(AGE));
    data.push_back(to_string(WEIGHT));
    data.push_back(to_string(WAIST));
    data.push_back(to_string(NECK));
    data.push_back(hip_size);
    data.push_back(to_string(HEIGHT));
    data.push_back(LIFESTYLE);

    // Writing the data
    for (int i = 0; i < data.size(); i++) {

        if (i == data.size() - 1) {
            out_file << data[i] << "\n";

        } else {
            out_file << data[i] << ",";
        }
    }

    out_file.close();
}

void readFromFile(char* filename) {

    // Opening the file in reading mode
    ifstream in_file(filename);

    // Ensure the file actually exists
    if (!in_file.is_open()) {
        cout << "Error opening input file.";
        exit(1);
    }

    // Looping through each line of the file until the end is reached
    string line;
    while(getline(in_file, line)) {
        vector<std::string> row;

        // Get stream object from row
        stringstream s(line);
        string data;

        // Comma delimeters
        while (getline(s, data, ',')) row.push_back(data);

        // Adding the row to the global user data vector
        USER_DATA.push_back(row);
    }
}

int main(int argc, char* argv[]) {

    // Checking to see if the user passed any arguments
    if (argc > 1) {

        // Reading user information from file
        readFromFile(argv[1]);

    // Single user
    } else {

        // Getting all relevant user information
        getUserDetails();

        // Getting bfp
        BFP_GROUP = get_bfp(WAIST, NECK, HEIGHT, HIP_SIZE, GENDER, AGE);


        // Getting the required daily calories
        DAILY_CALORIES = get_daily_calories(AGE, GENDER, LIFESTYLE);

        // Meal prepping (modify in place, returns nothing)
        meal_prep(DAILY_CALORIES, CARBS_NEEDED, PROTEIN_NEEDED, FAT_NEEDED);

        // All previous variables need to be global, since this function takes no arguments
        display();

        // Saving information to a file
        serialize("output.csv");
    }

    return 0;
} // end main