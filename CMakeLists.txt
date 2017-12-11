cmake_minimum_required(VERSION 3.2)
project(Chess)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp gridElement.cpp gridElement.h Board.cpp Board.h ChessPiece.cpp ChessPiece.h constants.h chesspieces/Rook.cpp chesspieces/Rook.h chesspieces/Bishop.cpp chesspieces/Bishop.h chesspieces/Knight.cpp chesspieces/Knight.h chesspieces/Pawn.cpp chesspieces/Pawn.h chesspieces/Queen.cpp chesspieces/Queen.h chesspieces/King.cpp chesspieces/King.h Player.cpp Player.h HumanPlayer.cpp HumanPlayer.cpp HumanPlayer.h Move.cpp Move.h)
add_executable(Chess ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Chess ${SFML_LIBRARIES})
endif()