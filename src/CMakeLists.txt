ecm_setup_version(${RELEASE_SERVICE_VERSION}
    VARIABLE_PREFIX KAPMAN
    VERSION_HEADER kapman_version.h
)

add_executable(kapman)

target_sources(kapman PRIVATE
    bonus.cpp
    bonus.h
    cell.cpp
    cell.h
    character.cpp
    character.h
    characteritem.cpp
    characteritem.h
    element.cpp
    element.h
    elementitem.cpp
    elementitem.h
    energizer.cpp
    energizer.h
    game.cpp
    game.h
    gamescene.cpp
    gamescene.h
    gameview.cpp
    gameview.h
    ghost.cpp
    ghost.h
    ghostitem.cpp
    ghostitem.h
    kapman.cpp
    kapman.h
    kapmanitem.cpp
    kapmanitem.h
    kapmanmainwindow.cpp
    kapmanmainwindow.h
    kapmanparser.cpp
    kapmanparser.h
    main.cpp
    maze.cpp
    maze.h
    mazeitem.cpp
    mazeitem.h
    pill.cpp
    pill.h

    kapman.qrc
)

kconfig_add_kcfg_files(kapman settings.kcfgc)

file(GLOB ICONS_SRCS "${CMAKE_SOURCE_DIR}/icons/*-apps-kapman.png")
ecm_add_app_icon(kapman ICONS ${ICONS_SRCS})

target_link_libraries(kapman
    KF5KDEGames
    KF5::CoreAddons
    KF5::DBusAddons
    KF5::XmlGui
    KF5::Crash
    Qt${QT_MAJOR_VERSION}::Svg
    Qt${QT_MAJOR_VERSION}::Xml
)
if (QT_MAJOR_VERSION STREQUAL "6")
    target_link_libraries(kapman Qt6::SvgWidgets)
endif()
install(TARGETS kapman ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS org.kde.kapman.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.kapman.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES defaultmaze.xml DESTINATION ${KDE_INSTALL_DATADIR}/kapman)
