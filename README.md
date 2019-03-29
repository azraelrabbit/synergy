Synergy
=======
Share one buggy mouse and one buggy keyboard between multiple computers.
---

**Visit https://github.com/yupi2/synergy/releases/latest for the latest 32/64-bit Windows installers and 64-bit Linux .deb files**<br/>
You can find more at https://github.com/yupi2/synergy/releases <br/>
**Last Windows XP build since LibreSSL doesn't support Windows XP anymore https://github.com/yupi2/synergy/releases/tag/4.2.0_master_0d1aad0dacc071f9981f778e2ee8a10f36b57ec5 .**

[Travis](https://travis-ci.org/yupi2/synergy) (Linux .debs) <br/>
[Appveyor](https://ci.appveyor.com/project/yupi2/synergy) (Windows)

This is a fork whose goal is to be less buggy, build easier, and to remove the activation requirement for features.

The `master` branch is what you want to use. `activey` is used for sharing code between my computers and is likely to have compilation errors or buggy code.

**IMPORTANT: I DON'T BUILD OR TEST OSX/MACOS.** I don't have an environment to use so builds are likely to fail.

Random thing: `-D_USE_C_DATE=OFF` will help with reproducible builds.


Changes in this fork
--------------------
There's a few things not listed here. Go through the commits.
+ Removed activation requirement for features.
+ Made it easier to build.
+ Moved configuration files location for no good reason.
  + Windows uses `%localappdata%\Synergy\`
  + macOS uses `~/Library/Preferences/Synergy/`
  + Linux/everything-else uses `~/.config/Synergy/`
+ Removed Python requirement by switching from the `hm` help script to purely CMake.
+ Replaced OpenSSL with LibreSSL because it can be built with CMake and statically linked to avoid .dlls
  + Source tarball is now downloaded from LibreSSL website (since 2017-04-11).
  + OpenSSL could probably be used on Linux/everything-else instead but that can be done again in the future.
  + Generating certificates now uses 4096 bits for RSA instead of 1024.
+ Printscreen doesn't send Alt+Printscreen to Windows clients anymore.
+ Some new icons for OSX? (maybe)
+ EXTREMELY EXTREMELY BUGGY AND BAD MEMORY LEAK FIX FOR SERVERS (LINUX ONLY?).
  + Toggle the checkbox in `Configured Server->Advanced server settings` named `VERY experimental memory leak fix for yupi2`.
  + Also for a server config file in `section: options` you can add a `
  expLeakFix = true` line.
+ Removed in-tree googletest source-code and replaced it with a git submodule.
+ Working Mouse 4 (browser backwards) and Mouse 5 (browser forwards).
+ Working Horizontal scrolling.
+ New screen option to pass NumLock, ScrollLock, and CapsLock to the target screen.
  + As opposed to not sending the keycodes and only treating them as modifiers.
  + `Configure Server -> Double-click a screen -> Pass LOCK keys`
+ Merged some pull-requests that are fine from the symless/synergy repo.

Licenses and stuff
------------------
Synergy and it's components are licensed under the terms of the GNU General Public License Version 2 (GPLv2) with an additional exemption so compiling, linking, and/or using OpenSSL is allowed.

uSynergy (micro Synergy) is a seperate project that falls under the zlib License. It is unused but is kept in the repo for "historical value".

A tar-gz archive of [LibreSSL](https://www.libressl.org/), an OpenSSL fork, is downloaded through CMake which includes software developed by Eric Young (eay@cryptsoft.com) and software developed by the OpenSSL Project for use in the OpenSSL Toolkit (http://www.openssl.org) along with work contributed from many other sources including the OpenBSD project and associates. More license information can be obtained by looking through the files in the tar-gz archive.

The archive is retrieved from https://ftp.openbsd.org/pub/OpenBSD/LibreSSL/


TODOs and wishlist
------------------
+ Detect local input even when not connected
  + Will need to look into this eventually.
  + https://github.com/symless/synergy-core/issues/6161
+ Cleaner core without obsolete legacy components
  + **NOT REMOVING STUFF** just seeing if merging any of the CMake stuff for exmaple would be good.
  + https://github.com/symless/synergy-core/issues/6151
+ Send modifier keys differently depending on active window
  + Seems to be a mostly Parallels oriented PR but it is OSX stuff which I don't have available to test.
  + https://github.com/symless/synergy-core/pull/6064
+ Map JIS Keys to make OS X synergy server comfortable.
  + More OSX stuff + would need testing for non-JIS keyboard layouts...
  + https://github.com/symless/synergy-core/pull/5730
+ Add an option to ignore VirtualBox network adapters
  + Should just add a drop-down box where you can pick your network adapter...
  + https://github.com/symless/synergy-core/pull/5245
+ Specfile for building in fedora/centos
  + Just need to look into this and then Fedora builds can likely be setup (.rpm files)
  + https://github.com/symless/synergy-core/pull/5073
+ Dependencies not found with the 'check_' macros
  + This is a big maybe. Not sure if this would be a better thing to use.
  + https://github.com/symless/synergy-core/pull/4542
+ Remove synwinhk DLL
  + The DLL isn't used in modern Windows and it just makes uninstalling/updating a pain. Also it loads the DLL into most processes which breaks Fornite with the latest update D:
  + https://github.com/symless/synergy-core/issues/6226
  + Add synwinhk support to synergyc - https://github.com/symless/synergy-core/commit/c3530a0ff35cd77c3f7221deeeebe83f90b5728a
  + Remove synwinhk DLL - https://github.com/symless/synergy-core/commit/703097c19b58f0bbd14f998107279dfda4ff1600
  + ^ That commit has some parents too which might be needed.
+ Compare source pid from event to detect local input on Mac
  + Haven't looked into this
  + https://github.com/symless/synergy-core/commit/9551329392ee597b2781626d38b4f249c71b96c1
+ Initialize XWindowsScreen to offscreen for secondary displays
  + I don't think this is a problem at the moment on this fork. It is based on a commit that touched some stuff so I don't know how different they are...
  + https://github.com/symless/synergy-core/pull/6249
  + Partial local input detection for Linux - https://github.com/symless/synergy-core/commit/41721e9eac5532ce7c048a3b63851b3736c0244b
+ Reallocate socket buffer when size is not big enough
  + I don't know if this is a problem for anyone.
  + https://github.com/symless/synergy-core/pull/6174

Building
--------
**You should really really really not downloading anything to build just yet. This is just a little run-down on requirements to build with more detailed instructions lower down.**

+ Operating system:
  + Windows OS with support for XP or newer APIs
  + Apple macOS (TODO)
  + Linux (and maybe some POSIX systems)
+ [CMake 3.0 or newer](https://cmake.org/)
+ A C++11 environment (maybe?)
+ Qt 5.6, 5.7, 5.8 or 5.9 (earlier versions might work but I haven't tested)
+ WiX Toolset if you plan to make installers for Windows Platforms.
+ Any recent version of Git in your command path

**Here's how I build on Linux:**<br/>
```
./configure
make -C build -j$(nproc)
```
or
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
cmake --build ./ -- -j$(nproc)
```
And optionally for packaging a .deb afterward: `./package_deb.sh`

**And on 64-bit Windows 7 with Visual Studio 2015:**<br/>
```
mkdir build
cd build
set PATH=%PATH%;C:\Qt\5.9.1\msvc2015_64\bin
cmake -DCMAKE_BUILD_TYPE=Release -G"Visual Studio 14 2015 Win64" ../
cmake --build ./ --config Release
msbuild synwix.sln
```

If you want to build the tests for Synergy (`-D_TESTS=ON`) you'll the [googletest (and googlemock)](https://github.com/google/googletest) framework. It is included as a submodule which will be downloaded if you run:
```
git clone --recursive https://github.com/yupi2/synergy.git
```
If you have a Synergy repository already but didn't run the command above initially then you can download the submodule by running this:
```
git submodule update --init
```
If you have a preinstalled version of *googletest* from a package-manager or something and want to use it then check out `src/test/CMakeLists.txt` and maybe change some directories.

**Some cmake things:**
+ `-DCMAKE_BUILD_TYPE=[Release|Debug|etc]` 
+ `-DDEB_ARCH=[amd64|i386|etc]` - used for setting the arch in `synergy/dist/deb/control.in`
+ `-D_TESTS=[ON|OFF]` - turn tests on or off
+ `-D_USE_C_DATE=[ON|OFF]` - useful for reproducible builds - embeds build time from compiler
+ `-D_LIBRESSL_PATH=path` - use your own LibreSSL release
+ `-D_GIT_REVISION=` - specify revision
+ `-D_GIT_BRANCH=` - specify branch

(Windows) Compiling with Microsoft's Visual C++ environment (and creating an installer!)
-----------------------------------------------------------
Requirements:
+ Visual C++ Build Tools (2013, 2015, or 2017)
  + Visual Studio 2013, 2015, and 2017 will provide this if installed with `C++ Tools` selected
  + Also you can optionally install the 2015 build tools with the VS2017 installer too.
  + There's standalone download for 2015 and 2017 build tools [here](http://landinghub.visualstudio.com/visual-cpp-build-tools)
+ [CMake](https://cmake.org/download/)
+ [Qt 5.6, 5.7, 5.8 or 5.9](https://www.qt.io/download-open-source/)
  + [Here's what I have selected for x32/x64 VS2015 and x64 VS2017](https://imgur.com/ImOghWy)
    + Some notes: 5.6 is a LTS (long term support) version ending in 2019 and 5.9 too ending in 2020.
    + Also you'll need to use 5.6 if you want to build targeting Windows XP.
+ [WiX Toolset build tools](http://wixtoolset.org/releases/) and maybe also the `WiX Toolset Visual Studio 201x Extension`

Notes:
+ If you're NOT going to use an installer and just want to run Synergy from the build directory you'll need to create a service to run `synergyd.exe` nicely. Here's something to put into an elevated (admin) command prompt to create a service (you'll need to correct the path to your binary location:
  + `sc create Synergy type= own start= auto error= ignore obj= LocalSystem DisplayName= "Synergy Daemon" binPath= "C:\code\synergy\build\bin\x64\Release\synergyd.exe"`
      + It might not start after creation so you'll need to do `sc start Synergy`. It will auto-start on boot though.
    + Also when `synergyd.exe` crashes you can restart the Service with `sc stop Synergy` then `sc start Synergy`

 1. Open a Visual Studio Native/Cross Tools Command Prompt. You should be able to find these in your start menu under your Visual Studio version folder.
     + Alternatively you can use `vcvarsall` (google it) in a command prompt
     + These tools might be prefixed with the VS version like `VS2015`
     + `x86 Native Tools Command Prompt` -- x86_32 builds on an x86_32 machine
       + Will work on x86_64 systems too.
     + `x86 x64 Cross Tools Command Prompt` -- x86_64 builds on an x86_32 machine
       + Will work on x86_64 systems too.
 2. `cd C:\`
 3. `mkdir code`
 4. `cd code`
 5. `git clone https://github.com/yupi2/synergy.git`
 6. `cd synergy`
 7. `mkdir build`
 8. `cd build`
 9. `set PATH=%PATH%;C:\Qt\5.9.1\msvc2015_64\bin`
     + You'll need to change this if you want to use other versions of Qt or VS.
10. `cmake -DCMAKE_BUILD_TYPE=Release -G"Visual Studio 14 2015 Win64" ../`
     + [Generators (-G)](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators) don't include the `Win64` if targetting x86_32 builds.
     + Examples:
       + `Visual Studio 14 2015` -- x86_32 VS2015
       + `Visual Studio 15 2017 Win64` -- x86_64 VS2017
       + `Visual Studio 12 2013` -- x86_32 VS2013
     + Also for targetting Windows XP you might need to provide a toolset argument such as `-T v140_xp` (the 2015 build tools XP target) or `-T v120_xp` (the 2013 one).
       + so `cmake -DCMAKE_BUILD_TYPE=Release -G"Visual Studio 14 2015" -T v140_xp ../`
11. `cmake --build ./ --config Release`
12. And if you want to build an installer: `msbuild synwix.sln`
     + You can find the installer at `build\bin\synergy_installer_*.msi` where `*` is a version, git branch, git revision, and architecture.
+ **Note:** You can also replace all instances above of `Release` with `Debug`, `RelWithDebInfo`, or `MinSizeRel`.


(Linux / POSIX) Compiling
-------------------------
Requirements:
+ Compiler!
+ CMake!
+ Qt5!
  + ~~Also you'll need the Qt5 Linguist Tools which might be `qttools5-dev-tools` or `qt5-tools`.~~ This isn't true anymore.
+ X11!
  + X11/Xorg dev packages (libxtst, libxext, and more I think).
+ Debian and Ubuntu packages:
  + (`apt install`) `git build-essential cmake xorg-dev qt5-default`
+ Fedora packages (INCOMPLETE):
  + `git cmake libXtst-devel libXext-devel qt5-devel `
1. Open terminal.
2. `cd ~/code`
3. `git clone https://github.com/yupi2/synergy.git`
4. `cd synergy`
5. `./configure`
    + You can pass regular cmake arguments to the `./configure` thing. Read the `configure` file for more information on what it does.
    + You can do `MY_SYN_BUILD_DIR=/folder/to/thing` for build dir and `MY_SYN_PWD=/folder/to/syn` for root synergy dir.
5. `make -C build -j$(nproc)`
    + `$(nproc)` uses the number of processors available. You can use a static number of cores with `-jN` where `N` is your number or remove it entirely
7. `ls bin`
8. If packaging a .deb then: `./package_deb.sh`
    + You can do `MY_SYN_BUILD_DIR=/folder/to/thing` for the build dir.
	+ You can install the .deb with `sudo dpkg -i build/deb/synergy.deb`

**or**

1. Open terminal.
2. `cd ~/code`
3. `git clone https://github.com/yupi2/synergy.git`
4. `cd synergy ; mkdir build ; cd build`
5. `cmake -DCMAKE_BUILD_TYPE=Release ../`
    + You can replace `Release` with `Debug` here
6. `cmake --build ./ -- -j$(nproc)`
    + `$(nproc)` uses the number of processors available. You can use a static number of cores with `-jN` where `N` is your number or remove it entirely `cmake -build ./`
7. `ls bin`
8. If packaging a .deb then: `./package_deb.sh`
    + You can do `MY_SYN_BUILD_DIR=/folder/to/thing` for the build dir.
	+ You can install the .deb with `sudo dpkg -i build/deb/synergy.deb`

(Apple macOS) Compiling
-----------------------
TODO
