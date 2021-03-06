{
  'includes': ['common.gypi'],
  'make_global_settings': [
    ['CXX','/usr/bin/clang++'],
    ['LINK','/usr/bin/clang++'],
  ],
  'target_defaults': {
    'include_dirs': [
      '../include',
    ],
    'xcode_settings': {
      'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0',
      'CLANG_CXX_LANGUAGE_STANDARD': 'c++0x',
      'MACOSX_DEPLOYMENT_TARGET': '10.8', # OS X Deployment Target: 10.8
      'CLANG_CXX_LIBRARY': 'libc++', # libc++ requires OS X 10.7 or later
    },
  },
  'targets': [
    {
      'target_name': 'cocoa_with_gyp',
      'product_name': 'CocoaWithGYP',
      'type': 'shared_library',
      'mac_bundle': 1,
      'include_dirs': [
        '../include',
      ],
      'sources': [
        '../include/CocoaWithGYP/CocoaOpenGLView.h',
        '../src/CocoaOpenGLView.mm',
        '../src/QuadRenderer.cpp',
        '../src/QuadRenderer.h',
      ],
      'link_settings': {
        'libraries': [
          '$(SDKROOT)/System/Library/Frameworks/Cocoa.framework',
          '$(SDKROOT)/System/Library/Frameworks/OpenGL.framework',
        ],
      },
      'mac_bundle_resources': [
        '../src/English.lproj/InfoPlist.strings',
      ],
      'xcode_settings': {
        'INFOPLIST_FILE': '../src/CocoaWithGYP-Info.plist',
        'DYLIB_INSTALL_NAME_BASE': '@executable_path/../../..',
        'CLANG_ENABLE_OBJC_ARC': 'YES',
        'GCC_INLINES_ARE_PRIVATE_EXTERN': 'YES', # '-fvisibility-inlines-hidden'
        'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES', # '-fvisibility=hidden'
      },
    },
  ],# "targets"
}
