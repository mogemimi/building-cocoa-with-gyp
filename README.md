cocoa-with-gyp
===================

## How to build

### Prerequisites

* Xcode 5
* OS X 10.7 or later
* Python (version 2.x)

### Prerequisite: Installing GYP

First, install GYP from https://chromium.googlesource.com/external/.  
Make sure git is installed.
From the root of your engine directory, run:  
```
$ git clone https://chromium.googlesource.com/external/gyp.git tools/gyp
```

or

```
$ svn --version
$ svn co http://gyp.googlecode.com/svn/trunk tools/gyp tools/gyp
```  

Second, run setup.py.  
To install globally with gyp:

```
$ cd tools/gyp
$ [sudo] python setup.py install
```

### Building under Xcode (Apple LLVM Clang++)

#### 1. Generate project

```
$ gyp build/test_app.gyp --depth=. -f xcode --generator-output=./build.xcodefiles/
```

#### 2. Build (Release/Debug)

```
$ xcodebuild -project build.xcodefiles/build/test_app.xcodeproj
```

To build in release mode, use -configuration option:

```
$ xcodebuild -project build/trivial.xcodeproj -configuration Release
```

#### 3. Running test

```
$ open build/build/Release/TestApp.app
```

## See also

* [gyp-getting-started](https://github.com/enginetrouble/gyp-getting-started)