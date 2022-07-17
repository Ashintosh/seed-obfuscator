cmake_minimum_required(VERSION 3.5)

project(seed-encryptor  VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/aboutwindow.cpp
        src/seedstringtools.cpp
        src/bip39.cpp
        src/seedencryptor.cpp
        src/crypto/crypto.cpp
)

set(HEADERS
    src/mainwindow.h
    src/aboutwindow.h
    src/seedstringtools.h
    src/bip39.h
    src/seedencryptor.h
    src/crypto/crypto.h
)

set(UI
    src/mainwindow.ui
    src/aboutwindow.ui
)

set(RESOURCES
    images.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(seed-encryptor
        MANUAL_FINALIZATION
        ${SOURCES}
        ${HEADERS}
        ${UI}
        ${RESOURCES}
    )
else()
    add_executable(seed-encryptor
        ${SOURCES}
        ${HEADERS}
        ${UI}
    )
endif()

target_link_libraries(seed-encryptor PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${CMAKE_SOURCE_DIR}/external/lib/cryptopp/libcryptopp.a
)

set_target_properties(seed-encryptor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER ashs.club
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(seed-encryptor )
endif()
