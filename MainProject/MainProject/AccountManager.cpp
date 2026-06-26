#include "..\MovieManagement\AccountManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

AccountManager accManager;

AccountManager::AccountManager() {
    currentUser = nullptr;
}



bool AccountManager::registerAccount(string username, string password) {

    // --- VALIDATION RULES ---
    if (username.empty() || isBlank(username)) {
        lastError = "Username cannot be empty!";
        return false;
    }

    if (password.empty() || isBlank(password)) {
        lastError = "Password cannot be empty!";
        return false;
    }


    if (username.length() < 3) {
        lastError = "Username must be at least 3 characters!";
        return false;
    }

    if (password.length() < 3) {
        lastError = "Password must be at least 3 characters!";
        return false;
    }

    for (auto& acc : accounts) {
        if (acc.username == username) {
            lastError = "Username already exists!";
            return false;
        }
    }


    // --- CHECK FOR DUPLICATE USERNAME ---
    for (auto& acc : accounts) {
        if (acc.username == username) {
            cout << "Username already exists!\n";
            return false;
        }
    }

    // --- CREATE ACCOUNT ---
    Account newAcc;
    newAcc.username = username;
    newAcc.password = password;
    newAcc.rank = "customer";

    accounts.push_back(newAcc);
    saveAccounts();

    cout << "Account created successfully!\n";
    return true;
}



void AccountManager::loadAccounts()
{
    ifstream file("accounts.txt");
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        Account acc;
        getline(ss, acc.username, '|');
        getline(ss, acc.password, '|');
        getline(ss, acc.rank, '|');

        bool exists = false;

        for (auto& a : accounts)
        {
            if (a.username == acc.username)
            {
                exists = true;
                break;
            }
        }

        if (!exists)
            accounts.push_back(acc);
    }
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
    return currentUser && (currentUser->rank == "admin" || currentUser->rank == "user");
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