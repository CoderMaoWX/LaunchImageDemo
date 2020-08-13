//
//  SecondVC.m
//  LaunchImageDemo
//
//  Created by 610582 on 2020/8/13.
//  Copyright © 2020 GFZ. All rights reserved.
//

#import "SecondVC.h"

@interface SecondVC ()
@property (nonatomic, strong) UIStackView * verticalStackView;
@property (nonatomic, strong) UIStackView * horizontalStackView;
@end

@implementation SecondVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor groupTableViewBackgroundColor];
    
    [self.view addSubview:self.horizontalStackView];
    self.horizontalStackView.frame = CGRectMake(10, 100, [UIScreen mainScreen].bounds.size.width-20, 100);
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    UILabel * lbl = [self textLbl];
    
    [self.horizontalStackView addArrangedSubview:lbl];
    [UIView animateWithDuration:1 animations:^{
        [self.horizontalStackView layoutIfNeeded];
    }];
    
    //测试 NSInvocation
    [self testInvocationMethod];
}

- (UILabel *)textLbl{
    UILabel * lbl = [UILabel new];
    CGFloat hue = ( arc4random() % 256 / 256.0 ); //0.0 to 1.0
    CGFloat saturation = ( arc4random() % 128 / 256.0 ) + 0.5; // 0.5 to 1.0,away from white
    CGFloat brightness = ( arc4random() % 128 / 256.0 ) + 0.5; //0.5 to 1.0,away from black
    lbl.backgroundColor = [UIColor colorWithHue:hue saturation:saturation brightness:brightness alpha:1];
    lbl.text = @"文字";
    return lbl;
}

#pragma mark --- 懒加载

- (UIStackView *)horizontalStackView{
    if (_horizontalStackView == nil) {
        _horizontalStackView = [UIStackView new];
        _horizontalStackView.axis = UILayoutConstraintAxisHorizontal;
        _horizontalStackView.distribution = UIStackViewDistributionFillEqually;
        _horizontalStackView.spacing = 10;
        _horizontalStackView.alignment = UIStackViewAlignmentFill;
        _horizontalStackView.backgroundColor = [UIColor yellowColor];
    }
    return _horizontalStackView;
}

/**
 * NSInvocation;用来包装方法和对应的对象，它可以存储方法的名称，对应的对象，对应的参数,
 * NSMethodSignature：签名：再创建NSMethodSignature的时候，必须传递一个签名对象， 签名对象的作用：用于获取参数的个数和方法的返回值
 */
 - (void)testInvocationMethod {
    //创建签名对象的时候不是使用NSMethodSignature这个类创建，而是方法属于谁就用谁来创建
    NSMethodSignature*signature = [SecondVC instanceMethodSignatureForSelector:@selector(sendMessageWithNumber:WithContent:)];
    //1、创建NSInvocation对象
    NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:signature];
    invocation.target = self;
    //invocation中的方法必须和签名中的方法一致。
    invocation.selector = @selector(sendMessageWithNumber:WithContent:);
    /*第一个参数：需要给指定方法传递的值, 第一个参数需要接收一个指针，也就是传递值的时候需要传递地址*/
    //第二个参数：需要给指定方法的第几个参数传值
    NSString*number = @"1111";
    //注意：设置参数的索引时不能从0开始，因为0已经被self占用，1已经被_cmd占用
    [invocation setArgument:&number atIndex:2];
    NSString*number2 = @"啊啊啊";
    [invocation setArgument:&number2 atIndex:3];
    //2、调用NSInvocation对象的invoke方法
    //只要调用invocation的invoke方法，就代表需要执行NSInvocation对象中制定对象的指定方法，并且传递指定的参数
    [invocation invoke];
}

- (void)sendMessageWithNumber:(NSString*)number WithContent:(NSString*)content{
    NSLog(@"number: %@, content: %@",number,content);
}

@end
