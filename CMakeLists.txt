cmake_minimum_required(VERSION 3.22)
project(wet2_mvne)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(wet2_mvne
        wet2util.h
        worldcup23a2.cpp
        worldcup23a2.h
        UnionFind.h
        Player.h
        Team.h
        UnionFind.cpp
        Player.cpp
        RankTree.h
        Team.cpp
        TeamAbility.h
        TeamAbility.cpp
        DynamicHash.h
        List.h
        DynamicHash.cpp
        main23a2.cpp)
