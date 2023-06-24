#pragma once

#include <memory>
#include "BoardPieceDescription.h"

struct BoardPiece {
    std::shared_ptr<BoardPieceDescription> backgroundLayer;
    std::shared_ptr<BoardPieceDescription> actionLayer;
};