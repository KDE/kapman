project(kapman)

cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)
set (QT_MIN_VERSION "5.3.0")

find_package(ECM 1.7.0 REQUIRED CONFIG)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Widgets Svg)
find_package(KF5 REQUIRED COMPONENTS 
    CoreAddons
    Config
    WindowSystem
    Config
    I18n
    ConfigWidgets
    XmlGui
    KIO
    NotifyConfig
    )

find_package(KF5KDEGames 4.9.0 REQUIRED)
find_package(Phonon4Qt5 CONFIG REQUIRED)

include_directories(BEFORE ${PHONON_INCLUDES})

include(FeatureSummary)
include(ECMInstallIcons)
include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)
include(ECMAddAppIcon)

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
add_definitions(-DTRANSLATION_DOMAIN="kapman")
add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")


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

ecm_install_icons(ICONS hi128-apps-kapman.png  hi16-apps-kapman.png  hi22-apps-kapman.png  hi32-apps-kapman.png  hi48-apps-kapman.png  hi64-apps-kapman.png DESTINATION ${KDE_INSTALL_ICONDIR})

file(GLOB ICONS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/hi*-apps-kapman.png")
ecm_add_app_icon(kapman_SRCS ICONS ${ICONS_SRCS})
add_executable(kapman ${kapman_SRCS})

target_link_libraries(kapman 
   Phonon::phonon4qt5
   KF5KDEGames
   KF5KDEGamesPrivate
   Qt5::Svg
   Qt5::Xml
   KF5::DBusAddons
   KF5::XmlGui
)

install(TARGETS kapman ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS org.kde.kapman.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES kapman.appdata.xml DESTINATION ${KDE_INSTALL_DATADIR}/appdata)
install(FILES kapmanui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/kapman)
install(FILES defaultmaze.xml DESTINATION ${KDE_INSTALL_DATADIR}/kapman)
install(FILES ${themes} DESTINATION ${KDE_INSTALL_DATADIR}/kapman/themes)
install(FILES ${sounds_ogg} DESTINATION ${KDE_INSTALL_SOUNDDIR}/kapman)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
