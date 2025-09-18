#include "uisettings.h"

namespace UISettings {
    QFont findBestSizeFont(int height, int width, QFont font, QString text, int maxSize,
                           int minSize) {
        while (minSize <= maxSize) {
            int currentSize = (minSize + maxSize) / 2;
            font.setPointSize(currentSize);
            QFontMetrics fm(font);
            
            int textW = fm.horizontalAdvance(text);
            int textH = fm.height();
            
            if (textW > width || textH > height) {
                maxSize = currentSize - 1;
            } else {
                minSize = currentSize + 1;
            }
        }
        font.setPointSize(maxSize);
        return font;
    }

    QFont workWithButton(QPushButton* button) {
        int widthButton = button->size().width() - 8;
        int heightButton = button->size().height() - 4;
        QFont fontButton = button->font();
        QString textButton = button->text();
        return findBestSizeFont(heightButton, widthButton, fontButton, textButton);
    }
}