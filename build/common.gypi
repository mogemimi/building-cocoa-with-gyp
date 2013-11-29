{
  'variables': {
    'conditions': [
      ['OS == "mac"', {
        'target_arch%': 'x64',
      }, {
        'target_arch%': 'ia32',
      }],
    ],
    #'target_arch%': '<(target_arch)',
  },
  'target_defaults': {
    'default_configuration': 'Release',
    'defines': [],
    'conditions': [
      ['target_arch == "arm"', {
        # arm
      }], # target_archs == "arm"
      ['target_arch == "ia32"', {
        # ia32
      }], # target_archs == "ia32"
      ['target_arch == "mipsel"', {
        # mipsel
      }], # target_archs == "mipsel"
      ['target_arch == "x64"', {
        'xcode_settings': {
          'ARCHS': ['x86_64'], # For the non-fragile objective-c ABI.
        },
      }], # target_archs == "x64"
    ],
    'configurations': {
      'Debug': {
        'defines': ['DEBUG=1'],
        'cflags': ['-g', '-O0'],
        'xcode_settings': {
          'OTHER_CFLAGS': ['-g'],
          'GCC_OPTIMIZATION_LEVEL': '0', # -O0
        },
      }, # Debug
      'Release': {
        'cflags': ['-O3'],
        'xcode_settings': {
          'GCC_OPTIMIZATION_LEVEL': '3', # -O3
        },
      }, # Release
    },
  }, # target_defaults
}
