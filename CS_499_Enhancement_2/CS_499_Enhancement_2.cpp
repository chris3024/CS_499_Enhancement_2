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
#include <memory>

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
        unique_ptr<Node> left;
        unique_ptr<Node> right;
        int height;
        Node(const CourseData& d)
            : data(d), left(nullptr), right(nullptr), height(1) {
        }
    };

    unique_ptr<Node> root = nullptr;

    // Returns the height of the node, if nullptr, height = 0
    int height(Node* n) {
        return n ? n->height : 0;
    }

    // Update node height based on max height of left/right subtrees
    void updateHeight(Node* n) {
        n->height = 1 + max(height(n->left.get()), height(n->right.get()));
    }

    // Calculate node balance factor (left height - right height)
    int balanceFactor(Node* n) {
        return n ? height(n->left.get()) - height(n->right.get()) : 0;
    }

    // Left rotation to fix right-heavy imbalance
    unique_ptr<Node> rotateLeft(unique_ptr<Node> x) {
        auto y = move(x->right);
        x->right = move(y->left);
        y->left = move(x);
        updateHeight(y->left.get());
        updateHeight(y.get());
        return y;
    }

    // Right rotation to fix left-heavy imbalance
    unique_ptr<Node> rotateRight(unique_ptr<Node> y) {
        auto x = move(y->left);
        y->left = move(x->right);
        x->right = move(y);
        updateHeight(x->right.get());
        updateHeight(x.get());
        return x;
    }

    // Inserts the data, then checks the balance and performs rotations if needed
    unique_ptr<Node> insert(unique_ptr<Node> node, const CourseData& course) {
        if (!node) {
            return make_unique<Node>(course);
        }

        if (course.courseID < node->data.courseID) {
            node->left = insert(move(node->left), course);
        }
        else {
            node->right = insert(move(node->right), course);
        }

        updateHeight(node.get());

        int balance = balanceFactor(node.get());

        if (balance > 1 && course.courseID < node->left->data.courseID) {
            return rotateRight(move(node));
        }
            
        if (balance < -1 && course.courseID > node->right->data.courseID) {
            return rotateLeft(move(node));
        }
            
        if (balance > 1 && course.courseID > node->left->data.courseID) {
            node->left = rotateLeft(move(node->left));
            return rotateRight(move(node));
        }

        if (balance < -1 && course.courseID < node->right->data.courseID) {
            node->right = rotateRight(move(node->right));
            return rotateLeft(move(node));
        }

        return node;
    }

    // Traverses the tree returning the data inOrder
    void inOrder(Node* node) const {
        if (!node) { return; }
        inOrder(node->left.get());
        cout << node->data.courseID << ", " << node->data.courseName << endl;
        inOrder(node->right.get());
    }

    // Searches for the given course
    const CourseData* search(Node* node, const string& courseID) const {
        if (!node) { 
            return nullptr; 
        }

        if (courseID == node->data.courseID) { 
            return &node->data; 
        }

        if (courseID < node->data.courseID) {
            return search(node->left.get(), courseID);
        }
        else {
            return search(node->right.get(), courseID);
        }
    }

public:
    
    void insert(CourseData course) {
        root = insert(move(root), course);
    }

    void printInOrder() const {
        inOrder(root.get());
    }

    const CourseData* find(const string& courseID) const {
        return search(root.get(), courseID);
    }
};

// Parse CSV and insert into AVL tree
static void loadCoursesFromFile(const string& fileName, AVLTree& tree) {
    ifstream file(fileName);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + fileName);
    }

    string line;
    while (getline(file, line)) {
        CourseData course;
        vector<string> tokens;
        istringstream iss(line);
        string token;

        while (getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) { 
            continue; 
        }
        course.courseID = convertCase(tokens[0]);
        course.courseName = tokens[1];
        for (size_t i = 2; i < tokens.size(); ++i) {
            course.preReqNames.push_back(tokens[i]);
        }

        tree.insert(course);
    }
}

// Search AVL tree for a course and print its prerequisites
static void printCourseInfo(const AVLTree& tree, const string& courseID) {
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
            if (i + 1 < course->preReqNames.size()) cout << ", ";
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
            cout << "\nMenu:\n"
                << "1. Load Data Structure\n"
                << "2. Print Course List\n"
                << "3. Print Course Information\n"
                << "9. Quit\n"
                << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Invalid input. Please enter a number.");
            }

            switch (choice) {
            case 1:
                cout << "Enter CSV file name (Making sure to add .csv to end of name): ";
                getline(cin >> ws, fileName);
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
