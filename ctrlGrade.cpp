#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


void read_file (string);
double calc_CW_Mark (int);
double predictor (double, int);
void prediction_report (string);
void student_report (int);

const int GRADE_A = 80;
const int GRADE_A_MINUS = 70;
const int GRADE_B_PLUS = 64;
const int GRADE_B = 58;
const int GRADE_B_MINUS = 52;
const int GRADE_C_PLUS = 46;
const int GRADE_C = 40;


const int NUM_STUDENT = 15;
int studentID[NUM_STUDENT];
string studentName[NUM_STUDENT];
int CW1[NUM_STUDENT];
int CW2[NUM_STUDENT];
int CW3[NUM_STUDENT];
int CW4[NUM_STUDENT];
int CW5[NUM_STUDENT];
int CW6[NUM_STUDENT];
double CWMark[NUM_STUDENT];
int count;

int main(){
    read_file("student.txt");
    prediction_report("prediction_report.txt");

    for (count = 0; count < NUM_STUDENT; count++){
        student_report(count);
    }


    cout << "Prediction report and individual student reports have been generated successfully." << endl;
    
    return 0;
}


void read_file (string fileName){
    ifstream inFile("student.txt");

        if (!inFile){
        cout << "Error opening file: " << fileName << endl;
        return;
    }else{
        cout << "File opened successfully: " << fileName << endl;
    }

    for (count = 0; count < NUM_STUDENT; count++){
        inFile >> studentID[count];
        inFile.ignore();
        getline(inFile, studentName[count], '\t');
        inFile >> CW1[count] >> CW2[count] >> CW3[count] >> CW4[count] >> CW5[count] >> CW6[count];
    }
    inFile.close();
}


void display_menu (){
    cout << "";
}


double calc_CW_Mark (int count){
    return CW1[count]*0.1 + CW2[count]*0.08 + CW3[count]*0.1 + CW4[count]*0.08 + CW5[count]*0.08 + CW6[count]*0.06;
}


double predictor (double CWMark, int targetMark){
    return (targetMark - CWMark)/50*100;
}


void prediction_report (string fileName){
    // Create Overall Prediction Report

    ofstream outFile(fileName.c_str());

    outFile << "=========================================================" << endl;
    outFile << "CCA101 FINAL EXAMINATION PREDICTION REPORT" << endl;
    outFile << "=========================================================" << endl << endl;

    outFile << setw(17) << left << "ID" << setw(16) << "Name" << setw(13) << "CW Mark" << setw(9) << "A" << setw(9) << "A-" <<  setw(9) << "B+" << setw(9) << "B" << setw(9) << "B-" << setw(9) << "C+" << setw(9) << "C" << endl;

    outFile << "-----------------------------------------------------------------------------------------------------------" << endl;

    outFile << setprecision(2) << fixed;

    for (count = 0; count < NUM_STUDENT; count++){
        CWMark[count] = calc_CW_Mark(count);

        outFile << studentID[count] << "\t";
        outFile << setw(25) << left << studentName[count];
        outFile << setw(6) << right << CWMark[count] << "    " ;
        outFile << setw(6) << predictor(CWMark[count], GRADE_A) << "   " ;
        outFile << setw(6) << predictor(CWMark[count], GRADE_A_MINUS) << "   " ;
        outFile << setw(6) << predictor(CWMark[count], GRADE_B_PLUS) << "   " ;
        outFile << setw(6) << predictor(CWMark[count], GRADE_B) << "   " ;
        outFile << setw(6) << predictor(CWMark[count], GRADE_B_MINUS) << "   ";
        if (CWMark[count] >= GRADE_C_PLUS){
            outFile << "Achieved " << "Achieved" << endl;
        }else if(CWMark[count] >= GRADE_C){
            outFile << setw(6) << predictor(CWMark[count], GRADE_C_PLUS) << "   ";
            outFile << "Achieved" << endl;
        }else{
            outFile << setw(6) << predictor(CWMark[count], GRADE_C_PLUS) << "   ";
            outFile << setw(6) << predictor(CWMark[count], GRADE_C) << endl;
        }
    }
    outFile << "============================================================================================================" << endl;

    outFile.close();
}

void student_report (int count){
    string fileName = to_string(studentID[count]) + ".txt";
    ofstream reportFile(fileName);

    reportFile << "===================================================================================" << endl;
    reportFile << "CCA101 STUDENT PERFORMANCE REPORT" << endl;
    reportFile << "===================================================================================" << endl << endl;

    reportFile << "Student ID   : " << studentID[count] << endl;
    reportFile << "Student Name : " << studentName[count] << endl << endl;

    reportFile << "-----------------------------------------------------------------------------------" << endl;
    reportFile << "COURSEWORK PERFORMANCE" << endl;
    reportFile << "-----------------------------------------------------------------------------------" << endl;
    reportFile << setw(32) << left << "CW1 - Test 1" << " : " << CW1[count] << endl;
    reportFile << setw(32) << "CW2 - Timed Programming 1" << " : " << CW2[count] << endl;
    reportFile << setw(32) << "CW3 - Test 2" << " : " << CW3[count] << endl;
    reportFile << setw(32) << "CW4 - Timed Programming 2" << " : " << CW4[count] << endl;
    reportFile << setw(32) << "CW5 - Report-Based Programming" << " : " << CW5[count] << endl;
    reportFile << setw(32) << "CW6 - Weekly Programming" << " : " << CW6[count] << endl << endl;

    reportFile << setprecision(2) << fixed;
    reportFile << setw(32) << "Coursework Contribution (50%)" << " : " << CWMark[count] << endl << endl;

    reportFile << "-----------------------------------------------------------------------------------" << endl;
    reportFile << "FINAL EXAMINATION PREDICTION" << endl;
    reportFile << "-----------------------------------------------------------------------------------" << endl << endl;

    reportFile << setw(16) << "Target Grade" << setw(23) << "Target Overall Mark" << "Required Final Exam Mark" << endl;
    reportFile << "-------------------------------------------------------------------" << endl;
    reportFile << setw(16) << left << "A" << setw(23) << GRADE_A << setw(5) << right << predictor (CWMark[count], GRADE_A) << endl;
    reportFile << setw(16) << left << "A-" << setw(23) << GRADE_A_MINUS << setw(5) << right << predictor (CWMark[count], GRADE_A_MINUS) << endl;
    reportFile << setw(16) << left << "B+" << setw(23) << GRADE_B_PLUS << setw(5) << right << predictor (CWMark[count], GRADE_B_PLUS) << endl;
    reportFile << setw(16) << left << "B" << setw(23) << GRADE_B << setw(5) << right << predictor (CWMark[count], GRADE_B) << endl;
    reportFile << setw(16) << left << "B-" << setw(23) << GRADE_B_MINUS << setw(5) << right << predictor (CWMark[count], GRADE_B_MINUS) << endl;
    if (CWMark[count] >= GRADE_C_PLUS){
        reportFile << setw(16) << left  << "C+" << setw(23) << GRADE_C_PLUS << "ALREADY ACHIEVED" << endl;
        reportFile << setw(16) << left  << "C" << setw(23) << GRADE_C << "ALREADY ACHIEVED" << endl;
    }else if(CWMark[count] >= GRADE_C){
        reportFile << setw(16) << left  << "C+" << setw(23) << GRADE_C_PLUS << setw(5) << right << predictor (CWMark[count], GRADE_C_PLUS) << endl;
        reportFile << setw(16) << left  << "C" << setw(23) << GRADE_C << "ALREADY ACHIEVED" << endl;
    }else{
        reportFile << setw(16) << left  << "C+" << setw(23) << GRADE_C_PLUS << setw(5) << right << predictor (CWMark[count], GRADE_C_PLUS) << endl;
        reportFile << setw(16) << left  << "C" << setw(23) << GRADE_C << setw(5) << right << predictor (CWMark[count], GRADE_C) << endl;
    }

    reportFile << endl;

    reportFile << "-----------------------------------------------------------------------------------" << endl;
    reportFile << "PERFORMANCE STATUS" << endl;
    reportFile << "-----------------------------------------------------------------------------------" << endl;

    reportFile << left << setw(18) << "Current Standing" << " : ";
    if (CWMark[count]>=45){
        reportFile << "Excellent";
    }else if (CWMark[count]>=40){
        reportFile << "Very Good";
    }else if (CWMark[count]>=35){
        reportFile << "Good";
    }else if (CWMark[count]>=25){
        reportFile << "Pass";
    }else{
        reportFile << "Needs Improvement";
    }
    reportFile << endl;

    reportFile << setw(18) << "Risk Category" << " : ";
    if (CWMark[count]>=40){
        reportFile << "Low Risk";
    }else if (CWMark[count]>=30){
        reportFile << "Moderate Risk";
    }else if (CWMark[count]>=20){
        reportFile << "High Risk";
    }else{
        reportFile << "Very High Risk";
    }
    reportFile << endl << endl;

    reportFile << "Remarks:" << endl;
    if (CWMark[count]>=46){
        reportFile << "Excellent work! You are performing exceptionally well in the coursework component." << endl;
        reportFile << "Securing a pass or a grade C+ is already guaranteed based on your current coursework performance." << endl;
        reportFile << "Keep up the excellent work and aim for an even higher final grade!" << endl;
    }else if (CWMark[count]>=40){
        reportFile << "You are performing well in the coursework component. Securing a pass" << endl;
        reportFile << "or a grade C is already guaranteed based on your current coursework" << endl;
        reportFile << "performance." << endl;
    }else if (CWMark[count]>=30){
        reportFile << "Your coursework performance is satisfactory, but there is still room for improvement." << endl;
        reportFile << "You should strengthen your understanding of the course content and dedicate more time" << endl;
        reportFile << "to revision to increase your chances of achieving a passing grade" << endl;
    }else if (CWMark[count]>=20){
        reportFile << "Your current coursework performance is below the desired level. Your may face difficulties" << endl;
        reportFile << "achieving a passing grade if your performance does not improve. Seek guidance from your" << endl;
        reportFile << "lecturer, identify your weak areas, and work on improving them before the final examination." << endl;
    }else{
        reportFile << "Your current coursework performance indicates a significant risk of failing the course." << endl;
        reportFile << "Immediate improvement is strongly recommended. Seek academic support from your lecturer," << endl;
        reportFile << "revisit the fundamental concepts, and dedicate more time to preparation for the final" << endl;
        reportFile << "examination." << endl;
    }

    reportFile << endl;

    reportFile << "===================================================================================" << endl;

    reportFile.close();
}