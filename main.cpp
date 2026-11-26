#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <string>
#include <cctype>

#include "includes/bank/Bank.h"
#include "includes/account/DebitAccount.h"
#include "includes/account/CreditAccount.h"
#include "includes/wallet/wallet.h"
#include "includes/card/DebitCard.h"
#include "includes/card/CreditCard.h"
#include "includes/ui/Option.h"
#include "includes/ui/Menu.h"

struct CardDetails {
    std::string pin;
    int expiryMonth;
    int expiryYear;
};

struct BankWalletContext {
    bank::Bank* bank;
    wallet::wallet* wallet;
};

struct AccountViewContext {
    account::Account* account;
    bank::Bank* bank;
    wallet::wallet* wallet;
};

struct LinkedCardContext {
    card::Card* card;
    ui::Menu* parentMenu;
    bool* shouldRefresh;
};

void clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string formatMoney(double amount) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << amount;
    return oss.str();
}

void showMessageMenu(const std::string& title, const std::string& message) {
    ui::Menu menu(title, "Go Back", message);
    menu.run();
}

// --- UI Validation Helpers ---

std::string promptAccountHolderName() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string name;

    while (true) {
        std::cout << "Enter Account Holder Name: ";
        std::getline(std::cin, name);

        if (name.empty()) {
            std::cout << "Invalid input: Name cannot be empty.\n";
            continue;
        }
        if (name.length() > 50) {
            std::cout << "Invalid input: Name cannot exceed 50 characters.\n";
            continue;
        }
        return name;
    }
}

double promptPositiveDouble(const std::string& prompt, double minVal = 0.0) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            clearInputStream();
            std::cout << "Invalid input: Please enter a valid number.\n";
            continue;
        }
        if (value <= minVal) {
            if (minVal == 0.0) {
                std::cout << "Invalid input: Value must be greater than 0.\n";
            } else {
                std::cout << "Invalid input: Value must be greater than " << formatMoney(minVal) << ".\n";
            }
            continue;
        }
        return value;
    }
}

double promptNonNegativeDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            clearInputStream();
            std::cout << "Invalid input: Please enter a valid number.\n";
            continue;
        }
        if (value < 0) {
            std::cout << "Invalid input: Value cannot be negative.\n";
            continue;
        }
        return value;
    }
}

bool validatePinFormat(const std::string& pin, std::string& errorMsg) {
    if (pin.length() != 4) {
        errorMsg = "PIN must be exactly 4 digits.";
        return false;
    }
    for (char c : pin) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            errorMsg = "PIN must contain digits only.";
            return false;
        }
    }
    return true;
}

bool validateCardDetails(const std::string& pin, int month, int year, std::string& errorMsg) {
    if (!validatePinFormat(pin, errorMsg)) {
        return false;
    }
    if (month < 1 || month > 12) {
        errorMsg = "Expiry month must be between 1 and 12.";
        return false;
    }
    if (year < 2026 || year > 2036) {
        errorMsg = "Expiry year must be between 2026 and 2036.";
        return false;
    }
    return true;
}

std::string promptPin() {
    std::string pin;
    while (true) {
        std::cout << "Enter 4-digit PIN: ";
        std::cin >> pin;

        std::string errorMsg;
        if (!validatePinFormat(pin, errorMsg)) {
            std::cout << "Invalid PIN: " << errorMsg << "\n";
            continue;
        }
        return pin;
    }
}

CardDetails promptCardDetails() {
    CardDetails details;

    while (true) {
        std::cout << "Enter 4-digit PIN: ";
        std::cin >> details.pin;

        std::cout << "Enter Expiry Month (1-12): ";
        std::cin >> details.expiryMonth;
        if (std::cin.fail()) {
            clearInputStream();
            std::cout << "Invalid input: Month must be a number.\n";
            continue;
        }

        std::cout << "Enter Expiry Year (2026-2036): ";
        std::cin >> details.expiryYear;
        if (std::cin.fail()) {
            clearInputStream();
            std::cout << "Invalid input: Year must be a number.\n";
            continue;
        }

        std::string errorMsg;
        if (!validateCardDetails(details.pin, details.expiryMonth, details.expiryYear, errorMsg)) {
            std::cout << "Invalid card details: " << errorMsg << "\n";
            continue;
        }

        return details;
    }
}

account::DebitAccount* selectDebitAccount(bank::Bank* myBank) {
    int totalAccounts = myBank->getNoOfAccounts();
    account::Account** allAccounts = myBank->getALLAccounts();

    account::DebitAccount* debitAccounts[10]{};
    int debitCount = 0;

    if (allAccounts != nullptr) {
        for (int i = 0; i < totalAccounts; i++) {
            account::DebitAccount* debitAcc = dynamic_cast<account::DebitAccount*>(allAccounts[i]);
            if (debitAcc != nullptr) {
                debitAccounts[debitCount] = debitAcc;
                debitCount++;
            }
        }
    }

    if (debitCount == 0) {
        return nullptr;
    }

    std::cout << "Select a Debit Account to link:\n";
    for (int i = 0; i < debitCount; i++) {
        std::cout << (i + 1) << ". Debit Account #" << debitAccounts[i]->getAccountNumber()
                  << " - " << debitAccounts[i]->getHolderName()
                  << " (Balance: $" << formatMoney(debitAccounts[i]->getBalance()) << ")\n";
    }

    int choice;
    while (true) {
        std::cout << "Select an account (1 to " << debitCount << "): ";
        std::cin >> choice;

        if (std::cin.fail()) {
            clearInputStream();
            std::cout << "Invalid input: Please enter a number.\n";
            continue;
        }
        if (choice < 1 || choice > debitCount) {
            std::cout << "Invalid selection. Please choose between 1 and " << debitCount << ".\n";
            continue;
        }
        return debitAccounts[choice - 1];
    }
}

// --- Card Payment & Details (Shared) ---

void makePaymentForCard(void* args) {
    card::Card* selectedCard = static_cast<card::Card*>(args);

    std::cout << "---- Make Payment (Card #" << selectedCard->getCardNumber() << ") ----\n";
    double amount = promptPositiveDouble("Enter Payment Amount (min $1.00): $", 0.999999);
    std::string pin = promptPin();

    try {
        selectedCard->makePayment(amount, pin);
        showMessageMenu(
            "Payment Successful",
            "Payment of $" + formatMoney(amount) + " made with Card #" + std::to_string(selectedCard->getCardNumber()) + "."
        );
    } catch (const std::exception& e) {
        showMessageMenu("Payment Failed", e.what());
    }
}

void viewCardDetails(void* args) {
    card::Card* selectedCard = static_cast<card::Card*>(args);
    card::CreditCard* creditCard = dynamic_cast<card::CreditCard*>(selectedCard);

    std::string details;
    if (creditCard != nullptr) {
        details += "Card Type: Credit Card\n";
    } else {
        details += "Card Type: Debit Card\n";
    }
    details += "Card Number: #" + std::to_string(selectedCard->getCardNumber()) + "\n";
    details += "Expiry Date: " + selectedCard->getExpiryDate() + "\n";

    if (selectedCard->getLinkedAccount() != nullptr) {
        details += "Linked Account: #" + std::to_string(selectedCard->getLinkedAccount()->getAccountNumber()) + "\n";
    }
    if (creditCard != nullptr) {
        details += "Cashback Rate: " + formatMoney(creditCard->getCashBackPer() * 100) + "%\n";
    }

    ui::Menu menu("Card Details");
    menu.setDetails(details);

    ui::Option options[1] = {
        ui::Option("Make Payment", makePaymentForCard, selectedCard)
    };
    menu.addOptions(options, 1);
    menu.run();
}

void viewLinkedCardDetails(void* args) {
    LinkedCardContext* ctx = static_cast<LinkedCardContext*>(args);
    viewCardDetails(ctx->card);
    *(ctx->shouldRefresh) = true;
    ctx->parentMenu->stop();
}

void runCardSelectionMenu(wallet::wallet* myWallet, const std::string& title, void (*onCardSelected)(void*)) {
    int totalCards = myWallet->getNoOfCards();
    card::Card** allCards = myWallet->getAllCards();

    // Sort cards by type: Debit Cards first, then Credit Cards
    card::Card* sortedCards[10]{};
    int sortedCount = 0;

    if (allCards != nullptr) {
        for (int i = 0; i < totalCards; i++) {
            if (dynamic_cast<card::DebitCard*>(allCards[i]) != nullptr) {
                sortedCards[sortedCount++] = allCards[i];
            }
        }
        for (int i = 0; i < totalCards; i++) {
            if (dynamic_cast<card::CreditCard*>(allCards[i]) != nullptr) {
                sortedCards[sortedCount++] = allCards[i];
            }
        }
    }

    ui::Option* options = nullptr;
    if (sortedCount > 0) {
        options = new ui::Option[sortedCount];
        for (int i = 0; i < sortedCount; i++) {
            std::string typeLabel = (dynamic_cast<card::CreditCard*>(sortedCards[i]) != nullptr) ? "[Credit]" : "[Debit]";
            std::string label = typeLabel + " Card #" + std::to_string(sortedCards[i]->getCardNumber()) +
                                " (Exp: " + sortedCards[i]->getExpiryDate() + ")";
            options[i] = ui::Option(label, onCardSelected, sortedCards[i]);
        }
    }

    ui::Menu menu(title, "Go Back", "No cards in wallet.");
    if (options != nullptr) {
        menu.addOptions(options, sortedCount);
    }
    menu.run();

    delete[] options;
}

// --- Account Actions & Submenus ---

void addAccountMenu(void* args) {
    bank::Bank* myBank = static_cast<bank::Bank*>(args);

    if (myBank->getNoOfAccounts() >= 10) {
        showMessageMenu("Add Account", "Cannot add account: Maximum number of accounts (10) reached.");
        return;
    }

    std::cout << "---- Add Account ----\n";
    std::cout << "Creating a new Debit Account (Note: Credit Accounts are created automatically when adding a Credit Card).\n\n";

    std::string name = promptAccountHolderName();

    account::DebitAccount* acc = new account::DebitAccount(name);
    myBank->addAccount(acc);

    showMessageMenu("Add Account", "Debit Account created! Account Number: " + std::to_string(acc->getAccountNumber()));
}

void viewAccountDetails(void* args) {
    AccountViewContext* ctx = static_cast<AccountViewContext*>(args);
    account::Account* acc = ctx->account;
    account::DebitAccount* debitAcc = dynamic_cast<account::DebitAccount*>(acc);
    account::CreditAccount* creditAcc = dynamic_cast<account::CreditAccount*>(acc);

    bool shouldRefresh = true;
    while (shouldRefresh) {
        shouldRefresh = false;

        std::string details;
        if (debitAcc != nullptr) {
            details += "Account Type: Debit Account\n";
        } else if (creditAcc != nullptr) {
            details += "Account Type: Credit Account\n";
        }
        details += "Account Number: #" + std::to_string(acc->getAccountNumber()) + "\n";
        details += "Holder Name: " + acc->getHolderName() + "\n";
        details += "Bank: " + ctx->bank->getInstituteName() + "\n";

        if (debitAcc != nullptr) {
            details += "Balance: $" + formatMoney(debitAcc->getBalance()) + "\n";
        } else if (creditAcc != nullptr) {
            details += "Balance: $" + formatMoney(creditAcc->getBalance()) + "\n";
            details += "Credit Limit: $" + formatMoney(creditAcc->getLimit()) + "\n";
            details += "Cashback Earned: $" + formatMoney(creditAcc->getCashBackEarned()) + "\n";
        }
        details += "\nLinked Cards:";

        // Collect cards in wallet linked to this account
        int totalCards = ctx->wallet->getNoOfCards();
        card::Card** allCards = ctx->wallet->getAllCards();
        card::Card* linkedCards[10]{};
        int linkedCount = 0;

        if (allCards != nullptr) {
            for (int i = 0; i < totalCards; i++) {
                if (allCards[i]->getLinkedAccount() == acc) {
                    linkedCards[linkedCount++] = allCards[i];
                }
            }
        }

        ui::Menu menu("Account Details", "Go Back", "No cards linked to this account.");
        menu.setDetails(details);

        LinkedCardContext cardContexts[10]{};
        ui::Option* linkedCardOptions = nullptr;

        if (linkedCount > 0) {
            linkedCardOptions = new ui::Option[linkedCount];
            for (int i = 0; i < linkedCount; i++) {
                cardContexts[i] = {linkedCards[i], &menu, &shouldRefresh};
                std::string typeLabel = (dynamic_cast<card::CreditCard*>(linkedCards[i]) != nullptr) ? "[Credit]" : "[Debit]";
                std::string label = typeLabel + " Card #" + std::to_string(linkedCards[i]->getCardNumber()) +
                                    " (Exp: " + linkedCards[i]->getExpiryDate() + ")";
                linkedCardOptions[i] = ui::Option(label, viewLinkedCardDetails, &cardContexts[i]);
            }
            menu.addOptions(linkedCardOptions, linkedCount);
        }

        menu.run();
        delete[] linkedCardOptions;
    }
}

void viewAccountsMenu(void* args) {
    BankWalletContext* ctx = static_cast<BankWalletContext*>(args);
    int totalAccounts = ctx->bank->getNoOfAccounts();
    account::Account** allAccounts = ctx->bank->getALLAccounts();

    // Sort accounts by type: Debit Accounts first, then Credit Accounts
    account::Account* sortedAccounts[10]{};
    int sortedCount = 0;

    if (allAccounts != nullptr) {
        for (int i = 0; i < totalAccounts; i++) {
            if (dynamic_cast<account::DebitAccount*>(allAccounts[i]) != nullptr) {
                sortedAccounts[sortedCount++] = allAccounts[i];
            }
        }
        for (int i = 0; i < totalAccounts; i++) {
            if (dynamic_cast<account::CreditAccount*>(allAccounts[i]) != nullptr) {
                sortedAccounts[sortedCount++] = allAccounts[i];
            }
        }
    }

    AccountViewContext accountContexts[10]{};
    ui::Option* options = nullptr;

    if (sortedCount > 0) {
        options = new ui::Option[sortedCount];
        for (int i = 0; i < sortedCount; i++) {
            accountContexts[i] = {sortedAccounts[i], ctx->bank, ctx->wallet};
            std::string typeLabel = (dynamic_cast<account::CreditAccount*>(sortedAccounts[i]) != nullptr) ? "[Credit]" : "[Debit]";
            std::string label = typeLabel + " Account #" + std::to_string(sortedAccounts[i]->getAccountNumber()) +
                                " - " + sortedAccounts[i]->getHolderName();
            options[i] = ui::Option(label, viewAccountDetails, &accountContexts[i]);
        }
    }

    ui::Menu menu("View Accounts", "Go Back", "No accounts found.");
    if (options != nullptr) {
        menu.addOptions(options, sortedCount);
    }
    menu.run();

    delete[] options;
}

// --- Card Actions & Submenus ---

void addDebitCard(void* args) {
    BankWalletContext* ctx = static_cast<BankWalletContext*>(args);

    if (ctx->wallet->getNoOfCards() >= 10) {
        showMessageMenu("Add Debit Card", "Cannot add card: Wallet cannot hold more than 10 cards.");
        return;
    }

    std::cout << "---- Add Debit Card ----\n";
    account::DebitAccount* linkedDebitAcc = selectDebitAccount(ctx->bank);
    if (linkedDebitAcc == nullptr) {
        showMessageMenu("Add Debit Card", "No Debit Accounts found. Please create a Debit Account first.");
        return;
    }

    CardDetails details = promptCardDetails();
    double depositAmount = promptNonNegativeDouble("Enter balance to add to linked Debit Account ($0 to skip): $");
    if (depositAmount > 0) {
        linkedDebitAcc->deposit(depositAmount);
    }

    card::DebitCard* newCard = new card::DebitCard(linkedDebitAcc, details.pin, details.expiryMonth, details.expiryYear);
    ctx->wallet->addCard(newCard);

    showMessageMenu(
        "Add Debit Card",
        "Debit Card added! Card Number: " + std::to_string(newCard->getCardNumber()) +
        " (Linked to Debit Account #" + std::to_string(linkedDebitAcc->getAccountNumber()) +
        ", Balance: $" + formatMoney(linkedDebitAcc->getBalance()) + ")"
    );
}

void addCreditCard(void* args) {
    BankWalletContext* ctx = static_cast<BankWalletContext*>(args);

    if (ctx->wallet->getNoOfCards() >= 10) {
        showMessageMenu("Add Credit Card", "Cannot add card: Wallet cannot hold more than 10 cards.");
        return;
    }
    if (ctx->bank->getNoOfAccounts() >= 10) {
        showMessageMenu("Add Credit Card", "Cannot add Credit Card: Maximum number of bank accounts (10) reached.");
        return;
    }

    std::cout << "---- Add Credit Card ----\n";
    std::cout << "A new Credit Account will be created and linked to this Credit Card.\n\n";

    std::string name = promptAccountHolderName();
    double limit = promptPositiveDouble("Enter Credit Limit: ");
    CardDetails details = promptCardDetails();
    double cashback = promptPositiveDouble("Enter Cashback Percentage (e.g. 0.02 for 2%): ");

    account::CreditAccount* creditAcc = new account::CreditAccount(name, limit);
    ctx->bank->addAccount(creditAcc);

    card::CreditCard* newCard = new card::CreditCard(cashback, creditAcc, details.pin, details.expiryMonth, details.expiryYear);
    ctx->wallet->addCard(newCard);

    showMessageMenu(
        "Add Credit Card",
        "Credit Card added! Card Number: " + std::to_string(newCard->getCardNumber()) +
        " (Linked to new Credit Account #" + std::to_string(creditAcc->getAccountNumber()) + ")"
    );
}

void addCardMenu(void* args) {
    BankWalletContext* ctx = static_cast<BankWalletContext*>(args);

    ui::Menu menu("Add Card");
    ui::Option options[2] = {
        ui::Option("Debit Card", addDebitCard, ctx),
        ui::Option("Credit Card", addCreditCard, ctx)
    };

    menu.addOptions(options, 2);
    menu.run();
}

void viewCardsMenu(void* args) {
    wallet::wallet* myWallet = static_cast<wallet::wallet*>(args);
    runCardSelectionMenu(myWallet, "View Cards", viewCardDetails);
}

void makePaymentMenu(void* args) {
    wallet::wallet* myWallet = static_cast<wallet::wallet*>(args);
    runCardSelectionMenu(myWallet, "Make Payment", makePaymentForCard);
}

int main() {
    bank::Bank myBank("My Bank");
    wallet::wallet myWallet;
    BankWalletContext bankWalletCtx{&myBank, &myWallet};

    ui::Menu mainMenu("Main Menu", "Exit");
    ui::Option mainOptions[5] = {
        ui::Option("Add Account", addAccountMenu, &myBank),
        ui::Option("View Accounts", viewAccountsMenu, &bankWalletCtx),
        ui::Option("Add Card", addCardMenu, &bankWalletCtx),
        ui::Option("View Cards", viewCardsMenu, &myWallet),
        ui::Option("Make Payment", makePaymentMenu, &myWallet)
    };

    mainMenu.addOptions(mainOptions, 5);
    mainMenu.run();

    return 0;
}
