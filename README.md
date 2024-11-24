# Flight Data Manager Application

A lightweight and platform-independent application built using **Qt**, designed to manage flight data stored in CSV format. This application features core functionalities like sorting, JSON generation, and database creation without requiring external dependencies. It runs seamlessly on any machine with Qt installed.

---

## Table of Contents

1. [Tasks Assigned](#tasks-assigned)  
2. [Features](#features)  
3. [Application Structure](#application-structure)  
   - [FlightData.h](#1-flightdatah)  
   - [MainWindow.h](#2-mainwindowh)  
4. [Execution Flow](#execution-flow)  
5. [Key Benefits](#key-benefits)  
6. [Demo](#demo)  
7. [How to Run the Application](#how-to-run-the-application)  

---

## Tasks Assigned

Tasks assigned can be found in the image below:

![Tasks Assigned](https://github.com/user-attachments/assets/d668a464-f9d4-48b7-aa7c-751301b9807e)

---

## Features

1. **CSV File Reading**  
   - Reads a CSV file containing flight data from the `data` folder.  
   - The file is loaded into a vector of `FlightData` objects using the `FlightData.h` class.

2. **Load Button**  
   - Displays the loaded data in the application for review.

3. **Sort Button**  
   - Sorts the flight data by time. Sorting logic ensures efficient handling of data for accurate results.

4. **JSON Button**  
   - Converts the sorted flight data into a JSON file for easy integration and future use.

5. **Database Button**  
   - Creates a database from the sorted flight data, ensuring structured storage for advanced queries and persistence.

---

## Application Structure

### 1. **FlightData.h**  
   - Defines the **FlightData** class.  
   - Acts as the data model to store and manage flight details within the application.  
   - Ensures clean separation of data storage logic from core business logic.

### 2. **MainWindow.h**  
   - Contains the core business logic of the application.  
   - Handles UI interactions, file loading, sorting, JSON generation, and database creation.  
   - Implements the processing logic in a modular and extensible manner.

---

## Execution Flow

1. **Load CSV File**  
   - Place the desired flight data CSV file in the `data` folder.  
   - Click the **Load** button to display the data in the application.

2. **Sort by Time**  
   - Use the **Sort** button to organize flight data chronologically by time.

3. **Generate JSON**  
   - After sorting, click the **JSON** button to export the data to a JSON file.

4. **Create Database**  
   - Use the **Database** button to store the sorted data in a structured database format.

---

## Key Benefits

- **No External Dependencies**: The application only requires Qt, ensuring portability across systems.  
- **Efficient Sorting**: Optimized logic for sorting ensures smooth handling of large datasets.  
- **Scalable Design**: Modular structure allows future enhancements, such as integrating with external APIs or cloud services.  
- **User-Friendly Interface**: Simplified UI ensures seamless interaction for all users.  

---

## Demo

Check out the application in action: [Application Demo](https://youtu.be/aqS5WuJykbo)

---

## How to Run the Application

1. Install **Qt** on your machine.  
2. Clone the repository or copy the application files.  
3. Open the project in Qt Creator and build it.  
4. Execute the application to start managing your flight data.

---
