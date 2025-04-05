#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <cstdlib>
#include <algorithm>
#include<iomanip>
using namespace std;

class shopping {
private:
    int pcode;
    float price;
    float dis;
    string pname;
    string category;


    vector<list<pair<int, string>>> hashTable;
    const int TABLE_SIZE = 10;

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }


    void loadData() {
        vector<string> categories = {"Food", "Hardware", "Books", "Electronics", "Fashion"};
        for (const string &category : categories) {
            fstream data;
            data.open(category + ".txt", ios::in);
            if (!data)
                continue;
            int code;
            string name;
            float price, discount;
            while (data >> code >> name >> price >> discount) {
                insertToHashTable(code, name);
            }
            data.close();
        }
    }

public:
    shopping() {
        hashTable.resize(TABLE_SIZE);
        loadData();
    }

    void menu();
    void administrator();
    void buyer();
    void signUp();
    bool signIn();
    void add();
    void edit();
    void rem();
    void displayProductList(const string& category);
    void receipt();
    void search();
    int searchByName();
    void viewOrders();

    void insertToHashTable(int code, const string &name) {
        int index = hashFunction(code);
        hashTable[index].push_back({code, name});
    }

    void addToCategory(const string& category, int pcode, const string& pname, float price, float dis) {
        fstream data;
        data.open(category + ".txt", ios::app | ios::out);
        data << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
    }

    string toLowerCase(const string& str) {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }
};


void shopping::menu() {
    system("cls");
    int choice;
    string email, password;

    do {

        cout << "\t\t\t\t________________________\n";
        cout << "\t\t\t\t      ECOMMERCE         \n";
        cout << "\t\t\t\t________________________\n";
        cout << "\t\t\t\t1. Administrator\n";
        cout << "\t\t\t\t2. Buyer\n";
        cout << "\t\t\t\t3. Exit\n";
        cout << "\t\t\t\tPlease select: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            cout << "\t\t\t\t  Please Login\n";
            cout << "\n\t\t\t\tEnter email: ";
            cin >> email;
            cout << "\t\t\t\tPassword: ";
            cin >> password;
            if (email == "jayar" && password == "admin123") {
                administrator();
            } else {
                cout << "Invalid email or password\n";
            }
            break;

        case 2:
            buyer();
            break;

        case 3:
            exit(0);

        default:
            cout << "\t\t\t\tInvalid choice. Please try again.\n";
        }
    } while (true);
}
void shopping::administrator() {
    system("cls");
    int choice;
    do {
        cout << "\n\n\n\t\t\t\tAdministrator Menu";
        cout << "\n\t\t\t\t1. Manage Products";
        cout << "\n\t\t\t\t2. View Product List";
        cout << "\n\t\t\t\t3. View Orders";
        cout << "\n\t\t\t\t4. Exit";
        cout << "\n\n\t\t\t\tPlease select: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int choice1;
            cout << "\n\t\t\t\t\t\t Manage Products";
            cout << "\n\n\t\t\t\t1. Add the Product";
            cout << "\n\t\t\t\t2. Modify the Product";
            cout << "\n\t\t\t\t3. Delete the Product";
            cout << "\n\t\t\t\t4. Search Product";
            cout << "\n\t\t\t\tPlease select: ";
            cin >> choice1;

            switch (choice1) {
            case 1:
                add();
                break;
            case 2:
                edit();
                break;
            case 3:
                rem();
                break;
            case 4:
                search();
                break;
            default:
                cout << "\nInvalid choice for managing products.\n";
            }
            break;
        }

        case 2: {
            int categoryChoice;
            string category;

            do {
                cout << "\nEnter the category to view products:";
                cout << "\n1. Food";
                cout << "\n2. Hardware";
                cout << "\n3. Books";
                cout << "\n4. Electronics";
                cout << "\n5. Fashion";
                cout << "\n\nPlease select: ";
                cin >> categoryChoice;

                switch (categoryChoice) {
                case 1:
                    category = "Food";
                    break;
                case 2:
                    category = "Hardware";
                    break;
                case 3:
                    category = "Books";
                    break;
                case 4:
                    category = "Electronics";
                    break;
                case 5:
                    category = "Fashion";
                    break;
                default:
                    cout << "\nInvalid choice. Please try again.\n";
                    continue;
                }

                displayProductList(category);
                break;
            } while (true);
            break;
        }

        case 3:
            viewOrders();
            break;

        case 4:
            return;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    } while (true);
}

void shopping::buyer() {
    while (true) {
        system("cls");
        int choice;
        cout << "\n\n\t\t\t\tCustomer\n";
        cout << "\n\n\t\t\t\t1. Sign Up\n";
        cout << "\t\t\t\t2. Sign In\n";
        cout << "\t\t\t\t3. Go Back\n";
        cout << "\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            signUp();
            break;

        case 2:
            if (signIn()) {
                while (true) {
                    system("cls");
                    int choice1;
                    cout << "\n\t\t\t\t1. View Products\n";
                    cout << "\t\t\t\t2. Search Products\n";
                    cout << "\t\t\t\t3. Go Back\n";
                    cout << "\t\t\t\tEnter your choice: ";
                    cin >> choice1;

                    switch (choice1) {
                    case 1:
                        receipt();
                        break;

                    case 2:
                        if (searchByName() == 0) {
                            continue;
                        }
                        break;

                    case 3:

                        menu();

                    default:
                        cout << "Invalid choice. Try again.\n";
                    }
                }
            }
            break;

        case 3:
            return;


        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

backToMain:
    return;
}


void shopping::signUp() {
    system("cls");
    fstream buyers;
    string name, age, address, email, password;

    cout << "\n\n\t\t\t\tSign Up for Buyer Account\n";
    cin.ignore();
    cout << "\t\t\t\tEnter your name: ";
    getline(cin, name);
    cout << "\t\t\t\tEnter your age: ";
    getline(cin, age);
    cout << "\t\t\t\tEnter your address: ";
    getline(cin, address);
    cout << "\t\t\t\tEnter your email: ";
    getline(cin, email);
    cout << "\t\t\t\tEnter your password: ";
    getline(cin, password);


    buyers.open("customer.txt", ios::app);
    if (!buyers) {
        cout << "\n\t\t\t\tError: Unable to open file.\n";
        return;
    }

    buyers << name << "," << age << "," << address << "," << email << "," << password << "\n";
    buyers.close();

    cout << "\n\t\t\t\tSign-up successful! You can now log in.\n";
}



bool shopping::signIn() {
    system("cls");
    fstream buyers;
    string name, age, address, email, password;
    string inputEmail, inputPassword;

    cout << "\n\n\t\t\t\tSign In to Your Buyer Account\n";
    cin.ignore();
    cout << "\t\t\t\tEnter your email: ";
    getline(cin, inputEmail);
    cout << "\t\t\t\tEnter your password: ";
    getline(cin, inputPassword);


    buyers.open("customer.txt", ios::in);
    if (!buyers) {
        cout << "\n\t\t\t\tNo buyer accounts found. Please sign up first.\n";
        return false;
    }


    while (getline(buyers, name, ',') &&
           getline(buyers, age, ',') &&
           getline(buyers, address, ',') &&
           getline(buyers, email, ',') &&
           getline(buyers, password)) {


        if (email == inputEmail && password == inputPassword) {
            cout << "\n\t\t\t\tLogin successful!\n";
            cout << "\t\t\t\tWelcome, " << name << "!\n";
            cout << "\t\t\t\tAge: " << age << "\n";
            cout << "\t\t\t\tAddress: " << address << "\n";
            buyers.close();
            return true;
        }
    }

    buyers.close();
    cout << "\n\t\t\t\tInvalid email or password.\n";
    return false;
}



void shopping::add() {
    system("cls");
    fstream data;
    char choice;
    int c;
    float p, d;
    string n, category;

    do {
        cout << "\n\n\tAdd new product";
        cout << "\n\n\tProduct code: ";
        cin >> c;
        cout << "\tName of the product: ";
        cin >> n;
        cout << "\tPrice of the product: ";
        cin >> p;
        cout << "\tDiscount of the product: ";
        cin >> d;

        int categoryChoice;

        do {
            cout << "\n\tCategory:";
            cout << "\n1. Food";
            cout << "\n2. Hardware";
            cout << "\n3. Books";
            cout << "\n4. Electronics";
            cout << "\n5. Fashion";
            cout << "\n\nPlease select: ";
            cin >> categoryChoice;

            switch (categoryChoice) {
            case 1:
                category = "Food";
                break;
            case 2:
                category = "Hardware";
                break;
            case 3:
                category = "Books";
                break;
            case 4:
                category = "Electronics";
                break;
            case 5:
                category = "Fashion";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                continue;
            }
            break;
        } while (true);

        addToCategory(category, c, n, p, d);
        insertToHashTable(c, n);

        cout << "\n\n\t\t\t\tProduct added successfully under " << category << " category.";
        cout << "\n\n\t\t\t\tDo you want to add more? Press 'y' for yes and 'n' for no: ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
}
void shopping::rem() {
    system("cls");
    fstream data, data1;
    int pkey, token = 0, categoryChoice;
    string category;

    cout << "\n\n\t\t\t\tDelete Product";


    do {
        cout << "\nCategory";
        cout << "\n1. Food";
        cout << "\n2. Hardware";
        cout << "\n3. Books";
        cout << "\n4. Electronics";
        cout << "\n5. Fashion";
        cout << "\n\nPlease select a category ";
        cin >> categoryChoice;

        switch (categoryChoice) {
        case 1:
            category = "Food";
            break;
        case 2:
            category = "Hardware";
            break;
        case 3:
            category = "Books";
            break;
        case 4:
            category = "Electronics";
            break;
        case 5:
            category = "Fashion";
            break;
        default:
            cout << "\nInvalid choice, try again.\n";
            continue;
        }
        break;
    } while (true);

    cout << "\n\n\t\t\t\tProduct Code: ";
    cin >> pkey;


    data.open(category + ".txt", ios::in);
    if (!data) {
        cout << "\n\n\t\t\t\tFile for category " << category << " doesn't exist.";
        return;
    }

    data1.open("temp.txt", ios::out);
    data >> pcode >> pname >> price >> dis;

    while (!data.eof()) {
        if (pkey == pcode) {
            cout << "\n\n\t\t\t\tProduct deleted successfully.";
            token++;
        } else {
            data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
        }
        data >> pcode >> pname >> price >> dis;
    }

    data.close();
    data1.close();
    remove((category + ".txt").c_str());
    rename("temp.txt", (category + ".txt").c_str());

    if (token == 0) {
        cout << "\n\n\t\t\t\tRecord not found in category " << category << ".";
    }
}




void shopping::edit() {
    system("cls");
    fstream data, data1;
    int pkey, token = 0, c,categoryChoice;
    float p, d;
    string n, category;

    cout << "\n\t\t\tModify the record";
    do {
        cout << "\nEnter the category to modify product from:";
        cout << "\n1. Food";
        cout << "\n2. Hardware";
        cout << "\n3. Books";
        cout << "\n4. Electronics";
        cout << "\n5. Fashion";
        cout << "\n\nPlease select a category: ";
        cin >> categoryChoice;

        switch (categoryChoice) {
        case 1:
            category = "Food";
            break;
        case 2:
            category = "Hardware";
            break;
        case 3:
            category = "Books";
            break;
        case 4:
            category = "Electronics";
            break;
        case 5:
            category = "Fashion";
            break;
        default:
            cout << "\nInvalid choice, try again.\n";
            continue;
        }
        break;
    } while (true);


    cout << "\n\n\t\t\tProduct Code: ";
    cin >> pkey;


    data.open(category + ".txt", ios::in);
    if (!data) {
        cout << "\n\n\t\t\tFile for category " << category << " doesn't exist.";
        return;
    }

    data1.open("temp.txt", ios::out);
    data >> pcode >> pname >> price >> dis;

    while (!data.eof()) {
        if (pkey == pcode) {
            cout << "\n\t\t\tProduct found. \n\n\t\t\tEnter new details:\n";
            cout << "\t\t\tNew Product Code: ";
            cin >> c;
            cout << "\t\t\tName of the Product: ";
            cin >> n;
            cout << "\t\t\tPrice: ";
            cin >> p;
            cout << "\t\t\tDiscount: ";
            cin >> d;
            data1 << c << " " << n << " " << p << " " << d << "\n";
            token++;
            cout << "\n\t\t\tProduct updated successfully.\n";
        } else {
            data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
        }
        data >> pcode >> pname >> price >> dis;
    }

    data.close();
    data1.close();


    remove((category + ".txt").c_str());
    rename("temp.txt", (category + ".txt").c_str());

    if (token == 0) {
        cout << "\n\n\t\t\tRecord not found in category " << category << ".";
    }
}




void shopping::displayProductList(const string& category) {
    system("cls");
    fstream data;
    data.open(category + ".txt", ios::in);
    if (!data) {
        cout << "\n\t\t\t\tNo records found in " << category << " category.\n";
        return;
    }

    cout << "\n\n\t\t\t\t\t\tProduct List\n";
       cout << "\t" << string(100, '-') << endl;

    cout << "\n\t\t"
         << setw(25) << left << "Product Code"
         << setw(30) << left << "Name"
         << setw(20) << right << "Price"
         << setw(15) << right << "Discount" << endl;
        cout << "\t" << string(100, '-') << endl;

    data >> pcode >> pname >> price >> dis;
    while (!data.eof()) {
        cout << "\t\t"
             << setw(25) << left << pcode
             << setw(29.5) << left << pname
             << setw(19.5) << right << price
             << setw(14.5) << right << dis <<"%"<< endl;
        data >> pcode >> pname >> price >> dis;


    }
    cout << "\t" << string(100, '-') << endl;
    data.close();
}



void shopping::receipt() {
    system("cls");
    fstream data, orders;
    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0, dis = 0, total = 0;
    string category;
    cout << "\n\n\t\t\t\tRECEIPT";
    int categoryChoice;

        do {
            cout << "\n\tCategory:";
            cout << "\n1. Food";
            cout << "\n2. Hardware";
            cout << "\n3. Books";
            cout << "\n4. Electronics";
            cout << "\n5. Fashion";
            cout << "\n\nPlease select: ";
            cin >> categoryChoice;

            switch (categoryChoice) {
            case 1:
                category = "Food";
                break;
            case 2:
                category = "Hardware";
                break;
            case 3:
                category = "Books";
                break;
            case 4:
                category = "Electronics";
                break;
            case 5:
                category = "Fashion";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                continue;
            }
            break;
        } while (true);


    data.open(category + ".txt", ios::in);
    if (!data) {
        cout << "\n\nEmpty Database in " << category << " category.";
        return;
    }
    data.close();
    displayProductList(category);

    cout << "\n\n\t\t\t\tPlease enter your name: ";
    string buyerName;
    cin.ignore();
    getline(cin, buyerName);

    cout << "\n\n\t\t\t\tPlease place the order:\n";
    do {
        cout << "\n\n\t\t\t\tProduct Code: ";
        cin >> arrc[c];
        cout << "\t\t\t\tEnter the product quantity: ";
        cin >> arrq[c];
        c++;
        cout << "\t\t\t\tDo you want to buy another product? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    system("cls");
    orders.open("orders.txt", ios::app);
    orders << "Order by: " << buyerName << "\n";

    cout << "\n\n\t\t\t\t\tRECEIPT\n";
    cout << "\t\tProduct Code\t\tQuantity\t\tPrice\t\tAmount\t\tAmount after Discount\n";

    for (int i = 0; i < c; i++) {
        data.open(category + ".txt", ios::in);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof()) {
            if (pcode == arrc[i]) {
                amount = price * arrq[i];
                dis = amount - (amount * dis / 100);
                total += dis;

                cout << "\t\t" << pcode << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << dis << "\n";
                orders << "Code: " << pcode << ", Name: " << pname << ", Quantity: " << arrq[i]
                       << ", Price: " << price << ", Amount: " << amount << ", Discounted Amount: " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
    }

    cout << "\n\t\tTotal Amount: " << total;
    orders << "Total Amount: " << total << "\n\n";
    orders.close();

    cout << "\n\nPress any key to exit...";
    cin.ignore();
    cin.get();
    system("cls");
}



int shopping::searchByName() {
    string searchName;
    char choice;

    do {
        system("cls");
        cin.ignore();

        cout << "\n\t\t\t\tEnter product name to search: ";
        getline(cin, searchName);
        searchName = toLowerCase(searchName);

        bool found = false;
        for (const auto& bucket : hashTable) {
            for (const auto& item : bucket) {
                string nameLower = toLowerCase(item.second);
                if (nameLower.find(searchName) != string::npos) {
                    cout << "\n\t\t\t\tProduct found: Code: " << item.first << ", Name: " << item.second << "\n";
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "\n\t\t\t\tProduct not found.\n";
        }


        cout << "\n\t\t\t\tWould you like to search again? (y/n): ";
        cin >> choice;
        choice = tolower(choice);

    } while (choice == 'y');

    cout << "\n\t\t\t\tReturning to the main menu...\n";

    return 2;
}



void shopping::search() {
    int searchCode;
    cout << "\n\n\t\t\t\tEnter product code to search: ";
    cin >> searchCode;

    int index = hashFunction(searchCode);
    for (auto &item : hashTable[index]) {
        if (item.first == searchCode) {
            cout << "\n\t\t\t\tProduct found: Code: " << item.first << ", Name: " << item.second << "\n";
            return;
        }
    }
    cout << "\nProduct not found.\n";
}


void shopping::viewOrders() {
    system("cls");
    fstream orders;
    string line;

    orders.open("orders.txt", ios::in);
    if (!orders) {
        cout << "\n\nNo orders have been placed yet.\n";
        return;
    }

    cout << "\n\n\t\t\t\tOrder Details\n";
    while (getline(orders, line)) {
        cout << line << "\n";
    }

    orders.close();
}


int main() {
    shopping s;
    s.menu();
    return 0;
}
