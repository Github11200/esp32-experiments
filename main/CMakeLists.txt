set( EXTRA_COMPONENTS, “components” )
set( EXTRA_COMPONENT_DIRS, “components/global_lib” ) 

idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_driver_gpio
                    REQUIRES driver
                    REQUIRES esp_driver_ledc)
