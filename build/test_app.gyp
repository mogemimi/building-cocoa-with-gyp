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
      'target_name': 'test_app',
      'product_name': 'TestApp',
      'type': 'executable',
      'mac_bundle': 1,
      'dependencies': [
        'framework.gyp:cocoa_with_gyp',
      ],
      'include_dirs': [
        '../include',
      ],
      'sources': [
        '../test/main.mm',
        '../test/TestApp-Prefix.pch',
        '../test/AppDelegate.h',
        '../test/AppDelegate.mm',
      ],
      'link_settings': {
        'libraries': [
          '$(SDKROOT)/System/Library/Frameworks/Cocoa.framework',
        ],
      },
      'mac_bundle_resources': [
        '../test/Base.lproj/MainMenu.xib',
        '../test/English.lproj/InfoPlist.strings',
      ],
      'xcode_settings': {
        'INFOPLIST_FILE': '../test/TestApp-Info.plist',
        'CLANG_ENABLE_OBJC_ARC': 'YES',
      },
    },
  ],# "targets"
}
