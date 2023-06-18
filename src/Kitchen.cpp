#include "Kitchen.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;


Kitchen::Kitchen(Ingredient ingr, int prepId)
        : ingredient(ingr), selected(false)
{
    this->prepId = prepId;
}

Ingredient Kitchen::getIngredient() {
    return ingredient;
}

bool Kitchen::getSelected() const {
    return selected;
}

void Kitchen::setSelected(bool select) {
    selected = select;
}

std::ostream& operator<<(std::ostream& os, const Kitchen& kitchen)
{
    os << "This is the Kitchen :" << endl;
    os << "ingredient : " << kitchen.ingredient << endl;
    os << "selected : " << kitchen.selected << endl;
    return os;
}

void Kitchen::setSprite(sf::Texture& texture, float scaleFactor, float position, int screenWidth, sf::Sprite jar, float scaleJar, float y_position, sf::Texture& timer) {
    sprite.setTexture(texture);
    sprite.setScale(scaleFactor,scaleFactor);
    sf::Vector2f position_sprite(8*screenWidth/10-position * sprite.getTextureRect().width * scaleFactor, 20);
    sprite.setPosition(position_sprite);
}

sf::Sprite Kitchen::getSprite() const {
    return sprite;
}


void Kitchen::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}



