#pragma once
#include <string>
#include <vector>

using namespace std;

struct Account {
    string username;
    string password;
    string rank; // user / admin
};

class AccountManager {
private:
    vector<Account> accounts;
    Account* currentUser;

public:
    AccountManager();

    void loadAccounts();
    void saveAccounts();

    bool login(const string& username, const string& password);

    bool isAdmin() const;
    string getCurrentUsername() const;
    string getCurrentRank() const;

    void displayUserBanner();

    bool addAccount(string username, string password, string rank);

};

extern class AccountManager accManager;