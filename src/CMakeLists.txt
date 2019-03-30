find_package(boost REQUIRED)
find_package(fmt REQUIRED)

add_executable(
        lox

        main.cc
        lox.cc
        scanner.cc
        token.cc
        error.cc
)

target_include_directories(
        lox
        PUBLIC
        ../includes
)

target_link_libraries(
        lox
        PRIVATE
        ${boost_LIBS}
        ${fmt_LIBS}
)

target_include_directories(
        lox
        PRIVATE
        ${boost_INCLUDES}
        ${fmt_INCLUDES}
)