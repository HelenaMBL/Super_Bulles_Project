cmake_minimum_required(VERSION 4.1)
project(SuperBullesProject_AuriannC_HelenaM_RomainL_Ing1_Gr09 C)

set(CMAKE_C_STANDARD 11)

add_executable(SuperBullesProject_AuriannC_HelenaM_RomainL_Ing1_Gr09 main.c
        animation.c
        animation.h
        object.h
        object.c
        sauvegarde.c
        sauvegarde.h
        jeu.c
        jeu.h
        constantes.h
        reglages.c
        reglages.h
        bonus.c
        bonus.h
        partie.c
        partie.h
)

target_link_libraries(SuperBullesProject_AuriannC_HelenaM_RomainL_Ing1_Gr09 -lmingw32 -lalleg44)