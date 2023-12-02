add_executable(
    day_1
        src/main.cpp
)

target_compile_features(day_1 PUBLIC cxx_std_23)

target_link_libraries(
    day_1 PRIVATE
        ${PROJECT_NAME}
)