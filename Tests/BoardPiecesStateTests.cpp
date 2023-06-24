#include "pch.h"

#include "../src/BoardPiecesState.h"

// 12 elements
auto testState = std::initializer_list<BoardPiece>{
    {std::make_shared<BoardPieceDescription>(), std::make_shared<BoardPieceDescription>()},
    {std::make_shared<BoardPieceDescription>(), std::make_shared<BoardPieceDescription>()},
    {std::make_shared<BoardPieceDescription>(), std::make_shared<BoardPieceDescription>()},
    {std::make_shared<BoardPieceDescription>(), std::make_shared<BoardPieceDescription>()},
    {std::make_shared<BoardPieceDescription>(), std::make_shared<BoardPieceDescription>()},
    {std::make_shared<BoardPieceDescription>(), std::make_shared<BoardPieceDescription>()},
    {std::make_shared<BoardPieceDescription>(), std::make_shared<BoardPieceDescription>()},
    {std::make_shared<BoardPieceDescription>(), std::make_shared<BoardPieceDescription>()},
    {std::make_shared<BoardPieceDescription>(), std::make_shared<BoardPieceDescription>()},
    {std::make_shared<BoardPieceDescription>(), std::make_shared<BoardPieceDescription>()},
    {std::make_shared<BoardPieceDescription>(), std::make_shared<BoardPieceDescription>()},
    {std::make_shared<BoardPieceDescription>(), std::make_shared<BoardPieceDescription>()}
};

TEST(BoardPiecesStateTests, WHEN_passed_invlid_state_THEN_throw_exception) {
    auto stateData = std::make_shared<std::vector<BoardPiece>>(testState);
    EXPECT_ANY_THROW(BoardPiecesState(stateData, 5, 4));
}

TEST(BoardPiecesStateTests, WHEN_passed_valid_state_THEN_create_instance) {
    auto stateData = std::make_shared<std::vector<BoardPiece>>(testState);
    EXPECT_NO_THROW(BoardPiecesState(stateData, 3, 4));
}



TEST(BoardPiecesStateTests, WHEN_used_invalid_coords_THEN_return_nullptr) {
    auto stateData = std::make_shared<std::vector<BoardPiece>>(testState);
    BoardPiecesState state(stateData, 3, 4);

    EXPECT_EQ(nullptr, state.at(5, 2));
    EXPECT_EQ(nullptr, state.at(-1, 2));
    EXPECT_EQ(nullptr, state.at(2, 7));
    EXPECT_EQ(nullptr, state.at(2, -3));
}

TEST(BoardPiecesStateTests, WHEN_used_valid_coords_THEN_return_piece) {
    auto stateData = std::make_shared<std::vector<BoardPiece>>(testState);
    BoardPiecesState state(stateData, 3, 4);

    EXPECT_EQ(&(stateData->at(2 * 3 + 0)), (BoardPiece*)state.at(0, 2));
    EXPECT_EQ(&(stateData->at(0 * 3 + 1)), (BoardPiece*)state.at(1, 0));
}

TEST(BoardPiecesStateTests, WHEN_asked_for_iterator_THEN_return_valid_iterator) {
    auto stateData = std::make_shared<std::vector<BoardPiece>>(testState);
    BoardPiecesState state(stateData, 3, 4);

    for (auto statePiece : state) {

    }

    EXPECT_EQ(stateData->begin(), state.begin());
}
