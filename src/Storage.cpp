#include "Storage.h"
#include "Kitchen.h"


Storage::Storage(Ingredient ingredient) : Kitchen(ingredient) {
}


bool Storage::isStorage(){
    return true;
}
