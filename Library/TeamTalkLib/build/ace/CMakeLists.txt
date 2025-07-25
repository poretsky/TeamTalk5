project(ACE)

include(ExternalProject)

##################################################
# ACE
##################################################

set (TOOLCHAIN_INSTALL_PREFIX_ACE ${TOOLCHAIN_INSTALL_PREFIX}/ace)

if (MSVC)

  file(TO_NATIVE_PATH ${TOOLCHAIN_INSTALL_PREFIX_ACE} TOOLCHAIN_INSTALL_PREFIX_ACE_NATIVE)

  if (TOOLCHAIN_BUILD_EXTERNALPROJECTS)

    configure_file(${CMAKE_CURRENT_LIST_DIR}/build_win.bat_sample ${CMAKE_CURRENT_BINARY_DIR}/build_win.bat @ONLY)

    if (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
      ExternalProject_Add(ACE-src
        GIT_REPOSITORY    https://github.com/DOCGroup/ACE_TAO.git
        GIT_TAG           ACE+TAO-8_0_4
        GIT_SUBMODULES_RECURSE TRUE
        GIT_SHALLOW       TRUE
        UPDATE_COMMAND    ""
        PATCH_COMMAND     git apply ${CMAKE_CURRENT_LIST_DIR}/0002-Enable-SNI-for-TLS.patch
        COMMAND           git apply ${CMAKE_CURRENT_LIST_DIR}/0003-Static-build-config-for-Windows.patch
        COMMAND           git submodule add --force https://github.com/DOCGroup/MPC ACE/MPC
        COMMAND           git submodule update --init ACE/MPC
        COMMAND           git -C ACE/MPC checkout ACE+TAO-8_0_4
        PREFIX            ${TOOLCHAIN_BUILD_PREFIX}/ace
        CONFIGURE_COMMAND ""
        BUILD_IN_SOURCE   TRUE
        BUILD_COMMAND     ${CMAKE_CURRENT_BINARY_DIR}/build_win.bat
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=x64 ace\\ace.sln -target:ACE /property:Configuration=Debug
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=x64 ace\\ace.sln -target:ACE /property:Configuration=Release
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=x64 ace\\ace.sln -target:SSL /property:Configuration=Debug
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=x64 ace\\ace.sln -target:SSL /property:Configuration=Release
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=x64 protocols\\protocols.sln -target:INet /property:Configuration=Debug
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=x64 protocols\\protocols.sln -target:INet /property:Configuration=Release
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=x64 protocols\\protocols.sln -target:INet_SSL /property:Configuration=Debug
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=x64 protocols\\protocols.sln -target:INet_SSL /property:Configuration=Release
        INSTALL_DIR       ${TOOLCHAIN_INSTALL_PREFIX_ACE}
        INSTALL_COMMAND   cd <SOURCE_DIR>
        COMMAND           ${CMAKE_CURRENT_LIST_DIR}\\install.bat <INSTALL_DIR>
        DEPENDS           openssl-src
        BUILD_BYPRODUCTS  <INSTALL_DIR>/lib/ACEsd.lib
                          <INSTALL_DIR>/lib/ACEs.lib
                          <INSTALL_DIR>/lib/ACE_SSLsd.lib
                          <INSTALL_DIR>/lib/ACE_SSLs.lib
                          <INSTALL_DIR>/lib/ACE_INetsd.lib
                          <INSTALL_DIR>/lib/ACE_INets.lib
                          <INSTALL_DIR>/lib/ACE_INet_SSLsd.lib
                          <INSTALL_DIR>/lib/ACE_INet_SSLs.lib
        )
      ExternalProject_Get_Property(ACE-src INSTALL_DIR)
    else()
      ExternalProject_Add(ACE-src
        GIT_REPOSITORY    https://github.com/DOCGroup/ACE_TAO.git
        GIT_TAG           ACE+TAO-8_0_4
        GIT_SUBMODULES_RECURSE TRUE
        GIT_SHALLOW       TRUE
        UPDATE_COMMAND    ""
        PATCH_COMMAND     git apply ${CMAKE_CURRENT_LIST_DIR}/0002-Enable-SNI-for-TLS.patch
        COMMAND           git apply ${CMAKE_CURRENT_LIST_DIR}/0003-Static-build-config-for-Windows.patch
        COMMAND           git submodule add --force https://github.com/DOCGroup/MPC ACE/MPC
        COMMAND           git submodule update --init ACE/MPC
        COMMAND           git -C ACE/MPC checkout ACE+TAO-8_0_4
        PREFIX            ${TOOLCHAIN_BUILD_PREFIX}/ace
        CONFIGURE_COMMAND ""
        BUILD_IN_SOURCE   TRUE
        BUILD_COMMAND     ${CMAKE_CURRENT_BINARY_DIR}/build_win.bat
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=win32 ace\\ace.sln -target:ACE /property:Configuration=Debug
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=win32 ace\\ace.sln -target:ACE /property:Configuration=Release
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=win32 ace\\ace.sln -target:SSL /property:Configuration=Debug
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=win32 ace\\ace.sln -target:SSL /property:Configuration=Release
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=win32 protocols\\protocols.sln -target:INet /property:Configuration=Debug
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=win32 protocols\\protocols.sln -target:INet /property:Configuration=Release
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=win32 protocols\\protocols.sln -target:INet_SSL /property:Configuration=Debug
        COMMAND           msbuild -maxCpuCount ${PLATFORMTOOLSET} /p:Platform=win32 protocols\\protocols.sln -target:INet_SSL /property:Configuration=Release
        INSTALL_DIR       ${TOOLCHAIN_INSTALL_PREFIX_ACE}
        INSTALL_COMMAND   cd <SOURCE_DIR>
        COMMAND           ${CMAKE_CURRENT_LIST_DIR}\\install.bat <INSTALL_DIR>
        DEPENDS           openssl-src
        BUILD_BYPRODUCTS  <INSTALL_DIR>/lib/ACEsd.lib
                          <INSTALL_DIR>/lib/ACEs.lib
                          <INSTALL_DIR>/lib/ACE_SSLsd.lib
                          <INSTALL_DIR>/lib/ACE_SSLs.lib
                          <INSTALL_DIR>/lib/ACE_INetsd.lib
                          <INSTALL_DIR>/lib/ACE_INets.lib
                          <INSTALL_DIR>/lib/ACE_INet_SSLsd.lib
                          <INSTALL_DIR>/lib/ACE_INet_SSLs.lib
        )
      ExternalProject_Get_Property(ACE-src INSTALL_DIR)
    endif()

    # Autogenerated paths must be created prior for
    # INTERFACE_INCLUDE_DIRECTORIES to work (target_include_directories ... INTERFACE ...)
    file(MAKE_DIRECTORY ${INSTALL_DIR}/include)
  else()
    set (INSTALL_DIR ${TOOLCHAIN_INSTALL_PREFIX_ACE})
  endif(TOOLCHAIN_BUILD_EXTERNALPROJECTS)

  add_library(ace STATIC IMPORTED GLOBAL)
  if (TOOLCHAIN_BUILD_EXTERNALPROJECTS)
    add_dependencies(ace ACE-src)
  endif()
  target_include_directories (ace INTERFACE ${INSTALL_DIR}/include)
  set_target_properties(ace PROPERTIES
    IMPORTED_LOCATION_DEBUG ${INSTALL_DIR}/lib/ACEsd.lib
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/ACEs.lib)

  add_library(ace_ssl STATIC IMPORTED GLOBAL)
  set_target_properties(ace_ssl PROPERTIES
    IMPORTED_LOCATION_DEBUG ${INSTALL_DIR}/lib/ACE_SSLsd.lib
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/ACE_SSLs.lib)
  target_link_libraries(ace_ssl INTERFACE ace openssl-crypto openssl-ssl)

  add_library(ace_inet STATIC IMPORTED GLOBAL)
  set_target_properties(ace_inet PROPERTIES
    IMPORTED_LOCATION_DEBUG ${INSTALL_DIR}/lib/ACE_INetsd.lib
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/ACE_INets.lib)
  target_link_libraries(ace_inet INTERFACE ace)

  add_library(ace_inet_ssl STATIC IMPORTED GLOBAL)
  set_target_properties(ace_inet_ssl PROPERTIES
    IMPORTED_LOCATION_DEBUG ${INSTALL_DIR}/lib/ACE_INet_SSLsd.lib
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/ACE_INet_SSLs.lib)
  target_link_libraries(ace_inet_ssl INTERFACE ace_inet ace_ssl)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

  if (TOOLCHAIN_BUILD_EXTERNALPROJECTS)
    ExternalProject_Add(MPC
      GIT_REPOSITORY    https://github.com/DOCGroup/MPC.git
      GIT_TAG           ACE+TAO-8_0_4
      GIT_SUBMODULES_RECURSE TRUE
      GIT_SHALLOW       TRUE
      UPDATE_COMMAND    ""
      PREFIX            ${TOOLCHAIN_BUILD_PREFIX}/MPC
      CONFIGURE_COMMAND ""
      BUILD_COMMAND     ""
      INSTALL_COMMAND   ""
      )
    ExternalProject_Get_Property(MPC SOURCE_DIR)
    set (MPC_DIR ${SOURCE_DIR})

    ExternalProject_Add(ACE-src
      GIT_REPOSITORY    https://github.com/DOCGroup/ACE_TAO.git
      GIT_TAG           ACE+TAO-8_0_4
      GIT_SUBMODULES_RECURSE TRUE
      GIT_SHALLOW       TRUE
      INSTALL_DIR       ${TOOLCHAIN_INSTALL_PREFIX_ACE}
      UPDATE_COMMAND    ""
      PATCH_COMMAND     git apply ${CMAKE_CURRENT_LIST_DIR}/0002-Enable-SNI-for-TLS.patch
      PREFIX            ${TOOLCHAIN_BUILD_PREFIX}/ace
      # Create 'platform_macros.GNU'
      CONFIGURE_COMMAND echo "shared_libs=0" > <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "static_libs_only=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "ssl=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "ipv6=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "c++17=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "include <SOURCE_DIR>/ACE/include/makeinclude/platform_macosx_mojave.GNU" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "CPPFLAGS+=-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -arch x86_64 -arch arm64" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "LDFLAGS+=-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -arch x86_64 -arch arm64" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "SSL_ROOT=${OPENSSL_DIR}" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "INSTALL_PREFIX=<INSTALL_DIR>" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      # Create 'config.h'
      COMMAND           echo "#define ACE_HAS_IPV6 1" > <SOURCE_DIR>/ACE/ace/config.h
      COMMAND           echo "#define ACE_HAS_CPP17" >> <SOURCE_DIR>/ACE/ace/config.h
      COMMAND           echo "#include \"ace/config-macosx.h\"" >> <SOURCE_DIR>/ACE/ace/config.h
      # Setup MPC
      COMMAND           ln -sf ${MPC_DIR} <SOURCE_DIR>/ACE/MPC
      # Generate build configuration for ACE
      COMMAND           export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/ace && <SOURCE_DIR>/ACE/bin/mwc.pl -type gnuace -recurse
      # Generate build configuration for protocols (INet)
      COMMAND           export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/protocols/ace/INet && <SOURCE_DIR>/ACE/bin/mwc.pl -type gnuace -recurse
      BUILD_IN_SOURCE   TRUE
      BUILD_COMMAND     export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/ace && make ${TOOLCHAIN_BUILD_MAKEJOBS}
      COMMAND           export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/protocols/ace/INet && make ${TOOLCHAIN_BUILD_MAKEJOBS}
      INSTALL_COMMAND   export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/ace && make ${TOOLCHAIN_BUILD_MAKEJOBS} install
      COMMAND           export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/protocols/ace/INet && make ${TOOLCHAIN_BUILD_MAKEJOBS} install
      DEPENDS           MPC openssl-src
      BUILD_BYPRODUCTS  <INSTALL_DIR>/lib/libACE.a
      <INSTALL_DIR>/lib/libACE_SSL.a
      <INSTALL_DIR>/lib/libACE_INet.a
      <INSTALL_DIR>/lib/libACE_INet_SSL.a
      )
    ExternalProject_Get_Property(ACE-src INSTALL_DIR)
    file(MAKE_DIRECTORY ${INSTALL_DIR}/include)
  else()
    set (INSTALL_DIR ${TOOLCHAIN_INSTALL_PREFIX_ACE})
  endif(TOOLCHAIN_BUILD_EXTERNALPROJECTS)

  add_library(ace STATIC IMPORTED GLOBAL)
  if (TOOLCHAIN_BUILD_EXTERNALPROJECTS)
    add_dependencies(ace ACE-src)
  endif()
  target_include_directories (ace INTERFACE ${INSTALL_DIR}/include)
  set_target_properties(ace PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE.a)

  add_library(ace_ssl STATIC IMPORTED GLOBAL)
  target_include_directories (ace_ssl INTERFACE ${INSTALL_DIR}/include)
  set_target_properties(ace_ssl PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE_SSL.a)
  target_link_libraries(ace_ssl INTERFACE ace openssl-ssl openssl-crypto)

  add_library(ace_inet STATIC IMPORTED GLOBAL)
  target_include_directories (ace_inet INTERFACE ${INSTALL_DIR}/include)
  set_target_properties(ace_inet PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE_INet.a)
  target_link_libraries(ace_inet INTERFACE ace)

  add_library(ace_inet_ssl STATIC IMPORTED GLOBAL)
  target_include_directories (ace_inet_ssl INTERFACE ${INSTALL_DIR}/include)
  set_target_properties(ace_inet_ssl PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE_INet_SSL.a)
  target_link_libraries(ace_inet_ssl INTERFACE ace_inet ace_ssl)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "iOS")

  if ("armv7" STREQUAL "${CMAKE_OSX_ARCHITECTURES}" OR "arm64" STREQUAL "${CMAKE_OSX_ARCHITECTURES}")
    set (ACE_CPPFLAGS -fembed-bitcode -miphoneos-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET})
    set (ACE_TARGET HARDWARE)
    set (ACE_EXPORT export ACE_ROOT=<SOURCE_DIR>/ACE)
  else()
    set (ACE_CPPFLAGS -mios-simulator-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET})
    set (ACE_TARGET SIMULATOR)
    set (ACE_EXPORT export ACE_ROOT=<SOURCE_DIR>/ACE)
  endif()

  if (TOOLCHAIN_BUILD_EXTERNALPROJECTS)
    ExternalProject_Add(MPC
      GIT_REPOSITORY    https://github.com/DOCGroup/MPC.git
      GIT_TAG           ACE+TAO-8_0_4
      GIT_SUBMODULES_RECURSE TRUE
      GIT_SHALLOW       TRUE
      UPDATE_COMMAND    ""
      PREFIX            ${TOOLCHAIN_BUILD_PREFIX}/MPC
      CONFIGURE_COMMAND ""
      BUILD_COMMAND     ""
      INSTALL_COMMAND   ""
      )
    ExternalProject_Get_Property(MPC SOURCE_DIR)
    set (MPC_DIR ${SOURCE_DIR})

    ExternalProject_Add(ACE-src
      GIT_REPOSITORY    https://github.com/DOCGroup/ACE_TAO.git
      GIT_TAG           ACE+TAO-8_0_4
      GIT_SUBMODULES_RECURSE TRUE
      GIT_SHALLOW       TRUE
      PATCH_COMMAND     git apply ${CMAKE_CURRENT_LIST_DIR}/0002-Enable-SNI-for-TLS.patch
      INSTALL_DIR       ${TOOLCHAIN_INSTALL_PREFIX_ACE}
      UPDATE_COMMAND    ""
      PREFIX            ${TOOLCHAIN_BUILD_PREFIX}/ace
      # Create 'platform_macros.GNU'
      CONFIGURE_COMMAND echo "shared_libs=0" > <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "static_libs_only=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "ssl=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "ipv6=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "c++17=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "IPHONE_TARGET=${ACE_TARGET}" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "include <SOURCE_DIR>/ACE/include/makeinclude/platform_macosx_iOS.GNU" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "IPHONE_HARDWARE_ARCHITECTURE=${CMAKE_OSX_ARCHITECTURES}" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "CPPFLAGS+=${ACE_CPPFLAGS}" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "LDFLAGS+=${ACE_CPPFLAGS}" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "SSL_ROOT=${OPENSSL_DIR}" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "INSTALL_PREFIX=<INSTALL_DIR>" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      # Create 'config.h'
      COMMAND           echo "#define ACE_HAS_IPV6 1" > <SOURCE_DIR>/ACE/ace/config.h
      COMMAND           echo "#define ACE_HAS_CPP17" >> <SOURCE_DIR>/ACE/ace/config.h
      COMMAND           echo "#include \"config-macosx-iOS.h\"" >> <SOURCE_DIR>/ACE/ace/config.h
      # Setup MPC
      COMMAND           ln -sf ${MPC_DIR} <SOURCE_DIR>/ACE/MPC
      # Generate build configuration for ACE
      COMMAND           ${ACE_EXPORT} && cd <SOURCE_DIR>/ACE/ace && <SOURCE_DIR>/ACE/bin/mwc.pl -type gnuace -recurse
      # Generate build configuration for protocols (INet)
      COMMAND           ${ACE_EXPORT} && cd <SOURCE_DIR>/ACE/protocols/ace/INet && <SOURCE_DIR>/ACE/bin/mwc.pl -type gnuace -recurse
      BUILD_IN_SOURCE   TRUE
      BUILD_COMMAND     ${ACE_EXPORT} && cd <SOURCE_DIR>/ACE/ace && make ${TOOLCHAIN_BUILD_MAKEJOBS}
      COMMAND           ${ACE_EXPORT} && cd <SOURCE_DIR>/ACE/protocols/ace/INet && make ${TOOLCHAIN_BUILD_MAKEJOBS}
      INSTALL_COMMAND   ${ACE_EXPORT} && cd <SOURCE_DIR>/ACE/ace && make ${TOOLCHAIN_BUILD_MAKEJOBS} install
      COMMAND           ${ACE_EXPORT} && cd <SOURCE_DIR>/ACE/protocols/ace/INet && make ${TOOLCHAIN_BUILD_MAKEJOBS} install
      DEPENDS           MPC openssl-src
      BUILD_BYPRODUCTS  <INSTALL_DIR>/lib/libACE.a
      <INSTALL_DIR>/lib/libACE_SSL.a
      <INSTALL_DIR>/lib/libACE_INet.a
      <INSTALL_DIR>/lib/libACE_INet_SSL.a
      )
    ExternalProject_Get_Property(ACE-src INSTALL_DIR)
    file(MAKE_DIRECTORY ${INSTALL_DIR}/include)
  else()
    set (INSTALL_DIR ${TOOLCHAIN_INSTALL_PREFIX_ACE})
  endif(TOOLCHAIN_BUILD_EXTERNALPROJECTS)

  add_library(ace STATIC IMPORTED GLOBAL)
  if (TOOLCHAIN_BUILD_EXTERNALPROJECTS)
    add_dependencies(ace ACE-src)
  endif()
  target_include_directories (ace INTERFACE ${INSTALL_DIR}/include)
  set_target_properties(ace PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE.a)

  add_library(ace_ssl STATIC IMPORTED GLOBAL)
  target_include_directories (ace_ssl INTERFACE ${INSTALL_DIR}/include)
  set_target_properties(ace_ssl PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE_SSL.a)
  target_link_libraries(ace_ssl INTERFACE ace openssl-ssl openssl-crypto)

  add_library(ace_inet STATIC IMPORTED GLOBAL)
  target_include_directories (ace_inet INTERFACE ${INSTALL_DIR}/include)
  set_target_properties(ace_inet PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE_INet.a)
  target_link_libraries(ace_inet INTERFACE ace)

  add_library(ace_inet_ssl STATIC IMPORTED GLOBAL)
  target_include_directories (ace_inet_ssl INTERFACE ${INSTALL_DIR}/include)
  set_target_properties(ace_inet_ssl PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE_INet_SSL.a)
  target_link_libraries(ace_inet_ssl INTERFACE ace_inet ace_ssl)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

  if (TOOLCHAIN_BUILD_EXTERNALPROJECTS)
    ExternalProject_Add(MPC
      GIT_REPOSITORY    https://github.com/DOCGroup/MPC.git
      GIT_TAG           ACE+TAO-8_0_4
      UPDATE_COMMAND    ""
      PREFIX            ${TOOLCHAIN_BUILD_PREFIX}/MPC
      CONFIGURE_COMMAND ""
      BUILD_COMMAND     ""
      INSTALL_COMMAND   ""
      )
    ExternalProject_Get_Property(MPC SOURCE_DIR)
    set (MPC_DIR ${SOURCE_DIR})

    ExternalProject_Add(ACE-src
      GIT_REPOSITORY    https://github.com/DOCGroup/ACE_TAO.git
      GIT_TAG           ACE+TAO-8_0_4
      INSTALL_DIR       ${TOOLCHAIN_INSTALL_PREFIX_ACE}
      UPDATE_COMMAND    ""
      PATCH_COMMAND     git apply ${CMAKE_CURRENT_LIST_DIR}/0002-Enable-SNI-for-TLS.patch
      PREFIX            ${TOOLCHAIN_BUILD_PREFIX}/ace
      # Create 'platform_macros.GNU'
      CONFIGURE_COMMAND echo "shared_libs=0" > <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "static_libs_only=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "ssl=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "ipv6=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "c++17=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "include <SOURCE_DIR>/ACE/include/makeinclude/platform_linux.GNU" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "CPPFLAGS+=-fPIC -DPIC" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "LDFLAGS+=-fPIC" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "INSTALL_PREFIX=<INSTALL_DIR>" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      # Create 'config.h'
      COMMAND           echo "#define ACE_AS_STATIC_LIBS 1" > <SOURCE_DIR>/ACE/ace/config.h
      COMMAND           echo "#define ACE_HAS_IPV6 1" >> <SOURCE_DIR>/ACE/ace/config.h
      COMMAND           echo "#define ACE_HAS_CPP17" >> <SOURCE_DIR>/ACE/ace/config.h
      COMMAND           echo "#include \"ace/config-linux.h\"" >> <SOURCE_DIR>/ACE/ace/config.h
      # Setup MPC
      COMMAND           ln -sf ${MPC_DIR} <SOURCE_DIR>/ACE/MPC
      # Generate build configuration for ACE
      COMMAND           export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/ace && <SOURCE_DIR>/ACE/bin/mwc.pl -type gnuace -recurse
      # Generate build configuration for protocols (INet)
      COMMAND           export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/protocols/ace/INet && <SOURCE_DIR>/ACE/bin/mwc.pl -type gnuace -recurse
      BUILD_IN_SOURCE   TRUE
      BUILD_COMMAND     export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/ace && make ${TOOLCHAIN_BUILD_MAKEJOBS}
      COMMAND           export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/protocols/ace/INet && make ${TOOLCHAIN_BUILD_MAKEJOBS}
      INSTALL_COMMAND   export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/ace && make ${TOOLCHAIN_BUILD_MAKEJOBS} install
      COMMAND           export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/protocols/ace/INet && make ${TOOLCHAIN_BUILD_MAKEJOBS} install
      DEPENDS           MPC
      BUILD_BYPRODUCTS  <INSTALL_DIR>/lib/libACE.a
      <INSTALL_DIR>/lib/libACE_SSL.a
      <INSTALL_DIR>/lib/libACE_INet.a
      <INSTALL_DIR>/lib/libACE_INet_SSL.a
      )
    ExternalProject_Get_Property(ACE-src INSTALL_DIR)
    file(MAKE_DIRECTORY ${INSTALL_DIR}/include)
  else()
    set (INSTALL_DIR ${TOOLCHAIN_INSTALL_PREFIX_ACE})
  endif(TOOLCHAIN_BUILD_EXTERNALPROJECTS)

  add_library(ace STATIC IMPORTED GLOBAL)
  if (TOOLCHAIN_BUILD_EXTERNALPROJECTS)
    add_dependencies(ace ACE-src)
  endif()
  target_include_directories (ace INTERFACE ${INSTALL_DIR}/include)
  set_target_properties(ace PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE.a)

  add_library(ace_ssl STATIC IMPORTED GLOBAL)
  set_target_properties(ace_ssl PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE_SSL.a)
  target_link_libraries(ace_ssl INTERFACE ace ssl crypto)

  add_library(ace_inet STATIC IMPORTED GLOBAL)
  set_target_properties(ace_inet PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE_INet.a)
  target_link_libraries(ace_inet INTERFACE ace)

  add_library(ace_inet_ssl STATIC IMPORTED GLOBAL)
  set_target_properties(ace_inet_ssl PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE_INet_SSL.a)
  target_link_libraries(ace_inet_ssl INTERFACE ace_inet ace_ssl)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Android")

  if (TOOLCHAIN_BUILD_EXTERNALPROJECTS)
    ExternalProject_Add(MPC
      GIT_REPOSITORY    https://github.com/DOCGroup/MPC.git
      GIT_TAG           ACE+TAO-8_0_4
      UPDATE_COMMAND    ""
      PREFIX            ${TOOLCHAIN_BUILD_PREFIX}/MPC
      CONFIGURE_COMMAND ""
      BUILD_COMMAND     ""
      INSTALL_COMMAND   ""
      )
    ExternalProject_Get_Property(MPC SOURCE_DIR)
    set (MPC_DIR ${SOURCE_DIR})

    set (ACE_EXPORT export PATH=${CMAKE_ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin:$ENV{PATH})

    if ("armeabi-v7a" STREQUAL "${ANDROID_ABI}")
      set (ACE_CC --target=armv7a-linux-androideabi${ANDROID_PLATFORM_LEVEL})
    elseif ("arm64-v8a" STREQUAL "${ANDROID_ABI}")
      set (ACE_CC --target=aarch64-linux-android${ANDROID_PLATFORM_LEVEL})
    elseif ("x86" STREQUAL "${ANDROID_ABI}")
      set (ACE_CC --target=i686-linux-android${ANDROID_PLATFORM_LEVEL})
    elseif ("x86_64" STREQUAL "${ANDROID_ABI}")
      set (ACE_CC --target=x86_64-linux-android${ANDROID_PLATFORM_LEVEL})
    else()
      message(WARNING "Unknown Android architecture")
    endif()

    ExternalProject_Add(ACE-src
      GIT_REPOSITORY    https://github.com/DOCGroup/ACE_TAO.git
      GIT_TAG           ACE+TAO-8_0_4
      INSTALL_DIR       ${TOOLCHAIN_INSTALL_PREFIX_ACE}
      UPDATE_COMMAND    ""
      PATCH_COMMAND     git apply ${CMAKE_CURRENT_LIST_DIR}/0001-Make-CROSS_COMPILE-configurable-for-Android.patch
      COMMAND           git apply ${CMAKE_CURRENT_LIST_DIR}/0002-Enable-SNI-for-TLS.patch
      PREFIX            ${TOOLCHAIN_BUILD_PREFIX}/ace
      # Create 'platform_macros.GNU'
      CONFIGURE_COMMAND echo "shared_libs=0" > <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "static_libs_only=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "ssl=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "ipv6=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "c++17=1" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "CPPFLAGS+=${ACE_CC} -fPIC -DPIC -D__ANDROID_API__=${ANDROID_PLATFORM_LEVEL}" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "LDFLAGS+=-fPIC" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "INSTALL_PREFIX=<INSTALL_DIR>" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "SSL_ROOT=${OPENSSL_DIR}" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "ANDROID_ABI=${ANDROID_ABI}" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "CROSS_COMPILE=\"\"" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      COMMAND           echo "include <SOURCE_DIR>/ACE/include/makeinclude/platform_android.GNU" >> <SOURCE_DIR>/ACE/include/makeinclude/platform_macros.GNU
      # Create 'config.h'
      COMMAND           echo "#define ACE_AS_STATIC_LIBS 1" > <SOURCE_DIR>/ACE/ace/config.h
      COMMAND           echo "#define ACE_HAS_IPV6 1" >> <SOURCE_DIR>/ACE/ace/config.h
      COMMAND           echo "#define ACE_HAS_CPP17" >> <SOURCE_DIR>/ACE/ace/config.h
      COMMAND           echo "#define ACE_LACKS_GETIPNODEBYADDR 1 /* missing in android netdb.h */" >> <SOURCE_DIR>/ACE/ace/config.h
      COMMAND           echo "#define ACE_LACKS_GETIPNODEBYNAME_IPV6 1" >> <SOURCE_DIR>/ACE/ace/config.h
      COMMAND           echo "#include \"ace/config-android.h\"" >> <SOURCE_DIR>/ACE/ace/config.h
      # Setup MPC
      COMMAND           ln -sf ${MPC_DIR} <SOURCE_DIR>/ACE/MPC
      # Generate build configuration for ACE
      COMMAND           ${ACE_EXPORT} && export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/ace && <SOURCE_DIR>/ACE/bin/mwc.pl -type gnuace -recurse
      # Generate build configuration for protocols (INet)
      COMMAND           ${ACE_EXPORT} && export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/protocols/ace/INet && <SOURCE_DIR>/ACE/bin/mwc.pl -type gnuace -recurse
      BUILD_IN_SOURCE   TRUE
      BUILD_COMMAND     ${ACE_EXPORT} && export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/ace && make ${TOOLCHAIN_BUILD_MAKEJOBS}
      COMMAND           ${ACE_EXPORT} && export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/protocols/ace/INet && make ${TOOLCHAIN_BUILD_MAKEJOBS}
      INSTALL_COMMAND   ${ACE_EXPORT} && export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/ace && make ${TOOLCHAIN_BUILD_MAKEJOBS} install
      COMMAND           ${ACE_EXPORT} && export ACE_ROOT=<SOURCE_DIR>/ACE && cd <SOURCE_DIR>/ACE/protocols/ace/INet && make ${TOOLCHAIN_BUILD_MAKEJOBS} install
      DEPENDS           MPC openssl-src
      BUILD_BYPRODUCTS  <INSTALL_DIR>/lib/libACE.a
      <INSTALL_DIR>/lib/libACE_SSL.a
      <INSTALL_DIR>/lib/libACE_INet.a
      <INSTALL_DIR>/lib/libACE_INet_SSL.a
      )
    ExternalProject_Get_Property(ACE-src INSTALL_DIR)
    file(MAKE_DIRECTORY ${INSTALL_DIR}/include)
  else()
    set (INSTALL_DIR ${TOOLCHAIN_INSTALL_PREFIX_ACE})
  endif(TOOLCHAIN_BUILD_EXTERNALPROJECTS)

  add_library(ace STATIC IMPORTED GLOBAL)
  if (TOOLCHAIN_BUILD_EXTERNALPROJECTS)
    add_dependencies(ace ACE-src)
  endif()
  target_include_directories (ace INTERFACE ${INSTALL_DIR}/include)
  set_target_properties(ace PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE.a)

  add_library(ace_ssl STATIC IMPORTED GLOBAL)
  set_target_properties(ace_ssl PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE_SSL.a)
  target_link_libraries(ace_ssl INTERFACE ace openssl-ssl openssl-crypto)

  add_library(ace_inet STATIC IMPORTED GLOBAL)
  set_target_properties(ace_inet PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE_INet.a)
  target_link_libraries(ace_inet INTERFACE ace)

  add_library(ace_inet_ssl STATIC IMPORTED GLOBAL)
  set_target_properties(ace_inet_ssl PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libACE_INet_SSL.a)
  target_link_libraries(ace_inet_ssl INTERFACE ace_inet ace_ssl)

endif()
