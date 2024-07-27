#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class Student {
private:
    string name, roll_no, course, address, email_id, contact_no;

public:
    void menu();
    void insert();
    void display();
    void modify();
    void search();
    void deleted();
};

void Student::menu() {
    while (true) {
        string username = "student", password = "password";
        string user, pass;

        cout << "USERNAME: ";
        getline(cin, user);
        cout << "PASSWORD: ";
        getline(cin, pass);

        if (username == user && password == pass) {
            break;
        } else {
            cout << "Incorrect username or password. Try again.\n";
        }
    }

    while (true) {
        int choice;
        cout << "\n\t\t\t-----------------------------" << endl;
        cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM |" << endl;
        cout << "\t\t\t-----------------------------" << endl;
        cout << "\t\t\t 1. Enter New Record" << endl;
        cout << "\t\t\t 2. Display Record" << endl;
        cout << "\t\t\t 3. Modify Record" << endl;
        cout << "\t\t\t 4. Search Record" << endl;
        cout << "\t\t\t 5. Delete Record" << endl;
        cout << "\t\t\t 6. Exit" << endl;

        cout << "\t\t\t---------------------------" << endl;
        cout << "\t\t\tChoose Option:[1/2/3/4/5/6]" << endl;
        cout << "\t\t\t---------------------------" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (choice) {
            case 1: {
                char x;
                do {
                    insert();
                    cout << "\n\t\t\t Add Another Student Record (Y/N): ";
                    cin >> x;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n')
                    ; // Ignore newline character
                } while (x == 'y' || x == 'Y');
                break;
            }
            case 2:
                display();
                break;
            case 3:
                modify();
                break;
            case 4:
                search();
                break;
            case 5:
                deleted();
                break;
            case 6:
                return;
            default:
                cout << "\n\t\t\t Invalid choice... Please Try Again..";
        }
    }
}

void Student::insert() {
    fstream file;
    cout << "\n-----------------------------------------------------------------------------------------------------";
    cout << "\n------------------------------------- Add Student Details ---------------------------------------------" << endl;
    
    cout << "\t\t\tEnter Name: ";
    getline(cin, name);
    cout << "\t\t\tEnter Roll No.: ";
    getline(cin, roll_no);
    cout << "\t\t\tEnter Course: ";
    getline(cin, course);
    cout << "\t\t\tEnter Email Id: ";
    getline(cin, email_id);
    cout << "\t\t\tEnter Contact No: ";
    getline(cin, contact_no);
    cout << "\t\t\tEnter Address: ";
    getline(cin, address);

    file.open("studentRecord.txt", ios::app);
    if (file.is_open()) {
        file << name << " " << roll_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
        file.close();
    } else {
        cout << "Unable to open file.\n";
    }
}

void Student::display() {
    fstream file;
    int total = 1;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Student Record Table --------------------------------------------" << endl;
    file.open("studentRecord.txt", ios::in);
    if (!file) {
        cout << "\n\t\t\tNo Data Is Present...";
    } else {
        while (file >> name >> roll_no >> course >> email_id >> contact_no >> address) {
            cout << "\n\n\t\t\t Student No.: " << total++ << endl;
            cout << "\t\t\t Student Name: " << name << endl;
            cout << "\t\t\t Student Roll No.: " << roll_no << endl;
            cout << "\t\t\t Student Course: " << course << endl;
            cout << "\t\t\t Student Email Id.: " << email_id << endl;
            cout << "\t\t\t Student Contact No.: " << contact_no << endl;
            cout << "\t\t\t Student Address: " << address << endl;
        }
        file.close();
    }
}

void Student::modify() {
    fstream file, file1;
    string rollno;
    int found = 0;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Student Modify Details ------------------------------------------" << endl;
    file.open("studentRecord.txt", ios::in);
    if (!file) {
        cout << "\n\t\t\tNo Data is Present..";
    } else {
        cout << "\nEnter Roll No. of Student which you want to Modify: ";
        getline(cin, rollno);
        file1.open("temp.txt", ios::app | ios::out);
        while (file >> name >> roll_no >> course >> email_id >> contact_no >> address) {
            if (rollno == roll_no) {
                cout << "\n\t\t\tCurrent Details:" << endl;
                cout << "\t\t\tName: " << name << endl;
                cout << "\t\t\tRoll No.: " << roll_no << endl;
                cout << "\t\t\tCourse: " << course << endl;
                cout << "\t\t\tEmail Id: " << email_id << endl;
                cout << "\t\t\tContact No: " << contact_no << endl;
                cout << "\t\t\tAddress: " << address << endl;

                cout << "\n\t\t\tEnter New Details (Leave blank to keep current value):" << endl;

                string newName, newRollNo, newCourse, newEmail, newContact, newAddress;
                
                cout << "\t\t\tEnter Name: ";
                getline(cin, newName);
                if (!newName.empty()) name = newName;

                cout << "\t\t\tEnter Roll No.: ";
                getline(cin, newRollNo);
                if (!newRollNo.empty()) roll_no = newRollNo;

                cout << "\t\t\tEnter Course: ";
                getline(cin, newCourse);
                if (!newCourse.empty()) course = newCourse;

                cout << "\t\t\tEnter Email Id: ";
                getline(cin, newEmail);
                if (!newEmail.empty()) email_id = newEmail;

                cout << "\t\t\tEnter Contact No: ";
                getline(cin, newContact);
                if (!newContact.empty()) contact_no = newContact;

                cout << "\t\t\tEnter Address: ";
                getline(cin, newAddress);
                if (!newAddress.empty()) address = newAddress;

                found = 1;
            }
            file1 << name << " " << roll_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
        }
        if (found == 0) {
            cout << "\n\n\t\t\t Student Roll No. Not Found....";
        }
        file1.close();
        file.close();
        remove("studentRecord.txt");
        rename("temp.txt", "studentRecord.txt");
    }
}

void Student::search() {
    fstream file;
    int found = 0;
    file.open("studentRecord.txt", ios::in);
    if (!file) {
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Student Search Data ------------------------------------------" << endl;
        cout << "\n\t\t\t No Data Is Present...";
    } else {
        string rollno;
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Student Search Data ------------------------------------------" << endl;
        cout << "\n Enter Roll No. of Student Which You Want to Search: ";
        getline(cin, rollno);
        while (file >> name >> roll_no >> course >> email_id >> contact_no >> address) {
            if (rollno == roll_no) {
                cout << "\n\t\t\t Student Name: " << name << endl;
                cout << "\t\t\t Student Roll No.: " << roll_no << endl;
                cout << "\t\t\t Student Course: " << course << endl;
                cout << "\t\t\t Student Email Id.: " << email_id << endl;
                cout << "\t\t\t Student Contact No.: " << contact_no << endl;
                cout << "\t\t\t Student Address: " << address << endl;
                found++;
            }
        }
        if (found == 0) {
            cout << "\n\t\t\tStudent Roll No. Not Found...";
        }
        file.close();
    }
}

void Student::deleted() {
    fstream file, file1;
    int found = 0;
    string roll;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Delete Student Details ------------------------------------------" << endl;
    file.open("studentRecord.txt", ios::in);
    if (!file) {
        cout << "\n\t\t\tNo Data is Present..";
    } else {
        cout << "\nEnter Roll No. of Student which you want Delete Data: ";
        getline(cin, roll);
        file1.open("temp.txt", ios::app | ios::out);
        while (file >> name >> roll_no >> course >> email_id >> contact_no >> address) {
            if (roll != roll_no) {
                file1 << name << " " << roll_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
            } else {
                found++;
                cout << "\n\t\t\tSuccessfully Deleted Data";
            }
        }
        if (found == 0) {
            cout << "\n\t\t\t Student Roll No. Not Found....";
        }
        file1.close();
        file.close();
        remove("studentRecord.txt");
        rename("temp.txt", "studentRecord.txt");
    }
}

int main() {
    Student project;
    project.menu();
    return 0;
}
