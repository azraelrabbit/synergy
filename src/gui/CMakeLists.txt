cmake_minimum_required(VERSION 3.0)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED) #LinguistTools
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#ile(GLOB GUI_TRANSLATIONS "res/lang/*.ts")
#qt5_add_translation (TRANSLATIONS ${GUI_TRANSLATIONS})

#execute_process(
#	COMMAND lrelease -silent ${GUI_TRANSLATIONS}
#	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#	ERROR_QUIET
#)

file(GLOB GUI_SOURCE_FILES "src/*.cpp" "src/*.h" "src/*.ui" ."./lib/ipc/Ipc.h")

if (APPLE)
	set(GUI_SOURCE_FILES ${GUI_SOURCE_FILES} "src/OSXHelpers.h" "src/OSXHelpers.mm")
endif()

add_executable (synergygui WIN32
	${GUI_SOURCE_FILES}
	"res/win/Synergy.rc"
	"res/Synergy.qrc"
)


add_dependencies(synergygui libressl)
target_link_libraries(synergygui ${OPENSSL_LIBCRYPTO})
if (WIN32)
	target_link_libraries(synergygui Ws2_32)
	add_custom_command(
		TARGET synergygui
		POST_BUILD
		COMMAND windeployqt.exe "${EXECUTABLE_OUTPUT_PATH}/synergygui.exe"
	)
endif()

include_directories(
	./src
	../lib
	${OPENSSL_INCLUDE}
)

qt5_use_modules(synergygui Widgets Network)

if (MSVC)
	set_target_properties(synergygui PROPERTIES LINK_FLAGS "/NODEFAULTLIB:LIBCMT")
endif()

if (APPLE)
	#set (MACOSX_BUNDLE_ICON_FILE Synergy.icns)
	#set (QSYNERGY_ICONS ${CMAKE_CURRENT_SOURCE_DIR}/res/mac/Synergy.icns)
	#set_source_files_properties ($QSYNERGY_ICONS} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()
