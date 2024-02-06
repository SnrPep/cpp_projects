cmake_minimum_required(VERSION 3.13)
project(vtk)

set(CMAKE_CXX_STANDARD 14)

find_package(VTK COMPONENTS
        CommonColor
        CommonCore
        CommonDataModel
        FiltersCore
        FiltersGeneral
        FiltersGeometry
        FiltersModeling
        FiltersSources
        IOImage
        InteractionStyle
        RenderingContextOpenGL2
        RenderingCore
        RenderingFreeType
        RenderingGL2PSOpenGL2
        RenderingOpenGL2
)

add_executable(VTK main.cpp)
target_link_libraries(VTK PRIVATE ${VTK_LIBRARIES})

vtk_module_autoinit(
        TARGETS VTK
        MODULES ${VTK_LIBRARIES}
)
