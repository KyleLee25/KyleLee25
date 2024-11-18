#include <iostream>
#include <string>
#include <limits>

struct Item {
    int id;
    std::string name;
    double price;
    int quantity;
    Item* next;
};

class Inventory {
private:
    Item* head;

public:
    Inventory() : head(nullptr) {}

    void AddItem() {
        int id;
        std::cout << "Enter Item ID: ";
        std::cin >> id;
        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a numeric ID.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        if (FindItemById(id)) {
            std::cout << "Item with ID " << id << " already exists.\n";
            return;
        }

        std::string name;
        std::cout << "Enter Item Name: ";
        std::getline(std::cin, name);

        double price;
        std::cout << "Enter Item Price: ";
        while (!(std::cin >> price) || price < 0) {
            std::cout << "Invalid input. Enter a positive number for price: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int quantity;
        std::cout << "Enter Quantity in Stock: ";
        while (!(std::cin >> quantity) || quantity < 0) {
            std::cout << "Invalid input. Enter a positive integer for quantity: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Item* newItem = new Item{id, name, price, quantity, head};
        head = newItem;
        std::cout << "Item added successfully!\n";
    }

    void RemoveItem(int id) {
        if (!head) {
            std::cout << "Inventory is empty. No item to remove.\n";
            return;
        }

        if (head->id == id) {
            Item* temp = head;
            head = head->next;
            delete temp;
            std::cout << "Item removed successfully!\n";
            return;
        }

        Item* current = head;
        while (current->next && current->next->id != id) {
            current = current->next;
        }

        if (current->next) {
            Item* temp = current->next;
            current->next = current->next->next;
            delete temp;
            std::cout << "Item removed successfully!\n";
        } else {
            std::cout << "Item not found. Cannot remove.\n";
        }
    }

    Item* FindItemById(int id) {
        Item* current = head;
        while (current) {
            if (current->id == id) return current;
            current = current->next;
        }
        return nullptr;
    }

    Item* FindItemByName(const std::string& name) {
        Item* current = head;
        while (current) {
            if (current->name == name) return current;
            current = current->next;
        }
        return nullptr;
    }

    void DisplayItems() const {
        if (!head) {
            std::cout << "Inventory is empty.\n";
            return;
        }

        Item* current = head;
        while (current) {
            std::cout << "ID: " << current->id << ", Name: " << current->name
                      << ", Price: $" << current->price
                      << ", Quantity: " << current->quantity << "\n";
            current = current->next;
        }
    }

    ~Inventory() {
        while (head) {
            Item* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Inventory inventory;
    int choice;

    do {
        std::cout << "\nInventory Management System\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. Remove Item\n";
        std::cout << "3. Search Item by ID\n";
        std::cout << "4. Search Item by Name\n";
        std::cout << "5. Display All Items\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail()) {
            std::cout << "Invalid choice. Please enter a valid number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        int id;
        std::string name;

        switch (choice) {
            case 1:
                inventory.AddItem();
                break;
            case 2:
                std::cout << "Enter Item ID to remove: ";
                std::cin >> id;
                if (std::cin.fail()) {
                    std::cout << "Invalid input. Please enter a numeric ID.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                inventory.RemoveItem(id);
                break;
            case 3:
                std::cout << "Enter Item ID to search: ";
                std::cin >> id;
                if (std::cin.fail()) {
                    std::cout << "Invalid input. Please enter a numeric ID.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                if (Item* item = inventory.FindItemById(id)) {
                    std::cout << "Item found - ID: " << item->id << ", Name: " << item->name
                              << ", Price: $" << item->price
                              << ", Quantity: " << item->quantity << "\n";
                } else {
                    std::cout << "Item not found.\n";
                }
                break;
            case 4:
                std::cout << "Enter Item Name to search: ";
                std::getline(std::cin, name);
                if (Item* item = inventory.FindItemByName(name)) {
                    std::cout << "Item found - ID: " << item->id << ", Name: " << item->name
                              << ", Price: $" << item->price
                              << ", Quantity: " << item->quantity << "\n";
                } else {
                    std::cout << "Item not found.\n";
                }
                break;
            case 5:
                inventory.DisplayItems();
                break;
            case 0:
                std::cout << "Exiting the system.\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
