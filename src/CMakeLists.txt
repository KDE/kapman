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

if(APPLE)
    set_target_properties(kapman PROPERTIES
        MACOSX_BUNDLE_DISPLAY_NAME "Kapman"
        MACOSX_BUNDLE_BUNDLE_NAME "Kapman"
        MACOSX_BUNDLE_LONG_VERSION_STRING "Kapman ${RELEASE_SERVICE_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}"
        MACOSX_BUNDLE_BUNDLE_VERSION "${RELEASE_SERVICE_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.kde.kapman"
        MACOSX_BUNDLE_COPYRIGHT "2024 The Kapman Developers")
endif()

target_link_libraries(kapman
    KDEGames6
    KF6::CoreAddons
    KF6::DBusAddons
    KF6::XmlGui
    KF6::Crash
    KF6::I18n
    KF6::IconThemes
    Qt6::Svg
    Qt6::SvgWidgets
    Qt6::Xml
)

install(TARGETS kapman ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS org.kde.kapman.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.kapman.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES defaultmaze.xml DESTINATION ${KDE_INSTALL_DATADIR}/kapman)
