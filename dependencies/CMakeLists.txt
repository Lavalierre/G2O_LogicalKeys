add_subdirectory(squirrel)
add_subdirectory(sqrat)
add_subdirectory(Union)
add_subdirectory(Hacks)

target_link_libraries(LogicalKeys PUBLIC Squirrel)
target_link_libraries(LogicalKeys PUBLIC SqRat)
target_link_libraries(LogicalKeys PUBLIC Union)
target_link_libraries(LogicalKeys PUBLIC Hacks)