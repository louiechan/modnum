cmake_minimum_required(VERSION 3.7)
project(modnum)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INSTALL_PREFIX /usr/local)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(SOURCE_FILES include/Utils.h include/Matrix.h src/Utils.cpp src/Matrix.cpp include/modnum.h)

add_library(modnum_shared SHARED ${SOURCE_FILES})
add_library(modnum_static STATIC ${SOURCE_FILES})

set_target_properties(modnum_shared PROPERTIES OUTPUT_NAME "modnum")
set_target_properties(modnum_static PROPERTIES OUTPUT_NAME "modnum")

install(TARGETS modnum_shared LIBRARY DESTINATION lib)
install(TARGETS modnum_static ARCHIVE DESTINATION lib)
install(FILES include/modnum.h DESTINATION include)
install(FILES include/Utils.h DESTINATION include)
install(FILES include/Matrix.h DESTINATION include)
