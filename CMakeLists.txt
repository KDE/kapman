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
	kapman.cpp
	kapmanview.cpp)

# build exec
kde4_add_executable(kapman ${kapmanSources})

# libraries needed
target_link_libraries(kapman
	${KDE4_KDEUI_LIBS}
	kdegames
)

# install the binary
install(TARGETS kapman DESTINATION ${BIN_INSTALL_DIR})
install(FILES kapmanui.rc  DESTINATION  ${DATA_INSTALL_DIR}/kapman)
