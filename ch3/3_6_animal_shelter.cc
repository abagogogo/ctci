#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

class Animal {
public:
    Animal(void) {
        name = "unknown";
        order = -1;
    }

    const string &get_name(void) {
        return name;
    }

    int get_order(void) {
        return order;
    }

    void set_order(int _order) {
        order = _order;
    }

protected:
    string  name;
    int     order;
};

class Dog : public Animal {
public:
    Dog(void) {
        name = "dog";
    }
};

class Cat : public Animal {
public:
    Cat(void) {
        name = "cat";
    }
};

struct cmp {
    bool operator()(Animal *lhs, Animal *rhs) {
        return (lhs->get_order() >= rhs->get_order());
    }
};

class Shelter {
public:
    Shelter(void) {
        order =  0;
    }

    void enqueue(Animal *animal) {
        animal->set_order(order++);
        if (animal->get_name() == "dog") {
            cout << "enqueue dog, order=" << animal->get_order() << endl;
            dog_q.push(animal);
        } else {
            cout << "enqueue cat, order=" << animal->get_order() << endl;
            cat_q.push(animal);
        }
    }

    Animal *dequeue(void) {
        Animal *animal = nullptr;

        if (!dog_q.empty() && !cat_q.empty()) {
            if (dog_q.top()->get_order() <= cat_q.top()->get_order()) {
                animal = dog_q.top();
                dog_q.pop();
                cout << "pop dog_q: " << animal->get_order() << endl;
            } else {
                animal = cat_q.top();
                cat_q.pop();
                cout << "pop cat_q: " << animal->get_order() << endl;
            }
            return animal;
        } else if (dog_q.empty() && cat_q.empty()) {
            cout << "both dog_q and cat_q are empty" << endl;
            return animal;
        } if (dog_q.empty()) {
            animal = cat_q.top(); 
            cat_q.pop();
            cout << "dog_q empty => pop cat_q: " << animal->get_order() << endl;
            return animal;
        } else {
            animal = dog_q.top(); 
            dog_q.pop();
            cout << "cat_q empty => pop dog_q: " << animal->get_order() << endl;
            return animal;
        }
    }

protected:
    int order;
    //priority_queue<Animal *, vector<Animal *>, decltype(&order_compare)> dog_q(order_compare); // NG: core dumps as the function order_compare is not acturally used.
    priority_queue<Animal *, vector<Animal *>, cmp> dog_q, cat_q;
};

int main(void) {
    Dog d0, d1, d2, d3;
    Cat c0, c1, c2, c3;
    vector<Animal *> animals = {&d0, &d1, &d2, &d3, &c0, &c1, &c2, &c3};
    Shelter shelter;

    for (Animal *a : animals) {
        shelter.enqueue(a);
    }

    Animal *a;
    while ((a = shelter.dequeue())) {
        cout << a->get_name() << ", order=" << a->get_order() << endl;
    }
    return 0;
}
