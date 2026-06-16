#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Expense {
    string date;
    string category;
    double amount;
};

int main() {
    string username;
    cout << "===== Expense Tracker & Budget Planner =====\n";
    cout << "Enter your username: ";
    cin >> username;

    double budget;
    cout << "Enter your monthly budget: ";
    cin >> budget;

    vector<Expense> expenses;

    ifstream fin("expenses.txt");
    Expense temp;
    while (fin >> temp.date >> temp.category >> temp.amount) {
        expenses.push_back(temp);
    }
    fin.close();

    int choice;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Budget Status\n";
        cout << "4. Category Summary\n";
        cout << "5. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Expense e;
            cout << "Enter date (DD-MM-YYYY): ";
            cin >> e.date;
            cout << "Enter category: ";
            cin >> e.category;
            cout << "Enter amount: ";
            cin >> e.amount;
            expenses.push_back(e);
            cout << "Expense added successfully!\n";
        }

        else if (choice == 2) {
            if (expenses.empty()) {
                cout << "No expenses recorded.\n";
            } else {
                cout << "\nDate         "
                     << setw(15) << left << "Category"
                     << "Amount\n";
                cout << "--------------------------------------\n";
                for (auto e : expenses) {
                    cout << setw(13) << left << e.date
                         << setw(15) << left << e.category
                         << e.amount << endl;
                }
            }
        }

        else if (choice == 3) {
            double total = 0;
            for (auto e : expenses)
                total += e.amount;

            cout << "\n===== Budget Report =====\n";
            cout << "Monthly Budget : " << budget << endl;
            cout << "Total Spent    : " << total << endl;

            if (budget >= total)
                cout << "Total Saved    : " << budget - total << endl;
            else
                cout << "Budget Exceeded By : " << total - budget << endl;
        }

        else if (choice == 4) {
            double food = 0, travel = 0, shopping = 0;
            double bills = 0, others = 0;

            for (auto e : expenses) {
                if (e.category == "Food")
                    food += e.amount;
                else if (e.category == "Travel")
                    travel += e.amount;
                else if (e.category == "Shopping")
                    shopping += e.amount;
                else if (e.category == "Bills")
                    bills += e.amount;
                else
                    others += e.amount;
            }

            cout << "\n===== Category Summary =====\n";
            cout << "Food      : " << food << endl;
            cout << "Travel    : " << travel << endl;
            cout << "Shopping  : " << shopping << endl;
            cout << "Bills     : " << bills << endl;
            cout << "Others    : " << others << endl;
        }

        else if (choice == 5) {
            ofstream fout("expenses.txt");
            for (auto e : expenses)
                fout << e.date << " "
                     << e.category << " "
                     << e.amount << endl;
            fout.close();

            cout << "\nData saved successfully.\n";
            cout << "Goodbye, " << username << "!\n";
        }

        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
