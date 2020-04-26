# Automatically generated by boost-vcpkg-helpers/generate-ports.ps1

include(vcpkg_common_functions)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/pool
    REF boost-1.72.0
    SHA512 87202bc193ee4d2de443b266f7bd786b6869691a164a8ec48949ce99a6101668153cc66d5cf407c4b55043d327fbc71b6c003ecdeb8965a976f8b4fb51610b0b
    HEAD_REF master
)

include(${CURRENT_INSTALLED_DIR}/share/boost-vcpkg-helpers/boost-modular-headers.cmake)
boost_modular_headers(SOURCE_PATH ${SOURCE_PATH})