# project name
project(kapman)

# search packages used by KDE
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalDependPackage)

# search packages used by kdegames
MACRO_OPTIONAL_DEPEND_PACKAGE(LibKDEGames "kdegames")
if(DEPEND_PACKAGE_LibKDEGames)
	macro_optional_find_package(LibKDEGames QUIET)
else(DEPEND_PACKAGE_LibKDEGames)
	macro_log_feature(KDEGAMES_FOUND "libkdegames" "" "" FALSE "" "")
endif(DEPEND_PACKAGE_LibKDEGames)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

include_directories (
	${CMAKE_SOURCE_DIR}
	${CMAKE_BINARY_DIR}
	${KDE4_INCLUDES}
	${KDEGAMES_INCLUDE_DIR}/highscore/
)

# display log message
macro_display_feature_log()

# project sources
set(kapmanSources
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
	kapman.cpp
	kapmanitem.cpp
	kapmanmainwindow.cpp
	main.cpp
	maze.cpp
	mazeitem.cpp
	mazeparser.cpp
	pill.cpp
	bonus.cpp
	ghostitem.cpp
)

kde4_install_icons( ${ICON_INSTALL_DIR}   )


# resources
set(kapmanResources
	kapmanui.rc
	defaultmaze.xml
	images/kapmanMaze.svg
	images/kapmanAnimTest.svg
	images/redGhost_test.svg
	images/greenGhost_test.svg
	images/blueGhost_test.svg
	images/pinkGhost_test.svg
	images/energizer_test.svg
	images/pill_test.svg
	images/carrot_test.svg
	images/burger_test.svg
	images/donut_test.svg
	images/spider_test.svg
	images/tomato_test.svg
	images/chiken_test.svg
	images/pizza_test.svg
)

# build exec
kde4_add_executable(kapman ${kapmanSources})

# libraries needed
target_link_libraries(kapman
	${KDE4_KDEUI_LIBS}
	kdegames
)

# Kapman test unit
kde4_add_unit_test(kapmanTest
	kapman.cpp
	character.cpp
	maze.cpp
	mazeparser.cpp
	cell.cpp
	element.cpp
	pill.cpp
	bonus.cpp
	energizer.cpp
	./tests/kapmantest.cpp
)
# Ghost test unit
kde4_add_unit_test(ghostTest
	ghost.cpp
	character.cpp
	maze.cpp
	mazeparser.cpp
	cell.cpp
	kapman.cpp
	element.cpp
	pill.cpp
	bonus.cpp
	energizer.cpp
	./tests/ghosttest.cpp
)
# Character test unit
kde4_add_unit_test(characterTest
	character.cpp
	maze.cpp
	mazeparser.cpp
	cell.cpp
	kapman.cpp
	element.cpp
	pill.cpp
	bonus.cpp
	energizer.cpp
	./tests/charactertest.cpp
)
# Game test unit
kde4_add_unit_test(gameTest
	kapman.cpp
	ghost.cpp
	character.cpp
	game.cpp
	maze.cpp
	cell.cpp
	mazeparser.cpp
	element.cpp
	pill.cpp
	bonus.cpp
	energizer.cpp
	./tests/gametest.cpp
)

# libraries needed for kapman tests
target_link_libraries(kapmanTest
	${KDE4_KDEUI_LIBS}
	kdegames
	${QT_QTTEST_LIBRARY}
)
# libraries needed for ghost tests
target_link_libraries(ghostTest
	${KDE4_KDEUI_LIBS}
	kdegames
	${QT_QTTEST_LIBRARY}
)
# libraries needed for character tests
target_link_libraries(characterTest
	${KDE4_KDEUI_LIBS}
	kdegames
	${QT_QTTEST_LIBRARY}
)
# libraries needed for game tests
target_link_libraries(gameTest
	${KDE4_KDEUI_LIBS}
	kdegames
	${QT_QTTEST_LIBRARY}
)

# install the binary
install(TARGETS kapman DESTINATION ${BIN_INSTALL_DIR})
install(FILES ${kapmanResources} DESTINATION ${DATA_INSTALL_DIR}/kapman)
