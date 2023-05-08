include_directories(${CMAKE_CURRENT_SOURCE_DIR} Unity/src)

add_executable(list_test utils/list_test.c Unity/src/unity.c)
target_include_directories(list_test PRIVATE ${CMAKE_SOURCE_DIR}/utils)

add_test(NAME list_test COMMAND $<TARGET_FILE:list_test>)


add_executable(message_test http/message_test.c Unity/src/unity.c ${CMAKE_SOURCE_DIR}/http/message.c)
target_include_directories(message_test PRIVATE ${CMAKE_SOURCE_DIR}/http ${CMAKE_SOURCE_DIR})
