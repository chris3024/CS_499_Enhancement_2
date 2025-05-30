# CS-499: Enhancement 2

[![MSBuild](https://github.com/chris3024/CS_499_Enhancement_2/actions/workflows/msbuild.yml/badge.svg)](https://github.com/chris3024/CS_499_Enhancement_2/actions/workflows/msbuild.yml)
[![CodeQL](https://github.com/chris3024/CS_499_Enhancement_2/actions/workflows/codeql.yml/badge.svg)](https://github.com/chris3024/CS_499_Enhancement_2/actions/workflows/codeql.yml)
___

This codebase holds the enhanced application from CS-300: Data Structures and Algorithms, Analysis and Design. The original code consisted of a console-based application that loaded a selected CSV file, entered by the user, into a data structure. This then allowed the user to output the loaded data in alphanumeric order, while also allowing the user to search for a specific course and return that course name and any required prerequisites. In this improved codebase, we have replaced the existing data structure, a vector, with an AVL tree. This allows us faster searches, sorted access, and faster prerequisite checks, as shown in the table below: 

Operation | Vector | AVL Tree 
--- | --- | ---
Sorted Printing | O(n log n) | O(n)
Search and Print Prereqs | O(k*n) | O(k log n)
<sub>k = number of prerequisites</sub>

___

Main Menu | Loading File
--- | ---
<img src="screenshots/Screenshot 2025-05-26 095451.png" alt="Menu System" width="557" /> | <img src="screenshots/Screenshot 2025-05-26 095506.png" alt="Loading File" width="557" />

Printing Courses (Alphanumerical) | Search Course / Return Prerequisites
--- | ---
<img src="screenshots/Screenshot 2025-05-26 095516.png" alt="Printed Courses - Alphanumerical" width="557" /> | <img src="screenshots/Screenshot 2025-05-26 095530.png" alt="Printed Course and Prereqs" width="557" />

___

## Installation Instructions

#### Prerequisites
  * <a href="https://visualstudio.microsoft.com/">Visual Studio 2022 or newer</a>

1. Clone Repository
   ```bash
   git clone https://github.com/chris3024/CS_499_Enhancement_2.git
   ```
   Manual Download
     * Click the green Code button
     * Select Download ZIP
     * Extract to a directory of your choice
       
2. Open the Project
   * Launch Visual Studio
   * Click File -> Open -> Project/Solution
   * Navigate to the cloned/extracted directory
   * Open the ```.sln``` (solution) file

3. Build the Project
   * Set the desired build configuration
       * ```Debug``` or ```Release```
       * ```x86``` or ```x64```
   * Click Build -> Build Solution

4. Run the application
   * Press F5 or click the Start button in Visual Studio to run the program

___

## Usage

1. Load Data Structure
   * Choose option ```1```
   * Enter full CSV filename (```ABCU_Test.csv```)
     
2. Print Course List
   * After the data structure is loaded:
     *  Choose option ```2```
     *  Display all loaded courses in sorted order

3. Print Course Information
   * After the data structure is loaded:
     * Choose option ```3```
     * Enter Course ID
     * Displays course name and prerequisites

4. Quit
   * Choose option ```9```

