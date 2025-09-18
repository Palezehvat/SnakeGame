#include <gtest/gtest.h>
#include "food.h"

TEST(food, isInitializationFoodCorrectly) {
    std::shared_ptr<nFood::Food> food = std::make_shared<nFood::Food>();
    ASSERT_NE(food, nullptr);
}

TEST(food, isRespawnReallyChoosesPosition) {
    std::shared_ptr<nFood::Food> food = std::make_shared<nFood::Food>();
    food->respawn({QPoint(0, 0), QPoint(1, 2)});
    std::optional<QPoint> positionWhereFood = food->getPosition();
    ASSERT_NE(positionWhereFood, std::nullopt);
}

TEST(food, isRespawnReallyChoosesCorrectPosition) {
    std::shared_ptr<nFood::Food> food = std::make_shared<nFood::Food>();
    food->respawn({QPoint(0, 0), QPoint(1, 2)});
    std::optional<QPoint> positionWhereFood = food->getPosition();
    ASSERT_TRUE(positionWhereFood.value() == QPoint(0, 0) ||
                positionWhereFood.value() == QPoint(1, 2));
}

TEST(food, isRespawnReallyNotChoosesPositionIfVectorFreeCellsEmpty) {
    std::shared_ptr<nFood::Food> food = std::make_shared<nFood::Food>();
    food->respawn({});
    std::optional<QPoint> positionWhereFood = food->getPosition();
    ASSERT_EQ(positionWhereFood, std::nullopt);
}

TEST(food, isClearWorkCorrectly) {
    std::shared_ptr<nFood::Food> food = std::make_shared<nFood::Food>();
    food->respawn({QPoint(0, 0), QPoint(1, 2)});
    food->clear();
    std::optional<QPoint> positionWhereFood = food->getPosition();
    ASSERT_EQ(positionWhereFood, std::nullopt);
}

TEST(food, isClearReturnedCorrectPosition) {
    std::shared_ptr<nFood::Food> food = std::make_shared<nFood::Food>();
    food->respawn({QPoint(0, 0), QPoint(1, 2)});
    std::optional<QPoint> positionWhereFood = food->clear();
    ASSERT_TRUE(positionWhereFood.value() == QPoint(0, 0) ||
                positionWhereFood.value() == QPoint(1, 2));
}