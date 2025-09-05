#ifndef UISETTINGS_H
#define UISETTINGS_H

#include <QColor>
#include <QCoreApplication>
#include <QPushButton>
#include <QFont>

namespace UISettings {
    constexpr unsigned int maxWidth            = 15;
    constexpr unsigned int minWidth            = 3;
    constexpr unsigned int maxHeight           = 10;
    constexpr unsigned int minHeight           = 3;

    constexpr qreal currentSizeCell            = 40;

    const QString backgroundButtonInScoreColor = "#aad851";
    const QString borderButtonInScoreColor     = "#57a800";
    const QString hoverButtonInScoreColor      = "#78db0d";
    const QString hoverTextColor               = "#1c89c4";
    const QString textColor                    = "white";
    const QString buttonBackgroundColor        = "#888";
    const QString sliderGrooveBackgroundColor  = "#555";
    const QString sliderHandleBackgroundColor  = "lightgray";

    const QString colorEvenFieldInGame         = "#aad851";
    const QString colorOddFieldInGame          = "#a2d04c";
    const QString colorBackgroundInGame        = "#568b33";
    const QString colorBackgroundScore         = "#aad840";

    const QString firstColorSnake              = "#278017";
    const QString secondColorSnake             = "#23c706";
    const QString colorEyesSnake               = "#e8ba31";

    const QString firstColorApple              = "#d63434";
    const QString secondColorApple             = "#ff4d4d";
    const QString firstColorStickApple         = "#5a3c0a";
    const QString secondColorStickApple        = "#8b5e2b";

    const QString backgroundPathMainMenu       = "/../images/mainmenu/background.png";
    const QString settingsIconPathMainMenu     = "/../images/mainmenu/iconSettings.png";

    const QString backgroundPathSettings       = "/../images/settings/background.png";

    const QString nameFileSettings             = "settings.ini";

    const QString styleToButton                = QString(R"(
        QPushButton {
            background-color: %1;
            padding: 6px;
            border: 1px solid white;
            color: %2;
        }
        QPushButton:hover {
            background-color: %3;
        }
    )").arg(buttonBackgroundColor, textColor, hoverTextColor);

    const QString styleToLabel                 = QString(R"(
        QLabel {
            color: %1;
            font-weight: bold;
        }
    )").arg(textColor);

    const QString styleToMenuButtons           = QString(R"(
        QPushButton {
            background-color: rgba(0, 0, 0, 10);
            color: #33bd06;
            border: %1px solid #30ab07;
            font-weight: bold;
            border-radius: 6px;
            padding: 8px 20px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: rgba(0, 0, 0, 140);
        }
        QPushButton:pressed {
            background-color: rgba(0, 0, 0, 160);
        }
    )");

    QFont findBestSizeFont(int height, int width, QFont font, QString text, int maxSize = 64,
                           int minSize = 1);
    QFont workWithButton(QPushButton* button);
    
} // UISettings

#endif // UISETTINGS_H