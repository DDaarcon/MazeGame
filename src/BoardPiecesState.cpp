#include "BoardPiecesState.h"

trusted_ptr<BoardPiece> BoardPiecesState::at(size_t x, size_t y) const
{
    if (!validateCoords(x, y))
        return trusted_ptr<BoardPiece>(nullptr);

    auto piece = &(_state->at(getStateIndex(x, y)));
    return trusted_ptr<BoardPiece>(piece);
}

bool BoardPiecesState::validateCoords(size_t x, size_t y) const
{
    if (x < 0)
        return false;
    if (x >= _width)
        return false;
    if (y < 0)
        return false;
    if (y >= _height)
        return false;

    return true;
}

size_t BoardPiecesState::getStateIndex(size_t x, size_t y) const
{
    return y * _width + x;
}
