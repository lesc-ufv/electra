# vim: set ts=2 sw=2 tw=0 et :
######################################################################
# @company     : Universidade Federal de Viçosa - Florestal
# @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
# @file        : CMakeLists
# @created     : Thursday Aug 01, 2019 22:20:14 -03
# @license     : MIT
# @description : Load Submodules at Configure Time
######################################################################

include(FetchContent)

# Override to show current download information
function(Fetch args)
  foreach(arg IN LISTS args)
    message("${C_GREEN} * ${C_RESET}Populating ${arg} Library")
    FetchContent_MakeAvailable(${arg})
  endforeach()
endfunction()


# Submodules
FetchContent_Declare(
  catch
  GIT_REPOSITORY git@github.com:catchorg/Catch2.git
  GIT_TAG v2.9.1
)

FetchContent_Declare(
  json
  GIT_REPOSITORY git@github.com:nlohmann/json.git
  GIT_TAG v3.7.0
)

FetchContent_Declare(
  alice
  GIT_REPOSITORY git@github.com:msoeken/alice.git
)

# Library options
set(JSON_BuildTests OFF)

# Populate Libraries
Fetch("catch;alice;json")
