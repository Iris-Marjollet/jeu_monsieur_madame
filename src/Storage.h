#pragma once
#include "Kitchen.h"


class Storage : public Kitchen {
public:
    explicit Storage(Ingredient ingredient, int prepId);
    bool isStorage();

};