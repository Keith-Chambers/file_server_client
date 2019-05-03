cmake_minimum_required(VERSION 2.8)

set(SERVER_PROJECT_NAME "file_server")
set(CLIENT_PROJECT_NAME "file_client")

set(BUILD_DIR "build")
set(CLIENT_SRC_DIR "client")
set(SERVER_SRC_DIR "server")
set(COMMON_SRC_DIR "common/src")
set(COMMON_INC_DIR "common/include")

project(SysSoftwareAssignment2)

# Server Setup
add_executable(${SERVER_PROJECT_NAME} ${SERVER_SRC_DIR}/main.c ${SERVER_SRC_DIR}/server.c)

target_link_libraries(${SERVER_PROJECT_NAME} PUBLIC "pthread")
target_include_directories(${SERVER_PROJECT_NAME} PRIVATE ${COMMON_INC_DIR}/)

# Client Setup
add_executable(${CLIENT_PROJECT_NAME}   ${CLIENT_SRC_DIR}/main.c
                                        ${CLIENT_SRC_DIR}/client.c
                                        ${COMMON_SRC_DIR}/file.c
                                        ${COMMON_SRC_DIR}/message.c
                                        ${COMMON_SRC_DIR}/util.c
                                        )

target_include_directories(${CLIENT_PROJECT_NAME} PRIVATE ${COMMON_INC_DIR}/)
