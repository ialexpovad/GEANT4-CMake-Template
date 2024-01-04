set(LIBRARY_TARGET_NAME ${PROJECT_NAME})

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")


# Find Geant4 package, activating all available UI and Vis drivers by default
option(WITH_GEANT4_UIVIS "Build with all Geant4 UIs and all visualization drivers" ON)
option(WITH_GEANT4_OPENGL "Build with Geant4 shell UI and OpenGl visualization" OFF)
option(WITH_GEANT4_QT "Build with Geant4 Qt UI" OFF)

if(WITH_GEANT4_OPENGL)
	find_package(Geant4 REQUIRED vis_opengl_x11 ui_tcsh)
elseif(WITH_GEANT4_QT)
	find_package(Geant4 REQUIRED qt)
elseif(WITH_GEANT4_UIVIS)
	find_package(Geant4 REQUIRED ui_all vis_all)
else()
	find_package(Geant4 REQUIRED)
endif()

add_definitions(${Geant4_DEFINITIONS})
include(${Geant4_USE_FILE})
set(LIBS ${LIBS} ${Geant4_LIBRARIES})

# Switch for static / shared library building.
if(Geant4_shared_FOUND)
	set(LIBRARY_MODE "SHARED")
else()
	set(LIBRARY_MODE "STATIC")
endif()

# Find ROOT package as needed
option(WITH_ROOT "Enable ROOT." OFF)
if(WITH_ROOT)
	set(CMAKE_CXX_FLAGS "-DWITH_ROOT ${CMAKE_CXX_FLAGS}")
  set(CMAKE_CXX_FLAGS "-DROOTSYS ${CMAKE_CXX_FLAGS}")
  find_package(ROOT REQUIRED)
  include_directories(${ROOT_INCLUDE_DIRS})
	set(LIBS ${LIBS} ${ROOT_LIBRARIES})
endif()

# Adds a library target called ${LIBRARY_TARGET_NAME} to be built from the
# source and header files listed in the command invocation.
add_library(${LIBRARY_TARGET_NAME} ${LIBRARY_MODE} ${sources} ${headers})

add_library(${PROJECT_NAME}::${LIBRARY_TARGET_NAME} ALIAS ${LIBRARY_TARGET_NAME})

set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES VERSION ${${PROJECT_NAME}_VERSION} PUBLIC_HEADER "${headers}")

target_include_directories(${LIBRARY_TARGET_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                                                         "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")

target_link_libraries(${LIBRARY_TARGET_NAME} ${LIBS})

# Specify installation targets, typology and destination folders.
install(TARGETS ${LIBRARY_TARGET_NAME}
        EXPORT  ${PROJECT_NAME}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_TARGET_NAME}" COMPONENT dev)


message(STATUS "Created target ${LIBRARY_TARGET_NAME} for export ${PROJECT_NAME}.")