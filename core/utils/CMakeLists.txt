add_library(utils STATIC
    include/bounded_counter.h
)
target_include_directories(utils
    PUBLIC include/
)
set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)
