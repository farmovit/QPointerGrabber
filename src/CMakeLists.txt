set(SOURCES QPointerGrabber.cpp APointerGrabberImpl_p.cpp WindowEventsWatcher_p.cpp)
set(HEADERS QPointerGrabber.h APointerGrabberImpl_p.h WindowEventsWatcher_p.h grabber_export.h)

add_definitions(-D${PROJECT_NAME}_SHARED_LIBRARY)

if(WIN32)
    set(SOURCES ${SOURCES} win/WinPointerGrabberImpl_p.cpp)
    set(HEADERS ${HEADERS} win/WinPointerGrabberImpl_p.h)
elseif(UNIX)
    set(SOURCES ${SOURCES} lin/LinuxPointerGrabberImpl_p.cpp lin/FiniteTimer_p.cpp)
    set(HEADERS ${HEADERS} lin/LinuxPointerGrabberImpl_p.h lin/FiniteTimer_p.h)
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets)
if (UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::X11Extras)
endif()
