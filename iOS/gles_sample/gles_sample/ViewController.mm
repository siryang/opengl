#import "ViewController.h"
#import <GLKit/GLKView.h>
#include "../source/triangle.h"

@interface ViewController ()
@property (strong, nonatomic) EAGLContext* context;
@end

@implementation ViewController
@synthesize context;

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
    gles::DemoEntry::init();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    NSLog(@"drawInRect");
    gles::DemoEntry::draw();
}

- (void)update {
    NSLog(@"update");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
