# NuGet consumer

A Visual Studio C++ project that consumes `Aspose.Slides.Cpp.FOSS` from NuGet and
writes a `.pptx` with it.

It is the acceptance test for the NuGet packaging, and it is deliberately built
the way a user's project is: it names the package and nothing else. No include
directory, no library, no path. Those come from
`build/native/Aspose.Slides.Cpp.FOSS.targets`, which NuGet imports out of the
package by itself.

There is no `<Import>` of that targets file in the project. Adding one would prove
the targets file works while hiding whether NuGet can find it — and where it sits
inside the package is exactly the thing that goes wrong. The sibling
`Aspose.Cells.Cpp.FOSS` package ships its targets one directory too deep, so it is
never imported; installing that package gives you no include path and no library,
and nothing about it looks broken until your first `#include` fails.

## Running it against a package you just built

```powershell
python packaging\nuget\pack.py --work build\nuget-pack

$feed = "$pwd\build\nuget-pack\package"

# Restore first, as its own invocation. See below for why.
msbuild examples\nuget-consumer\nuget-consumer.vcxproj -t:restore `
    -p:Configuration=Release -p:Platform=x64 `
    -p:AsposeSlidesFossVersion=26.9.0 -p:RestoreSources=$feed `
    -p:RestorePackagesPath="$pwd\build\consumer-packages"

msbuild examples\nuget-consumer\nuget-consumer.vcxproj -t:build `
    -p:Configuration=Release -p:Platform=x64 `
    -p:AsposeSlidesFossVersion=26.9.0 `
    -p:RestorePackagesPath="$pwd\build\consumer-packages" `
    -p:OutDir="$pwd\build\consumer-x64-Release\"

build\consumer-x64-Release\nuget-consumer.exe out.pptx
python tests\conformance\validate.py out.pptx --require-python-pptx
```

**Restore and build must be two invocations.** `-t:restore,build` evaluates the project once, before
restore has written the generated import that pulls in the package's `.targets` — so the build half
of that same invocation never sees the include path the package provides, and fails on the first
`#include`. Worse, it then appears to work on every subsequent run, because the earlier restore has
left the generated file behind. On a cold package cache the first configuration fails and the ones
after it pass, which reads as a flaky test rather than a wrong command.

The last line matters as much as the build: a consumer that links and runs can
still write a package PowerPoint refuses, and the validator reads the file with an
implementation that shares none of this library's assumptions.

Four platform and configuration pairs are shipped — x64 and Win32, Debug and
Release — and each is a different set of archives inside the package, so a check
that runs only one of them proves one of four.
