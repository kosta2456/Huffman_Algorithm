cmake_minimum_required(VERSION 3.13)
project(COP3530_S19_Huffman_Algorithm_master_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(COP3530_S19_Huffman_Algorithm_master_2
    texts/all_ascii.txt
    texts/balanced_alphabet.txt
    texts/iliad_1.txt
    texts/litany.txt
    texts/mississippi.txt
    texts/single_letter.txt
    texts/unbalanced_alphabet.txt
    catch.hpp
    catch_main.cpp
    huffman_tree.cpp
    huffman_tree.h
    tests.cpp)
