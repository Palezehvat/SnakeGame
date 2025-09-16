#include <gtest/gtest.h>
#include "snake.h"

TEST(snake, isInitializationSnakeCorrectly) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(10, 15);
    ASSERT_NE(snake, nullptr);
}

TEST(snake, isInitializationBodySnakeCorrectly) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(10, 15);
    std::shared_ptr<std::vector<QPoint>> bodySnake = snake->getBody();
    ASSERT_EQ(bodySnake->size(), 3);
    ASSERT_EQ((*bodySnake)[0], QPoint(0, 0));
    ASSERT_EQ((*bodySnake)[1], QPoint(1, 0));
    ASSERT_EQ((*bodySnake)[2], QPoint(2, 0));
}

TEST(snake, isInitializationSnakeMovementCorrect) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(10, 15);
    ASSERT_EQ(snake->getCurrentDirection(), nSnake::Movement::Right);
}

TEST(snake, doesMovementChangeWorkCorrectly) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(10, 15);
    snake->setNextDirection(nSnake::Movement::Up);
    snake->move();
    ASSERT_EQ(snake->getCurrentDirection(), nSnake::Movement::Up);
    snake->setNextDirection(nSnake::Movement::Left);
    snake->move();
    ASSERT_EQ(snake->getCurrentDirection(), nSnake::Movement::Left);
    snake->setNextDirection(nSnake::Movement::Down);
    snake->move();
    ASSERT_EQ(snake->getCurrentDirection(), nSnake::Movement::Down);
    snake->setNextDirection(nSnake::Movement::Right);
    snake->move();
    ASSERT_EQ(snake->getCurrentDirection(), nSnake::Movement::Right);
}

TEST(snake, isImpossibleToReverseMovement) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(10, 15);
    snake->setNextDirection(nSnake::Movement::Left);
    snake->move();
    ASSERT_EQ(snake->getCurrentDirection(), nSnake::Movement::Right);
    snake->setNextDirection(nSnake::Movement::Up);
    snake->move();
    snake->setNextDirection(nSnake::Movement::Down);
    snake->move();
    ASSERT_EQ(snake->getCurrentDirection(), nSnake::Movement::Up);
    snake->setNextDirection(nSnake::Movement::Left);
    snake->move();
    snake->setNextDirection(nSnake::Movement::Right);
    snake->move();
    ASSERT_EQ(snake->getCurrentDirection(), nSnake::Movement::Left);
    snake->setNextDirection(nSnake::Movement::Down);
    snake->move();
    snake->setNextDirection(nSnake::Movement::Up);
    snake->move();
    ASSERT_EQ(snake->getCurrentDirection(), nSnake::Movement::Down);
}

TEST(snake, isSnakeChangePositionAfterMoveing) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(10, 15);
    snake->move();
    std::shared_ptr<std::vector<QPoint>> bodySnake = snake->getBody();
    ASSERT_EQ((*bodySnake)[0], QPoint(1, 0));
    ASSERT_EQ((*bodySnake)[1], QPoint(2, 0));
    ASSERT_EQ((*bodySnake)[2], QPoint(3, 0));
    snake->setNextDirection(nSnake::Movement::Up);
    snake->move();
    ASSERT_EQ((*bodySnake)[0], QPoint(2, 0));
    ASSERT_EQ((*bodySnake)[1], QPoint(3, 0));
    ASSERT_EQ((*bodySnake)[2], QPoint(3, -1));
}

TEST(snake, isSnakeGrowingAfterMethodGrow) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(10, 15);
    snake->grow();
    snake->move();
    std::shared_ptr<std::vector<QPoint>> bodySnake = snake->getBody();
    ASSERT_EQ(bodySnake->size(), 4);
    ASSERT_EQ((*bodySnake)[0], QPoint(0, 0));
    ASSERT_EQ((*bodySnake)[1], QPoint(1, 0));
    ASSERT_EQ((*bodySnake)[2], QPoint(2, 0));
    ASSERT_EQ((*bodySnake)[3], QPoint(3, 0));
}

TEST(snake, willTrueReturnedIfSnakeCrashedToUpWall) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(3, 3);
    snake->setNextDirection(nSnake::Movement::Up);
    snake->move();
    ASSERT_EQ(snake->checkCollusion(), true);
}

TEST(snake, willTrueReturnedIfSnakeCrashedToRightWall) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(3, 3);
    snake->move();
    ASSERT_EQ(snake->checkCollusion(), true);
}

TEST(snake, willTrueReturnedIfSnakeCrashedToDownWall) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(3, 3);
    snake->setNextDirection(nSnake::Movement::Down);
    snake->move();
    snake->move();
    snake->move();
    ASSERT_EQ(snake->checkCollusion(), true);
}

TEST(snake, willTrueReturnedIfSnakeCrashedToLeftWall) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(3, 3);
    snake->setNextDirection(nSnake::Movement::Down);
    snake->move();
    snake->setNextDirection(nSnake::Movement::Left);
    snake->move();
    snake->move();
    snake->move();
    ASSERT_EQ(snake->checkCollusion(), true);
}

TEST(snake, willFalseReturnedIfSnakeNotCrashedToWallsAndOwnBody) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(4, 4);
    ASSERT_EQ(snake->checkCollusion(), false);
    snake->move();
    ASSERT_EQ(snake->checkCollusion(), false);
}

TEST(snake, willTrueReturnedIfSnakeCrashedToOwnBody) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(5, 5);
    snake->grow();
    snake->grow();
    snake->move();
    snake->move();
    snake->setNextDirection(nSnake::Movement::Down);
    snake->move();
    snake->setNextDirection(nSnake::Movement::Left);
    snake->move();
    snake->setNextDirection(nSnake::Movement::Up);
    snake->move();
    ASSERT_EQ(snake->checkCollusion(), true);
}

TEST(snake, isNextSnakeHeadPositionCorrect) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(4, 4);
    ASSERT_EQ(snake->getNextHeadPosition(), QPoint(3, 0));
    snake->move();
    snake->setNextDirection(nSnake::Movement::Down);
    ASSERT_EQ(snake->getNextHeadPosition(), QPoint(3, 1));
    snake->move();
    snake->setNextDirection(nSnake::Movement::Left);
    ASSERT_EQ(snake->getNextHeadPosition(), QPoint(2, 1));
}

TEST(snake, isRestartClearCurrentSnakeAndDirectionCorrect) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(4, 4);
    std::shared_ptr<std::vector<QPoint>> bodySnake = snake->getBody();
    snake->setNextDirection(nSnake::Movement::Down);
    snake->grow();
    snake->move();
    snake->restart(4, 4);
    ASSERT_EQ(bodySnake->size(), 3);
    ASSERT_EQ((*bodySnake)[0], QPoint(0, 0));
    ASSERT_EQ((*bodySnake)[1], QPoint(1, 0));
    ASSERT_EQ((*bodySnake)[2], QPoint(2, 0));
    ASSERT_EQ(snake->getCurrentDirection(), nSnake::Movement::Right);
}

TEST(snake, isRestartClearCurrentSnakeAndDirectionCorrectAfterCreateSnake) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(4, 4);
    snake->restart(4, 4);
    std::shared_ptr<std::vector<QPoint>> bodySnake = snake->getBody();
    ASSERT_EQ(bodySnake->size(), 3);
    ASSERT_EQ((*bodySnake)[0], QPoint(0, 0));
    ASSERT_EQ((*bodySnake)[1], QPoint(1, 0));
    ASSERT_EQ((*bodySnake)[2], QPoint(2, 0));
    ASSERT_EQ(snake->getCurrentDirection(), nSnake::Movement::Right);
}

TEST(snake, isInterpolationWorkCorrectWithTheValueParameterTEqualToZero) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(4, 4);
    snake->move();
    auto currBody = snake->getInterpolatedBody(0);
    ASSERT_EQ(currBody.size(), 3);
    ASSERT_EQ(currBody[0], QPointF(0, 0));
    ASSERT_EQ(currBody[1], QPointF(1, 0));
    ASSERT_EQ(currBody[2], QPointF(2, 0));
}

TEST(snake, isInterpolationWorkCorrectWithTheValueParameterTEqualToOne) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(4, 4);
    snake->move();
    auto currBody = snake->getInterpolatedBody(1);
    ASSERT_EQ(currBody.size(), 3);
    ASSERT_EQ(currBody[0], QPointF(1, 0));
    ASSERT_EQ(currBody[1], QPointF(2, 0));
    ASSERT_EQ(currBody[2], QPointF(3, 0));
}

TEST(snake, isInterpolationWorkCorrectWithTheValueParameterTEqualToHalfOne) {
    std::shared_ptr<nSnake::Snake> snake = std::make_shared<nSnake::Snake>(4, 4);
    snake->move();
    auto currBody = snake->getInterpolatedBody(0.5);
    ASSERT_EQ(currBody.size(), 3);
    ASSERT_EQ(currBody[0], QPointF(0.5, 0));
    ASSERT_EQ(currBody[1], QPointF(1.5, 0));
    ASSERT_EQ(currBody[2], QPointF(2.5, 0));
}