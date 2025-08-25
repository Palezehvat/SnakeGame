#ifndef UISETTINGS_H
#define UISETTINGS_H

#include <QColor>
#include <QCoreApplication>

namespace UISettings {
    constexpr unsigned int maxWidth = 15;
    constexpr unsigned int minWidth = 3;
    constexpr unsigned int maxHeight = 10;
    constexpr unsigned int minHeight = 3;

    constexpr qreal currentSizeCell = 40;

    const QString backgroundButtonInScoreColor = "#aad851";
    const QString borderButtonInScoreColor = "#57a800";
    const QString hoverButtonInScoreColor = "#78db0d";
    const QString hoverTextColor = "#1c89c4";
    const QString textColor = "white";
    const QString buttonBackgroundColor = "#888";
    const QString sliderGrooveBackgroundColor = "#555";
    const QString sliderHandleBackgroundColor = "lightgray";

    const QString colorEvenFieldInGame = "#aad851";
    const QString colorOddFieldInGame = "#a2d04c";
    const QString colorBackgroundInGame = "#568b33";
    const QString colorBackgroundScore = "#aad840";

    const QString backgroundPathMainMenu   = "/../images/mainmenu/background.png";
    const QString settingsIconPathMainMenu = "/../images/mainmenu/iconSettings.png";

    const QString backgroundPathSettings   = "/../images/settings/background.png";
} // UISettings

#endif // UISETTINGS_H