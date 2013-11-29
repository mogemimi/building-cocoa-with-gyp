//
//  Copyright (C) <year> <copyright holders>.
//

#import <CocoaWithGYP/CocoaOpenGLView.h>
#include <OpenGL/gl.h>
#include <array>

@implementation CocoaOpenGLView

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
		NSOpenGLPFAWindow,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFADepthSize, 24,
		NSOpenGLPFAStencilSize, 8,
		NSOpenGLPFAColorSize, 24,
		NSOpenGLPFAAlphaSize, 8,
		NSOpenGLPFANoRecovery,
		NSOpenGLPFAAccelerated,
		0
	};
	return [[NSOpenGLPixelFormat alloc] initWithAttributes:attribute];
}

- (void)prepareOpenGL
{
	if ([self openGLContext]) {
		return;
	}
        
	if ([self pixelFormat] == nil) {
		[self setPixelFormat:[CocoaOpenGLView defaultPixelFormat]];
	}
        
	[self setOpenGLContext:[[NSOpenGLContext alloc] initWithFormat:pixelFormat_ shareContext: nil]];
	[[self openGLContext] makeCurrentContext];
}

- (void)clearGLContext
{
	if (openGLContext_ != nil) {
		[self setOpenGLContext:nil];
	}
}

- (void)update
{
}

- (void)reshape
{
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
	
	glFlush();
	
	[context flushBuffer];
}

@end
