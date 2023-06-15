//
// Created by Sarah Zakon on 14/06/2023.
//
#pragma once
#include "Ingredient.h"
#include <vector>
#include <map>
#include "Pizza.h"
#include "Preparation.h"
#include <queue>


#ifndef GLOUTON_PIZZAPOOL_H
#define GLOUTON_PIZZAPOOL_H


class PizzaPool {
private:
    std::vector<Pizza> pizzas;  // Store all Pizza objects
    std::queue<int> availableIndices;  // Queue of indices representing available Pizza objects
    Pizza* firstAvailable;
public:
    PizzaPool(const std::vector<Ingredient>& ingr);
    Pizza& acquirePizza();
    void releasePizza(Pizza& pizza);

};



#endif //GLOUTON_PIZZAPOOL_H