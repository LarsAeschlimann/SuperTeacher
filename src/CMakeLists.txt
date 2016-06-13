project(superteacher)

find_package (Threads REQUIRED)
find_package(SFML 2.1 REQUIRED COMPONENTS graphics window system audio)

if(MSVC)
   set(Boost_USE_STATIC_LIBS       ON)
   set(Boost_USE_STATIC_RUNTIME    ON)
   set(Boost_ALL_DYN_LINK         OFF)
else()
   set(Boost_USE_STATIC_LIBS       OFF)
   set(Boost_USE_STATIC_RUNTIME    OFF)
   set(Boost_ALL_DYN_LINK           ON)   # force dynamic linking for all libraries
   ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK) # Tell boost.log to use dynamic linking
endif()

set(Boost_USE_MULTITHREADED      ON)

find_package(Boost 1.54 REQUIRED COMPONENTS system filesystem log)

include( ExternalJson )

include_directories(
        ${SFML_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR}
)

link_directories(${Boost_LIBRARY_DIRS})

add_executable(superteacher
        main.cpp
        Path.cpp Path.h
        ResourceManager.cpp ResourceManager.h
        HIManager.cpp HIManager.h
        Physics.cpp Physics.h
        Object.cpp Object.h
        Background.cpp Background.h
        Logs.cpp Logs.h
        JSON.h
        Ground.cpp Ground.h
        Character.cpp Character.h
		View.cpp View.h
		Text.cpp Text.h
		Interactives.cpp Interactives.h
        Pencil.cpp Pencil.h)


add_dependencies(superteacher JSON)

target_link_libraries(superteacher
        ${CMAKE_THREAD_LIBS_INIT}
        ${SFML_LIBRARIES}
        ${Boost_LIBRARIES})
install(TARGETS superteacher RUNTIME DESTINATION bin)

set_property(TARGET superteacher PROPERTY CXX_STANDARD 14)
set_property(TARGET superteacher PROPERTY CXX_STANDARD_REQUIRED ON)
