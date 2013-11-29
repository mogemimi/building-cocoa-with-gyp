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
      'MACOSX_DEPLOYMENT_TARGET': '10.7', # OS X Deployment Target: 10.7
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
        'OTHER_CPLUSPLUSFLAGS': ['-std=c++11','-stdlib=libc++'],
        'OTHER_LDFLAGS': ['-stdlib=libc++'],
        'CLANG_ENABLE_OBJC_ARC': 'YES',
      },
    },
  ],# "targets"
}
