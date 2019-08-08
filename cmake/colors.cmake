# vim: set ts=2 sw=2 tw=0 et :
######################################################################
# @company     : Universidade Federal de Viçosa - Florestal
# @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
# @file        : colors
# @created     : Thursday Aug 01, 2019 22:22:46 -03
# @license     : MIT
# @description : CMake Color Variables
######################################################################

macro(define_colors)
  string(ASCII 27 Esc)
  set(C_RESET "${Esc}[m" CACHE INTERNAL "")
  set(C_RED     "${Esc}[1;31m" CACHE INTERNAL "")
  set(C_GREEN   "${Esc}[1;32m" CACHE INTERNAL "")
  set(C_YELLOW  "${Esc}[1;33m" CACHE INTERNAL "")
  set(C_BLUE    "${Esc}[1;34m" CACHE INTERNAL "")
  set(C_MAGENTA "${Esc}[1;35m" CACHE INTERNAL "")
  set(C_CYAN    "${Esc}[1;36m" CACHE INTERNAL "")
  set(C_WHITE   "${Esc}[1;37m" CACHE INTERNAL "")
endmacro()
