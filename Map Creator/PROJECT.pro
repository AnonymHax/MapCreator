######################################################################
# Automatically generated by qmake (2.01a) jeu. 19. avr. 04:08:58 2012
######################################################################

# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O3

QT += core gui

TARGET = MapCreator
TEMPLATE = app


INCLUDEPATH += C:\SFML\include #\
               #C:\QJson\src

#LIBS += -Lc:\QJson\lib -lqjson
win32:CONFIG(release, debug|release):LIBS += C:\SFML\lib\libsfml-system.a \
        C:\SFML\lib\libsfml-window.a \
        C:\SFML\lib\libsfml-graphics.a \
        C:\SFML\lib\libsfml-audio.a \
        C:\SFML\lib\libsfml-network.a

win32:CONFIG(debug, debug|release):LIBS += C:\SFML\lib\libsfml-system-d.a \
        C:\SFML\lib\libsfml-window-d.a \
        C:\SFML\lib\libsfml-graphics-d.a \
        C:\SFML\lib\libsfml-audio-d.a \
        C:\SFML\lib\libsfml-network-d.a



HEADERS += \
    GUI/ObjectLayer.h \
    GUI/Render.h \
    GUI/ObjectElementContainer.h \
    GUI/Object.h \
    GUI/MapRender.h \
    GUI/FPS.h \
    GAME_ELEMENTS/Selector.h \
    GAME_ELEMENTS/Light.h \
    GAME_ELEMENTS/Element.h \
    GAME_ELEMENTS/Cube.h \
    GAME_ELEMENTS/Collision.h \
    GAME_ELEMENTS/Cell.h \
    GAME_ELEMENTS/Tile.h \
    MANAGERS/MapManager.h \
    MANAGERS/LightManager.h \
    SYSTEM/Singleton.h \
    SYSTEM/Public.h \
    SYSTEM/BaseEngine.h \
    GUI/UnmovableItem.h \
    GUI/Movable_Item.h \
    GUI/MapGlobal.h \
    SYSTEM/Manager.h \
    MANAGERS/TileManager.h \
    SYSTEM/IdGenerator.h \
    GUI/QSFMLCanvas.h \
    GAME_ELEMENTS/ElementContainer.h \
    GAME_ELEMENTS/DirectionalLight.h \
    GAME_ELEMENTS/GameLayer.h \
    GAME_ELEMENTS/Effect.h \
    SYSTEM/TileEditorDialog.h \
    GAME_ELEMENTS/TileAnimationData.h \
    SYSTEM/MainWindow.h \
    SYSTEM/ToolWidget.h \
    SYSTEM/LayerWidget.h \
    SYSTEM/NewMapDialog.hpp \
    SYSTEM/GoToWidget.h \
    SYSTEM/LightWidget.h \
    SYSTEM/TilesWidget.h \

SOURCES += \
    GUI/Render.cpp \
    GUI/QSFMLCanvas.cpp \
    GUI/ObjectLayer.cpp \
    GUI/ObjectContainer.cpp \
    GUI/Object.cpp \
    GUI/MapRender.cpp \
    GUI/FPS.cpp \
    GAME_ELEMENTS/Selector.cpp \
    GAME_ELEMENTS/Light.cpp \
    GAME_ELEMENTS/Element.cpp \
    GAME_ELEMENTS/Cube.cpp \
    GAME_ELEMENTS/Collision.cpp \
    GAME_ELEMENTS/Cell.cpp \
    GAME_ELEMENTS/Tile.cpp \
    MANAGERS/MapManager.cpp \
    MANAGERS/LightManager.cpp \
    SYSTEM/Public.cpp \
    main.cpp \
    SYSTEM/BaseEngine.cpp \
    GUI/UnmovableItem.cpp \
    GUI/Movable_Item.cpp \
    GUI/MapGlobal.cpp \
    SYSTEM/IdGenerator.cpp \
    MANAGERS/TileManager.cpp \
    GAME_ELEMENTS/ElementContainer.cpp \
    GAME_ELEMENTS/DirectionalLight.cpp \
    GAME_ELEMENTS/GameLayer.cpp \
    GAME_ELEMENTS/Effect.cpp \
    SYSTEM/TileEditorDialog.cpp \
    GAME_ELEMENTS/TileAnimationData.cpp \
    SYSTEM/MainWindow.cpp \
    SYSTEM/ToolWidget.cpp \
    SYSTEM/LayerWidget.cpp \
    SYSTEM/NewMapDialog.cpp \
    SYSTEM/GoToWidget.cpp \
    SYSTEM/LightWidget.cpp \
    SYSTEM/TilesWidget.cpp \

RESOURCES += \
    resources.qrc \

#RC_FILE = icon.rc \