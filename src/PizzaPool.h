#pragma once
#include "Ingredient.h"
#include <vector>
#include <map>
#include "Pizza.h"
#include "Preparation.h"
#include <queue>

class PizzaPool {
private:
    std::vector<Pizza> pizzas;  // Store all Pizza objects
    std::queue<int> availableIndices;  // Queue of indices representing available Pizza objects
public:
    PizzaPool(std::vector<Ingredient>& ingr);
    Pizza acquirePizza();
    void releasePizza(Pizza& pizza);
    const vector<Pizza> getPizzas() const;
    const queue<int> getAvailableIndices() const;

};
