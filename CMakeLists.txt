project(kapman)

find_package(KDE4 REQUIRED)
find_package(LibKDEGames REQUIRED)

include(KDE4Defaults)
include(MacroOptionalDependPackage)
MACRO_OPTIONAL_DEPEND_PACKAGE(LibKDEGames "kdegames")

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
	images/burger_test.svg
	images/carrot_test.svg
	images/chicken_test.svg
	images/donut_test.svg
	images/energizer_test.svg
	images/ghostblue.svg
	images/ghostgreen.svg
	images/ghostpink.svg
	images/ghostred.svg
	images/kapmanAnimTest.svg
	images/kapmanMaze.svg
	images/pill_test.svg
	images/pizza_test.svg
	images/spider_test.svg
	images/tomato_test.svg
	kapmanui.rc
)
set(kapmanSound
)

kde4_install_icons(${ICON_INSTALL_DIR})

kde4_add_executable(kapman ${kapmanSources})

kde4_add_unit_test(characterTest
	bonus.cpp
	cell.cpp
	character.cpp
	element.cpp
	energizer.cpp
	kapman.cpp
	maze.cpp
	mazeparser.cpp
	pill.cpp
	./tests/charactertest.cpp
)
kde4_add_unit_test(gameTest
	bonus.cpp
	cell.cpp
	character.cpp
	element.cpp
	energizer.cpp
	game.cpp
	ghost.cpp
	kapman.cpp
	maze.cpp
	mazeparser.cpp
	pill.cpp
	./tests/gametest.cpp
)
kde4_add_unit_test(ghostTest
	bonus.cpp
	cell.cpp
	character.cpp
	element.cpp
	energizer.cpp
	ghost.cpp
	kapman.cpp
	maze.cpp
	mazeparser.cpp
	pill.cpp
	./tests/ghosttest.cpp
)
kde4_add_unit_test(kapmanTest
	energizer.cpp
	bonus.cpp
	cell.cpp
	character.cpp
	element.cpp
	kapman.cpp
	maze.cpp
	mazeparser.cpp
	pill.cpp
	./tests/kapmantest.cpp
)

target_link_libraries(kapman ${KDE4_KDEUI_LIBS}	${KDE4_PHONON_LIBS} kdegames)
target_link_libraries(characterTest ${QT_QTTEST_LIBRARY} ${KDE4_KDEUI_LIBS} ${KDE4_PHONON_LIBS} kdegames)
target_link_libraries(gameTest ${QT_QTTEST_LIBRARY} ${KDE4_KDEUI_LIBS} ${KDE4_PHONON_LIBS} kdegames)
target_link_libraries(ghostTest ${QT_QTTEST_LIBRARY} ${KDE4_KDEUI_LIBS} ${KDE4_PHONON_LIBS} kdegames)
target_link_libraries(kapmanTest ${QT_QTTEST_LIBRARY} ${KDE4_KDEUI_LIBS} ${KDE4_PHONON_LIBS} kdegames)

install(TARGETS kapman DESTINATION ${BIN_INSTALL_DIR})
install(FILES ${kapmanData} DESTINATION ${DATA_INSTALL_DIR}/kapman)
install(FILES ${kapmanSound} DESTINATION ${SOUND_INSTALL_DIR}/kapman)
