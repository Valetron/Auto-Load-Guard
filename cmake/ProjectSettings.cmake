set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_CREATOR_SKIP_CONAN_SETUP ON)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(DEBUG "ccache found")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
endif()

find_package(Git)
if(Git_FOUND)
    message(DEBUG "Git found at ${GIT_EXECUTABLE}")
    execute_process(COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_HASH_COMMIT
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    message(DEBUG "Hash commit: ${GIT_HASH_COMMIT}")
    set(Project_HASH ${GIT_HASH_COMMIT})
else()
    set(Project_HASH 0)
endif()

# TODO: version from git tag?
#set(PROJECT_VESRION ${Project_VERSION_MAJOR}.${Project_VERSION_MINOR}.${Project_VERSION_PATCH})

# NOTE: нужен ли на MSVC?
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#add_compile_definitions(UNICODE) # TODO: хочу ли я использовать функции с W окончанием


if (MSVC)
# NOTE: https://cmake.org/cmake/help/latest/prop_tgt/COMMON_LANGUAGE_RUNTIME.html
    add_compile_options(
#        /W4            # NOTE: это или Wall?
        /Wall
        /fsanitize
        /MP             # TODO: проверить с и без. Должен сократить время компиляции
    )
else() # TODO: подумать над clang, mingw
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
