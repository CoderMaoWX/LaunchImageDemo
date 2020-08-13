//
//  VCManager.m
//  LaunchImageDemo
//
//  Created by 610582 on 2020/8/13.
//  Copyright © 2020 GFZ. All rights reserved.
//

#import "VCManager.h"

@implementation VCManager


- (IBAction)kissMeAction:(UIButton *)sender {
    NSLog(@"sender: %@", sender.currentTitle);
    
}


- (IBAction)testMethodAction {
    NSLog(@"%@", NSStringFromSelector(_cmd));
}


@end
