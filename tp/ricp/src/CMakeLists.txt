ADD_LIBRARY (ricp CollectionReader.h CollectionReader.cpp CollectionWriter.h CollectionWriter.cpp Document.h Document.cpp envDefault.h)
TARGET_LINK_LIBRARIES(ricp z)