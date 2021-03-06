
# Currently we are in the Powerball/Code folder: ${CMAKE_CURRENT_LIST_DIR}
# Get the platform specific folder ${pal_dir} for the current folder: ${CMAKE_CURRENT_LIST_DIR}/Platform/${PAL_PLATFORM_NAME}
# Note: ly_get_list_relative_pal_filename will take care of the details for us, as this may be a restricted platform
#       in which case it will see if that platform is present here or in the restricted folder.
#       i.e. It could here : Powerball/Code/Platform/<platorm_name>  or
#            <restricted_folder>/<platform_name>/Powerball/Code
ly_get_list_relative_pal_filename(pal_dir ${CMAKE_CURRENT_LIST_DIR}/Platform/${PAL_PLATFORM_NAME} ${o3de_project_restricted_path} ${o3de_project_path} ${o3de_project_name})

# Now that we have the platform abstraction layer (PAL) folder for this folder, thats where we will find the
# traits for this platform. Traits for a platform are defines for things like whether or not something in this project
# is supported by this platform.
include(${pal_dir}/PAL_${PAL_PLATFORM_NAME_LOWERCASE}.cmake)

# Now that we have loaded our project traits for this platform, see if this project is even supported on this platform.
# If its not supported we just return after including the unsupported.
if(NOT PAL_TRAIT_POWERBALL_SUPPORTED)
    return()
endif()

# We are on a supported platform, so add the Powerball target
# Note: We include the common files and the platform specific files which are set in powerball_files.cmake and
# in ${pal_dir}/powerball_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
ly_add_target(
    NAME Powerball.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        powerball_files.cmake
        ${pal_dir}/powerball_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
    INCLUDE_DIRECTORIES
        PUBLIC
            Include
    BUILD_DEPENDENCIES
        PRIVATE
            AZ::AzGameFramework
            Gem::Atom_AtomBridge.Static
)

ly_add_target(
    NAME Powerball ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        powerball_shared_files.cmake
        ${pal_dir}/powerball_shared_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
    INCLUDE_DIRECTORIES
        PUBLIC
            Include
    BUILD_DEPENDENCIES
        PRIVATE
            Gem::Powerball.Static
            AZ::AzCore
)

# if enabled, Powerball is used by all kinds of applications
ly_create_alias(NAME Powerball.Builders NAMESPACE Gem TARGETS Gem::Powerball)
ly_create_alias(NAME Powerball.Tools    NAMESPACE Gem TARGETS Gem::Powerball)
ly_create_alias(NAME Powerball.Clients  NAMESPACE Gem TARGETS Gem::Powerball)
ly_create_alias(NAME Powerball.Servers  NAMESPACE Gem TARGETS Gem::Powerball)

################################################################################
# Gem dependencies
################################################################################

# The GameLauncher uses "Clients" gem variants:
ly_enable_gems(
    PROJECT_NAME Powerball GEM_FILE enabled_gems.cmake
    TARGETS 
        Powerball.GameLauncher
    VARIANTS 
        Clients)

if(PAL_TRAIT_BUILD_HOST_TOOLS)

    # the builder type applications use the "Builders" variants of the enabled gems.
    ly_enable_gems(
        PROJECT_NAME Powerball GEM_FILE enabled_gems.cmake
        TARGETS
            AssetBuilder
            AssetProcessor
            AssetProcessorBatch
        VARIANTS 
            Builders)
    
    # the Editor applications use the "Tools" variants of the enabled gems.
    ly_enable_gems(
        PROJECT_NAME Powerball GEM_FILE enabled_gems.cmake
        TARGETS
            Editor
        VARIANTS 
            Tools)
endif()

if(PAL_TRAIT_BUILD_SERVER_SUPPORTED)
    # this property causes it to actually make a ServerLauncher.
    # if you don't want a Server application, you can remove this and the
    # following ly_enable_gems lines.
    set_property(GLOBAL APPEND PROPERTY LY_LAUNCHER_SERVER_PROJECTS Powerball)
    
    # The ServerLauncher uses the "Servers" variants of enabled gems:
    ly_enable_gems(
        PROJECT_NAME Powerball GEM_FILE enabled_gems.cmake
        TARGETS
            Powerball.ServerLauncher
        VARIANTS 
            Servers)
endif()
