project(kapman)

find_package(KDE4 REQUIRED)
find_package(LibKDEGames REQUIRED)

include(KDE4Defaults)

include_directories (${KDE4_INCLUDES})
add_definitions(${KDE4_DEFINITIONS})

set(kapmanSources
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
	main.cpp
	maze.cpp
	mazeitem.cpp
	mazeparser.cpp
	pill.cpp
)
set(kapmanData
	defaultmaze.xml
	images/bonus.svg
	images/energizer.svg
	images/ghostblue.svg
	images/ghostgreen.svg
	images/ghostpink.svg
	images/ghostred.svg
	images/kapman.svg
	images/maze.svg
	images/pill.svg
	kapmanui.rc
)

kde4_install_icons(${ICON_INSTALL_DIR})

kde4_add_executable(kapman ${kapmanSources})

target_link_libraries(kapman ${KDE4_KDEUI_LIBS}	${KDE4_PHONON_LIBS} ${KDEGAMES_LIBRARY})

install(TARGETS kapman ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES ${kapmanData} DESTINATION ${DATA_INSTALL_DIR}/kapman)

