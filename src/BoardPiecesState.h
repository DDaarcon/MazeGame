#pragma once

#include <exception>

#include "BoardPiece.h"
#include "utils/trusted_ptr.h"

class BoardPiecesState {
public:
    /// <summary>
    /// state dimensions: <br />
    /// <para> width </para>
    /// <para>0, 1, 2, 3, 4</para>
    /// <para>5, 6, 7, 8, 9  height</para>
    /// <para>...          </para>
    /// </summary>
    /// <param name="state"></param>
    /// <param name="width"></param>
    /// <param name="height"></param>
    BoardPiecesState(std::shared_ptr<std::vector<BoardPiece>> state, size_t width, size_t height) 
        : _state(nullptr), _width(width), _height(height) 
    { 
        if (state == nullptr
            || state->size() != width * height) 
        {
            throw std::exception("Invalid state, either null or invalid size");
        }

        _state = state;
    }

    trusted_ptr<BoardPiece> at(size_t x, size_t y) const;

    std::vector<BoardPiece>::iterator begin() { return _state->begin(); }
    std::vector<BoardPiece>::const_iterator begin() const { return static_cast<std::shared_ptr<const std::vector<BoardPiece>>>(_state)->begin(); }
    std::vector<BoardPiece>::iterator end() { return _state->end(); }
    std::vector<BoardPiece>::const_iterator end() const { return static_cast<std::shared_ptr<const std::vector<BoardPiece>>>(_state)->end(); }

    size_t getWidth() { return _width; }
    size_t getHeight() { return _height; }

private:
    bool validateCoords(size_t x, size_t y) const;
    size_t getStateIndex(size_t x, size_t y) const;
    
private:
    std::shared_ptr<std::vector<BoardPiece>> _state;
    size_t _width;
    size_t _height;
};