# 标题
cmake_minimum_required(VERSION 3.10.0)
project(GhostEscape VERSION 0.1.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 强制 Debug 模式（优先级最高，防止被外部覆盖）
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

# 编译选项：按编译器区分（核心修改）
if (MSVC)
    # ========== MSVC（Visual Studio 编译器）配置 ==========
    add_compile_options(/W4 /utf-8)  # /W4 警告级别，/utf-8 编码
    # MSVC 调试符号：/Zi（生成程序数据库），关闭优化：/Od
    add_compile_options(/Zi /Od)
    # MSVC 链接时生成调试信息（必须加，否则调试器找不到符号）
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")
    # MSVC 的 Debug 编译标志（用 /Zi /Od，替代 -g -O0）
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od" CACHE STRING "Debug CXX flags" FORCE)
    set(CMAKE_C_FLAGS_DEBUG "/Zi /Od" CACHE STRING "Debug C flags" FORCE)
else()
    # ========== MinGW/GCC/Clang 配置 ==========
    add_compile_options(-Wall -Wextra -Wpedantic -g -O0)
    # MinGW 的 Debug 编译标志（保持 -g -O0）
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0" CACHE STRING "Debug CXX flags" FORCE)
    set(CMAKE_C_FLAGS_DEBUG "-g -O0" CACHE STRING "Debug C flags" FORCE)
endif()

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 查找并载入Cmake预设
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(glm REQUIRED)

# 添加可执行文件
add_executable(${TARGET} 
                src/core/game.cpp
                src/core/scene.cpp
                src/core/actor.cpp
                src/core/object.cpp
                src/core/object_world.cpp
                src/core/object_affiliate.cpp
                src/core/asset_store.cpp
                src/affiliate/sprite.cpp
                src/affiliate/sprite_anim.cpp
                src/affiliate/collider.cpp
                src/raw/stats.cpp
                src/raw/weapon.cpp
                src/world/effect.cpp
                src/world/spell.cpp
                src/screen/ui_mouse.cpp
                src/player.cpp
                src/enemy.cpp
                src/main.cpp
                src/scene_main.cpp
                src/spawner.cpp
                src/weapon_thunder.cpp
                )

# 链接库
target_link_libraries(${TARGET}
                        ${SDL3_LIBRARIES}
                        SDL3_image::SDL3_image
                        SDL3_mixer::SDL3_mixer
                        SDL3_ttf::SDL3_ttf
                        glm::glm
                        )


