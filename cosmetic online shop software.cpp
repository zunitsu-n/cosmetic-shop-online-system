#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;


class Product {
public:
    virtual void displayDetails() = 0;  // Pure virtual function
    virtual double calculatePrice() = 0;  // Pure virtual function
    virtual ~Product() {}
};


class SkincareProduct : public Product {
private:
    string name;
    double price;
    string brand;

public:
    SkincareProduct(string name, double price, string brand)
        : name(name), price(price), brand(brand) {}

    void displayDetails() override {
        cout << "Skincare Product: " << name << "\nPrice: " << price
             << "\nBrand: " << brand << endl;
    }

    double calculatePrice() override {
        return price;  // No discount for simplicity
    }
};

// Derived class for Makeup Products
class MakeupProduct : public Product {
private:
    string name;
    double price;
    string color;

public:
    MakeupProduct(string name, double price, string color)
        : name(name), price(price), color(color) {}

    void displayDetails() override {
        cout << "Makeup Product: " << name << "\nPrice: " << price
             << "\nColor: " << color << endl;
    }

    double calculatePrice() override {
        return price * 1.1;  // Applying a 10% markup for makeup
    }
};

// Customer class
class Customer {
private:
    string name;
    string email;

public:
    Customer(string name, string email) : name(name), email(email) {}

    void displayCustomerInfo() {
        cout << "Customer: " << name << "\nEmail: " << email << endl;
    }

    string getEmail() const {
        return email;
    }
};

// Order class
class Order {
private:
    Customer* customer;
    vector<Product*> products;

public:
    Order(Customer* customer) : customer(customer) {}

    void addProduct(Product* product) {
        products.push_back(product);
    }

    void displayOrderDetails() {
        cout << "Order for " << customer->getEmail() << ":\n";
        double total = 0;
        for (auto product : products) {
            product->displayDetails();
            total += product->calculatePrice();
        }
        cout << "Total Price: " << total << endl;
    }
};

// Shop class to manage products and customers
class Shop {
private:
    vector<Product*> products;
    vector<Customer*> customers;

public:
    void addProduct(Product* product) {
        products.push_back(product);
    }

    void addCustomer(Customer* customer) {
        customers.push_back(customer);
    }

    void displayProducts() {
        for (auto product : products) {
            product->displayDetails();
        }
    }

    void displayCustomers() {
        for (auto customer : customers) {
            customer->displayCustomerInfo();
        }
    }

    void saveProductsToFile(const string& filename) {
        try {
            ofstream outFile(filename, ios::out);
            if (!outFile) throw ios_base::failure("Failed to open file for writing.");

            for (auto product : products) {
                // Here we just save product name and price for simplicity
                outFile << "Product: " << product->calculatePrice() << "\n";
            }
            outFile.close();
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    void loadProductsFromFile(const string& filename) {
        try {
            ifstream inFile(filename, ios::in);
            if (!inFile) throw ios_base::failure("Failed to open file for reading.");

            // For simplicity, we assume the data is just names and prices
            string name;
            double price;
            while (inFile >> name >> price) {
                // For example, create a SkincareProduct (you can enhance this)
                addProduct(new SkincareProduct(name, price, "Brand Placeholder"));
            }
            inFile.close();
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
};

// Main Menu Interface
void showMenu() {
    cout << "1. Add Product\n";
    cout << "2. Add Customer\n";
    cout << "3. Display Products\n";
    cout << "4. Display Customers\n";
    cout << "5. Exit\n";
}

int main() {
    Shop shop;
    int choice;

    while (true) {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, brand_or_color;
                double price;
                cout << "Enter product name: ";
                cin >> name;
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter brand (for Skincare) or color (for Makeup): ";
                cin >> brand_or_color;
                shop.addProduct(new SkincareProduct(name, price, brand_or_color));  // Example for adding skincare product
                break;
            }
            case 2: {
                string name, email;
                cout << "Enter customer name: ";
                cin >> name;
                cout << "Enter customer email: ";
                cin >> email;
                shop.addCustomer(new Customer(name, email));
                break;
            }
            case 3:
                shop.displayProducts();
                break;
            case 4:
                shop.displayCustomers();
                break;
            case 5:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
