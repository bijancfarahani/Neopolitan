target_include_directories("${PROJECT_NAME}" PRIVATE
  ${CMAKE_SOURCE_DIR}/Source/Components
)




# Add sources from the current directory to the project target.
# We pass the target that needs the sources as the first argument,
# then a visibility parameter for the sources (which should normally be PRIVATE).
# Finally, we supply a list of source files that will be built into the target.

target_sources("${PROJECT_NAME}"
    PRIVATE
        PluginParameters.h
        PluginProcessor.h
        PluginProcessor.cpp
        FrequencySpectrumAnalyzer.h
        FrequencySpectrumAnalyzer.cpp)

# Add subdirectories with source files, if present
add_subdirectory(Components)