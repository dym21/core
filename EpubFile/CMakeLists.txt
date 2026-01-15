# CMakeLists.txt for EpubFile
# Generated from EpubFile.vcxproj

# Source files
set(EpubFile_SOURCES
    src/CBookContentItem.cpp
    src/CBookInfo.cpp
    src/CBookItem.cpp
    src/CBookToc.cpp
    src/CEpubFile.cpp
)

# Header files
set(EpubFile_HEADERS
    src/CBookContentItem.h
    src/CBookInfo.h
    src/CBookItem.h
    src/CBookToc.h
    CEpubFile.h
    src/EpubFile_global.h
)

add_library(EpubFile SHARED
    ${EpubFile_SOURCES}
    ${EpubFile_HEADERS}
)

# Include directories
target_include_directories(EpubFile PUBLIC
    GeneratedFiles/
    GeneratedFiles
    .
)

# Preprocessor definitions
target_compile_definitions(EpubFile PRIVATE
    _WINDOWS
    UNICODE
    _UNICODE
    WIN32
    _ENABLE_EXTENDED_ALIGNED_STORAGE
    WIN64
    EPUBFILE_USE_DYNAMIC_LIBRARY
    INTVER=2.5.565.0
    WIN_INTVER=2,5,565,0
    COPYRIGHT_YEAR=2025
    _WIN32
    NOMINMAX
    _WIN64
    WINDOWS_IGNORE_PACKING_MISMATCH
    NDEBUG
    QT_NO_DEBUG
    QT_PLUGIN
)

# Link libraries
target_link_libraries(EpubFile PRIVATE
    graphics
)

set_target_properties(EpubFile PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "$(SolutionDir)build/bin/win_64"
    ARCHIVE_OUTPUT_DIRECTORY "$(SolutionDir)build/bin/win_64"
)

