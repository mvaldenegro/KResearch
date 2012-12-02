project(kresearch)
find_package(KDE4 REQUIRED)
include (KDE4Defaults)

include_directories(${KDE4_INCLUDES})
include_directories(src)

if (CMAKE_COMPILER_IS_GNUCXX)
  set ( CMAKE_CXX_FLAGS "-Wall -pedantic -Wno-long-long")
endif ()

file(GLOB kresearch_SOURCES src/*.cpp src/*/*.cpp src/*/*/*.cpp)

kde4_add_ui_files(kresearch_SOURCES src/import/TitlePage.ui src/import/AuthorPage.ui src/ui/PublicationEdit.ui
                                    src/ui/PublicationInformation.ui src/ui/AuthorEdit.ui)

set(QT_USE_QTSQL true)
INCLUDE(${QT_USE_FILE}) 

kde4_add_executable(kresearch ${kresearch_SOURCES})
target_link_libraries(kresearch ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${QT_LIBRARIES} ${KDE4_KPARTS_LIBS} ${KDE4_KROSSCORE_LIBS} poppler-qt4)

install(TARGETS kresearch ${INSTALL_TARGETS_DEFAULT_ARGS})
