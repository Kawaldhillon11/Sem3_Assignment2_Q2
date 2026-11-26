#include "includes/bank/Bank.h"
#include "includes/wallet/wallet.h"
#include "includes/ui/Option.h"
#include "includes/ui/Menu.h"

void addAccountMenu(void* args) {
    bank::Bank* myBank = static_cast<bank::Bank*>(args);
    (void)myBank;

    ui::Menu menu("Add Account");
    menu.run();
}

void viewAccountsMenu(void* args) {
    bank::Bank* myBank = static_cast<bank::Bank*>(args);
    (void)myBank;

    ui::Menu menu("View Accounts");
    menu.run();
}

void addCardMenu(void* args) {
    wallet::wallet* myWallet = static_cast<wallet::wallet*>(args);
    (void)myWallet;

    ui::Menu menu("Add Card");
    menu.run();
}

void viewCardsMenu(void* args) {
    wallet::wallet* myWallet = static_cast<wallet::wallet*>(args);
    (void)myWallet;

    ui::Menu menu("View Cards");
    menu.run();
}

int main() {
    bank::Bank myBank("My Bank");
    wallet::wallet myWallet;

    ui::Menu mainMenu("Main Menu", "Exit");
    ui::Option mainOptions[4] = {
        ui::Option("Add Account", addAccountMenu, &myBank),
        ui::Option("View Accounts", viewAccountsMenu, &myBank),
        ui::Option("Add Card", addCardMenu, &myWallet),
        ui::Option("View Cards", viewCardsMenu, &myWallet)
    };

    mainMenu.addOptions(mainOptions, 4);
    mainMenu.run();

    return 0;
}
