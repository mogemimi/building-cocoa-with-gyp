//
//  Copyright (C) <year> <copyright holders>.
//

#import <Cocoa/Cocoa.h>
#include <memory>

@class NSOpenGLContext, NSOpenGLPixelFormat;

@interface CocoaOpenGLView : NSView
{
@private
	NSOpenGLContext*     openGLContext_;
	NSOpenGLPixelFormat* pixelFormat_;
}

@property (nonatomic, retain) NSOpenGLContext*     openGLContext;
@property (nonatomic, retain) NSOpenGLPixelFormat* pixelFormat;

- (id)initWithFrame:(NSRect)frameRect;

- (void)prepareOpenGL;
- (void)clearGLContext;

- (void)update;
- (void)reshape;

@end
