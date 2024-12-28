#include <iostream>
#include <vector>
#include <string>

class Product {
protected:
    std::string name;
    double price;

public:
    Product(const std::string& name = "", double price = 0.0) : name(name), price(price) {}

    virtual void display() const {
        std::cout << "Название: " << name << "\nЦена: " << price << "\n";
    }

    virtual void modifyPrice(double newPrice) {
        price = newPrice;
    }

    double getPrice() const {
        return price;
    }

    virtual ~Product() {}

    virtual std::string getCategory() const = 0;
};

class ElectronicWatch : public Product {
private:
    std::string brand;

public:
    ElectronicWatch(const std::string& name, double price, const std::string& brand)
        : Product(name, price), brand(brand) {}

    void display() const override {
        Product::display();
        std::cout << "Бренд: " << brand << "\n";
    }

    std::string getCategory() const override {
        return "Электронные часы";
    }

    void modifyBrand(const std::string& newBrand) {
        brand = newBrand;
    }
};

class Confectionery : public Product {
private:
    double weight;

public:
    Confectionery(const std::string& name, double price, double weight)
        : Product(name, price), weight(weight) {}

    void display() const override {
        Product::display();
        std::cout << "Вес: " << weight << " кг\n";
    }

    std::string getCategory() const override {
        return "Кондитерские изделия";
    }

    void modifyWeight(double newWeight) {
        weight = newWeight;
    }
};

void findCheapestProduct(const std::vector<Product*>& products) {
    if (products.empty()) {
        std::cout << "Нет товаров для анализа.\n";
        return;
    }

    Product* cheapest = products[0];
    for (const auto& product : products) {
        if (product->getPrice() < cheapest->getPrice()) {
            cheapest = product;
        }
    }

    std::cout << "Самый дешевый товар: \n";
    cheapest->display();
}

void displayMenu() {
    std::cout << "\nМеню:\n"
              << "1. Добавить электронные часы\n"
              << "2. Добавить кондитерское изделие\n"
              << "3. Показать все товары\n"
              << "4. Изменить цену товара\n"
              << "5. Найти самый дешевый товар\n"
              << "0. Выход\n"
              << "Ваш выбор: ";
}

int main() {
    std::vector<Product*> products;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name, brand;
                double price;
                std::cout << "Введите название, цену и бренд: ";
                std::cin >> name >> price >> brand;
                products.push_back(new ElectronicWatch(name, price, brand));
                break;
            }
            case 2: {
                std::string name;
                double price, weight;
                std::cout << "Введите название, цену и вес (в кг): ";
                std::cin >> name >> price >> weight;
                products.push_back(new Confectionery(name, price, weight));
                break;
            }
            case 3:
                for (const auto& product : products) {
                    product->display();
                    std::cout << "--------------------\n";
                }
                break;
            case 4: {
                int index;
                double newPrice;
                std::cout << "Введите индекс товара для изменения цены (начиная с 0): ";
                std::cin >> index;
                if (index >= 0 && index < static_cast<int>(products.size())) {
                    std::cout << "Введите новую цену: ";
                    std::cin >> newPrice;
                    products[index]->modifyPrice(newPrice);
                    std::cout << "Цена изменена.\n";
                } else {
                    std::cout << "Неверный индекс.\n";
                }
                break;
            }
            case 5:
                findCheapestProduct(products);
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    for (auto product : products) {
        delete product;
    }

    return 0;
}
