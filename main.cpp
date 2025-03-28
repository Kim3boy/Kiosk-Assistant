#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// Base class for a generic items in the kiosk
class Item {
protected:
    std::string name;
    double price;

public:
    Item(const std::string& name, double price) : name(name), price(price) {}
    virtual ~Item() { std::cout << "Item destructor called for " << name << "\n"; }

    const std::string& getName() const { return name; }

    virtual void display() const {
        std::cout << "Name: " << name << ", Price: $" << price << "\n";
    }
};

// Derived class for a product in the kiosk
class Product : public Item {
private:
    int stock;

public:
    Product(const std::string& name, double price, int stock)
        : Item(name, price), stock(stock) {}

    int getStock() const { return stock; }

    void restock(int quantity) { stock += quantity; }
    bool sell(int quantity) {
        if (quantity <= stock) {
            stock -= quantity;
            return true;
        }
        return false;
    }

    void display() const override {
        Item::display();
        std::cout << "Stock: " << stock << "\n";
    }
};

// Class representing the kiosk
class Kiosk {
private:
    std::vector<Product> inventory;

public:
    void addProduct(const Product& product) {
        inventory.push_back(product);
    }

    void displayProducts() const {
        std::cout << "Available Products:\n";
        for (const auto& product : inventory) {
            product.display();
        }
    }

    void sellProduct(const std::string& productName, int quantity) {
        for (auto& product : inventory) {
            if (product.getName() == productName) {
                if (product.sell(quantity)) {
                    std::cout << "Sold " << quantity << " of " << productName << ".\n";
                } else {
                    std::cout << "Insufficient stock for " << productName << ".\n";
                }
                return;
            }
        }
        std::cout << "Product " << productName << " not found.\n";
    }
};

// Function overloading example
void displayMessage(const std::string& message) {
    std::cout << message << "\n";
}

void displayMessage(const std::string& message, int count) {
    std::cout << message << " (Count: " << count << ")\n";
}

// Operator overloading example
class Discount {
private:
    double percentage;

public:
    Discount(double percentage) : percentage(percentage) {}

    double operator()(double price) const {
        return price - (price * percentage / 100);
    }
};

// Exception handling example
void checkStock(int stock) {
    if (stock < 0) {
        throw std::invalid_argument("Stock cannot be negative!");
    }
}

int main() {
    try {
        Kiosk kiosk;

        // Adding products to the kiosk
        kiosk.addProduct(Product("Soda", 1.50, 20));
        kiosk.addProduct(Product("Chips", 2.00, 15));
        kiosk.addProduct(Product("Candy", 0.75, 30));

        // Displaying available products
        kiosk.displayProducts();

        // Selling products
        kiosk.sellProduct("Soda", 5);
        kiosk.sellProduct("Chips", 20);

        // Displaying updated inventory
        kiosk.displayProducts();

        // Function overloading
        displayMessage("Welcome to the kiosk!");
        displayMessage("Products available", 3);

        // Operator overloading
        Discount discount(10); // 10% discount
        double discountedPrice = discount(2.00);
        std::cout << "Discounted price: $" << discountedPrice << "\n";

        // Exception handling
        checkStock(-5); // This will throw an exception

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}