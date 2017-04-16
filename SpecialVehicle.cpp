#include "SpecialVehicle.hpp"

SpecialVehicle::SpecialVehicle(Board & board, vector<Coordinate2D> coordinates): HorizontalVehicle(board, coordinates) {
}

SpecialVehicle::~SpecialVehicle() {
}

//overrides moveleft/right to change isInWinningSpace