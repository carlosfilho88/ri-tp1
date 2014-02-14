# CmakeLists.txt in src dir

# Adds a library called RICPlib from the source files

ADD_LIBRARY( RICP CollectionReader.h CollectionReader.cpp CollectionWriter.h CollectionWriter.cpp Document.h Document.cpp envDefault.h)
TARGET_LINK_LIBRARIES(RICP z)

