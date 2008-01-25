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
	main.cpp
	kapmanmainwindow.cpp
	game.cpp
	gameview.cpp
	maze.cpp
	cell.cpp
	mazeparser.cpp
	mazeitem.cpp
	kapman.cpp
	kapmanitem.cpp
	ghost.cpp
	gamescene.cpp
	character.cpp
	characteritem.cpp
)

# resources
set(kapmanResources
	kapmanui.rc
	defaultmaze.xml
	images/kapmanMaze.svg
	images/kapman_test.svg
	images/redGhost_test.svg
	images/greenGhost_test.svg
	images/blueGhost_test.svg
	images/pinkGhost_test.svg)

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
	./tests/ghosttest.cpp
)
# Character test unit
kde4_add_unit_test(characterTest
	character.cpp
	maze.cpp
	mazeparser.cpp
	cell.cpp
	kapman.cpp
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
