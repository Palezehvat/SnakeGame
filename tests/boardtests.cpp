#include <gtest/gtest.h>
#include "gameboard.h"

TEST(board, isInitializationGameBoardCorrectly) {
    std::shared_ptr<nGameBoard::GameBoard> board = std::make_shared<nGameBoard::GameBoard>();
    ASSERT_NE(board, nullptr);
}

TEST(board, isCreateBoardWorkCorrectly) {
    std::shared_ptr<nGameBoard::GameBoard> board = std::make_shared<nGameBoard::GameBoard>();
    board->createBoard(3, 3);
    EXPECT_NO_THROW({
        const auto& cell1 = board->getCell(0, 0);
        const auto& cell2 = board->getCell(1, 0);
        const auto& cell3 = board->getCell(2, 0);
        const auto& cell4 = board->getCell(0, 1);
        const auto& cell5 = board->getCell(1, 1);
        const auto& cell6 = board->getCell(2, 1);
        const auto& cell7 = board->getCell(0, 2);
        const auto& cell8 = board->getCell(1, 2);
        const auto& cell9 = board->getCell(2, 2);
    });
}

TEST(board, isInCreatedBoardExistSnake) {
    std::shared_ptr<nGameBoard::GameBoard> board = std::make_shared<nGameBoard::GameBoard>();
    board->createBoard(3, 3);
    const auto& cell1 = board->getCell(0, 0);
    const auto& cell2 = board->getCell(1, 0);
    const auto& cell3 = board->getCell(2, 0);

    ASSERT_EQ(cell1.type, nGameBoard::TypeCell::snake);
    ASSERT_EQ(cell2.type, nGameBoard::TypeCell::snake);
    ASSERT_EQ(cell3.type, nGameBoard::TypeCell::snake);
}

TEST(board, isInCreatedBoardCellsExceptSnakeAreGrass) {
    std::shared_ptr<nGameBoard::GameBoard> board = std::make_shared<nGameBoard::GameBoard>();
    board->createBoard(3, 3);
    const auto& cell1 = board->getCell(0, 1);
    const auto& cell2 = board->getCell(1, 1);
    const auto& cell3 = board->getCell(2, 1);
    const auto& cell4 = board->getCell(0, 2);
    const auto& cell5 = board->getCell(1, 2);
    const auto& cell6 = board->getCell(2, 2);

    ASSERT_EQ(cell1.type, nGameBoard::TypeCell::grass);
    ASSERT_EQ(cell2.type, nGameBoard::TypeCell::grass);
    ASSERT_EQ(cell3.type, nGameBoard::TypeCell::grass);
    ASSERT_EQ(cell4.type, nGameBoard::TypeCell::grass);
    ASSERT_EQ(cell5.type, nGameBoard::TypeCell::grass);
    ASSERT_EQ(cell6.type, nGameBoard::TypeCell::grass);
}

TEST(board, isSetCellWorkCorrectly) {
    std::shared_ptr<nGameBoard::GameBoard> board = std::make_shared<nGameBoard::GameBoard>();
    board->createBoard(3, 3);
    ASSERT_EQ(board->getCell(2,2).type, nGameBoard::TypeCell::grass);
    board->setCell(2, 2, nGameBoard::TypeCell::rock);
    ASSERT_EQ(board->getCell(2,2).type, nGameBoard::TypeCell::rock);
}

TEST(board, isGetEmptyCellsWorkCorrectly) {
    std::shared_ptr<nGameBoard::GameBoard> board = std::make_shared<nGameBoard::GameBoard>();
    board->createBoard(3, 3);
    board->setCell(2, 2, nGameBoard::TypeCell::rock);
    auto emptyCells = board->getEmptyCells();
    
    ASSERT_EQ(emptyCells.size(), 5);

    for (auto positionCell : emptyCells) {
        auto cell = board->getCell(positionCell.x(), positionCell.y());
        ASSERT_EQ(cell.type, nGameBoard::TypeCell::grass);
    }
}

TEST(board, isRestartWorkCorrectly) {
    std::shared_ptr<nGameBoard::GameBoard> board = std::make_shared<nGameBoard::GameBoard>();
    board->createBoard(3, 3);
    board->setCell(2, 2, nGameBoard::TypeCell::rock);
    auto emptyCells = board->getEmptyCells();
    
    ASSERT_EQ(emptyCells.size(), 5);

    for (auto positionCell : emptyCells) {
        auto cell = board->getCell(positionCell.x(), positionCell.y());
        ASSERT_EQ(cell.type, nGameBoard::TypeCell::grass);
    }
}