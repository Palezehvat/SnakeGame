#include "food.h"

namespace nFood {
    Food::Food(int length, int width) {
        numberOfCellsLength = length;
        numberOfCellsWidth = width;

        logger = Log::Logger::getLogger();
        logger->info("Класс Food успешно инициализирован");
    }

    void Food::respawn(const std::vector<QPoint>& freeCells) {
        if (freeCells.empty()) {
            position = std::nullopt;
            return;
        }
        int index = QRandomGenerator::global()->bounded(static_cast<int>(freeCells.size()));
        position = freeCells[index];
        logger->info("Одна единица еды успешно создана");
    }

    std::optional<QPoint> Food::getPosition() const {
        return position;
    }
}