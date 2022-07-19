project(csharp-project VERSION 0.1.0 LANGUAGES CSharp)

file(GLOB_RECURSE csharp-src *.cs)
add_library(csharp-script SHARED ${csharp-src})

