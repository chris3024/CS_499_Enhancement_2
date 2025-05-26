/* CS-499: Enhancement 2
*  Developer: Christopher Sharp
*  Date: 05/31/2025
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <filesystem>

using namespace std;

struct CourseData {
    string courseID;
    string courseName;
    vector<string> preReqNames;
};

static string convertCase(const string& userCourseID) {
    string results;
    for (char c : userCourseID) {
        results += toupper(c);
    }
    return results;
}

/*
* Original AVL tree code gathered from: https://www.wscubetech.com/resources/dsa/avl-tree,
* then reworked to better fit this project
*/
class AVLTree {
private:

    // Internal node structure
    struct Node {
        CourseData data;
        Node* left;
        Node* right;
        int height;
        Node(CourseData d) : data(d), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root = nullptr;

     
    
    // Returns the height of the node, if nullptr, height = 0
    int height(Node* n) {
        if (n == nullptr)
            return 0;
        return n->height;
    }

    // Update node height based on max height of left/right subtrees
    void updateHeight(Node* n) {
        n->height = 1 + max(height(n->left), height(n->right));
    }

    // Calculate node balance factor (left height - right height)
    int balanceFactor(Node* n) {
        if (n == nullptr)
            return 0;
        return height(n->left) - height(n->right);
    }

    // Left rotation to fix right-heavy imbalance
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // Right rotation to fix left-heavy imbalance
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // Inserts the data, then checks the balance and performs rotations if needed
    Node* insert(Node* node, CourseData course) {
        if (node == nullptr) 
            return new Node(course);

        if (course.courseID < node->data.courseID)
            node->left = insert(node->left, course);
        else
            node->right = insert(node->right, course);

        updateHeight(node);
        int balance = balanceFactor(node);

        if (balance > 1 && course.courseID < node->left->data.courseID)
            return rotateRight(node);
        if (balance < -1 && course.courseID > node->right->data.courseID)
            return rotateLeft(node);
        if (balance > 1 && course.courseID > node->left->data.courseID) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && course.courseID < node->right->data.courseID) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Traverses the tree returning the data inOrder
    void inOrder(Node* node) {
        if (node == nullptr)
            return;
        inOrder(node->left);
        cout << node->data.courseID << ", " << node->data.courseName << endl;
        inOrder(node->right);
    }

    // Searches for the given course
    const CourseData* search(Node* node, const string& courseID) const {
        if (!node) return nullptr;
        if (courseID == node->data.courseID) return &node->data;
        if (courseID < node->data.courseID) return search(node->left, courseID);
        return search(node->right, courseID);
    }

public:
    void insert(CourseData course) {
        root = insert(root, course);
    }

    void printInOrder() {
        inOrder(root);
    }

    const CourseData* find(const string& courseID) const {
        return search(root, courseID);
    }
};

// Parse CSV and insert into AVL tree
static void loadCoursesFromFile(const string& fileName, AVLTree& tree) {
    ifstream file(fileName);
    string line;
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + fileName);
    }

    while (getline(file, line)) {
        CourseData course;
        vector<string> tokens;
        istringstream iss(line);
        string token;

        while (getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) continue;
        course.courseID = convertCase(tokens[0]);
        course.courseName = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            course.preReqNames.push_back(tokens[i]);
        }

        tree.insert(course);
    }
    file.close();
}

// Search AVL tree for a course and print its prerequisites
static void printCourseInfo(const AVLTree& tree, const string& courseID)  {
    const CourseData* course = tree.find(convertCase(courseID));
    if (!course) {
        cout << "Course not found.\n";
        return;
    }
    cout << course->courseID << ", " << course->courseName << "\nPrerequisites: ";
    if (course->preReqNames.empty()) {
        cout << "None";
    }
    else {
        for (size_t i = 0; i < course->preReqNames.size(); ++i) {
            cout << course->preReqNames[i];
            if (i != course->preReqNames.size() - 1) cout << ", ";
        }
    }
    cout << endl;
}

/* Main application entry point
*  Runs the user interface and handles menu interactions
*/ 
int main() {
    AVLTree courseTree;
    int choice = 0;
    string fileName;
    string courseID;

    while (choice != 9) {
        try {
            cout << "\nMenu:\n";
            cout << "1. Load Data Structure\n";
            cout << "2. Print Course List\n";
            cout << "3. Print Course Information\n";
            cout << "9. Quit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw runtime_error("Invalid input. Please enter a number.");
            }

            switch (choice) {
            case 1:
                cout << "Enter file name: ";
                cin >> fileName;
                loadCoursesFromFile(fileName, courseTree);
                cout << "Courses loaded successfully.\n";
                break;
            case 2:
                courseTree.printInOrder();
                break;
            case 3:
                cout << "Enter course ID: ";
                cin >> courseID;
                printCourseInfo(courseTree, courseID);
                break;
            case 9:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid menu option.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}


