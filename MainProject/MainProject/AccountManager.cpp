#include "..\MovieManagement\AccountManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

AccountManager accManager;

AccountManager::AccountManager() {
    currentUser = nullptr;
}


bool AccountManager::registerAccount(string username, string password) {

    // Check if username already exists
    for (auto& acc : accounts) {
        if (acc.username == username) {
            cout << "Username already exists!\n";
            return false;
        }
    }

    Account newAcc;
    newAcc.username = username;
    newAcc.password = password;
    newAcc.rank = "user"; // default rank

    accounts.push_back(newAcc);
    saveAccounts();

    cout << "Account created successfully!\n";
    return true;
}


void AccountManager::loadAccounts() {
    ifstream file("accounts.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        Account acc;

        getline(ss, acc.username, '|');
        getline(ss, acc.password, '|');
        getline(ss, acc.rank, '|');

        accounts.push_back(acc);
    }

    file.close();
}

void AccountManager::saveAccounts() {
    ofstream file("accounts.txt");

    for (auto& acc : accounts) {
        file << acc.username << "|"
            << acc.password << "|"
            << acc.rank << "\n";
    }

    file.close();
}

bool AccountManager::login(const string& username, const string& password) {
    for (auto& acc : accounts) {
        if (acc.username == username && acc.password == password) {
            currentUser = &acc;
            return true;
        }
    }
    return false;
}

bool AccountManager::isAdmin() const {
    return currentUser && currentUser->rank == "admin";
}

string AccountManager::getCurrentUsername() const {
    return currentUser ? currentUser->username : "Guest";
}

string AccountManager::getCurrentRank() const {
    return currentUser ? currentUser->rank : "none";
}

void AccountManager::displayUserBanner() {
    cout << "\n=============================\n";
    cout << "Logged in as: " << getCurrentUsername()
        << " [" << getCurrentRank() << "]\n";
    cout << "=============================\n";
}

bool AccountManager::addAccount(string username, string password, string rank) {
    if (!isAdmin()) {
        cout << "Only admins can create accounts!\n";
        return false;
    }

    accounts.push_back({ username, password, rank });
    saveAccounts();
    return true;
}