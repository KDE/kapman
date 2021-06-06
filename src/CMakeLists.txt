ecm_setup_version(${RELEASE_SERVICE_VERSION}
    VARIABLE_PREFIX KAPMAN
    VERSION_HEADER kapman_version.h
)

add_executable(kapman)

target_sources(kapman PRIVATE
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

    kapman.qrc
)

kconfig_add_kcfg_files(kapman settings.kcfgc)

file(GLOB ICONS_SRCS "${CMAKE_SOURCE_DIR}/icons/*-apps-kapman.png")
ecm_add_app_icon(kapman ICONS ${ICONS_SRCS})

target_link_libraries(kapman 
    KF5KDEGames
    KF5KDEGamesPrivate
    KF5::DBusAddons
    KF5::XmlGui
    KF5::Crash
    Qt::Svg
    Qt::Xml
)

install(TARGETS kapman ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS org.kde.kapman.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.kapman.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES defaultmaze.xml DESTINATION ${KDE_INSTALL_DATADIR}/kapman)
