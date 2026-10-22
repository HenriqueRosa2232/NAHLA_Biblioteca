cmake_minimum_required(VERSION 3.16)

project(NAHLA_Biblioteca VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql) #add sql aqui

set(TS_FILES NAHLA_Biblioteca_pt_BR.ts)

set(PROJECT_SOURCES
    QT/main.cpp
    QT/mainwindow.cpp
    QT/mainwindow.h
    QT/mainwindow.ui
    QT/loginwindow.cpp
    QT/loginwindow.h
    QT/loginwindow.ui
    ${TS_FILES}

    # Implementacoes do sistema original
    #src/Aluno.cpp
    #src/Acervo_Livro.cpp
    #src/Acervo_Pessoas.cpp
    #src/Bibliotecario.cpp
    #src/Funcionario.cpp
    #src/Gerenciador_Emprestimo.cpp
    #src/Gerenciador_Pedidos.cpp
    #src/Livro.cpp
    #src/Usuario.cpp
    #src/Validador.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NAHLA_Biblioteca
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        QT/form.h QT/form.cpp QT/form.ui
        QT/loginwindow.h QT/loginwindow.cpp QT/loginwindow.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET NAHLA_Biblioteca APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(NAHLA_Biblioteca SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(NAHLA_Biblioteca
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_include_directories(NAHLA_Biblioteca PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(NAHLA_Biblioteca
PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql #add sql aqui
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.NAHLA_Biblioteca)
endif()
set_target_properties(NAHLA_Biblioteca PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS NAHLA_Biblioteca
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NAHLA_Biblioteca)
endif()
