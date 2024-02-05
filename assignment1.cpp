#include <iostream>
#include <string>
#include <bits/stdc++.h> // Log function

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

void getUserDetails() {

    // Gender
    cout << "Enter your gender [Male or Female]: ";
    cin >> GENDER;

    // Ensuring gender input is lowercase for comparison
    for (int i = 0; i < GENDER.size(); i++) {
        GENDER[i] = tolower(GENDER[i]);
    }

    // Age
    cout << "Enter your age: ";
    cin >> AGE;

    // Weight
    cout << "Enter your weight: ";
    cin >> WEIGHT;

    // Waist
    cout << "Enter your waist size: ";
    cin >> WEIGHT;

    // Neck
    cout << "Enter your neck size: ";
    cin >> NECK;

    // Height
    cout << "Enter your height: ";
    cin >> HEIGHT;

    // Lifestyle
    cout << "Enter your lifestyle [sedintary, moderate, moderatley active, active]: ";
    cin >> LIFESTYLE;

    // If user is female
    if (GENDER == "female") {
        cout << "Enter your hip size: ";
        cin >> HIP_SIZE;
    }
}

pair<int, string> get_bfp(double waist, double neck, double height, double hip, string gender, int age) {
    int bfp;
    string group;

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
}

int main() {

    // Getting all relevant user information
    getUserDetails();

    // Getting bfp
    get_bfp(WAIST, NECK, HEIGHT, HIP_SIZE, GENDER, AGE);

    return 0;
} // end main