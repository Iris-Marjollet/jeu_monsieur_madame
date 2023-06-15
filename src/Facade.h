#pragma once
#include "Ingredient.h"
#include <vector>
#include <map>
#include "Pizza.h"
#include "Kitchen.h"
#include "Storage.h"
#include <memory>
#include <optional>
#include "Drawing.h"
#include "colors.h"
#include <SFML/Graphics.hpp>

struct Ingr {
    Ingredient ingredient;
    bool added;
};


class Facade {
private:
    std::vector<Pizza> pizzas;
    std::vector<Storage> storages;
    std::vector<Preparation> preparations;
    std::map<std::string, Ingr> ingredients;
    std::optional<Kitchen> selected;
    std::string selected_type;
    int score;
    // Declare other member functions and variables

public:
    sf::RenderWindow window;
    Facade();  // Constructor
    void init();
    void draw_init();
    void startCooking(Preparation preparation);
    int addIngredient(Pizza pizza);
    sf::Texture loadTextureFromFile(const std::string& filePath);
};
