project(kapman)

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
set(kapmanData
	defaultmaze.xml
	kapmanui.rc
)
file(GLOB themes
	"themes/*.svgz"
	"themes/*.desktop"
	"themes/*.copyright"
	"themes/*.png"
)
file(GLOB sounds_ogg "sounds/*.ogg")

kde4_add_kcfg_files(kapman_SRCS settings.kcfgc)

kde4_install_icons(${ICON_INSTALL_DIR})

kde4_add_app_icon(kapman_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/hi*-app-kapman.png"})
kde4_add_executable(kapman ${kapman_SRCS})

target_link_libraries(kapman ${KDE4_KDEUI_LIBS} ${KDE4_PHONON_LIBS} ${QT_QTXML_LIBRARY} kdegames kdegamesprivate)

install(TARGETS kapman ${INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS kapman.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES ${kapmanData} DESTINATION ${DATA_INSTALL_DIR}/kapman)
install(FILES ${themes} DESTINATION ${DATA_INSTALL_DIR}/kapman/themes)
install(FILES ${sounds_ogg} DESTINATION ${SOUND_INSTALL_DIR}/kapman)

