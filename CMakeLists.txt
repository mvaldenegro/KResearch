project(kresearch)
find_package(KDE4 REQUIRED)
include (KDE4Defaults)

include_directories(${KDE4_INCLUDES})
include_directories(src)

if (CMAKE_COMPILER_IS_GNUCXX)
  set ( CMAKE_CXX_FLAGS "-Wall -pedantic -Wno-long-long")
endif ()

set(kresearch_SRCS src/main.cpp src/MainWindow.cpp
                   src/ui/CollectionDockWidget.cpp src/ui/InformationDockWidget.cpp src/ui/PreviewTab.cpp
                   src/ui/PublicationEditDialog.cpp src/ui/AuthorEditWidget.cpp src/ui/ConcealedTabWidget.cpp
                   src/LibraryView.cpp src/BaseView.cpp src/AuthorView.cpp src/JournalView.cpp
                   src/library/LibraryManager.cpp
                   src/library/Author.cpp src/library/Document.cpp src/library/Journal.cpp src/library/BaseEntity.cpp
                   src/library/Repository.cpp
                   src/library/dao/AuthorDAO.cpp src/library/dao/DocumentDAO.cpp src/library/dao/BaseDAO.cpp
                   src/library/dao/JournalDAO.cpp
                   src/library/model/DocumentModel.cpp src/library/model/AuthorModel.cpp src/library/model/JournalModel.cpp
                   src/import/PublicationImportService.cpp src/import/PDFImportWizard.cpp
                   src/import/PDFImportWizardTitlePage.cpp src/import/PDFImportWizardAuthorPage.cpp
                   src/library/sqlite/SQLiteAuthorDAO.cpp src/library/sqlite/SQLiteRepository.cpp
                   src/library/sqlite/SQLiteDocumentDAO.cpp src/library/sqlite/SQLiteBaseDAO.cpp 
                   src/library/sqlite/SQLiteJournalDAO.cpp
                   src/pdfwidget/PDFDocumentWidget.cpp src/pdfwidget/PDFDocumentDialog.cpp
                   )

kde4_add_ui_files(kresearch_SRCS src/import/TitlePage.ui src/import/AuthorPage.ui src/ui/PublicationEdit.ui
                                 src/ui/PublicationInformation.ui src/ui/AuthorEdit.ui)

set(QT_USE_QTSQL true)
INCLUDE(${QT_USE_FILE}) 

kde4_add_executable(kresearch ${kresearch_SRCS})
target_link_libraries(kresearch ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${QT_LIBRARIES} ${KDE4_KPARTS_LIBS} poppler-qt4)

install(TARGETS kresearch ${INSTALL_TARGETS_DEFAULT_ARGS})
