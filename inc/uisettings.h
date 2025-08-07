#ifndef UISETTINGS_H
#define UISETTINGS_H

#include <QColor>

namespace UISettings {
    constexpr unsigned int maxWidth = 15;
    constexpr unsigned int maxHeight = 10;
    constexpr unsigned int currentSizeCell = 40;

    const QString hoverTextColor = "#1c89c4";
    const QString textColor = "white";
    const QString buttonBackgroundColor = "#888";
    const QString sliderGrooveBackgroundColor = "#555";
    const QString sliderHandleBackgroundColor = "lightgray";
} // UISettings

#endif // UISETTINGS_H