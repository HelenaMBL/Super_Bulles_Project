cmake_minimum_required(VERSION 4.1)
project(SuperBullesProject_AuriannC_HelenaM_RomainL_Ing1_Gr09 C)

set(CMAKE_C_STANDARD 11)

add_executable(SuperBullesProject_AuriannC_HelenaM_RomainL_Ing1_Gr09 main.c
        animation.c
        animation.h
        sauvegarde.c
        sauvegarde.h
        donnees.c
        donnees.h
        parametre.c
        parametre.h
)

target_link_libraries(SuperBullesProject_AuriannC_HelenaM_RomainL_Ing1_Gr09 -lmingw32 -lalleg44)
