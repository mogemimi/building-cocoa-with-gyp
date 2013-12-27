//
//  Copyright (C) <year> <copyright holders>.
//

#import <CocoaWithGYP/CocoaOpenGLView.h>
#include <memory>
#include <array>
#include <OpenGL/gl3.h>
#include "QuadRenderer.h"

using BuildingCocoaWithGyp::QuadRenderer;

@implementation CocoaOpenGLView
{
	std::unique_ptr<QuadRenderer> quadRenderer;
}

@synthesize openGLContext = openGLContext_;
@synthesize pixelFormat = pixelFormat_;

- (id)initWithFrame:(NSRect)frameRect
{
	self = [super initWithFrame:frameRect];
	if (self) {
		[[NSNotificationCenter defaultCenter] addObserver:self
			selector:@selector(_surfaceNeedsUpdate:)
			name:NSViewGlobalFrameDidChangeNotification
			object:self];
	}
	return self;
}

- (void)_surfaceNeedsUpdate:(NSNotification*)notification
{
	[self update];
}

- (void)awakeFromNib
{
	[super awakeFromNib];
	
	[self prepareOpenGL];
}

+ (NSOpenGLPixelFormat*)defaultPixelFormat
{
	NSOpenGLPixelFormatAttribute attribute[] = {
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFANoRecovery,
		NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
		NSOpenGLPFADepthSize, 24,
		NSOpenGLPFAStencilSize, 8,
		NSOpenGLPFAColorSize, 24,
		NSOpenGLPFAAlphaSize, 8,
		0
	};
	return [[NSOpenGLPixelFormat alloc] initWithAttributes:attribute];
}

- (void)prepareOpenGL
{
	if ([self openGLContext]) {
		return;
	}

	[self createOpenGLContext];
	
	
	quadRenderer.reset(new QuadRenderer());
}

- (void)createOpenGLContext
{
	if ([self pixelFormat] == nil) {
		[self setPixelFormat:[CocoaOpenGLView defaultPixelFormat]];
	}

	[self setOpenGLContext:[[NSOpenGLContext alloc] initWithFormat:pixelFormat_ shareContext: nil]];
	[[self openGLContext] makeCurrentContext];
}

- (void)clearGLContext
{
	quadRenderer.reset();

	if (openGLContext_ != nil) {
		[self setOpenGLContext:nil];
	}
}

- (void)update
{
}

- (void)reshape
{
	GLint width = [self frame].size.width;
	GLint height = [self frame].size.height;
	glViewport(0, 0, width, height);
}

- (void)lockFocus
{
	NSOpenGLContext* context = [self openGLContext];
	
	[super lockFocus];
	if ([context view] != self) {
		[context setView:self];
	}
	[context makeCurrentContext];
}

-(void)viewDidMoveToWindow
{
	NSOpenGLContext* context = [self openGLContext];
	
	[super viewDidMoveToWindow];
	
	if ([self window] == nil) {
		[context clearDrawable];
	}
}

- (void)drawRect:(NSRect)dirtyRect
{
	NSOpenGLContext* context = [self openGLContext];
	
	[context makeCurrentContext];

	std::array<GLfloat, 3> CornflowerBlue = { 100/255.f, 149/255.f, 237/255.f };
	
	glClearColor(CornflowerBlue[0], CornflowerBlue[1], CornflowerBlue[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	quadRenderer->Draw();
	
	glFlush();
	
	[context flushBuffer];
}

@end
