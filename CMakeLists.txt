cmake_minimum_required(VERSION 3.14)

project(graphics-engine)

add_library(math STATIC
    src/math/src/vector2.cpp
    src/math/src/vector3.cpp
)

target_include_directories(math PUBLIC
    ${PROJECT_SOURCE_DIR}/src/math/include
)

add_executable(graphics-engine
    src/main.cpp
    src/app.cpp
)

target_link_libraries(graphics-engine PRIVATE math)


include(CPack)

set(CPACK_PACKAGE_NAME "graphics-engine")
set(CPACK_PACKAGE_VERSION "1.0.0")

if(WIN32)
  set(CPACK_GENERATOR "ZIP")
elseif(APPLE)
  set(CPACK_GENERATOR "ZIP")
else()
  set(CPACK_GENERATOR "ZIP")
endif()