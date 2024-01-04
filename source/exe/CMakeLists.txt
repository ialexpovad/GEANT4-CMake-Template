set(EXE_TARGET_NAME ${PROJECT_NAME}_exe)

add_executable(${EXE_TARGET_NAME} main.cpp)

target_link_libraries(${EXE_TARGET_NAME} ${PROJECT_NAME}::${PROJECT_NAME})

install(TARGETS ${EXE_TARGET_NAME} DESTINATION bin)