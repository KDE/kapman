project(kapman)

cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)
set (QT_MIN_VERSION "5.3.0")

find_package(ECM 1.3.0 REQUIRED CONFIG)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Widgets Qml Quick QuickWidgets Svg Test)
find_package(KF5 REQUIRED COMPONENTS 
    CoreAddons
    Config
    ItemModels
    WidgetsAddons
    WindowSystem
    Config
    DBusAddons
    I18n
    ConfigWidgets
    TextWidgets
    XmlGui
    KIO
    NotifyConfig
    NewStuff
    KDELibs4Support)

find_package(KF5KDEGames 4.9.0 REQUIRED)
find_package(Phonon4Qt5 CONFIG REQUIRED)

include_directories(BEFORE ${PHONON_INCLUDES})

include(FeatureSummary)
include(ECMInstallIcons)
include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
add_definitions(-DTRANSLATION_DOMAIN="kapman")



add_subdirectory(doc)

set(kapman_SRCS
	bonus.cpp
	cell.cpp
	character.cpp
	characteritem.cpp
	element.cpp
	elementitem.cpp
	energizer.cpp
	game.cpp
	gamescene.cpp
	gameview.cpp
	ghost.cpp
	ghostitem.cpp
	kapman.cpp
	kapmanitem.cpp
	kapmanmainwindow.cpp
	kapmanparser.cpp
	main.cpp
	maze.cpp
	mazeitem.cpp
	pill.cpp
)
file(GLOB themes
	"themes/*.svgz"
	"themes/*.desktop"
	"themes/*.copyright"
	"themes/*.png"
)
file(GLOB sounds_ogg "sounds/*.ogg")

kconfig_add_kcfg_files(kapman_SRCS settings.kcfgc)

ecm_install_icons(ICONS hi128-apps-kapman.png  hi16-apps-kapman.png  hi22-apps-kapman.png  hi32-apps-kapman.png  hi48-apps-kapman.png  hi64-apps-kapman.png DESTINATION ${ICON_INSTALL_DIR})

kde4_add_app_icon(kapman_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/hi*-apps-kapman.png")
add_executable(kapman ${kapman_SRCS})

target_link_libraries(kapman  Phonon::phonon4qt5 Qt5::Xml KF5KDEGames KF5KDEGamesPrivate Qt5::Svg)

install(TARGETS kapman ${INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS org.kde.kapman.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES kapman.appdata.xml DESTINATION ${DATA_INSTALL_DIR}/appdata)
install(FILES kapmanui.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/kapman)
install(FILES defaultmaze.xml DESTINATION ${DATA_INSTALL_DIR}/kapman)
install(FILES ${themes} DESTINATION ${DATA_INSTALL_DIR}/kapman/themes)
install(FILES ${sounds_ogg} DESTINATION ${SOUND_INSTALL_DIR}/kapman)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
