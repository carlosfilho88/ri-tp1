INCLUDE_DIRECTORIES(${TP_SOURCE_DIR}/ricp/src)

ADD_EXECUTABLE(ircpReader testReader)
TARGET_LINK_LIBRARIES(ircpReader ricp z)
ADD_EXECUTABLE(ircpWriter testWriter)
TARGET_LINK_LIBRARIES(ircpWriter ricp z)