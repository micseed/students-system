#include <iostream>
using namespace std;

struct Student {
    string s_fname;
    string s_lname;
    string s_course;
    int s_ID;
    float s_gpa;
};

void resizeArray(Student *&students, int &s_memory);
void addStudents (Student *&students, int &s_size, int &s_memory);
void editStudents(Student *students, int s_size);
void deleteStudents (Student *&students, int &s_size);
void viewStudents(Student *students, int s_size);
void displayStudent(const Student &s);

int main(){
    int s_size = 0;
    int s_memory = 5;
    Student *students = new Student[s_memory];

    int choice;
    do{
        cout << "\n-----Menu-----\n";
        cout << "\n[1] Add Student\n";
        cout << "\n[2] Edit Student\n";
        cout << "\n[3] Delete Student\n";
        cout << "\n[4] View Student\n";
        cout << "\n[5] Exit Program\n";
        cout << "\nSelect option: ";
        cin >> choice;

        system("cls");

        switch(choice){
        case 1: addStudents (students, s_size, s_memory); break;
        case 2: editStudents (students, s_size); break;
        case 3: deleteStudents (students, s_size); break;
        case 4: viewStudents (students, s_size); break;
        case 5: cout << "Exiting System...\n"; break;
        default: cout << "Invalid choice. Please try again!\n";
        }
    } while (choice!=5);

    delete[] students;

    return 0;
}

void addStudents (Student *&students, int &s_size, int &s_memory){
    if (s_size == s_memory){
        resizeArray(students, s_memory);
    }

    Student s;
    cout << "\nEnter Student ID: ";
    cin >> s.s_ID;

    while (s.s_ID < 0) {
        cout << "Enter a positive number!\n";
        cout << "Enter again: ";
        cin >> s.s_ID;
    }

    for(int i = 0; i < s_size; i++){
        while(students[i].s_ID == s.s_ID){
            cout << "Student ID already exists! Please enter another Student ID and try again.\n";
            cout << "Enter again: ";
            cin >> s.s_ID;
        }
    }

    cin.ignore();
    cout << "Enter Student's First Name: ";
    getline(cin, s.s_fname);
    cout << "Enter Student's Last Name: ";
    getline(cin, s.s_lname);

    for (int i = 0; i < s_size; i++) {
        if (students[i].s_fname == s.s_fname && students[i].s_lname == s.s_lname) {
            cout << "A student with the same name already exists! Please enter different details.\n";
            cout << "Redirecting to menu...\n";
            return;
        }
    }

    cout << "Enter Student's Course: ";
    getline(cin, s.s_course);
    cout << "Enter Student's previous semestral GPA: ";
    cin >> s.s_gpa;

    while (s.s_gpa < 0) {
        cout << "Enter a positive number!\n";
        cout << "Enter again: ";
        cin >> s.s_gpa;
    }

    students[s_size++] = s;
    cout << "Student is added successfully.\n";
}

void editStudents(Student *students, int s_size){
    if (s_size ==0){
        cout << "No Record!\n";
        return;
    }

    int searchID;
    cout << "\nEnter Student ID to edit: ";
    cin >> searchID;

    while (searchID < 0) {
        cout << "Enter a positive number!\n";
        cout << "Enter again: ";
        cin >> searchID;
    }

    for (int i = 0; i < s_size; i++){
        if(students[i].s_ID == searchID) {
            cout << "Student Data: \n";
            displayStudent(students[i]);

            cin.ignore();
            cout << "Edit Student Data\n";
            cout << "Enter [new] Student's First Name: ";
            getline(cin, students[i].s_fname);
            cout << "Enter [new] Student's Last Name: ";
            getline(cin, students[i].s_lname);
            cout << "Enter [new] Student's Course: ";
            getline(cin, students[i].s_course);
            cout << "Enter [new] Student's previous semestral GPA: ";
            cin >> students[i].s_gpa;

           while (students[i].s_gpa < 0) {
                cout << "Enter a positive number!\n";
                cout << "Enter again: ";
                cin >> students[i].s_gpa;
            }

            cout << "The student record was updated successfully!\n";
            return;
        }
    }
    cout << "Student was not in the system!\n";
}

void deleteStudents (Student *&students, int &s_size){
    if (s_size ==0){
        cout << "No Record!\n";
        return;
    }

    int searchID;
    cout << "\nEnter Student's ID to delete: ";
    cin >> searchID;

    while (searchID < 0) {
        cout << "Enter a positive number!\n";
        cout << "Enter again: ";
        cin >> searchID;
    }

    int index = -1;
    for (int i = 0; i < s_size; i++){
        if(students[i].s_ID == searchID){
            index = i;
            break;
    }
}
    if (index == -1){
        cout << "The system did not found the student!\n";
        return;
    }

    cout << "Deleting student record: \n";
    displayStudent(students[index]);

    for (int i = index; i < s_size -1; i++){
        students[i] = students[i+1];
    }
    s_size--;

    cout << "Student's record was deleted successfully!\n";

}

void viewStudents(Student *students, int s_size){
    if (s_size == 0){
        cout << "No student information recorded!\n";
        return;
    }

    cout << "\nSelect Viewing Options\n";
    cout << "[1] Alphabetically\n";
    cout << "[2] GPA\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    while (choice < 0) {
        cout << "Enter a positive number!\n";
        cout << "Enter again: ";
        cin >> choice;
    }

    Student *sortedStudents = new Student[s_size];
    for (int i = 0; i < s_size; i++) {
        sortedStudents[i] = students[i];
    }

    for (int i = 0; i < s_size - 1; i++) {
        for (int j = 0; j < s_size - i - 1; j++) {
            bool swapCondition = false;
            if (choice == 1) {
                if (sortedStudents[j].s_lname > sortedStudents[j + 1].s_lname) {
                    swapCondition = true;
                }
            } else if (choice == 2) {
                if (sortedStudents[j].s_gpa > sortedStudents[j + 1].s_gpa) {
                    swapCondition = true;
                }
            }

            if (swapCondition) {
                Student temp = sortedStudents[j];
                sortedStudents[j] = sortedStudents[j + 1];
                sortedStudents[j + 1] = temp;
            }
        }
    }

    cout << "\nStudents Records\n";
    cout << "-----------------------------------------------------------\n";
    cout << "ID\tFirst Name\tLast Name\tCourse\t\tGPA\n";
    cout << "-----------------------------------------------------------\n";
    for (int i = 0; i < s_size; i++) {
        cout << sortedStudents[i].s_ID << "\t"
             << sortedStudents[i].s_fname << "\t" << "\t"
             << sortedStudents[i].s_lname << "\t" << "\t"
             << sortedStudents[i].s_course << "\t" << "\t"
             << sortedStudents[i].s_gpa << endl;
    }


    delete[] sortedStudents;
}

void resizeArray(Student *&students, int &s_memory){
    int newMemory = s_memory * 2;
    Student *newStudents = new Student[newMemory];

    for (int i = 0; i < s_memory;i++){
        newStudents[i] = students[i];
    }

    delete[] students;
    students = newStudents;
    s_memory = newMemory;
}

void displayStudent(const Student &s){
    cout << "\nID: " << s.s_ID << "\nName: " << s.s_fname << " " << s.s_lname
        << "\nCourse: " << s.s_course << "\nGPA: " << s.s_gpa << endl;
}


