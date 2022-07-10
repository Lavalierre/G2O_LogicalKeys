cmake_minimum_required(VERSION 3.17)

project(Union)

file(GLOB SRC
	"UnionAfx.h"
	"ZenGin/zGothicAPI.h"
	"Union/*.h"
	"ZenGin/Gothic_I_Classic/*.h"
	"ZenGin/Gothic_I_Classic/*.cpp"
	"ZenGin/Gothic_I_Classic/API/*.h"
	"ZenGin/Gothic_I_Addon/*.h"
	"ZenGin/Gothic_I_Addon/*.cpp"
	"ZenGin/Gothic_I_Addon/API/*.h"
	"ZenGin/Gothic_II_Classic/*.h"
	"ZenGin/Gothic_II_Classic/*.cpp"
	"ZenGin/Gothic_II_Classic/API/*.h"
	"ZenGin/Gothic_II_Addon/*.h"
	"ZenGin/Gothic_II_Addon/*.cpp"
	"ZenGin/Gothic_II_Addon/API/*.h"
	"ZenGin/Gothic_UserAPI/*.inl"
)

add_library(Union INTERFACE)
target_sources(Union INTERFACE ${SRC})

target_include_directories(Union
	INTERFACE
		"./"
		"ZenGin/Gothic_UserAPI/"
)

target_compile_definitions(Union INTERFACE __G2A)