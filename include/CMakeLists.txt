# vim: set ts=2 sw=2 tw=0 et :
######################################################################
# @company     : Universidade Federal de Viçosa - Florestal
# @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
# @file        : CMakeLists
# @created     : Sunday Aug 04, 2019 18:35:44 -03
# @license     : MIT
# @description : Electra - Field-Coupled Nanocomputing Data Structures
######################################################################

add_library(electra INTERFACE)
target_include_directories(electra INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(electra INTERFACE cxx_std_17)
