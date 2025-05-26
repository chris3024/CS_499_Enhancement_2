# CS-499: Enhancement 2

[![MSBuild](https://github.com/chris3024/CS_499_Enhancement_2/actions/workflows/msbuild.yml/badge.svg)](https://github.com/chris3024/CS_499_Enhancement_2/actions/workflows/msbuild.yml)
___

This codebase holds the enhanced application from CS-300: Data Structures and Algorithms, Analysis and Design. The original code consisted of a console-based application that loaded a selected CSV file, entered by the user, into a data structure. This then allowed the user to output the loaded data in alphanumeric order, while also allowing the user to search for a specific course and return that course name and any required prerequisites. In this improved codebase, we have replaced the existing data structure, a vector, with an AVL tree. This allows us faster searches, sorted access, and faster prerequisite checks, as shown in the table below: 

Operation | Vector | AVL Tree 
--- | --- | ---
Sorted Printing | O(n log n) | O(n)
Search and Print Prereqs | O(k*n) | O(k log n)

<sub>k = number of prerequisites</sub>
