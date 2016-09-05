#import "ViewController.h"
#import <GLKit/GLKView.h>
#include "../source/triangle.h"

@interface ViewController ()
@property (strong, nonatomic) EAGLContext* context;
@end

@implementation ViewController
@synthesize context;

gles::DemoEntry g_glesDemo;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.

    // create glcontext
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    [EAGLContext setCurrentContext:self.context];

    // initialize glview
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;

    // initialize demo
    g_glesDemo.init(800, 600);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    // NSLog(@"drawInRect");
    g_glesDemo.draw();
    [context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)update {
    // NSLog(@"update");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
