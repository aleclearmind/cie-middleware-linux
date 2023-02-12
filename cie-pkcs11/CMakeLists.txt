cmake_minimum_required(VERSION 3.22)

project(cie-pkcs11)

include_directories(/usr/include/PCSC/)
set(CMAKE_CXX_FLAGS "-Wno-write-strings -Wno-conversion-null -Wno-pointer-arith -Wno-return-type -Wno-int-to-pointer-cast")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
add_library(cie-pkcs11 SHARED
./CSP/FirmaConCIE.cpp
./CSP/VerificaConCIE.cpp
./CSP/ATR.cpp
./CSP/AbilitaCIE.cpp
./CSP/ExtAuthKey.cpp
./CSP/IAS.cpp
./CSP/PINManager.cpp
./Crypto/AES.cpp
./Crypto/ASNParser.cpp
./Crypto/Base64.cpp
./Crypto/DES3.cpp
./Crypto/MAC.cpp
./Crypto/MD5.cpp
./Crypto/RSA.cpp
./Crypto/SHA1.cpp
./Crypto/SHA256.cpp
./Crypto/SHA512.cpp
./LOGGER/Logger.cpp
./PCSC/APDU.cpp
./PCSC/CardLocker.cpp
./PCSC/PCSC.cpp
./PCSC/Token.cpp
./PKCS11/CIEP11Template.cpp
./PKCS11/CardContext.cpp
./PKCS11/CardTemplate.cpp
./PKCS11/Mechanism.cpp
./PKCS11/P11Object.cpp
./PKCS11/PKCS11Functions.cpp
./PKCS11/Slot.cpp
./PKCS11/initP11.cpp
./PKCS11/session.cpp
./Sign/CIESign.cpp
./Sign/CIEVerify.cpp
./Util/UtilException.cpp
./Util/Array.cpp
./Util/CacheLib.cpp
./Util/CryptoppUtils.cpp
./Util/IniSettings.cpp
./Util/ModuleInfo.cpp
./Util/SyncroEvent.cpp
./Util/SyncroMutex.cpp
./Util/TLV.cpp
./Util/UUCByteArray.cpp
./Util/UUCProperties.cpp
./Util/UUCStringTable.cpp
./Util/UUCTextFileReader.cpp
./Util/funccallinfo.cpp
./Util/log.cpp
./Util/util.cpp
)
target_link_libraries(cie-pkcs11 cryptopp crypto)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PCSCLITE REQUIRED libpcsclite)
target_link_libraries(cie-pkcs11 ${PCSCLITE_LIBRARIES})
target_include_directories(cie-pkcs11 PUBLIC ${PCSCLITE_INCLUDE_DIRS})
target_compile_options(cie-pkcs11 PUBLIC ${PCSCLITESDL2_CFLAGS_OTHER})


add_executable(enable-cie enable-cie.cpp)
target_link_libraries(enable-cie cie-pkcs11)
