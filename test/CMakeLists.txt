# vim: set ts=2 sw=2 tw=0 et :
######################################################################
# @company     : Universidade Federal de Viçosa - Florestal
# @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
# @file        : CMakeLists
# @created     : Tuesday Aug 06, 2019 10:52:02 -03
# @license     : MIT
# @description : Electra - Field-Coupled Nanocomputing Data Structures
######################################################################

add_executable(test test.cpp)
target_link_libraries(test PRIVATE electra Catch2)
