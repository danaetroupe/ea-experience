#include <string>
#include<iostream>
#include <utility>
#include <unordered_map>

// https://github.com/danaetroupe/ea-experience
// SEE GITHUB REPOSITORY FOR SOURCE CONTROL

class Item {
private:
    std::string name;
    int quantity;
    float price;

public:
    Item(
            std::string name,
            int quantity,
            float price
    ) :
            name{std::move(name)},
            quantity{quantity},
            price{price} {

    }

    std::string get_name() const {
        return name;
    }

    int get_quantity() const {
        return quantity;
    }

    void set_quantity(int new_quantity) {
        quantity = new_quantity;
    }

    float get_price() const {
        return price;
    }
    
    void set_price(float new_price) {
        price = new_price;
    }

    bool is_match(const std::string &other) {
        return name == other;
    }
};

class Inventory {
private:
    std::unordered_map <std::string, Item*> items;
    float total_money;

    static void display_data(Item &item) {
        std::cout << "\nItem name: " << item.get_name();
        std::cout << "\nQuantity: " << item.get_quantity();
        std::cout << "\nPrice: " << item.get_price();
    }

public:
    Inventory() :
           total_money{0} {

    }

    // Prompts player to submit item info. 
    void add_item() {
        std::string name;
        int quantity;
        float price;

        std::cin.ignore();
        std::cout << "\nEnter item name: ";
        std::cin >> name;
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        std::cout << "Enter price (USD$): ";
        std::cin >> price;
        if (items.count(name) == 0) {
            // Insert new item in inventory
            items[name] = new Item(name, quantity, price);
        }
        // If item already exists...
        else {
            // Identify item within inventory and change values
            Item* item = items[name];
            int current = item->get_quantity();
            item->set_quantity(current + quantity);
            item->set_price(price);
        }
    }
    // Sell item
    void sell_item() {
        std::string name;
        if (list_names()) {
            std::cin.ignore();
            std::cout << "\nEnter item name: ";
            std::cin >> name;

            if (items.count(name) > 0) {
                remove_item(name);
            }
            else {
                std::cout << "\nThis item is not in your Inventory";
            }
        }
        else {
            std::cout << "\nInventory empty.";
        } 
    }
    // Called by sell_item()
    void remove_item(std::string name) {
        int input_quantity;
        Item* item = items[name];
        std::cout << "\nEnter number of items to sell: ";
        std::cin >> input_quantity;

        int quantity = item->get_quantity();
        if (input_quantity <= quantity) {
            float price = item->get_price();
            float money_earned = price * input_quantity;
            item->set_quantity(quantity - input_quantity);
            std::cout << "\nItems sold";
            std::cout << "\nMoney received: " << money_earned;
            total_money += money_earned;
            std::cout << "\nTotal Money: " << total_money;
        if (input_quantity == quantity) {
            delete item;
            items.erase(name);
        }
        } else {
            std::cout << "\nCannot sell more items than you have.";
        }
    }
    // Lists all items in inventory in console
    void list_items() {
        if (items.size() == 0) {
            std::cout << "\nInventory empty.";
            return;
        }

        for (auto item : items) {
            display_data(*item.second);
            std::cout << "\n";
        }
    }
    // Lists names for selling items
    bool list_names() {
        // List names or returns false if empty
        if (items.size() == 0) {
            return false;
        }
        else {
            int count = 1;
            for (auto item : items) {
                std::cout << "\n" << count << ". " << item.first;
                count++;
            }
            return true;
        }
    }
};

// no need to modify anything here
int main() {
    int choice;
    Inventory inventory_system;
    std::cout << "Welcome to the inventory!";

    while (1) {
        std::cout << "\n\nMENU\n"
                  << "1. Add new item\n"
                  << "2. Sell item\n"
                  << "3. List items\n"
                  << "4. Exit\n\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                inventory_system.add_item();
                break;

            case 2:
                inventory_system.sell_item();
                break;

            case 3:
                inventory_system.list_items();
                break;

            case 4:
                exit(0);

            default:
                std::cout << "\nInvalid choice entered";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
        }
    }
}
