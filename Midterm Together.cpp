//This cpp file is all the classes and code in one file as I do get errors in the other files that I am unable to figure out but works in other instances

//Student Records

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

//Class Grade
class Grades {
private:

    string subject;
    char grade;

public:
    //Construtor
    Grades(string subject, char grade) {
        subject = subject;
        grade = grade;

    }
    //Functions

    //Getter
    string getSubject() const {
        return subject;
    }

    //Setter
    void setSubject(string subject) {
        subject = subject;
    }


    //Getter
    char getGrade() const {
        return grade;
    }

    //Setter 
    void setGrade(char grade) {
        grade = grade;
    }


};

//Class Student
class Student {
private:
    string name;
    string id;
    vector <Grades> grades;

public:
    //Constuctors
    Student(string n, string i, vector <Grades>& g) {
        name = n;
        id = i;
        grades = g;
    }

    Student(string n, string i) {
        name = n;
        id = i;
    }
    //Functions
    void addSubject(string subject, char grade) {
        grades.push_back(Grades(subject, grade));
    }

    void removeSubject(string subject) {
        for (size_t i = 0; i < grades.size(); ) {
            if (grades[i].getSubject() == subject) {
                grades.erase(grades.begin() + i);
            }
            else {
                ++i;
            }
        }
    }


    void updateGrade(string subject, char grade) {
        for (Grades& g : grades) {
            if (g.getSubject() == subject) {
                g.setGrade(grade);
                break;
            }
        }
    }
    //Getters and Setters
    string getName() const {
        return name;
    }
    void setName(string n) {
        name = n;
    }

    string getID() const {
        return id;
    }
    void setID(string i) {
        id = i;
    }


    const vector<Grades> getGrades() const {
        return grades;
    }


};

//Class Student Database
class studentDatabase {

private:
    vector <Student> students;

public:
    //Functions
    void addStudent(Student student) {
        students.push_back(student);
    }


    void updateGradeDetails(const string& studentID, const string& subject, char grade) {
        for (Student& s : students) {
            if (s.getID() == studentID) {
                s.updateGrade(subject, grade);
                break;
            }
        }
    }

    void displayStudentRecords()
        const {
        for (const auto& student : students) { //auto& is very useful, let's me not worry about type 
            cout << "Name: " << student.getName() << " ID: " << student.getID() << endl;
            const vector<Grades>& grades = student.getGrades();
            cout << "Grades:\n";
            for (const auto& grade : grades) {
                cout << "  Subject: " << grade.getSubject() << " Grade: " << grade.getGrade() << endl;
            }
        }
    }


    const Student* findStudentByID(const string& studentID) const {
        for (const auto& student : students) {
            if (student.getID() == studentID) {
                return &student;
            }
        }
        return nullptr;
    }

    double calculateAverageGPA() const {
        double totalGPA = 0.0;
        int totalStudents = 0;
        for (const auto& student : students) {
            const vector<Grades>& grades = student.getGrades();
            double studentGPA = 0.0;
            for (const auto& grade : grades) {
                // Assigning a numerical value to grades (A=4, B=3, C=2, D=1, F=0)
                switch (grade.getGrade()) {
                case 'A': studentGPA += 4.0; break;
                case 'B': studentGPA += 3.0; break;
                case 'C': studentGPA += 2.0; break;
                case 'D': studentGPA += 1.0; break;
                case 'F': studentGPA += 0.0; break;
                }
            }
            totalGPA += studentGPA / grades.size();
            totalStudents++;
        }
        if (totalStudents > 0) {
            return totalGPA / totalStudents;
        }
        return 0.0; // No students in the database
    }

    double calculateStudentGPA(const Student& student) const {
        const vector<Grades>& grades = student.getGrades();
        double studentGPA = 0.0;
        for (const auto& grade : grades) {
            // Assigning a numerical value to grades (A=4, B=3, C=2, D=1, F=0)
            switch (grade.getGrade()) {
            case 'A': studentGPA += 4.0; break;
            case 'B': studentGPA += 3.0; break;
            case 'C': studentGPA += 2.0; break;
            case 'D': studentGPA += 1.0; break;
            case 'F': studentGPA += 0.0; break;
            }
        }
        if (!grades.empty()) {
            return studentGPA / grades.size();
        }
        return 0.0; // No grades for the student
    }
};

// Helper function to validate grade input
bool isValidGrade(char grade) {
    return (grade == 'A' || grade == 'B' || grade == 'C' || grade == 'D' || grade == 'F');
};
int main() {
    studentDatabase database;

    while (true) {
        cout << "\nStudent Record System Menu:\n";
        cout << "1. Add Student\n";
        cout << "2. Update Student Grades\n";
        cout << "3. Display All Students\n";
        cout << "4. Search for Student by ID\n";
        cout << "5. Calculate Average GPA\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
        {
            string name, id;
            cout << "Enter student name: ";
            cin.ignore(); // Clear newline character from previous input
            getline(cin, name);
            cout << "Enter student ID: ";
            cin >> id;

            Student student(name, id);
            database.addStudent(student);

            int subChoice;
            do {
                string subject;
                char grade;

                cout << "Enter subject name: ";
                cin.ignore(); // Clear newline character from previous input
                getline(cin, subject);

                do {
                    cout << "Enter grade (A, B, C, D, F): ";
                    cin >> grade;
                } while (!isValidGrade(grade));

                student.addSubject(subject, grade);

                cout << "Do you want to add another subject? (1 for yes, 0 for no): ";
                cin >> subChoice;
            } while (subChoice == 1);

            break;
        }

        case 2:
        {
            string studentID, subject;
            char grade;

            cout << "Enter student ID: ";
            cin >> studentID;

            const Student* foundStudent = database.findStudentByID(studentID);
            if (foundStudent == nullptr) {
                cout << "Student with ID " << studentID << " not found." << endl;
            }
            else {
                cout << "Enter the subject you want to update: ";
                cin.ignore(); // Clear newline character from previous input
                getline(cin, subject);

                do {
                    cout << "Enter the updated grade (A, B, C, D, F): ";
                    cin >> grade;
                } while (!isValidGrade(grade));

                database.updateGradeDetails(studentID, subject, grade);
                cout << "Grade updated successfully." << endl;
            }

            break;
        }

        case 3:
            database.displayStudentRecords();
            break;

        case 4:
        {
            string studentID;
            cout << "Enter student ID to search: ";
            cin >> studentID;

            const Student* foundStudent = database.findStudentByID(studentID);
            if (foundStudent == nullptr) {
                cout << "Student with ID " << studentID << " not found." << endl;
            }
            else {
                cout << "Student found!\n";
                cout << "Name: " << foundStudent->getName() << " ID: " << foundStudent->getID() << endl;
                const vector<Grades>& grades = foundStudent->getGrades();
                cout << "Grades:\n";
                for (const auto& grade : grades) {
                    cout << "  Subject: " << grade.getSubject() << " Grade: " << grade.getGrade() << endl;
                }
            }

            break;
        }

        case 5:
            cout << "Average GPA for all students: " << database.calculateAverageGPA() << endl;
            break;

        case 6:
            cout << "Exiting the program. Goodbye!" << endl;
            return 0;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            break;
        }
    }

    return 0;
}