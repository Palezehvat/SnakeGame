#include "food.h"

namespace nFood {
    Food::Food() {
        logger = Log::Logger::getLogger();
        logger->info("Класс Food успешно инициализирован");
    }

    std::optional<QPoint> Food::clear() {
        if (position.has_value()) {
            QPoint pos = position.value();
            position.reset();
            return pos;
        }
        return std::nullopt;
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

    void Food::restart() {
        clear();
    }
}